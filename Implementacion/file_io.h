#ifndef __FILE_IO_H__
#define __FILE_IO_H__

#include <stdio.h>

FILE * abrir_entrada(int argc, char* argv[]);
FILE * abrir_salida (int argc, char* argv[]);
void cerrar_salida (FILE * f);

#endif
