#ifndef __TABLA_H__
#define __TABLA_H__

/* Código adaptado de las diapositivas del tema 7 y del guión de prácticas apéndice F
 (diapositiva 75)*/

typedef enum {
  marca,            // Indica que la entrada es una marca de principio de bloque
  procedimiento,
  variable,         // variable local
  parametroFormal,  // parámetro de un procedimiento situado en una entrada anterior de la tabla
  instrControl      // etiquetas utilizadas en una instrucción de control
} TipoEntrada;


/* Tipo de dato.
   Sólo aplicable cuando sea variable o parametroFormal*/
typedef enum {
  entero,
  real,
  booleano,
  caracter,
  listaentero,
  listareal,
  listabool,
  listachar,
  desconocido
} TipoDato;


// TODO: Documentar
#define MAX_IDS 50
#define MAX_ELEM 200

typedef struct IDS{
  int tope_id;
  char* lista_ids[MAX_IDS];
} IDS;

typedef struct Elem{
  TipoDato tipos[MAX_ELEM];
  int tope_elem;
} Elem;

typedef struct {
  char * EtiquetaSalida;
  char * EtiquetaElse;
  #define EtiquetaEntrada EtiquetaElse
} DescriptorDeInstrControl;

#define INIT_IDS(X) IDS X = {.tope_id = 0}
#define INIT_Elem(X) Elem X = {.tope_elem = 0}

/* Tipo de dato de los atributos */
typedef struct atributos{
  int token; // Código del token
  TipoDato tipo; // tipo del token
  char * lexema; // Nombre del token
  IDS lid;
  Elem el;
} atributos;


/*******************************************************/
/* DEFINICIÓN DE LOS ELEMENTOS DE LA TABLA DE SÍMBOLOS */
/*******************************************************/

#define MAX_TS 1024

typedef struct entrada_ts {
  TipoEntrada tipo_entrada; // Tipo de entrada
  char * nombre;      // nombre del identificador
  TipoDato tipo_dato; // Tipo del identificador
  int parametros;     // Número de parámetros
  DescriptorDeInstrControl etiquetasControl;  // Etiquetas para instrucciones de control
} entrada_ts;

struct entrada_ts TS[MAX_TS];
extern long int tope; // Índice de la tabla de símbolos
extern int linea;

void entraBloqueTS();
void salBloqueTS();
void insertaVar(char* identificador, char * nombre_dato);
void insertaProcedimiento(char * identificador);
void insertaParametro(char * identificador, char * nombre_dato);
void insertaIf(char * etiqueta_salida, char * etiqueta_else);
void insertaRepeatUntil(char * etiqueta_entrada);
void insertaWhile(char * etiqueta_entrada, char * etiqueta_salida);
void salEstructuraControl();
TipoDato tipoTS(char * identificador);
TipoDato leeTipoDato(char * nombre_tipo);
char * tipoStr(TipoDato tipo);
char * tipoCStr(TipoDato tipo);    // Devuelve tipo correspodiente en C
int findTS(char * identificador);
char * findGotoSalida();
char * findGotoElse();
#define findGotoEntrada findGotoElse

int esMain();

#endif
