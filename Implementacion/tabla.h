
/* Código adaptado de las diapositivas del tema 7 y del guión de prácticas apéndice F
 (diapositiva 75)*/

typedef enum {
  marca, // Indica que la entrada es una marca de principio de bloque
  procedimiento,
  variable, // variable local
  parametroFormal  // parámetro de un procedimiento situado en una entrada anterior de la tabla
} TipoEntrada;


/* Tipo de dato.
   Sólo aplicable cuando sea variable o parametroFormal*/
typedef enum {
  entero,
  real,
  booleano,
  caracter,
  lista, // TODO: no se distingue?
  desconocido
} TipoDato;

typedef struct atributos{
  int token; // Código del token
  TipoDato tipo; // tipo del token
  char * lexema; // Nombre del token
} atributos;

#define YYSTYPE atributos

/*******************************************************/
/* DEFINICIÓN DE LOS ELEMENTOS DE LA TABLA DE SÍMBOLOS */
/*******************************************************/

#define MAX_TS 1024

typedef struct entrada_ts {
  TipoEntrada tipo_entrada; // Tipo de entrada
  char * nombre; // nombre del identificador
  TipoDato tipo_dato; // Tipo del identificador
  int parametros; // Número de parámetros
} entrada_ts;

struct entrada_ts TS[MAX_TS];
extern long int tope; // Índice de la tabla de símbolos
extern int yylineno;

void entraBloqueTS();
void salBloqueTS();
void insertaVar(char* identificador, char * nombre_dato);
void insertaProcedimiento(char * identificador);
void insertaParametro(char * identificador, char * nombre_dato);