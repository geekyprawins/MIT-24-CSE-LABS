#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define FILEINPUT "input.c"
struct token
{
    char lexeme[64];
    int row, col;
    char type[20];
};
static int row = 1, col = 1;
char buf[024];
const char specialsymbols[] = {'?', ';', ':', ','};
const char *Keywords[] = {"const", "char", "int", "return", "for", "while", "do", "switch", "if", "else", "unsigned", "case", "break"};
const char arithmeticsymbols[] = {'*','+','-','/'};
int isKeyword(const char *str)
{
    for (int i = 0; i < sizeof(Keywords) / sizeof(char *); i++)
    {
        if (strcmp(str, Keywords[i]) == 0)
            return 1;
    }
    return 0;
}
int charBelongsTo(int c, const char *arr)
{
    int len;
    if (arr == specialsymbols)
        len = sizeof(specialsymbols) / sizeof(char);
    else if (arr == arithmeticsymbols)
        len = sizeof(arithmeticsymbols) / sizeof(char);
    for (int i = 0; i < len; i++)
    {
        if (c == arr[i])
            return 1;
    }
    return 0;
}
void fillToken(struct token *tkn, char c, int row, int col, char *type)
{
    tkn->row = row;
    tkn->col = col;
    strcpy(tkn->type, type);
    tkn->lexeme[0] = c;
    tkn->lexeme[1] = '\0';
}
void newLine()
{
    ++row;
    col = 1;
}
struct token getNextToken(FILE *fin)
{
    int c;
    struct token tkn = {.row = -1};
    int gotToken = 0;
    while (!gotToken && (c = fgetc(fin)) != EOF)
    {
        if (charBelongsTo(c, specialsymbols))
        {
            switch(c){
                case ';':
                
                    fillToken(&tkn, c, row, col, ";");
                    break;
                case ':':
                
                    fillToken(&tkn, c, row, col, ":");
                    break;
                case '?':
                
                    fillToken(&tkn, c, row, col, "?");
                    break;
                case ',':
                
                    fillToken(&tkn, c, row, col, ",");
                    break;
                default : break;
                
            }
            // fillToken(&tkn, c, row, col,"SS");
            gotToken = 1;
            ++col;
        }
        else if (charBelongsTo(c, arithmeticsymbols))

        { 
            switch(c){
                case '+':
                
                    fillToken(&tkn, c, row, col, "+");
                    break;
                case '-':
                
                    fillToken(&tkn, c, row, col, "-");
                    break;
                case '*':
                
                    fillToken(&tkn, c, row, col, "*");
                    break;
                case '/':
                
                    fillToken(&tkn, c, row, col, "/");
                    break;
                default : break;
                
            }
            // fillToken(&tkn, c, row, col, "ArithmeticOperator");
            gotToken = 1;
            ++col;
        }
        else if (c == '(')
        {
            fillToken(&tkn, c, row, col, "(");
            gotToken = 1;
            ++col;
        }
        else if (c == ')')
        {
            fillToken(&tkn, c, row, col, ")");
            gotToken = 1;
            ++col;
        }
        else if (c == '{')
        {
            fillToken(&tkn, c, row, col, "{");
            gotToken = 1;
            ++col;
        }
        else if (c == '}')
        {
            fillToken(&tkn, c, row, col, "}");
            gotToken = 1;
            ++col;
        }
        else if (c == '+')
        {
            int d = fgetc(fin);
            if (d != '+')
            {
                fillToken(&tkn, c, row, col, "+");
                gotToken = 1;
                ++col;
                fseek(fin, -1, SEEK_CUR);
            }
            else
            {
                fillToken(&tkn, c, row, col, "++");
                strcpy(tkn.lexeme, "++");
                gotToken = 1;
                col += 2;
            }
        }
        else if (c == '-')
        {
            int d = fgetc(fin);
            if (d != '-')
            {
                fillToken(&tkn, c, row, col, "-");
                gotToken = 1;
                ++col;
                fseek(fin, -1, SEEK_CUR);
            }
            else
            {
                fillToken(&tkn, c, row, col, "--");
                strcpy(tkn.lexeme, "--");
                gotToken = 1;
                col += 2;
            }
        }
        else if (c == '=')
        {
            int d = fgetc(fin);
            if (d != '=')
            {
                fillToken(&tkn, c, row, col, "=");
                gotToken = 1;
                ++col;
                fseek(fin, -1, SEEK_CUR);
            }
            else
            {
                fillToken(&tkn, c, row, col, "==");
                strcpy(tkn.lexeme, "==");
                gotToken = 1;
                col += 2;
            }
        }
        else if (isdigit(c))
        {
            tkn.row = row;
            tkn.col = col++;
            tkn.lexeme[0] = c;
            int k = 1;
            while ((c = fgetc(fin)) != EOF && isdigit(c))
            {
                tkn.lexeme[k++] = c;
                col++;
            }
            tkn.lexeme[k] = '\0';
            strcpy(tkn.type, "Number");
            gotToken = 1;
            fseek(fin, -1, SEEK_CUR);
        }
        else if (c == '#')
        {
            while ((c = fgetc(fin)) != EOF && c != '\n')
                ;
            newLine();
        }
        else if (c == '\n')
        {
            newLine();
            c = fgetc(fin);
            if (c == '#')
            {
                while ((c = fgetc(fin)) != EOF && c != '\n')
                    ;
                newLine();
            }
            else if (c != EOF)
                fseek(fin, -1, SEEK_CUR);
        }
        else if (isspace(c))
            ++col;
        else if (isalpha(c) || c == '_')
        {
            tkn.row = row;
            tkn.col = col++;
            tkn.lexeme[0] = c;
            int k = 1;
            while ((c = fgetc(fin)) != EOF && isalnum(c))
            {
                tkn.lexeme[k++] = c;
                ++col;
            }
            tkn.lexeme[k] = '\0';
            if (isKeyword(tkn.lexeme))
                strcpy(tkn.type, "Keyword");
            else
                strcpy(tkn.type, "Identifier");
            gotToken = 1;
            fseek(fin, -1, SEEK_CUR);
        }
        else if (c == '/')
        {
            int d = fgetc(fin);
            ++col;
            if (d == '/')
            {
                while ((c = fgetc(fin)) != EOF && c != '\n')
                    ++col;
                if (c == '\n')
                    newLine();
            }
            else if (d == '*')
            {
                do
                {
                    if (d == '\n')
                        newLine();
                    while ((c == fgetc(fin)) != EOF && c != '*')
                    {
                        ++col;
                        if (c == '\n')
                            newLine();
                    }
                    ++col;
                } while ((d == fgetc(fin)) != EOF && d != '/' && (++col));
                ++col;
            }
            else
            {
                fillToken(&tkn, c, row, --col, "/");
                gotToken = 1;
                fseek(fin, -1, SEEK_CUR);
            }
        }
        else if (c == '"')
        {
            tkn.row = row;
            tkn.col = col;
            strcpy(tkn.type, "StringLiteral");
            int k = 1;
            tkn.lexeme[0] = '"';
            while ((c = fgetc(fin)) != EOF && c != '"')
            {
                tkn.lexeme[k++] = c;
                ++col;
            }
            tkn.lexeme[k] = '"';
            gotToken = 1;
        }
        else if (c == '<' || c == '>' || c == '!')
        {
            switch(c){
                case '>':
                
                    fillToken(&tkn, c, row, col, ">");
                    break;
                case '<':
                
                    fillToken(&tkn, c, row, col, "<");
                    break;
                case '!':
                
                    fillToken(&tkn, c, row, col, "!");
                    break;
                default : break;
                
            }
            // fillToken(&tkn, c, row, col, "RelationalOperator");
            ++col;
            int d = fgetc(fin);
            if (d == '=')
            {
                ++col;
                strcat(tkn.lexeme, "=");
            }
            else
            {
                if (c == '!')
                    strcpy(tkn.type, "!=");
                fseek(fin, -1, SEEK_CUR);
            }
            gotToken = 1;
        }
        else if (c == '&' || c == '|')
        {
            int d = fgetc(fin);
            if (c == d)
            {
                tkn.lexeme[0] = tkn.lexeme[1] = c;
                tkn.lexeme[2] = '\0';
                tkn.row = row;
                tkn.col = col;
                ++col;
                gotToken = 1;
                switch(c){
                case '&':
                
                    fillToken(&tkn, c, row, col, "&&");
                    break;
                case '|':
                
                    fillToken(&tkn, c, row, col, "||");
                    break;
                default : break;
                
            }
                // strcpy(tkn.type, "LogicalOperator");
            }
            else
                fseek(fin, -1, SEEK_CUR);
            ++col;
        }
        else
            ++col;
    }
    return tkn;
}
int main()
{
    FILE *fin = fopen("input.c", "r");
    if (!fin)
    {
        printf("Error! File cannot be opened!\n");
        return 0;
    }
    struct token tkn;
    while ((tkn = getNextToken(fin)).row != -1)
        printf( "<%s, %d, %d>\n", tkn.type, tkn.row, tkn.col);
    fclose(fin);
}