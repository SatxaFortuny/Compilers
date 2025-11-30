%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "value.h"
#include "symtab.h"

/* yylex() is the flex scanner. yyerror() is the fuction Bison will call in case of an error. */
int yylex(void);
void yyerror(const char *s);
extern int yylineno;

void print_result(struct TempValue *res);

char *strdup(const char *s);

struct TempValue* compare(struct TempValue* v1, struct TempValue* v2, int op)
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
%token POWER
%token EQ LE GE NE LT GT AND OR NOT POWER

%type <expr> expression
%type <expr> term
%type <expr> atom
%type <expr> unary
%type <expr> pow
%type <expr> predicate
%%

/* Now we will try to classify everything into a program. Which is defined by a series of lines */
program:
    | program line
    ;

line:
    or_predicate EOL {
        printf("BISON: Result: ");
        print_result($1); 
        free($1);
    }
    | declaration EOL { printf("BISON: DECLARATION TRACKED.\n"); }
    | assignation EOL { printf("BISON: ASSIGNATION TRACKED.\n"); }
    | EOL        { printf("BISON: EOL\n"); }
    | error EOL  { printf("BISON: Detected error. Jumping to the next line.\n"); yyerrok; }
    ;

or_predicate:
    and_predicate { $$ = $1; }
    | or_predicate OR and_predicate {
        struct TempValue *res = $1;
        res->value.b_val = ($1->value.b_val || $3->value.b_val);
        free($3);
        $$ = res;
    }
    ;

and_predicate:
    predicate { $$ = $1; }
    | and_predicate AND predicate {
        struct TempValue *res = $1;
        res->value.b_val = ($1->value.b_val && $3->value.b_val);
        free($3);
        $$ = res;
    }
    ;

predicate:
    expression { $$ = $1; }
    | expression EQ expression { $$ = compare($1, $3, EQ); }
    | expression NE expression { $$ = compare($1, $3, NE); }
    | expression LT expression { $$ = compare($1, $3, LT); }
    | expression LE expression { $$ = compare($1, $3, LE); }
    | expression GT expression { $$ = compare($1, $3, GT); }
    | expression GE expression { $$ = compare($1, $3, GE); }
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
    unary { $$ = $1; } 
    | term '*' unary {
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
    | term '/' unary {
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
    | term '%' unary {
        TempValue *res1 = $1;
        TempValue *res2 = $3;
        if (res1->type == TYPE_INT && res2->type == TYPE_INT) {
            if (res2->value.i_val == 0) {
                 yyerror("Semantic error: Mod by 0");
                 $$ = 0;
            } else {
                 res1->value.i_val = res1->value.i_val % res2->value.i_val;
                 $$ = res1;
            }
            free(res2);
        } else {
            yyerror("Semantic error: Mod requires INTEGER types");
            $$ = 0;
        }
    }
    ;

unary:
    pow { $$ = $1; }
    | '-' unary {
        TempValue *res = $2;
        if (res->type == TYPE_INT) {
            res->value.i_val = -res->value.i_val;
        } else if (res->type == TYPE_FLOAT) {
            res->value.f_val = -res->value.f_val;
        } else {
            yyerror("Semantic error: Invalid type for minus");
        }
        $$ = res;
    }
    | '+' unary { $$ = $2; } 
    ;

pow:
    atom { $$ = $1; }
    | pow POWER atom { 
        TempValue *res1 = $1;
        TempValue *res2 = $3;
        if (res1->type == TYPE_INT && res2->type == TYPE_INT) {
            res1->value.i_val = (int)pow((double)res1->value.i_val, (double)res2->value.i_val);
        } else {
            float val1 = (res1->type == TYPE_INT) ? (float)res1->value.i_val : res1->value.f_val;
            float val2 = (res2->type == TYPE_INT) ? (float)res2->value.i_val : res2->value.f_val;            
            res1->type = TYPE_FLOAT;
            res1->value.f_val = (float)pow((double)val1, (double)val2);
        }
        free(res2);
        $$ = res1;
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
    ID ASSIGN expression { 
        TokenValue *s;
        struct TempValue *res = $3; 

        if (sym_lookup($1, &s) == SYMTAB_NOT_FOUND) {
            yyerror("SEMANTIC ERROR: Variable not found");
        } else {
            if (s->type != res->type) {
                yyerror("SEMANTIC ERROR: Incompatible types in assignment");
                printf("Error detail: Variable is type %d, Value is type %d\n", s->type, res->type);
            } else {
                switch (s->type) {
                    case TYPE_INT:
                        s->value.i_val = res->value.i_val;
                        break;
                    case TYPE_FLOAT:
                        s->value.f_val = res->value.f_val;
                        break;
                    case TYPE_BOOL:
                        s->value.b_val = res->value.b_val;
                        break;
                    case TYPE_STRING:
                        if (s->inicialized && s->value.s_val) {
                            free(s->value.s_val);
                        }
                        s->value.s_val = strdup(res->value.s_val);
                        break;
                }
                s->inicialized = true;
                printf("BISON: Assigned variable '%s'\n", $1);
            }
        }
        free($1);
        if (res->type == TYPE_STRING) {
            free(res->value.s_val);
        }
        free(res);
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

struct TempValue* compare(struct TempValue* v1, struct TempValue* v2, int op) {
    struct TempValue* res = (struct TempValue*) malloc(sizeof(struct TempValue));
    res->type = TYPE_BOOL;
    
    /* 1. Obtenir els valors com a float per poder comparar INT amb FLOAT */
    float val1 = 0.0, val2 = 0.0;
    
    /* Extreure valor 1 */
    if (v1->type == TYPE_INT) val1 = (float)v1->value.i_val;
    else if (v1->type == TYPE_FLOAT) val1 = v1->value.f_val;
    else {
        /* Opcional: Gestionar error si intentes comparar strings o bools amb < > */
        /* Per simplicitat assumim 0 si no és número */
    }

    /* Extreure valor 2 */
    if (v2->type == TYPE_INT) val2 = (float)v2->value.i_val;
    else if (v2->type == TYPE_FLOAT) val2 = v2->value.f_val;
    else {
        /* Idem */
    }

    /* 2. Calcular el resultat */
    int r = 0;
    switch(op) {
        case EQ: r = (val1 == val2); break;
        case NE: r = (val1 != val2); break; /* Has definit el token com NE */
        case LT: r = (val1 < val2); break;
        case LE: r = (val1 <= val2); break;
        case GT: r = (val1 > val2); break;
        case GE: r = (val1 >= val2); break;
    }

    res->value.b_val = r;
    
    /* 3. Neteja de memòria: Els operands v1 i v2 ja no es necessiten */
    free(v1); 
    free(v2);
    
    return res;
}

int main(int argc, char **argv) {
    printf("--- Starting Parser (Bison + Flex) ---\n");
    yyparse();
    
    printf("--- End of Parser ---\n");
    return 0;
}