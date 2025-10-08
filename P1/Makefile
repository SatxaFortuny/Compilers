######################################################################
#
#                           Compiladors
#
######################################################################

CC = gcc
LEX = flex
YACC = bison
LIB = -lfl

SRC_LEX = lexi.l
SRC_YACC = sint.y

LEX_OUT = lexi.yy.c
YACC_OUT_C = sint.tab.c
YACC_OUT_H = sint.tab.h
YACC_OUT = $(YACC_OUT_C) $(YACC_OUT_H)

OTHERS = calc.output
OBJ = *.o

SRC = exemple_main.c
BIN = calc.exe

SRC_EXTRA = exemple_dades.c exemple_funcions.c

LFLAGS =
YFLAGS = -d -v
CFLAGS = -Wall -g

EG_IN = global_test.txt
EG_OUT = ex_sortida.txt



######################################################################

all : yacc lex
	$(CC) -o $(BIN) $(CFLAGS) $(SRC) $(SRC_EXTRA) $(YACC_OUT_C) $(LEX_OUT) $(LIB)

yacc : $(SRC_YACC)
	$(YACC) $(YFLAGS) $(SRC_YACC)

lex : $(SRC_LEX)
	$(LEX) $(LFLAGS) $(SRC_LEX)

clean :
	rm -f *~ $(BIN) $(OBJ) $(YACC_OUT) $(LEX_OUT) $(OTHERS) $(EG_OUT)

eg : $(EG_IN)
	./$(BIN) $(EG_IN) $(EG_OUT)
	cat $(EG_OUT)
