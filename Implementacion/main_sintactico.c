/**************************************************
** main_sintactico.c                             **
** Programa principial del analizador sintáctico **
**************************************************/

#include "file_io.h"

extern FILE *yyin;
int     yyparse();

// Programa sencillo que analiza sintácticamente,
// imprime los errores léxicos y sintácticos y
// devuelve 1 si hubo algún error irrecuperable y 0 en otro caso
int main(int argc, char * argv[]) {
  yyin = abrir_entrada(argc, argv);
  return yyparse();
}
