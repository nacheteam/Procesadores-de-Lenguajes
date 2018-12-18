#include <stdlib.h>
#include "string.h"
#include "file_io.h"

FILE * abrir_entrada(int argc, char* argv[]) {
  FILE *f = NULL;
  int pos_archivo = 1;
  while (pos_archivo < argc && strcmp("-o", argv[pos_archivo]) == 0)
    pos_archivo += 2;
  if (pos_archivo < argc) {
    f = fopen(argv[pos_archivo], "r");
    if (f == NULL) {
      fprintf(stderr, "No se ha podido abrir el fichero %s", argv[1]);
      exit(1);
    }
  } else
    printf("Leyendo código a través de entrada estándar...\n");

  return f;
}


FILE * abrir_salida(int argc, char* argv[]) {
  FILE *f = (FILE*) stdout;
  int pos_archivo = 1;
  while (pos_archivo < argc-1 && strcmp("-o", argv[pos_archivo]) != 0)
    pos_archivo++;

  if (pos_archivo < argc-1) {
    pos_archivo++;
    f = fopen(argv[pos_archivo], "w");
  }
  // else f = fopen("salida.c", "w"); // TODO: decidir entre imprimir a salida estándar o a un archivo por defecto

  if (f == NULL) {
    fprintf(stderr, "No se ha podido abrir el fichero %s", argv[pos_archivo]);
    exit(1);
  }

  return f;
}

void cerrar_salida(FILE * f) {
  fclose(f);
}
