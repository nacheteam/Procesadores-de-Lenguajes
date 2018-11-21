#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "yyerror.h"

// // // // // // // // // // // // // // // // // // // //
//
// Error message printing
//
// Must make messages look nice.  For example:
// msg = "syntax error, unexpected ',', expecting BOOL or CHAR or INT or ID."
// becomes (xx marks important data):
//  0 syntax
//  1 error,
//  2 unexpected
//  3 ',',    xx
//  4 expecting
//  5 BOOL    xx
//  6 or
//  7 CHAR    xx
//  8 or
//  9 INT     xx
// 10 or
// 11 ID.     xx

// assumes a string with breakchar separating each element.
// breakchars will be replaced by null chars: '\0'
// array of pointers to strings is then returned in
// the array strs which must be allocated by the user!
// the number of strings found is returned as a value of
// the function.  This number is always at least 1.
// The array is terminated by a NULL so there must be
// enough room for all the string pointers plus one for the
// sentinal marker.
int split(char *s, char *strs[], char breakchar)
{
    int num;

    strs[0] = s;
    num = 1;
    for (char *p = s; *p; p++) {
        if (*p==breakchar) {
            strs[num++] = p+1;
            *p = '\0';
        }
    }
    strs[num] = NULL;

    return num;
}


// trim off the last character
void trim(char *s)
{
    s[strlen(s)-1] = '\0';
}

#define NUM_TOKENS 38 

static char * const MAP_TOKENS[2*NUM_TOKENS] = {
    "INCR",      "++",
    "DECR",      "--",
    "ASIGN",     "=",
    "IF",        "if",
    "ELSE",      "else",
    "WHILE",     "while",
    "REPEAT",    "repeat",
    "UNTIL",     "until",
    "READ",      "read",
    "WRITE",     "write",
    "VARBEGIN",  "begin",
    "VAREND",    "end",
    "CADENA",    "cadena",
    "LITERAL",   "liter",
    "LISTOF",    "list of",
    "TIPOBASE",  "un tipo",
    "MAIN",      "main()",
    "ID",        "identificador",
    "PARIZQ",    "(",
    "PARDER",    ")",
    "SIGNO",     "+|-",
    "UNARIODER", "<< | >>",
    "UNARIOIZQ", "operador unario por la izquierda",
    "OR",        "||",
    "AND",       "&&",
    "XOR",       "^",
    "COMP_IG",   "== o !=",
    "COMP_MM",   "<= o >= o < o >",
    "PROD_DIV_MOD", "multiplicación o división o módulo",
    "EXP",       "**",
    "ARROBA",    "@",
    "ARROBARROBA", "@@",
    "LLAIZQ",    "{",
    "LLADER",    "}",
    "CORIZQ",    "[",
    "CORDER",    "]",
    "PYC",       ";",
    "COMA",      ","
};


// looks of pretty printed words for tokens that are
// not already in single quotes.  It uses the niceTokenNameMap table.
char *niceTokenStr(char *tokenName) {
    if (tokenName[0] == '\'') return tokenName;

    for (int i = 0; i < NUM_TOKENS; i++)
        if (strcmp(tokenName, MAP_TOKENS[2*i]) == 0)
            return MAP_TOKENS[2*i + 1];

    fprintf(stderr, "Error en la definición de yyerror: '%s' no está entre los tokens definidos\n", tokenName);
    fflush(stderr);
    exit(1);
}


// Is this a message that we need to elaborate with the current parsed token.
// This elaboration is some what of a crap shoot since the token could
// be already overwritten with a look ahead token.   But probably not.
int elaborate(char *s)
{
    return (strstr(s, "constant") || strstr(s, "identifier"));
}


// A tiny sort routine for SMALL NUMBERS of
// of char * elements.  num is the total length
// of the array but only every step elements will
// be sorted.  The "up" flag is direction of sort.
// For example:
//    tinySort(str, i, 2, direction);      // sorts even number elements in array
//    tinySort(str+1, i-1, 2, direction);  // sorts odd number elements in array
//    tinySort(str, i, 1, direction);      // sorts all elements in array
//
void tinySort(char *base[], int num, int step, int up)
{
    for (int i=step; i<num; i+=step) {
        for (int j=0; j<i; j+=step) {
            if (up ^ (strcmp(base[i], base[j])>0)) {
                char *tmp;
                tmp = base[i]; base[i] = base[j]; base[j] = tmp;
            }
        }
    }
}


// This is the yyerror called by the bison parser for errors.
// It only does errors and not warnings.
void yyerror(const char *msg)
{
    if (strncmp(msg, "Error l", 7) == 0) {
        fprintf(stderr, "[Línea %d] %s", linea, msg);
        fflush(stderr);   // force a dump of the error
        return;
    }
  
    char *space;
    char *strs[100];
    int numstrs;

    // make a copy of msg string
    space = strdup(msg);

    // split out components
    numstrs = split(space, strs, ' ');
    if (numstrs>4) trim(strs[3]);

    // translate components
    for (int i=3; i<numstrs; i+=2) {
        strs[i] = niceTokenStr(strs[i]);
    }

    // print components
    fprintf(stderr, "[Línea %d] Error sintáctico: se encontró %s", linea, strs[3]);
    if (elaborate(strs[3])) {
        if (yytext[0]=='\'' || yytext[0]=='"') fprintf(stderr, " %s", yytext);
        else fprintf(stderr, " \'%s\'", yytext);
    }

    if (numstrs>4) fprintf(stderr, ",");

    // print sorted list of expected
    tinySort(strs+5, numstrs-5, 2, 1);
    for (int i=4; i<numstrs; i++) {
        fprintf(stderr, " %s", strs[i]);
    }
    fprintf(stderr, "\n");
    fflush(stderr);   // force a dump of the error

    free(space);
}
