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

extern FILE *yyin;

char *strdup(const char *s);

int global_offset = 25, temp_counter = 1, instruction_line = 1;

Type current_type;

char* newTemp(void);
int get_current_line(void);
void emit(char *op, char *arg1, char *arg2, char *dest);
void emit_unary(char *op, char *arg1, char *dest);
void emit_move(char *src, char *dest);
void emit_goto_line(int line);
void emit_if_goto(char *cond_var, int line);
void emit_array_load(char *arr_name, char *index, char *dest);
void emit_array_store(char *arr_name, char *index, char *src);
%}

%union {
    int ival;
    float fval;
    char *sval;
    struct TempValue *expr;
}

/* Here what we are doing is defining the tokens that will be given by the Flex scanner. */
%token <ival> NUMBER
%token <sval> ID
%token INT
%token FLOAT
%token EOL 
%token <fval> FLOAT_LITERAL   
%token ASSIGN
%token POWER
%token REPEAT DO DONE

%type <expr> expression
%type <expr> term
%type <expr> atom
%type <expr> unary
%type <expr> pow
%type <expr> loop_header

%%

/* Now we will try to classify everything into a program. Which is defined by a series of lines */
program: stmt_list ;

stmt_list:
    | stmt_list line
    ;

line:
    stmt EOL 
    | EOL          { printf("BISON: EOL\n"); }
    | error EOL    { printf("BISON: Error, next line.\n"); yyerrok; }
    ;

stmt:
    expression { 
        emit("PARAM", $1->addr, NULL, NULL);
        if ($1->type == TYPE_INT) emit("CALL", "PUTI", "1", NULL);
        else emit("CALL", "PUTF", "1", NULL);
    }
    | declaration  { /* Ja genera el seu codi dins la regla */ }
    | assignation  { /* Ja genera el seu codi dins la regla */ }
    | iteration    { /* La nova regla per bucles */ }
    ;

iteration:
    loop_header stmt_list DONE {
        /* Aquí recuperem la info del loop_header ($1) */
        int start_line = $1->type;
        char *counter = $1->addr;

        /* 1. Decrementem el comptador: cnt := cnt - 1 */
        emit("SUBI", counter, "1", counter);

        /* 2. Salt condicional: IF cnt > 0 GOTO start */
        emit_if_goto(counter, start_line);
        
        /* Neteja */
        free($1);
    }
    ;

/* Regla auxiliar per preparar el bucle */
/* Retorna un TempValue on: type = Línia d'inici, addr = Nom comptador */
loop_header:
    REPEAT expression DO {
        $$ = (struct TempValue*) malloc(sizeof(struct TempValue));
        
        if ($2->type != TYPE_INT) {
            yyerror("Error: El comptador del REPEAT ha de ser enter");
        }

        /* 1. Creem el comptador temporal */
        char *counter = newTemp();
        emit_move($2->addr, counter); /* $t_cnt := expressió */

        /* 2. Guardem la línia actual com a INICI del bucle */
        /* Aquesta és la línia on saltarem per repetir */
        int start_line = get_current_line();

        /* 3. Empaquetem la info per passar-la al DONE */
        $$->type = start_line;   /* TRUC: Guardem l'enter a 'type' */
        $$->addr = counter;      /* Guardem el nom del comptador */
        
        /* Nota: Amb aquesta estructura (Post-Check), el bucle s'executa 
           almenys 1 vegada. Per fer-ho exacte caldrien etiquetes alfanumèriques. */
    }
    ;

