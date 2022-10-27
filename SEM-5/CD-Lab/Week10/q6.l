%{
	#include <stdio.h>
    #include <ctype.h>
%}

%%
\/\/.* { fwrite(yytext, 1, yyleng, yyout); }
[A-Z] { yytext[0] += 32; fwrite(yytext, 1, yyleng, yyout); }
%%

main(int argc, char **argv) {
	yyin = fopen("ip.txt", "r");
	yyout = fopen("out.txt", "w+");
	yylex();
}

int yywrap() {
	return 1;
}