%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "value.h"
#include "symtab.h"

int yylex(void);
void yyerror(const char *s);
extern int yylineno;
extern FILE *yyin;

char *strdup(const char *s);

int global_offset = 25, temp_counter = 1, instruction_line = 1;
Type current_type;

typedef struct {
    char *op; char *arg1; char *arg2; char *res;
} Quad;

Quad code_memory[4096];

/* --- SWITCH STACK --- */
#define MAX_SWITCH 10
char *switch_stack[MAX_SWITCH];
int switch_top = 0;

void push_switch(char *var) {
    if (switch_top < MAX_SWITCH) switch_stack[switch_top++] = strdup(var);
}
char* get_switch() {
    if (switch_top > 0) return switch_stack[switch_top-1];
    return "error";
}
void pop_switch() {
    if (switch_top > 0) switch_top--;
}
/* -------------------- */

char* newTemp(void);
int get_current_line(void);
void emit(char *op, char *arg1, char *arg2, char *dest);
void emit_unary(char *op, char *arg1, char *dest);
void emit_move(char *src, char *dest);
void emit_goto_line(int line);
void emit_if_goto(char *cond_var, int line);
void emit_array_load(char *arr_name, char *index, char *dest);
void emit_array_store(char *arr_name, char *index, char *src);

struct ListInt* makelist(int i);
struct ListInt* merge(struct ListInt* l1, struct ListInt* l2);
void backpatch(struct ListInt* l, int label);
void print_code_to_file();
%}

%union {
    int ival;
    float fval;
    char *sval;
    struct TempValue *expr;
}

/* TOKENS */
%token <ival> NUMBER
%token <sval> ID
%token INT FLOAT BOOL
%token EOL 
%token <fval> FLOAT_LITERAL   
%token ASSIGN POWER REPEAT DO DONE
%token TRUE FALSE IF THEN ELSE FI WHILE UNTIL FOR IN
%token SWITCH CASE BREAK DEFAULT FSWITCH
%token AND OR NOT GT GE LT LE EQ NE RANGE

/* TYPES */
%type <expr> expression bool_term bool_factor relation simple_expr term unary pow atom
%type <expr> stmt stmt_list marker loop_header case_list case_item for_header line assignation declaration

%%

program: stmt_list ;

marker: 
    { 
        /* USEM CALLOC PER NETEJAR MEMÒRIA */
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        $$->instr = get_current_line(); 
    }
    ;

stmt_list:
    /* buit */ { $$ = NULL; }
    | stmt_list line { 
        $$ = $2; 
    }
    ;

line:
    stmt EOL       { $$ = $1; }
    | EOL          { $$ = NULL; }
    | error EOL    { printf("Error sintàctic a línia %d\n", yylineno); yyerrok; $$ = NULL; }
    ;

stmt:
    simple_expr { 
        emit("PARAM", $1->addr, NULL, NULL);
        if ($1->type == TYPE_INT) emit("CALL", "PUTI", "1", NULL);
        else emit("CALL", "PUTF", "1", NULL);
    }
    | declaration  { 
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue)); 
    }
    | assignation  { 
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue)); 
    }
    
    /* IF - THEN - FI */
    | IF expression THEN marker stmt_list FI {
        backpatch($2->truelist, $4->instr);
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        $$->nextlist = merge($2->falselist, $5 ? $5->nextlist : NULL);
        backpatch($$->nextlist, instruction_line);
        free($4);
    }
    /* IF - THEN - ELSE - FI */
    | IF expression THEN marker stmt_list ELSE 
      { 
          $<expr>$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
          $<expr>$->nextlist = makelist(instruction_line); 
          emit("GOTO", NULL, NULL, NULL); 
      }
      marker stmt_list FI {
          struct TempValue *goto_exit = $<expr>7; 
          backpatch($2->truelist, $4->instr);
          backpatch($2->falselist, $8->instr);
          $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
          struct ListInt *temp = merge($5 ? $5->nextlist : NULL, goto_exit->nextlist);
          $$->nextlist = merge(temp, $9 ? $9->nextlist : NULL);
          backpatch($$->nextlist, instruction_line);
          free($4); free($8); free(goto_exit);
      }
    /* WHILE */
    | WHILE marker expression DO marker stmt_list DONE {
        backpatch($3->truelist, $5->instr);
        backpatch($6 ? $6->nextlist : NULL, $2->instr);
        emit_goto_line($2->instr);
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        $$->nextlist = $3->falselist;
        backpatch($$->nextlist, instruction_line);
        free($2); free($5);
    }
    /* DO - UNTIL */
    | DO marker stmt_list UNTIL marker expression {
        backpatch($6->falselist, $2->instr);
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        $$->nextlist = $6->truelist;
        backpatch($$->nextlist, instruction_line);
        free($2); free($5);
    }
    /* FOR */
    | for_header marker stmt_list DONE {
        TokenValue *s;
        sym_lookup($1->addr, &s);
        
        char *temp_inc = newTemp();
        emit("ADDI", s->name, "1", temp_inc);
        emit_move(temp_inc, s->name);

        emit_goto_line($1->instr);
        backpatch($1->falselist, instruction_line);

        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        free($1);
    }
    /* SWITCH */
    | SWITCH expression EOL
      { push_switch($2->addr); } 
      case_list FSWITCH 
      { 
          struct TempValue *cl = $5;
          backpatch(cl->nextlist, instruction_line);
          backpatch(cl->falselist, instruction_line);
          pop_switch(); 
      }
    /* REPEAT */
    | loop_header stmt_list DONE {
        int start_line = $1->type; char *cnt = $1->addr;
        emit("SUBI", cnt, "1", cnt); emit_if_goto(cnt, start_line);
        free($1);
    }
    ;

