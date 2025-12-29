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

"int"        { return INT; }
"float"      { return FLOAT; }
"repeat"     { return REPEAT; }
"do"         { return DO;}
"done"       { return DONE;}
[0-9]+\.[0-9]+([eE][+-]?[0-9]+)?|[0-9]+[eE][+-]?[0-9]+ {
                yylval.fval = atof(yytext);
                return FLOAT_LITERAL; }
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

"**"         { return POWER; }
"%"          { return '%'; }
"+"          { return '+'; }
"-"          { return '-'; }
"*"          { return '*'; }
"/"          { return '/'; }
"("          { return '('; }
")"          { return ')'; }
","          { return ','; }
"["          { return '['; }
"]"          { return ']'; }
":="         {
                return ASSIGN; }
.           {  }

%%

int yywrap() {
    return 1; 
}