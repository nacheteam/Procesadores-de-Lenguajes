%{
  /****************************************
  ** semantico.y                         **
  ** Analizador y traductor del lenguaje **
  ****************************************/

  #include <stdio.h>
  #include "tabla.h"
  #include "comprobaciones.h"
  #include "string.h"
  #include "file_io.h"
  void yyerror(const char * msg);
  int yylex();
  FILE * yyout;

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
%token <lexema> CADENA
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
%type <atrib> lista

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
         declar_de_subprogs {if(esMain()) genprintf("#include \"%s\"\n\nint main(){\n", "dec_fun");}
         sentencias
         fin_de_bloque
;

cabecera_subprograma : PROCED ID PARIZQ {
  insertaProcedimiento($2);
  entraProced();
  genprintf("void %s(", $2);
 } lista_parametros PARDER { genprintf(")\n"); }
   | PROCED ID PARIZQ PARDER {
     insertaProcedimiento($2);
     entraProced();
     genprintf("void %s()\n", $2);
 }
;

cuerpo_declar_variables : tipo lista_identificadores {
  for(int i=0; i<$2.lid.tope_id;++i) {
    insertaVar($2.lid.lista_ids[i],$1);
    genprintf("%s %s;\n", tipoCStr(leeTipoDato($1)), $2.lid.lista_ids[i]);
  }
 } PYC
                        | error
;

declar_de_subprogs : | declar_de_subprogs declar_subprog
;

declar_de_variables_locales : |  marca_ini_declar_variables
                                 variables_locales
                                 marca_fin_declar_variables
;

declar_subprog : cabecera_subprograma { genprintf("{\n"); } bloque { genprintf("}\n"); salProced(); }
;

elementos : expresion { $$.el.tipos[$$.el.tope_elem++] = $1.tipo;
                        $$.lid.lista_ids[$$.lid.tope_id++] = $1.lexema;
                      }
          | elementos COMA expresion {
                        $$.el.tipos[$$.el.tope_elem++] = $3.tipo;
                        $$.lid.lista_ids[$$.lid.tope_id++] = $3.lexema;
                      }
;

expresion : PARIZQ expresion PARDER {$$.tipo = $2.tipo;
                                    $$.lexema = temporal(); // TODO: ¿hace falta una nueva variable para esto?
                                    genprintf("  %s %s ;\n", tipoCStr($$.tipo), $$.lexema);
                                    genprintf("  %s = %s ;\n", $$.lexema, $2.lexema);
                                  }
| expresion INCR expresion ARROBARROBA expresion {if(esTipoElemento($3.tipo,$1.tipo) && $5.tipo==entero){
                                                    $$.tipo = $1.tipo;
                                                    $$.lexema = temporal();
                                                    genprintf("  %s %s;",tipoCStr($$.tipo),$$.lexema);
                                                    if($$.tipo==listaentero || $$.tipo == listabool){
                                                      genprintf("  %s = anadeElementoInt(&%s,%s,%s);",$$.lexema,$1.lexema,$5.lexema,$3.lexema);
                                                    }
                                                    else if($$.tipo==listareal){
                                                      genprintf("  %s = anadeElementoDouble(&%s,%s,%s);",$$.lexema,$1.lexema,$5.lexema,$3.lexema);
                                                    }
                                                    else if($$.tipo==listachar){
                                                      genprintf("  %s = anadeElementoChar(&%s,%s,%s);",$$.lexema,$1.lexema,$5.lexema,$3.lexema);
                                                    }
                                                  }
                                                  else{
                                                    semprintf("Los tipos %s y %s no son compatibles o %s no es entero para aplicar el operador ternario %s y %s\n", tipoStr($1.tipo),tipoStr($3.tipo),tipoStr($5.tipo),$2,$4);
                                                    $$.tipo = desconocido;}}
          | INCR expresion {if(esNumero($2.tipo)){
                              // TODO: ¿esto debería ser sentencia?
                              $$.tipo = $2.tipo;
                              $$.lexema = temporal();
                              genprintf("  %s %s ;\n", tipoCStr($$.tipo), $$.lexema);
                              genprintf("  %s = ++%s ;\n", $$.lexema, $2.lexema);
                           }
                           else{
                             semprintf("El tipo %s no es ni entero ni real para aplicar el operador unario %s\n", tipoStr($2.tipo),$1);
                             $$.tipo = desconocido;
                            }}
           | DECR expresion {if(esNumero($2.tipo)){
                              // TODO: ¿esto debería ser sentencia?
                              $$.tipo = $2.tipo;
                              $$.lexema = temporal();
                              genprintf("  %s %s ;\n", tipoCStr($$.tipo), $$.lexema);
                              genprintf("  %s = --%s ;\n", $$.lexema, $2.lexema);
                            }
                            else{
                              semprintf("El tipo %s no es ni entero ni real para aplicar el operador unario %s\n", tipoStr($2.tipo),$1);
                              $$.tipo = desconocido;}}
          | UNARIOIZQ expresion {if((strcmp($1,"!")==0 && $2.tipo==booleano))
                                  $$.tipo  = $2.tipo;
                                else if(strcmp($1,"#")==0 && esLista($2.tipo)){
                                  $$.tipo  = entero;
                                }
                                else if(strcmp($1,"?")==0 && esLista($2.tipo)){
                                  $$.tipo  = getTipoElemento($2.tipo);
                                }
                                else if(strcmp($1,"$")==0){
                                  $$.tipo =$2.tipo;
                                }
                                else{
                                  semprintf("El tipo %s no se corresponde con el operador %s\n", tipoStr($2.tipo),$1);
                                  $$.tipo  = desconocido;
                                }
                              if($$.tipo!=desconocido){
                                // TODO: ¿$lista no debería ser una sentencia?
                                $$.lexema = temporal();
                                genprintf("  %s %s ;\n", tipoCStr($$.tipo), $$.lexema);
                                 if(strcmp($1,"#")==0){
                                   genprintf("  %s = numeroElementos(&%s);\n",$$.lexema,$2.lexema);
                                 }
                                 else if(strcmp($1,"?")==0){
                                   if($$.tipo==entero || $$.tipo==booleano){
                                     genprintf("  %s = devuelveActualInt(&%s);\n",$$.lexema,$2.lexema);
                                   }
                                   else if($$.tipo==real){
                                     genprintf("  %s = devuelveActualDouble(&%s);\n",$$.lexema,$2.lexema);
                                   }
                                   else if($$.tipo==caracter){
                                     genprintf("  %s = devuelveActualChar(&%s);\n",$$.lexema,$2.lexema);
                                   }
                                 }
                                 else if(strcmp($1,"$")==0){
                                   genprintf("  reiniciaCursor(&%s);\n",$2.lexema);
                                 }
                                 else{
                                   genprintf("  %s = %s %s ;\n", $$.lexema, $1, $2.lexema);
                                 }
                              }}
           | expresion UNARIODER {if(esLista($1.tipo)){
                                    $$.tipo = $1.tipo;
                                    genprintf("  %s %s ;\n", tipoCStr($$.tipo), $$.lexema);
                                    if(strcmp($2,"<<")==0){
                                      genprintf("  retrocedeCursor(&%s);",$1.lexema);
                                    }
                                    else if(strcmp($2,">>")==0){
                                      genprintf("  avanzaCursor(&%s);",$1.lexema);
                                    }
                                    // TODO: ¿estas operaciones no debían ser una sentencia?
                                }
                                else{
                                  semprintf("El tipo %s no es una lista para aplicar %s\n", tipoStr($1.tipo),$2);
                                  $$.tipo = desconocido;
                                }}
           | SIGNO expresion  {if(esNumero($2.tipo)){
                                $$.tipo = $2.tipo;
                                $$.lexema = temporal();
                                genprintf("  %s %s ;\n", tipoCStr($$.tipo), $$.lexema);
                                genprintf("  %s = %s %s ;\n", $$.lexema, $1, $2.lexema);
                              }
                              else
                                { semprintf("El tipo %s no es compatible con el operador unario %s\n", tipoStr($2.tipo),$1);
                                  $$.tipo = desconocido;}} %prec UNARIOIZQ
          | expresion SIGNO expresion {if(esTipoElemento($3.tipo, $1.tipo) || (esNumero($1.tipo) && $1.tipo == $3.tipo)){
                                        $$.tipo = $1.tipo;
                                        // TODO: lo siguiente funciona con números. Escribir el operador de lista cuando sea pertinente
                                        $$.lexema = temporal();
                                        genprintf("  %s %s ;\n", tipoCStr($$.tipo), $$.lexema);
                                        char tipo[20];
                                        char operacion[20];
                                        char* lista;
                                        char* valor;

                                        if(esLista($1.tipo) || esLista($3.tipo)){
                                          switch ($1.tipo) {
                                            case listaentero:
                                              strcpy(tipo,"Int");
                                              lista = $1.lexema;
                                              valor = $3.lexema;
                                              break;
                                            case listareal:
                                              strcpy(tipo,"Double");
                                              lista = $1.lexema;
                                              valor = $3.lexema;
                                              break;
                                            case entero:
                                              strcpy(tipo,"Int");
                                              lista = $3.lexema;
                                              valor = $1.lexema;
                                              break;
                                            case real:
                                              strcpy(tipo,"Double");
                                              lista = $3.lexema;
                                              valor = $1.lexema;
                                              break;
                                          }
                                          if(strcmp($2,"-")==0)
                                            strcpy(operacion,"resta");
                                          else
                                            strcpy(operacion,"suma");

                                          $$.lexema = temporal();
                                          genprintf("  %s %s ;\n", tipoCStr($$.tipo), $$.lexema);
                                          genprintf("  %s = %sValor%s(&%s,%s);", $$.lexema, operacion, tipo, lista, valor);
                                        }
                                        else
                                          genprintf("  %s = %s %s %s ;\n", $$.lexema, $1.lexema, $2, $3.lexema);
                                      }
                                      else{
                                        semprintf("Los tipos %s y %s no son iguales o no son un entero, real o lista para aplicar %s.\n", tipoStr($1.tipo),tipoStr($3.tipo),$2);
                                        $$.tipo = desconocido;}} // TODO: Comprobar según token
          | expresion OR expresion {if($1.tipo==booleano && $3.tipo==booleano){
                                      $$.tipo=$1.tipo;
                                      $$.lexema = temporal();
                                      genprintf("  %s %s ;\n", tipoCStr($$.tipo), $$.lexema);
                                      genprintf("  %s = %s %s %s ;\n", $$.lexema, $1.lexema, $2, $3.lexema);
                                    }
                                   else{
                                   semprintf("Los tipos %s y %s no son booleanos para aplicar %s.\n", tipoStr($1.tipo),tipoStr($3.tipo),$2);
                                   $$.tipo = desconocido;
                                   }}
          | expresion AND expresion {if($1.tipo==booleano && $3.tipo==booleano){
                                      $$.tipo=$1.tipo;
                                      $$.lexema = temporal();
                                      genprintf("  %s %s ;\n", tipoCStr($$.tipo), $$.lexema);
                                      genprintf("  %s = %s %s %s ;\n", $$.lexema, $1.lexema, $2, $3.lexema);
                                    }
                                    else{
                                      semprintf("Los tipos %s y %s no son booleanos para aplicar %s.\n", tipoStr($1.tipo),tipoStr($3.tipo),$2);
                                      $$.tipo = desconocido;
                                    }}
          | expresion XOR expresion {if($1.tipo==booleano && $3.tipo==booleano){
                                      $$.tipo=$1.tipo;
                                      $$.lexema = temporal();
                                      genprintf("  %s %s ;\n", tipoCStr($$.tipo), $$.lexema);
                                      genprintf("  %s = %s %s %s ;\n", $$.lexema, $1.lexema, $2, $3.lexema);
                                    }
                                    else{
                                      semprintf("Los tipos %s y %s no son booleanos para aplicar %s.\n", tipoStr($1.tipo),tipoStr($3.tipo),$2);
                                      $$.tipo = desconocido;}}
          | expresion COMP_IG expresion {if($1.tipo==$3.tipo){
                                          $$.tipo=booleano;
                                          $$.lexema = temporal();
                                          genprintf("  %s %s ;\n", tipoCStr($$.tipo), $$.lexema);
                                          genprintf("  %s = %s %s %s ;\n", $$.lexema, $1.lexema, $2, $3.lexema);
                                        }
                                        else{
                                          semprintf("Los tipos %s y %s no coinciden para aplicar %s.\n", tipoStr($1.tipo),tipoStr($3.tipo),$2);
                                          $$.tipo = desconocido;
                                        }}
          | expresion COMP_MM expresion {if($1.tipo==$3.tipo && esNumero($1.tipo)){
                                          $$.tipo=booleano;
                                          $$.lexema = temporal();
                                          genprintf("  %s %s ;\n", tipoCStr($$.tipo), $$.lexema);
                                          genprintf("  %s = %s %s %s ;\n", $$.lexema, $1.lexema, $2, $3.lexema);
                                        }
                                         else{
                                             semprintf("Los tipos %s y %s no coinciden o no son enteros o reales para aplicar %s\n", tipoStr($1.tipo),tipoStr($3.tipo),$2);
                                             $$.tipo = desconocido;
                                         }}
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
                                              char tipo[20];
                                              char* lista;
                                              char* valor;

                                              if(esLista($1.tipo)){
                                                strcpy(tipo,"Double");
                                                lista = $1.lexema;
                                                valor = $3.lexema;

                                                $$.lexema = temporal();
                                                genprintf("  %s %s ;\n", tipoCStr($$.tipo), $$.lexema);
                                                genprintf("  %s = divideValor%s(&%s,%s);\n", $$.lexema, tipo, lista, valor);
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
                                                  $$.tipo = $3.tipo;
                                             }
                                             else{
                                                 semprintf("Los tipos %s y %s no coinciden o no son aplicables con el operador %s\n", tipoStr($1.tipo),tipoStr($3.tipo),$2);
                                                 $$.tipo = desconocido;
                                              }

                                              char tipo[20];
                                              char* lista;
                                              char* valor;
                                              if(esLista($1.tipo) || esLista($3.tipo)){
                                                switch ($1.tipo) {
                                                  case listaentero:
                                                    strcpy(tipo,"Int");
                                                    lista = $1.lexema;
                                                    valor = $3.lexema;
                                                    break;
                                                  case listareal:
                                                    strcpy(tipo,"Double");
                                                    lista = $1.lexema;
                                                    valor = $3.lexema;
                                                    break;
                                                  case entero:
                                                    strcpy(tipo,"Int");
                                                    lista = $3.lexema;
                                                    valor = $1.lexema;
                                                    break;
                                                  case real:
                                                    strcpy(tipo,"Double");
                                                    lista = $3.lexema;
                                                    valor = $1.lexema;
                                                    break;
                                                }

                                                $$.lexema = temporal();
                                                genprintf("  %s %s ;\n", tipoCStr($$.tipo), $$.lexema);
                                                genprintf("  %s = productoValor%s(&%s,%s);\n", $$.lexema, tipo, lista, valor);
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
                                              // TODO: operador de lista
                                        }
                                        if(!esLista($$.tipo)){
                                          // TODO: comprobar que las operaciones división y módulo de C son las mismas que las que se especifican en nuestro lenguaje
                                          // TODO: lo siguiente es aplicable si el operador es de números, pero no si es de listas, en cuyo caso requiere implementación de listas
                                          $$.lexema = temporal();
                                          genprintf("  %s %s ;\n", tipoCStr($$.tipo), $$.lexema);
                                          genprintf("  %s = %s %s %s ;\n", $$.lexema, $1.lexema, $2, $3.lexema);
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

                                      if(esNumero($$.tipo)) {
                                        // Implementación de la exponenciación mediante un procedimiento binario
                                        // TODO: ¿mover a otro lugar del código?
                                        $$.lexema = temporal();
                                        genprintf("  %s %s ;\n", tipoCStr($$.tipo), $$.lexema);
                                        genprintf("  %s = 1 ;\n", $$.lexema);
                                        char * base = temporal();
                                        genprintf("  %s %s ;\n", tipoCStr($$.tipo), base);
                                        genprintf("  %s = %s ;\n", base, $1.lexema);
                                        char * exponente = temporal();
                                        genprintf("  int %s ;\n", exponente);
                                        genprintf("  %s = %s ;\n", exponente, $3.lexema);
                                        char * etiqueta_exp = etiqueta();
                                        char * etiqueta_fin = etiqueta();
                                        char * etiqueta_par = etiqueta();
                                        char * impar = temporal();
                                        genprintf("  int %s ;\n", impar);
                                        genprintf("  if (%s >= 0) goto %s ;\n", exponente, etiqueta_exp);
                                        genprintf("  %s = 1.0 / %s ;\n  %s = -%s ;\n", base, base, exponente, exponente);
                                        genprintf("%s:\n", etiqueta_exp);
                                        genprintf("  if (%s == 0) goto %s ;\n", exponente, etiqueta_fin);
                                        genprintf("  %s = (1 & %s) ;\n", impar, exponente);
                                        genprintf("  %s = %s / 2 ;\n", exponente, exponente);
                                        genprintf("  if (!%s) goto %s ;\n", impar, etiqueta_par);
                                        genprintf("  %s = %s * %s ;\n", $$.lexema, $$.lexema, base);
                                        genprintf("%s:\n", etiqueta_par);
                                        genprintf("  %s = %s * %s ;\n", base, base, base);
                                        genprintf("  goto %s ;\n", etiqueta_exp);
                                        genprintf("%s:;\n", etiqueta_fin);
                                      } else if ($$.tipo!=desconocido) {
                                        $$.lexema = temporal();
                                        genprintf("  INIT_lista%s(%s, 0);\n", tipoStr(getTipoElemento($$.tipo)), $$.lexema);
                                        genprintf("  %s = concatenaListas(&%s, &%s);\n", $$.lexema, $1.lexema, $3.lexema);
                                      }
                                    }

           | expresion ARROBA expresion {if(esLista($1.tipo) && $3.tipo==entero){
                                          $$.lexema = temporal();
                                          $$.tipo= getTipoElemento($$.tipo);
                                          char * tipo_elemento = tipoCStr($1.tipo);
                                          char * sentencia_get[3] = {"devuelvePosicionInt", "devuelvePosicionDouble", "devuelvePosicionChar"};
                                          int s = ($1.tipo == listaentero || $1.tipo == listabool ? 0 : ($1.tipo == listareal ? 1 : 2));
                                          genprintf("  %s %s;\n", tipo_elemento, $$.lexema);
                                          genprintf("  %s = %s(&%s, %s);\n", $$.lexema, sentencia_get[s], $1.lexema, $3.lexema);
                                        }
                                       else {
                                         semprintf("%s no es una lista o %s no es entero para aplicar %s\n", tipoStr($1.tipo),tipoStr($3.tipo),$2);
                                         $$.tipo = desconocido;
                                       }}
          | expresion DECR expresion {if(esLista($1.tipo) && $3.tipo==entero){
                                        $$.tipo=$1.tipo;
                                        // TODO: operador de lista pendiente de implementar
                                      }
                                      else{
                                        semprintf("%s no es una lista o %s no es entero para aplicar %s\n", tipoStr($1.tipo),tipoStr($3.tipo),$2);
                                        $$.tipo = desconocido;}
                                       }
          | ID {$$.tipo = tipoTS($1);
                $$.lexema = temporal();
                genprintf("  %s %s ;\n", tipoCStr($$.tipo),$$.lexema);
                genprintf("  %s = %s ;\n", $$.lexema, $1);}
          | LITERAL {$$.tipo = getTipoLiteral($1);
                    $$.lexema = temporal();
                    genprintf("  %s %s ;\n",  tipoCStr($$.tipo), $$.lexema);
                    char * literal_c = $1;
                    char literales_booleanos[4] = {'0', 0, '1', 0};
                    if ($$.tipo == booleano)
                      literal_c = literales_booleanos + 2*(!strcmp("True", $1)); // "1" si True, "0" si False
                    // TODO: lo siguiente puede no dar resultado si el literal usado no existe o no significa lo mismo en C (ejemplos que se me ocurren: True, False)
                    genprintf("  %s = %s ;\n",$$.lexema, literal_c);}
          | lista {$$.tipo=$1.tipo;
                   $$.lexema = temporal();
                   genprintf("  INIT_lista%s(%s, %d);\n", tipoStr(getTipoElemento($$.tipo)), $$.lexema, $1.lid.tope_id);
                   char * sentencia_insercion[3] = {"insertaInt", "insertaDouble", "insertaChar"};
                   int s = ($$.tipo == listaentero || $$.tipo == listabool ? 0 : ($$.tipo == listareal ? 1 : 2));
                   for(int i=0; i < $1.lid.tope_id; ++i) {
                     char * id = $1.lid.lista_ids[i];
                     genprintf("  %s(&%s, %s);\n", sentencia_insercion[s], $$.lexema, id);
                   }
                   }
          | error {$$.tipo = desconocido;}
;

expresion_o_cadena : expresion {
                     char char_tipo;
                     int es_lista = 0;
                     char * extra_bool = ""; // Cadena adicional para gestionar la salida de un booleano
                     switch($1.tipo) {
                       case entero:
                         char_tipo = 'd';
                         break;
                       case real:
                         char_tipo = 'f';
                         break;
                       case booleano: // Se imprimirá la cadena True o False
                         char_tipo = 's';
                         extra_bool = " ? \"True\" : \"False\"";
                         break;
                       case caracter:
                         char_tipo = 'c';
                         break;
                       case listaentero:
                         es_lista = 1;
                         genprintf("  imprimeListaInt(&%s);",$1.lexema);
                         break;
                       case listareal:
                         es_lista = 1;
                         genprintf("  imprimeListaDouble(&%s);",$1.lexema);
                         break;
                       case listachar:
                         es_lista = 1;
                         genprintf("  imprimeListaChar(&%s);",$1.lexema);
                         break;
                       case listabool:
                         es_lista = 1;
                         genprintf("  imprimeListaBool(&%s);",$1.lexema);
                         break;
                       default:
                         char_tipo = 'd'; // TODO: lista o tipo desconocido; imprimir correctamente o provocar mensaje de error de algún tipo
                     }
                     if(!es_lista)
                       genprintf("  printf(\"%%%c\", %s%s);\n", char_tipo, $1.lexema, extra_bool);
                   }
                   | CADENA {
                     genprintf("  printf(\"%%s\", %s);\n", $1);
                   }
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

                                                                    if ($$.tipo!=desconocido){
                                                                      $$.tipo = getTipoLista($2.el.tipos[0]);
                                                                      $$.lid = $2.lid;
                                                                    }}
