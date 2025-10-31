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
%token <fval> FLOAT_LITERAL 
%token <sval> STRING_LITERAL 
%token <ival> BOOL_LITERAL   
%token ASSIGN              
%%

/* Now we will try to classify everything into a program. Which is defined by a series of lines */
program:
    | program line
    ;

line:
    NUMBER EOL { printf("BISON: NUMBER (%d) + EOL\n", $1); }
    | declaration EOL { printf("BISON: DECLARATION TRACKED.\n"); }
    | assignation EOL { printf("BISON: ASSIGNATION TRACKED.\n"); }
    | EOL        { printf("BISON: EOL\n"); }
    | error EOL  { printf("BISON: Detected error. Jumping to the next line.\n"); yyerrok; }
    ;

declaration:
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

assignation:
    ID ASSIGN NUMBER {
        TokenValue *s;
        if (sym_lookup($1, &s) == SYMTAB_NOT_FOUND) {
            yyerror("SEMANTIC ERROR: Variable not found");
            free($1);
        } else {
            if (s->type != TYPE_INT) {
                yyerror("SEMANTIC ERROR: Uncompatible assignation");
            } else {
                s->value.i_val = $3;
                s->inicialized = true;
                printf("BISON: Assigned %s := %d\n", $1, $3);
            }
        }
    }
    | ID ASSIGN FLOAT_LITERAL {
        TokenValue *s;
        if (sym_lookup($1, &s) == SYMTAB_NOT_FOUND) {
            yyerror("SEMANTIC ERROR: Variable not found");
            free($1);
        } else {
            if (s->type != TYPE_FLOAT) {
                yyerror("SEMANTIC ERROR: Uncompatible assignation");
            } else {
                s->value.f_val = $3;
                s->inicialized = true;
                printf("BISON: Assigned %s := %f\n", $1, $3);
            }
        }
    }
    | ID ASSIGN STRING_LITERAL {
        TokenValue *s;
        if (sym_lookup($1, &s) == SYMTAB_NOT_FOUND) {
            yyerror("SEMANTIC ERROR: Variable not found");
            free($1);
            free($3);
        } else {
            if (s->type != TYPE_STRING) {
                yyerror("SEMANTIC ERROR: Uncompatible assignation");
            } else {
                if (s->inicialized && s->value.s_val) free(s->value.s_val);
                s->value.s_val = $3; 
                s->inicialized = true;
                printf("BISON: Assigned %s := \"%s\"\n", $1, $3);
            }
        }
    }
    | ID ASSIGN BOOL_LITERAL {
        TokenValue *s;
        if (sym_lookup($1, &s) == SYMTAB_NOT_FOUND) {
            yyerror("SEMANTIC ERROR: Variable not found");
            free($1);
        } else {
            if (s->type != TYPE_BOOL) {
                yyerror("SEMANTIC ERROR: Uncompatible assignation");
            } else {
                s->value.b_val = $3; 
                s->inicialized = true;
                printf("BISON: Assigned %s := %s\n", $1, $3 ? "true" : "false");
            }
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