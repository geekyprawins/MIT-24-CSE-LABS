//C Grammar Parser
//parser.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include "la.c"

struct Token retToken;
FILE *fp;

void match();
void Program();
void declarations();
int data_type();
void identifier_list();
void identifier_listprime();
void identifier_listprimeprime();
void statement_list();
int statement();
int assign_stat();
void expn();
void eprime();
void simple_expn();
void seprime();
void term();
void tprime();
void factor();
int relop();
int addop();
int mulop();

void valid()
{
	printf("\n----------PARSER SUCCESS!----------\n\n");
	exit(0);
}

void invalid(char *follow)
{
	printf("\n----------PARSER ERROR!----------\n\n");
	printf("Error reported at row no. %d column no. %d\n",retToken.row, retToken.col);
	printf("Expected %s\n", follow);
	exit(0);
}

int main(int argc, char const *argv[])
{
	fp = fopen(argv[1], "r");
	if (fp == NULL){
	printf("Cannot open file \n");
	exit(0); }	
	//printf("File opened\nParsing Started\n");
	Program();
	if(strcmp(retToken.token_name,"eof")==0||feof(fp))
		valid();
	else
		invalid("EOF");
}

void match()
{	
	//printf("Inside Match\n");
	retToken=getNextToken(fp);
	if(retToken.row == -1)
	 		return;
	if(strcmp(retToken.token_name,"eof")==0)
		return;
	printToken(retToken);
}

void Program()
{
	match();
	if(strcmp(retToken.token_name,"main")==0)
	{
		match();
		if(strcmp(retToken.token_name,"(")==0)
		{
			match();
			if(strcmp(retToken.token_name,")")==0)
			{
				match();
				if(strcmp(retToken.token_name,"{")==0)
				{
					match();
					declarations();
					statement_list();
					if(strcmp(retToken.token_name,"}")==0)
					{
						match();
					}
					else
					{
						invalid("}");
					}
				}
				else
				{
					invalid("{");
				}
			}
			else
			{
				invalid(")");
			}
		}
		else
		{
			invalid("(");
		}
	}
	else
	{
		invalid("main");
	}
}

void declarations()
{
	if(data_type())
	{
		identifier_list();
		if(strcmp(retToken.token_name,";")==0)
		{
			match();
			declarations();
		}
		else
		{
			invalid(";");
		}
	}
}

int data_type()
{
	if(strcmp(retToken.token_name,"int")==0 )
	{
		match();
		return 1;
	}
	else if(strcmp(retToken.token_name,"char")==0 )
	{
		match();
		return 1;
	}
	else
	{
		return 0;
	}
}

void identifier_list()
{
	if(strcmp(retToken.token_name,"id")==0)
	{
		match();
		identifier_listprime();
	}
	else
	{
		invalid("id");
	}
}

void identifier_listprime()
{
	if(strcmp(retToken.token_name,",")==0)
	{
		match();
		identifier_list();
	}
	else if(strcmp(retToken.token_name,"[")==0)
	{
		// printf("its a match [\n");
		match();
		if(strcmp(retToken.token_name,"num")==0)
		{
			match();
		        if(strcmp(retToken.token_name,"]")==0)
			{
				match();
				identifier_listprimeprime();
			}
			else
			{
				invalid("]");
			}
		}
		else
		{
			invalid("num");
		}
	}
}

void identifier_listprimeprime()
{
	if(strcmp(retToken.token_name,",")==0)
	{
		match();
		identifier_list();
	}
}

void statement_list()
{
	if(statement())
	{
		statement_list();
	}
}

int statement()
{
	if(assign_stat())
	{
		if(strcmp(retToken.token_name,";")==0)
		{
			match();
			return 1;
		}
		else
		{
			invalid(";");
		}
	}
	else
	{
		return 0;
	}
}

int assign_stat()
{
	if(strcmp(retToken.token_name,"id")==0)
	{
		match();
		if(strcmp(retToken.token_name,"=")==0)
		{
			match();
			expn();
			return 1;
		}
		else
		{
			invalid("=");
		}
	}
	else
	{
		return 0;
	}
}

void expn()
{
	simple_expn();
	eprime();
}

void eprime()
{
	if(relop())
	{
		simple_expn();
	}
}

void simple_expn()
{
	term();
	seprime();
}

void seprime()
{
	if(addop())
	{
		term();
		seprime();
	}
}

void term()
{
	factor();
	tprime();
}

void tprime()
{
	if(mulop())
	{
		factor();
		tprime();
	}
}

void factor()
{
	if(strcmp(retToken.token_name,"id")==0)
	{
		match();
	}
	else if(strcmp(retToken.token_name,"num")==0)
	{
		match();
	}
	else
	{
		invalid("id | num");
	}
}

int relop()
{
	if(strcmp(retToken.token_name,"==")==0)
	{
		match();
		return 1;
	}
	else if(strcmp(retToken.token_name,"!=")==0)
	{
		match();
		return 1;
	}
	else if(strcmp(retToken.token_name,"<=")==0)
	{
		match();
		return 1;
	}
	else if(strcmp(retToken.token_name,">=")==0)
	{
		match();
		return 1;
	}
	else if(strcmp(retToken.token_name,">")==0)
	{
		match();
		return 1;
	}
	else if(strcmp(retToken.token_name,"<")==0)
	{
		match();
		return 1;
	}
	else
	{
		return 0;
	}
}

int addop()
{
	if(strcmp(retToken.token_name,"+")==0)
	{
		match();
		return 1;
	}
	else if(strcmp(retToken.token_name,"-")==0)
	{
		match();
		return 1;
	}
	else
	{
		return 0;
	}
}

int mulop()
{
	if(strcmp(retToken.token_name,"*")==0)
	{
		match();
		return 1;
	}
	else if(strcmp(retToken.token_name,"/")==0)
	{
		match();
		return 1;
	}
	else if(strcmp(retToken.token_name,"%")==0)
	{
		match();
		return 1;
	}
	else
	{
		return 0;
	}
}
