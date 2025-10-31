%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "calc.tab.h"
%}
/* This option makes Flex keep an account of the number of lines (which increments each time it reads \n.)
This way we keep track of where the error is if there happens to be one*/
%option yylineno

%%

"int"       {   printf("(%d)TRACKED: Integer\n", yylineno);
                return K_INT; }
"float"       {   printf("(%d)TRACKED: Float\n", yylineno);
                return K_FLOAT; }
"string"       {   printf("(%d)TRACKED: String\n", yylineno);
                return K_STRING; }
"bool"       {   printf("(%d)TRACKED: Bool\n", yylineno);
                return K_BOOL; }

[ \t]+      { printf("(%d) IGNORED: SPACE OR TAB\n", yylineno); }
"//".*      { printf("(%d) IGNORED: SINGLE LINE COMMENT.\n", yylineno); }
"#".*       { printf("(%d) IGNORED: SINGLE LINE COMMENT #.\n", yylineno); }
[0-9]+      {   yylval.ival = atoi(yytext);
                printf("(%d) TRACKED: NUMBER (%d)\n", yylineno, yylval.ival); 
                return NUMBER;}
\n          { printf("(%d) TRACKED: EOL\n", yylineno); return EOL;}
[a-zA-Z][a-zA-Z0-9_]* {
    yylval.sval = strdup(yytext);
    printf("(%d) TRACKED: ID (%s)\n", yylineno, yylval.sval);
    return ID;
}
.           { printf("(%d) TRACKED: LEXICAL ERROR\n", yylineno); }

%%

int yywrap() {
    return 1; /* 1 = no hay más archivos */
}