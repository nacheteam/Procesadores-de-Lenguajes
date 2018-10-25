/**************************************
** sintactico.c                      **
** Analizador sintático del lenguaje **
**************************************/

#include <stdio.h>
#include <stdlib.h>

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

// Programa sencillo que analiza sintácticamente, imprime los errores
// léxicos y sintácticos y devuelve 1 si hubo algún error sintáctico
// (trata de recuperar los errores de léxico) y 0 en otro caso
int main(int argc, char * argv[]) {
  yyin = abrir_entrada(argc, argv);
  return yyparse();
}
