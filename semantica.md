# Semántica
## Tipos

\nombre tiene tipos base y tipos compuestos. Los tipos base son enteros, booleanos, caracteres y reales. Para cada tipo base existe un tipo compuesto, que son las listas dinámicas con elementos de ese tipo.

Una lista es una secuencia ordenada de elementos de tipo base acompañada de un cursor, que es un entero no negativo menor que el número de elementos de la lista. El valor por defecto de un cursor es 0. El tamaño de una lista no está especificado y puede cambiar durante la ejecución.

La declaración de una variable de tipo lista de elementos de tipo `tipo_base` se realiza con la instrucción `list of tipo_base unalista, otralista;`.

Los enteros tienen signo y se representan con 32 bits, y los reales se representan con 64 bits y siguen la aritmética de punto flotante.

## Operadores

### Varios tipos

- `==` y `!=` pueden utilizarse entre dos elementos de un mismo tipo y comparan por igualdad (esto es, si las expresiones se evalúan a lo mismo).
- `<`,`>`,`<=`,`>=` comparan por desigualdad dos elementos de un mismo tipo. Devuelven un booleano. `False < True` y las listas se comparan por orden lexicográfico.

### Enteros

- `/` devuelve la división entera: el mayor entero menor o igual al cociente como números reales.
- La suma, resta, multiplicación, ++ y -- se comportan igual que en C. Devuelven un entero.
- `++` y `--` modifican el valor antes de devolverlo
- `**` permite elevar un número a otro teniendo que ser el exponente un entero. El resultado es la potencia de base el elemento a la izquierda de ** y de exponente el elemento a la derecha del mismo.
- \% realiza la operación módulo sobre dos enteros, devolviendo el resto de su división. Es decir, para $a,b$ se define $a \% b = a - (a/b) \cdot b$ donde `/` es la división entera.

### Booleanos

- `!`, `||`, `&&` y `^`  calculan las operaciones NOT, OR, AND y XOR respectivamente.

### Real

- Los operadores de suma, división, resta, multiplicación son las operaciones usuales que devuelven como resultado un elemento de tipo real.
- `**` es el operador de potencia, que tiene un elemento real a la izquierda, que será la base, y un elemento entero a la derecha, será el exponente. Devuelve un real.

### Listas

- `#` calcula la longitud de una lista, un valor entero que expresa el número de elementos de la lista. La longitud de `lista` se obtiene con `#lista`.
- `?` calcula el elemento actual: el valor del elemento de una lista en la posición indicada por el cursor. El elemento actual `lista` sería `?lista`.
- `@` expresa el valor del elemento de una lista en una posición, expresada por un entero comprendido entre 0 inclusive y la longitud de la lista exclusive. El primer elemento está en la posición 0. El elemento en la posición `n` de la lista `lista` es `lista@n`.
- `l++x@n` devuelve una nueva lista a partir de una lista `l`, un elemento `x` y una posición `n`. La lista que devuelve tiene un elemento más que la lista original, tiene valores idénticos para elementos en posiciones menores que `n`, tiene como valor en la posición `n` el de `x` y para cada elemento en la posición `i+1` con `i` mayor o igual que `n` tiene el valor del elemento en la posición `i` de la lista `l`. La posición `n` debe estar comprendida entre 0 y el tamaño de la lista, ambos inclusive.
- `--` devuelve una lista a partir de una lista `l` y una posición `n`. La lista que devuelve tiene un elemento menos que la lista original, tiene valores idénticos a la lista `l` para posiciones menores que `n` y para cada posición `i` con `i` mayor o igual que `n` tiene el valor el elemento en la posición `i+1` de la lista `l`. La posición `n` debe estar comprendida entre 0 inclusive y el tamaño de la lista exclusive. El operador borrar el elemento en la posición `n` de la lista `l` se expresa como `l--n`.
- `%` devuelve una lista a partir de una lista `l` y una posición `n` que excluye los elementos de `l` a partir de `n`. La lista que devuelve tiene tamaño `n` y cada elemento vale lo mismo que el elemento en la misma posición en la lista `l`. La posición `n` debe ser mayor o igual que 0. El operador borrar lista `l` a partir de la posición `n` se expresa como `l%n`.
- `**` toma dos listas `l1` y `l2` de longitudes $n$ y $m$ respectivamente y devuelve otra lista `l3` de longitud `n`+`m`. Se expresa `l1**l2`. `l3@i` = `l1@i` cuando $\texttt{i} < \texttt{n}$ y si $\texttt{i} > \texttt{n}$, sea $j = i - n$, entonces `l3@i` = `l2@j`.
- `+` y `*` toman una lista `l` con longitud $n$ y un valor `x` del tipo base de la lista que debe ser entero o real. Se expresan como `l+x` o`x+l` en el caso del operador suma y `l*x` o `x*l` en el caso del producto. En ambos casos devuelven una nueva lista `l2` de longitud $n$. Si `i` es una posición válida,
en el caso del operador suma $\texttt{l2@i} = \texttt{l1@i} + \texttt{x}$ y en el operador producto, $\texttt{l2@i} = \texttt{l1@i}*\texttt{x}$.
- `-` toma una lista `l` con longitud $n$ y un valor `x` del tipo base de la lista, que debe ser entero o real. Se expresa como `l-x`. Devuelven una nueva lista `l2` de longitud $n$. Si `i` es una posición válida, $\texttt{l2@i} = \texttt{l1@i} - \texttt{x}$.
- `/` toma una lista `l` con longitud $n$ y un valor `x` del tipo base de la lista, que debe ser real. Se expresa como `l-x`. Devuelven una nueva lista `l2` de longitud $n$. Si `i` es una posición válida, $\texttt{l2@i} = \texttt{l1@i}/\texttt{x}$.

## Literales

Un agregado es una expresión que construye una lista. Consiste en una secuencia entre corchetes posiblemente vacía de expresiones del mismo tipo base separadas por comas. Por ejemplo, un agregado que construye una lista de enteros sería `[0, 1+2, 3*4]`. El valor inicial del cursor es 0. El orden de los elementos de la expresión indica el orden de los elementos de la lista.

## Sentencias

### Listas

Las sentencias sobre listas son las siguientes:

- Sentencia avanzar: la sentencia avanzar incrementa en una unidad el valor del cursor de una lista si este es menor que el tamaño de la lista y no lo modifica en otro caso. Avanzar una lista `l` se expresa como `l>>`.
- Sentencia retroceder: la sentencia avanzar decrementa en una unidad el valor del cursor de una lista si este es mayor que 0 y no lo modifica en otro caso. Retroceder una lista `l` se expresa como `l<<`.
- Sentencia cursor al comienzo de la lista: la sentencia cursor al comienzo de la lista modifica el valor del cursor de una lista y lo pone a 0. Aplicar esta sentencia a la lista `l` se expresa como `$l`.

### Estructuras de control

El lenguaje tiene estructuras de control básicas de cualquier lenguaje como `if`/`else` o `while` y sentencias de asignación. También tiene sentencias de tipo `repeat <Sentencia> until <expresion>`, que funciona de la siguiente manera:

1. ejecuta `<Sentencia>`;
2. si `<expresion>` se evalúa a `True`, termina; si se evalúa a `False`, repite 1.
