#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
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



// map from string to char * for storing nice translation of
// internal names for tokens.  Preserves (char *) used by
// bison.
static std::map<std::string , char *> niceTokenNameMap;    // use an ordered map (not as fast as unordered)

// WARNING: this routine must be called to initialize mapping of
// (strings returned as error message) --> (human readable strings)
//
void initErrorProcessing() {
    niceTokenNameMap["INCR"] = (char *)"++";
    niceTokenNameMap["DECR"] = (char *)"--";
    niceTokenNameMap["ASIGN"] = (char *)"=";
    niceTokenNameMap["IF"] = (char *)"if";
    niceTokenNameMap["ELSE"] = (char *)"else";
    niceTokenNameMap["WHILE"] = (char *)"while";
    niceTokenNameMap["REPEAT"] = (char *)"repeat";
    niceTokenNameMap["UNTIL"] = (char *)"until";
    niceTokenNameMap["READ"] = (char *)"read";
    niceTokenNameMap["WRITE"] = (char *)"write";
    niceTokenNameMap["VARBEGIN"] = (char *)"begin";
    niceTokenNameMap["VAREND"] = (char *)"end";
    niceTokenNameMap["CADENA"] = (char *)"cadena";
    niceTokenNameMap["LITERAL"] = (char *)"liter";
    niceTokenNameMap["LISTOF"] = (char *)"list of";
    niceTokenNameMap["TIPOBASE"] = (char *)"un tipo";
    niceTokenNameMap["MAIN"] = (char *)"main()";
    niceTokenNameMap["ID"] = (char *)"identificador";
    niceTokenNameMap["PARIZQ"] = (char *)"(";
    niceTokenNameMap["PARDER"] = (char *)")";
    niceTokenNameMap["SIGNO"] = (char *)"+|-";
    niceTokenNameMap["UNARIODER"] = (char *)"<< | >>";
    niceTokenNameMap["UNARIOIZQ"] = (char *)"operador unario por la izquierda";
    niceTokenNameMap["OR"] = (char *)"||";
    niceTokenNameMap["AND"] = (char *)"&&";
    niceTokenNameMap["XOR"] = (char *)"^";
    niceTokenNameMap["COMP_IG"] = (char *)"== o !=";
    niceTokenNameMap["COMP_MM"] = (char *)"<= o >= o < o >";
    niceTokenNameMap["PROD_DIV_MOD"] = (char *)"multiplicación o división o módulo";
    niceTokenNameMap["EXP"] = (char *)"**";
    niceTokenNameMap["ARROBA"] = (char *)"@";
    niceTokenNameMap["ARROBARROBA"] = (char *)"@@";
    niceTokenNameMap["LLAIZQ"] = (char *)"{";
    niceTokenNameMap["LLADER"] = (char *)"}";
    niceTokenNameMap["CORIZQ"] = (char *)"[";
    niceTokenNameMap["CORDER"] = (char *)"]";
    niceTokenNameMap["PYC"] = (char *)";";
    niceTokenNameMap["COMA"] = (char *)",";
}


// looks of pretty printed words for tokens that are
// not already in single quotes.  It uses the niceTokenNameMap table.
char *niceTokenStr(char *tokenName ) {
    if (tokenName[0] == '\'') return tokenName;
    if (niceTokenNameMap.find(tokenName) == niceTokenNameMap.end()) {
        printf("ERROR(sistema): La cadena '%s' no está entre los tokens definidos\n", tokenName);
        fflush(stdout);
        exit(1);
    }
    return niceTokenNameMap[tokenName];
}


// Is this a message that we need to elaborate with the current parsed token.
// This elaboration is some what of a crap shoot since the token could
// be already overwritten with a look ahead token.   But probably not.
bool elaborate(char *s)
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
void tinySort(char *base[], int num, int step, bool up)
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
    printf("Error en la línea %d: Error sintáctico, cadena no esperada %s", linea, strs[3]);
    if (elaborate(strs[3])) {
        if (yytext[0]=='\'' || yytext[0]=='"') printf(" %s", yytext);
        else printf(" \'%s\'", yytext);
    }

    if (numstrs>4) printf(",");

    // print sorted list of expected
    tinySort(strs+5, numstrs-5, 2, true);
    for (int i=4; i<numstrs; i++) {
        printf(" %s", strs[i]);
    }
    printf(".\n");
    fflush(stdout);   // force a dump of the error

    free(space);
}
