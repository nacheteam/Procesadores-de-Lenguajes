#ifndef __YYERROR_H__
#define __YYERROR_H__

extern int linea;

// Implementación de yyerror
void yyerror(char * msg) {
  fprintf(stderr, "[Línea %d] %s\n", linea, msg);
}

#endif
