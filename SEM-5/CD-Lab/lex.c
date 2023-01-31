#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *dtype[] = {"int", "char", "float", "void"};

int entryCounter = 0;
char dbuf[20] = "void";
int row = 1;
int col = 1;
 
int isDtype(char *str)
{
    int l = sizeof(dtype) / sizeof(char *);
    for (int i = 0; i < l; i++)
    {
        if (strcmp(str, dtype[i]) == 0)
        {
            return 1;
        }
    }

    return 0;
}

int retSize(char *str)
{
    if (strcmp(str, "int") == 0)
    {
        return 4;
    }

    else if (strcmp(str, "char") == 0)
    {
        return 1;
    }

    return 0;
}

struct token
{
    char lexeme[50];
    char type[50];
    int row;
    int col;
};

struct entry
{
    char lexeme[50];
    char type[50];
    char rtype[50];

    int size;
};

struct entry symbolTable[100];

int search(char *str)
{
    for (int i = 0; i < entryCounter; i++)
    {
        if (strcmp(symbolTable[i].lexeme, str) == 0)
        {
            return 1;
        }
    }
    return 0;
}

char *keyword[] = {"int", "main", "printf", "char", "return"};

int isKeyword(char *str)
{
    int l = sizeof(keyword) / sizeof(keyword[0]);

    for (int i = 0; i < l; i++)
    {
        if (strcmp(str, keyword[i]) == 0)
        {
            return 1;
        }
    }

    return 0;
}

struct token getNextToken(FILE *fin)
{
    struct token tkn = {.row = -1};

    int gotToken = 0;
    char c;

    while (!gotToken && (c = fgetc(fin)) != EOF)
    {

        if (isalpha(c) != 0)
        {
            int iter = 0;
            while (isalpha(c) != 0)
            {
                tkn.lexeme[iter++] = c;
                c = fgetc(fin);
            }

            tkn.lexeme[iter] = '\0';

            if (isKeyword(tkn.lexeme))
            {
                strcpy(tkn.type, "KEYWORD");
            }

            else
            {
                strcpy(tkn.type, "IDENTIFIER");
            }

            tkn.col = col;
            tkn.row = row;
            col += strlen(tkn.lexeme);
            gotToken = 1;
            fseek(fin, -1, SEEK_CUR);
        }

        else if (c == '#')
        {
            while (c != '\n')
            {
                c = fgetc(fin);
            }

            fseek(fin, -1, SEEK_CUR);
        }

        else if (c == '/')
        {
            char ch = fgetc(fin);
            if (ch == '/')
            {
                while (c != '\n')
                {
                    c = fgetc(fin);
                }

                fseek(fin, -1, SEEK_CUR);
            }

            else if (ch == '*')
            {
                do
                {
                    while ((c = fgetc(fin)) != EOF && c != '*')
                    {
                        col += 1;
                        if (c == '\n')
                        {
                            row += 1;
                            col = 1;
                        }
                    }
                    col += 1;
                } while ((ch = fgetc(fin)) != EOF && ch != '/' && (col++));
            }

            else
            {
                fseek(fin, -1, SEEK_CUR);
            }
        }

        else if (c == '(')
        {
            tkn.lexeme[0] = '(';
            tkn.lexeme[1] = '\0';
            strcpy(tkn.type, "OPEN PARANTHESIS");
            col += 1;
            tkn.col = col;
            tkn.row = row;
            gotToken = 1;
        }

        else if (c == '\n')
        {
            row += 1;
            col = 1;
        }

        else if (c == ' ')
        {
            col += 1;
        }

        else if (c == ',')
        {
            tkn.lexeme[0] = ',';
            tkn.lexeme[1] = '\0';
            strcpy(tkn.type, "COMMA");
            col += 1;
            tkn.col = col;
            tkn.row = row;
            gotToken = 1;
        }

        else if (c == '=')
        {
            tkn.lexeme[0] = '=';
            tkn.lexeme[1] = '\0';
            strcpy(tkn.type, "ASS");
            col += 1;
            tkn.col = col;
            tkn.row = row;
            gotToken = 1;
        }

        else if (c == ')')
        {
            tkn.lexeme[0] = ')';
            tkn.lexeme[1] = '\0';
            strcpy(tkn.type, "CLOSE PARANTHESIS");
            col += 1;
            tkn.col = col;
            tkn.row = row;
            gotToken = 1;
        }

        else if (c == '{')
        {
            tkn.lexeme[0] = '{';
            tkn.lexeme[1] = '\0';
            strcpy(tkn.type, "OPEN BRACKET");
            col += 1;
            tkn.col = col;
            tkn.row = row;
            gotToken = 1;
        }

        else if (c == '}')
        {
            tkn.lexeme[0] = '}';
            tkn.lexeme[1] = '\0';
            strcpy(tkn.type, "CLOSE BRACKET");
            col += 1;
            tkn.col = col;
            tkn.row = row;
            gotToken = 1;
        }

        else if (c == ';')
        {
            tkn.lexeme[0] = ';';
            tkn.lexeme[1] = '\0';
            strcpy(tkn.type, "SEMIcolON");
            col += 1;
            tkn.col = col;
            tkn.row = row;
            gotToken = 1;
        }

        else if (c == '"')
        {
            int iter = 0;
            tkn.lexeme[iter++] = c;
            c = fgetc(fin);

            while (c != '"')
            {
                tkn.lexeme[iter++] = c;
                c = fgetc(fin);
            }

            tkn.lexeme[iter++] = c;
            tkn.lexeme[iter] = '\0';

            strcpy(tkn.type, "STRING LITERAL");
            col += 1;
            tkn.col = col;
            tkn.row = row;

            gotToken = 1;
        }
    }

