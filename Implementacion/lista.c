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

/*
 * Devuelve un elemento de tipo lista con el elemento en la posición pos quitado
 */
Lista eliminaElemento(Lista l, int pos){
  Lista res;
  int contador = 0;
  //Ajustamos los valores del tope, cursor y tipo.
  res.tope = l.tope-1;
  if(l.cursor==tope-1)
    res.cursor = l.cursor-1;
  else
    res.cursor = l.cursor;
  res.tipo = l.tipo;

  //En función del tipo rellenamos una lista u otra.
  if(res.tipo==listaentero){
    res.lista_entero = (int *) malloc(res.tope * sizeof(int));
    for(int i = 0; i < l.tope; ++i){
      if(i!=pos){
        res.lista_entero[contador] = l.lista_entero[i];
        contador++;
      }
    }
  }
  else if(res.tipo==listareal){
    res.lista_real = (double *) malloc(res.tope * sizeof(double));
    for(int i = 0; i < l.tope; ++i){
      if(i!=pos){
        res.lista_entero[contador] = l.lista_entero[i];
        contador++;
      }
    }
  }
  else if(res.tipo==listachar){
    res.lista_char = (char *) malloc(res.tope * sizeof(char));
    for(int i = 0; i < l.tope; ++i){
      if(i!=pos){
        res.lista_entero[contador] = l.lista_entero[i];
        contador++;
      }
    }
  }
  else if(res.tipo==listabool){
    res.lista_bool = (bool *) malloc(res.tope * sizeof(bool));
    for(int i = 0; i < l.tope; ++i){
      if(i!=pos){
        res.lista_entero[contador] = l.lista_entero[i];
        contador++;
      }
    }
  }
  return(res);
}

/*
 * Devuelve una lista quitando los elementos a partir de la posición pos.
 */
Lista eliminaFinal(Lista l, int pos){
  Lista res;
  //Ajustamos los valores del tope, cursor y tipo.
  res.tope = pos+1;
  if(l.cursor>=pos+1)
    res.cursor = pos;
  else
    res.cursor = l.cursor;
  res.tipo = l.tipo;

  //En función del tipo rellenamos una lista u otra.
  if(res.tipo==listaentero){
    res.lista_entero = (int *) malloc(res.tope * sizeof(int));
    for(int i = 0; i < l.tope && i<=pos; ++i){
      res.lista_entero[i] = l.lista_entero[i];
    }
  }
  else if(res.tipo==listareal){
    res.lista_real = (double *) malloc(res.tope * sizeof(double));
    for(int i = 0; i < l.tope && i<=pos; ++i){
      res.lista_entero[o] = l.lista_entero[i];
    }
  }
  else if(res.tipo==listachar){
    res.lista_char = (char *) malloc(res.tope * sizeof(char));
    for(int i = 0; i < l.tope && i<=pos; ++i){
      res.lista_entero[o] = l.lista_entero[i];
    }
  }
  else if(res.tipo==listabool){
    res.lista_bool = (bool *) malloc(res.tope * sizeof(bool));
    for(int i = 0; i < l.tope && i<=pos; ++i){
      res.lista_entero[o] = l.lista_entero[i];
    }
  }
  return(res);
}

/*
 * Concatena dos listas y devuelve una copia
 */
Lista concatenaListas(Lista l1, Lista l2){
  Lista res;
  int contador = 0;
  //Actualiza tope, cursor y tipo de forma adecuada
  res.tope = l1.tope+l2.tope;
  res.cursor = 0;      //Lo pongo a 0 por ponerlo a algo
  res.tipo = l1.tipo;

  //En función del tipo de la lista la generas en orden
  if(res.tipo==listaentero){
    res.lista_entero = (int *) malloc(res.tope * sizeof(int));
    for(int i = 0; i < l1.tope; ++i){
      res.lista_entero[contador] = l1.lista_entero[i];
      contador++;
    }
    for(int i = 0; i < l2.tope; ++i){
      res.lista_entero[contador] = l2.lista_entero[i];
      contador++;
    }
  }
  else if(res.tipo==listareal){
    res.lista_real = (double *) malloc(res.tope * sizeof(double));
    for(int i = 0; i < l1.tope; ++i){
      res.lista_real[contador] = l1.lista_real[i];
      contador++;
    }
    for(int i = 0; i < l2.tope; ++i){
      res.lista_real[contador] = l2.lista_real[i];
      contador++;
    }
  }
  else if(res.tipo==listabool){
    res.lista_bool = (bool *) malloc(res.tope * sizeof(bool));
    for(int i = 0; i < l1.tope; ++i){
      res.lista_bool[contador] = l1.lista_bool[i];
      contador++;
    }
    for(int i = 0; i < l2.tope; ++i){
      res.lista_bool[contador] = l2.lista_bool[i];
      contador++;
    }
  }
  else if(res.tipo==listachar){
    res.lista_char = (char *) malloc(res.tope * sizeof(char));
    for(int i = 0; i < l1.tope; ++i){
      res.lista_char[contador] = l1.lista_char[i];
      contador++;
    }
    for(int i = 0; i < l2.tope; ++i){
      res.lista_char[contador] = l2.lista_char[i];
      contador++;
    }
  }
  return(res);
}

/*
 * Suma x a los elementos de la lista
 */
void sumaValorInt(Lista& l, int x){
  for(int i = 0; i < l.tope; ++i)
    l.lista_entero[i]+=x;
}

/*
 * Suma x a los elementos de la lista
 */
void sumaValorDouble(Lista& l, double x){
  for(int i = 0; i < l.tope; ++i)
    l.lista_real[i]+=x;
}

/*
 * Resta x a los elementos de la lista
 */
void restaValorInt(Lista& l, int x){
  for(int i = 0; i < l.tope; ++i)
    l.lista_entero[i]-=x;
}

/*
 * Resta x a los elementos de la lista
 */
void restaValorDouble(Lista& l, double x){
  for(int i = 0; i < l.tope; ++i)
    l.lista_real[i]-=x;
}

/*
 * Multiplica x a los elementos de la lista
 */
void productoValorInt(Lista& l, int x){
  for(int i = 0; i < l.tope; ++i)
    l.lista_entero[i]*=x;
}

/*
 * Multiplica x a los elementos de la lista
 */
void productoValorDouble(Lista& l, double x){
  for(int i = 0; i < l.tope; ++i)
    l.lista_real[i]*=x;
}

/*
 * Divide por x a los elementos de la lista
 */
void divideValorDouble(Lista& l, double x){
  for(int i = 0; i < l.tope; ++i)
    l.lista_real[i]/=x;
}
