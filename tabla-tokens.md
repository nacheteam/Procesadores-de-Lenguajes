# Tabla de tokens

| Nombre del token |    Expresión regular     | Código | Atributos |
| ---------------- | ------------------------ | -------| --------- |
| INCR             | \"++\"                   | 256    |           |
| DECR             | \"\-\-\"                 | 257    |           |
| ASIGN            | \"=\"                    | 258    |           |
| IF               | \"if\"                   | 259    |           |
| ELSE             | \"else\"                 | 260    |           |
| WHILE            | \"while\"                | 261    |           |
| REPEAT           | \"repeat\"               | 262    |           |
| UNTIL            | \"until\"                | 263    |           |
| READ             | \"read\"                 | 264    |           |
| WRITE            | \"write\"                | 265    |           |
| VARBEGIN         | \"begin\"                | 266    |           |
| VAREND           | \"end\"                  | 267    |           |
| CADENA           | \\\"(\[^\\\"\'\\]\|\\[\\\"\'nt\])*\\\" | 268 |        |
| LITERAL          | \[0-9\]+(\.\[0-9\]+)?(E\[+-\]?\[0-9\]+)? \| 0x\[0-9a-f\]+ \| \'(\[^\"\'\\]\|\\[\"\'nt\])\' \| \"True\" \| \"False\" | 269 | |
| LISTOF           | \"list of\"              | 270    |           |
| TIPOBASE         | \"int\"\|\"bool\"\|\"char\"\|\"double\" | 271 | |
| MAIN             | \"main()\"               | 272    |           |
| ID               | \[a-zA-Z\]\[a-zA-Z0-9\]* | 273    |           |
| PARIZQ           | \"(\"                    | 274    |           |
| PARDER           | \")\"                    | 275    |           |
| SIGNO            | \[+-\]                   | 276    |           |
| UNARIODER        | \"<<\"\|\">>\"           | 277    |           |
| UNARIOIZQ        | \[!#?$\]                 | 278    |           |
| BINARIO          | \[*/^%\]\|\[=!\]=\|\[<>\]=?\|&&\|\"\|\|\"\|\"**\" | 279 | 0:^\|\"**\", 1:\[*/\], 2:\[=!\]=\|[<>]=?, 3:&&, 4:\"\|\|\" |
| ARROBA           | \"@\"                    | 280    |           |
| LLAIZQ           | \"{\"                    | 281    |           |
| LLADER           | \"}\"                    | 282    |           |
| CORIZQ           | \"\[\"                   | 283    |           |
| CORDER           | \"\]\"                   | 284    |           |
| PYC              | \";\"                    | 285    |           |
| COMA             | \",\"                    | 286    |           |
