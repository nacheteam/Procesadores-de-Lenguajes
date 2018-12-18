#include <stdlib.h>
#include "string.h"
#include "file_io.h"

char DEFAULT_MAIN[] = "salida.c";
FILE * main_file = NULL;

char DEFAULT_PROC[] = "dec_dat";
FILE * proced_file = NULL;

/* Abre fichero y comprueba */
FILE * abrir(char * nombre, char* modo){
  FILE * f;
  f = fopen(nombre, modo);

  if (f == NULL) {
    fprintf(stderr, "No se ha podido abrir el fichero %s", nombre);
    exit(1);
  }

  return f;
}

FILE * abrir_entrada(int argc, char* argv[]) {
  FILE *f = NULL;
  int pos_archivo = 1;
  while (pos_archivo < argc && strcmp("-o", argv[pos_archivo]) == 0)
    pos_archivo += 2;

  if (pos_archivo < argc)
    f = abrir(argv[pos_archivo], "r");
  else
    printf("Leyendo código a través de entrada estándar...\n");

  return f;
}


char * nombre_salida(int argc, char* argv[]){
  FILE *f = (FILE*) stdout;
  int pos_archivo = 1;
  while (pos_archivo < argc-1 && strcmp("-o", argv[pos_archivo]) != 0)
    pos_archivo++;

  if (pos_archivo < argc-1)
    return argv[pos_archivo];
  else
    return DEFAULT_MAIN;
}

FILE * abrir_salida(int argc, char* argv[]) {
  main_file = abrir(nombre_salida(argc, argv), "w");
  return main_file;
}



int profundidad = 0;
extern FILE * yyout;

/* Entra en un procedimiento */
void entraProced(){
  profundidad++;
  if(!proced_file)
    proced_file = abrir(DEFAULT_PROC, "w");
  yyout = proced_file;
}

/* Sal de un procedimiento */
void salProced(){
  profundidad--;
  if(profundidad == 0)
    yyout = main_file;
}
