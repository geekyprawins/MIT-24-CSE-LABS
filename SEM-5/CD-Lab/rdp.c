#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lex.c"


struct token tkn;
 
FILE* fin;

void program();
void declarations();
int data_type();
void identifier_list();
void identifier_listprime();
void assign_stat();
void assign_statprime();

void valid(){
    printf("----SUCCESS------");
    exit(0);
}


void invalid(){
    printf("Error at line no: %d, column: %d", tkn.row, tkn.col);
    exit(0);
}



void program(){
    tkn = getNextToken(fin);
    if (strcmp(tkn.lexeme, "int") == 0){
        tkn = getNextToken(fin);
        if (strcmp(tkn.lexeme, "main") == 0){
            tkn = getNextToken(fin);
            if (strcmp(tkn.lexeme, "(") == 0){
                tkn = getNextToken(fin);
                if (strcmp(tkn.lexeme, ")") == 0){
                    tkn = getNextToken(fin);
                    if (strcmp(tkn.lexeme, "{") == 0){
                        tkn = getNextToken(fin);
                        declarations();
                        assign_stat();

                        tkn = getNextToken(fin);
                        if (strcmp(tkn.lexeme, "}") == 0){
                            valid();
                        }

                        else{
                            
                            invalid();
                        }

                    }

                    else{
                        
                        invalid();
                    }
                }

                else{
                  
                    invalid();
                }
            }

            else{
               
                invalid();
            }
        }

        else{
         
            invalid();
        }

    }

    else{
     
        invalid();
    }

}


void declarations(){

    if (data_type()){
        tkn = getNextToken(fin);
        identifier_list();
        if (strcmp(tkn.lexeme, ";") == 0){
            tkn = getNextToken(fin);
            declarations();
        }

        else{
            printf("Semicolon Missing\n");
            invalid();
        }
        
    }
}

void identifier_list(){
    if (strcmp(tkn.type, "IDENTIFIER") == 0){
        tkn = getNextToken(fin);
        identifier_listprime();
    }

    else{
        printf("Missing Identifier\n");
        invalid();
    }
}

void identifier_listprime(){
    if (strcmp(tkn.lexeme, ",") == 0){
        tkn = getNextToken(fin);
        identifier_list();
    }
}



int data_type(){
    if (strcmp(tkn.lexeme,"int") == 0 || strcmp(tkn.lexeme, "char") == 0){
        return 1;
    }
    return 0;
}

void assign_stat(){

    if (strcmp(tkn.type, "IDENTIFIER") == 0){
        tkn = getNextToken(fin);
        if (strcmp(tkn.lexeme, "=") == 0){
            
            tkn = getNextToken(fin);
            assign_statprime();
        }

        else{
            invalid();
        }
    }

    else{
        invalid();
    }
}

void assign_statprime(){
    if (strcmp(tkn.type, "IDENTIFIER") == 0 || strcmp(tkn.type, "NUMBER")== 0){
        tkn = getNextToken(fin);
        if (strcmp(tkn.lexeme, ";") == 0){
            return;
        }

        else{
            invalid();
        }
    }
}



int main(){
    fin = fopen("test.txt", "r");
    
    createSymbolTable(fin);
    printSymbolTable();
    printToken(fin);
    program();
    

    return 0;


}