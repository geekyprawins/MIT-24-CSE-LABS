//C Grammar Parser
//parser.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "la.c"

struct Token retToken;
FILE *fp;

void match();
void Program();
void declarations();
int data_type();
void identifier_list();
void identifier_listprime();
void assign_stat();
void assign_statprime();

void valid()
{
	printf("\n----------PARSER SUCCESS!----------\n\n");
	exit(0);
}

void invalid(char *follow)
{
	printf("\n----------PARSER ERROR!----------\n\n");
	printf("Error reported at row no. %d column no. %d\n", retToken.row, retToken.col);
	printf("Expected %s\n", follow);
	exit(0);
}

int main(int argc, char const *argv[])
{
	fp = fopen(argv[1], "r");
	if (fp == NULL)
	{
		printf("Cannot open file \n");
		exit(0);
	}
	//printf("File opened\nParsing Started\n");
	Program();
	printSymbolTable();
	if (strcmp(retToken.token_name, "eof") == 0 || feof(fp))
		valid();
	else
		invalid("EOF");
}

void match()
{
	//printf("Inside Match\n");
	retToken = getNextToken(fp);
	if (retToken.row == -1)
		return;
	if (strcmp(retToken.token_name, "eof") == 0)
		return;
	printToken(retToken);
}

void Program()
{
	match();
	if (strcmp(retToken.token_name, "main") == 0)
	{
		match();
		if (strcmp(retToken.token_name, "(") == 0)
		{
			match();
			if (strcmp(retToken.token_name, ")") == 0)
			{
				match();
				if (strcmp(retToken.token_name, "{") == 0)
				{
					match();
					declarations();
					assign_stat();
					if (strcmp(retToken.token_name, "}") == 0)
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
	if (data_type())
	{
		identifier_list();
		if (strcmp(retToken.token_name, ";") == 0)
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
	if (strcmp(retToken.token_name, "int") == 0)
	{
		match();
		return 1;
	}
	else if (strcmp(retToken.token_name, "char") == 0)
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
	if (strcmp(retToken.token_name, "id") == 0)
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
	if (strcmp(retToken.token_name, ",") == 0)
	{
		match();
		identifier_list();
	}
}

void assign_stat()
{
	if (strcmp(retToken.token_name, "id") == 0)
	{
		match();
		if (strcmp(retToken.token_name, "=") == 0)
		{
			match();
			assign_statprime();
		}
		else
		{
			invalid("=");
		}
	}
	else
	{
		invalid("id");
	}
}

void assign_statprime()
{
	if (strcmp(retToken.token_name, "id") == 0)
	{
		match();
		if (strcmp(retToken.token_name, ";") == 0)
		{
			match();
		}
		else
		{
			invalid(";");
		}
	}
	else if (strcmp(retToken.token_name, "num") == 0)
	{
		match();
		if (strcmp(retToken.token_name, ";") == 0)
		{
			match();
		}
		else
		{
			invalid(";");
		}
	}
	else
	{
		invalid("id | num");
	}
}
