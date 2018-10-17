%{
  #include <stdio.h>
  #include "tabla.h"
  int linea = 1;    // En caso de error se imprimirá la línea donde se dio, empezando en 1
  int error = 0;    // El programa devuelve 1 si ha habido errores de léxico
%}

 // Definiciones

natural     [0-9]+
exponente   E[+-]?{natural}
hex         0x[0-9a-f]+
numero      {natural}(\.{natural})?{exponente}?|{hex}
ascii       [^\"\\]|\\[\"nt]
cadena      \"{ascii}*\"
literal     {numero}|\'{ascii}\'|"True"|"False"
tbase       "int"|"bool"|"char"|"double"
id          [a-zA-Z][a-zA-Z0-9]*
binario     [*/^%]|[=!]=|[<>]=?|&&|"||"|"**"

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
{cadena}    return CADENA;
{literal}   return LITERAL;
"list of"   return LISTOF;
{tbase}     return TIPOBASE;
"main()"    return MAIN;
{id}        return ID;
"("         return PARIZQ;
[+-]        return SIGNO;
"<<"|">>"   return UNARIODER;
[!#?$]      return UNARIOIZQ;
{binario}   return BINARIO;
"@"         return ARROBA;
"{"         return LLAIZQ;
"}"         return LLADER;
")"         return PARDER;
"["         return CORIZQ;
"]"         return CORDER;
";"         return PYC;
","         return COMA;
[ \t]       ;  // Se ignoran los espacios en blanco
\n          ++linea;
.           error = 1; printf("Error léxico en la línea %d: token %s\n", linea, yytext);

%%

 // Procedimientos

int main() {
  int val = yylex();
  while (val != 0) {
    printf(" %d <- %s\n", val, yytext);
    val = yylex();
  }

  return error;
}
