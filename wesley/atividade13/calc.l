%option noyywrap

%{
    #include <stdio.h>
    #include "calc.tab.h"
%}

DIGIT [0-9]

/*[ \t] Ignora todos os espacos*/
%%
\n { return T_NEW_LINE; }
"ADD" { return T_PLUS; }
"SUB" { return T_MINUS; }
"PRINT" { return T_PRINT; }
{DIGIT}+\.{DIGIT}* { yylval.fval = atof(yytext); return T_FLOAT; }
{DIGIT}+ { yylval.ival = atoi(yytext); return T_INT; }
[a-zA-Z]+ { yylval.cval = yytext; return T_STRING; }
[ \t]   ;
%%

/*To compile use*/
/*flex calc.l*/
/*gcc calc.tab.c lex.yy.c -o calc -lm*/

/*Codigo de usuario*/
// int main() {
//     /*Roda a analise lexa*/
//     yylex();
//     return 0;
// }
