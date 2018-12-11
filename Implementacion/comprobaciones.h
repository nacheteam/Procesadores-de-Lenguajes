#ifndef __COMPROBACIONES_H__
#define __COMPROBACIONES_H__

extern int linea;

/* Obtiene el tipo de un literal */
// TODO: Implementar
TipoDato getTipoLiteral(char * literal){
    return desconocido;
}

void compruebaCondicion(char * sentencia, TipoDato tipo){
  if(tipo != booleano)
    printf("[Línea %d] Error semántico: Expresión de tipo %d en condición para '%s'\n", linea, tipo, sentencia);
}


#endif
