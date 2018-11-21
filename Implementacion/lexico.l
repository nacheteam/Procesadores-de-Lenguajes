%{
  /***********************************
  ** lexico.l                       **
  ** Analizador léxico del lenguaje **
  ***********************************/

  #include <stdio.h>
  #include "y.tab.h"    // Contiene los códigos asociados a los tokens
  #include "yyerror.h"  // Implementación de yyerror
  #define LONGITUD_ERROR 256
  char buffer_error[LONGITUD_ERROR];
  int linea = 1;    // En caso de error se imprimirá la línea donde se dio, empezando en 1
  int error = 0;    // El programa devuelve 1 si ha habido errores de léxico
%}

%option noyywrap

 // Definiciones

natural     [0-9]+
exponente   E[+-]?{natural}
hex         0x[0-9a-f]+
numero      {natural}(\.{natural})?{exponente}?|{hex}
ascii       [^\"'\\]|\\[\"'nt]
cadena      \"{ascii}*\"
literal     {numero}|\'{ascii}\'|"True"|"False"
tbase       "int"|"bool"|"char"|"double"
id          [a-zA-Z][a-zA-Z0-9]*
com_linea   (\/\/[^\n]*\n)

%%

 // Reglas

"++"        return INCR;
"--"        return DECR;
"="         return ASIGN;
"if"        return IF;
"else"      return ELSE;
"while"     return WHILE;
"repeat"    return REPEAT;
"until"     return UNTIL;
"read"      return READ;
"write"     return WRITE;
"begin"     return VARBEGIN;
"end"       return VAREND;
{cadena}    return CADENA;
{literal}   return LITERAL;
"list of"   return LISTOF;
{tbase}     return TIPOBASE;
"main()"    return MAIN;
{id}        return ID;
"("         return PARIZQ;
")"         return PARDER;
[+-]        return SIGNO;
"<<"|">>"   return UNARIODER;
[!#?$]      return UNARIOIZQ;
"||"        return OR;
"&&"        return AND;
"^"         return XOR;
[=!]=       return COMP_IG;
[<>]=?      return COMP_MM;
[*/%]       return PROD_DIV_MOD;
"**"        return EXP;
"@"         return ARROBA;
"@@"        return ARROBARROBA;
"{"         return LLAIZQ;
"}"         return LLADER;
"["         return CORIZQ;
"]"         return CORDER;
";"         return PYC;
","         return COMA;
[ \t]+      ;        // Se ignoran los espacios en blanco
{com_linea} ++linea; // Se ignoran los comentarios al final de línea
\n          ++linea;
.           error = 1; snprintf(buffer_error, LONGITUD_ERROR, "Error léxico: '%s' no se identifica con ningún token conocido\n", yytext); yyerror(buffer_error);

%%

 // Procedimientos. No se implementa ni declara la función main si no se define
 // MAIN_LEXICO; así solo se usa en el ejecutable del analizador léxico

#ifdef MAIN_LEXICO
int main() {
  int val = yylex();
  while (val != 0) {
    printf(" %d <- %s\n", val, yytext);
    val = yylex();
  }

  return error;
}
#endif
