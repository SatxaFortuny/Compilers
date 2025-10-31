%{
    #include <stdio.h>
%}
/* This option makes Flex keep an account of the number of lines (which increments each time it reads \n.)
This way we keep track of where the error is if there happens to be one*/
%option yylineno

%%

[ \t]+      { printf("(%d) IGNORED: SPACE AND/OR TAB\n", yylineno); }
"//".*      { printf("(%d) IGNORED: SINGLE LINE COMMENT.\n", yylineno); }
"#".*       { printf("(%d) IGNORED: SINGLE LINE COMMENT #.\n", yylineno); }
[0-9]+      { printf("(%d) TRACKED: NUMBER\n", yylineno); }
\n          { printf("(%d) TRACKED: EOL\n", yylineno); }
.           { printf("(%d) TRACKED: LEXICAL ERROR\n", yylineno); }


%%
int main(int argc, char **argv) {
    printf("--- Iniciando Scanner (sólo Flex) ---\n");
    
    /* yylex() es la función que Flex genera. Empezará a escanear */
    yylex();
    
    printf("--- Fin del Scanner ---\n");
    return 0;
}

/* Flex nos pide esta función. Con 'return 1' le decimos */
/* que hemos terminado cuando se acabe el archivo. */
int yywrap() {
    return 1; /* 1 = no hay más archivos */
}