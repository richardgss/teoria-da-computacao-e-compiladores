/*Definicoes e inclusao de definicoes usando include "inc.h"*/
/*https://www.lysator.liu.se/c/ANSI-C-grammar-y.html#translation-unit*/
%{
    #include <stdio.h>
    #include <stdlib.h>

    extern int yylex();
    extern int yyparse();
    extern FILE* yyin;

    void yyerror(const char *);
%}

%union{
    int ival;
    float fval;
    char* cval;
}

%token <ival> T_INT
%token <fval> T_FLOAT
%token <cval> T_STRING
%token T_PLUS T_MINUS
%token T_NEW_LINE
%token T_DQUOTE
%token T_PRINT

%type<ival> expression
%type<fval> expression_f
%type<cval> expression_p

%start calculation

%%
calculation :
        |   calculation line
;

line : T_NEW_LINE
        |   expression    T_NEW_LINE    { printf("\tResultado: %i\n", $1); }
        |   expression_f  T_NEW_LINE    { printf("\tResultado: %f\n", $1); }
        |   expression_p  T_NEW_LINE    { printf("\tResultado: %s\n", $1); }
;

expression : T_INT { $$ = $1; }
        |   T_PLUS expression expression   { $$ = $2 + $3; }
        |   T_MINUS expression expression  { $$ = $2 - $3; }
;


expression_f : T_FLOAT { $$ = $1; }
        |   T_PLUS expression_f expression_f   { $$ = $2 + $3; }
        |   T_MINUS expression_f expression_f  { $$ = $2 - $3; }
        |   T_PLUS expression_f expression     { $$ = $2 + $3; }
        |   T_MINUS expression_f expression    { $$ = $2 - $3; }
        |   T_PLUS expression expression_f     { $$ = $2 + $3; }
        |   T_MINUS expression expression_f    { $$ = $2 - $3; }
;

expression_p : T_STRING { $$ = $1; }
        | T_PRINT expression_p { $$ = $2; }
;

%%

int main() {
    yyin = stdin;
    do {
        yyparse();
    } while(!feof(yyin));
}

void yyerror(const char *s) {
    fprintf(stderr, "Erro de parse: %s\n", s);
    exit(1);
}

/* To compile use: */
/* bison -d calc.y */
