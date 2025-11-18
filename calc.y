%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "value.h"
#include "symtab.h"

/* yylex() is the flex scanner. yyerror() is the fuction Bison will call in case of an error. */
int yylex(void);
void yyerror(const char *s);
extern int yylineno;

void print_result(struct TempValue *res);

char *strdup(const char *s);
%}

%union {
    int ival;
    float fval;
    char *sval;
    int bval;
    struct TempValue *expr;
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

%type <expr> expression
%type <expr> term
%type <expr> atom
%%

/* Now we will try to classify everything into a program. Which is defined by a series of lines */
program:
    | program line
    ;

line:
    expression EOL  { 
        printf("BISON: Result: ");
        print_result($1); 
        free($1); 
    }
    | declaration EOL { printf("BISON: DECLARATION TRACKED.\n"); }
    | assignation EOL { printf("BISON: ASSIGNATION TRACKED.\n"); }
    | EOL        { printf("BISON: EOL\n"); }
    | error EOL  { printf("BISON: Detected error. Jumping to the next line.\n"); yyerrok; }
    ;

expression:
    term { $$ = $1; }
    | expression '+' term {
        TempValue *res1 = $1;
        TempValue *res2 = $3;
        
        if (res1->type == TYPE_INT && res2->type == TYPE_INT) {
            res1->value.i_val = res1->value.i_val + res2->value.i_val;
            free(res2);
            $$ = res1;
        }
        else if (res1->type == TYPE_FLOAT && res2->type == TYPE_FLOAT) {
            res1->value.f_val = res1->value.f_val + res2->value.f_val;
            free(res2);
            $$ = res1;
        }
        else if (res1->type == TYPE_INT && res2->type == TYPE_FLOAT) {
            res1->type = TYPE_FLOAT;
            res1->value.f_val = (float)res1->value.i_val + res2->value.f_val;
            free(res2);
            $$ = res1;
        }
        else if (res1->type == TYPE_FLOAT && res2->type == TYPE_INT) {
            res1->value.f_val = res1->value.f_val + (float)res2->value.i_val;
            free(res2);
            $$ = res1;
        }
        else {
            yyerror("Semanthic error: Uncompatible type for '+'");
            $$ = 0;
        }
    }
    | expression '-' term {
        TempValue *res1 = $1;
        TempValue *res2 = $3;
        if (res1->type == TYPE_INT && res2->type == TYPE_INT) {
            res1->value.i_val = res1->value.i_val - res2->value.i_val;
            free(res2);
            $$ = res1;
        } 
        else if (res1->type == TYPE_FLOAT && res2->type == TYPE_FLOAT) {
            res1->value.f_val = res1->value.f_val - res2->value.f_val;
            free(res2);
            $$ = res1;
        }
        else if (res1->type == TYPE_INT && res2->type == TYPE_FLOAT) {
            res1->type = TYPE_FLOAT;
            res1->value.f_val = (float)res1->value.i_val - res2->value.f_val;
            free(res2);
            $$ = res1;
        }
        else if (res1->type == TYPE_FLOAT && res2->type == TYPE_INT) {
            res1->value.f_val = res1->value.f_val - (float)res2->value.i_val;
            free(res2);
            $$ = res1;
        }
        else {
            yyerror("Semanthic error: Uncompatible type for '-'");
            $$ = 0;
        }
    }
    ;

term:
    atom { $$ = $1; } 
    | term '*' atom {
        TempValue *res1 = $1;
        TempValue *res2 = $3;
        if (res1->type == TYPE_INT && res2->type == TYPE_INT) {
            res1->value.i_val = res1->value.i_val * res2->value.i_val;
            free(res2);
            $$ = res1;
        }
        else if (res1->type == TYPE_FLOAT && res2->type == TYPE_FLOAT) {
            res1->value.f_val = res1->value.f_val * res2->value.f_val;
            free(res2);
            $$ = res1;
        }
        else if (res1->type == TYPE_INT && res2->type == TYPE_FLOAT) {
            res1->type = TYPE_FLOAT;
            res1->value.f_val = (float)res1->value.i_val * res2->value.f_val;
            free(res2);
            $$ = res1;
        }
        else if (res1->type == TYPE_FLOAT && res2->type == TYPE_INT) {
            res1->value.f_val = res1->value.f_val * (float)res2->value.i_val;
            free(res2);
            $$ = res1;
        }
        else {
            yyerror("Semanthic error: Uncompatible type for '*'");
            $$ = 0;
        }
        
    }
    | term '/' atom {
        TempValue *res1 = $1;
        TempValue *res2 = $3;
        if (res1->type == TYPE_INT && res2->type == TYPE_INT) {
            if (res2->value.i_val == 0) {
                yyerror("Semanthic error: Division by 0");
                $$ = 0;
            } else {
                res1->value.i_val = res1->value.i_val / res2->value.i_val;
                $$ = res1;
            }
            free(res2);
        }
        else if (res1->type == TYPE_FLOAT && res2->type == TYPE_FLOAT) {
            if (res2->value.f_val == 0) {
                yyerror("Semanthic error: Division by 0");
                $$ = 0;
            } else {
                res1->value.f_val = res1->value.f_val / res2->value.f_val;
                $$ = res1;
            }
            free(res2);
        }
        else if (res1->type == TYPE_INT && res2->type == TYPE_FLOAT) {
            if (res2->value.f_val == 0) {
                yyerror("Semanthic error: Division by 0");
                $$ = 0;
            } else {
                res1->type = TYPE_FLOAT;
                res1->value.f_val = (float)res1->value.i_val / res2->value.f_val;
                $$ = res1;
            }
            free(res2);
        }
        else if (res1->type == TYPE_FLOAT && res2->type == TYPE_INT) {
            if (res2->value.i_val == 0) {
                yyerror("Semanthic error: Division by 0");
                $$ = 0;
            } else {
                res1->value.f_val = res1->value.f_val / (float)res2->value.i_val;
                $$ = res1;
            }
            free(res2);
        }
        else {
            yyerror("Semanthic error: Uncompatible type for '/'");
            $$ = 0;
        }
        
    }
    ;

atom:
    NUMBER {
        $$ = (TempValue*) malloc(sizeof(TempValue));
        $$->type = TYPE_INT;
        $$->value.i_val = $1;
    }
    | FLOAT_LITERAL {
        $$ = (TempValue*) malloc(sizeof(TempValue));
        $$->type = TYPE_FLOAT;
        $$->value.f_val = $1;
    }
    | ID {
        TokenValue *s;
        $$ = (TempValue*) malloc(sizeof(TempValue)); 
        
        if (sym_lookup($1, &s) == SYMTAB_NOT_FOUND) {
            yyerror("Semanthic error: Undeclared variable.");
            $$->type = TYPE_INT; $$->value.i_val = 0;
        } else if (!s->inicialized) {
            yyerror("Semanthic error: Uninicialized variable");
            $$->type = TYPE_INT; $$->value.i_val = 0;
        } else {
            $$->type = s->type;
            switch (s->type) {
                case TYPE_INT:
                    $$->value.i_val = s->value.i_val;
                    break;
                case TYPE_FLOAT:
                    $$->value.f_val = s->value.f_val;
                    break;
                case TYPE_STRING:
                    /* Para strings, duplicamos memoria */
                    $$->value.s_val = strdup(s->value.s_val);
                    break;
                case TYPE_BOOL:
                    $$->value.b_val = s->value.b_val;
                    break;
                default:
                    break;
            }
        }
        free($1); 
    }
    | '(' expression ')' {
        $$ = $2; 
    }
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

void print_result(struct TempValue *res) {
    if (!res) return;
    switch (res->type) {
        case TYPE_INT:
            printf("%d (TYPE_INT)\n", res->value.i_val);
            break;
        case TYPE_FLOAT:
            printf("%f (TYPE_FLOAT)\n", res->value.f_val);
            break;
        case TYPE_STRING:
            printf("%s (TYPE_STRING)\n", res->value.s_val);
            free(res->value.s_val); /* Liberamos la copia temporal */
            break;
        case TYPE_BOOL:
            printf("%s (TYPE_BOOL)\n", res->value.b_val ? "true" : "false");
            break;
    }
}

void yyerror(const char *s) {
    fprintf(stderr, "LINE %d: Syntax Error - %s\n", yylineno, s);
}

int main(int argc, char **argv) {
    printf("--- Starting Parser (Bison + Flex) ---\n");
    yyparse();
    
    printf("--- End of Parser ---\n");
    return 0;
}