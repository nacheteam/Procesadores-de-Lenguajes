#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tabla.h"
#include "y.tab.h"

/* ACCIONES SOBRE LA TABLA DE SÍMBOLOS */

long int tope = 0;

/* Inserta entrada en TS */
void pushTS(entrada_ts entrada){
  if(tope >= MAX_TS){
    printf("\n[Línea %d] Error: La tabla de símbolos está llena", yylineno);
    exit(2);
  }

  TS[tope] = entrada;
  tope++;
}

/* Halla índice de identificador en TS */
int findTS(char * identificador){
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
const entrada_ts MARCA_BLOQUE = {marca, "1marca", desconocido, 0};

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
  case caracter: return "caracter";
  case lista: return "lista";
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

/* Añade a la tabla de símbolos marca de comienzo
 */
void entraBloqueTS(){
  pushTS(MARCA_BLOQUE);
}


/* Sal de bloque y elimina de la tabla de símbolos todos los símbolos hasta la última marca
 */
void salBloqueTS(){
  imprimeTS();

  for(int j = tope - 1; j > 0; j--){
    if(TS[j].tipo_entrada == marca){
      tope = j - 1; // TODO: Podría darse j == 0?
      return;
    }
  }

  printf("\n[Linea %d] Error de implementación, se intentó salir de un bloque cuando no hay", yylineno);
}
