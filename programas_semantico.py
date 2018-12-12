import subprocess
import time

# Error 1 en el issue #14
print("------------------------------------------------------------------------")
print("Se espera que haya un error léxico, uno sintáctico y otro semántico en la declaración de variables.")
print("------------------------------------------------------------------------")
subprocess.call(['./Implementacion/semantico', './Ejemplos/Semanticos/declaracion_variables_lss.pimf'])
print("========================================================================")
espera = input("Presiona intro cuando quieras seguir...")
print("\n\n\n")

# Error 2 en el issue #14
print("------------------------------------------------------------------------")
print("Se espera un error de tipo semántico por declarar un parámetro dentro de una función.")
print("------------------------------------------------------------------------")
subprocess.call(['./Implementacion/semantico', './Ejemplos/Semanticos/subprograma_declara_parametro.pimf'])
print("========================================================================")
espera = input("Presiona intro cuando quieras seguir...")
print("\n\n\n")

# Error 3 en el issue #14
print("------------------------------------------------------------------------")
print("Se esperan errores por llamar una función con más argumentos de los que tiene, con argumentos de tipo erróneo y con variables fuera de alcance.")
print("------------------------------------------------------------------------")
subprocess.call(['./Implementacion/semantico', './Ejemplos/Semanticos/subprograma_numero_tipo_fuera_alcance.pimf'])
print("========================================================================")
espera = input("Presiona intro cuando quieras seguir...")
print("\n\n\n")

# Error 4 en el issue #14
print("------------------------------------------------------------------------")
print("Se esperan dos errores por tipos en comparaciones lógicas y dos errores de tipo en operaciones aritméticas.")
print("------------------------------------------------------------------------")
subprocess.call(['./Implementacion/semantico', './Ejemplos/Semanticos/error_tipo_expresiones_logicas_aritmeticas.pimf'])
print("========================================================================")
espera = input("Presiona intro cuando quieras seguir...")
print("\n\n\n")

# Error 5 en el issue #14
print("------------------------------------------------------------------------")
print("Se esperan dos errores: uno por introducir un double en una lista de enteros y otro por igualar una lista de enteros y otra de doubles.")
print("------------------------------------------------------------------------")
subprocess.call(['./Implementacion/semantico', './Ejemplos/Semanticos/errores_expresiones_listas.pimf'])
print("========================================================================")
espera = input("Presiona intro cuando quieras seguir...")
print("\n\n\n")
