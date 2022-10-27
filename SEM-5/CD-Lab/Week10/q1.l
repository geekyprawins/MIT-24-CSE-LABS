%{
	#include <stdio.h>
	int vowels = 0;
	int consonants = 0;
%}

%%
[a,e,i,o,u,A,E,I,O,U] {vowels++;}
[a-zA-Z] {consonants++;}
%%

int main() {
	yyin = fopen("ip.txt", "r");
	yylex();
	printf("%d %d", vowels, consonants);
}

int yywrap() { 
	return 1;
}