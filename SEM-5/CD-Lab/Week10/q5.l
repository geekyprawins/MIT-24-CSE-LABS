%{
	#include <stdio.h>
%}

%%
[0-9] { fwrite(yytext, 1, yyleng, yyout); }
10 { fwrite("A", 1, 1, yyout); }
11 { fwrite("B", 1, 1, yyout); }
12 { fwrite("C", 1, 1, yyout); }
13 { fwrite("D", 1, 1, yyout); }
14 { fwrite("E", 1, 1, yyout); }
15 { fwrite("F", 1, 1, yyout); }
%%

main(int argc, char **argv) {
	yyin = fopen("ip.txt", "r");
	yyout = fopen("out.txt", "w+");
	yylex();
}

int yywrap() {
	return 1;
}