#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getNextToken.h"

struct node{
    char lexeme[20];
    struct node* next;
};


struct entry{

    char lexeme[20];
    char dtype[10];
    char rtype[10];
    int size;

};

const char *Datatypes[] = {"int", "char", "float"};
const char *Predef[] = {"printf"};
struct entry symbolTable[100];
int entryCount = 0;


unsigned long hash(unsigned char *str){

        unsigned long hash = 5381;
        int c;

        while (c = *str++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return (hash%100);
}

struct node* HashMap[100] = {NULL};



void insert(char* str){

    int hashVal = hash(str);
    struct node* temp = (struct node*) malloc(sizeof(struct node));
    strcpy(temp->lexeme, str);

    if (HashMap[hashVal] == NULL){
        HashMap[hashVal] = temp;
    }

    else{
        HashMap[hashVal]->next = temp;
    }

}



int search(char* str){
    int hashVal = hash(str);

    struct node* temp = HashMap[hashVal];

    while(temp != NULL){
        if (strcmp(temp->lexeme, str) == 0){
            return 1;
        }

        temp = temp->next;
    }
    return 0;
}


int retSize(char* str){

    if (strcmp(str, "int") == 0){
        return 4;
    }

    else if (strcmp(str, "char") == 0){
        return 1;
    }

    else{
        return 0;
    }
}

int isDtype(const char *str)
{
    for (int i = 0; i < sizeof(Datatypes) / sizeof(char *); i++)
    {
        if (strcmp(str, Datatypes[i]) == 0)
            return 1;
    }
    return 0;
}

int notPreDefined(char* str){
    for (int i = 0; i < sizeof(Predef) / sizeof(char *); i++)
    {
        if (strcmp(str, Predef[i]) == 0)
            return 0;
    }
    return 1;
}

int main()
{
    FILE *fin = fopen("input.txt", "r");
    if (!fin)
    {
        printf("Error! File cannot be opened!\n");
        return 0;
    }
    struct token tkn;
    struct token nxt;

    char dbuf[10] = "hi";

    while ((tkn = getNextToken(fin)).row != -1){
        printf("<%s, %d, %d>\n", tkn.type, tkn.row, tkn.col);

        if (strcmp(tkn.type, "Identifier") == 0 && notPreDefined(tkn.lexeme)){
            
            if (search(tkn.lexeme) == 0){
                struct entry tuple;
                strcpy(tuple.dtype, dbuf);
                strcpy(tuple.rtype, "NULL");
                strcpy(tuple.lexeme, tkn.lexeme);
                tuple.size = retSize(dbuf);
                if ((nxt = getNextToken(fin)).row != -1){
                    if (strcmp(nxt.lexeme, "(") == 0){
                        strcpy(tuple.dtype,"FUNC");
                        strcpy(tuple.rtype, dbuf);
                        tuple.size = 0;
                    }

                }  
                symbolTable[entryCount++] = tuple;
                insert(tuple.lexeme);
            }
            
            
        }

        else if (strcmp(tkn.type, "Keyword") == 0){
            if (isDtype(tkn.lexeme) == 0){
                strcpy(dbuf, "Void");
            }
            else{
                strcpy(dbuf, tkn.lexeme);
            }
        }    
    }

    printf("\n\nSymbol Table\n\n");
    printf("Lexeme\t\tDtype\t\tRtype\t\tSize\n");
    for (int i=0 ;i<entryCount; i++){
        printf("%s\t\t%s\t\t%s\t\t%d \n", symbolTable[i].lexeme, symbolTable[i].dtype, symbolTable[i].rtype, symbolTable[i].size );  //, symbolTable[i].size);

    }
    fclose(fin);
    return 0;
}