    return tkn;
}

void createSymbolTable(FILE *fin)
{
    struct token tkn;
    while ((tkn = getNextToken(fin)).row != -1)
    {

        if (strcmp(tkn.type, "KEYWORD") == 0)
        {

            if (isDtype(tkn.lexeme) == 1)
            {
                strcpy(dbuf, tkn.lexeme);
            }

            else
            {
                strcpy(dbuf, "void");
            }
        }

        else if (strcmp(tkn.type, "IDENTIFIER") == 0)
        {

            if (search(tkn.lexeme) == 0)
            {

                struct entry tuple;
                struct token nxt = getNextToken(fin);

                if (strcmp(nxt.lexeme, "(") == 0)
                {
                    strcpy(tuple.lexeme, tkn.lexeme);
                    strcpy(tuple.rtype, dbuf);
                    strcpy(tuple.type, "FUNC");
                    tuple.size = 0;
                }

                else
                {

                    int size = retSize(dbuf);
                    strcpy(tuple.type, dbuf);
                    strcpy(tuple.lexeme, tkn.lexeme);
                    strcpy(tuple.rtype, "NULL");
                    tuple.size = size;
                }

                symbolTable[entryCounter++] = tuple;
            }
        }
    }

    row = 1;
    col = 1;
    fseek(fin, 0, SEEK_SET);
}

void printSymbolTable()
{
    printf("lexeme\tdatatype\treturn type\tsize \n");
    for (int i = 0; i < entryCounter; i++)
    {
        printf("%s\t%s\t%s\t%d \n", symbolTable[i].lexeme, symbolTable[i].type, symbolTable[i].rtype, symbolTable[i].size);
    }
}

void printToken(FILE *fin)
{
    struct token tkn;
    while ((tkn = getNextToken(fin)).row != -1)
    {
        printf("<%s, %s, %d, %d> \n", tkn.lexeme, tkn.type, tkn.row, tkn.col);
    }

    fseek(fin, 0, SEEK_SET);
}

int main()
{

    FILE *fin = fopen("test.txt", "r");

    createSymbolTable(fin);
    printSymbolTable();

    struct token tkn;
    while ((tkn = getNextToken(fin)).row != -1)
    {

        printf("<%s, %s, %d, %d> \n", tkn.lexeme, tkn.type, tkn.row, tkn.col);
    }

    return 0;
}