# Makefile para la Calculadora

# Compilador y flags
CC = gcc
CFLAGS = -Wall

# Archivos objeto y ejecutables
TARGET = calc.exe
SOURCES = calc.tab.c lex.yy.c symtab.c

all: $(TARGET)

# Regla principal: compilar el ejecutable
# Se añade -lm para las funciones matemáticas (sin, cos, pow)
$(TARGET): calc.tab.c lex.yy.c symtab.c
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) -lm

# Generar código de Bison (Crea calc.tab.c y calc.tab.h)
calc.tab.c calc.tab.h: calc.y
	bison -d calc.y

# Generar código de Flex (Crea lex.yy.c)
lex.yy.c: calc.l calc.tab.h
	flex calc.l

# Limpieza de archivos generados
clean:
	del $(TARGET) calc.tab.c calc.tab.h lex.yy.c