;

lista_expresiones_o_cadenas : lista_expresiones_o_cadenas COMA expresion_o_cadena
                            | expresion_o_cadena
;

lista_identificadores : ID {$$.lid.lista_ids[$$.lid.tope_id] = $1;$$.lid.tope_id+=1;} | lista_identificadores COMA ID {$$.lid.lista_ids[$$.lid.tope_id] = $3;$$.lid.tope_id+=1;}
;

lista_parametros : parametro
                 | lista_parametros COMA { genprintf(", "); } parametro
;

llamada_proced : ID PARIZQ elementos PARDER PYC {
  compruebaLlamada(&$3.el, $1);
  genprintf("  %s(", $1);
  for(int i=0; i < $3.lid.tope_id; ++i) {
    char * id = $3.lid.lista_ids[i];
    genprintf("%s%s", (i == 0 ? "" : ","), id);
  }
  genprintf(");\n");
 }
               | ID PARIZQ PARDER PYC {
  compruebaLlamada(NULL, $1);
  genprintf("  %s();\n", $1);
 }
;

marca_ini_declar_variables : VARBEGIN
;

marca_fin_declar_variables : VAREND
;

parametro : tipo ID {
  insertaParametro($2, $1);
  genprintf("%s %s", tipoCStr(leeTipoDato($1)), $2);
 }
          | error
