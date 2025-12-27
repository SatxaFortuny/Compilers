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

extern FILE *yyin;

void print_result(struct TempValue *res);

char *strdup(const char *s);

struct TempValue* compare(struct TempValue* v1, struct TempValue* v2, int op);

struct Token* find_field(struct Token* list, char* name);

struct Token* copy_tokens(struct Token* source);
%}

%union {
    int ival;
    float fval;
    char *sval;
    int bval;
    struct TempValue *expr;
    struct Token *tokens;
}

/* Here what we are doing is defining the tokens that will be given by the Flex scanner. */
%token <ival> NUMBER
%token <sval> ID
%token INT
%token FLOAT
%token STRING
%token BOOL
%token EOL 
%token <fval> FLOAT_LITERAL 
%token <sval> STRING_LITERAL 
%token <ival> BOOL_LITERAL   
%token ASSIGN
%token POWER
%token EQ LE GE NE LT GT AND OR NOT
%token PI E SIN COS TAN LEN SUBSTR
%token STRUCT

%type <expr> or_predicate
%type <expr> and_predicate
%type <expr> not_predicate
%type <expr> predicate
%type <expr> expression
%type <expr> term
%type <expr> atom
%type <expr> unary
%type <expr> pow

%type <tokens> token_list token_decl
%type <tokens> id_list

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
    not_predicate { $$ = $1; }
    | and_predicate AND predicate {
        struct TempValue *res = $1;
        res->value.b_val = ($1->value.b_val && $3->value.b_val);
        free($3);
        $$ = res;
    }
    ;