/* --- HELPER PEL FOR --- */
for_header:
    FOR ID IN simple_expr RANGE simple_expr DO {
        TokenValue *s;
        if (sym_lookup($2, &s) == SYMTAB_NOT_FOUND) yyerror("Variable del FOR no declarada");
        
        emit_move($4->addr, $2);
        
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        $$->addr = strdup($2); 
        $$->instr = get_current_line(); 
        
        $$->falselist = makelist(instruction_line);
        emit("IFGT", $2, $6->addr, NULL); 
    }
    ;

case_list:
    case_item { $$ = $1; }
    | case_list marker case_item {
        backpatch($1->falselist, $2->instr);
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        $$->falselist = $3->falselist;
        $$->nextlist = merge($1->nextlist, $3->nextlist);
        free($1); free($2); free($3);
    }
    | case_list EOL { $$ = $1; } 
    ;

case_item:
    CASE NUMBER ':' stmt_list BREAK EOL {
        char buf[20]; sprintf(buf, "%d", $2);
        struct ListInt *fail = makelist(instruction_line);
        emit("IFNE", get_switch(), buf, NULL);
        struct ListInt *brk = makelist(instruction_line);
        emit("GOTO", NULL, NULL, NULL);
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        $$->falselist = fail;
        $$->nextlist = brk;
    }
    ;

declaration:
    type_specifier var_list { $$ = NULL; }
    ;

type_specifier:
    INT { current_type = TYPE_INT; }
    | FLOAT { current_type = TYPE_FLOAT; }
    | BOOL { current_type = TYPE_BOOL; }
    ;

var_list:
    var_item
    | var_list ',' var_item
    ;

var_item:
    ID {
        TokenValue *dummy;
        if (sym_lookup($1, &dummy) != SYMTAB_NOT_FOUND) yyerror("Variable repetida");
        else {
            TokenValue *val = (TokenValue*) malloc(sizeof(TokenValue));
            val->type = current_type; val->size = 1; val->name = strdup($1);
            val->offset = global_offset++; sym_add($1, &val);
        }
        free($1);
    }
    | ID '[' NUMBER ']' {
        TokenValue *dummy;
        if (sym_lookup($1, &dummy) != SYMTAB_NOT_FOUND) yyerror("Variable repetida");
        else {
            TokenValue *val = (TokenValue*) malloc(sizeof(TokenValue));
            val->type = current_type; val->size = $3; val->name = strdup($1);
            val->offset = global_offset; global_offset += $3; sym_add($1, &val);
        }
        free($1);
    }
    ;

assignation:
    ID ASSIGN expression {
        TokenValue *s;
        if (sym_lookup($1, &s) == SYMTAB_NOT_FOUND) yyerror("Variable no declarada");
        else {
            /* ARA NO PETARÀ PERQUÈ ESTEM USANT CALLOC (MEMÒRIA NETA) */
            if ($3->truelist) backpatch($3->truelist, instruction_line);
            if ($3->falselist) backpatch($3->falselist, instruction_line);

            if (s->type == TYPE_FLOAT && $3->type == TYPE_INT) {
                char *t = newTemp(); emit_unary("I2F", $3->addr, t); emit_move(t, s->name);
            } else emit_move($3->addr, s->name);
        }
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue)); 
        free($1);
    }
    | ID '[' expression ']' ASSIGN expression {
        TokenValue *s;
        if (sym_lookup($1, &s) == SYMTAB_NOT_FOUND) yyerror("Array no declarat");
        else {
            if ($6->truelist) backpatch($6->truelist, instruction_line);
            if ($6->falselist) backpatch($6->falselist, instruction_line);

            char *val_addr = $6->addr;
            if (s->type == TYPE_FLOAT && $6->type == TYPE_INT) {
                char *t = newTemp(); emit_unary("I2F", val_addr, t); val_addr = t;
            }
            emit_array_store(s->name, $3->addr, val_addr);
        }
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue)); 
        free($1);
    }
    ;

