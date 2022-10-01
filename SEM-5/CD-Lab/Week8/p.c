#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getNextToken.h"
struct token tkn;
FILE *fin ;
void program();
void declarations();
void dataType();
void identifierList();
void assign_stat();
void relop();
void addop();
void mulop();
void factor();
void tprime();
void term();
void seprime();
void simpleExp();
void eprime();
void expn();
void statement();
void statementList();


void valid()
{
	printf("----------SUCCESS!----------\n");
	exit(0);
}

void invalid()
{
	printf("----------ERROR!----------\n");
	exit(0);
}




void program(){
	if(strcmp(tkn.lexeme,"main")==0){
		tkn = getNextToken(fin);
		if(strcmp(tkn.lexeme,"(")==0){
			tkn = getNextToken(fin);
			if(strcmp(tkn.lexeme,")")==0){
				tkn = getNextToken(fin);
				if(strcmp(tkn.lexeme,"{")==0){
					tkn = getNextToken(fin);

					declarations();
    			printf("\n <%s %s>",tkn.lexeme,tkn.type);

					statementList();
    			printf("\n <%s %s>",tkn.lexeme,tkn.type);

					if(strcmp(tkn.lexeme,"}")==0){
						tkn = getNextToken(fin);
						valid();
					}else{
						printf("\n } expected!");
						exit(0);

					}
				}else{
					printf("\n { expected!");
					exit(0);

				}
			}else{
				printf("\n ) expected!");
				exit(0);

			}
		}else{
			printf("\n ( expected!");
			exit(0);

		}
	}else{
		printf("\n main expected!");
		exit(0);

	}
}

void statementList(){
	if(strcmp(tkn.type,"Identifier")==0){
		statement();
		statementList();
	}else{
		return;
	}
}

void statement(){
	assign_stat();
	if(strcmp(tkn.lexeme,";")==0){
		tkn = getNextToken(fin);
		return;
	}else{
		printf("semicolon expected");
		exit(0);
	}
}

void simpleExp(){
	term();
	seprime();
}
void eprime(){
	if(strcmp(tkn.type,"RelationalOperator")==0){
		relop();
		simpleExp();
	}else{
		return;
	}
}
void expn(){
	simpleExp();
	eprime();
}

void addop(){
	if(strcmp(tkn.lexeme,"+")==0){
		tkn = getNextToken(fin);
		return;	
	}
	else if(strcmp(tkn.lexeme,"-")==0){
		tkn = getNextToken(fin);
		return;
		
	}else{
			printf("addop expected\n");
		exit(0);
		
		}
}

void mulop(){
	if(strcmp(tkn.lexeme,"*")==0){
		tkn = getNextToken(fin);
		return;	
	}
	else if(strcmp(tkn.lexeme,"/")==0){
		tkn = getNextToken(fin);
		return;
		
	}else if(strcmp(tkn.lexeme,"%")==0){
		tkn = getNextToken(fin);
		return;
		
	}else{
		printf("mulop expected\n");
		exit(0);
		}
}



void relop(){
	if(strcmp(tkn.type,"RelationalOperator")==0){
		tkn = getNextToken(fin);

		
	}else{
		printf("relop expected\n");

	}
}
void factor(){
	if(strcmp(tkn.type,"Identifier")==0||strcmp(tkn.type,"Number")==0 ){
		tkn = getNextToken(fin);
	}
	else{
		printf("Number or identifier expected\n");
		exit(0);
	}
}

void tprime(){
	if(strcmp(tkn.lexeme,"*")==0||strcmp(tkn.lexeme,"%")==0||strcmp(tkn.lexeme,"/")==0){
		mulop();
		factor();
		tprime();
	}else{
		return;
	}
	
}
void term(){
	factor();
	tprime();
}

void seprime(){
	if(strcmp(tkn.lexeme,"+")==0||strcmp(tkn.lexeme,"-")==0){
		addop();
		term();
		seprime();
	}else{
		return;
	}
	
}


void declarations(){

	dataType();
	identifierList();
	if(strcmp(tkn.lexeme,";")==0){
		tkn = getNextToken(fin);
		if(strcmp(tkn.type,"Identifier")!=0)
		declarations();

		return;
	}else{
		printf("\n ; expected");
		exit(0);
	}
	return;
}
void dataType(){

	if(strcmp(tkn.lexeme,"int")==0){
		tkn = getNextToken(fin);
		return;
	}
	else if(strcmp(tkn.lexeme,"char")==0){
		tkn = getNextToken(fin);
		return;
	}
	else{
		printf("\n dataType expected");
		exit(0);
	}
}

void identifierList(){
	if(strcmp(tkn.type,"Identifier")==0)
	{
		tkn = getNextToken(fin);
		if(strcmp(tkn.lexeme,",")==0)
		{
			tkn = getNextToken(fin);
			identifierList();
		}
		else if(strcmp(tkn.lexeme,"[")==0)
		{
			tkn = getNextToken(fin);
			if(strcmp(tkn.type,"Number")==0)
			{
				tkn = getNextToken(fin);
				if(strcmp(tkn.lexeme,"]")==0)
				{
					tkn = getNextToken(fin);
					if(strcmp(tkn.lexeme,",")==0)
					{
						tkn = getNextToken(fin);
						identifierList();
					}
					else
					{
						return;
					}
				}
			}
		}
		else
		{
			return;
		}
		
	}else{
		printf("Identifier expected");
		exit(0);
	}
}

void assign_stat(){
    printf("\n <%s %s>",tkn.lexeme,tkn.type);

	if(strcmp(tkn.type,"Identifier")==0){
		tkn = getNextToken(fin);
		if(strcmp(tkn.lexeme,"=")==0){
			tkn = getNextToken(fin);
			expn();
			
		}else{
			printf(" = expected!");
			exit(0);
		}
	}else{
		printf(" ID expected!");
		exit(0);
	}

}


int main(){
	fin = fopen("input.c", "r");
    if (!fin)
    {
        printf("Error! File cannot be opened.\n");
        return 0;
    }

	tkn = getNextToken(fin);
	program();
    printf("\n final<%s %s>",tkn.lexeme,tkn.type);

	return 0;
}