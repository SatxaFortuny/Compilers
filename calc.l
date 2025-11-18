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
"true"       {
                printf("(%d) TRACKED: BOOL_LITERAL (true)\n", yylineno);
                yylval.ival = 1;
                return BOOL_LITERAL; }
"false"      {
                printf("(%d) TRACKED: BOOL_LITERAL (false)\n", yylineno);
                yylval.ival = 0;
                return BOOL_LITERAL; }
[0-9]+\.[0-9]+ {
                yylval.fval = atof(yytext);
                printf("(%d) TRACKED: FLOAT_LITERAL (%f)\n", yylineno, yylval.fval);
                return FLOAT_LITERAL; }
\"[^"\n]*\" {
                yylval.sval = strdup(yytext + 1);
                yylval.sval[strlen(yylval.sval) - 1] = '\0'; 
                printf("(%d) TRACKED: STRING_LITERAL (%s)\n", yylineno, yylval.sval);
                return STRING_LITERAL;
            }
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
"+"          { return '+'; }
"-"          { return '-'; }
"*"          { return '*'; }
"/"          { return '/'; }
"("          { return '('; }
")"          { return ')'; }
":="         {
                printf("(%d) TRACKED: ASSIGN (:=)\n", yylineno);
                return ASSIGN; }
.           { printf("(%d) TRACKED: LEXICAL ERROR\n", yylineno); }

%%

int yywrap() {
    return 1; /* 1 = no hay más archivos */
}