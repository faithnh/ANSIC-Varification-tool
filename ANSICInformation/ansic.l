D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
P                       [Pp][+-]?{D}+
FS			(f|F|l|L)
IS                      ((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))


%{
#include <stdio.h>
#include <string.h>
#include "AST.h"
#include "Synbol.h"
#include "../Library/CSTLString.h"
#include "y.tab.h"

int column = 0;
int line = 1;
TYPEDEF_TABLE_LIST *typedef_table_list;
STRUCT_TABLE_LIST *struct_table_list;
VARIABLE_TABLE_LIST *variable_table_list;
void comment(void);
void count(void);
%}

%%
"/*"			{ comment(); }
"//"[^\n]*              { /* consume //-comment */ }


"auto"			{yylval.val = same_new_AST(yytext,line); count(); return(AUTO); }
"_Bool"			{yylval.val = same_new_AST(yytext,line); count(); return(BOOL); }
"break"			{yylval.val = same_new_AST(yytext,line); count(); return(BREAK); }
"case"			{yylval.val = same_new_AST(yytext,line); count(); return(CASE); }
"char"			{yylval.val = same_new_AST(yytext,line); count(); return(CHAR); }
"_Complex"		{yylval.val = same_new_AST(yytext,line); count(); return(COMPLEX); }
"const"			{yylval.val = same_new_AST(yytext,line); count(); return(CONST); }
"continue"		{yylval.val = same_new_AST(yytext,line); count(); return(CONTINUE); }
"default"		{yylval.val = same_new_AST(yytext,line); count(); return(DEFAULT); }
"do"			{yylval.val = same_new_AST(yytext,line); count(); return(DO); }
"double"		{yylval.val = same_new_AST(yytext,line); count(); return(DOUBLE); }
"else"			{yylval.val = same_new_AST(yytext,line); count(); return(ELSE); }
"enum"			{yylval.val = same_new_AST(yytext,line); count(); return(ENUM); }
"extern"		{yylval.val = same_new_AST(yytext,line); count(); return(EXTERN); }
"float"			{yylval.val = same_new_AST(yytext,line); count(); return(FLOAT); }
"for"			{yylval.val = same_new_AST(yytext,line); count(); return(FOR); }
"goto"			{yylval.val = same_new_AST(yytext,line); count(); return(GOTO); }
"if"			{yylval.val = same_new_AST(yytext,line); count(); return(IF); }
"_Imaginary"		{yylval.val = same_new_AST(yytext,line); count(); return(IMAGINARY); }
"inline"		{yylval.val = same_new_AST(yytext,line); count(); return(INLINE); }
"int"			{yylval.val = same_new_AST(yytext,line); count(); return(INT); }
"long"			{yylval.val = same_new_AST(yytext,line); count(); return(LONG); }
"register"		{yylval.val = same_new_AST(yytext,line); count(); return(REGISTER); }
"restrict"		{yylval.val = same_new_AST(yytext,line); count(); return(RESTRICT); }
"return"		{yylval.val = same_new_AST(yytext,line); count(); return(RETURN); }
"short"			{yylval.val = same_new_AST(yytext,line); count(); return(SHORT); }
"signed"		{yylval.val = same_new_AST(yytext,line); count(); return(SIGNED); }
"sizeof"		{yylval.val = same_new_AST(yytext,line); count(); return(SIZEOF); }
"static"		{yylval.val = same_new_AST(yytext,line); count(); return(STATIC); }
"struct"		{yylval.val = same_new_AST(yytext,line); count(); return(STRUCT); }
"switch"		{yylval.val = same_new_AST(yytext,line); count(); return(SWITCH); }
"typedef"		{yylval.val = same_new_AST(yytext,line); count(); return(TYPEDEF); }
"union"			{yylval.val = same_new_AST(yytext,line); count(); return(UNION); }
"unsigned"		{yylval.val = same_new_AST(yytext,line); count(); return(UNSIGNED); }
"void"			{yylval.val = same_new_AST(yytext,line); count(); return(VOID); }
"volatile"		{yylval.val = same_new_AST(yytext,line); count(); return(VOLATILE); }
"while"			{yylval.val = same_new_AST(yytext,line); count(); return(WHILE); }

{L}({L}|{D})*		{yylval.val = getTYPEDEFfromAST(typedef_table_list, yytext, line); count();
			 return(check_type(yylval.val));}

0[xX]{H}+{IS}?		{yylval.val = new_AST("CONSTANT",yytext,line); count(); return(CONSTANT); }
0{D}+{IS}?		{yylval.val = new_AST("CONSTANT",yytext,line); count(); return(CONSTANT); }
{D}+{IS}?		{yylval.val = new_AST("CONSTANT",yytext,line); count(); return(CONSTANT); }
L?'(\\.|[^\\'\n])+'	{yylval.val = new_AST("CONSTANT",yytext,line); count(); return(CONSTANT); }

{D}+{E}{FS}?		{yylval.val = new_AST("CONSTANT",yytext,line); return(CONSTANT); }
{D}*"."{D}+({E})?{FS}?	{yylval.val = new_AST("CONSTANT",yytext,line); return(CONSTANT); }
{D}+"."{D}*({E})?{FS}?	{yylval.val = new_AST("CONSTANT",yytext,line); return(CONSTANT); }
0[xX]{H}+{P}{FS}?               {yylval.val = new_AST("CONSTANT",yytext,line); count(); return(CONSTANT); }
0[xX]{H}*"."{H}+({P})?{FS}?     {yylval.val = new_AST("CONSTANT",yytext,line); count(); return(CONSTANT); }
0[xX]{H}+"."{H}*({P})?{FS}?     {yylval.val = new_AST("CONSTANT",yytext,line); count(); return(CONSTANT); }


