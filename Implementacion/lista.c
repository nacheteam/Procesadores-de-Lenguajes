#include "listas.h"

#define DBUG 1

void avanzaCursor(Lista l){
  if(l.cursor+1>=l.tope && DBUG!=0)
    printf("No se puede avanzar el cursor más allá del tope de la lista\n");
  else{
    cursor++;
  }
}
