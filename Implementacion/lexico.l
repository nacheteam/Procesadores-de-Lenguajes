%{
  /***********************************
  ** lexico.l                       **
  ** Analizador léxico del lenguaje **
  ***********************************/

  #include <stdio.h>
  #include "file_io.h"
  #include "tabla.h"
  #include "y.tab.h"  // Contiene los códigos asociados a los tokens
  #include "error.h"  // Presentación de errores
  #define LONGITUD_ERROR 256
  char buffer_error[LONGITUD_ERROR];
  int linea = 1;    // En caso de error se imprimirá la línea donde se dio, empezando en 1
  int error = 0;    // El programa devuelve 1 si ha habido errores de léxico

  #ifndef MAIN_LEXICO
    #define SET_LEXEMA { yylval.lexema = strdup(yytext); }
  #else
    #define SET_LEXEMA
  #endif
%}

%option noyywrap

 // Definiciones

natural     [0-9]+
exponente   [Ee][+-]?{natural}
hex         0x[0-9a-fA-F]+
numero      {natural}(\.{natural})?{exponente}?|{hex}
ascii       [^\"'\\]|\\[\"'nt]
cadena      \"{ascii}*\"
literal     {numero}|\'{ascii}\'|"True"|"False"
tbase       "int"|"bool"|"char"|"double"
id          [a-zA-Z][a-zA-Z0-9]*
com_linea   (\/\/[^\n]*\n)

%%

 // Reglas

"++"        {SET_LEXEMA; return INCR;}
"--"        {SET_LEXEMA; return DECR;}
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
{cadena}    {SET_LEXEMA; return CADENA;}
{literal}   {SET_LEXEMA; return LITERAL;}
"list of"   {SET_LEXEMA; return LISTOF;}
{tbase}     {SET_LEXEMA; return TIPOBASE;}
"main()"    return MAIN;
"void"      return PROCED;
{id}        {SET_LEXEMA; return ID;}
"("         return PARIZQ;
")"         return PARDER;
[+-]        {SET_LEXEMA; return SIGNO;}
"<<"|">>"   {SET_LEXEMA; return UNARIODER;}
[!#?$]      {SET_LEXEMA; return UNARIOIZQ;}
"||"        {SET_LEXEMA; return OR;}
"&&"        {SET_LEXEMA; return AND;}
"^"         {SET_LEXEMA; return XOR;}
[=!]=       {SET_LEXEMA; return COMP_IG;}
[<>]=?      {SET_LEXEMA; return COMP_MM;}
[*/%]       {SET_LEXEMA; return PROD_DIV_MOD;}
"**"        {SET_LEXEMA; return EXP;}
"@"         {SET_LEXEMA; return ARROBA;}
"@@"        {SET_LEXEMA; return ARROBARROBA;}
"{"         return LLAIZQ;
"}"         return LLADER;
"["         {return CORIZQ;}
"]"         {return CORDER;}
";"         return PYC;
","         return COMA;
[ \t]+      ;        // Se ignoran los espacios en blanco
{com_linea} ++linea; // Se ignoran los comentarios al final de línea
\n          ++linea;
.           error++; snprintf(buffer_error, LONGITUD_ERROR, "'%s' no se identifica con ningún token conocido\n", yytext); lerror(buffer_error);

%%

 // Procedimientos. No se implementa ni declara la función main si no se define
 // MAIN_LEXICO; así solo se usa en el ejecutable del analizador léxico

#ifdef MAIN_LEXICO
int main(int argc, char* argv[]) {
  yyin = abrir_entrada(argc, argv);
  int val = yylex();
  while (val != 0) {
    printf(" %d <- %s\n", val, yytext);
    val = yylex();
  }

  return error;
}
#endif
