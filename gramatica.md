<entero> ::= <entero> <digito> | <entero>
<digito> ::= 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0
<real> ::= <entero>.<entero>

¿Aquí tenemos que meter todos los caracteres o solo las letras?
<caracter> ::= a | ... | z | A | ... | Z
<booleano> ::= True | False

<op_unario> ::= ++ | -- | !
<op_binario> ::= + | / | - | * | < | <= | > | >= | == | !=

<Programa> ::= <Cabecera_programa> <bloque>
<bloque> ::= <Inicio_de_bloque>
             <Declar_de_variables_locales>
             <Declar_de_subprogs>
             <Sentencias>
             <Fin_de_bloque>
<Declar_de_subprogs> ::= <Declar_de_subprogs> <Declar_subprog>
                         |
<Declar_subprog> ::= <Cabecera_subprograma> <bloque>
<Declar_de_variables_locales> ::= <Marca_ini_declar_variables>
                                  <Variables_locales>
                                  <Marca_fin_declar_variables>
                                  |
<Cabecera_programa> ::= (Dependerá del lenguaje de referencia)
<Inicio_de_bloque> ::= {
<Fin_de_bloque> ::= }
<Variables_locales> ::= <Variables_locales> <Cuerpo_declar_variables>
                        | <Cuerpo_declar_variables>
<Cuerpo_declar_variables> ::= (Dependerá del lenguaje de referencia)
<Cabecera_subprog> ::= (Dependerá del lenguaje de referencia)
<Sentencias> ::= <Sentencias> <Sentencia>
                 | <Sentencia>
<Sentencia> ::= <bloque>
                | <sentencia_asignacion>
                | <sentencia_if>
                | <sentencia_while>
                | <sentencia_entrada>
                | <sentencia_salida>
                | <sentencia_return> (si el lenguaje soporta funciones)
                | <llamada_proced> (si el lenguaje soporta proced.)
                | (Resto de sentencias del lenguaje asignado)
<sentencia_asignacion> ::= (Dependerá del lenguaje de referencia)
                           | <entero> = <entero>
                           | <caracter> = <caracter>
                           | <booleano> = <booleano>
                           | <real> = <real>
                           | <booleano> = <entero>
                           | <entero> = <booleano>
                           | <real> = <entero>
                           | <real> = <booleano>
<sentencia_if> ::= if <expresion> <Inicio_de_bloque>
                   <Sentencia>
                   <Fin_de_bloque>
<sentencia_while> ::= while <expresion> <Inicio_de_bloque>
                      <Sentencia>
                      <Fin_de_bloque>
<sentencia_entrada> ::= <nomb_entrada> <lista_variables>
<sentencia_salida> ::= <nomb_salida> <lista_expresiones_o_cadena>
<expresion> ::= ( <expresion> )
                | <op_unario> <expresion>
                | <expresion> <op_binario> <expresion>
                | <identificador>
                | <entero>  Aquí ponía constante pero en nuestro caso es lo mismo.
                | <funcion> (si el lenguaje soporta funciones)
                | <entero> <op_binario> <entero>
                | <entero> <op_binario> <real>
                | <real> <op_binario> <entero>
                | <real> <op_binario> <real>
                | <booleano> <op_binario> <booleano>
                | <op_unario> <real>
                | <op_unario> <entero>
                | <op_unario> <booleano>
                | (Resto de expresiones del lenguaje de referencia)  
