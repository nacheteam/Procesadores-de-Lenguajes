%{
  /***************************************
  ** sintactico.y                       **
  ** Analizador sintáctico del lenguaje **
  ***************************************/

  #include <stdio.h>
  #include "tabla.h"
  #include "comprobaciones.h"
  #include "string.h"
  void yyerror(const char * msg);
  int yylex();

  //TipoDato getTipoLiteral(char * literal);
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
%token <lexema> INCR DECR
%token ASIGN
%token IF ELSE WHILE REPEAT UNTIL
%token READ WRITE
%token CADENA
%token <lexema> LITERAL
%token <lexema> LISTOF
%token <lexema> TIPOBASE
%token MAIN
%token PROCED
%token <lexema> ID
%token PARIZQ PARDER
%token SIGNO
%token <lexema> UNARIODER
%token <lexema> UNARIOIZQ
%token OR AND XOR
%token COMP_IG COMP_MM
%token <lexema> PROD_DIV_MOD
%token <lexema> EXP
%token <lexema> ARROBA
%token ARROBARROBA
%token LLAIZQ LLADER
%token CORIZQ CORDER
%token PYC COMA

%type <lexema> tipo
%type <lid> lista_identificadores
%type <tipo> expresion
%type <tipo> elementos

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

elementos : expresion {$$ = $1;}
          | elementos COMA expresion {$$ = $3;} // TODO: Comprobación
;

expresion : PARIZQ expresion PARDER {$$ = $2;}
          | expresion INCR expresion ARROBARROBA expresion {if(($1==listaentero && $3==entero && $5==entero) || ($1==listareal && $3==real && $5==entero) || ($1==listabool && $3==booleano && $5==entero) || ($1==listachar && $3==caracter && $5==entero))
                                                              $$ = $1;
                                                            else
                                                              printf("Los tipos %s y %s no son compatibles o %s no es entero\n",tipoStr($1),tipoStr($3),tipoStr($5));} // TODO: Comprobación
          | INCR expresion {if($2==entero || $2==real)
                              $$ = $2;
                            else
                              printf("El tipo %s no es ni entero ni real\n",tipoStr($2));} // TODO: Comprobación
          | DECR expresion {if($2==entero || $2==real)
                              $$ = $2;
                            else
                              printf("El tipo %s no es ni entero ni real\n",tipoStr($2));} // TODO: Comprobación
          | UNARIOIZQ expresion {if((strcmp($1,"!")==0 && $2==booleano) || ((strcmp($1,"#")==0 || strcmp($1,"?")==0 || strcmp($1,"$")==0) && ($2==listaentero || $2==listareal || $2==listabool || $2==listachar)))
                                  $$ = $2;
                                else
                                  printf("El tipo %s no se corresponde con el operador %s\n",tipoStr($2),$1);} // TODO: Comprobar según token
          | expresion UNARIODER {if($1,listaentero || $1==listareal || $1==listabool || $1==listachar)
                                  $$ = $1;
                                else
                                  printf("El tipo %s no es una lista para aplicar %s\n",tipoStr($1),$2);} // TODO: Comprobar según token
          | SIGNO expresion  {if($2==entero || $2==real)
                                $$ = $2;
                              else
                                printf("El tipo %s no es compatible con + y -\n",tipoStr($2));} %prec UNARIOIZQ // TODO: Comprobar según token
          | expresion SIGNO expresion {if(($1==$3 && ($1==listaentero || $1==listareal || $1==listabool || $1==listachar)) || (($1==entero || $1==real) && ($3==entero || $3==real)))
                                        $$ = $1;
                                      else
                                        printf("Los tipos %s y %s no son iguales o no son un entero, real o lista.\n",tipoStr($1),tipoStr($3));} // TODO: Comprobar según token
          | expresion OR expresion {if($1==booleano && $3==booleano)
                                      $$=$1;
                                    else
                                      printf("Los tipos %s y %s no son booleanos.\n", tipoStr($1),tipoStr($3));}
          | expresion AND expresion {if($1==booleano && $3==booleano)
                                      $$=$1;
                                    else
                                      printf("Los tipos %s y %s no son booleanos.\n", tipoStr($1),tipoStr($3));}
          | expresion XOR expresion {if($1==booleano && $3==booleano)
                                      $$=$1;
                                    else
                                      printf("Los tipos %s y %s no son booleanos.\n", tipoStr($1),tipoStr($3));}
          | expresion COMP_IG expresion {if($1==$3)
                                          $$=$1;
                                        else
                                          printf("Los tipos %s y %s no coinciden.\n", tipoStr($1),tipoStr($3));}
          | expresion COMP_MM expresion {if($1==$3 && ($1==entero || $1==real))
                                          $$=$1;
                                        else
                                          printf("Los tipos %s y %s no coinciden o no son enteros o reales\n", tipoStr($1),tipoStr($3));}
          | expresion PROD_DIV_MOD expresion {if((strcmp($2,"%")==0 && ($1==entero || $1==real) && $1==entero) || ($1==$2 && ($1==listaentero || $1==listareal || $1==listabool || $1==listachar)) || (($1==entero || $1==real) && ($3==entero || $3==real)))
                                                $$ = $1;
                                              else
                                                printf("Los tipos %s y %s no coinciden o no son aplicables con el operador %s\n",tipoStr($1),tipoStr($3),$2);}
          | expresion EXP expresion {if(($1==entero || $1==real) && $3==entero)
                                      $$=$1;
                                    else
                                      printf("%s no es entero o %s no es entero o real para aplicar %s\n",tipoStr($3),tipoStr($1),$2);}
          | expresion ARROBA expresion {if(($1==listaentero || $1==listareal || $1==listabool || $1==listachar) && $3==entero)
                                          $$=$1;
                                        else
                                          printf("%s no es una lista o %s no es entero para aplicar %s\n",tipoStr($1),tipoStr($3),$2);}
          | expresion DECR expresion {if(($1==listaentero || $1==listareal || $1==listabool || $1==listachar) && $3==entero)
                                        $$=$1;
                                      else
                                        printf("%s no es una lista o %s no es entero para aplicar %s",tipoStr($1),tipoStr($3),$2);}
          | ID {$$ = tipoTS($1);}
          | LITERAL {$$ = getTipoLiteral($1);}
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

sentencia_if : IF PARIZQ expresion PARDER sentencia sentencia_else {compruebaCondicion("if", $3);}
;

sentencia_repeat_until : REPEAT sentencia UNTIL expresion PYC {compruebaCondicion("repeat-until", $4);}
;

sentencia_salida : WRITE lista_expresiones_o_cadenas PYC
;

sentencia_while : WHILE PARIZQ expresion PARDER sentencia {compruebaCondicion("while", $3);}
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