expression:
    term { $$ = $1; }
    | expression '+' term {
        /* Reservem resultat */
        $$ = (struct TempValue*) malloc(sizeof(struct TempValue));
        if ($1->is_const && $3->is_const) {
            $$->is_const = 1;
            char buf[30];

            if ($1->type == TYPE_INT && $3->type == TYPE_INT) {
                $$->type = TYPE_INT;
                $$->val = $1->val + $3->val;
                sprintf(buf, "%d", (int)$$->val);
            } else {
                $$->type = TYPE_FLOAT;
                $$->val = $1->val + $3->val;
                sprintf(buf, "%.5f", $$->val);
            }
            $$->addr = strdup(buf);
            /* NO EMETEM C3A! */
        } 
        /* CAS NORMAL: Generem Codi */
        else {
            $$->is_const = 0;
            /* CAS 1: INT + INT */
            if ($1->type == TYPE_INT && $3->type == TYPE_INT) {
                $$->type = TYPE_INT;
                $$->addr = newTemp(); /* Demanem temporal: $t1 */
                emit("ADDI", $1->addr, $3->addr, $$->addr); /* $t1 := a ADDI 5 */
            }
            /* CAS 2: FLOAT + FLOAT */
            else if ($1->type == TYPE_FLOAT && $3->type == TYPE_FLOAT) {
                $$->type = TYPE_FLOAT;
                $$->addr = newTemp();
                emit("ADDF", $1->addr, $3->addr, $$->addr);
            }
            /* CAS 3: INT + FLOAT (Conversió del primer) */
            else if ($1->type == TYPE_INT && $3->type == TYPE_FLOAT) {
                $$->type = TYPE_FLOAT;
                char *t_conv = newTemp(); /* Temporal per la conversió */
                
                emit_unary("I2F", $1->addr, t_conv); /* $t1 := I2F var_int */
                
                $$->addr = newTemp(); /* Temporal pel resultat final */
                emit("ADDF", t_conv, $3->addr, $$->addr); /* $t2 := $t1 ADDF var_float */
            }
            /* CAS 4: FLOAT + INT (Conversió del segon) */
            else if ($1->type == TYPE_FLOAT && $3->type == TYPE_INT) {
                $$->type = TYPE_FLOAT;
                char *t_conv = newTemp();
                
                emit_unary("I2F", $3->addr, t_conv);
                
                $$->addr = newTemp();
                emit("ADDF", $1->addr, t_conv, $$->addr);
            }
        }
    }
    | expression '-' term {
        $$ = (struct TempValue*) malloc(sizeof(struct TempValue));
        
        if ($1->is_const && $3->is_const) {
            $$->is_const = 1;
            char buf[30];
            if ($1->type == TYPE_INT && $3->type == TYPE_INT) {
                $$->type = TYPE_INT;
                $$->val = $1->val - $3->val; /* RESTA */
                sprintf(buf, "%d", (int)$$->val);
            } else {
                $$->type = TYPE_FLOAT;
                $$->val = $1->val - $3->val; /* RESTA */
                sprintf(buf, "%.5f", $$->val);
            }
            $$->addr = strdup(buf);
        } else {
            $$->is_const = 0;
            if ($1->type == TYPE_INT && $3->type == TYPE_INT) {
                $$->type = TYPE_INT; $$->addr = newTemp();
                emit("SUBI", $1->addr, $3->addr, $$->addr);
            } else if ($1->type == TYPE_FLOAT && $3->type == TYPE_FLOAT) {
                $$->type = TYPE_FLOAT; $$->addr = newTemp();
                emit("SUBF", $1->addr, $3->addr, $$->addr);
            } else {
                $$->type = TYPE_FLOAT; $$->addr = newTemp();
                char *t = newTemp();
                if ($1->type == TYPE_INT) { emit_unary("I2F", $1->addr, t); emit("SUBF", t, $3->addr, $$->addr); }
                else { emit_unary("I2F", $3->addr, t); emit("SUBF", $1->addr, t, $$->addr); }
            }
        }
    }
    ;

