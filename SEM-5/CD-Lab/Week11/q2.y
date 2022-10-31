%{
	#include<stdio.h>
	#include<stdlib.h>
	int yylex();
	int yyerror();
%}
%token IF ELSE OB CB OP CP RELOP MULOP ADDOP ID NUM NL SC ASS
%%
statementList: statement statementList {printf("Vaild decision statement\n"); exit(0);}
				 |
				 ;
statement: assignStat SC
		 |decisionStat
		 ;
assignStat: ID ASS expn
		  ;
decisionStat: IF OP expn CP OB statementList CB dprime
				;
dprime: ELSE OB statementList CB
	   |
	   ;
expn: simpleExpn eprime
	 ;
eprime: RELOP simpleExpn
		|
		;
simpleExpn:term seprime
			 ;
seprime: ADDOP term seprime
	    |
	    ;
term: factor tprime
	 ;
tprime: MULOP factor tprime
		|
		;
factor: ID
		| NUM
		;
%%
int yyerror(char * msg)
{
	printf("Invalid decision statement!\n");
	return 1;
}
int main()
{
	printf("Enter decision statement:\n");
	yyparse();
}
