%{
	int chars = 0;
	int words = 0;
	int blanks = 0;
	int lines = 0;
%}

%%
" " {blanks++;}
[a-zA-Z]+ { words++; chars += strlen(yytext); }
\n { chars++; lines++; }
. { chars++; }
%%

main(int argc, char **argv) {
	yyin = fopen("ip.txt", "r");
	yylex();
	printf("%d %d %d %d\n", lines, words, chars, blanks); 
}
int yywrap() {
	return 1;
}