%{
  /***************************************
  ** sintactico.y                       **
  ** Analizador sintáctico del lenguaje **
  ***************************************/

  #include <stdio.h>
  #include "tabla.h"
  #include "string.h"
  void yyerror(const char * msg);
  int yylex();
%}

%error-verbose   // Permite mensajes de error detallados

/* // Structs usados en herencia para la tabla de símbolos */
/* %union{ */
/*   char * lexema; */
/*   int token; */
/*   int tipo; */
/*  } */

// Lista de nombres de los tokens

%token VARBEGIN VAREND
%token INCR DECR
%token ASIGN
%token IF ELSE WHILE REPEAT UNTIL
%token READ WRITE
%token CADENA
%token LITERAL
%token <lexema> LISTOF
%token <lexema> TIPOBASE
%token MAIN
%token PROCED
%token <lexema> ID
%token PARIZQ PARDER
%token SIGNO
%token UNARIODER
%token UNARIOIZQ
%token OR AND XOR
%token COMP_IG COMP_MM
%token PROD_DIV_MOD
%token EXP
%token ARROBA
%token ARROBARROBA
%token LLAIZQ LLADER
%token CORIZQ CORDER
%token PYC COMA

%type <lexema> tipo
%type <lid> lista_identificadores

// Precedencias

%left OR
%left AND
%left XOR
%left COMP_IG
%left COMP_MM
%left SIGNO
%left PROD_DIV_MOD
%left EXP
%right ARROBA
%right ARROBARROBA
%right UNARIOIZQ
%right DECR
%right INCR
%nonassoc UNARIODER


%start programa

%%

// Producciones

bloque : inicio_de_bloque
         declar_de_variables_locales
         declar_de_subprogs
         sentencias
         fin_de_bloque
;

cabecera_subprograma : PROCED ID PARIZQ {insertaProcedimiento($2);} lista_parametros PARDER
   | PROCED ID PARIZQ PARDER {insertaProcedimiento($2);}
;

cuerpo_declar_variables : tipo lista_identificadores {for(int i=0; i<$2.tope_id;++i){insertaVar($2.lista_ids[i],$1);};} PYC
                        | error
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
          | expresion INCR expresion ARROBARROBA expresion
          | INCR expresion
          | DECR expresion
          | UNARIOIZQ expresion
          | expresion UNARIODER
          | SIGNO expresion  %prec UNARIOIZQ
          | expresion SIGNO expresion
          | expresion OR expresion
          | expresion AND expresion
          | expresion XOR expresion
          | expresion COMP_IG expresion
          | expresion COMP_MM expresion
          | expresion PROD_DIV_MOD expresion
          | expresion EXP expresion
          | expresion ARROBA expresion
          | expresion DECR expresion
          | ID
          | LITERAL
          | lista
          | error
;

expresion_o_cadena : expresion | CADENA
;

fin_de_bloque : LLADER {salBloqueTS();}
;

inicio_de_bloque : LLAIZQ {entraBloqueTS();}
;

lista : CORIZQ CORDER | CORIZQ elementos CORDER
;

lista_expresiones_o_cadenas : lista_expresiones_o_cadenas COMA expresion_o_cadena
                            | expresion_o_cadena
;

lista_identificadores : ID {$$.lista_ids[$$.tope_id] = $1;$$.tope_id+=1;} | lista_identificadores COMA ID {$$.lista_ids[$$.tope_id] = $3;$$.tope_id+=1;}
;

lista_parametros : parametro
                 | lista_parametros COMA parametro
;

lista_variables : lista_identificadores
;

llamada_proced : ID PARIZQ elementos PARDER PYC
               | ID PARIZQ PARDER PYC
;

marca_ini_declar_variables : VARBEGIN
;

marca_fin_declar_variables : VAREND
;

parametro : tipo ID {insertaParametro($2, $1);}
          | error
;

programa : PROCED MAIN bloque
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

tipo : TIPOBASE {$$=$1;} | LISTOF TIPOBASE {char str[100]="list of", str1[100];strcat(str," ");strcat(str,$2);$$=str;}
;

variables_locales : variables_locales cuerpo_declar_variables
                  | cuerpo_declar_variables
;


%%

#include "lexico.yy.c"    // Generador por Lex, implementa la función yylex
#include "yyerror.h"      // Función yyerror
