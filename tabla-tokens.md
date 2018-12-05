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
| PROCED           | \"void\"                 | 273    |           |
| ID               | \[a-zA-Z\]\[a-zA-Z0-9\]* | 274    |           |
| PARIZQ           | \"(\"                    | 275    |           |
| PARDER           | \")\"                    | 276    |           |
| SIGNO            | \[+-\]                   | 277    |           |
| UNARIODER        | \"<<\"\|\">>\"           | 278    |           |
| UNARIOIZQ        | \[!#?$\]                 | 279    |           |
| OR               | \"\|\|\"                 | 280    |           |
| AND              | \"&&\"                   | 281    |           |
| XOR              | \"^\"                    | 282    |           |
| COMP_IG          | \[=!\]=                  | 283    |           |
| COMP_MM          | \[<>\]=?                 | 284    |           |
| PROD_DIV_MOD     | \[*/%\]                  | 285    |           |
| EXP              | \"**\"                   | 286    |           |
| ARROBA           | \"@\"                    | 287    |           |
| ARROBARROBA      | \"@@\"                   | 288    |           |
| LLAIZQ           | \"{\"                    | 289    |           |
| LLADER           | \"}\"                    | 290    |           |
| CORIZQ           | \"\[\"                   | 291    |           |
| CORDER           | \"\]\"                   | 292    |           |
| PYC              | \";\"                    | 293    |           |
| COMA             | \",\"                    | 294    |           |
