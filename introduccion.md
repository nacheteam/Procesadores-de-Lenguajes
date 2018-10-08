# Introducción

*Pimf* es un lenguaje imperativo, fuertemente tipado y con sintaxis inspirada en la sintaxis tipo C.
Su principales diferencias con la sintaxis tipo C están en el uso de delimitadores para la sección de declaración de variables (con `begin` y `end` respectivamente)y en la posibilidad de declaración anidada de subprogramas.

Sus palabras reservadas están en inglés e incluyen las sentencias `read` y `write` que se utilizan para lectura y escritura, así como las referentes a las estructuras de control como `if` o `while`.
Incluye una estructura de control `repeat`-`until` con una semántica similar al bucle `do`-`while` en C.

No existen las funciones en *Pimf*: los programas se dividen en subprogramas que funcionan como procedimientos.
El paso es por referencia para posibilitar la devolución de resultados por parte de los procedimientos.

La estructura compuesta básica de *Pimf* es el tipo `list`. `list` define una lista enlazada de tipo homogéneo junto con un cursor que permite operaciones de acceso y modificación arbitrarias.
El lenguaje permite constantes de tipo lista construidos a partir de una lista de expresiones de tipo homogéneo.


