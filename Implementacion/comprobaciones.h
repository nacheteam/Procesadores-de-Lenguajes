#ifndef __COMPROBACIONES_H__
#define __COMPROBACIONES_H__

#include <string.h>
#include "error.h"
#include <stdarg.h>
#include <stdlib.h>

// Une todos los parámetros que se le pasan
char* uneCadenas(const char* primero, ...)
{
    if( primero == NULL ) {
        return NULL;
    }

    va_list argumentos;
    int i;
    const char *actual;

    va_start(argumentos, primero);
    size_t num_argumentos = 0;
    for(
        actual = primero;
        actual != NULL;
        actual = va_arg(argumentos, char *)
    ) {
        num_argumentos++;
    }
    va_end(argumentos);

    size_t tam_str[num_argumentos];

    size_t res_tam = 0;
    va_start(argumentos, primero);
    for(
        i = 0, actual = primero;
        actual != NULL;
        i++, actual = va_arg(argumentos, char *)
    ) {
        tam_str[i] = strlen(actual);
        res_tam += tam_str[i];
    }
    va_end(argumentos);

    char *res = malloc(res_tam + 1);
    if( res == NULL ) {
        return NULL;
    }

    char *res_pos = res;
    va_start(argumentos, primero);
    for(
        i = 0, actual = primero;
        actual != NULL;
        i++, actual = va_arg(argumentos, char *)
    ) {
        memcpy( res_pos, actual, tam_str[i] );
        res_pos += tam_str[i];
    }
    va_end(argumentos);

    res_pos[0] = '\0';

    return res;
}

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
        if (*p == '.'){
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
