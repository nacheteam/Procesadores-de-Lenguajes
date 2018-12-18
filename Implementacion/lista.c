#include "listas.h"

//Si es 0 se desactiva el print, cualquier otro valor hace print.
#define DBUG 1

/******************************************************************************/
/*                    Operadores sobre el cursor                              */
/******************************************************************************/

/*
 * Aumenta el cursor si no te sales del tope de la lista
 */
void avanzaCursor(Lista l){
  if(l.cursor+1>=l.tope){
    if(DBUG!=0)
      printf("No se puede avanzar el cursor más allá del tope de la lista\n");
    exit(1);
  }
  else{
    l.cursor++;
  }
}

/*
 * Decrementa el cursor si no te vas a los negativos
 */
void retrocedeCursor(Lista l){
  if(l.cursor-1<0 && DBUG!=0)
    printf("No se puede retroceder el cursor a menos de 0\n");
  else{
    l.cursor--;
  }
}

/*
 * Pone el cursor a 0
 */
void reiniciaCursor(Lista l){
  l.cursor=0;
}

/******************************************************************************/
/*                 Operadores unarios sobre la lista                          */
/******************************************************************************/

/*
 * Devuelve el número de elementos de la lista que es el tope de la misma.
 */
int numeroElementos(Lista l){
  return(l.tope);
}

/*
 * Devuelve el elemento en la posición del cursor de la lista de enteros
 */
int devuelveActualInt(Lista l){
  return(lista_entero[cursor]);
}

/*
 * Devuelve el elemento en la posición del cursor de la lista de reales
 */
double devuelveActualDouble(Lista l){
  return(lista_real[cursor]);
}

/*
 * Devuelve el elemento en la posición del cursor de la lista de bools
 */
bool devuelveActualBool(Lista l){
  return(lista_bool[cursor]);
}

/*
 * Devuelve el elemento en la posición del cursor de la lista de chars
 */
char devuelveActualChar(Lista l){
  return(lista_entero[cursor]);
}

/******************************************************************************/
/*                Operadores binarios sobre la lista                          */
/******************************************************************************/

/*
 * Devuelve el elemento en la posición pos si la posición no se sale de los límites.
 */
int devuelvePosicionInt(Lista l, int pos){
  if(pos<l.tope && pos>=0)
    return(l.lista_entero[pos]);
  else{
    if(DBUG!=0)
      printf("No se puede acceder a una posición de la lista fuera del rango\n");
    exit(1);
  }
}

/*
 * Devuelve el elemento en la posición pos si la posición no se sale de los límites.
 */
double devuelvePosicionDouble(Lista l, int pos){
  if(pos<l.tope && pos>=0)
    return(l.lista_real[pos]);
  else{
    if(DBUG!=0)
      printf("No se puede acceder a una posición de la lista fuera del rango\n");
    exit(1);
  }
}

/*
 * Devuelve el elemento en la posición pos si la posición no se sale de los límites.
 */
bool devuelvePosicionBool(Lista l, int pos){
  if(pos<l.tope && pos>=0)
    return(l.lista_bool[pos]);
  else{
    if(DBUG!=0)
      printf("No se puede acceder a una posición de la lista fuera del rango\n");
    exit(1);
  }
}

/*
 * Devuelve el elemento en la posición pos si la posición no se sale de los límites.
 */
char devuelvePosicionChar(Lista l, int pos){
  if(pos<l.tope && pos>=0)
    return(l.lista_char[pos]);
  else{
    if(DBUG!=0)
      printf("No se puede acceder a una posición de la lista fuera del rango\n");
    exit(1);
  }
}
