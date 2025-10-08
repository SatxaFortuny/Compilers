%{
#include "calc.tab.h"
#include <stdlib.h>
#include <string.h>
%}

digit   [0-9]
id      [a-zA-Z_][a-zA-Z0-9_]*
real    {digit}+("."{digit}+)?([eE][+-]?{digit}+)?

%%

"int"       { return INT; }
"float"     { return FLOAT; }
"bool"      { return BOOL; }
"string"    { return STRING; }
"true"      { yylval.ival = 1; return BOOLVAL; }
"false"     { yylval.ival = 0; return BOOLVAL; }

{id}        { yylval.sval = strdup(yytext); return ID; }
{real}      { yylval.fval = atof(yytext); return FLOATVAL; }
{digit}+    { yylval.ival = atoi(yytext); return INTVAL; }

":="        { return ASSIGN; }
"**"        { return POW; }
"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return MUL; }
"/"         { return DIV; }
"%"         { return MOD; }
";"         { return ';'; }
"("         { return '('; }
")"         { return ')'; }

[ \t\r\n]+  { /* ignorar espais */ }
"//".*      { /* ignorar comentaris d’una línia */ }
"/*"([^*]|\*+[^*/])*\*+ "/" { /* comentaris multilínia */ }
"#".*       { /* comentari fins a final de línia */ }

.           { return yytext[0]; }

%%
