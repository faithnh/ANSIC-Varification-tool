%{

#include <stdio.h>
#include <string.h>

#include "../Library/CSTLString.h"
#include "../Library/StoreInformation.h"
#include "../Library/FlagDatabase.h"
#include "AST.h"
#include "Synbol.h"
#include "Varidate_Statement.h"
#include "PreProcess.h"
#include "ForInformation.h"
#include "FunctionInformation.h"


#define FILE_PATH 512

void yyerror(char const *s);

#define ENABLE_ARGUMENT 2

extern int line;

extern TYPEDEF_TABLE_LIST *typedef_table_list;
extern STRUCT_TABLE_LIST *struct_table_list;
extern VARIABLE_TABLE_LIST *variable_table_list;
ValidateVariableList *varidate_variable_list;
ValidateStatementList *varidate_statement_list;
INCLUDE_LIST *include_list;
ForInformationList *for_information_list;
FUNCTION_INFORMATION_LIST *function_information_list;

AST *programAST;

%}
%union{
	AST *val;
}

%token IDENTIFIER CONSTANT STRING_LITERAL SIZEOF
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token TYPEDEF EXTERN STATIC AUTO REGISTER INLINE RESTRICT
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token BOOL COMPLEX IMAGINARY
%token STRUCT UNION ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%token ';'
%token '{'
%token '}'
%token ','
%token ':'
%token '='
%token '('
%token ')'
%token '['
%token ']'
%token '.'
%token '&'
%token '!'
%token '~'
%token '-'
%token '+'
%token '*'
%token '/'
%token '%'
%token '<'
%token '>'
%token '^'
%token '|'
%token '?'

%left OR_OP
%left AND_OP
%left 'l'
%left '^'
%left '&'
%left EQ_OP NE_OP
%left GE_OP LE_OP '>' '<'
%left RIGHT_OP LEFT_OP
%left '+' '-'
%left '*' '/' '%'

%type <val> IDENTIFIER CONSTANT STRING_LITERAL SIZEOF
%type <val> PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%type <val> AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%type <val> SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%type <val> XOR_ASSIGN OR_ASSIGN TYPE_NAME

%type <val> TYPEDEF EXTERN STATIC AUTO REGISTER INLINE RESTRICT
%type <val> CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%type <val> BOOL COMPLEX IMAGINARY
%type <val> STRUCT UNION ENUM ELLIPSIS

%type <val> CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN
%type <val> ';'
%type <val> '{'
%type <val> '}'
%type <val> ','
%type <val> ':'
%type <val> '='
%type <val> '('
%type <val> ')'
%type <val> '['
%type <val> ']'
%type <val> '.'
%type <val> '&'
%type <val> '!'
%type <val> '~'
%type <val> '-'
%type <val> '+'
%type <val> '*'
%type <val> '/'
%type <val> '%'
%type <val> '<'
%type <val> '>'
%type <val> '^'
%type <val> '|'
%type <val> '?'
%type <val> program
%type <val> primary_expression
%type <val> postfix_expression
%type <val> array_content
%type <val> argument_expression_list
%type <val> argument_expression
%type <val> unary_expression
%type <val> cast_expression
%type <val> all_expression
%type <val> conditional_expression
%type <val> assignment_expression
%type <val> assignment_operator
%type <val> expression
%type <val> constant_expression
%type <val> declaration
%type <val> declaration_specifiers
%type <val> init_declarator_list
%type <val> init_declarator
%type <val> storage_class_specifier
%type <val> type_specifier
%type <val> struct_or_union_specifier
%type <val> struct_or_union
%type <val> struct_declaration_list
%type <val> struct_declaration
%type <val> specifier_qualifier_list
%type <val> struct_declarator_list
%type <val> struct_declarator
%type <val> enum_specifier
%type <val> enumerator_list
%type <val> enumerator
%type <val> type_qualifier
%type <val> function_specifier
%type <val> declarator
%type <val> direct_declarator
%type <val> pointer
%type <val> type_qualifier_list
%type <val> parameter_type_list
%type <val> parameter_list
%type <val> parameter_declaration
%type <val> identifier_list
%type <val> type_name
%type <val> abstract_declarator
%type <val> direct_abstract_declarator
%type <val> initializer
%type <val> initializer_list
%type <val> designation
%type <val> designator_list
%type <val> designator
%type <val> statement
%type <val> labeled_statement
%type <val> compound_statement
%type <val> block_item_list
%type <val> block_item
%type <val> expression_statement
%type <val> selection_statement
%type <val> do_while_expression
%type <val> while_expression
%type <val> for_expression
%type <val> for_expression_statement
%type <val> for_declaration
%type <val> iteration_statement
%type <val> jump_statement
%type <val> translation_unit
%type <val> external_declaration
%type <val> function_definition
%type <val> declaration_list
%start program
%%

primary_expression
	: IDENTIFIER			{$$ = $1;}
	| CONSTANT				{$$ = $1;}
	| STRING_LITERAL		{$$ = $1;}
	| '(' expression ')'	{$$ = new_AST("primary_expression","", $1->line); multi_push_back_childrenAST($$, 3, $1, $2, $3);}
	;

