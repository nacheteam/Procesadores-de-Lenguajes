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
  int cabezal;          //Posición actual del cabezal
} List;



#endif
