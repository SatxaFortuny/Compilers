%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc.tab.h"
%}
%option yylineno
%x COMMENT

%%

"/*"            { BEGIN(COMMENT); }
<COMMENT>"*/"   { BEGIN(INITIAL); } 
<COMMENT>\n     { }
<COMMENT>.      { }

"//".* { }
"#".* { }

"int"           { return INT; }
"float"         { return FLOAT; }
"bool"          { return BOOL; }
"true"          { yylval.ival = 1; return TRUE; }
"false"         { yylval.ival = 0; return FALSE; }

"if"            { return IF; }
"then"          { return THEN; }
"else"          { return ELSE; }
"fi"            { return FI; }
"while"         { return WHILE; }
"do"            { return DO; }
"done"          { return DONE; }
"repeat"        { return REPEAT; }
"until"         { return UNTIL; }
"for"           { return FOR; }
"in"            { return IN; }

"switch"        { return SWITCH; }
"case"          { return CASE; }
"break"         { return BREAK; }
"default"       { return DEFAULT; }
"fswitch"       { return FSWITCH; }

"and"           { return AND; }
"or"            { return OR; }
"not"           { return NOT; }

">"             { return GT; }
"<"             { return LT; }
">="            { return GE; }
"<="            { return LE; }
"=="            { return EQ; }
"<>"            { return NE; }
":="            { return ASSIGN; }
"**"            { return POWER; }
".."            { return RANGE; }

[0-9]+\.[0-9]+([eE][+-]?[0-9]+)?|[0-9]+[eE][+-]?[0-9]+ {
                yylval.fval = atof(yytext);
                return FLOAT_LITERAL; }

[0-9]+          { yylval.ival = atoi(yytext); return NUMBER; }

[a-zA-Z][a-zA-Z0-9_]* {
                yylval.sval = strdup(yytext);
                return ID; }

[ \t\r]+        { }
\n              { return EOL; }
.               { return yytext[0]; }

%%

int yywrap() { return 1; }