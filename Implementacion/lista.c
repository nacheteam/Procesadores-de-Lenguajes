#include <stdlib.h> // exit
#include "lista.h"

//Si es 0 se desactiva el print, cualquier otro valor hace print.
#define DBUG 1


/******************************************************************************/
/*                   Operadores de inicialización                             */
/******************************************************************************/

/*
 * Reserva memoria para almacenar elementos
 * Asume que la lista está vacía
 */
void reservaMemoria(Lista * l, int n) {
  if(l->tipo==listaentero || l->tipo==listabool)
    l->lista_entero = (int *) malloc(n * sizeof(int));
  else if(l->tipo==listareal)
    l->lista_real = (double *) malloc(n * sizeof(double));
  else if(l->tipo==listachar)
    l->lista_char = (char *) malloc(n * sizeof(char));
}

/*
 * Inserta un entero en la primera posición vacía de la lista
 * Asume que se dispone de memoria suficiente para ello
 */
void insertaInt(Lista * l, int x) {
  l->lista_entero[l->tope++] = x;
}

/*
 * Inserta un real en la primera posición vacía de la lista
 * Asume que se dispone de memoria suficiente para ello
 */
void insertaDouble(Lista * l, double x) {
  l->lista_real[l->tope++] = x;
}

/*
 * Inserta un char en la primera posición vacía de la lista
 * Asume que se dispone de memoria suficiente para ello
 */
void insertaChar(Lista * l, char x) {
  l->lista_char[l->tope++] = x;
}

Lista copiaLista(Lista* l1){
  Lista res;
  res.tope = l1->tope;
  res.cursor = l1->cursor;
  res.lista_entero = (int*) malloc(res.tope*sizeof(int));
  for(int i = 0; i < res.tope; ++i){
    res.lista_entero[i] = l1->lista_entero[i];
  }
  return res;
}
/******************************************************************************/
/*                    Operadores sobre el cursor                              */
/******************************************************************************/

/*
 * Aumenta el cursor si no te sales del tope de la lista
 */
void avanzaCursor(Lista * l){
  if(l->cursor+1 < l->tope)
    l->cursor++;
}

/*
 * Decrementa el cursor si no te vas a los negativos
 */
void retrocedeCursor(Lista * l){
  if(l->cursor > 0)
    l->cursor--;
}

/*
 * Pone el cursor a 0
 */
void reiniciaCursor(Lista * l){
  l->cursor=0;
}

/******************************************************************************/
/*                 Operadores unarios sobre la lista                          */
/******************************************************************************/

/*
 * Devuelve el número de elementos de la lista que es el tope de la misma.
 */
int numeroElementos(Lista * l){
  return(l->tope);
}

/*
 * Devuelve el elemento en la posición del cursor de la lista de enteros
 */
int devuelveActualInt(Lista * l){
  return(l->lista_entero[l->cursor]);
}

/*
 * Devuelve el elemento en la posición del cursor de la lista de reales
 */
double devuelveActualDouble(Lista * l){
  return(l->lista_real[l->cursor]);
}

/*
 * Devuelve el elemento en la posición del cursor de la lista de chars
 */
char devuelveActualChar(Lista * l){
  return(l->lista_char[l->cursor]);
}

/******************************************************************************/
/*                Operadores binarios sobre la lista                          */
/******************************************************************************/

/*
 * Devuelve el elemento en la posición pos si la posición no se sale de los límites.
 */
int devuelvePosicionInt(Lista * l, int pos){
  if(pos < l->tope && pos >= 0)
    return(l->lista_entero[pos]);
  else{
    if(DBUG!=0)
      printf("No se puede acceder a una posición de la lista fuera del rango\n"); // TODO: además de terminar la ejecución, sería razonable imprimir un error (un poco más detallado) en tiempo de ejecución siempre, eliminando el DBUG [aplíquese también a devuelvePosicionDouble y devuelvePosicionChar]
    exit(1);
  }
}

/*
 * Devuelve el elemento en la posición pos si la posición no se sale de los límites.
 */
double devuelvePosicionDouble(Lista * l, int pos){
  if(pos < l->tope && pos>=0)
    return(l->lista_real[pos]);
  else{
    if(DBUG!=0)
      printf("No se puede acceder a una posición de la lista fuera del rango\n");
    exit(1);
  }
}

/*
 * Devuelve el elemento en la posición pos si la posición no se sale de los límites.
 */
char devuelvePosicionChar(Lista * l, int pos){
  if(pos < l->tope && pos>=0)
    return(l->lista_char[pos]);
  else{
    if(DBUG!=0)
      printf("No se puede acceder a una posición de la lista fuera del rango\n");
    exit(1);
  }
}

