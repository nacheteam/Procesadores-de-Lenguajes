#include <stdio.h>
#include <string.h>

/* Código adaptado de las diapositivas del tema 7 y del guión de prácticas apéndice F
 (diapositiva 75)
 TODO: No tengo muy claro dónde debería ir este código*/


typedef enum {
  marca, // Indica que la entrada es una marca de principio de bloque
  procedimiento,
  variable, // variable local
  parametroFormal  // parámetro de un procedimiento situado en una entrada anterior de la tabla
} tipoEntrada;


/* Tipo de dato.
   Sólo aplicable cuando sea funcion, variable o parametroFormal*/
typedef enum {
  entero,
  real,
  booleano,
  caracter,
  lista,
  desconocido
} tipoDato;

typedef struct {
  int token; // Código del token
  TipoDato tipo; // tipo del token
  char * lexema; // Nombre del token
} atributos

#define YYSTYPE atributos

/*******************************************************/
/* DEFINICIÓN DE LOS ELEMENTOS DE LA TABLA DE SÍMBOLOS */
/*******************************************************/

#define MAX_TS 1000


typedef struct entrada_ts {
  TipoEntrada tipo_entrada; // Tipo de entrada
  char * nombre; // nombre del identificador
  TipoDato tipo_dato; // Tipo del identificador
  int parametros; // Número de parámetros
};

struct entrada_ts TS[MAX_TS];
long int tope = 0; // Índice de la tabla de símbolos


/* ACCIONES SOBRE LA TABLA DE SÍMBOLOS */


/* Inserta entrada en TS */
void pushTS(entrada_ts entrada){
  if(tope == MAX_TS -1){
    printf("\n[Línea %d] Error: La tabla de símbolos está llena", yylineno);
    exit(2);
  }
  TS[tope] = entrada;
  tope++;
}

/* Halla índice de identificador en TS */
void findTS(char * identificador){
  for(int j = 0; j < tope; j++)
    if(!strcmp(TS[j].nombre, identificador))
      return j;

  return -1;
}

/*
 * Introduce un identificador en la tabla de símbolos
 */
void pushVar(char* identificador, TipoDato tipo_dato){

  if(findTS(identificador) != -1){
    printf("\n[Línea %d] Error semántico: Identificador duplicado %s\n", yylineno, identificador);
    return;
  }

  entrada_ts entrada = {
    variable,
    strdup(identificador),
    tipo_dato,
    0
  };

  pushTS(entrada);
}

/*
 * Devuelve el tipo de identificador en TS
 * Si no existe el tipo es "desconocido"
 */

TipoDato tipoTS(char * identificador){
  int j = findTS(identificador);

  if(j != -1)
    return TS[j].tipo_dato;

  printf("\n[Línea %d] Error semántico: Identificador no declarado %s\n", yylineno, identificador);
  return desconocido;
}


// Entrada que indica comienzo de bloque
const entrada_ts * MARCA_BLOQUE = {marca, "1marca", desconocido, 0};

/* Añade a la tabla de símbolos marca de comienzo
 */
void entraBloqueTS(){
  pushTS(MARCA_BLOQUE);
}


/* Sal de bloque y elimina de la tabla de símbolos todos los símbolos hasta la última marca
 */
void popTS(){
  for(int j = i; j > 0; j--){
    if(TS[j].tipo_entrada == marca){
      i = j - 1; // TODO: Podría darse j == 0?
      return;
    }
  }

  printf("\n[Linea %d] Error de implementación, se intentó salir de un bloque cuando no hay", yylineno);
}
