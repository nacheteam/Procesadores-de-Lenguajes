#ifndef __YYERROR_H__
#define __YYERROR_H__

extern int linea;
extern char *yytext;           // assumes yytext is still valid from when the syntax error was found!

// Implementación de yyerror
void yyerror(const char * msg);

#endif
