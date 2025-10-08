######################################################################
#
#                      Explicacio makefile
#
######################################################################

CC = gcc            # Compilador de C
LEX = flex          # Programa flex
YACC = bison        # Programa bison
LIB = -lfl          # Librería de Flex

SRC_LEX = exemple.l # Fichero fuente de Flex
SRC_YACC = exemple.y # Fichero fuente de Bison

LEX_OUT = lex.yy.c  # Código C generado por Flex
YACC_OUT_C = exemple.tab.c  # Código C generado por Bison
YACC_OUT_H = exemple.tab.h  # Cabecera generada por Bison
YACC_OUT = $(YACC_OUT_C) $(YACC_OUT_H) # Agrupa los dos outputs

OTHERS = exemple.output  # Ficheros adicionales (ej: informe de Bison)
OBJ = *.o                # Objetos temporales de compilación

SRC = exemple_main.c      # Programa principal
BIN = exemple.exe         # Nombre del ejecutable final (Windows)

SRC_EXTRA = exemple_dades.c exemple_funcions.c # Otros módulos de C

LFLAGS =                  # Flags extra para Flex (vacío en este caso)
YFLAGS = -d -v            # -d: genera .h con tokens | -v: genera informe parser.output
CFLAGS = -Wall -g         # -Wall: todas las advertencias | -g: info para depuración

EG_IN = ex_entrada.txt    # Archivo de entrada de prueba
EG_OUT = ex_sortida.txt   # Archivo de salida de prueba

######################################################################
#
#                            Cicle de vida
#
######################################################################

1. Pasamos el codigo exemple.y (codigo donde se especifican las reglas de deteccion de tokens) a un exemple.tab.c y exemple.tab.h

2. Pasamos el codigo exemple.y (codigo donde se especifican las funciones que detectan los tokens) a un lex.yy.c

3. Compilamos los .c con gcc

4. Es genera un 