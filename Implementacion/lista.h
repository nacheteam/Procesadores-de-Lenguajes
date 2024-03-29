#ifndef __LISTA_H__
#define __LISTA_H__

#include "tabla.h"
#include <string.h>
#include <stdio.h>

typedef struct Lista{
  int * lista_entero;
  double * lista_real;
  char * lista_char;
  TipoDato tipo;       // Tipo de la lista
  int tope;            // Siguiente posición disponible de la lista
  int cursor;          // Posición actual del cabezal
} Lista;

// Reserva memoria para almacenar n elementos del tipo de la lista
void reservaMemoria(Lista * l, int n);

#define INIT_listaentero(X, n)   Lista X = {.tipo=listaentero, .tope = 0, .cursor = 0}; reservaMemoria(&X, n)
#define INIT_listareal(X, n)     Lista X = {.tipo = listareal, .tope = 0, .cursor = 0}; reservaMemoria(&X, n)
#define INIT_listacaracter(X, n) Lista X = {.tipo = listachar, .tope = 0, .cursor = 0}; reservaMemoria(&X, n)
#define INIT_listabooleano(X, n) Lista X = {.tipo = listabool, .tope = 0, .cursor = 0}; reservaMemoria(&X, n)

// Inserta un elemento en una lista asumiendo que hay memoria suficiente
void insertaInt(Lista * l, int x);
void insertaDouble(Lista * l, double x);
void insertaChar(Lista * l, char x);

//Operaciones sobre el cursor
void avanzaCursor(Lista * l); //Operador l>>
void retrocedeCursor(Lista * l);  //Operador l<<
void reiniciaCursor(Lista * l); //Operador $l

//Operadores unarios sobre la lista
int numeroElementos(Lista * l); //Operador #l
int devuelveActualInt(Lista * l); //Operador ?l
double devuelveActualDouble(Lista * l); //Operador ?l
char devuelveActualChar(Lista * l); //Operador ?l

//Operadores binarios sobre la lista
int devuelvePosicionInt(Lista * l,int pos); //Operador l@x
double devuelvePosicionDouble(Lista * l,int pos); //Operador l@x
char devuelvePosicionChar(Lista * l,int pos); //Operador l@x
Lista eliminaElemento(Lista * l,int pos); //Operador l--x
Lista eliminaFinal(Lista * l, int pos); //Operador l%x
Lista concatenaListas(Lista * l1, Lista * l2);  //Operador l1**l2
Lista sumaValorInt(Lista * l, int x);  //Operador l+x ó x+l
Lista sumaValorDouble(Lista * l, double x);  //Operador l+x ó x+l
Lista restaValorInt(Lista * l, int x); //Operador l-x
Lista restaValorDouble(Lista * l, double x); //Operador l-x
Lista productoValorInt(Lista * l, int x);  //Operador l*x ó x*l
Lista productoValorDouble(Lista * l, double x);  //Operador l*x ó x*l
Lista divideValorDouble(Lista * l, double x);  //Operador l/x

//Operadores ternarios sobre la lista
Lista anadeElementoInt(Lista * l, int pos, int elem); //Operador l++x@z
Lista anadeElementoDouble(Lista * l, int pos, double elem); //Operador l++x@z
Lista anadeElementoChar(Lista * l, int pos, char elem); //Operador l++x@z


void imprimeListaInt(Lista * l);
void imprimeListaDouble(Lista * l);
void imprimeListaChar(Lista * l);
void imprimeListaBool(Lista * l);

#endif
