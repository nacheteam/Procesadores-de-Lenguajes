%{
  /***************************************
  ** sintactico.y                       **
  ** Analizador sintáctico del lenguaje **
  ***************************************/

  #include <stdio.h>
  void yyerror(const char * msg);
  int yylex();
%}

%error-verbose   // Permite mensajes de error detallados


// Lista de nombres de los tokens

%token VARBEGIN
%token VAREND
%token INCR
%token DECR
%token ASIGN
%token IF
%token ELSE
%token WHILE
%token REPEAT
%token UNTIL
%token READ
%token WRITE
%token CADENA
%token LITERAL
%token LISTOF
%token TIPOBASE
%token MAIN
%token ID
%token PARIZQ
%token SIGNO
%token UNARIODER
%token UNARIOIZQ
%token BINARIO
%token ARROBA
%token LLAIZQ
%token LLADER
%token PARDER
%token CORIZQ
%token CORDER
%token PYC
%token COMA

// Atributos

%left "^" "**"
%left "*" "/"
%left "[=!]=?" "[<>]=?"
%left "&&"
%left "||"

%%

// Producciones

programa : MAIN bloque
;

bloque : inicio_de_bloque
         declar_de_variables_locales
         declar_de_subprogs
         sentencias
         fin_de_bloque
;

cabecera_subprograma : ID PARIZQ parametros PARDER
;

cuerpo_declar_variables : tipo lista_identificadores PYC
;

declar_de_subprogs : | declar_de_subprogs declar_subprog
;

declar_de_variables_locales : |  marca_ini_declar_variables
                                 variables_locales
                                 marca_fin_declar_variables
;

declar_subprog : cabecera_subprograma bloque
;

elementos : expresion | elementos COMA expresion
;

expresion : PARIZQ expresion PARDER
          | op_unario_iz expresion
          | expresion op_unario_der
          | expresion op_binario expresion
          | expresion INCR expresion ARROBA expresion
          | ID
          | LITERAL
          | lista
          | SIGNO expresion
;

expresion_o_cadena : elementos | CADENA
;

fin_de_bloque : LLADER
;

inicio_de_bloque : LLAIZQ
;

lista : CORIZQ CORDER | CORIZQ elementos CORDER
;

lista_expresiones_o_cadenas : lista_expresiones_o_cadenas COMA expresion_o_cadena
                            | expresion_o_cadena
;

lista_identificadores : ID | lista_identificadores COMA ID
;

lista_parametros : tipo ID | lista_parametros COMA tipo ID
;

lista_variables : lista_identificadores
;

llamada_proced : ID PARIZQ elementos PARDER PYC
;

marca_ini_declar_variables : VARBEGIN
;

marca_fin_declar_variables : VAREND
;

op_binario : SIGNO | BINARIO | ARROBA | DECR
;

op_unario_der : INCR
              | DECR
              | UNARIODER
;

op_unario_iz : INCR
             | DECR
             | UNARIOIZQ
;

parametros :| lista_parametros
;

sentencia : bloque
          | sentencia_asignacion
          | sentencia_if
          | sentencia_while
          | sentencia_repeat_until
          | sentencia_entrada
          | sentencia_salida
          | llamada_proced
;

sentencia_asignacion :  ID ASIGN expresion PYC
;

sentencia_else :| ELSE sentencia
;

sentencia_entrada : READ lista_variables PYC
;

sentencia_if : IF PARIZQ expresion PARDER sentencia sentencia_else
;

sentencia_repeat_until : REPEAT sentencia UNTIL expresion PYC
;

sentencia_salida : WRITE lista_expresiones_o_cadenas PYC
;

sentencia_while : WHILE PARIZQ expresion PARDER sentencia
;

sentencias : sentencias sentencia
           | sentencia
;

tipo : TIPOBASE | LISTOF TIPOBASE
;

variables_locales : variables_locales cuerpo_declar_variables
                  | cuerpo_declar_variables
;


%%

#include "lexico.yy.c"    // Generador por Lex, implementa la función yylex
#include "yyerror.h"      // Función yyerror
