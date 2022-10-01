#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int row = 1, column = 1;
int symboltableindex=-1;
int lexemeindex=0;
char buff[80];
char dbuf[80]="int";
struct Token
{
	char *token_name;
	int index;
	int row,col; //Line numbers.
	char *type;
};

struct Node
{
char lexeme[20];
int size;
char type[50];
}symboltable[10][100];

char symboltablename[10][100];
int symboltablesize[10];
const char *keywords[] = {
    "auto",
    "break",
    "case",
    "char",
    "continue",
    "do",
    "default",
    "const",
    "double",
    "else",
    "enum",
    "extern",
    "for",
    "if",
    "include",
    "goto",
    "float",
    "int",
    "long",
    "register",
    "return",
    "signed",
    "static",
    "sizeof",
    "short",
    "struct",
    "switch",
    "typedef",
    "union",
    "void",
    "while",
    "volatile",
    "unsigned",
    "printf",
    "scanf",
    "bool",
    "main"
};
const char *dataTypes[] = {
	"int","void","char","float","bool"
};

const char specialsymbols[]={'?',';',':',',', '(', ')', '[', ']', '{', '}'};

int isKeyword(char* id) {
	for(int i = 0; i < sizeof(keywords)/sizeof(char*); i++) {
		if(strcmp(id, keywords[i]) == 0)
			return 1;
	}
	return 0;
}

int isDataType(char* id) {
	for(int i = 0; i < sizeof(dataTypes)/sizeof(char*); i++) {
		if(strcmp(id, dataTypes[i]) == 0)
			return 1;
	}
	return 0;
}

int isspecialSymbol(char id) {
	for(int i = 0; i < sizeof(specialsymbols)/sizeof(char); i++) {
		if(id == specialsymbols[i])
			return 1;
	}
	return 0;
}

int isAlpha(char in) {
	if((in >= (int)('A') && in <= (int)('Z')) || (in >= (int)('a') && in <= (int)('z')) )
		return 1;
	return 0;
}

int isDigit(char in) {
	if((in >= (int)('0') && in <= (int)('9')))
		return 1;
	return 0;
}

void printToken(struct Token tk)
{
	printf("< %s , %d , %d >\n", tk.token_name, tk.row, tk.col);
}

void fillToken(struct Token* tok, char* token_name, int row, int column) {
	tok->token_name = token_name;
	tok->row = row;
	tok->col = column;
}

void printLexeme(int i, int j)
{	
	printf(" %d \t",j+1);
	printf(" %s \t\t",symboltable[i][j].lexeme);
	printf(" %s \t",symboltable[i][j].type);
	printf(" %d \n",symboltable[i][j].size);
}
void printSymbolTable()
{
	int i,j;
	for(i=0;i<=symboltableindex;i++)
	{
		printf("------------------------------------------------------------\n");
		printf("Symbol Table for %s:\n", symboltablename[i]);
		printf("   \t Lexeme_name \t Type \t Size \n");
		for(j=0;j<symboltablesize[i];j++)
		{
			printLexeme(i,j);
		}
	}
}

void createSymbolTable(char *buf)
{
	symboltableindex++;
	lexemeindex=0;
	strcpy(symboltablename[symboltableindex],buf);
	// printf("Symbol table index%d\n",symboltableindex);
	// printf("Lexeme index%d\n",lexemeindex);
}

int searchSymbolTable(char *buf)
{
	int i;
	for(i=0;i<lexemeindex;i++)
	{
		if(strcmp(symboltable[symboltableindex][i].lexeme,buf)==0)
			return 1;
	}
	return 0;
}
void insertSymbolTable(char *buff,char *dbuf,FILE *fp){
	int arrayMultiplier=1;
	int arrayLength=0;
	if(searchSymbolTable(buff))return;
	else{
		//bringing the pointer one back to read whether it is an aray or function
		//fseek(fp,-1,SEEK_CUR);
		char c=fgetc(fp);
		fseek(fp,-1,SEEK_CUR);
		// printf("%c",c);
		if(c=='(')
		{
			if(strcmp(dbuf,"none")!=0)
				createSymbolTable(buff);
			else{
				strcpy(symboltable[symboltableindex][lexemeindex].lexeme,buff);
				symboltable[symboltableindex][lexemeindex].size = -1;
				strcpy(symboltable[symboltableindex][lexemeindex].type,"Func");
				lexemeindex++;
				symboltablesize[symboltableindex]=lexemeindex;
			}
		}
		else{
			if(c=='[')
			{
				c=fgetc(fp);
				while(c!=']'){
					//converting char digit to single digit
					arrayLength=arrayLength+((int)c-48)*10;
					c=fgetc(fp);
				}
				arrayMultiplier=arrayLength;
			}
			strcpy(symboltable[symboltableindex][lexemeindex].lexeme,buff);
			int sizeDataType=0;
			if(strcmp(dbuf,"int")==0){
				sizeDataType=4;
			}else if(strcmp(dbuf,"char")==0){
				sizeDataType=1;
			}else if(strcmp(dbuf,"float")==0){
				sizeDataType=8;
			}else if(strcmp(dbuf,"bool")==0){
				sizeDataType=1;
			}
			symboltable[symboltableindex][lexemeindex].size = sizeDataType*arrayMultiplier;
			strcpy(symboltable[symboltableindex][lexemeindex].type,dbuf);
			lexemeindex++;
			symboltablesize[symboltableindex]=lexemeindex;
		}
	}
}

