# Tabla de tokens

| Nombre del token | Expresión regular          | Código del token | Atributos |
| ---------------- | -------------------------- | ---------------- | --------- |
| INCR             | ++                         | <!---------- TODO ----------->
| DECR             | --
| ASIGN            | =
| IF               | if
| ELSE             | else
| WHILE            | while
| REPEAT           | repeat
| UNTIL            | until
| READ             | read
| WRITE            | write
| CADENA           | "(\[^"\\\]\|\\\["nt\])*"
| LITERAL          | \[0-9\]+(\.\[0-9\]+)?(E\[+-\]\[0-9\]+)?\|0x\[0-9a-f\]+\|'(\[^"\\\]\|\\\["nt\])'\|True\|False
| LISTOF           | list of
| ID               | \[a-zA-Z\][a-zA-Z0-9]*
| TIPOBASE         | (int\|bool\|char\|double)
| MAIN             | main()
| PARIZQ           | (
| SIGNO            | +\|-
| UNARIODER        | <<\|>>
| UNARIOIZQ        | (!\|#\|?\|$)
| BINARIO          | **?\|/\|\[<>\]=?\|==\|!=\|&&\| \|\| \|^\|%
| ARROBA           | @
| LLAIZQ           | {
| LLADER           | }
| PARDER           | )
| CORIZQ           | \[
| CORDER           | \]
| PYC              | ;
| COMA             | ,