expression:
    bool_term { $$ = $1; }
    | expression OR marker bool_term {
        backpatch($1->falselist, $3->instr);
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        $$->type = TYPE_BOOL;
        $$->truelist = merge($1->truelist, $4->truelist);
        $$->falselist = $4->falselist;
        free($3);
    }
    ;
bool_term:
    bool_factor { $$ = $1; }
    | bool_term AND marker bool_factor {
        backpatch($1->truelist, $3->instr);
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        $$->type = TYPE_BOOL;
        $$->truelist = $4->truelist;
        $$->falselist = merge($1->falselist, $4->falselist);
        free($3);
    }
    ;
bool_factor:
    relation { $$ = $1; }
    | NOT bool_factor {
        $$ = $2;
        struct ListInt *temp = $$->truelist;
        $$->truelist = $$->falselist;
        $$->falselist = temp;
    }
    ;
relation:
    simple_expr { $$ = $1; }
    | simple_expr GT simple_expr {
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        $$->type = TYPE_BOOL;
        $$->truelist = makelist(instruction_line); emit("IFGT", $1->addr, $3->addr, NULL);
        $$->falselist = makelist(instruction_line); emit("GOTO", NULL, NULL, NULL);
    }
    | simple_expr LT simple_expr {
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        $$->type = TYPE_BOOL; 
        $$->truelist = makelist(instruction_line); emit("IFLT", $1->addr, $3->addr, NULL);
        $$->falselist = makelist(instruction_line); emit("GOTO", NULL, NULL, NULL);
    }
    | simple_expr EQ simple_expr {
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        $$->type = TYPE_BOOL; 
        $$->truelist = makelist(instruction_line); emit("IFEQ", $1->addr, $3->addr, NULL);
        $$->falselist = makelist(instruction_line); emit("GOTO", NULL, NULL, NULL);
    }
    | simple_expr GE simple_expr {
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        $$->type = TYPE_BOOL; 
        $$->truelist = makelist(instruction_line); emit("IFGE", $1->addr, $3->addr, NULL);
        $$->falselist = makelist(instruction_line); emit("GOTO", NULL, NULL, NULL);
    }
    | simple_expr LE simple_expr {
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        $$->type = TYPE_BOOL; 
        $$->truelist = makelist(instruction_line); emit("IFLE", $1->addr, $3->addr, NULL);
        $$->falselist = makelist(instruction_line); emit("GOTO", NULL, NULL, NULL);
    }
    | simple_expr NE simple_expr {
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        $$->type = TYPE_BOOL; 
        $$->truelist = makelist(instruction_line); emit("IFNE", $1->addr, $3->addr, NULL);
        $$->falselist = makelist(instruction_line); emit("GOTO", NULL, NULL, NULL);
    }
    | TRUE {
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        $$->type = TYPE_BOOL;
        $$->addr = strdup("1");
        $$->truelist = makelist(instruction_line); emit("GOTO", NULL, NULL, NULL);
    }
    | FALSE {
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        $$->type = TYPE_BOOL;
        $$->addr = strdup("0");
        $$->falselist = makelist(instruction_line); emit("GOTO", NULL, NULL, NULL);
    }
    ;
simple_expr:
    term { $$ = $1; }
    | simple_expr '+' term {
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        if ($1->type == TYPE_INT && $3->type == TYPE_INT) {
             $$->type = TYPE_INT; $$->addr = newTemp(); emit("ADDI", $1->addr, $3->addr, $$->addr);
        } else {
             $$->type = TYPE_FLOAT; $$->addr = newTemp();
             if($1->type==TYPE_INT){char*t=newTemp();emit_unary("I2F",$1->addr,t);emit("ADDF",t,$3->addr,$$->addr);}
             else if($3->type==TYPE_INT){char*t=newTemp();emit_unary("I2F",$3->addr,t);emit("ADDF",$1->addr,t,$$->addr);}
             else emit("ADDF", $1->addr, $3->addr, $$->addr);
        }
    }
    | simple_expr '-' term {
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        if ($1->type == TYPE_INT && $3->type == TYPE_INT) {
             $$->type = TYPE_INT; $$->addr = newTemp(); emit("SUBI", $1->addr, $3->addr, $$->addr);
        } else {
             $$->type = TYPE_FLOAT; $$->addr = newTemp();
             if($1->type==TYPE_INT){char*t=newTemp();emit_unary("I2F",$1->addr,t);emit("SUBF",t,$3->addr,$$->addr);}
             else if($3->type==TYPE_INT){char*t=newTemp();emit_unary("I2F",$3->addr,t);emit("SUBF",$1->addr,t,$$->addr);}
             else emit("SUBF", $1->addr, $3->addr, $$->addr);
        }
    }
    ;
