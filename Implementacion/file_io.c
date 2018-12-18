#include <stdlib.h>
#include "string.h"
#include "file_io.h"

FILE * abrir_entrada(int argc, char* argv[]) {
  FILE *f = NULL;
  if (argc > 1) {
    f = fopen(argv[1], "r");
    if (f == NULL) {
      fprintf(stderr, "No se ha podido abrir el fichero %s", argv[1]);
      exit(1);
    }
  } else
    printf("Leyendo código a través de entrada estándar...\n");

  return f;
}

char DEFAULT[9] = "salida.c";

char * nombre_salida(int argc, char* argv[]){
  int pos_archivo = 1;
  while (pos_archivo < argc-1 && strcmp("-o", argv[pos_archivo]) != 0)
    pos_archivo++;

  if (pos_archivo < argc-1)
    return argv[pos_archivo];
  else
    return DEFAULT;
}

FILE * abrir_salida(int argc, char* argv[]) {
  FILE * f;
  char * nombre = nombre_salida(argc, argv);
  f = fopen(nombre, "w");

  if (f == NULL) {
    fprintf(stderr, "No se ha podido abrir el fichero %s", nombre);
    exit(1);
  }

  return f;
}
