%{
  /***************************************
  ** sintactico.y                       **
  ** Analizador sintáctico del lenguaje **
  ***************************************/

  #include <stdio.h>
  void yyerror(char * msg);
  int yylex();
%}

%error-verbose   // Permite mensajes de error detallados


// Lista de nombres de los tokens

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

%%

// Producciones

programa : MAIN LLAIZQ LLADER // TODO: esta línea sobra; es para comprobar que compila y funciona
/* TODO: pasar al formato de YACC

<alfanum> : | <caracter> <alfanum> | <digito> <alfanum>

<bloque> : <Inicio_de_bloque>
 <Declar_de_variables_locales>
 <Declar_de_subprogs>
 SENTENCIAS
 <Fin_de_bloque>

<booleano> : True | False

<Cabecera_subprograma> : <identificador>PARIZQ<parametros>PARDER

<cadena> : " <lista_imprimibles> "

<caracter> : a | ... | z | A | ... | Z

<Cuerpo_declar_variables> : <tipo> <lista_identificadores> PYC

<Declar_de_subprogs> : <Declar_de_subprogs> <Declar_subprog>

<Declar_de_variables_locales> : <Marca_ini_declar_variables>
<Variables_locales>
<Marca_fin_declar_variables>

<Declar_subprog> : <Cabecera_subprograma> <bloque>

<decimales> := . <natural> | $\varepsilon$

<digito> : 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0

<digitohex> : <digito> | a | b | c | d | e | f

<elementos> : <expresion> | <elementos>, <expresion>

<entero> : <natural> | 0x<hex>

<exponente> : E+ <natural> | E <natural> | E- <natural> | $\varepsilon$

<expresion> : PARIZQ <expresion> PARDER
| OP_UNARIO_IZ <expresion>
| <expresion> <op_unario_der>
| <expresion> <op_binario> <expresion>
| <expresion>INCR<expresion>@<expresion>
| <identificador>
| <literal>
| <lista>
| SIGNO <expresion>

<expresion_o_cadena> : <elementos> | <cadena>

<Fin_de_bloque> : \}

<hex> : <hex> <digitohex> | <digitohex>

<identificador> : <caracter> <alfanum>

<imprimible> : PARIZQcualquier carácter ASCIIPARDER

<Inicio_de_bloque> : \{

<lista> : [] | [<elementos>]

<lista_expresiones_o_cadenas> : <lista_expresiones_o_cadenas>, <expresion_o_cadena>
| <expresion_o_cadena>

<lista_identificadores> : <identificador> | <lista_identificadores>, <identificador>

<lista_imprimibles> :| <lista_imprimibles> <imprimible>

<lista_parametros> : <tipo> <identificador> | <lista_parametros>, <tipo> <identificador>

<lista_variables> : <lista_identificadores>

<literal> : <entero>
| <real>
| '<imprimible>'
| <booleano>

<llamada_proced> : <identificador>PARIZQ<elementos>PARDER

<Marca_ini_declar_variables> : begin

<Marca_fin_declar_variables> : end

<natural> : <natural> <digito> | <digito>

<op_binario> : + | / | - | * | < | <= | > | >= | BINARIO | BINARIO | && | || | ^ | @ | DECR | % | **

OP_UNARIO_DER : INCR
   | DECR
   | UNARIODER

OP_UNARIO_IZ : INCR
   | DECR
   | UNARIOIZQ

<parametros> :| <lista_parametros>

<Programa> : MAIN <bloque>

<real> : <natural> <decimales> <exponente>

SENTENCIA : <bloque>
| <sentencia_asignacion>
| <sentencia_if>
| <sentencia_while>
| <sentencia_REPEAT_UNTIL>
| <sentencia_entrada>
| <sentencia_salida>
| <llamada_proced>

<sentencia_asignacion> :  <identificador> = <expresion> PYC

<sentencia_else> :| else SENTENCIA

<sentencia_entrada> : READ <lista_variables> PYC

<sentencia_if> : if PARIZQ<expresion>PARDER SENTENCIA <sentencia_else>

<sentencia_REPEAT_UNTIL> : REPEAT SENTENCIA UNTIL <expresion> PYC

<sentencia_salida> : WRITE <lista_expresiones_o_cadenas> PYC

<sentencia_while> : while PARIZQ<expresion>PARDER SENTENCIA

SENTENCIAS : SENTENCIAS SENTENCIA
| SENTENCIA

<tipo> : TIPOBASE | LISTOF TIPOBASE

<Variables_locales> : <Variables_locales> <Cuerpo_declar_variables>
| <Cuerpo_declar_variables>

TODO */

%%

#include "lexico.yy.c"    // Generador por Lex, implementa la función yylex
#include "yyerror.h"      // Función yyerror