term:
    unary { $$ = $1; }
    | term '*' unary {
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        if ($1->type == TYPE_INT && $3->type == TYPE_INT) {
             $$->type = TYPE_INT; $$->addr = newTemp(); emit("MULI", $1->addr, $3->addr, $$->addr);
        } else {
             $$->type = TYPE_FLOAT; $$->addr = newTemp();
             if($1->type==TYPE_INT){char*t=newTemp();emit_unary("I2F",$1->addr,t);emit("MULF",t,$3->addr,$$->addr);}
             else if($3->type==TYPE_INT){char*t=newTemp();emit_unary("I2F",$3->addr,t);emit("MULF",$1->addr,t,$$->addr);}
             else emit("MULF", $1->addr, $3->addr, $$->addr);
        }
    }
    | term '/' unary {
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        if ($1->type == TYPE_INT && $3->type == TYPE_INT) {
             $$->type = TYPE_INT; $$->addr = newTemp(); emit("DIVI", $1->addr, $3->addr, $$->addr);
        } else {
             $$->type = TYPE_FLOAT; $$->addr = newTemp();
             if($1->type==TYPE_INT){char*t=newTemp();emit_unary("I2F",$1->addr,t);emit("DIVF",t,$3->addr,$$->addr);}
             else if($3->type==TYPE_INT){char*t=newTemp();emit_unary("I2F",$3->addr,t);emit("DIVF",$1->addr,t,$$->addr);}
             else emit("DIVF", $1->addr, $3->addr, $$->addr);
        }
    }
    | term '%' unary {
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        if ($1->type == TYPE_INT && $3->type == TYPE_INT) {
            $$->type = TYPE_INT; $$->addr = newTemp(); emit("MODI", $1->addr, $3->addr, $$->addr);
        } else {
            yyerror("Error: Mòdul només amb enters");
            $$->type = TYPE_INT; $$->addr = strdup("0");
        }
    }
    ;
unary:
    pow { $$ = $1; }
    | '-' unary {
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        $$->type = $2->type; $$->addr = newTemp();
        if ($2->type == TYPE_INT) emit_unary("CHSI", $2->addr, $$->addr);
        else emit_unary("CHSF", $2->addr, $$->addr);
    }
    | '+' unary { $$ = $2; }
    ;
pow:
    atom { $$ = $1; }
    | atom POWER pow {
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        $$->type = $1->type; $$->addr = newTemp();
        if ($$->type == TYPE_INT) emit_move("1", $$->addr); else emit_move("1.0", $$->addr);
    }
    ;
atom:
    NUMBER {
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        $$->type = TYPE_INT; 
        char buf[20]; sprintf(buf, "%d", $1); $$->addr = strdup(buf);
    }
    | FLOAT_LITERAL {
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        $$->type = TYPE_FLOAT;
        char buf[30]; sprintf(buf, "%.5f", $1); $$->addr = strdup(buf);
    }
    | ID {
        TokenValue *s;
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        if (sym_lookup($1, &s) == SYMTAB_NOT_FOUND) {
            yyerror("Variable no declarada"); $$->type = TYPE_INT; $$->addr = strdup("0");
        } else {
            $$->type = s->type; $$->addr = strdup(s->name);
        }
        free($1);
    }
    | ID '[' expression ']' {
        TokenValue *s;
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        if (sym_lookup($1, &s) == SYMTAB_NOT_FOUND) {
             yyerror("Array no declarat"); $$->type = TYPE_INT; $$->addr = strdup("0");
        } else {
             $$->type = s->type; $$->addr = newTemp();
             emit_array_load(s->name, $3->addr, $$->addr);
        }
        free($1);
    }
    | '(' expression ')' { $$ = $2; }
    ;

