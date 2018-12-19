#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tabla.h"
#include "y.tab.h"

// Muestra DEBUG sii DEBUG no es 0.
#define DEBUG 0

// Muestra tabla de símbolos antes de eliminar una marca sii IMPRIME no es 0
#define IMPRIME 0


#ifndef PUNTO
  #define PUNTO "↳"
#endif

/* ACCIONES SOBRE LA TABLA DE SÍMBOLOS */

// Tope de la tabla de símbolos
long int tope = 0;

// Posición en la tabla de símbolos del último procedimiento
long int ultimoProcedimiento = -1;

// Si los parámetros del último procedimiento se han insertado como variables
int subProg = 0;


// Número de bloques anidados
int prof = 0;

/********************/
/* ACCIONES BÁSICAS */
/********************/

/*
 * Devuelve una cadena con el tipo que corresponda en C
 */
char * tipoCStr(TipoDato tipo) {
  switch(tipo) {
    case entero:
    case booleano: // en C las variables booleanas son int
      return "int";
    case real:
      return "double";
    case caracter:
      return "char";
    case listaentero:
    case listabool:
    case listareal:
    case listachar:
      return "Lista";
    default:
      printf("[Línea %d] Error de implementación, %s no está asociado a ningún tipo nativo de C\n", linea, tipoStr(tipo));
      return "error";
  }
}

/*
 * Devuelve una cadena con el tipo del parámetro
 */
char* tipoStr(TipoDato tipo){
  switch (tipo) {
  case entero: return "entero";
  case real: return "real";
  case booleano: return "booleano";
  case caracter: return "caracter";
  case listaentero: return "listaentero";
  case listareal: return "listareal";
  case listabool: return "listabool";
  case listachar: return "listachar";
  case desconocido: return "desconocido";
  default: return "error";
  }
}

/* Inserta entrada en TS */
void insertaTS(entrada_ts entrada){
  if(DEBUG){
    printf("[insertaTS] entrada con nombre '%s' en línea %d\n", entrada.nombre, linea);
    fflush(stdout);
  }

  if(tope >= MAX_TS){
    printf("[%d] Error: La tabla de símbolos está llena\n", linea);
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

  printf("[%d] Error semántico: Identificador no declarado %s\n", linea, identificador);
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
     printf("%s%s [marca]\n", sangria, PUNTO);
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
    printf("[%d] Error semántico: Identificador duplicado '%s'\n", linea, identificador);
    return;
  }

  entrada_ts entrada = {
    variable,
    strdup(identificador),
    tipo_dato,
    0,
    {NULL, NULL}
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
    printf("[%d] Error semántico: Identificador duplicado '%s'\n", linea, identificador);
    return;
  }

  entrada_ts entrada = {
    procedimiento,
    strdup(identificador),
    desconocido,
    0, // Inicialmente hay 0 parámetros
    {NULL, NULL}
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

  if(ultimoProcedimiento == -1){
    printf("[%d] Error de implementación: Parámetro formal '%s' sin procedimiento anterior\n",
           linea, identificador);
    return;
  }

  TipoDato tipo_dato = leeTipoDato(nombre_tipo);
  entrada_ts entrada = {
    parametroFormal,
    strdup(identificador),
    tipo_dato,
    0, // Inicialmente hay 0 parámetros
    {NULL, NULL}
  };

  insertaTS(entrada);
  TS[ultimoProcedimiento].parametros += 1;
}

/*
 * Inserta el descriptor de una instrucción de control if/else
 */
void insertaIf(char * etiqueta_salida, char * etiqueta_else) {
  if(DEBUG){
    printf("[insertaIf] etiqueta de salida '%s'", etiqueta_salida);
    if (etiqueta_else != NULL)
      printf(" y etiqueta de else '%s'", etiqueta_else);

    printf(" en línea %d\n", linea);
    fflush(stdout);
  }

  entrada_ts entrada = {
    instrControl,
    "",
    desconocido,
    0,
    {etiqueta_salida, etiqueta_else}
  };

  insertaTS(entrada);
}

/*
 * Inserta el descriptor de una instrucción de control while
 */
void insertaWhile(char * etiqueta_entrada, char * etiqueta_salida) {
  if(DEBUG){
    printf("[insertaWhile] etiqueta de entrada '%s' y etiqueta de salida '%s' en línea %d\n", etiqueta_entrada, etiqueta_salida, linea);
    fflush(stdout);
  }

  entrada_ts entrada = {
    instrControl,
    "",
    desconocido,
    0,
    {etiqueta_salida, etiqueta_entrada}
  };

  insertaTS(entrada);
}

/*
 * Inserta el descriptor de una instrucción de control repeat/until
 */
void insertaRepeatUntil(char * etiqueta_entrada) {
  if(DEBUG){
    printf("[insertaRepeatUntil] etiqueta de entrada '%s' en línea %d\n", etiqueta_entrada, linea);
    fflush(stdout);
  }

  entrada_ts entrada = {
    instrControl,
    "",
    desconocido,
    0,
    {NULL, etiqueta_entrada}
  };

  insertaTS(entrada);
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

  prof++;
  const entrada_ts MARCA_BLOQUE = {marca, "[MARCA]", desconocido, 0, {NULL, NULL}};
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
    printf("Estoy saliendo de un bloque.\n");
    fflush(stdout);
  }

  if(IMPRIME)
    imprimeTS();

  prof--;
  for(int j = tope - 1; j >= 0; j--){
    if(TS[j].tipo_entrada == marca){
      tope = j;
      return;
    }
  }

  printf("[Linea %d] Error de implementación, se intentó salir de un bloque cuando no hay\n", linea);
}


/* Sale de bloque y elimina de la tabla de símbolos todos los símbolos
 * hasta el último descriptor de una instrucción de control
 */
void salEstructuraControl(){
  if(DEBUG){
    printf("Estoy saliendo de una estructura de control.\n");
    fflush(stdout);
  }

  if(IMPRIME)
    imprimeTS();

  for(int j = tope - 1; j >= 0; j--){
    if(TS[j].tipo_entrada == instrControl){
      tope = j;
      free(TS[j].etiquetasControl.EtiquetaSalida);
      free(TS[j].etiquetasControl.EtiquetaElse);
      return;
    }
  }

  printf("[Linea %d] Error de implementación, se intentó salir de una estructura de control cuando no hay\n", linea);
}

/* Encuentra el nombre de la etiqueta de salida de la estructura de control actual
 */
char * findGotoSalida(){
  for (int j = tope - 1; j >= 0; j--)
    if (TS[j].tipo_entrada == instrControl)
      return TS[j].etiquetasControl.EtiquetaSalida;

  printf("[Linea %d] Error de implementación, se intentó encontrar la etiqueta de salida de la estructura de control actual cuando no la hay\n", linea);
  return NULL;
}

/* Encuentra el nombre de la etiqueta de else de la estructura de control actual
 */
char * findGotoElse(){
  for (int j = tope - 1; j >= 0; j--)
    if (TS[j].tipo_entrada == instrControl)
      return TS[j].etiquetasControl.EtiquetaElse;

  printf("[Linea %d] Error de implementación, se intentó encontrar la etiqueta de else de la estructura de control actual cuando no la hay\n", linea);
  return NULL;
}


/* Indica si es main */
int esMain(){
  return prof == 1;
}
