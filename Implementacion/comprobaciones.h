#ifndef __COMPROBACIONES_H__
#define __COMPROBACIONES_H__

extern int linea;

/* Obtiene el tipo de un literal */
// TODO: probar
// TODO: ¿esto no debería hacerlo el analizador léxico?
TipoDato getTipoLiteral(char * literal){
  switch(literal[0]) {
    case 'T':
    case 'F':
      return booleano;
    case '\'':
      return caracter;
    default:
      for (char * p = literal; *p != '\0'; ++p)
        if (*p <= '0' || *p >= '9')
          return real;

      return entero;
  }
}

void compruebaCondicion(char * sentencia, TipoDato tipo){
  if(tipo != booleano)
    printf("[Línea %d] Error semántico: Expresión de tipo '%s' en condición para '%s'\n", linea, tipoStr(tipo), sentencia);
}


#endif