;

programa : {genprintf("#include <stdio.h>\n#include \"Implementacion/lista.h\"\n\n");} PROCED MAIN bloque {genprintf("}\n");}
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

sentencia_asignacion : ID ASIGN { genprintf("{\n"); } expresion PYC {
  if(tipoTS($1) != desconocido && tipoTS($1) != $4.tipo){
    semprintf("Asignación de '%s' a variable '%s' de tipo '%s'\n",
           tipoStr($4.tipo), $1, tipoStr(tipoTS($1)));
   }
   genprintf("  %s = %s;\n}\n", $1, $4.lexema);
 }
;

sentencia_else :| ELSE sentencia
;

sentencia_entrada : READ lista_identificadores PYC {
  for(int i=0; i < $2.lid.tope_id; ++i) {
    char * id = $2.lid.lista_ids[i];
    TipoDato tipo = tipoTS(id);
    char * str_tipo;
    switch(tipo) {
      case booleano: // Los booleanos se leerán como 0 o 1 // TODO: ¿hacer que se lea como True o False?
        // TODO: un valor booleano distinto puede provocar errores tras hacer operaciones lógicas con él, ¿gestionar?
      case entero:
        str_tipo = "i"; // Podrá leer enteros con signo en formato decimal (por defecto) o hexadecimal (si empieza por 0x)
        break;
      case real:
        str_tipo = "lf";
        break;
      case caracter:
        str_tipo = "c";
        break;
      default:
        str_tipo = "i"; // TODO: lista o tipo desconocido; imprimir correctamente o provocar mensaje de error de algún tipo
    }
    genprintf("  scanf(\"%%%s\", &%s);\n", str_tipo, id);
  }
 }