struct Token getNextToken(FILE* fp) {
	int k = 0;
	char c = fgetc(fp);
	struct Token tok;
	while (c != EOF) {
		// if(c==EOF)
  //       {
  //       	strcpy(tok.token_name,"eof");
  //       	tok.row=row;
  //       	tok.col=column;
  //       	return(tok);
  //       }
		if (c == '#') {
			buff[0] = '\0';
			int k = 0;
			c = fgetc(fp);

			while(isAlpha(c))
			{
				buff[k++] = c;
				c = fgetc(fp);
			}
			fseek(fp, -1, SEEK_CUR);
			buff[k]='\0';	
			if(strcmp(buff,"include") == 0 || strcmp(buff,"define") == 0)
			{
				c = fgetc(fp);
				while(c != '\n') {
					c = fgetc(fp);
				} 
				row++;
				column = 0;
				c = fgetc(fp);
				continue;
			}
			fillToken(&tok, "#", row, column);
			column++;
			return tok;
		}
		// Remove comments
		if(c == '/') {
			c = fgetc(fp);
			int k = 0;
			column++;
			if(c == '/') {
				while(c != '\n') 
					c = fgetc(fp);
				row++;
				column = 0;
				c = fgetc(fp);
				continue;
			}
			else if (c == '*') {
				do {
					while(c != '*') {
						if(c == '\n') {
							row++;
							column = 0;
						}
						else {
							column++;
						}
						c = fgetc(fp);
					}
					if(c == '\n') {
						row++;
						column = 0;
					}
					else {
						column++;
					}
					c = fgetc(fp);
				} while(c != '/');
			}
		}
		buff[0] = '\0';
		if(c == '=')
		{
			c = fgetc(fp);
			if(c == '=') {
				fillToken(&tok, "==", row, column);
				column += 2;
			}
			else {
				fillToken(&tok, "=", row, column);
				column++;
				fseek(fp, -1, SEEK_CUR);
			}
			return tok;
		}
		else if(c == '<') {
			c = fgetc(fp);
			if(c == '=') {
				fillToken(&tok, "<=", row, column);
				column += 2;
			}
			else {
				fillToken(&tok, "<", row, column);
				column++;
				fseek(fp, -1, SEEK_CUR);
			}
			return tok;
		}
		else if(c == '>') {
			c = fgetc(fp);
			if(c == '=') {
				fillToken(&tok, ">=", row, column);
				column += 2;
			}
			else {
				fillToken(&tok, ">", row, column);
				column++;
				fseek(fp, -1, SEEK_CUR);
			}
			return tok;
		}
		else if(c == '!') {
			c = fgetc(fp);
			if(c == '=') {
				fillToken(&tok, "!=", row, column);
				column += 2;
			}
			else {
				fillToken(&tok, "!", row, column);
				column++;
				fseek(fp, -1, SEEK_CUR);
			}
			return tok;
		}
		else if(c == '&') {
			c = fgetc(fp);
			if(c == '&') {
				fillToken(&tok, "&&", row, column);
				column += 2;
			}
			else {
				fillToken(&tok, "&", row, column);
				column++;
				fseek(fp, -1, SEEK_CUR);
			}
			return tok;
		}
		else if(c == '|') {
			c = fgetc(fp);
			if(c == '|') {
				fillToken(&tok, "||", row, column);
				column += 2;
			}
			else {
				fillToken(&tok, "|", row, column);
				column++;
				fseek(fp, -1, SEEK_CUR);
			}
			return tok;
		}
		else if(isspecialSymbol(c)) {
			buff[0] = c;
			buff[1] = '\0';
			fillToken(&tok, buff, row, column);
			column++;
			if(buff[0]==';')strcpy(dbuf,"int");
			return tok;
		}
		else if(c == '+') {
			c = fgetc(fp);
			if(c == '+') {
				fillToken(&tok, "++", row, column);
				column += 2;
			}
			else if(c == '=') {
				fillToken(&tok, "+=", row, column);
				column += 2;
			}
			else {
				fillToken(&tok, "+", row, column);
				column++;
				fseek(fp, -1, SEEK_CUR);
			}
			return tok;
		}
		else if(c == '-') {
			c = fgetc(fp);
			if(c == '-') {
				fillToken(&tok, "--", row, column);
				column += 2;
			}
			else if(c == '=') {
				fillToken(&tok, "-=", row, column);
				column += 2;
			}
			else {
				fillToken(&tok, "-", row, column);
				column++;
				fseek(fp, -1, SEEK_CUR);
			}
			return tok;
		}
		else if(c == '*') {
			c = fgetc(fp);
			if(c == '=') {
				fillToken(&tok, "*=", row, column);
				column += 2;
			}
			else {
				fillToken(&tok, "*", row, column);
				column++;
				fseek(fp, -1, SEEK_CUR);
			}
			return tok;
		}
		else if(c == '/') {
			c = fgetc(fp);
			if(c == '=') {
				fillToken(&tok, "=/", row, column);
				column += 2;
			}
			else {
				fillToken(&tok, "/", row, column);
				column++;
				fseek(fp, -1, SEEK_CUR);
			}
			return tok;
		}
		else if(isAlpha(c)) {
			// printf("%c",c);
			int k = 0;
			do {
				buff[k++] = c;
				c = fgetc(fp);
				// printf("%c",c);
			} while(isAlpha(c) || isDigit(c) || c == '_');
			// printf("%c",c);
			fseek(fp, -1, SEEK_CUR);
			buff[k] = '\0';		
			// printf("WORD %s\n", id);
			if(isKeyword(buff)) {
				fillToken(&tok, buff, row, column);
				if(isDataType(buff)){
					// printf("%s",dbuf);
					// printf("is a datatype\n");
					// dbuf[0]='\0';
					// printf("Changing dbuf %s",buff);
					strcpy(dbuf,buff);
					// printf("%s",dbuf);
				}
				//For symbol table
				//if(strcmp("main",buff)==0)insertSymbolTable(buff,dbuf,fp);
			} 
			else {
				// printf("I was here %s",buff);
				fillToken(&tok, "id", row, column);
				//For symbol table
				//insertSymbolTable(buff,dbuf,fp);
			}
			column += k;
			return tok;
		}
		else if(c == '\"') {
			int k = 0;
			buff[k++] = c;
			do {
				c = getc(fp);
				buff[k++] = c;
			} while((char)c != '\"');
			buff[k] = '\0';
			fillToken(&tok, buff, row, column);
			column += k;
			return tok;
		}
		else if(isDigit(c)) {
			int k = 0;
			do {
				buff[k++] = c;
				c = getc(fp);
			} while(isDigit(c));
			buff[k] = '\0';
			fillToken(&tok, "num", row, column);
			fseek(fp, -1, SEEK_CUR);
			column += k;
			return tok;
		}
		else {
			if(c != '\n') {
				column++;
			}
			else {
				row++;
				column = 1;
			}
		}
		c = fgetc(fp);
		// printf("%c\n",c);
	}
	tok.row = -1;
	return tok;
}

// int main(int argc, char const *argv[]) {
// 	FILE *fa;
// 	char c;
// 	fa = fopen(argv[1], "r");

// 	if(fa == NULL) {
// 		printf("Cannot open file\n");
// 		exit(0);
// 	}

// 	do {
// 		struct Token tok = getNextToken(fa);
// 				if(tok.row == -1)
// 			break;
// 		printToken(tok);
// 		// c=fgetc(fa);
// 		// fseek(fa, -1, SEEK_CUR);
// 		// printf("%c going for the second token \n",c);
// 	} while (1);
// 	printf("\n");
// 	printSymbolTable();
// 	fclose(fa);
// 	return 0;
// }