%{
#include "q1.tab.h"
%}
%%
"int" {return INT;}
";" {return SC;}
"," {return CM;}
[a-zA-Z][a-zA-Z0-9_]* {return ID; }
\n {return NL;}
%%

int yywrap(){return 1;}