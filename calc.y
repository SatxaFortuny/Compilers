%{
#include <stdio.h>
/* yylex() is the flex scanner. yyerror() is the fuction Bison will call in case of an error. */
int yylex(void);
void yyerror(const char *s);
%}

%union {
    int ival;
}

/* Here what we are doing is defining the tokens that will be given by the Flex scanner. */
%token <ival> NUMBER
%token EOL 

%%

/* Now we will try to classify everything into a program. Which is defined by a series of lines */
program:
    | program line
    ;

line:
    NUMBER EOL { printf("BISON: NUMBER (%d) + EOL\n", $1); }
    | EOL        { printf("BISON: EOL\n"); }
    ;

%%

void yyerror(const char *s) {
    extern int yylineno;
    fprintf(stderr, "Línea %d: Syntax Error - %s\n", yylineno, s);
}

int main(int argc, char **argv) {
    printf("--- Starting Parser (Bison + Flex) ---\n");
    
    yyparse();
    
    printf("--- End of Parser ---\n");
    return 0;
}