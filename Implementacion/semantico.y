%{
  /****************************************
  ** semantico.y                         **
  ** Analizador y traductor del lenguaje **
  ****************************************/

  #include <stdio.h>
  #include "tabla.h"
  #include "comprobaciones.h"
  #include "string.h"
  void yyerror(const char * msg);
  int yylex();

  TipoDato getTipoLiteral(char * literal);
  char * etiqueta();
  char * temporal();
%}

%error-verbose   // Permite mensajes de error detallados

/* // Structs usados en herencia para la tabla de símbolos */
 %union{
  char * lexema;
  struct atributos atrib;
  TipoDato tipo;
 }

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
%token <lexema> SIGNO
%token <lexema> UNARIODER
%token <lexema> UNARIOIZQ
%token <lexema> OR AND XOR
%token <lexema> COMP_IG COMP_MM
%token <lexema> PROD_DIV_MOD
%token <lexema> EXP
%token <lexema> ARROBA
%token <lexema> ARROBARROBA
%token LLAIZQ LLADER
%token CORIZQ CORDER
%token PYC COMA

%type <lexema> tipo
%type <atrib> lista_identificadores
%type <atrib> expresion
%type <atrib> elementos
%type <tipo> lista

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

cuerpo_declar_variables : tipo lista_identificadores {for(int i=0; i<$2.lid.tope_id;++i){insertaVar($2.lid.lista_ids[i],$1);};} PYC
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

elementos : expresion { $$.el.tipos[$$.el.tope_elem] = $1.tipo; $$.el.tope_elem++; }
          | elementos COMA expresion { $$.el.tipos[$$.el.tope_elem] = $3.tipo; $$.el.tope_elem++; }
;

