
CC = gcc
CFLAGS = -Wall

TARGET = calc.exe

SOURCES = ./calc.tab.c ./lex.yy.c ./symtab.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) -lm -lfl

calc.tab.c calc.tab.h: ./calc.y
	bison -d ./calc.y

lex.yy.c: ./calc.l ./calc.tab.h
	flex ./calc.l

clean:
	del $(TARGET) calc.tab.c calc.tab.h lex.yy.c