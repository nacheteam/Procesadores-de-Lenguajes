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
| OR               | \"\|\|\"                 | 279    |           |
| AND              | \"&&\"                   | 280    |           |
| XOR              | \"^\"                    | 281    |           |
| COMP_IG          | \[=!\]=                  | 282    |           |
| COMP_MM          | \[<>\]=?                 | 283    |           |
| PROD_DIV_MOD     | \[*/%\]                  | 284    |           |
| EXP              | \"**\"                   | 285    |           |
| ARROBA           | \"@\"                    | 286    |           |
| LLAIZQ           | \"{\"                    | 287    |           |
| LLADER           | \"}\"                    | 288    |           |
| CORIZQ           | \"\[\"                   | 289    |           |
| CORDER           | \"\]\"                   | 290    |           |
| PYC              | \";\"                    | 291    |           |
| COMA             | \",\"                    | 292    |           |