expresion : PARIZQ expresion PARDER {$$.tipo = $2.tipo;}
| expresion INCR expresion ARROBARROBA expresion {if(esTipoElemento($3.tipo,$1.tipo) && $5.tipo==entero)
                                                              $$.tipo = $1.tipo;
                                                            else{
                                                              semprintf("Los tipos %s y %s no son compatibles o %s no es entero para aplicar el operador ternario %s y %s\n", tipoStr($1.tipo),tipoStr($3.tipo),tipoStr($5.tipo),$2,$4);
                                                              $$.tipo = desconocido;}}
          | INCR expresion {if($2.tipo==entero || $2.tipo==real)
                              $$.tipo = $2.tipo;
                           else{
                             semprintf("El tipo %s no es ni entero ni real para aplicar el operador unario %s\n", tipoStr($2.tipo),$1);
                             $$.tipo = desconocido;
                            }}
          | DECR expresion {if($2.tipo==entero || $2.tipo==real)
                              $$.tipo = $2.tipo;
                            else{
                              semprintf("El tipo %s no es ni entero ni real para aplicar el operador unario %s\n", tipoStr($2.tipo),$1);
                              $$.tipo = desconocido;}}
          | UNARIOIZQ expresion {if((strcmp($1,"!")==0 && $2.tipo==booleano))
                                  $$.tipo  = $2.tipo;
                                else if(strcmp($1,"#")==0 && esLista($2.tipo))
                                  $$.tipo  = entero;
                                else if(strcmp($1,"?")==0 && esLista($2.tipo))
                                  $$.tipo  = getTipoElemento($2.tipo);
                                else if(strcmp($1,"$")==0)
                                  $$.tipo =$2.tipo;
                                else{
                                  semprintf("El tipo %s no se corresponde con el operador %s\n", tipoStr($2.tipo),$1);
                                  $$.tipo  = desconocido;
                                }}
           | expresion UNARIODER {if(esLista($1.tipo))
                                  $$.tipo = $1.tipo;
                                else{
                                  semprintf("El tipo %s no es una lista para aplicar %s\n", tipoStr($1.tipo),$2);
                                  $$.tipo = desconocido;
                                }}
           | SIGNO expresion  {if(esNumero($2.tipo))
                                $$.tipo = $2.tipo;
                              else
                                { semprintf("El tipo %s no es compatible con el operador unario %s\n", tipoStr($2.tipo),$1);
                                  $$.tipo = desconocido;}} %prec UNARIOIZQ
                                  | expresion SIGNO expresion {if(($1.tipo==$3.tipo && esLista($1.tipo)) || (esNumero($1.tipo) && esNumero($3.tipo)))
                                        $$.tipo = $1.tipo;
                                      else{
                                        semprintf("Los tipos %s y %s no son iguales o no son un entero, real o lista para aplicar %s.\n", tipoStr($1.tipo),tipoStr($3.tipo),$2);
                                        $$.tipo = desconocido;}} // TODO: Comprobar según token
          | expresion OR expresion {if($1.tipo==booleano && $3.tipo==booleano)
                                      $$.tipo=$1.tipo;
                                   else{
                                   semprintf("Los tipos %s y %s no son booleanos para aplicar %s.\n", tipoStr($1.tipo),tipoStr($3.tipo),$2);
                                   $$.tipo = desconocido;
                                   }}
          | expresion AND expresion {if($1.tipo==booleano && $3.tipo==booleano)
                                      $$.tipo=$1.tipo;
                                    else{
                                      semprintf("Los tipos %s y %s no son booleanos para aplicar %s.\n", tipoStr($1.tipo),tipoStr($3.tipo),$2);
                                      $$.tipo = desconocido;
                                    }}
          | expresion XOR expresion {if($1.tipo==booleano && $3.tipo==booleano)
                                      $$.tipo=$1.tipo;
                                    else{
                                      semprintf("Los tipos %s y %s no son booleanos para aplicar %s.\n", tipoStr($1.tipo),tipoStr($3.tipo),$2);
                                      $$.tipo = desconocido;}}
          | expresion COMP_IG expresion {if($1.tipo==$3.tipo)
                                          $$.tipo=booleano;
                                        else{
                                          semprintf("Los tipos %s y %s no coinciden para aplicar %s.\n", tipoStr($1.tipo),tipoStr($3.tipo),$2);
                                          $$.tipo = desconocido;
                                        }}
          | expresion COMP_MM expresion {if($1.tipo==$3.tipo && esNumero($1.tipo))
                                          $$.tipo=booleano;
                                         else{
                                             semprintf("Los tipos %s y %s no coinciden o no son enteros o reales para aplicar %s\n", tipoStr($1.tipo),tipoStr($3.tipo),$2);
                                             $$.tipo = desconocido;
                                         }}
          // TODO: ($1.tipo==entero || $1.tipo==real) && $1.tipo==entero <-- absorción; revisar la lógica
          | expresion PROD_DIV_MOD expresion {
                                        if(strcmp($2,"/")==0) {
                                             if (esNumero($1.tipo) && $1.tipo==$3.tipo){
                                                  $$.tipo = $1.tipo;
                                             }
                                             else if (($1.tipo==listareal) && $3.tipo==real) {
                                                  $$.tipo = $1.tipo;
                                             }
                                             else{
                                                 semprintf("Los tipos %s y %s no coinciden o no son aplicables con el operador %s\n", tipoStr($1.tipo),tipoStr($3.tipo),$2);
                                                 $$.tipo = desconocido;
                                              }
                                        }
                                        if(strcmp($2,"*")==0) {
                                             if (esNumero($1.tipo) && ($1.tipo==$3.tipo)){
                                                  $$.tipo = $1.tipo;
                                             }
                                             else if (esNumero($3.tipo) && esTipoElemento($3.tipo, $1.tipo)) {
                                                  $$.tipo = $1.tipo;
                                             }
                                             else if (esNumero($1.tipo) && esTipoElemento($1.tipo, $3.tipo)) {
                                                  $$.tipo = $1.tipo;
                                             }
                                             else{
                                                 semprintf("Los tipos %s y %s no coinciden o no son aplicables con el operador %s\n", tipoStr($1.tipo),tipoStr($3.tipo),$2);
                                                 $$.tipo = desconocido;
                                              }
                                        }
                                        if(strcmp($2,"%")==0) {
                                             if (($1.tipo==entero) && ($1.tipo==$3.tipo)){
                                                  $$.tipo = $1.tipo;
                                             }
                                             else if (($1.tipo==listaentero) && ($3.tipo==entero)){
                                                  $$.tipo = $1.tipo;
                                             }
                                             else{
                                                 semprintf("Los tipos %s y %s no coinciden o no son aplicables con el operador %s\n", tipoStr($1.tipo),tipoStr($3.tipo),$2);
                                                 $$.tipo = desconocido;
                                              }
                                        }
                                  }
           | expresion EXP expresion { if (esNumero($1.tipo)) {
                                      if ($3.tipo == entero)
                                        $$.tipo=$1.tipo;
                                      else
                                        semprintf("%s debe entero y %s debe ser entero o real para aplicar %s\n", tipoStr($3.tipo),tipoStr($1.tipo),$2);
                                      } else if ($1.tipo==$3.tipo && ($1.tipo==listaentero || $1.tipo==listachar || $1.tipo==listabool || $1.tipo==listareal))
                                        $$.tipo=$1.tipo;
                                      else
                                        semprintf("Los tipos %s y %s no coinciden o no son aplicables con el operador %s\n", tipoStr($1.tipo),tipoStr($3.tipo),$2);
                                    }

           | expresion ARROBA expresion {if(esLista($1.tipo) && $3.tipo==entero)
                                          $$.tipo=$1.tipo;
                                       else {
                                         semprintf("%s no es una lista o %s no es entero para aplicar %s\n", tipoStr($1.tipo),tipoStr($3.tipo),$2);
                                         $$.tipo = desconocido;
                                       }}
          | expresion DECR expresion {if(esLista($1.tipo) && $3.tipo==entero)
                                        $$.tipo=$1.tipo;
                                      else{
                                        semprintf("%s no es una lista o %s no es entero para aplicar %s\n", tipoStr($1.tipo),tipoStr($3.tipo),$2);
                                        $$.tipo = desconocido;}
                                       }
          | ID {$$.tipo = tipoTS($1);}
          | LITERAL {$$.tipo = getTipoLiteral($1);}
          | lista {$$.tipo=$1;}
          | error {$$.tipo = desconocido;}
