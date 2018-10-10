# Semántica
## Tipos

En este lenguaje tenemos tipos base y tipos compuestos. Los tipos base son enteros, booleanos, caracteres y reales. Para cada tipo base existe un tipo compuesto, que son las listas dinámicas con elementos de ese tipo.

Los enteros tienen signo y se representan con 32 bits y los reales se representan con 64 bits siguen la aritmética de punto flotante.

Una lista es una secuencia ordenada de elementos de tipo base acompañada de un cursor, que es un entero no negativo menor que el número de elementos de la lista. El valor por defecto de un cursor es 0. El tamaño de una lista no está especificado y puede cambiar durante la ejecución.

La declaración de una variable de tipo lista de elementos de tipo `tipo_base` se realiza con la instrucción `list of tipo_base unalista, otralista;`.

## Expresiones

### Enteros

#### Operadores

- Operador de división: devuelve la división entera: el mayor entero menor o igual al cociente como números reales.
- Los operadores de suma, resta, multiplicación, ++ y -- tienen el comportamiento esperado al igual que en C, devolviendo todos como resultado un elemento de tipo entero y modificando el valor antes de devolverlo.

- Los operadores lógicos asociados <,>,<=,>=,!=,== tienen el comportamiento esperado, devolviendo como resultado un elemento de tipo booleano.
- El operador ** permite elevar un número a otro teniendo que ser el exponente un entero. El resultado es la potencia de base el elemento a la izquierda de ** y de exponente el elemento a la derecha del mismo.
- El operador \% realiza la operación módulo sobre dos enteros, devolviendo el resto de su división. Es decir, para $a,b$ se define $a \% b = a - (a/b) \cdot b$.

### Booleanos

#### Operadores

- Los operadores usuales entre booleanos como !, ||, \&\& tienen el comportamiento esperado, devolviendo la negación del booleano, la operación OR y la operación AND respectivamente devolviendo un booleano como resultado.
- El operador ^ realiza la operación XOR entre booleanos, devolviendo como resultado un elemento de tipo booleano.

### Real

#### Operadores

- El operador ** es el operador de potencia, que tiene un elemento real a la izquierda, que será la base, y un elemento entero a la derecha, que será entero y representará al exponente. Devuelve, por tanto, un elemento de tipo real.
- Los operadores <,>,>=,<=,!=,== devuelven un elemento de tipo booleano y representan las operaciones usuales de comparación.

### Caracter

#### Operadores

- Los operadores asociados a los elementos de tipo caracter son == y != que nos devuelven un elemento de tipo booleano y representan la operaciones usuales de comparación.

### Listas

#### Agregados

Un agregado es una expresión que construye una lista. Consiste en una secuencia entre corchetes posiblemente vacía de expresiones del mismo tipo base separadas por comas. Por ejemplo, un agregado que construye una lista de enteros sería `[0, 1+2, 3*4]`. El valor inicial del cursor es 0. El orden de los elementos de la expresión indica el orden de los elementos de la lista.

#### Operadores

Los operadores sobre listas son:

- Operador longitud: la longitud de la lista es un valor entero que expresa el número de elementos de la lista. La longitud de la lista `lista` se obtiene con `#lista`.
- Operador elemento actual: el elemento actual es el valor del elemento de una lista en la posición indicada por el cursor. El elemento actual de la lista `lista` sería `?lista`.
- Operador elemento posición: el operador elemento posición expresa el valor del elemento de una lista en una posición expresada por un entero que está comprendido entre cero inclusive y la longitud de la lista exclusive. Consideramos que el primer elemento está en la posición 0. El elemento en la posición `n` de la lista `lista` es `lista@n`.
- Operador añadir elemento en una posición: el operador añadir elemento en una posición devuelve una lista a partir de una lista `l`, un elemento `x` y una posición `n`. La lista que devuelve tiene un elemento más que la lista original, tiene valores idénticos para elementos en posiciones menores que `n`, tiene como valor en la posición `n` el de `x` y para cada elemento en la posición `i+1` con `i` mayor o igual que `n` tiene el valor del elemento en la posición `i` de la lista `l`. La posición `n` debe estar comprendida entre 0 y el tamaño de la lista, ambos inclusive. El operador añadir el elemento `x` en la posición `n` de la lista `l` se expresaría como `l++x@n`.
- Operador borrar elemento en una posición: el operador borrar elemento en una posición devuelve una lista a partir de una lista `l` y una posición `n`. La lista que devuelve tiene un elemento menos que la lista original, tiene valores idénticos a la lista `l` para posiciones menores que `n` y para cada posición `i` con `i` mayor o igual que `n` tiene el valor el elemento en la posición `i+1` de la lista `l`. La posición `n` debe estar comprendida entre 0 inclusive y el tamaño de la lista exclusive. El operador borrar el elemento en la posición `n` de la lista `l` se expresa como `l--n`.
- Operador borrar lista a partir de una posición: el operador borrar lista a partir de una posición devuelve una lista a partir de una lista `l` y una posición `n`. La lista que devuelve tiene tamaño `n` y cada elemento vale lo mismo que el elemento en la misma posición en la lista `l`. La posición `n` debe ser mayor o igual que 0. El operador borrar lista `l` a partir de la posición `n` se expresa como `l%n`.
- Operador concatenar listas: El operador de concatenación de listas toma dos listas `l1` y `l2` de longitudes $n$ y $m$ respectivamente y devuelve otra lista `l3` de longitud `n`+`m`. Se expresa `l1**l2`. `l3@i` = `l1@i` cuando $\texttt{i} < \texttt{n}$ y si $\texttt{i} > \texttt{n}$, sea $j = i - n$, entonces `l3@i` = `l2@j`.
- Operador suma y producto: Los operadores suma y producto toman una lista `l` con longitud $n$ y un valor `x` del tipo base de la lista que debe ser entero o real. Se expresan como `l+x` o`x+l` en el caso del operador suma y `l*x` o `x*l` en el caso del producto. En ambos casos devuelven una nueva lista `l2` de longitud $n$. Si `i` es una posición válida,
en el caso del operador suma $\texttt{l2@i} = \texttt{l1@i} + \texttt{x}$ y en el operador producto, $\texttt{l2@i} = \texttt{l1@i}*\texttt{x}$.
- Operador resta: El operador resta toma una lista `l` con longitud $n$ y un valor `x` del tipo base de la lista, que debe ser entero o real. Se expresa como `l-x`. Devuelven una nueva lista `l2` de longitud $n$. Si `i` es una posición válida, $\texttt{l2@i} = \texttt{l1@i} - \texttt{x}$.
- Operador división: El operador división toma una lista `l` con longitud $n$ y un valor `x` del tipo base de la lista, que debe ser real. Se expresa como `l-x`. Devuelven una nueva lista `l2` de longitud $n$. Si `i` es una posición válida, $\texttt{l2@i} = \texttt{l1@i}/\texttt{x}$.


## Sentencias

### Listas

Las sentencias sobre listas son las siguientes:

- Sentencia avanzar: la sentencia avanzar incrementa en una unidad el valor del cursor de una lista si este es menor que el tamaño de la lista y no lo modifica en otro caso. Avanzar una lista `l` se expresa como `l>>`.
- Sentencia retroceder: la sentencia avanzar decrementa en una unidad el valor del cursor de una lista si este es mayor que 0 y no lo modifica en otro caso. Retroceder una lista `l` se expresa como `l<<`.
- Sentencia cursor al comienzo de la lista: la sentencia cursor al comienzo de la lista modifica el valor del cursor de una lista y lo pone a 0. Aplicar esta sentencia a la lista `l` se expresa como `$l`.

### Estructuras de control

El lenguaje tiene estructuras de control básicas de cualquier lenguaje como `if`/`else` o `while`. También tiene sentencias de tipo `repeat <Sentencia> until <expresion>`, que funciona de la siguiente manera:

1. ejecuta `<Sentencia>`;
2. si `<expresion>` se evalúa a `True`, termina; si se evalúa a `False`, repite 1.