term:
    unary { $$ = $1; } 
    | term '*' unary {
        $$ = (struct TempValue*) malloc(sizeof(struct TempValue));
        
        if ($1->is_const && $3->is_const) {
            $$->is_const = 1;
            char buf[30];
            if ($1->type == TYPE_INT && $3->type == TYPE_INT) {
                $$->type = TYPE_INT;
                $$->val = $1->val * $3->val; /* MULT */
                sprintf(buf, "%d", (int)$$->val);
            } else {
                $$->type = TYPE_FLOAT;
                $$->val = $1->val * $3->val; /* MULT */
                sprintf(buf, "%.5f", $$->val);
            }
            $$->addr = strdup(buf);
        } else {
            $$->is_const = 0;
            if ($1->type == TYPE_INT && $3->type == TYPE_INT) {
                $$->type = TYPE_INT; $$->addr = newTemp();
                emit("MULI", $1->addr, $3->addr, $$->addr);
            } else if ($1->type == TYPE_FLOAT && $3->type == TYPE_FLOAT) {
                $$->type = TYPE_FLOAT; $$->addr = newTemp();
                emit("MULF", $1->addr, $3->addr, $$->addr);
            } else {
                $$->type = TYPE_FLOAT; $$->addr = newTemp();
                char *t = newTemp();
                if ($1->type == TYPE_INT) { emit_unary("I2F", $1->addr, t); emit("MULF", t, $3->addr, $$->addr); }
                else { emit_unary("I2F", $3->addr, t); emit("MULF", $1->addr, t, $$->addr); }
            }
        }
    }
    | term '/' unary {
        $$ = (struct TempValue*) malloc(sizeof(struct TempValue));
        
        if ($1->is_const && $3->is_const) {
            $$->is_const = 1;
            char buf[30];
            /* Nota: Aquí assumim que no divideixes per 0 */
            if ($1->type == TYPE_INT && $3->type == TYPE_INT) {
                $$->type = TYPE_INT;
                $$->val = $1->val / $3->val; /* DIV */
                sprintf(buf, "%d", (int)$$->val);
            } else {
                $$->type = TYPE_FLOAT;
                $$->val = $1->val / $3->val; /* DIV */
                sprintf(buf, "%.5f", $$->val);
            }
            $$->addr = strdup(buf);
        } else {
            $$->is_const = 0;
            if ($1->type == TYPE_INT && $3->type == TYPE_INT) {
                $$->type = TYPE_INT; $$->addr = newTemp();
                emit("DIVI", $1->addr, $3->addr, $$->addr);
            } else if ($1->type == TYPE_FLOAT && $3->type == TYPE_FLOAT) {
                $$->type = TYPE_FLOAT; $$->addr = newTemp();
                emit("DIVF", $1->addr, $3->addr, $$->addr);
            } else {
                $$->type = TYPE_FLOAT; $$->addr = newTemp();
                char *t = newTemp();
                if ($1->type == TYPE_INT) { emit_unary("I2F", $1->addr, t); emit("DIVF", t, $3->addr, $$->addr); }
                else { emit_unary("I2F", $3->addr, t); emit("DIVF", $1->addr, t, $$->addr); }
            }
        }
    }
    | term '%' unary {
        $$ = (struct TempValue*) malloc(sizeof(struct TempValue));

        /* INT % INT */
        if ($1->type == TYPE_INT && $3->type == TYPE_INT) {
            $$->type = TYPE_INT;
            $$->addr = newTemp();
            emit("MODI", $1->addr, $3->addr, $$->addr); 
        } else {
            yyerror("Error Semàntic: L'operació mòdul (%) només admet enters.");
            $$->type = TYPE_INT; 
            $$->addr = strdup("0");
        }
    }
    ;

unary:
    pow { $$ = $1; }
    | '-' unary {
        $$ = (struct TempValue*) malloc(sizeof(struct TempValue));
        
        /* OPTIMITZACIÓ: Si l'operand és constant (ex: "5"), el resultat és constant (ex: "-5") */
        if ($2->is_const) {
            $$->is_const = 1;
            $$->type = $2->type;
            $$->val = -($2->val); /* Calculem el negatiu aquí */
            
            char buf[30];
            if ($$->type == TYPE_INT) sprintf(buf, "%d", (int)$$->val);
            else                      sprintf(buf, "%.5f", $$->val);
            $$->addr = strdup(buf);
        } 
        /* CAS NORMAL */
        else {
            $$->is_const = 0;
            $$->type = $2->type; 
            $$->addr = newTemp();
            if ($2->type == TYPE_INT) emit_unary("CHSI", $2->addr, $$->addr);
            else                      emit_unary("CHSF", $2->addr, $$->addr);
        }
    }
    | '+' unary { 
        $$ = $2; /* El + unari no fa res (+5 és 5) */
    } 
    ;

