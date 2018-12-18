#ifndef __LISTAS_H__
#define __LISTAS_H__

#include "tabla.h"
#include <string.h>
#include <stdio.h>

typedef struct List{
  int * lista_entero;
  double * lista_real;
  char * lista_char;
  bool * lista_bool;
  TipoDato tipo;        //Tipo de la lista
  int tope;             //Siguiente posición disponible de la lista
  int cursor;          //Posición actual del cabezal
} List;

// Rellena los elementos de la lista en función del tipo.
void declaraLista(char* elementos, TipoDato tipo);

//Operaciones sobre el cursor
void avanzaCursor(Lista l);     //Operador l>>
void retrocedeCursor(Lista l);  //Operador l<<
void reiniciaCursor(Lista l);   //Operador $l

//Operadores unarios sobre la lista
int numeroElementos(Lista l);      //Operador #l


#endif
