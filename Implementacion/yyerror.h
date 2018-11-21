#ifndef __YYERROR_H__
#define __YYERROR_H__

extern int linea;
extern char *yytext;

void yyerror(const char * msg);

#endif