pow:
    atom { $$ = $1; }
    | atom POWER pow {
        /* $1 és la BASE, $3 és l'EXPONENT */
        
        $$ = (struct TempValue*) malloc(sizeof(struct TempValue));
        
        /* 1. Comprovació de tipus (Exponent ha de ser ENTER) */
        if ($3->type != TYPE_INT) {
            yyerror("Error Semàntic: L'exponent ha de ser enter.");
            /* Recuperació d'errors */
            $$->type = TYPE_INT;
            $$->addr = strdup("1");
        } else {
            /* 2. Inicialització de variables */
            
            /* RESULTAT ($$): Comença valent 1 */
            $$->type = $1->type; /* El resultat tindrà el tipus de la base */
            $$->addr = newTemp();
            if ($$->type == TYPE_INT) emit_move("1", $$->addr);
            else                      emit_move("1.0", $$->addr);

            /* COMPTADOR (t_cnt): Copiem l'exponent */
            char *t_cnt = newTemp();
            emit_move($3->addr, t_cnt);

            /* 3. Gestió de Salts i Línies */
            
            /* Guardem on comença el bucle (per tornar-hi després) */
            /* +1 perquè la línia actual serà el GOTO d'entrada que escriurem ara */
            int linia_inici_bucle = get_current_line() + 1;
            
            /* Saltem a la comprovació (Salt endavant) */
            /* Saltem 2 instruccions: la multiplicació i la resta */
            emit_goto_line(get_current_line() + 3);

            /* --- COS DEL BUCLE (Aquí és on cau linia_inici_bucle) --- */
            
            /* A. Multiplicació: res = res * base */
            if ($$->type == TYPE_INT) {
                emit("MULI", $$->addr, $1->addr, $$->addr);
            } else {
                emit("MULF", $$->addr, $1->addr, $$->addr);
            }

            /* B. Decrement: cnt = cnt - 1 */
            emit("SUBI", t_cnt, "1", t_cnt);

            /* --- COMPROVACIÓ (Aquí és on cau el GOTO inicial) --- */
            
            /* Si el comptador encara és > 0, tornem a dalt */
            emit_if_goto(t_cnt, linia_inici_bucle);
        }
        
        /* Neteja (Opcional) */
        /* free($1); free($3); */
    }
;

