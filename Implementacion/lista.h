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
int devuelveActualInt(Lista l);    //Operador ?l
double devuelveActualDouble(Lista l);    //Operador ?l
bool devuelveActualBool(Lista l);    //Operador ?l
char devuelveActualChar(Lista l);    //Operador ?l

//Operadores binarios sobre la lista
int devuelvePosicionInt(Lista l,int pos);    //Operador l@x
double devuelvePosicionDouble(Lista l,int pos);    //Operador l@x
bool devuelvePosicionBool(Lista l,int pos);    //Operador l@x
char devuelvePosicionChar(Lista l,int pos);    //Operador l@x
Lista eliminaElemento(Lista l,int pos);       //Operador l--x
Lista eliminaFinal(Lista l, int pos);         //Operador l%x
Lista concatenaListas(Lista l1, Lista l2);    //Operador l1**l2
void sumaValorInt(Lista& l, int x);            //Operador l+x ó x+l
void sumaValorDouble(Lista& l, double x);            //Operador l+x ó x+l

//Operadores ternarios sobre la lista

#endif
