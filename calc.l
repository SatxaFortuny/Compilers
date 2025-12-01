%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "calc.tab.h"
%}
/* This option makes Flex keep an account of the number of lines (which increments each time it reads \n.)
This way we keep track of where the error is if there happens to be one*/
%option yylineno
%x COMMENT
%%

"/*"            { BEGIN(COMMENT); }

<COMMENT>"*/"   { BEGIN(INITIAL); } 
<COMMENT>\n     {  }
<COMMENT>.      {  }

"and"        { return AND; }
"or"         { return OR; }
"not"        { return NOT; }
"PI"         { return PI; }
"E"          { return E; }
"sin"        { return SIN; }
"cos"        { return COS; }
"tan"        { return TAN; }
"LEN"        { return LEN; }

"struct"     { return STRUCT; }
"{"          { return '{'; }
"}"          { return '}'; }
"."          { return '.'; }
";"          { return ';'; }
","          { return ','; }

"int"        { return INT; }
"float"      { return FLOAT; }
"string"     { return STRING; }
"bool"       { return BOOL; }
"true"       {
                yylval.ival = 1;
                return BOOL_LITERAL; }
"false"      {
                yylval.ival = 0;
                return BOOL_LITERAL; }
[0-9]+\.[0-9]+ {
                yylval.fval = atof(yytext);
                return FLOAT_LITERAL; }
\"[^"\n]*\" {
                yylval.sval = strdup(yytext + 1);
                yylval.sval[strlen(yylval.sval) - 1] = '\0'; 
                return STRING_LITERAL;
            }
[ \t]+      {  }
"//".*      {  }
"#".*       {  }
[0-9]+      {   yylval.ival = atoi(yytext);
                return NUMBER;}
\n          { return EOL;}
[a-zA-Z][a-zA-Z0-9_]* {
    yylval.sval = strdup(yytext);
    return ID;
}
"=="         { return EQ; }
"<="         { return LE; }
">="         { return GE; }
"!="         { return NE; }
"<"          { return LT; }
">"          { return GT; }

"**"         { return POWER; }
"%"          { return '%'; }
"+"          { return '+'; }
"-"          { return '-'; }
"*"          { return '*'; }
"/"          { return '/'; }
"("          { return '('; }
")"          { return ')'; }
":="         {
                return ASSIGN; }
.           {  }

%%

int yywrap() {
    return 1; /* 1 = no hay más archivos */
}