postfix_expression
	: primary_expression												{
																			$$ = new_AST("postfix_expression", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	| postfix_expression '[' array_content ']'							{
																			$$ = new_AST("array_access", "", $1->line);
																			multi_push_back_childrenAST($$, 4, $1, $2, $3, $4);
																		}
	| postfix_expression '(' ')'										{
																			$$ = new_AST("call_function", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	| postfix_expression '(' argument_expression_list ')'				{
																			$$ = new_AST("call_function", "", $1->line);
																			multi_push_back_childrenAST($$, 4, $1, $2, $3, $4);
																		}
	| postfix_expression '.' IDENTIFIER									{
																			$$ = new_AST("struct_access", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	| postfix_expression PTR_OP IDENTIFIER								{
																			$$ = new_AST("p_struct_access", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	| postfix_expression INC_OP											{
																			$$ = new_AST("inc_after_expr", "", $1->line);
																			multi_push_back_childrenAST($$, 2, $1, $2);
																		}
	| postfix_expression DEC_OP											{
																			$$ = new_AST("dec_after_expr", "", $1->line);
																			multi_push_back_childrenAST($$, 2, $1, $2);
																		}
	| '(' type_name ')' '{' initializer_list '}'						{
																			$$ = new_AST("postfix_expression", "", $1->line);
																			multi_push_back_childrenAST($$, 6, $1, $2, $3, $4, $5, $6);
																		}
	| '(' type_name ')' '{' initializer_list ',' '}'					{
																			$$ = new_AST("postfix_expression", "", $1->line);
																			multi_push_back_childrenAST($$, 7, $1, $2, $3, $4, $5, $6, $7);
																		}
	;
	array_content
	: assignment_expression												{
																			$$ = new_AST("array_content", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	| expression ',' assignment_expression								{
																			$$ = new_AST("array_content", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	;

argument_expression_list
	: argument_expression												{
																			$$ = new_AST("argument_expression_list", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	| argument_expression_list ',' argument_expression					{
																			$$ = new_AST("argument_expression_list", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	;
argument_expression
	: conditional_expression											{
																			$$ = new_AST("t_argument_expression", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	| unary_expression assignment_operator argument_expression			{
																			$$ = new_AST("argument_expression", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	;

unary_expression
	: postfix_expression												{
																			$$ = new_AST("unary_expression", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	| INC_OP unary_expression											{
																			$$ = new_AST("inc_expr","",$1->line);
																			multi_push_back_childrenAST($$, 2, $1, $2);
																		}
	| DEC_OP unary_expression											{
																			$$ = new_AST("dec_expr","",$1->line);
																			multi_push_back_childrenAST($$, 2, $1, $2);
																		}
	| '&' cast_expression												{
																			$$ = new_AST("address_ref","",$1->line);
																			multi_push_back_childrenAST($$, 2, $1, $2);
																		}
	| '*' cast_expression												{
																			$$ = new_AST("direct_ref","",$1->line);
																			multi_push_back_childrenAST($$, 2, $1, $2);
																		}
	| '+' cast_expression												{
																			$$ = new_AST("plus_op","",$1->line);
																			multi_push_back_childrenAST($$, 2, $1, $2);
																		}
	| '-' cast_expression												{
																			$$ = new_AST("minus_op","",$1->line);
																			multi_push_back_childrenAST($$, 2, $1, $2);
																		}
	| '~' cast_expression												{
																			$$ = new_AST("xor_op","",$1->line);
																			multi_push_back_childrenAST($$, 2, $1, $2);
																		}
	| '!' cast_expression												{
																			$$ = new_AST("not_op","",$1->line);
																			multi_push_back_childrenAST($$, 2, $1, $2);
																		}
	| SIZEOF unary_expression											{
																			$$ = new_AST("sizeof_expression","",$1->line);
																			multi_push_back_childrenAST($$, 2, $1, $2);
																		}
	| SIZEOF '(' type_name ')'											{
																			$$ = new_AST("sizeof_expression","",$1->line);
																			multi_push_back_childrenAST($$, 4, $1, $2, $3, $4);
																		}
	;


cast_expression
	: unary_expression													{
																			$$ = new_AST("t_cast_expression", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	| '(' type_name ')' cast_expression									{
																			$$ = new_AST("cast_expression", "", $1->line);
																			multi_push_back_childrenAST($$, 4, $1, $2, $3, $4);
																		}
	;

all_expression
	: all_expression OR_OP all_expression								{
																			$$ = new_AST("log_or_expr", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}

	| all_expression AND_OP all_expression								{
																			$$ = new_AST("log_and_expr", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	| all_expression '|' all_expression									{
																			$$ = new_AST("or_expr", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	| all_expression '^' all_expression									{
																			$$ = new_AST("xor_expr", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	| all_expression '&' all_expression									{
																			$$ = new_AST("and_expr", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	| all_expression EQ_OP all_expression								{
																			$$ = new_AST("eq_expr", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	| all_expression NE_OP all_expression								{
																			$$ = new_AST("ne_expr", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	| all_expression '<' all_expression									{
																			$$ = new_AST("lethan_expr", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	| all_expression '>' all_expression									{
																			$$ = new_AST("gethan_expr", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	| all_expression LE_OP all_expression								{
																			$$ = new_AST("leeq_expr", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	| all_expression GE_OP all_expression								{
																			$$ = new_AST("geeq_expr", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	| all_expression LEFT_OP all_expression								{
																			$$ = new_AST("left_expr", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	| all_expression RIGHT_OP all_expression							{
																			$$ = new_AST("right_expr", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	| all_expression '+' all_expression									{
																			$$ = new_AST("plus_expr", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	| all_expression '-' all_expression									{
																			$$ = new_AST("minus_expr", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	| all_expression '*' all_expression									{
																			$$ = new_AST("mul_expr", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	| all_expression '/' all_expression									{
																			$$ = new_AST("div_expr", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	| all_expression '%' all_expression									{
																			$$ = new_AST("mod_expr", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	| cast_expression													{
																			$$ = new_AST("t_all_expression", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}

	;

conditional_expression
	: all_expression													{
																			$$ = new_AST("t_conditional_expression", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	| all_expression '?' expression ':' conditional_expression			{
																			$$ = new_AST("conditional_expression", "", $1->line);
																			multi_push_back_childrenAST($$, 5, $1, $2, $3, $4, $5);
																		}
	;

assignment_expression
	: conditional_expression											{
																			$$ = new_AST("t_assignment_expression", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	| unary_expression assignment_operator assignment_expression		{
																			$$ = new_AST("assignment_expression", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	;

assignment_operator
	: '='																{
																			$$ = $1;
																		}
	| MUL_ASSIGN														{
																			$$ = $1;
																		}
	| DIV_ASSIGN														{
																			$$ = $1;
																		}
	| MOD_ASSIGN														{
																			$$ = $1;
																		}
	| ADD_ASSIGN														{
																			$$ = $1;
																		}
	| SUB_ASSIGN														{
																			$$ = $1;
																		}
	| LEFT_ASSIGN														{
																			$$ = $1;
																		}
	| RIGHT_ASSIGN														{
																			$$ = $1;
																		}
	| AND_ASSIGN														{
																			$$ = $1;
																		}
	| XOR_ASSIGN														{
																			$$ = $1;
																		}
	| OR_ASSIGN															{
																			$$ = $1;
																		}
	;

expression
	: assignment_expression												{
																			$$ = new_AST("t_expression", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	| expression ',' assignment_expression								{
																			$$ = new_AST("expression", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	;

constant_expression
	: conditional_expression											{
																			$$ = new_AST("constant_expression", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	;

declaration
	: declaration_specifiers ';'										{
																			$$ = new_AST("declaration", "", $1->line);
																			multi_push_back_childrenAST($$, 2, $1, $2);
																		}
	| declaration_specifiers init_declarator_list ';'					{
																			$$ = new_AST("declaration_with_init", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																			//TYPEDEFテーブルリストに登録させる
																			getTYPEDEF_TABLE_DATA(typedef_table_list, $1, $2);
																		}
	;

declaration_specifiers
	: storage_class_specifier											{
																			$$ = new_AST("storage_class_specifier", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	| storage_class_specifier declaration_specifiers					{
																			$$ = new_AST("declaration_specifiers", "", $1->line);
																			multi_push_back_childrenAST($$, 2, $1, $2);
																		}
	| type_specifier													{
																			$$ = new_AST("type_specifier", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	| type_specifier declaration_specifiers								{
																			$$ = new_AST("declaration_specifiers", "", $1->line);
																			multi_push_back_childrenAST($$, 2, $1, $2);
																		}
	| type_qualifier													{
																			$$ = new_AST("type_qualifier", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	| type_qualifier declaration_specifiers								{
																			$$ = new_AST("declaration_specifiers", "", $1->line);
																			multi_push_back_childrenAST($$, 2, $1, $2);
																		}
	| function_specifier												{
																			$$ = new_AST("function_specifier", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	| function_specifier declaration_specifiers							{
																			$$ = new_AST("declaration_specifiers", "", $1->line);
																			multi_push_back_childrenAST($$, 2, $1, $2);
																		}
	;

init_declarator_list
	: init_declarator													{
																			$$ = new_AST("t_init_declarator_list", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	| init_declarator_list ',' init_declarator							{
																			$$ = new_AST("init_declarator_list", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	;

init_declarator
	: declarator														{
																			$$ = new_AST("t_init_declarator", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	| declarator '=' initializer										{
																			$$ = new_AST("init_declarator", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	;

storage_class_specifier
	: TYPEDEF															{
																			$$ = $1;
																		}
	| EXTERN															{
																			$$ = $1;
																		}
	| STATIC															{
																			$$ = $1;
																		}
	| AUTO																{
																			$$ = $1;
																		}
	| REGISTER															{
																			$$ = $1;
																		}
	;

type_specifier
	: VOID																{
																			$$ = $1;
																		}
	| CHAR																{
																			$$ = $1;
																		}
	| SHORT																{
																			$$ = $1;
																		}
	| INT																{
																			$$ = $1;
																		}
	| LONG																{
																			$$ = $1;
																		}
	| FLOAT																{
																			$$ = $1;
																		}
	| DOUBLE															{
																			$$ = $1;
																		}
	| SIGNED															{
																			$$ = $1;
																		}
	| UNSIGNED															{
																			$$ = $1;
																		}
	| BOOL																{
																			$$ = $1;
																		}
	| COMPLEX															{
																			$$ = $1;
																		}
	| IMAGINARY															{
																			$$ = $1;
																		}
	| struct_or_union_specifier											{
																			$$ = new_AST("type_specifier", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	| enum_specifier													{
																			$$ = new_AST("type_specifier", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	| TYPE_NAME															{
																			$$ = $1;
																		}
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}'		{
																			$$ = new_AST("struct_or_union_specifier", "", $1->line);
																			multi_push_back_childrenAST($$, 5, $1, $2, $3, $4 ,$5);
																		}
	| struct_or_union '{' struct_declaration_list '}'					{
																			$$ = new_AST("struct_or_union_specifier", "", $1->line);
																			multi_push_back_childrenAST($$, 4, $1, $2, $3 ,$4);
																		}
	| struct_or_union IDENTIFIER										{
																			$$ = new_AST("struct_or_union_specifier", "", $1->line);
																			multi_push_back_childrenAST($$, 2, $1, $2);
																		}
	;

struct_or_union
	: STRUCT															{
																			$$ = $1;
																		}
	| UNION																{
																			$$ = $1;
																		}
	;

struct_declaration_list
	: struct_declaration												{
																			$$ = new_AST("t_struct_declaration_list", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	| struct_declaration_list struct_declaration						{
																			$$ = new_AST("struct_declaration_list", "", $1->line);
																			multi_push_back_childrenAST($$, 2, $1, $2);
																		}
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'				{
																			$$ = new_AST("struct_declaration", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list							{
																			$$ = new_AST("specifier_qualifier_list", "", $1->line);
																			multi_push_back_childrenAST($$, 2, $1, $2);
																		}
	| type_specifier													{
																			$$ = new_AST("type_specifier", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	| type_qualifier specifier_qualifier_list							{
																			$$ = new_AST("specifier_qualifier_list", "", $1->line);
																			multi_push_back_childrenAST($$, 2, $1, $2);
																		}
	| type_qualifier													{
																			$$ = new_AST("type_qualifier", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	;

struct_declarator_list
	: struct_declarator													{
																			$$ = new_AST("t_struct_declarator_list", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	| struct_declarator_list ',' struct_declarator						{
																			$$ = new_AST("struct_declarator_list", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	;

struct_declarator
	: declarator														{
																			$$ = new_AST("struct_declarator", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	| ':' constant_expression											{
																			$$ = new_AST("struct_declarator_list", "", $1->line);
																			multi_push_back_childrenAST($$, 2, $1, $2);
																		}
	| declarator ':' constant_expression								{
																			$$ = new_AST("struct_declarator_list", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	;

enum_specifier
	: ENUM '{' enumerator_list '}'										{
																			$$ = new_AST("struct_declarator_list", "", $1->line);
																			multi_push_back_childrenAST($$, 4, $1, $2, $3, $4);
																		}
	| ENUM IDENTIFIER '{' enumerator_list '}'							{
																			$$ = new_AST("struct_declarator_list", "", $1->line);
																			multi_push_back_childrenAST($$, 5, $1, $2, $3, $4, $5);
																		}
	| ENUM '{' enumerator_list ',' '}'									{
																			$$ = new_AST("struct_declarator_list", "", $1->line);
																			multi_push_back_childrenAST($$, 5, $1, $2, $3, $4, $5);
																		}
	| ENUM IDENTIFIER '{' enumerator_list ',' '}'						{
																			$$ = new_AST("struct_declarator_list", "", $1->line);
																			multi_push_back_childrenAST($$, 6, $1, $2, $3, $4, $5, $6);
																		}
	| ENUM IDENTIFIER													{
																			$$ = new_AST("struct_declarator_list", "", $1->line);
																			multi_push_back_childrenAST($$, 2, $1, $2);
																		}
	;

enumerator_list
	: enumerator														{
																			$$ = new_AST("t_enumerator_list", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	| enumerator_list ',' enumerator									{
																			$$ = new_AST("enumerator_list", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	;

enumerator
	: IDENTIFIER														{
																			$$ = new_AST("enumerator", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	| IDENTIFIER '=' constant_expression								{
																			$$ = new_AST("enumerator_assign", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	;

type_qualifier
	: CONST																{
																			$$ = $1;
																		}
	| RESTRICT															{
																			$$ = $1;
																		}
	| VOLATILE															{
																			$$ = $1;
																		}
	;

function_specifier
	: INLINE															{
																			$$ = $1;
																		}
	;

declarator
	: pointer direct_declarator											{
																			$$ = new_AST("declarator", "", $1->line);
																			multi_push_back_childrenAST($$, 2, $1, $2);
																		}
	| direct_declarator													{
																			$$ = new_AST("declarator", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	;


direct_declarator
	: IDENTIFIER																	{
																						$$ = new_AST("direct_declarator", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	| '(' declarator ')'															{
																						$$ = new_AST("direct_declarator", "", $1->line);
																						multi_push_back_childrenAST($$, 3, $1, $2, $3);
																					}
	| direct_declarator '[' type_qualifier_list assignment_expression ']'			{
																						$$ = new_AST("direct_declarator_array", "", $1->line);
																						multi_push_back_childrenAST($$, 5, $1, $2, $3, $4, $5);
																					}
	| direct_declarator '[' type_qualifier_list ']'									{
																						$$ = new_AST("direct_declarator_array", "", $1->line);
																						multi_push_back_childrenAST($$, 4, $1, $2, $3, $4);
																					}
	| direct_declarator '[' assignment_expression ']'								{
																						$$ = new_AST("direct_declarator_array", "", $1->line);
																						multi_push_back_childrenAST($$, 4, $1, $2, $3, $4);
																					}
	| direct_declarator '[' STATIC type_qualifier_list assignment_expression ']'	{
																						$$ = new_AST("direct_declarator_array", "", $1->line);
																						multi_push_back_childrenAST($$, 6, $1, $2, $3, $4, $5, $6);
																					}
	| direct_declarator '[' type_qualifier_list STATIC assignment_expression ']'	{
																						$$ = new_AST("direct_declarator_array", "", $1->line);
																						multi_push_back_childrenAST($$, 6, $1, $2, $3, $4, $5, $6);
																					}
	| direct_declarator '[' type_qualifier_list '*' ']'								{
																						$$ = new_AST("direct_declarator_array", "", $1->line);
																						multi_push_back_childrenAST($$, 5, $1, $2, $3, $4, $5);
																					}
	| direct_declarator '[' '*' ']'													{
																						$$ = new_AST("direct_declarator_array", "", $1->line);
																						multi_push_back_childrenAST($$, 4, $1, $2, $3, $4);
																					}
	| direct_declarator '[' ']'														{
																						$$ = new_AST("direct_declarator_array", "", $1->line);
																						multi_push_back_childrenAST($$, 3, $1, $2, $3);
																					}
	| direct_declarator '(' parameter_type_list ')'									{
																						$$ = new_AST("direct_declarator_function", "", $1->line);
																						multi_push_back_childrenAST($$, 4, $1, $2, $3, $4);
																					}
	| direct_declarator '(' identifier_list ')'										{
																						$$ = new_AST("direct_declarator_function", "", $1->line);
																						multi_push_back_childrenAST($$, 4, $1, $2, $3, $4);
																					}
	| direct_declarator '(' ')'														{
																						$$ = new_AST("direct_declarator_function", "", $1->line);
																						multi_push_back_childrenAST($$, 3, $1, $2, $3);
																					}
	;

pointer
	: '*'																			{
																						$$ = new_AST("pointer", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	| '*' type_qualifier_list														{
																						$$ = new_AST("pointer", "", $1->line);
																						multi_push_back_childrenAST($$, 2, $1, $2);
																					}
	| '*' pointer																	{
																						$$ = new_AST("pointer", "", $1->line);
																						multi_push_back_childrenAST($$, 2, $1, $2);
																					}
	| '*' type_qualifier_list pointer												{
																						$$ = new_AST("pointer", "", $1->line);
																						multi_push_back_childrenAST($$, 3, $1, $2, $3);
																					}
	;

type_qualifier_list
	: type_qualifier																{
																						$$ = new_AST("type_qualifier", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	| type_qualifier_list type_qualifier											{
																						$$ = new_AST("type_qualifier_list", "", $1->line);
																						multi_push_back_childrenAST($$, 2, $1, $2);
																					}
	;


parameter_type_list
	: parameter_list																{
																						$$ = new_AST("parameter_type_list", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	| parameter_list ',' ELLIPSIS													{
																						$$ = new_AST("parameter_type_list", "", $1->line);
																						multi_push_back_childrenAST($$, 3, $1, $2, $3);
																					}
	;

parameter_list
	: parameter_declaration															{
																						$$ = new_AST("t_parameter_list", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	| parameter_list ',' parameter_declaration										{
																						$$ = new_AST("parameter_list", "", $1->line);
																						multi_push_back_childrenAST($$, 3, $1, $2, $3);
																					}
	;

parameter_declaration
	: declaration_specifiers declarator												{
																						$$ = new_AST("parameter_declaration_with_declarator", "", $1->line);
																						multi_push_back_childrenAST($$, 2, $1, $2);
																					}
	| declaration_specifiers abstract_declarator									{
																						$$ = new_AST("parameter_declaration", "", $1->line);
																						multi_push_back_childrenAST($$, 2, $1, $2);
																					}
	| declaration_specifiers														{
																						$$ = new_AST("parameter_declaration", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	;

identifier_list
	: IDENTIFIER																	{
																						$$ = new_AST("t_identifier_list", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	| identifier_list ',' IDENTIFIER												{
																						$$ = new_AST("identifier_list", "", $1->line);
																						multi_push_back_childrenAST($$, 3, $1, $2, $3);
																					}
	;

type_name
	: specifier_qualifier_list														{
																						$$ = new_AST("type_name", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	| specifier_qualifier_list abstract_declarator									{
																						$$ = new_AST("type_name", "", $1->line);
																						multi_push_back_childrenAST($$, 2, $1, $2);
																					}
	;

abstract_declarator
	: pointer																		{
																						$$ = new_AST("abstract_declarator", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	| direct_abstract_declarator													{
																						$$ = new_AST("abstract_declarator", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	| pointer direct_abstract_declarator											{
																						$$ = new_AST("abstract_declarator", "", $1->line);
																						multi_push_back_childrenAST($$, 2, $1, $2);
																					}
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'													{
																						$$ = new_AST("direct_abstract_declarator", "", $1->line);
																						multi_push_back_childrenAST($$, 3, $1, $2, $3);
																					}
	| '[' ']'																		{
																						$$ = new_AST("direct_abstract_declarator_array", "", $1->line);
																						multi_push_back_childrenAST($$, 2, $1, $2);
																					}
	| '[' assignment_expression ']'													{
																						$$ = new_AST("direct_abstract_declarator_array", "", $1->line);
																						multi_push_back_childrenAST($$, 3, $1, $2, $3);
																					}
	| direct_abstract_declarator '[' ']'											{
																						$$ = new_AST("direct_abstract_declarator_array", "", $1->line);
																						multi_push_back_childrenAST($$, 3, $1, $2, $3);
																					}
	| direct_abstract_declarator '[' assignment_expression ']'						{
																						$$ = new_AST("direct_abstract_declarator_array", "", $1->line);
																						multi_push_back_childrenAST($$, 4, $1, $2, $3, $4);
																					}
	| '[' '*' ']'																	{
																						$$ = new_AST("direct_abstract_declarator_array", "", $1->line);
																						multi_push_back_childrenAST($$, 3, $1, $2, $3);
																					}
	| direct_abstract_declarator '[' '*' ']'										{
																						$$ = new_AST("direct_abstract_declarator_array", "", $1->line);
																						multi_push_back_childrenAST($$, 4, $1, $2, $3, $4);
																					}
	| '(' ')'																		{
																						$$ = new_AST("direct_abstract_declarator", "", $1->line);
																						multi_push_back_childrenAST($$, 2, $1, $2);
																					}
	| '(' parameter_type_list ')'													{
																						$$ = new_AST("direct_abstract_declarator_array", "", $1->line);
																						multi_push_back_childrenAST($$, 3, $1, $2, $3);
																					}
	| direct_abstract_declarator '(' ')'											{
																						$$ = new_AST("direct_abstract_declarator_function", "", $1->line);
																						multi_push_back_childrenAST($$, 3, $1, $2, $3);
																					}
	| direct_abstract_declarator '(' parameter_type_list ')'						{
																						$$ = new_AST("direct_abstract_declarator_function", "", $1->line);
																						multi_push_back_childrenAST($$, 4, $1, $2, $3, $4);
																					}
	;

initializer
	: assignment_expression															{
																						$$ = new_AST("initializer", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	| '{' initializer_list '}'														{
																						$$ = new_AST("initializer", "", $1->line);
																						multi_push_back_childrenAST($$, 3, $1, $2, $3);
																					}
	| '{' initializer_list ',' '}'													{
																						$$ = new_AST("initializer", "", $1->line);
																						multi_push_back_childrenAST($$, 4, $1, $2, $3, $4);
																					}
	;

initializer_list
	: initializer																	{
																						$$ = new_AST("t_initializer_list", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	| designation initializer														{
																						$$ = new_AST("t_initializer_list", "", $1->line);
																						multi_push_back_childrenAST($$, 2, $1, $2);
																					}
	| initializer_list ',' initializer												{
																						$$ = new_AST("identifier_list", "", $1->line);
																						multi_push_back_childrenAST($$, 3, $1, $2, $3);
																					}
	| initializer_list ',' designation initializer									{
																						$$ = new_AST("identifier_list", "", $1->line);
																						multi_push_back_childrenAST($$, 4, $1, $2, $3, $4);
																					}
	;

designation
	: designator_list '='															{
																						$$ = new_AST("designation", "", $1->line);
																						multi_push_back_childrenAST($$, 2, $1, $2);
																					}
	;

designator_list
	: designator																	{
																						$$ = new_AST("t_designator_list", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	| designator_list designator													{
																						$$ = new_AST("designator_list", "", $1->line);
																						multi_push_back_childrenAST($$, 2, $1, $2);
																					}
	;

designator
	: '[' constant_expression ']'													{
																						$$ = new_AST("designator", "", $1->line);
																						multi_push_back_childrenAST($$, 3, $1, $2, $3);
																					}
	| '.' IDENTIFIER																{
																						$$ = new_AST("designator", "", $1->line);
																						multi_push_back_childrenAST($$, 2, $1, $2);
																					}
	;

statement
	: labeled_statement																{
																						$$ = new_AST("statement", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	| compound_statement															{
																						$$ = new_AST("statement", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	| expression_statement															{
																						$$ = new_AST("statement", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	| selection_statement															{
																						$$ = new_AST("statement", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	| iteration_statement															{
																						$$ = new_AST("statement", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	| jump_statement																{
																						$$ = new_AST("statement", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	;

labeled_statement
	: IDENTIFIER ':' statement														{
																						$$ = new_AST("goto_labeled_statement", "", $1->line);
																						multi_push_back_childrenAST($$, 3, $1, $2, $3);
																					}
	| CASE constant_expression ':' statement										{
																						$$ = new_AST("case_labeled_statement", "", $1->line);
																						multi_push_back_childrenAST($$, 4, $1, $2, $3, $4);
																					}
	| DEFAULT ':' statement															{
																						$$ = new_AST("default_labeled_statement", "", $1->line);
																						multi_push_back_childrenAST($$, 3, $1, $2, $3);
																					}
	;

compound_statement
	: '{' '}'																		{
																						$$ = new_AST("compound_statement_a", "", $1->line);
																						multi_push_back_childrenAST($$, 2, $1, $2);
																					}
	| '{' block_item_list '}'														{
																						$$ = new_AST("compound_statement_b", "", $1->line);
																						multi_push_back_childrenAST($$, 3, $1, $2, $3);
																					}
	;

block_item_list
	: block_item																	{
																						$$ = new_AST("t_block_item_list", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	| block_item_list block_item													{
																						$$ = new_AST("block_item_list", "", $1->line);
																						multi_push_back_childrenAST($$, 2, $1, $2);
																					}
	;

block_item
	: declaration																	{
																						$$ = new_AST("block_item", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	| statement																		{
																						$$ = new_AST("block_item", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	;

expression_statement
	: ';'																			{
																						$$ = new_AST("expression_statement", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	| expression ';'																{
																						$$ = new_AST("expression_statement", "", $1->line);
																						multi_push_back_childrenAST($$, 2, $1, $2);
																					}
	;

selection_statement
	: IF '(' expression ')' statement												{
																						$$ = new_AST("if_statement", "", $1->line);
																						multi_push_back_childrenAST($$, 5, $1, $2, $3, $4, $5);
																					}
	| IF '(' expression ')' statement ELSE statement								{
																						$$ = new_AST("ifelse_statement", "", $1->line);
																						multi_push_back_childrenAST($$, 7, $1, $2, $3, $4, $5, $6, $7);
																					}
	| SWITCH '(' expression ')' statement											{
																						$$ = new_AST("switch_statement", "", $1->line);
																						multi_push_back_childrenAST($$, 5, $1, $2, $3, $4, $5);
																					}
	;


do_while_expression
	: assignment_expression												{
																			$$ = new_AST("t_do_while_expression", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	| expression ',' assignment_expression								{
																			$$ = new_AST("do_while_expression", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	;

while_expression
	: assignment_expression												{
																			$$ = new_AST("t_while_expression", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	| expression ',' assignment_expression								{
																			$$ = new_AST("while_expression", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	;

for_expression
	: assignment_expression												{
																			$$ = new_AST("t_for_expression", "", $1->line);
																			push_back_childrenAST($$, $1);
																		}
	| expression ',' assignment_expression								{
																			$$ = new_AST("for_expression", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																		}
	;

for_expression_statement
	: ';'																			{
																						$$ = new_AST("for_expression_statement", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	| expression ';'																{
																						$$ = new_AST("for_expression_statement", "", $1->line);
																						multi_push_back_childrenAST($$, 2, $1, $2);
																					}
	;

for_declaration
	: declaration_specifiers ';'										{
																			$$ = new_AST("for_declaration", "", $1->line);
																			multi_push_back_childrenAST($$, 2, $1, $2);
																		}
	| declaration_specifiers init_declarator_list ';'					{
																			$$ = new_AST("for_declaration_with_init", "", $1->line);
																			multi_push_back_childrenAST($$, 3, $1, $2, $3);
																			//TYPEDEFテーブルリストに登録させる
																			getTYPEDEF_TABLE_DATA(typedef_table_list, $1, $2);
																		}
	;

iteration_statement
	: WHILE '(' while_expression ')' statement										{
																						$$ = new_AST("while_statement", "", $1->line);
																						multi_push_back_childrenAST($$, 5, $1, $2, $3, $4, $5);
																					}
	| DO statement WHILE '(' do_while_expression ')' ';'							{
																						$$ = new_AST("dowhile_statement", "", $1->line);
																						multi_push_back_childrenAST($$, 7, $1, $2, $3, $4, $5, $6, $7);
																					}

	| FOR '(' for_expression_statement for_expression_statement ')' statement		{
																						$$ = new_AST("for_statement_type_a", "", $1->line);
																						multi_push_back_childrenAST($$, 6, $1, $2, $3, $4, $5, $6);
																					}
	| FOR '(' for_expression_statement for_expression_statement for_expression ')' statement	{
																									$$ = new_AST("for_statement_type_b", "", $1->line);
																									multi_push_back_childrenAST($$, 7, $1, $2, $3, $4, $5, $6, $7);
																								}
	| FOR '(' for_declaration for_expression_statement ')' statement				{
																						$$ = new_AST("for_statement_type_c", "", $1->line);
																						multi_push_back_childrenAST($$, 6, $1, $2, $3, $4, $5, $6);
																					}
	| FOR '(' for_declaration for_expression_statement for_expression ')' statement	{
																						$$ = new_AST("for_statement_type_d", "", $1->line);
																						multi_push_back_childrenAST($$, 7, $1, $2, $3, $4, $5, $6, $7);
																					}
	;

jump_statement
	: GOTO IDENTIFIER ';'															{
																						$$ = new_AST("goto_statement", "", $1->line);
																						multi_push_back_childrenAST($$, 3, $1,$2, $3);
																					}
	| CONTINUE ';'																	{
																						$$ = new_AST("continue_statement", "", $1->line);
																						multi_push_back_childrenAST($$, 2, $1, $2);
																					}
	| BREAK ';'																		{
																						$$ = new_AST("break_statement", "", $1->line);
																						multi_push_back_childrenAST($$, 2, $1, $2);
																					}
	| RETURN ';'																	{
																						$$ = new_AST("return_statement", "", $1->line);
																						multi_push_back_childrenAST($$, 2, $1, $2);
																					}
	| RETURN expression ';'															{
																						$$ = new_AST("return_expr_statement", "", $1->line);
																						multi_push_back_childrenAST($$, 3, $1,$2, $3);
																					}
	;
program
	: translation_unit																{
																						$$ = new_AST("program", "", $1->line);
																						push_back_childrenAST($$, $1);
																						programAST = $$;


																					}
	;
translation_unit
	: external_declaration															{
																						$$ = new_AST("t_translation_unit", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	| translation_unit external_declaration											{
																						$$ = new_AST("translation_unit", "", $1->line);
																						multi_push_back_childrenAST($$, 2, $1, $2);
																					}
	;

external_declaration
	: function_definition															{
																						$$ = new_AST("external_declaration", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	| declaration																	{
																						$$ = new_AST("external_declaration", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement			{
																						$$ = new_AST("function_definition_type_a", "", $1->line);
																						multi_push_back_childrenAST($$, 4, $1, $2, $3, $4);
																					}
	| declaration_specifiers declarator compound_statement							{
																						$$ = new_AST("function_definition_type_b", "", $1->line);
																						multi_push_back_childrenAST($$, 3, $1, $2, $3);
																					}
	;

declaration_list
	: declaration																	{
																						$$ = new_AST("t_declaration_list", "", $1->line);
																						push_back_childrenAST($$, $1);
																					}
	| declaration_list declaration													{
																						$$ = new_AST("declaration_list", "", $1->line);
																						multi_push_back_childrenAST($$, 2, $1, $2);
																					}
	;


%%
#include <stdio.h>

extern char yytext[];
extern int column;
extern int line;

//構文解析本体のエラーフラグ
int error_flag = 0;
void yyerror(char const *s)
{
	fflush(stdout);
	printf("#%s#:%d:Syntax Error!!\n", getFileName(), line);

	//構文解析本体のエラーフラグを立てる
	error_flag = 1;
}
/*
int main(int argc, char *argv[]){
	extern FILE *yyin;
	FILE *output;
	//フラグデータベースの設定
	int flag_database = getFlagDatabase(argc, argv);

	int i;
	//フラグを飛ばす
	for(i = 1;i < argc && strlen(argv[i]) >= 2 && ( argv[i][0] == '-' && argv[i][1] == '-' ); i++);
	if(i == argc){
		fprintf(stderr, "開くファイル名が存在しません！\n");
		exit(1);
	}

	char preprocess_file_name[FILE_PATH];
	char output_file_name[FILE_PATH];
	if(argc >= ENABLE_ARGUMENT){
		//ファイル名を設定する（これは他のエラー処理などでファイル名を表示させるようにするために必要）
		setFileName(argv[i]);

		//前処理に成功した場合
		if(preProcesser(argv[i])){

			//プリプロセス後のファイル名の設定
			snprintf(preprocess_file_name, FILE_PATH, "%s_out.c_pre.c", argv[i]);

			//インクルードファイルリストを取得
			include_list = INCLUDE_LIST_new();
			readIncludeDataFromFile(preprocess_file_name, include_list);

			yyin = fopen(preprocess_file_name, "r");

			//ファイルのオープンに成功したら、構文解析を開始する
			if(yyin != NULL){
				typedef_table_list = TYPEDEF_TABLE_LIST_new();
				//あらかじめプログラムのASTはNULLにしておく
				programAST = NULL;
				//構文解析の開始
				yyparse();


				//構文解析に成功した場合
				if(error_flag == 0 && programAST != NULL){

					//ASTノードに、返却の型名・ブロックレベル・ブロックIDを付加する。
					setASTReturnType(programAST);
					setASTBlocklevelAndId(programAST);

					//ＸＭＬモードである場合
					if(isXmlMode(flag_database)){
						//AST木全体をXMLとして出力する
						//traverseASTwithXML(programAST, 0);
						printTargetASTNode(programAST, "array_access", 1, 1);
						printTargetASTNode(programAST, "direct_ref", 1, 1);
						printTargetASTNode(programAST, "expression_statement", 1, 1);
						printTargetASTNode(programAST, "function_definition", 1, 1);
						printTargetASTNode(programAST, "if_statement",1, 1);
					}else{
						//AST木全体を出力する
						//traverseAST(programAST, 0);

						//AST木からプログラムを出力する
						int tmp = 1;
						//printDataFromAST(programAST, &tmp);

						//AST木から生成したTYPEDEFテーブルを表示
						//printTYPEDEF_TABLE_LIST(typedef_table_list);

						//AST木から構造体テーブルを生成して出力
						struct_table_list = STRUCT_TABLE_LIST_new();
						getSTRUCT_TABLE_DATA(struct_table_list, programAST);
						//printSTRUCT_TABLE_LIST(struct_table_list);

						//AST木から変数テーブルを生成して出力
						variable_table_list = VARIABLE_TABLE_LIST_new();
						getVARIABLE_TABLE_LIST(variable_table_list, programAST);
						getParameterVARIABLE_TABLE_LIST(variable_table_list, programAST);
						//printVARIABLE_TABLE_LIST(variable_table_list);

						//変数テーブルから検証用変数テーブルを生成して出力
						varidate_variable_list = VARIDATE_VARIABLE_LIST_new();
						getVaridate_Variable(variable_table_list, varidate_variable_list);

						//printVARIDATE_VARIABLE_LIST(varidate_variable_list);

						//関数に関するリストを生成して出力
						function_information_list = FUNCTION_INFORMATION_LIST_new();
						getFunctionInformation(function_information_list, programAST);

						printFUNCTION_INFORMATION_LIST(function_information_list);

						//（実験）指定されたASTの情報を出力
						//printTargetASTNode(programAST, "call_function", 0, 0);
						//printTargetASTNode(programAST, "direct_ref", 0, 0);
						//printTargetASTNode(programAST, "assignment_expression", 0, 0);
						//printTargetASTNode(programAST, "expression_statement", 0, 0);

						//検証式の生成
						varidate_statement_list = VARIDATE_STATEMENT_LIST_new();
						for_information_list = FOR_INFORMATION_LIST_new();
						createVaridateStatementFromArrayDefine(varidate_variable_list, varidate_statement_list, variable_table_list);
						createVaridateStatementFromPointerDefine(varidate_statement_list, variable_table_list);
						createVaridateStatement(programAST,  function_information_list, variable_table_list, varidate_variable_list, varidate_statement_list,
						 for_information_list, isUndefineControlCheckMode(flag_database), isZeroDivitionCheckMode(flag_database), isArrayUnboundCheckMode(flag_database));

						//出力ファイルに検証式付きのプログラムを出力させる
						snprintf(output_file_name, FILE_PATH, "%s_output.c", preprocess_file_name);
						output = fopen(output_file_name, "w");
						//printProgramDataWithVaridateStatement(programAST, varidate_variable_list, varidate_statement_list);
						fprintProgramDataWithVaridateStatement(output, programAST, varidate_variable_list, varidate_statement_list, for_information_list);

						//入力ファイルおよび出力ファイルを閉じる
						fclose(yyin);
						fclose(output);

						//インクルードリストからインクルードを付加する
						addIncludeDataFromFile(output_file_name, include_list);

					}
				}else{
					printf("Syntax_error is occured!! Please Check your source file!!\n");
				}

			}
		}else{
			printf("PreProcesser is failed!! Please Check your source file!!\n");
		}
	}
*/

AST *parserANSIC(FILE *name, TYPEDEF_TABLE_LIST **out_typedef_table_list){
	extern FILE *yyin;
	yyin = name;

	//lineとcolumnを初期化
	line = 1;
	column = 0;

	//あらかじめプログラムのASTはNULLにしておく
	programAST = NULL;
	//タイプ定義を初期化する
	typedef_table_list = TYPEDEF_TABLE_LIST_new();

	//構文解析の開始
	yyparse();

	//構文解析に成功した場合
	if(error_flag == 0 && programAST != NULL){
		*out_typedef_table_list = typedef_table_list;
	}
	//構文解析に失敗した場合は強制終了させる
	else{
		printf("Syntax_error is occured!! Please Check your source file!!\n");
		exit(1);
	}
	return programAST;
}