L?\"(\\.|[^\\"\n])*\"	{yylval.val = new_AST("STRING_LITERAL",yytext,line); count(); return(STRING_LITERAL); }

"..."			{yylval.val = same_new_AST(yytext,line); count(); return(ELLIPSIS); }
">>="			{yylval.val = same_new_AST(yytext,line); count(); return(RIGHT_ASSIGN); }
"<<="			{yylval.val = same_new_AST(yytext,line); count(); return(LEFT_ASSIGN); }
"+="			{yylval.val = same_new_AST(yytext,line); count(); return(ADD_ASSIGN); }
"-="			{yylval.val = same_new_AST(yytext,line); count(); return(SUB_ASSIGN); }
"*="			{yylval.val = same_new_AST(yytext,line); count(); return(MUL_ASSIGN); }
"/="			{yylval.val = same_new_AST(yytext,line); count(); return(DIV_ASSIGN); }
"%="			{yylval.val = same_new_AST(yytext,line); count(); return(MOD_ASSIGN); }
"&="			{yylval.val = same_new_AST(yytext,line); count(); return(AND_ASSIGN); }
"^="			{yylval.val = same_new_AST(yytext,line); count(); return(XOR_ASSIGN); }
"|="			{yylval.val = same_new_AST(yytext,line); count(); return(OR_ASSIGN); }
">>"			{yylval.val = same_new_AST(yytext,line); count(); return(RIGHT_OP); }
"<<"			{yylval.val = same_new_AST(yytext,line); count(); return(LEFT_OP); }
"++"			{yylval.val = same_new_AST(yytext,line); count(); return(INC_OP); }
"--"			{yylval.val = same_new_AST(yytext,line); count(); return(DEC_OP); }
"->"			{yylval.val = same_new_AST(yytext,line); count(); return(PTR_OP); }
"&&"			{yylval.val = same_new_AST(yytext,line); count(); return(AND_OP); }
"||"			{yylval.val = same_new_AST(yytext,line); count(); return(OR_OP); }
"<="			{yylval.val = same_new_AST(yytext,line); count(); return(LE_OP); }
">="			{yylval.val = same_new_AST(yytext,line); count(); return(GE_OP); }
"=="			{yylval.val = same_new_AST(yytext,line); count(); return(EQ_OP); }
"!="			{yylval.val = same_new_AST(yytext,line); count(); return(NE_OP); }
";"			{yylval.val = same_new_AST(yytext,line); count(); return(';'); }
("{"|"<%")		{yylval.val = same_new_AST(yytext,line); count(); return('{'); }
("}"|"%>")		{yylval.val = same_new_AST(yytext,line); count(); return('}'); }
","			{yylval.val = same_new_AST(yytext,line); count(); return(','); }
":"			{yylval.val = same_new_AST(yytext,line); count(); return(':'); }
"="			{yylval.val = same_new_AST(yytext,line); count(); return('='); }
"("			{yylval.val = same_new_AST(yytext,line); count(); return('('); }
")"			{yylval.val = same_new_AST(yytext,line); count(); return(')'); }
("["|"<:")		{yylval.val = same_new_AST(yytext,line); count(); return('['); }
("]"|":>")		{yylval.val = same_new_AST(yytext,line); count(); return(']'); }
"."			{yylval.val = same_new_AST(yytext,line); count(); return('.'); }
"&"			{yylval.val = same_new_AST(yytext,line); count(); return('&'); }
"!"			{yylval.val = same_new_AST(yytext,line); count(); return('!'); }
"~"			{yylval.val = same_new_AST(yytext,line); count(); return('~'); }
"-"			{yylval.val = same_new_AST(yytext,line); count(); return('-'); }
"+"			{yylval.val = same_new_AST(yytext,line); count(); return('+'); }
"*"			{yylval.val = same_new_AST(yytext,line); count(); return('*'); }
"/"			{yylval.val = same_new_AST(yytext,line); count(); return('/'); }
"%"			{yylval.val = same_new_AST(yytext,line); count(); return('%'); }
"<"			{yylval.val = same_new_AST(yytext,line); count(); return('<'); }
">"			{yylval.val = same_new_AST(yytext,line); count(); return('>'); }
"^"			{yylval.val = same_new_AST(yytext,line); count(); return('^'); }
"|"			{yylval.val = same_new_AST(yytext,line); count(); return('|'); }
"?"			{yylval.val = same_new_AST(yytext,line); count(); return('?'); }

[ \t\v\n\f]		{ count(); }
.			{ /* Add code to complain about unmatched characters */ }

%%

int yywrap(void)
{
	return 1;
}


void comment(void)
{
	char c, prev = 0;

	while ((c = input()) != 0)      /* (EOF maps to 0) */
	{
		if (c == '/' && prev == '*')
			return;
		prev = c;
	}
	printf("unterminated comment");
}



void count(void)
{
	int i;

	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n'){
			column = 0;
			line++;
		}
		else if (yytext[i] == '\t')
			column += 8 - (column % 8);
		else
			column++;
	ECHO;
}


int check_type(AST *ast)
{
	if(CSTLString_find(ast->name, "TYPE_NAME", 0) != CSTL_NPOS){
		return TYPE_NAME;
	}else{
                return IDENTIFIER;
	}

}