not_predicate:
    predicate { $$ = $1; }
    | NOT not_predicate {
        struct TempValue *res = $2;
        if (res->type != TYPE_BOOL) {
            yyerror("Semantic Error: NOT requires boolean operand");
        } else {
            res->value.b_val = !res->value.b_val;
        }
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

token_list:
    token_decl { 
        $$ = $1;
    }
    | token_decl token_list {
        $1->next = $2; 
        $$ = $1; 
    }
    ;

id_list:
    ID {
        /* Creamos un nodo solo para guardar el nombre */
        struct Token *t = (struct Token*) malloc(sizeof(struct Token));
        t->name = $1; 
        t->next = NULL;
        $$ = t;
    }
    | id_list ',' ID {
        /* Añadimos el nuevo ID al final o principio de la lista */
        struct Token *t = (struct Token*) malloc(sizeof(struct Token));
        t->name = $3;
        t->next = $1; /* Lo ponemos al principio para ir rápido (orden inverso, no importa) */
        $$ = t;
    }
    ;

/* Regla para crear un solo campo (int x;) */
token_decl:
    INT ID ';' {
        struct Token *t = (struct Token*) malloc(sizeof(struct Token));
        t->name = $2;      /* Guardamos el nombre "x" */
        t->type = TYPE_INT;
        t->next = NULL;
        $$ = t;            /* Subimos el puntero */
    }
    | FLOAT ID ';' {
        struct Token *t = (struct Token*) malloc(sizeof(struct Token));
        t->name = $2;
        t->type = TYPE_FLOAT;
        t->next = NULL;
        $$ = t;
    }
    | STRING ID ';' {
        struct Token *t = (struct Token*) malloc(sizeof(struct Token));
        t->name = $2;
        t->type = TYPE_STRING;
        t->next = NULL;
        $$ = t;
    }
    | BOOL ID ';' {
        struct Token *t = (struct Token*) malloc(sizeof(struct Token));
        t->name = $2;
        t->type = TYPE_BOOL;
        t->next = NULL;
        $$ = t;
    }
    ;

expression:
    term { $$ = $1; }
    | expression '+' term {
        TempValue *res1 = $1;
        TempValue *res2 = $3;

        if (res1->type == TYPE_STRING || res2->type == TYPE_STRING) {
            char buffer1[100], buffer2[100];
            char *str1, *str2;

            /* Convertir primer operando a texto */
            if (res1->type == TYPE_STRING) {
                str1 = res1->value.s_val;
            } else if (res1->type == TYPE_INT) {
                sprintf(buffer1, "%d", res1->value.i_val);
                str1 = buffer1;
            } else if (res1->type == TYPE_FLOAT) {
                sprintf(buffer1, "%g", res1->value.f_val);
                str1 = buffer1;
            } else { /* BOOL */
                str1 = res1->value.b_val ? "true" : "false";
            }

            /* Convertir segundo operando a texto */
            if (res2->type == TYPE_STRING) {
                str2 = res2->value.s_val;
            } else if (res2->type == TYPE_INT) {
                sprintf(buffer2, "%d", res2->value.i_val);
                str2 = buffer2;
            } else if (res2->type == TYPE_FLOAT) {
                sprintf(buffer2, "%g", res2->value.f_val);
                str2 = buffer2;
            } else { /* BOOL */
                str2 = res2->value.b_val ? "true" : "false";
            }

            /* Reservar memoria y concatenar */
            char *resultStr = (char*)malloc(strlen(str1) + strlen(str2) + 1);
            strcpy(resultStr, str1);
            strcat(resultStr, str2);

            /* Liberar operandos viejos */
            if (res1->type == TYPE_STRING) free(res1->value.s_val);
            if (res2->type == TYPE_STRING) free(res2->value.s_val);
            free(res2); // res1 se reutiliza

            res1->type = TYPE_STRING;
            res1->value.s_val = resultStr;
            $$ = res1;
        }
        else if (res1->type == TYPE_INT && res2->type == TYPE_INT) {
            res1->value.i_val = res1->value.i_val + res2->value.i_val;
            free(res2);
            $$ = res1;
        }
        else {
             float v1 = (res1->type == TYPE_INT) ? (float)res1->value.i_val : res1->value.f_val;
             float v2 = (res2->type == TYPE_INT) ? (float)res2->value.i_val : res2->value.f_val;
             
             res1->type = TYPE_FLOAT;
             res1->value.f_val = v1 + v2;
             free(res2);
             $$ = res1;
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
    | BOOL_LITERAL {
        $$ = (struct TempValue*) malloc(sizeof(struct TempValue));
        $$->type = TYPE_BOOL;
        $$->value.b_val = $1;
    }
    | STRING_LITERAL {
        $$ = (struct TempValue*) malloc(sizeof(struct TempValue));
        $$->type = TYPE_STRING;
        /* Flex ya hizo el strdup, así que nos lo quedamos */
        $$->value.s_val = $1; 
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
    | PI {
        $$ = (struct TempValue*) malloc(sizeof(struct TempValue));
        $$->type = TYPE_FLOAT;
        $$->value.f_val = 3.14159265358979323846;
    }
    | E {
        $$ = (struct TempValue*) malloc(sizeof(struct TempValue));
        $$->type = TYPE_FLOAT;
        $$->value.f_val = 2.71828182845904523536;
    }
    | SIN '(' expression ')' {
        struct TempValue *arg = $3;
        float val = 0.0;
        if (arg->type == TYPE_INT) val = (float)arg->value.i_val;
        else if (arg->type == TYPE_FLOAT) val = arg->value.f_val;
        else {
            yyerror("Semantic Error: sin() requires a number");
        }
        
        arg->type = TYPE_FLOAT;
        arg->value.f_val = sin(val);
        $$ = arg; 
    }
    | COS '(' expression ')' {
        struct TempValue *arg = $3;
        float val = 0.0;
        if (arg->type == TYPE_INT) val = (float)arg->value.i_val;
        else if (arg->type == TYPE_FLOAT) val = arg->value.f_val;
        else {
            yyerror("Semantic Error: cos() requires a number");
        }
        
        arg->type = TYPE_FLOAT;
        arg->value.f_val = cos(val); 
        $$ = arg; 
    }
    | TAN '(' expression ')' {
        struct TempValue *arg = $3;
        float val = 0.0;
        if (arg->type == TYPE_INT) val = (float)arg->value.i_val;
        else if (arg->type == TYPE_FLOAT) val = arg->value.f_val;
        else {
            yyerror("Semantic Error: tan() requires a number");
        }
        
        arg->type = TYPE_FLOAT;
        arg->value.f_val = tan(val);
        $$ = arg; 
    }
    | LEN '(' expression ')' {
        struct TempValue *arg = $3;
        if (arg->type != TYPE_STRING) {
            yyerror("Semantic Error: LEN() requires a string");
            arg->type = TYPE_INT; 
            arg->value.i_val = 0;
        } else {
            int len = strlen(arg->value.s_val);
            free(arg->value.s_val); 
            arg->type = TYPE_INT;
            arg->value.i_val = len;
        }
        $$ = arg;
    }
    | SUBSTR '(' expression ';' expression ';' expression ')' {
        struct TempValue *str = $3;
        struct TempValue *start = $5;
        struct TempValue *len = $7;
        if (str->type != TYPE_STRING || start->type != TYPE_INT || len->type != TYPE_INT) {
             yyerror("Semantic Error: SUBSTR expects (string; int; int)");
             $$ = str; 
        } else {
             int s_idx = start->value.i_val;
             int l_val = len->value.i_val;
             int max_len = strlen(str->value.s_val);
             if (s_idx < 0) s_idx = 0;
             if (s_idx > max_len) s_idx = max_len;
             if (l_val < 0) l_val = 0;
             if (s_idx + l_val > max_len) l_val = max_len - s_idx;
             char *sub = (char*) malloc(l_val + 1);
             strncpy(sub, str->value.s_val + s_idx, l_val);
             sub[l_val] = '\0'; // Terminador nulo

             free(str->value.s_val);
             str->value.s_val = sub;
             $$ = str;
        }
        free(start);
        free(len);
    }
    /* Acceso a miembro: ID . ID */
    | ID '.' ID {
        TokenValue *s;
        $$ = (struct TempValue*) malloc(sizeof(struct TempValue));

        /* 1. Buscamos la variable principal (el struct) */
        if (sym_lookup($1, &s) == SYMTAB_NOT_FOUND) {
            yyerror("Semantic Error: Struct variable not found");
            $$->type = TYPE_INT; $$->value.i_val = 0;
        } else if (s->type != TYPE_STRUCT) {
            yyerror("Semantic Error: Variable is not a struct");
            $$->type = TYPE_INT; $$->value.i_val = 0;
        } else {
            /* 2. Buscamos el campo dentro de su lista */
            struct Token *field = find_field(s->value.tokens, $3);
            
            if (field == NULL) {
                yyerror("Semantic Error: Field not found in struct");
                $$->type = TYPE_INT; $$->value.i_val = 0;
            } else {
                /* 3. ¡Éxito! Copiamos tipo y valor al resultado temporal */
                $$->type = field->type;
                
                switch(field->type) {
                    case TYPE_INT: $$->value.i_val = field->value.i_val; break;
                    case TYPE_FLOAT: $$->value.f_val = field->value.f_val; break;
                    case TYPE_BOOL: $$->value.b_val = field->value.b_val; break;
                    case TYPE_STRING: $$->value.s_val = strdup(field->value.s_val); break;
                    default: break;
                }
            }
        }
        free($1); free($3); /* Limpieza de los nombres */
    }
    | '(' or_predicate ')' {
        $$ = $2; 
    }
    ;

declaration:
    INT ID {
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
    | FLOAT ID {
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
    | STRING ID {
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
    | BOOL ID {
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
    /* Regla MODIFICADA para soportar múltiples variables */
    | STRUCT ID '{' token_list '}' id_list {
        /* $2: Nombre del tipo (ej: "Punto") */
        /* $4: Plantilla de campos (x, y) */
        /* $6: Lista de variables (p1, p2) */
        
        printf("BISON: Defining struct type '%s'\n", $2);
        
        /* Recorremos la lista de variables (p1, p2...) */
        struct Token *current_var = $6;
        while (current_var != NULL) {
            
            /* 1. Crear la variable en memoria */
            TokenValue *val = (TokenValue*) malloc(sizeof(TokenValue));
            val->type = TYPE_STRUCT;
            val->inicialized = true;
            
            /* 2. ¡IMPORTANTE! Darle su propia COPIA de los campos */
            val->value.tokens = copy_tokens($4); 
            
            /* 3. Registrar en la Tabla de Símbolos */
            if (sym_add(current_var->name, &val) == SYMTAB_DUPLICATE) {
                yyerror("SEMANTIC ERROR: Duplicate variable in struct declaration");
                free(val); /* (Deberíamos liberar también la lista copiada) */
                free(current_var->name);
            } else {
                printf("BISON: Struct instance '%s' created.\n", current_var->name);
            }
            
            /* Avanzar al siguiente ID (p2...) y limpiar el nodo auxiliar */
            struct Token *temp = current_var;
            current_var = current_var->next;
            free(temp); /* Liberamos el nodo de la lista de IDs */
        }
        
        /* Limpieza final */
        free($2); /* Nombre del tipo */
        /* Deberíamos liberar la plantilla original $4, ya que hemos hecho copias */
        /* (Te dejo esa limpieza como opcional para no complicar más) */
    }
;

assignation:
    ID ASSIGN or_predicate { 
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
                    default:
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
    /* Asignación a miembro: ID . ID := valor */
    | ID '.' ID ASSIGN or_predicate {
        TokenValue *s;
        struct TempValue *res = $5; /* El valor calculado (derecha) */

        /* 1. Buscar Struct */
        if (sym_lookup($1, &s) == SYMTAB_NOT_FOUND) {
            yyerror("Error: Struct variable not found");
        } else if (s->type != TYPE_STRUCT) {
            yyerror("Error: Variable is not a struct");
        } else {
            /* 2. Buscar Campo */
            struct Token *field = find_field(s->value.tokens, $3);
            
            if (field == NULL) {
                yyerror("Error: Field not found in struct");
            } else {
                /* 3. Chequear compatibilidad de tipos */
                if (field->type != res->type) {
                    yyerror("Error: Type mismatch in field assignment");
                } else {
                    /* 4. Asignar el valor directamente al campo */
                    switch(field->type) {
                        case TYPE_INT:   field->value.i_val = res->value.i_val; break;
                        case TYPE_FLOAT: field->value.f_val = res->value.f_val; break;
                        case TYPE_BOOL:  field->value.b_val = res->value.b_val; break;
                        case TYPE_STRING: 
                            /* (Aquí podrías hacer free si ya tenía valor, pero simplificamos) */
                            field->value.s_val = strdup(res->value.s_val); 
                            break;
                        default: break;
                    }
                    printf("BISON: Assigned field %s.%s\n", $1, $3);
                }
            }
        }
        free($1); free($3); 
        /* free(res); (Depende de si necesitas liberar el TempValue aquí o lo hace Bison) */
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
        default:
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

struct Token* find_field(struct Token* list, char* name) {
    struct Token *current = list;
    while (current != NULL) {
        /* strcmp devuelve 0 si son iguales */
        if (strcmp(current->name, name) == 0) {
            return current; /* ¡Encontrado! */
        }
        current = current->next;
    }
    return NULL; /* No existe ese campo */
}

/* Copia profunda de la lista de campos para que cada variable tenga la suya propia */
struct Token* copy_tokens(struct Token* source) {
    if (source == NULL) return NULL;
    
    struct Token *new_node = (struct Token*) malloc(sizeof(struct Token));
    /* Copiamos los datos básicos */
    new_node->name = strdup(source->name);
    new_node->type = source->type;
    new_node->value = source->value; /* Copia la unión (inicializada a 0/NULL) */
    
    /* Recursión para copiar el resto de la lista */
    new_node->next = copy_tokens(source->next);
    
    return new_node;
}

int main(int argc, char **argv) {
    
    /* 1. Comprobamos que nos pasen 2 argumentos (entrada y salida) */
    if (argc != 3) {
        fprintf(stderr, "Uso correcto: %s <fichero_entrada> <fichero_salida>\n", argv[0]);
        return 1;
    }

    /* 2. Abrimos el archivo de ENTRADA en modo lectura ("r") */
    FILE *input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "Error: No se pudo abrir el archivo de entrada '%s'\n", argv[1]);
        return 1;
    }

    /* 3. Le decimos a Flex que lea de este archivo en vez de la consola */
    yyin = input;

    /* 4. Redirigimos la SALIDA estándar (stdout) al archivo de salida */
    /* De esta forma, todos tus printf() irán al archivo automáticamente */
    if (freopen(argv[2], "w", stdout) == NULL) {
        fprintf(stderr, "Error: No se pudo crear el archivo de salida '%s'\n", argv[2]);
        fclose(input);
        return 1;
    }

    /* 5. (Opcional) Mensaje de inicio para el log de errores (stderr) */
    fprintf(stderr, "--- Iniciando Compilacion ---\n");
    fprintf(stderr, "Entrada: %s\n", argv[1]);
    fprintf(stderr, "Salida:  %s\n", argv[2]);

    /* 6. Ejecutamos el parser */
    yyparse();

    /* 7. Cerramos el archivo de entrada (stdout se cierra solo al terminar) */
    fclose(input);
    
    fprintf(stderr, "--- Fin de la Compilacion ---\n");
    return 0;
}