loop_header:
    REPEAT expression DO {
        $$ = (struct TempValue*) calloc(1, sizeof(struct TempValue));
        char *counter = newTemp(); emit_move($2->addr, counter);
        $$->type = get_current_line(); $$->addr = counter;
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "LINE %d: Syntax Error - %s\n", yylineno, s);
}

struct ListInt* makelist(int i) {
    struct ListInt* l = (struct ListInt*) malloc(sizeof(struct ListInt));
    l->instr = i; l->next = NULL; return l;
}
struct ListInt* merge(struct ListInt* l1, struct ListInt* l2) {
    if (!l1) return l2; if (!l2) return l1;
    struct ListInt* p = l1; while (p->next) p = p->next;
    p->next = l2; return l1;
}
void backpatch(struct ListInt* l, int label) {
    char buf[20]; sprintf(buf, "%d", label);
    struct ListInt* temp = l;
    while (temp) {
        int idx = temp->instr;
        if (code_memory[idx].res) free(code_memory[idx].res);
        code_memory[idx].res = strdup(buf);
        temp = temp->next;
    }
}
void emit(char *op, char *arg1, char *arg2, char *dest) {
    code_memory[instruction_line].op   = strdup(op);
    code_memory[instruction_line].arg1 = arg1 ? strdup(arg1) : NULL;
    code_memory[instruction_line].arg2 = arg2 ? strdup(arg2) : NULL;
    code_memory[instruction_line].res  = dest ? strdup(dest) : NULL;
    instruction_line++;
}
char* newTemp(void) { char b[20]; sprintf(b, "$t%02d", temp_counter++); return strdup(b); }
int get_current_line(void) { return instruction_line; }
void emit_unary(char *op, char *arg1, char *dest) { emit(op, arg1, NULL, dest); }
void emit_move(char *src, char *dest) { emit(":=", src, NULL, dest); }
void emit_goto_line(int line) { char b[20]; sprintf(b, "%d", line); emit("GOTO", NULL, NULL, b); }
void emit_if_goto(char *cond, int line) { char b[20]; sprintf(b, "%d", line); emit("IF_GT_0", cond, NULL, b); }
void emit_array_load(char *arr, char *idx, char *dest) { emit("=[]", arr, idx, dest); }
void emit_array_store(char *arr, char *idx, char *src) { emit("[]=", arr, idx, src); }

void print_code_to_file() {
    int i;
    for (i = 1; i < instruction_line; i++) {
        Quad q = code_memory[i];
        printf("%d: ", i);
        if (strcmp(q.op, "PARAM") == 0) printf("PARAM %s\n", q.arg1);
        else if (strcmp(q.op, "CALL") == 0) printf("CALL %s, %s\n", q.arg1, q.arg2);
        else if (strcmp(q.op, "GOTO") == 0) printf("GOTO %s\n", q.res ? q.res : "??");
        else if (strcmp(q.op, ":=") == 0) printf("%s := %s\n", q.res, q.arg1);
        else if (strcmp(q.op, "=[]") == 0) printf("%s := %s[%s]\n", q.res, q.arg1, q.arg2);
        else if (strcmp(q.op, "[]=") == 0) printf("%s[%s] := %s\n", q.arg1, q.arg2, q.res);
        else if (strncmp(q.op, "IF", 2) == 0 && strcmp(q.op, "IF_GT_0") != 0) {
            char *rel = "??";
            if      (strcmp(q.op, "IFGT") == 0) rel = ">";
            else if (strcmp(q.op, "IFGE") == 0) rel = ">=";
            else if (strcmp(q.op, "IFLT") == 0) rel = "<";
            else if (strcmp(q.op, "IFLE") == 0) rel = "<=";
            else if (strcmp(q.op, "IFEQ") == 0) rel = "=";
            else if (strcmp(q.op, "IFNE") == 0) rel = "!=";
            printf("IF %s %s %s GOTO %s\n", q.arg1, rel, q.arg2, q.res ? q.res : "??");
        }
        else if (strcmp(q.op, "IF_GT_0") == 0) printf("IF %s > 0 GOTO %s\n", q.arg1, q.res);
        else {
            if (q.arg2) printf("%s := %s %s %s\n", q.res, q.arg1, q.op, q.arg2);
            else printf("%s := %s %s\n", q.res, q.op, q.arg1);
        }
    }
    printf("%d: HALT\n", instruction_line);
}

int main(int argc, char **argv) {
    if (argc != 3) return 1;
    FILE *input = fopen(argv[1], "r");
    if (!input) return 1;
    yyin = input;
    freopen(argv[2], "w", stdout);
    yyparse();
    print_code_to_file();
    fclose(input);
    return 0;
}