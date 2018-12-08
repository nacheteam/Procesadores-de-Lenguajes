#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tabla.h"
#include "y.tab.h"

/* ACCIONES SOBRE LA TABLA DE SÍMBOLOS */

long int tope = 0;


/********************/
/* ACCIONES BÁSICAS */
/********************/

/* Inserta entrada en TS */
void insertaTS(entrada_ts entrada){
  if(tope >= MAX_TS){
    printf("\n[Línea %d] Error: La tabla de símbolos está llena", yylineno);
    exit(2);
  }

  TS[tope] = entrada;
  tope++;
}

/* Halla índice de identificador de variable o procedimiento en TS
 * Nota: NO funciona con parámetro
*/
int findTS(char * identificador){
  for(int j = 0; j < tope; j++)
    if(!strcmp(TS[j].nombre, identificador) &&
       (TS[j].tipo_entrada == variable || TS[j].tipo_entrada == procedimiento))
      return j;
  return -1;
}



/*
 * Devuelve el tipo de identificador en TS
 * Si no existe el tipo es "desconocido"
 * Nota: para los parámetros se añaden después como variable así que esto sirve.
 */

TipoDato tipoTS(char * identificador){
  int j = findTS(identificador);

  if(j != -1)
    return TS[j].tipo_dato;

  printf("\n[Línea %d] Error semántico: Identificador no declarado %s\n", yylineno, identificador);
  return desconocido;
}


///////////////////////////////////////////////////

/*******************/
/* IMPRESIÓN DE TS */
/*******************/

char * imprimeTipoE(TipoEntrada tipo){
  switch (tipo) {
  case marca: return "marca";
  case procedimiento: return "procedimiento";
  case variable: return "variable";
  case parametroFormal: return "parámetro";
  default: return "error";
  }
}

char * imprimeTipoD(TipoDato tipo){
  switch (tipo) {
  case entero: return "entero";
  case real: return "real";
  case booleano: return "booleano";
  case caracter: return "carácter";
  case listaentero: return "lista de enteros";
  case listareal: return "lista de reales";
  case listabool: return "lista de booleanos";
  case listachar: return "lista de caracteres";
  case desconocido: return "desconocido";
  default: return "error";
  }
}

void imprimeTS(){
  char sangria[] = "\0";
  printf("Tabla de símbolos en la línea %d:\n", yylineno);
  for(int i = 0; i < tope; i++)
    if(TS[i].tipo_entrada == marca){
     strcat(sangria, "  ");
     printf("%s↳ [marca]\n", sangria);
    } else{
      printf("%s%s: '%s'", sangria, imprimeTipoE(TS[i].tipo_entrada), TS[i].nombre);

      if(TS[i].tipo_entrada == variable || TS[i].tipo_entrada == parametroFormal)
        printf(" de tipo %s\n", imprimeTipoD(TS[i].tipo_dato));
      else
        printf(" con %d parámetros\n", TS[i].parametros);
    }
}


//////////////////////////////////////////////////////

/*******************************/
/* ENTRADA Y SALIDA DE BLOQUES */
/*******************************/

/* Añade a la tabla de símbolos marca de comienzo
 */
void entraBloqueTS(){
  // Entrada que indica comienzo de bloque
  const entrada_ts MARCA_BLOQUE = {marca, "1marca", desconocido, 0};
  insertaTS(MARCA_BLOQUE);

  // TODO: Incluir aquí los parámetros como variables si se entra en un bloque de subprograma.
}


/* Sal de bloque y elimina de la tabla de símbolos todos los símbolos hasta la última marca
 */
void salBloqueTS(){
  imprimeTS();

  for(int j = tope - 1; j > 0; j--){
    if(TS[j].tipo_entrada == marca){
      tope = j - 1;
      return;
    }
  }

  printf("\n[Linea %d] Error de implementación, se intentó salir de un bloque cuando no hay", yylineno);
}


/**********************/
/* INSERCIÓN EN LA TS */
/**********************/

// Lee el tipo de dato
TipoDato leeTipoDato(char * nombre_tipo){
  if(!strcmp(nombre_tipo, "int"))
    return entero;
  else if(!strcmp(nombre_tipo, "double"))
    return real;
  else if(!strcmp(nombre_tipo, "bool"))
    return booleano;
  else if(!strcmp(nombre_tipo, "char"))
    return caracter;
  else if(!strcmp(nombre_tipo, "list of int"))
    return listaentero;
  else if(!strcmp(nombre_tipo, "list of double"))
    return listareal;
  else if(!strcmp(nombre_tipo, "list of bool"))
    return listabool;
  else if(!strcmp(nombre_tipo, "list of char"))
    return listachar;

  printf("\n[Linea %d] Error de implementación, '%s' no es un tipo válido", yylineno, nombre_tipo);
  return desconocido;
}

/*
 * Introduce un identificador en la tabla de símbolos
 */
void insertaVar(char* identificador, char * nombre_tipo){

  if(findTS(identificador) != -1){
    printf("\n[Línea %d] Error semántico: Identificador duplicado '%s'\n", yylineno, identificador);
    return;
  }

  TipoDato tipo_dato = leeTipoDato(nombre_tipo);

  entrada_ts entrada = {
    variable,
    strdup(identificador),
    tipo_dato,
    0
  };

  insertaTS(entrada);
}

// Posición en la tabla de símbolos del último procedimiento
long int ultimoProcedimiento = -1;

/*
 * Inserta procedimiento en la tabla de símbolos
 */
void insertaProcedimiento(char * identificador){
  if(findTS(identificador) != -1){
    printf("\n[Línea %d] Error semántico: Identificador duplicado '%s'\n", yylineno, identificador);
    return;
  }

  entrada_ts entrada = {
    procedimiento,
    strdup(identificador),
    desconocido,
    0 // Inicialmente hay 0 parámetros
  };

  insertaTS(entrada);
  ultimoProcedimiento = tope - 1;
}

/*
 * Inserta parámetro formal en la tabla de símbolos
 */
void insertaParametro(char * identificador, char * nombre_tipo){
  if(findTS(identificador) != -1){
    printf("\n[Línea %d] Error semántico: Identificador duplicado '%s'\n", yylineno, identificador);
    return;
  }

  if(ultimoProcedimiento == -1){
    printf("\n[Línea %d] Error de implementación: Parámetro formal '%s' sin procedimiento anterior\n",
           yylineno, identificador);
    return;
  }

  TipoDato tipo_dato = leeTipoDato(nombre_tipo);
  entrada_ts entrada = {
    parametroFormal,
    strdup(identificador),
    tipo_dato,
    0 // Inicialmente hay 0 parámetros
  };

  insertaTS(entrada);
  TS[ultimoProcedimiento].parametros += 1;
}