atom:
    NUMBER {
        /* 1. Reservem espai pel paquet d'informació que pujarà */
        $$ = (struct TempValue*) malloc(sizeof(struct TempValue));
        $$->type = TYPE_INT;
        
        /* 2. Convertim el número enter a text ("5") */
        char buffer[20];
        sprintf(buffer, "%d", $1);
        $$->addr = strdup(buffer);
        $$->is_const = 1; 
        $$->val = (float)$1;
    }
    | FLOAT_LITERAL {
        $$ = (struct TempValue*) malloc(sizeof(struct TempValue));
        $$->type = TYPE_FLOAT;
        
        /* Convertim el float a text ("3.14") */
        char buffer[30];
        sprintf(buffer, "%.5f", $1); 
        $$->addr = strdup(buffer);
        $$->is_const = 1;
        $$->val = $1;
    }
    | ID {
        TokenValue *s;
        $$ = (struct TempValue*) malloc(sizeof(struct TempValue));
        
        /* 3. Mirem si la variable existeix a la taula */
        if (sym_lookup($1, &s) == SYMTAB_NOT_FOUND) {
            yyerror("Error: Variable no declarada");
            /* Recuperació d'errors: ens inventem un valor segur */
            $$->type = TYPE_INT;
            $$->addr = strdup("0"); 
        } else {
            /* Tot bé: copiem el tipus i el NOM de la variable ("x") */
            $$->type = s->type;
            $$->addr = strdup(s->name); 
            
            /* TODO: Més endavant aquí mirarem si és un Array */
        }
        $$->is_const = 0;
        free($1); /* Ja no necessitem el text cru del Flex */
    }
    | ID '[' expression ']' {
        TokenValue *s;
        $$ = (struct TempValue*) malloc(sizeof(struct TempValue));
        
        /* 1. Comprovar que existeix */
        if (sym_lookup($1, &s) == SYMTAB_NOT_FOUND) {
            yyerror("Error: Array no declarat");
            $$->type = TYPE_INT; $$->addr = strdup("0");
        } 
        /* 2. Comprovar que és realment un array (size > 1) */
        else if (s->size == 1) {
            yyerror("Error Semàntic: La variable no és un array.");
            $$->type = TYPE_INT; $$->addr = strdup("0");
        }
        /* 3. Comprovar que l'índex és enter */
        else if ($3->type != TYPE_INT) {
            yyerror("Error Semàntic: L'índex ha de ser enter.");
            $$->type = TYPE_INT; $$->addr = strdup("0");
        }
        else {
            /* 4. Generar codi */
            $$->type = s->type;      /* El tipus del resultat és el de l'array */
            $$->addr = newTemp();    /* Nou temporal pel resultat */
            
            /* Generem: $t1 := nom_array[index_addr] */
            emit_array_load(s->name, $3->addr, $$->addr);
        }
        $$->is_const = 0;
        free($1);
        /* free($3); */
    }
    | '(' expression ')' {
        $$ = $2; /* Els parèntesis només passen la info amunt */
    }
    ;

declaration:
    type_specifier var_list
    ;

/* Detectem el tipus i el guardem a la variable global */
type_specifier:
    INT   { current_type = TYPE_INT; }
    | FLOAT { current_type = TYPE_FLOAT; }
    ;

/* Llista recursiva: "item" o "llista, item" */
var_list:
    var_item
    | var_list ',' var_item
    ;

/* L'ítem individual (pot ser simple o array) */
var_item:
    /* VARIABLE SIMPLE: x */
    ID {
        TokenValue *dummy;
        /* Utilitzem 'current_type' en lloc de TYPE_INT/FLOAT directament */
        
        if (sym_lookup($1, &dummy) != SYMTAB_NOT_FOUND) {
            yyerror("Error: Variable ja declarada.");
        } else {
            TokenValue *val = (TokenValue*) malloc(sizeof(TokenValue));
            val->type = current_type; /* <--- Aquí està la màgia */
            val->size = 1;
            val->name = strdup($1);
            val->offset = global_offset;
            global_offset += 1;
            
            sym_add($1, &val);
        }
        free($1);
    }
    /* ARRAY: x[10] */
    | ID '[' NUMBER ']' {
        TokenValue *dummy;
        
        if (sym_lookup($1, &dummy) != SYMTAB_NOT_FOUND) {
            yyerror("Error: Variable ja declarada.");
        } else {
            TokenValue *val = (TokenValue*) malloc(sizeof(TokenValue));
            val->type = current_type; /* <--- Màgia */
            val->size = $3;           /* La mida és el número */
            val->name = strdup($1);
            val->offset = global_offset;
            global_offset += val->size;
            
            sym_add($1, &val);
        }
        free($1);
    }
    ;

