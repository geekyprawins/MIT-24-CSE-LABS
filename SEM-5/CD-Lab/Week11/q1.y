%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
int yyerror();
%}
%token INT ID SC CM NL
%%
stmt : DC NL
;
DC : DT IDL SC { printf("Valid declaration statement!\n"); exit(0);}
;
DT : INT
;
IDL: ID
|ID CM IDL 
;
%%
int yyerror(char *msg)
{
printf("Invalid declaration statement!\n");
exit(0);
}
void main ()
{
printf("Enter the declaration statement:\n");
yyparse();
}