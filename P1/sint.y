%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int yylex(void);
void yyerror(const char *s);

/* --- Taula de símbols molt simple --- */
typedef struct {
    char *id;
    double val;
} symbol;

symbol symtab[100];
int symcount = 0;

double lookup(char *id) {
    for (int i = 0; i < symcount; i++) {
        if (strcmp(symtab[i].id, id) == 0) return symtab[i].val;
    }
    fprintf(stderr, "Error: variable %s no definida\n", id);
    exit(1);
}

void assign(char *id, double val) {
    for (int i = 0; i < symcount; i++) {
        if (strcmp(symtab[i].id, id) == 0) {
            symtab[i].val = val;
            return;
        }
    }
    symtab[symcount].id = id;
    symtab[symcount].val = val;
    symcount++;
}
%}

%union {
    int ival;
    double fval;
    char *sval;
}

%token <ival> INTVAL BOOLVAL
%token <fval> FLOATVAL
%token <sval> ID
%token INT FLOAT BOOL STRING
%token ASSIGN
%token PLUS MINUS MUL DIV MOD POW

%left PLUS MINUS
%left MUL DIV MOD
%right POW

%type <fval> expr

%%
program:
      /* buit */
    | program stmt
    ;

stmt:
      ID ASSIGN expr ';'   { assign($1, $3); }
    | expr ';'             { printf("= %lf\n", $1); }
    ;

expr:
      INTVAL               { $$ = $1; }
    | FLOATVAL             { $$ = $1; }
    | ID                   { $$ = lookup($1); }
    | expr PLUS expr       { $$ = $1 + $3; }
    | expr MINUS expr      { $$ = $1 - $3; }
    | expr MUL expr        { $$ = $1 * $3; }
    | expr DIV expr        { $$ = $1 / $3; }
    | expr MOD expr        { $$ = fmod($1, $3); }
    | expr POW expr        { $$ = pow($1, $3); }
    | '(' expr ')'         { $$ = $2; }
    ;
%%
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    printf("Calculadora amb Flex i Bison\n");
    yyparse();
    return 0;
}