;

sentencia_if : IF {
  char * e_salida = etiqueta();
  char * e_else   = etiqueta();
  insertaIf(e_salida, e_else);
 } PARIZQ expresion PARDER {
  compruebaCondicion("if", $4.tipo);
  genprintf("{\n  if (!%s) goto %s;\n", $4.lexema, findGotoElse());
 } sentencia {
  genprintf("  goto %s;\n", findGotoSalida());
  genprintf("%s:;\n", findGotoElse());
 } sentencia_else {
   genprintf("%s:;\n}\n", findGotoSalida());
   salEstructuraControl();
 }
;

sentencia_repeat_until : REPEAT {
  char * e_entrada = etiqueta();
  insertaRepeatUntil(e_entrada);
  genprintf("{\n%s:;\n", e_entrada);
 } sentencia UNTIL expresion PYC {
   compruebaCondicion("repeat-until", $5.tipo);
   genprintf("  if (!%s) goto %s;\n}\n", $5.lexema, findGotoEntrada());
   salEstructuraControl();
 }
;

sentencia_salida : WRITE { genprintf("{\n"); } lista_expresiones_o_cadenas PYC {
  genprintf("  printf(\"\\n\");\n}\n"); // Imprime un salto de línea al final de la lista // TODO: ¿incluir este salto de línea? ¿Hacer fflush de stdout? ¿Separar cada par de elementos con un espacio?
 }
;

sentencia_while : WHILE {
  char * e_entrada = etiqueta();
  char * e_salida  = etiqueta();
  insertaWhile(e_entrada, e_salida);
  genprintf("{\n%s:;\n", e_entrada);
 } PARIZQ expresion PARDER {
   compruebaCondicion("while", $4.tipo);
   genprintf("  if (!%s) goto %s;\n", $4.lexema, findGotoSalida());
 } sentencia {
   genprintf("  goto %s;\n", findGotoEntrada());
   genprintf("%s:;\n}\n", findGotoSalida());
   salEstructuraControl();
 }
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
