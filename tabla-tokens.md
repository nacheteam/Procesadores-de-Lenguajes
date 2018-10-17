# Tabla de tokens

| Nombre del token |    Expresión regular     | Código | Atributos |
| ---------------- | ------------------------ | -------| --------- |
| INCR             | \"++\"                   | 256    |           |
| DECR             | \"\-\-\"                   | 257    |           |
| ASIGN            | \"=\"                    | 258    |           |
| IF               | \"if\"                   | 259    |           |
| ELSE             | \"else\"                 | 260    |           |
| WHILE            | \"while\"                | 261    |           |
| REPEAT           | \"repeat\"               | 262    |           |
| UNTIL            | \"until\"                | 263    |           |
| READ             | \"read\"                 | 264    |           |
| WRITE            | \"write\"                | 265    |           |
| CADENA           | \\\"(\[^\\\"\'\\]\|\\[\\\"\'nt\])*\\\" | 266 |        |
| LITERAL          | \[0-9\]+(\.\[0-9\]+)?(E\[+-\]?\[0-9\]+)? \| 0x\[0-9a-f\]+ \| \'(\[^\"\'\\]\|\\[\"\'nt\])\' \| \"True\" \| \"False\" | 267 | |
| LISTOF           | \"list of\"              | 268    |           |
| TIPOBASE         | \"int\"\|\"bool\"\|\"char\"\|\"double\" | 269 | |
| MAIN             | \"main()\"               | 270    |           |
| ID               | \[a-zA-Z\]\[a-zA-Z0-9\]* | 271    |           |
| PARIZQ           | \"(\"                    | 272    |           |
| SIGNO            | \[+-\]                   | 273    |           |
| UNARIODER        | \"<<\"\|\">>\"           | 274    |           |
| UNARIOIZQ        | \[!#?$\]                 | 275    |           |
| BINARIO          | \[*/^%\]\|\[=!\]=\|\[<>\]=?\|&&\|\"\|\|\"\|\"**\" | 276 | |
| ARROBA           | \"@\"                    | 277    |           |
| LLAIZQ           | \"{\"                    | 278    |           |
| LLADER           | \"}\"                    | 279    |           |
| PARDER           | \")\"                    | 280    |           |
| CORIZQ           | \"\[\"                   | 281    |           |
| CORDER           | \"\]\"                   | 282    |           |
| PYC              | \";\"                    | 283    |           |
| COMA             | \",\"                    | 284    |           |