/*
 * Devuelve un elemento de tipo lista con el elemento en la posición pos quitado
 */
Lista eliminaElemento(Lista * l, int pos){
  Lista res;
  int contador = 0;
  //Ajustamos los valores del tope, cursor y tipo.
  res.tope = l->tope-1;
  if(l->cursor == l->tope-1)
    res.cursor = l->cursor-1;
  else
    res.cursor = l->cursor;
  res.tipo = l->tipo;

  //En función del tipo rellenamos una lista u otra.
  if(res.tipo==listaentero || res.tipo==listabool){
    res.lista_entero = (int *) malloc(res.tope * sizeof(int));
    for(int i = 0; i < l->tope; ++i){
      if(i!=pos){
        res.lista_entero[contador] = l->lista_entero[i];
        contador++;
      }
    }
  }
  else if(res.tipo==listareal){
    res.lista_real = (double *) malloc(res.tope * sizeof(double));
    for(int i = 0; i < l->tope; ++i){
      if(i!=pos){
        res.lista_entero[contador] = l->lista_entero[i];
        contador++;
      }
    }
  }
  else if(res.tipo==listachar){
    res.lista_char = (char *) malloc(res.tope * sizeof(char));
    for(int i = 0; i < l->tope; ++i){
      if(i!=pos){
        res.lista_entero[contador] = l->lista_entero[i];
        contador++;
      }
    }
  }
  return(res);
}

/*
 * Devuelve una lista quitando los elementos a partir de la posición pos.
 */
Lista eliminaFinal(Lista * l, int pos){
  Lista res;
  //Ajustamos los valores del tope, cursor y tipo.
  res.tope = pos+1;
  if(l->cursor>=pos+1)
    res.cursor = pos;
  else
    res.cursor = l->cursor;
  res.tipo = l->tipo;

  //En función del tipo rellenamos una lista u otra.
  if(res.tipo==listaentero || res.tipo==listabool){
    res.lista_entero = (int *) malloc(res.tope * sizeof(int));
    for(int i = 0; i < l->tope && i<=pos; ++i){
      res.lista_entero[i] = l->lista_entero[i];
    }
  }
  else if(res.tipo==listareal){
    res.lista_real = (double *) malloc(res.tope * sizeof(double));
    for(int i = 0; i < l->tope && i<=pos; ++i){
      res.lista_entero[i] = l->lista_entero[i];
    }
  }
  else if(res.tipo==listachar){
    res.lista_char = (char *) malloc(res.tope * sizeof(char));
    for(int i = 0; i < l->tope && i<=pos; ++i){
      res.lista_entero[i] = l->lista_entero[i];
    }
  }
  return(res);
}

/*
 * Concatena dos listas y devuelve una copia
 */
Lista concatenaListas(Lista * l1, Lista * l2){
  Lista res;
  int contador = 0;
  //Actualiza tope, cursor y tipo de forma adecuada
  res.tope = l1->tope+l2->tope;
  res.cursor = 0;
  res.tipo = l1->tipo;

  //En función del tipo de la lista la generas en orden
  if(res.tipo==listaentero || res.tipo==listabool){
    res.lista_entero = (int *) malloc(res.tope * sizeof(int));
    for(int i = 0; i < l1->tope; ++i){
      res.lista_entero[contador] = l1->lista_entero[i];
      contador++;
    }
    for(int i = 0; i < l2->tope; ++i){
      res.lista_entero[contador] = l2->lista_entero[i];
      contador++;
    }
  }
  else if(res.tipo==listareal){
    res.lista_real = (double *) malloc(res.tope * sizeof(double));
    for(int i = 0; i < l1->tope; ++i){
      res.lista_real[contador] = l1->lista_real[i];
      contador++;
    }
    for(int i = 0; i < l2->tope; ++i){
      res.lista_real[contador] = l2->lista_real[i];
      contador++;
    }
  }
  else if(res.tipo==listachar){
    res.lista_char = (char *) malloc(res.tope * sizeof(char));
    for(int i = 0; i < l1->tope; ++i){
      res.lista_char[contador] = l1->lista_char[i];
      contador++;
    }
    for(int i = 0; i < l2->tope; ++i){
      res.lista_char[contador] = l2->lista_char[i];
      contador++;
    }
  }
  return(res);
}

/*
 * Suma x a los elementos de la lista
 */
Lista sumaValorInt(Lista * l, int x){
  Lista res = copiaLista(l);
  for(int i = 0; i < res.tope; ++i)
    res.lista_entero[i]+=x;
  return res;
}

/*
 * Suma x a los elementos de la lista
 */
Lista sumaValorDouble(Lista * l, double x){
  Lista res = copiaLista(l);
  for(int i = 0; i < res.tope; ++i)
    res.lista_real[i]+=x;
  return res;
}

