#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tabla.h"
#include "y.tab.h"

// Muestra DEBUG sii DEBUG no es 0.
#define DEBUG 0

/* ACCIONES SOBRE LA TABLA DE SÍMBOLOS */

// Tope de la tabla de símbolos
long int tope = 0;

// Posición en la tabla de símbolos del último procedimiento
long int ultimoProcedimiento = -1;

// Si los parámetros del último procedimiento se han insertado como variables
int subProg = 0;


/********************/
/* ACCIONES BÁSICAS */
/********************/

/* Inserta entrada en TS */
void insertaTS(entrada_ts entrada){
  if(DEBUG){
    printf("[insertaTS] entrada con nombre '%s' en línea %d\n", entrada.nombre, linea);
    fflush(stdout);
  }

  if(tope >= MAX_TS){
    printf("[Línea %d] Error: La tabla de símbolos está llena\n", linea);
    fflush(stdout);
    exit(2);
  }

  TS[tope] = entrada;
  tope++;
}

/* Halla índice de identificador de variable o procedimiento en TS
 * Nota: NO funciona con parámetro
*/
int findTS(char * identificador){

  if(DEBUG){
    printf("[findTS] '%s' en línea %d\n", identificador, linea);
    fflush(stdout);
  }

  for(int j = tope - 1; j >= 0; j--)
    if(!strcmp(TS[j].nombre, identificador) &&
       (TS[j].tipo_entrada == variable || TS[j].tipo_entrada == procedimiento))
      return j; // Devuelve primera ocurrencia de abajo a arriba
  return -1;
}


/* Comprueba si un identificador está duplicado en su ámbito.
 * 0 si no es duplicado, 1 si sí lo es
 */
int esDuplicado(char * identificador){
  for(int j = tope - 1; j >= 0; j--){
    if(!strcmp(TS[j].nombre, identificador) &&
       (TS[j].tipo_entrada == variable || TS[j].tipo_entrada == procedimiento))
      return 1; // Si hay uno con el mismo nombre en el mismo bloque
    else if(TS[j].tipo_entrada == marca)
      return 0;
  }
}


/*
 * Devuelve el tipo de identificador en TS
 * Si no existe el tipo es "desconocido"
 * Nota: para los parámetros se añaden después como variable así que esto sirve.
 */

TipoDato tipoTS(char * identificador){
  if(DEBUG){
    printf("[tipoTS] Encuentra tipo de '%s' en línea %d\n", identificador, linea);
    fflush(stdout);
  }

  int j = findTS(identificador);

  if(j != -1)
    return TS[j].tipo_dato;

  printf("[Línea %d] Error semántico: Identificador no declarado %s\n", linea, identificador);
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
  char sangria[100] = "\0";
  printf("Tabla de símbolos en la línea %d:\n", linea);
  fflush(stdout);
  for(int i = 0; i < tope; i++){
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
}


//////////////////////////////////////////////////////

/**********************/
/* INSERCIÓN EN LA TS */
/**********************/

// Lee el tipo de dato
TipoDato leeTipoDato(char * nombre_tipo){
  if(DEBUG){
    printf("[leeTipoDato] Lee tipo '%s' en línea %d\n", nombre_tipo, linea);
    fflush(stdout);
  }

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

  printf("[Linea %d] Error de implementación, '%s' no es un tipo válido\n", linea, nombre_tipo);
  return desconocido;
}

/*
 * Introduce un identificador en la tabla de símbolos
 */

void insertaVarTipo(char * identificador, TipoDato tipo_dato){
  if(DEBUG){
    printf("[insertaVar] variable '%s' con tipo '%s' en línea %d\n",
           identificador, imprimeTipoD(tipo_dato), linea);
    fflush(stdout);
  }

  if(esDuplicado(identificador)){
    printf("[Línea %d] Error semántico: Identificador duplicado '%s'\n", linea, identificador);
    return;
  }

  entrada_ts entrada = {
    variable,
    strdup(identificador),
    tipo_dato,
    0
  };

  insertaTS(entrada);
}

void insertaVar(char* identificador, char * nombre_tipo){
  TipoDato tipo_dato = leeTipoDato(nombre_tipo);
  insertaVarTipo(identificador, tipo_dato);
}

/*
 * Inserta procedimiento en la tabla de símbolos
 */
void insertaProcedimiento(char * identificador){
  if(DEBUG){
    printf("[insertaProcedimiento] procedimiento '%s' en línea %d\n", identificador, linea);
    fflush(stdout);
  }

  if(esDuplicado(identificador)){
    printf("[Línea %d] Error semántico: Identificador duplicado '%s'\n", linea, identificador);
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
  subProg = 1; // Indica que hay que insertar parámetros como variables
}

/*
 * Inserta parámetro formal en la tabla de símbolos
 */
void insertaParametro(char * identificador, char * nombre_tipo){
  if(DEBUG){
    printf("[insertaParametro] '%s' con tipo '%s' en línea %d\n", identificador, nombre_tipo, linea);
    fflush(stdout);
  }

  if(esDuplicado(identificador)){
    printf("[Línea %d] Error semántico: Identificador duplicado '%s'\n", linea, identificador);
    return;
  }

  if(ultimoProcedimiento == -1){
    printf("[Línea %d] Error de implementación: Parámetro formal '%s' sin procedimiento anterior\n",
           linea, identificador);
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


/*******************************/
/* ENTRADA Y SALIDA DE BLOQUES */
/*******************************/

// Inserta parámetros como variables en la TS
void insertaParametrosComoVariables(){
  for (int i = 1; i <= TS[ultimoProcedimiento].parametros; i++)
    insertaVarTipo(TS[ultimoProcedimiento + i].nombre, TS[ultimoProcedimiento + i].tipo_dato);
}

/* Añade a la tabla de símbolos marca de comienzo
 */
void entraBloqueTS(){
  // Entrada que indica comienzo de bloque
  if(DEBUG){
    printf("Estoy entrando en un bloque.\n");
    fflush(stdout);
  }
  const entrada_ts MARCA_BLOQUE = {marca, "[MARCA]", desconocido, 0};
  insertaTS(MARCA_BLOQUE);

  if(subProg){
    insertaParametrosComoVariables();
    subProg = 0;
  }
}


/* Sal de bloque y elimina de la tabla de símbolos todos los símbolos hasta la última marca
 */
void salBloqueTS(){
  if(DEBUG){
    printf("Estoy saliendo en un bloque.\n");
    fflush(stdout);
  }
  imprimeTS();
  for(int j = tope - 1; j >= 0; j--){
    if(TS[j].tipo_entrada == marca){
      tope = j;
      return;
    }
  }

  printf("[Linea %d] Error de implementación, se intentó salir de un bloque cuando no hay\n", linea);
}
