# Introducción

\nombre es un lenguaje imperativo, fuertemente tipado y con sintaxis inspirada en la sintaxis tipo C.
Sus principales diferencias con la sintaxis tipo C están en el uso de delimitadores para la sección de declaración de variables (con `begin` y `end` respectivamente) y en la posibilidad de declaración anidada de subprogramas.

Sus palabras reservadas están en inglés e incluyen las sentencias `read` y `write` que se utilizan para lectura y escritura, así como las referentes a las estructuras de control como `if` o `while`.
Incluye una estructura de control `repeat`-`until` con una semántica similar al bucle `do`-`while` en C.

No existen las funciones en \nombre: los programas se dividen en subprogramas que funcionan como procedimientos.
El paso es por referencia para posibilitar la devolución de resultados por parte de los procedimientos.

La estructura compuesta básica de \nombre es el tipo `list`. `list` define una lista enlazada de tipo homogéneo junto con un cursor que permite operaciones de acceso y modificación arbitrarias.
El lenguaje permite constantes de tipo lista construidos a partir de una lista de expresiones de tipo homogéneo.

Los tipos de datos elementales de \nombre son los enteros, reales, caracteres y booleanos. Estos tipos tienen las operaciones elementales como la suma, resta, producto, división y las operaciones de comparación entre los mismos. Cada tipo tiene implementadas sus operaciones internas, es decir, que una operación entre dos elementos de un tipo (como la suma, multiplicación, resta o división de enteros) devuelve un valor de ese tipo. Esta regla no es aplicable a las operaciones de comparación ya que estas devuelven un valor booleano. Cabe destacar que otra diferencia entre C y \nombre es la implementación de la división entre enteros. En este caso la división que se realiza por defecto es la división entera.

Igual que en C, \nombre es *case sensitive* con lo que se distingue entre palabras con las mismas letras pero con mayúsculas y minúsculas.