;

expresion_o_cadena : expresion | CADENA
;

fin_de_bloque : LLADER {salBloqueTS();}
;

inicio_de_bloque : LLAIZQ {entraBloqueTS();}
;

lista : CORIZQ elementos CORDER {for(int i=0;i<$2.el.tope_elem-1;++i)
                                                                    if($2.el.tipos[i]!=$2.el.tipos[i+1]){
                                                                      semprintf("lista con elementos de distinto tipo: %s y %s\n", tipoStr($2.el.tipos[i]),tipoStr($2.el.tipos[i+1]));
                                                                      break;
                                                                    }

                                                                    if ($$!=desconocido)
                                                                      $$ = getTipoLista($2.el.tipos[0]);
                                                                    }
;

lista_expresiones_o_cadenas : lista_expresiones_o_cadenas COMA expresion_o_cadena
                            | expresion_o_cadena
;

lista_identificadores : ID {$$.lid.lista_ids[$$.lid.tope_id] = $1;$$.lid.tope_id+=1;} | lista_identificadores COMA ID {$$.lid.lista_ids[$$.lid.tope_id] = $3;$$.lid.tope_id+=1;}
;

lista_parametros : parametro
                 | lista_parametros COMA parametro
;

lista_variables : lista_identificadores
;

llamada_proced : ID PARIZQ elementos PARDER PYC { compruebaLlamada(&$3.el, $1); }
               | ID PARIZQ PARDER PYC { compruebaLlamada(NULL, $1); }
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

sentencia_asignacion :  ID ASIGN expresion PYC {
  if(tipoTS($1) != desconocido && tipoTS($1) != $3.tipo){
    semprintf("Asignación de '%s' a variable '%s' de tipo '%s'\n",
           tipoStr($3.tipo), $1, tipoStr(tipoTS($1)));
   }
 }
;

sentencia_else :| ELSE sentencia
;

sentencia_entrada : READ lista_variables PYC
;

sentencia_if : IF PARIZQ expresion PARDER {compruebaCondicion("if", $3.tipo);} sentencia sentencia_else
;

sentencia_repeat_until : REPEAT sentencia UNTIL expresion PYC {compruebaCondicion("repeat-until", $4.tipo);}
;

sentencia_salida : WRITE lista_expresiones_o_cadenas PYC
;

sentencia_while : WHILE PARIZQ expresion PARDER {compruebaCondicion("while", $3.tipo);} sentencia
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

#include "lexico.yy.c"  // Generador por Lex, implementa la función yylex
#include "error.h"      // Función yyerror
