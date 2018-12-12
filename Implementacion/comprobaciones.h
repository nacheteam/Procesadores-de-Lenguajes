#ifndef __COMPROBACIONES_H__
#define __COMPROBACIONES_H__

extern int linea;

/* Obtiene el tipo de un literal */
TipoDato getTipoLiteral(char * literal){
  if(!strcmp(literal, "True") || !strcmp(literal, "False"))
    return booleano;
  else if(literal[0] == "'")
    return caracter;
  else{
    int n = strlen(literal);
    for (int i = 0; i < n; i++) {
      if(literal[i] == '.')
        return real;
    }
    return entero;
  }

  printf("[Línea %d] Error de implementación: Literal '%s' de tipo desconocido\n", linea, literal);
  return desconocido;
}

void compruebaCondicion(char * sentencia, TipoDato tipo){
  if(tipo != booleano)
    printf("[Línea %d] Error semántico: Expresión de tipo '%s' en condición para '%s'\n", linea, tipoStr(tipo), sentencia);
}


#endif
