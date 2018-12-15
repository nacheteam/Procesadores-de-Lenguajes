/*************************************************
** main_semantico.c                             **
** Programa principial del analizador semántico **
*************************************************/

#include "file_io.h"
#include "tabla.h"

extern FILE *yyin;
int     yyparse();

// Programa sencillo que analiza sintáctica y semánticamente,
// imprime los errores léxicos, sintácticos y semánticos y
// devuelve 1 si hubo algún error sintáctico irrecuperable y 0 en otro caso
int main(int argc, char * argv[]) {
  yyin = abrir_entrada(argc, argv);
  return yyparse();
}
