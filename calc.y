%{
#include <stdio.h>
#include <stdlib.h>
#include "value.h"
#include "symtab.h"

/* yylex() is the flex scanner. yyerror() is the fuction Bison will call in case of an error. */
int yylex(void);
void yyerror(const char *s);
extern int yylineno;
%}

%union {
    int ival;
    float fval;
    char *sval;
    int bval;
}

/* Here what we are doing is defining the tokens that will be given by the Flex scanner. */
%token <ival> NUMBER
%token <sval> ID
%token K_INT
%token K_FLOAT
%token K_STRING
%token K_BOOL
%token EOL 

%%

/* Now we will try to classify everything into a program. Which is defined by a series of lines */
program:
    | program line
    ;

line:
    NUMBER EOL { printf("BISON: NUMBER (%d) + EOL\n", $1); }
    | assign EOL { printf("BISON: ASSIGNATION TRACKED.\n"); }
    | EOL        { printf("BISON: EOL\n"); }
    | error EOL  { printf("BISON: Semantic error. Jumping to the next line.\n"); yyerrok; }
    ;

assign:
    K_INT ID {
        TokenValue *val = (TokenValue*) malloc(sizeof(TokenValue));
        val->type = TYPE_INT;
        val->inicialized=false;
        if (sym_add($2, &val) == SYMTAB_DUPLICATE) {
            yyerror("SEMANTIC ERROR: Duplicate variable\n");
            free(val);
            free($2);
        } else {
            printf("BISON: (%s) -> INTEGER.\n", $2);
        }
    }
    | K_FLOAT ID {
        TokenValue *val = (TokenValue*) malloc(sizeof(TokenValue));
        val->type = TYPE_FLOAT;
        val->inicialized=false;
        if (sym_add($2, &val) == SYMTAB_DUPLICATE) {
            yyerror("SEMANTIC ERROR: Duplicate variable\n");
            free(val);
            free($2);
        } else {
            printf("BISON: (%s) -> FLOAT.\n", $2);
        }
    }
    | K_STRING ID {
        TokenValue *val = (TokenValue*) malloc(sizeof(TokenValue));
        val->type = TYPE_STRING;
        val->inicialized=false;
        if (sym_add($2, &val) == SYMTAB_DUPLICATE) {
            yyerror("SEMANTIC ERROR: Duplicate variable\n");
            free(val);
            free($2);
        } else {
            printf("BISON: (%s) -> STRING.\n", $2);
        }
    }
    | K_BOOL ID {
        TokenValue *val = (TokenValue*) malloc(sizeof(TokenValue));
        val->type = TYPE_BOOL;
        val->inicialized=false;
        if (sym_add($2, &val) == SYMTAB_DUPLICATE) {
            yyerror("SEMANTIC ERROR: Duplicate variable\n");
            free(val);
            free($2);
        } else {
            printf("BISON: (%s) -> BOOL.\n", $2);
        }
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "LINE %d: Syntax Error - %s\n", yylineno, s);
}

int main(int argc, char **argv) {
    printf("--- Starting Parser (Bison + Flex) ---\n");
    yyparse();
    
    printf("--- End of Parser ---\n");
    return 0;
}