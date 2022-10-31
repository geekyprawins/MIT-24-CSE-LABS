%{
	#include "q2.tab.h"
%}
%%
"if" {return IF;}
"else" {return ELSE;}
";" {return SC;}
"{" {return OB;}
"}" {return CB;}
"(" {return OP;}
")" {return CP;}
">="|"<="|"!="|"==" {return RELOP;}
"<"|">" {return RELOP;}
"=" {return ASS;}
"*"|"/"|"%" {return MULOP;}
"+"|"-" {return ADDOP;}
"\n" {return NL;}
[0-9]+ {return NUM;}
[A-Za-z_]+[A-Za-z_0-9]* {return ID;}
%%
int yywrap(){return 1;}