assignation:
    ID ASSIGN expression { 
        TokenValue *s;
        struct TempValue *res = $3; 

        /* 1. Busquem la variable */
        if (sym_lookup($1, &s) == SYMTAB_NOT_FOUND) {
            yyerror("Error: Variable no declarada");
        } else {
            /* 2. Comprovem tipus */
            
            /* INT := INT o FLOAT := FLOAT */
            if (s->type == res->type) {
                emit_move(res->addr, s->name);
            }
            /* FLOAT := INT (Promoció) */
            else if (s->type == TYPE_FLOAT && res->type == TYPE_INT) {
                char *temp = newTemp();
                emit_unary("I2F", res->addr, temp);
                emit_move(temp, s->name);
            }
            /* INT := FLOAT (Error) */
            else if (s->type == TYPE_INT && res->type == TYPE_FLOAT) {
                yyerror("Error: No es pot assignar Float a Int");
            }
        }
        free($1);
        /* free(res); */
    }
    | ID '[' expression ']' ASSIGN expression {
        TokenValue *s;
        struct TempValue *idx = $3; /* L'índex (dins els corxets) */
        struct TempValue *val = $6; /* El valor a guardar (dreta) */

        if (sym_lookup($1, &s) == SYMTAB_NOT_FOUND) {
            yyerror("Error: Array no declarat");
        }
        else if (s->size == 1) {
            yyerror("Error: La variable no és un array");
        }
        else if (idx->type != TYPE_INT) {
            yyerror("Error: L'índex ha de ser enter");
        }
        else {
            /* Comprovar tipus i fer CAST si cal (igual que assignació simple) */
            char *val_addr = val->addr;
            
            /* Si array és FLOAT i valor és INT -> I2F */
            if (s->type == TYPE_FLOAT && val->type == TYPE_INT) {
                char *temp = newTemp();
                emit_unary("I2F", val->addr, temp);
                val_addr = temp;
            }
            /* Si array és INT i valor és FLOAT -> Error */
            else if (s->type == TYPE_INT && val->type == TYPE_FLOAT) {
                 yyerror("Error: No es pot assignar Float a array Int");
            }

            /* Generem: a[index] := valor */
            emit_array_store(s->name, idx->addr, val_addr);
        }
        free($1);
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "LINE %d: Syntax Error - %s\n", yylineno, s);
}

char* newTemp(void) {
    char buffer[20];
    sprintf(buffer, "$t%02d", temp_counter++); 
    return strdup(buffer);
}

int get_current_line(void) {
    return instruction_line;
}

/* $t1 := a ADDI b */
void emit(char *op, char *a1, char *a2, char *d) { 
    if(d) {
        printf("%d: %s := %s %s %s\n", instruction_line++, d, a1, op, a2); 
    } else {
        if (a2) printf("%d: %s %s, %s\n", instruction_line++, op, a1, a2);
        else    printf("%d: %s %s\n", instruction_line++, op, a1);
    }
}

/* $t1 := CHS x */
void emit_unary(char *op, char *arg1, char *dest) {
    printf("%d: %s := %s %s\n", instruction_line++, dest, op, arg1);
}

/* x := $t1 */
void emit_move(char *src, char *dest) {
    printf("%d: %s := %s\n", instruction_line++, dest, src);
}

/* GOTO 12 */
void emit_goto_line(int line) {
    printf("%d: GOTO %d\n", instruction_line++, line);
}

/* IF $t1 > 0 GOTO 12 */
void emit_if_goto(char *cond_var, int line) {
    printf("%d: IF %s > 0 GOTO %d\n", instruction_line++, cond_var, line);
}

/* DEST := ARRAY[INDEX] */
void emit_array_load(char *arr_name, char *index, char *dest) {
    printf("%d: %s := %s[%s]\n", instruction_line++, dest, arr_name, index);
}

/* ARRAY[INDEX] := SRC */
void emit_array_store(char *arr_name, char *index, char *src) {
    printf("%d: %s[%s] := %s\n", instruction_line++, arr_name, index, src);
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

    printf("%d: HALT\n", instruction_line++);
    /* 7. Cerramos el archivo de entrada (stdout se cierra solo al terminar) */
    fclose(input);
    
    fprintf(stderr, "--- Fin de la Compilacion ---\n");
    return 0;
}