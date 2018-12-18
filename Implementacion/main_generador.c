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
extern int error;
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


int main(int argc, char * argv[]) {
  yyin = abrir_entrada(argc, argv);
  yyout = abrir_salida(argc, argv); // TODO: ¿escribir código inicial aquí o en el .y?
  char* nombre = nombre_salida(argc, argv);
  int result =  yyparse();
  if(error){
    if(error == 1)
      fprintf(stderr, "Se ha detectado 1 error, compilación abortada.\n");
    else
      fprintf(stderr, "Se han detectado %d errores, compilación abortada.\n", error);
    remove(nombre);
    remove("dec_dat");
  }
}