/*
 * Resta x a los elementos de la lista
 */
Lista restaValorInt(Lista * l, int x){
  Lista res = copiaLista(l);
  for(int i = 0; i < l->tope; ++i)
    l->lista_entero[i]-=x;
}

/*
 * Resta x a los elementos de la lista
 */
Lista restaValorDouble(Lista * l, double x){
  Lista res = copiaLista(l);
  for(int i = 0; i < res.tope; ++i)
    res.lista_real[i]-=x;
  return res;
}

/*
 * Multiplica x a los elementos de la lista
 */
Lista productoValorInt(Lista * l, int x){
  Lista res = copiaLista(l);
  for(int i = 0; i < res.tope; ++i)
    res.lista_entero[i]*=x;
  return res;
}

/*
 * Multiplica x a los elementos de la lista
 */
Lista productoValorDouble(Lista * l, double x){
  Lista res = copiaLista(l);
  for(int i = 0; i < res.tope; ++i)
    res.lista_real[i]*=x;
  return res;
}

/*
 * Divide por x a los elementos de la lista
 */
Lista divideValorDouble(Lista * l, double x){
  Lista res = copiaLista(l);
  for(int i = 0; i < res.tope; ++i)
    res.lista_real[i]/=x;
  return res;
}

/******************************************************************************/
/*               Operadores ternarios sobre la lista                          */
/******************************************************************************/

/*
 * Añade el elemento elem en la posición pos devolviendo una copia
 */
Lista anadeElementoInt(Lista * l, int pos, int elem){
  Lista res;
  int contador = 0;
  res.tope = l->tope+1;
  res.cursor = l->cursor;
  res.tipo = l->tipo;
  if (res.cursor <= pos)
    res.cursor++; // El cursor estará en el mismo elemento en el que estaba en la lista original

  res.lista_entero = (int *) malloc(res.tope * sizeof(int));
  for(int i = 0; i < res.tope; ++i){
    if(i==pos)
      res.lista_entero[i] = elem;
    else{
      res.lista_entero[i] = l->lista_entero[contador];
      contador++;
    }
  }
  return(res);
}

/*
 * Añade el elemento elem en la posición pos devolviendo una copia
 */
Lista anadeElementoDouble(Lista * l, int pos, double elem){
  Lista res;
  int contador = 0;
  res.tope = l->tope+1;
  res.cursor = l->cursor;
  res.tipo = l->tipo;
  if (res.cursor <= pos)
    res.cursor++; // El cursor estará en el mismo elemento en el que estaba en la lista original

  res.lista_real = (double *) malloc(res.tope * sizeof(double));
  for(int i = 0; i < res.tope; ++i){
    if(i==pos)
      res.lista_real[i] = elem;
    else{
      res.lista_real[i] = l->lista_real[contador];
      contador++;
    }
  }
  return(res);
}

/*
 * Añade el elemento elem en la posición pos devolviendo una copia
 */
Lista anadeElementoChar(Lista * l, int pos, char elem){
  Lista res;
  int contador = 0;
  res.tope = l->tope+1;
  res.cursor = l->cursor;
  res.tipo = l->tipo;
  if (res.cursor <= pos)
    res.cursor++; // El cursor estará en el mismo elemento en el que estaba en la lista original

  res.lista_char = (char *) malloc(res.tope * sizeof(char));
  for(int i = 0; i < res.tope; ++i){
    if(i==pos)
      res.lista_char[i] = elem;
    else{
      res.lista_char[i] = l->lista_char[contador];
      contador++;
    }
  }
  return(res);
}


/*
 * Imprime listas
 *
*/

void imprimeListaInt(Lista * l){
  printf("[");
  for(int i = 0; i < l->tope; ++i){
    printf("%d", l->lista_entero[i]);
    if(i != l->tope -1)
      printf(", ");
  }
  printf("]");
}

void imprimeListaDouble(Lista * l){
  printf("[");
  for(int i = 0; i < l->tope; ++i){
    printf("%lf", l->lista_real[i]);
    if(i != l->tope -1)
      printf(", ");
  }
  printf("]");
}

void imprimeListaChar(Lista * l){
  printf("[");
  for(int i = 0; i < l->tope; ++i){
    printf("%c", l->lista_char[i]);
    if(i != l->tope -1)
      printf(", ");
  }
  printf("]");
}

void imprimeListaBool(Lista * l){
  printf("[");
  for(int i = 0; i < l->tope; ++i){
    if(l->lista_entero[i])
      printf("True");
    else
      printf("False");
    if(i != l->tope -1)
      printf(", ");
  }
  printf("]");
}
