#ifndef __COMPROBACIONES_H__
#define __COMPROBACIONES_H__

#include <string.h>
#include "error.h"

/* Obtiene el tipo de un literal */
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
        if (*p == '.' || *p == 'E' || *p == 'e'){
          return real;
        }
      return entero;
  }
}

void compruebaCondicion(char * sentencia, TipoDato tipo){
  if(tipo != booleano)
    semprintf("Expresión de tipo no booleano en condición para '%s'\n", sentencia);
}

void compruebaLlamada(Elem * elems, char * proced) {
  INIT_Elem(_elems);
  if (elems == NULL)
    elems = &_elems;

  int proced_id = findTS(proced);
  int parametros_esperados = TS[proced_id].parametros;

  if (elems->tope_elem != parametros_esperados) {
    semprintf("Número de parámetros inesperado en una llamada a '%s': se esperaban %d y se ha llamado con %d\n", proced, parametros_esperados, elems->tope_elem);
  }

  // Comprueba los primeros parámetros aunque haya parámetros de más o de menos
  int n_param = parametros_esperados;
  if (n_param > elems->tope_elem)
    n_param = elems->tope_elem;

  for (int i = 0; i < n_param; i++) {
    TipoDato tipo_usado = elems->tipos[i];
    TipoDato tipo_esperado = TS[proced_id + i + 1].tipo_dato;
    if (tipo_usado != tipo_esperado) {
      semprintf("El parámetro número %d con el que se ha llamado a '%s' no tiene el tipo esperado: se esperaba %s y se ha recibido %s\n", i+1, proced, tipoStr(tipo_esperado), tipoStr(tipo_usado));
    }
  }
}

/* Obten tipo de elemento dado tipo de lista. */
TipoDato getTipoElemento(TipoDato tipoLista){
  switch (tipoLista) {
  case listaentero:
    return entero;
  case listareal:
    return real;
  case listabool:
    return booleano;
  case listachar:
    return caracter;
  default:
    return desconocido;
  }
}

/* Obten tipo de lista dado tipo de elemento. */
TipoDato getTipoLista(TipoDato tipoElemento){
  switch (tipoElemento) {
  case entero:
    return listaentero;
  case real:
    return listareal;
  case booleano:
    return listabool;
  case caracter:
    return listachar;
  default:
    return desconocido;
  }
}

/* Comprueba si un elemento es del tipo de una lista. */
int esTipoElemento(TipoDato elemento, TipoDato tipoLista){
  return elemento == getTipoElemento(tipoLista);
}

/* Comprueba si un tipo es lista. */
int esLista(TipoDato tipo){
  return tipo==listaentero || tipo==listareal ||
    tipo==listabool || tipo==listachar;
}

/* Comprueba si es número */
int esNumero(TipoDato tipo){
  return tipo == entero || tipo == real;
}


#endif
