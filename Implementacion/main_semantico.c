/**************************************
** main.c                            **
** Programa principial               **
**************************************/

#include <stdio.h>
#include <stdlib.h>
#include "tabla.h"

extern FILE *yyin;
int     yyparse();

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

// Programa sencillo que analiza sintácticamente,
// imprime los errores léxicos y sintácticos y
// devuelve 1 si hubo algún error irrecuperable y 0 en otro caso
int main(int argc, char * argv[]) {
  /*
   * Ejemplo de prueba inútil de la tabla de símbolos
   */
  const entrada_ts A = {procedimiento, "main", desconocido, 0};
  const entrada_ts B = {variable, "a", entero, 0};
  const entrada_ts MARCA_BLOQUE = {marca, "1marca", desconocido, 0};

  pushTS(A);
  pushTS(MARCA_BLOQUE);
  pushTS(B);
  salBloqueTS();

  //yyin = abrir_entrada(argc, argv);
  //return yyparse();
}
