#ifndef __FILE_IO_H__
#define __FILE_IO_H__

#include <stdio.h>

extern int error;
#define genprintf(f_, ...) { if(!error){fprintf(yyout, (f_), ##__VA_ARGS__); fflush(yyout);} }

FILE * abrir_entrada(int argc, char* argv[]);
FILE * abrir_salida (int argc, char* argv[]);
char * nombre_salida(int argc, char* argv[]);

void entraProced();
void salProced();

#endif
