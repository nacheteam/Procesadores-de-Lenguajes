/***********************************************************
** main_generador.c                                       **
** Programa principial del generador de código intermedio **
***********************************************************/

#include <stdlib.h>
#include <assert.h>
#include "file_io.h"
#include "tabla.h"

extern FILE *yyin;
extern FILE *yyout;
int     yyparse();


int proxima_etiqueta = 0;
int proxima_temporal = 0;
#define TAM_BUFFER 13
char * etiqueta() {
  assert(proxima_etiqueta < 100000);
  char * buffer = malloc(sizeof(char) * TAM_BUFFER);
  snprintf(buffer, TAM_BUFFER, "etiqueta%d", proxima_etiqueta++);
  return buffer; // TODO: free
}
char * temporal() {
  assert(proxima_temporal < 1000000000);
  char * buffer = malloc(sizeof(char) * TAM_BUFFER);
  snprintf(buffer, TAM_BUFFER, "temp%d", proxima_temporal++);
  return buffer; // TODO: free
}

// TODO: debería no imprimir nada si hubo errores
int main(int argc, char * argv[]) {
  yyin = abrir_entrada(argc, argv);
  yyout = abrir_salida(argc, argv); // TODO: ¿escribir código inicial aquí o en el .y?
  int resultado = yyparse();
  cerrar_salida(yyout);
  return resultado;
}
