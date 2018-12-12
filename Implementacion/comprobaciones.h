#ifndef __COMPROBACIONES_H__
#define __COMPROBACIONES_H__

#include <string.h>

extern int linea;

/* Obtiene el tipo de un literal */
// TODO: probar
// TODO: ¿esto no debería hacerlo el analizador léxico?
TipoDato getTipoLiteral(char * literal){
  switch(literal[0]) {
    case 'T':
    case 'F':
      return booleano;
    case '\'':
      return caracter;
    default:
      for (char * p = literal; *p != '\0'; ++p)
        if (*p == '.'){
          return real;
        }
      return entero;
  }
}

void compruebaCondicion(char * sentencia, TipoDato tipo){
  if(tipo != booleano)
    printf("[%d] Error semántico: Expresión de tipo no booleano en condición para '%s'\n", linea, sentencia);
}

void compruebaLlamada(Elem * elems, char * proced) {
  INIT_Elem(_elems);
  if (elems == NULL)
    elems = &_elems;

  int proced_id = findTS(proced);
  int parametros_esperados = TS[proced_id].parametros;

  if (elems->tope_elem != parametros_esperados) {
    printf("[%d] Error semántico: Número de parámetros inesperado en una llamada a '%s': se esperaban %d y se ha llamado con %d\n", linea, proced, parametros_esperados, elems->tope_elem);
  }

  // Comprueba los primeros parámetros aunque haya parámetros de más o de menos
  int n_param = parametros_esperados;
  if (n_param > elems->tope_elem)
    n_param = elems->tope_elem;

  for (int i = 0; i < n_param; i++) {
    TipoDato tipo_usado = elems->tipos[i];
    TipoDato tipo_esperado = TS[proced_id + i + 1].tipo_dato;
    if (tipo_usado != tipo_esperado) {
      printf("[%d] Error semántico: El parámetro número %d con el que se ha llamado a '%s' no tiene el tipo esperado: se esperaba %s y se ha recibido %s\n", linea, i+1, proced, tipoStr(tipo_esperado), tipoStr(tipo_usado));
    }
  }
}


#endif
