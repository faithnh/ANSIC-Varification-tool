#include "Varidate_statement.h"
#include "../Library/Stack_int.h"
#include "../Library/StoreInformation.h"
#include "ANSIC_CODE.h"
#include <stdio.h>
#include<limits.h>

//デバッグモード
#define DEBUG_MODE


//文字列の長さ
#define STRLEN 256

//VARIDATEで使用したというフラグの値
#define VALIDATE_USED 1
//VARIDATEで使用していないというフラグの値
#define VALIDATE_NOTUSED 0
//動的配列を示すタイプ
#define MALLOC_DYNAMIC_ARRAY_MODE 1
//単一の値を示すタイプ
#define MALLOC_SINGLE_MODE 2
//いずれも当てはまらないタイプ
#define MALLOC_UNDEF_TYPE 0

//アンパサンド記号（アドレス演算子）を経由しているか否かを示す記号
#define VIA_ANPASAND 1
#define NOT_VIA_ANPASAND 0

//インクリメントかデクリメントが含まれているかどうかを示すフラグ
#define NOT_INC_DEC 0
#define VIA_INC 1
#define VIA_DEC 2

//出力するタイプが検証式編集タイプかチェックタイプかを示すフラグ
#define CHECK_VS 0
#define MODIFY_VS 1

//成功した場合
#define SUCCESS 1
//失敗した場合
#define FAILED 0

//除算か剰余算かどうかのフラグ
#define TYPE_DIV 0
#define TYPE_MOD 1

//代入演算子が何かというフラグ0:=,1:+=,2:-=,3:*=,4:/=,5:%=,6:<<=,7:>>=,8:&=,9:|=,10:^=
#define EQUAL 0
#define PLUS_EQUAL 1
#define MINUS_EQUAL 2
#define MUL_EQUAL 3
#define DIV_EQUAL 4
#define MOD_EQUAL 5
#define LEFT_EQUAL 6
#define RIGHT_EQUAL 7
#define AND_EQUAL 8
#define OR_EQUAL 9
#define XOR_EQUAL 10

//正か偽か
#define TRUE 1
#define FALSE 0

//assert(0);
#define ASSERT_STRING "assert(0);"

CSTL_LIST_IMPLEMENT(ValidateVariableList, ValidateVariable);

CSTL_LIST_IMPLEMENT(ValidateStatementList, ValidateStatement);

/**
実際に検証式として挿入するための情報を生成する。
@param target_id この検証式の識別ID(どの順序でこの検証式を入れていくかを確認するためのID)
@param check_or_modify 検証式をチェックするタイプか、プログラムを元に編集するタイプかを判断するフラグ。０：チェックするタイプ、１：編集するタイプ
@param used この検証式は使用しているかどうかのフラグ 1:使用 0:未使用
@param statement この検証式の内容
@param target_statement この検証式のターゲットとなるASTノードへのアドレス

@return 実際に検証式として挿入するための情報へのアドレスを返す。
*/
ValidateStatement *new_VALIDATE_STATEMENT_char(int target_id, int check_or_modify, int used, char *statement, AST *target_statement){

	CSTLString *statement_cstl = CSTLString_new();
	CSTLString_assign(statement_cstl, statement);

	return new_VALIDATE_STATEMENT(target_id, check_or_modify, used, statement_cstl, target_statement);
}

/**
実際に検証式として挿入するための情報を生成する。
@param target_id この検証式の識別ID(どの順序でこの検証式を入れていくかを確認するためのID)
@param check_or_modify 検証式をチェックするタイプか、プログラムを元に編集するタイプかを判断するフラグ。０：チェックするタイプ、１：編集するタイプ
@param used この検証式は使用しているかどうかのフラグ 1:使用 0:未使用
@param statement この検証式の内容
@param target_statement この検証式のターゲットとなるASTノードへのアドレス

@return 実際に検証式として挿入するための情報へのアドレスを返す。
*/
ValidateStatement *new_VALIDATE_STATEMENT(int target_id, int check_or_modify, int used, CSTLString *statement, AST *target_statement){
	//実際に検証式として挿入するための情報を生成する
	ValidateStatement* new_validate_statement = (ValidateStatement*)malloc(sizeof(ValidateStatement));

	//必要な情報を代入していく
	new_validate_statement->target_id = target_id;
	new_validate_statement->check_or_modify = check_or_modify;
	new_validate_statement->used = used;
	new_validate_statement->statement = statement;
	new_validate_statement->target_statement = target_statement;

	//実際に検証式として挿入するための情報へのアドレスを返す
	return new_validate_statement;
}

/**
新しい検証用変数テーブルのデータを生成させる。
@param used この検証用変数テーブルを使用したかどうか
@param enable_start この変数の有効範囲の始まりの行数
@param enable_end この変数の有効範囲の終わりの行数
@param declaration_location この変数を宣言した場所の行数
@param block_level この変数のブロックレベル（グローバル変数なら０とし、関数の中での定義なら１、その関数内のfor文などのブロック文ないでの宣言なら２とする）
@param block_id ブロックごとのID（基本的には0から始り、ブロックレベル２が２回目にくると、１となる）
@param type 型名
@param variable_name 変数名
@param target_variable_name 検証対象の変数名
@param offset_level この変数の配列やポインタの次元レベル

@return 新しく生成された検証用変数のデータへのアドレスが返される。
*/
ValidateVariable *new_VALIDATE_VARIABLE(int used, int enable_start, int enable_end, int declaration_location,
								   int block_level ,int block_id, CSTLString *type, CSTLString *variable_name, CSTLString *target_variable_name, int offset_level){
	//新しい検証用変数データを生成する
	ValidateVariable *new_validate_variable_data = (ValidateVariable*)malloc(sizeof(ValidateVariable));

	//検証用変数データに必要なデータを設定する
	new_validate_variable_data->used = used;
	new_validate_variable_data->enable_start = enable_start;
	new_validate_variable_data->enable_end = enable_end;
	new_validate_variable_data->declaration_location = declaration_location;
	new_validate_variable_data->block_level = block_level;
	new_validate_variable_data->block_id = block_id;
	new_validate_variable_data->type = type;
	new_validate_variable_data->variable_name = variable_name;
	new_validate_variable_data->target_variable_name = target_variable_name;
	new_validate_variable_data->offset_level = offset_level;

	//新しく生成された検証用変数のデータへのアドレスが返される
	return new_validate_variable_data;
}

/**
新しい検証用変数テーブルのデータを生成させる(char対応版)。
@param used この検証用変数テーブルを使用したかどうか
@param enable_start この変数の有効範囲の始まりの行数
@param enable_end この変数の有効範囲の終わりの行数
@param declaration_location この変数を宣言した場所の行数
@param block_level この変数のブロックレベル（グローバル変数なら０とし、関数の中での定義なら１、その関数内のfor文などのブロック文ないでの宣言なら２とする）
@param block_id ブロックごとのID（基本的には0から始り、ブロックレベル２が２回目にくると、１となる）
@param type 型名
@param variable_name 変数名
@param target_variable_name 検証対象の変数名
@param offset_level この変数の配列やポインタの次元レベル

@return 新しく生成された検証用変数のデータへのアドレスが返される。
*/
ValidateVariable *new_VALIDATE_VARIABLE_with_char(int used, int enable_start, int enable_end, int declaration_location,
								   int block_level ,int block_id, char *type, char *variable_name, char *target_variable_name, int offset_level){
	//CSTLString属性の型名、変数名、検証対象の変数名を設定する
	CSTLString *CSTLtype = CSTLString_new();
	CSTLString *CSTLvariable_name = CSTLString_new();
	CSTLString *CSTLtarget_variable_name = CSTLString_new();

	CSTLString_assign(CSTLtype, type);
	CSTLString_assign(CSTLvariable_name, variable_name);
	CSTLString_assign(CSTLtarget_variable_name, target_variable_name);

	//新しい検証用変数データを生成する
	ValidateVariable *new_validate_variable_data = new_VALIDATE_VARIABLE(used, enable_start, enable_end, declaration_location,
									block_level , block_id, CSTLtype, CSTLvariable_name, CSTLtarget_variable_name, offset_level);

	//新しく生成された検証用変数のデータへのアドレスが返される
	return new_validate_variable_data;
}

/**
検証式リストの使用フラグを未使用状態に初期化する。
@param validate_statement_list *初期化対象の検証式リスト

@return なし
 */
void initVaridateStatement_flag(ValidateStatementList *validate_statement_list){
	ValidateStatementListIterator vs_list_i;

	//すべての検証式リストの使用フラグを未使用状態に初期化する
	for(vs_list_i = ValidateStatementList_begin(validate_statement_list);
		vs_list_i != ValidateStatementList_end(validate_statement_list);
		vs_list_i = ValidateStatementList_next(vs_list_i)){
			ValidateStatementList_data(vs_list_i)->used = VALIDATE_NOTUSED;
		}
}

/**
プログラムの変数リストをもとにプログラムの検証用の変数を設定する。
@param variable_table_list プログラムの変数リスト
@param validate_variable 検証用の変数リスト
@return なし
*/
void getValidate_Variable(VARIABLE_TABLE_LIST *variable_table_list, ValidateVariableList *validate_variable)
{
	VARIABLE_TABLE_LISTIterator valist;
	//ポインタの次元、配列の次元を決める
	int pointer_level, array_level;
	int i,j;

	//検証式の変数名を設定させるのに使用する
	char variable_name[STRLEN];
	//検証対象の変数名を設定させるのに使用する
	char variable_table_lists_name_char[STRLEN];

	CSTLString *astalisk = CSTLString_new();
	CSTLString *variable_table_lists_name = CSTLString_new();

	//ポインタで始める次元のオフセット
	int pointer_start_offset=0;

	//検証用変数としてmallocの識別番号を付加するための変数を定義する
	/*ValidateVariableList_push_back_ref( validate_variable,

	new_VALIDATE_VARIABLE_with_char(VALIDATE_NOTUSED,
									1,
									INT_MAX,
									1,
									0,
									0,
									"int",
									"malloc_number = 1",
									"null",
									1
	)
	);*/

	//プログラムの変数リストをすべて参照させる
	for(valist = VARIABLE_TABLE_LIST_begin(variable_table_list);
		valist != VARIABLE_TABLE_LIST_end(variable_table_list);
		valist = VARIABLE_TABLE_LIST_next(valist)){
			//検証対象の変数名を取得する
			CSTLString_assign(variable_table_lists_name,CSTLString_c_str(VARIABLE_TABLE_LIST_data(valist)->variable_name));
			//検証対象の変数名からポインタや配列を示す記号をすべて除去する
			deletePointerAndArraySynbol(variable_table_lists_name);
			//検証対象の変数名を設定するための文字列配列に入れておく
			sprintf(variable_table_lists_name_char, "%s", CSTLString_c_str(variable_table_lists_name));
			//検証対象の変数名からポインタの次元および、配列の次元を計算する
			getPointerLevelAndArrayLevelFromVARIABLE_TABLE(VARIABLE_TABLE_LIST_data(valist), &pointer_level, &array_level);



			//検証するための変数にポインタ記号を入れるために生成する
			//（これはダブルポインタ以降は、格納している場所が異なると、格納できるポインタの数も変えることができるため、
			//その階層分の状態も検証できるようにするために必要である。)
			CSTLString_assign(astalisk,"");

			for(i = 1; i <= pointer_level + array_level; i++){

				//ポインタ配列の許容範囲（すなわち配列の大きさ）を示す検証用の変数を生成する

				sprintf(variable_name, "*%smax_size_%d_%s", CSTLString_c_str(astalisk), i, variable_table_lists_name_char);

				ValidateVariableList_push_back_ref( validate_variable,

					new_VALIDATE_VARIABLE_with_char(VALIDATE_NOTUSED,
													VARIABLE_TABLE_LIST_data(valist)->enable_start,
													VARIABLE_TABLE_LIST_data(valist)->enable_end,
													VARIABLE_TABLE_LIST_data(valist)->enable_start,
													VARIABLE_TABLE_LIST_data(valist)->block_level,
													VARIABLE_TABLE_LIST_data(valist)->block_id,
													"int",
													variable_name,
													variable_table_lists_name_char,
													i
					)
					);

				//ポインタが今現在示している配列の位置を示す検証用の変数を生成する
				sprintf(variable_name, "%sbasis_location_%d_%s", CSTLString_c_str(astalisk), i, variable_table_lists_name_char);

				ValidateVariableList_push_back_ref( validate_variable,

					new_VALIDATE_VARIABLE_with_char(VALIDATE_NOTUSED,
													VARIABLE_TABLE_LIST_data(valist)->enable_start,
													VARIABLE_TABLE_LIST_data(valist)->enable_end,
													VARIABLE_TABLE_LIST_data(valist)->enable_start,
													VARIABLE_TABLE_LIST_data(valist)->block_level,
													VARIABLE_TABLE_LIST_data(valist)->block_id,
													"int",
													variable_name,
													variable_table_lists_name_char,
													i
					)
					);

				//ポインタが動的・静的な変数を問わずアドレスが設定されているかどうか示すための検証用の変数を生成する
				sprintf(variable_name, "*%sdefined_%d_%s", CSTLString_c_str(astalisk), i, variable_table_lists_name_char);

				ValidateVariableList_push_back_ref( validate_variable,

					new_VALIDATE_VARIABLE_with_char(VALIDATE_NOTUSED,
													VARIABLE_TABLE_LIST_data(valist)->enable_start,
													VARIABLE_TABLE_LIST_data(valist)->enable_end,
													VARIABLE_TABLE_LIST_data(valist)->enable_start,
													VARIABLE_TABLE_LIST_data(valist)->block_level,
													VARIABLE_TABLE_LIST_data(valist)->block_id,
													"int",
													variable_name,
													variable_table_lists_name_char,
													i
					)
					);

				//ポインタが動的な変数のアドレスが設定されているかどうかを示すための検証用の変数を生成する
				sprintf(variable_name, "*%smalloc_flag_%d_%s", CSTLString_c_str(astalisk), i, variable_table_lists_name_char);


				ValidateVariableList_push_back_ref( validate_variable,

					new_VALIDATE_VARIABLE_with_char(VALIDATE_NOTUSED,
													VARIABLE_TABLE_LIST_data(valist)->enable_start,
													VARIABLE_TABLE_LIST_data(valist)->enable_end,
													VARIABLE_TABLE_LIST_data(valist)->enable_start,
													VARIABLE_TABLE_LIST_data(valist)->block_level,
													VARIABLE_TABLE_LIST_data(valist)->block_id,
													"int",
													variable_name,
													variable_table_lists_name_char,
													i
					)
					);

				//ポインタを示すアスタリスクを追加させる
				CSTLString_append(astalisk, "*");
			}

	}
	//アスタリスクを示す文字列をメモリを解放させる
	CSTLString_delete(astalisk);
	//検証対象の変数名を取得するために使用した文字列のメモリを解放させる
	CSTLString_delete(variable_table_lists_name);
}

/**
検証用変数テーブルのリストの内容を出力させる。
@param validate_variable_list 出力対象の検証用変数テーブルのリスト
@return なし

*/
void printValidateVariableList(ValidateVariableList *validate_variable_list){
	ValidateVariableListIterator vtlist;
	int counter = 1;

	printf("---------------VARIDATE_VARIABLE_TABLE---------------\n\n");

	for(vtlist = ValidateVariableList_begin(validate_variable_list);
	vtlist != ValidateVariableList_end(validate_variable_list);
	vtlist = ValidateVariableList_next(vtlist)){
		printf("---------------VARIDATE_VARIABLE_%d_INFO---------------\n\n", counter);
		printf("VARIDATE_VARIABLE_%d_USED = \"%d\"\n", counter, ValidateVariableList_data(vtlist)->used);
		printf("VARIDATE_VARIABLE_%d_TYPE = \"%s\"\n", counter, CSTLString_c_str(ValidateVariableList_data(vtlist)->type));
		printf("VARIDATE_VARIABLE_%d_NAME = \"%s\"\n", counter, CSTLString_c_str(ValidateVariableList_data(vtlist)->variable_name));
		printf("VARIDATE_VARIABLE_%d_TARGET_VARIABLE_NAME = \"%s\"\n", counter, CSTLString_c_str(ValidateVariableList_data(vtlist)->target_variable_name));
		printf("VARIDATE_VARIABLE_%d_ENABLE_START = \"%d\"\n", counter, ValidateVariableList_data(vtlist)->enable_start);
		printf("VARIDATE_VARIABLE_%d_ENABLE_END = \"%d\"\n", counter, ValidateVariableList_data(vtlist)->enable_end);
		printf("VARIDATE_VARIABLE_%d_DECLARATION_LOCATION = \"%d\"\n", counter, ValidateVariableList_data(vtlist)->declaration_location);
		printf("VARIDATE_VARIABLE_%d_BLOCK_LEVEL = \"%d\"\n", counter, ValidateVariableList_data(vtlist)->block_level);
		printf("VARIDATE_VARIABLE_%d_BLOCK_ID = \"%d\"\n\n", counter, ValidateVariableList_data(vtlist)->block_id);
		printf("VARIDATE_VARIABLE_%d_OFFSET_LEVEL = \"%d\"\n\n", counter, ValidateVariableList_data(vtlist)->offset_level);
		counter++;
	}
	printf("--------------------------------------------\n\n");
}

/**
基本的な検証式の生成を行う。
@param root 検証式生成対象のASTノード
@param function_informaiton_list 関数に関する情報のリスト
@param vtlist 検証対象の式をマークするための変数リスト
@param validate_statement_list 検証用変数リスト
@param validate_variable_list 取得した検証式が格納するところ
@param for_information_list for文に関する情報
@param undefined_control_check 未定義な処理（未定義ポインタの参照など）を行っていないかどうかを検証するための式を生成するかどうか １：生成する ０：生成しない
@param zero_divition_check 0で割っていないかどうかを検証するための式を生成するかどうか　１：生成する　０：生成しない
@param array_unbound_check 配列が範囲外を参照していないかどうかを検証するための式を生成するかどうか　１：生成する　０：生成しない
@param free_violation_check メモリ解放関係で不正な処理を行っていないかどうかを検証するための式を生成するかどうか　１：生成する　０：生成しない

@return なし
*/
void createValidateStatement(AST * root, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist, ValidateVariableList *validate_variable_list,
											ValidateStatementList *validate_statement_list, ForInformationList *for_information_list, int undefined_control_check,
											int zero_divition_check, int array_unbound_check, int free_violation_check){
	//ASTの子ノードを参照させるためのイテレータ
	ASTListIterator ast_iterator;
	//ポインタでの位置が検証済みである、IDENTIFIERを無視するためのASTのアドレスリスト
	ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();
	//式の指標となるexpression_statementが見つけられたら
	if(CSTLString_compare_with_char(root->name, "expression_statement") == 0){
		//指定したノードから、代入式を探し出し、その検証内容をvalidate_statement_listへ入れる。
		getValidateStatementFromAssignStatement(root, function_information_list, vtlist, validate_variable_list, validate_statement_list, ignore_ast_list,
												root, undefined_control_check, zero_divition_check, array_unbound_check, free_violation_check);

	}
	//変数の定義である場合
	else if(CSTLString_compare_with_char(root->name, "declaration_with_init") == 0){
		//変数の初期定義を見つけ出し、それに基づいて検証内容をvalidate_statement_listへ入れる。
		getValidateStatementFromInitializer(root, function_information_list, vtlist, validate_variable_list, validate_statement_list, ignore_ast_list,
											root, undefined_control_check, zero_divition_check, array_unbound_check);
	}
	//for文系統が来た場合
	else if(CSTLString_compare_with_char(root->name, "for_statement_type_a") == 0 ||
		CSTLString_compare_with_char(root->name, "for_statement_type_b") == 0 ||
		CSTLString_compare_with_char(root->name, "for_statement_type_c") == 0 ||
		CSTLString_compare_with_char(root->name, "for_statement_type_d") == 0){

		//for文に関する情報を取得する
		getFOR_INFORMATION_LIST(for_information_list, root);

		//for文の末尾の情報から、検証式を取得し、検証式リストに入れる
		getValidateStatementFromForIteration(validate_statement_list, for_information_list, function_information_list, vtlist, validate_variable_list, ignore_ast_list,
			undefined_control_check, zero_divition_check, array_unbound_check , free_violation_check);
	}


	//ASTの子ノードも参照させる
	for(ast_iterator = ASTList_begin(root->children);
		ast_iterator != ASTList_end(root->children);
		ast_iterator = ASTList_next(ast_iterator)){

		createValidateStatement( ASTList_data(ast_iterator), function_information_list, vtlist,validate_variable_list,
				validate_statement_list, for_information_list, undefined_control_check, zero_divition_check, array_unbound_check, free_violation_check);

	}
}

/**
指定したASTノードrootから、assign_expressionを探しだし、そこからVARIDATE_STATEMENTに関する情報を取得する。
@param root 指定したノード
@param function_information_list 関数に関する情報のリスト
@param vtlist 対象の変数リスト
@param validate_variable_list 検証用変数リスト
@param validate_statement_list 取得した検証式が格納するところ
@param ignore_ast_list ポインタでの位置が検証済みである、IDENTIFIERを無視するためのASTのアドレスリスト
@param target_expression assign_expressionが属しているexpression_statement
@param undefined_control_check 未定義な処理（未定義ポインタの参照など）を行っていないかどうかを検証するための式を生成するかどうか １：生成する ０：生成しない
@param zero_divition_check 0で割っていないかどうかを検証するための式を生成するかどうか　１：生成する　０：生成しない
@param array_unbound_check 配列が範囲外を参照していないかどうかを検証するための式を生成するかどうか　１：生成する　０：生成しない
@param free_violation_check メモリ解放関係で不正な処理を行っていないかどうかを検証するための式を生成するかどうか　１：生成する　０：生成しない

@return なし
*/
void getValidateStatementFromAssignStatement(AST *root, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
											ValidateVariableList *validate_variable_list,
											ValidateStatementList *validate_statement_list, ASTPOINTER_LIST *ignore_ast_list,
											AST *target_expression, int undefined_control_check, int zero_divition_check, int array_unbound_check
											, int free_violation_check){
	//ASTの子ノードを参照させるためのイテレータ
	ASTListIterator ast_iterator;
	int mode = 0;

	//代入式を見つけた場合
	if(CSTLString_compare_with_char(root->name, "assignment_expression") == 0){
		int a_op_flag;

		//malloc関係の情報
		MEMALLOC_INFO * memalloc_info = NULL;
		//左辺値における各次元のポインタや配列のオフセットに関する情報のリスト
		ARRAY_OFFSET_LIST * left_array_offset_list = ARRAY_OFFSET_LIST_new();

		//右辺式における各次元のポインタや配列のオフセットに関する情報のリスト
		ARRAY_OFFSET_LIST * right_array_offset_list = ARRAY_OFFSET_LIST_new();

		AST *left_expression = ASTList_data(ASTList_begin(root->children));

		AST *right_expression = ASTList_data(ASTList_next(ASTList_next(ASTList_begin(root->children))));

		//除算および剰余に関する情報リスト
		DIVITION_INFORMATION_LIST *divition_information_list = DIVITION_INFORMATION_LIST_new();

		//代入式のタイプを取得する
		a_op_flag = getAssignment_TYPE(root);

		//代入式の左辺値について探索させる（子ノードの１番目の参照）
		getLeftAssignmentInfo(left_expression , function_information_list, vtlist, ignore_ast_list, left_array_offset_list, target_expression, &mode);
		//代入式の右辺式について探索させる（子ノードの３番目の参照）
		getRightAssignmentInfo(right_expression, function_information_list, vtlist, &memalloc_info, right_array_offset_list, ignore_ast_list, target_expression);

		//右辺式から、除算および剰余算に関する情報を格納させる
		getDIVITION_INFORMATION_LIST(right_expression, function_information_list, vtlist, divition_information_list, target_expression, ignore_ast_list);

		//DEBUG_MODEが有効な時メモリ確保関係の情報を出力する
		#ifdef DEBUG_MODE
			if(memalloc_info != NULL){
				printMEMALLOC_INFO(memalloc_info);
			}
		#endif

		//もし、malloc_infoから何らかの情報を取得できた場合
		if(memalloc_info != NULL){
			//malloc_infoやleft_array_offset_listから検証式を生成する
			createValidateStatementForMallocAction(validate_statement_list, memalloc_info, left_array_offset_list, validate_variable_list);

			//関数呼び出しを探し、その時の関数名がmallocまたはcallocの場合はmalloc用識別番号を入れるための変数を生成させる
			AST *call_function = NULL;
			CSTLString *function_name = CSTLString_new();

			call_function = getASTwithString(right_expression, "call_function", -1);

			getStringFromAST(function_name, ASTList_data(ASTList_begin(call_function->children)));

			if(call_function != NULL && (CSTLString_compare_with_char(function_name, "malloc") == 0 ||
				CSTLString_compare_with_char(function_name, "calloc") == 0)){

				getValidateStatementFromMallocNumber(validate_statement_list, call_function, left_array_offset_list, memalloc_info);

			}

			CSTLString_delete(function_name);
		}

		//もし、array_unbound_checkが有効になっていた場合、配列の範囲外参照を検証するための検証式を追加する

		//左辺値に対する配列範囲外参照を検証するための検証式を追加する
		if(ARRAY_OFFSET_LIST_size(left_array_offset_list) > 0){
			createCheckUnboundAndUndefineOperationCheck(validate_statement_list, left_array_offset_list, array_unbound_check, undefined_control_check);
		}
		//右辺式に対する配列範囲外参照を検証するための検証式を追加する
		if(ARRAY_OFFSET_LIST_size(right_array_offset_list) > 0){
			createCheckUnboundAndUndefineOperationCheck(validate_statement_list, right_array_offset_list, array_unbound_check, undefined_control_check);
		}


		//ゼロ除算のフラグが立っていた場合は、ゼロ除算および剰余がないかどうかをチェックするための検証式を追加する
		if(zero_divition_check == 1){
			createZeroDivitionCheck(validate_statement_list, divition_information_list);
		}
		//もし、memalloc_infoが何らかを取得した場合、その内容を開放する
		if(memalloc_info != NULL){
			free(memalloc_info);
		}
		//memalloc_infoが存在せず、なおかつ両辺になんらかのオフセット情報があれば、ポインタ演算式後の内容を検証用変数に反映するための検証式を追加する
		else if(ARRAY_OFFSET_LIST_size(left_array_offset_list) > 0 && ARRAY_OFFSET_LIST_size(left_array_offset_list) > 0){
			getValidateStatementFromPointerOperator(validate_statement_list, left_array_offset_list, right_array_offset_list, right_expression, a_op_flag);
		}

		//各次元のポインタや配列のオフセットに関する情報のリストを削除する
		ARRAY_OFFSET_LIST_clear(left_array_offset_list);
		ARRAY_OFFSET_LIST_delete(left_array_offset_list);
		ARRAY_OFFSET_LIST_clear(right_array_offset_list);
		ARRAY_OFFSET_LIST_delete(right_array_offset_list);

		//除算および剰余算に関する情報のリストを削除する
		DIVITION_INFORMATION_LIST_clear(divition_information_list);
		DIVITION_INFORMATION_LIST_delete(divition_information_list);


	}
	//t_assignment_expression(単一の式)が来た場合
	else if(CSTLString_compare_with_char(root->name, "t_assignment_expression") == 0){
		//除算および剰余に関する情報リスト
		DIVITION_INFORMATION_LIST *divition_information_list = DIVITION_INFORMATION_LIST_new();

		//単一の式から、オフセットリストを取得する
		ARRAY_OFFSET_LIST *array_offset_list = ARRAY_OFFSET_LIST_new();
		getARRAY_OFFSET_LIST(root, array_offset_list, function_information_list, vtlist, ignore_ast_list, target_expression);

		//式から、除算および剰余算に関する情報を格納させる
		getDIVITION_INFORMATION_LIST(root, function_information_list, vtlist, divition_information_list, target_expression, ignore_ast_list);

		//配列範囲外のチェックを入れている場合

		if(ARRAY_OFFSET_LIST_size(array_offset_list) > 0){
			createCheckUnboundAndUndefineOperationCheck(validate_statement_list, array_offset_list, array_unbound_check, undefined_control_check);
		}


		//ゼロ除算のフラグが立っていた場合は、ゼロ除算および剰余がないかどうかをチェックするための検証式を追加する
		if(zero_divition_check == 1){
			createZeroDivitionCheck(validate_statement_list, divition_information_list);
		}

		//インクリメントやデクリメントに対して、検証式を取得する。
		if(ARRAY_OFFSET_LIST_size(array_offset_list) > 0){
			createValidateStatemenFromIncDecExpr(validate_statement_list, array_offset_list);
		}
		ARRAY_OFFSET_LIST_clear(array_offset_list);
		ARRAY_OFFSET_LIST_delete(array_offset_list);

		//除算および剰余算に関する情報のリストを削除する
		DIVITION_INFORMATION_LIST_clear(divition_information_list);
		DIVITION_INFORMATION_LIST_delete(divition_information_list);
	}
	//call_functionが来た場合
	else if(CSTLString_compare_with_char(root->name, "call_function") == 0){
		FREEMEMINFO *freememinfo = NULL;

		getFreememInfo(&freememinfo, root, function_information_list, vtlist, target_expression);

		//もし、free解放関係の情報がきたら、出力する
		#ifdef DEBUG_MODE
			if(freememinfo != NULL){
				printFREEMEMINFO(freememinfo);
			}
		#endif
		//もし、メモリ解放関係の情報が取得できた場合
		if(freememinfo != NULL){
			//free_violation_flagが有効である場合
			if(free_violation_check == 1){
				//メモリ解放関数freeで禁止行為を行っていないかどうか確認するための検証式を生成する
				createViolentFreeOperation(validate_statement_list, freememinfo);
			}
			//メモリ解放関係の情報から検証式を生成する
			createValidateStatementForFreeAction(validate_statement_list, freememinfo, validate_variable_list);

		}
	}

	//ASTの子ノードも参照させる
	for(ast_iterator = ASTList_begin(root->children);
		ast_iterator != ASTList_end(root->children);
		ast_iterator = ASTList_next(ast_iterator)){

		getValidateStatementFromAssignStatement( ASTList_data(ast_iterator), function_information_list, vtlist, validate_variable_list, validate_statement_list, ignore_ast_list
												, target_expression, undefined_control_check, zero_divition_check, array_unbound_check, free_violation_check);

	}
}

/**
指定したASTノードrootから、init_declaratorを探しだし、そこからVARIDATE_STATEMENTに関する情報を取得する。
@param root 指定したノード
@param function_information_list 関数に関する情報のリスト
@param vtlist 対象の変数リスト
@param validate_variable_list 検証用変数リスト
@param validate_statement_list 取得した検証式が格納するところ
@param ignore_ast_list ポインタでの位置が検証済みである、IDENTIFIERを無視するためのASTのアドレスリスト
@param target_expression assign_expressionが属しているexpression_statement
@param undefined_control_check 未定義な処理を行っていないかどうかを検証するための式を生成するかどうか １：生成する ０：生成しない
@param zero_divition_check 0で割っていないかどうかを検証するための式を生成するかどうか　１：生成する　０：生成しない
@param array_unbound_check 配列が範囲外を参照していないかどうかを検証するための式を生成するかどうか　１：生成する　０：生成しない

@return なし
*/
void getValidateStatementFromInitializer(AST *root, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
											ValidateVariableList *validate_variable_list,ValidateStatementList *validate_statement_list, ASTPOINTER_LIST *ignore_ast_list,
											AST *target_expression, int undefined_control_check, int zero_divition_check, int array_unbound_check){
	//ASTの子ノードを参照させるためのイテレータ
	ASTListIterator ast_iterator;
	int mode = 0;

	//代入式を見つけた場合
	if(CSTLString_compare_with_char(root->name, "init_declarator") == 0){

		//代入式のフラグと文字列
		int a_op_flag;

		CSTLString *a_op_string = CSTLString_new();

		//malloc関係の情報
		MEMALLOC_INFO * memalloc_info = NULL;
		//変数の定義に対するノードにおける各次元のポインタや配列のオフセットに関する情報のリスト
		ARRAY_OFFSET_LIST * declarator_array_offset_list = ARRAY_OFFSET_LIST_new();

		//初期の式における各次元のポインタや配列のオフセットに関する情報のリスト
		ARRAY_OFFSET_LIST * initializer_array_offset_list = ARRAY_OFFSET_LIST_new();

		AST *declarator_expression = getASTwithString(ASTList_data(ASTList_begin(root->children)), "IDENTIFIER", -1);

		AST *initializer_expression = ASTList_data(ASTList_next(ASTList_next(ASTList_begin(root->children))));

		//変数テーブルから、変数の定義に対するノードに該当する情報を探し、それに対する配列オフセット情報を取得する。（子ノードの１番目の参照）
		getDeclaratorArrayOffset(declarator_array_offset_list, declarator_expression, target_expression, vtlist);
		//初期の式について探索させる（子ノードの３番目の参照）
		getRightAssignmentInfo(initializer_expression, function_information_list, vtlist, &memalloc_info, initializer_array_offset_list, ignore_ast_list, target_expression);

		//代入演算子を取得する
		getStringFromAST(a_op_string, ASTList_data(ASTList_next(ASTList_begin(root->children))));

		//もし=の場合
		if(CSTLString_compare_with_char(a_op_string, "=") == 0){
					a_op_flag = EQUAL;
		}
		//それ以外の場合は、エラーを出力し、強制終了させる
		else{
			fprintf(stderr,"#%s#:%d:Don't Assignment Operator %s!!",
					getFileName(), ASTList_data(ASTList_next(ASTList_begin(root->children)))->line, CSTLString_c_str(a_op_string));
			exit(1);
		}
		CSTLString_delete(a_op_string);

		//DEBUG_MODEが有効な時メモリ確保関係の情報を出力する
		#ifdef DEBUG_MODE
			if(memalloc_info != NULL){
				printMEMALLOC_INFO(memalloc_info);
			}
		#endif

		//もし、malloc_infoから何らかの情報を取得できた場合
		if(memalloc_info != NULL){
			//malloc_infoやdeclarator_array_offset_listから検証式を生成する
			createValidateStatementForMallocAction(validate_statement_list, memalloc_info, declarator_array_offset_list, validate_variable_list);

			//関数呼び出しを探し、その時の関数名がmallocまたはcallocの場合はmalloc用識別番号を入れるための変数を生成させる
			AST *call_function = NULL;
			CSTLString *function_name = CSTLString_new();

			call_function = getASTwithString(initializer_expression, "call_function", -1);

			getStringFromAST(function_name, ASTList_data(ASTList_begin(call_function->children)));

			if(call_function != NULL && (CSTLString_compare_with_char(function_name, "malloc") == 0 ||
				CSTLString_compare_with_char(function_name, "calloc") == 0)){

				getValidateStatementFromMallocNumber(validate_statement_list, call_function, declarator_array_offset_list, memalloc_info);

			}
			CSTLString_delete(function_name);
		}


		//初期の式に対する配列範囲外参照を検証するための検証式を追加する
		if(ARRAY_OFFSET_LIST_size(initializer_array_offset_list) > 0){
			createCheckUnboundAndUndefineOperationCheck(validate_statement_list, initializer_array_offset_list, array_unbound_check, undefined_control_check);
		}


		//もし、memalloc_infoが何らかを取得した場合、その内容を開放する
		if(memalloc_info != NULL){
			free(memalloc_info);
		}

		//plus_minus_flagは0にする。
		//memalloc_infoが存在せず、なおかつ両辺になんらかのオフセット情報があれば、ポインタ演算式後の内容を検証用変数に反映するための検証式を追加する
		else if(ARRAY_OFFSET_LIST_size(declarator_array_offset_list) > 0 && ARRAY_OFFSET_LIST_size(initializer_array_offset_list) > 0){
			getValidateStatementFromPointerOperator(validate_statement_list, declarator_array_offset_list, initializer_array_offset_list, initializer_expression, a_op_flag);
		}

		//各次元のポインタや配列のオフセットに関する情報のリストを削除する
		ARRAY_OFFSET_LIST_clear(declarator_array_offset_list);
		ARRAY_OFFSET_LIST_delete(declarator_array_offset_list);
		ARRAY_OFFSET_LIST_clear(initializer_array_offset_list);
		ARRAY_OFFSET_LIST_delete(initializer_array_offset_list);


	}

	//ASTの子ノードも参照させる
	for(ast_iterator = ASTList_begin(root->children);
		ast_iterator != ASTList_end(root->children);
		ast_iterator = ASTList_next(ast_iterator)){

		getValidateStatementFromInitializer( ASTList_data(ast_iterator), function_information_list, vtlist, validate_variable_list, validate_statement_list, ignore_ast_list
												, target_expression, undefined_control_check, zero_divition_check, array_unbound_check);

	}
}

/**
malloc用識別番号を付加するための関数に変換するための検証式を追加させる。
@param validate_statement_list 追加先の検証式リスト
@param call_function 関数呼び出しに対するノード
@param right_array_offset_list 左辺値に関する配列オフセットリスト
@param memalloc_info メモリ確保情報

@return なし
*/
void getValidateStatementFromMallocNumber(ValidateStatementList *validate_statement_list, AST *call_function, ARRAY_OFFSET_LIST* right_array_offset_list, MEMALLOC_INFO *memalloc_info){
	CSTLString *statement = CSTLString_new();
	CSTLString *variable = CSTLString_new();
	CSTLString *astalist = CSTLString_new();

	int offset_level_counter;

	ARRAY_OFFSET *array_offset = ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(right_array_offset_list));
	OFFSET_LISTIterator off_list_i;

	//変数名を取得する
	CSTLString_assign(variable, CSTLString_c_str(array_offset->variable_name));
	//配列オフセットリストから検証用変数の配列式を生成する
	offset_level_counter = createValidateVariableArrayExpression(variable, array_offset);

	//オフセットレベルが１の場合は、レベル１専用のmalloc_number関数として記述する
	if(offset_level_counter == 1){
		CSTLString_printf(statement, 0, "malloc(sizeof(%s)*(%s)) ; malloc_flag_1_%s = malloc(sizeof(int)) ; *malloc_flag_1_%s = malloc_number ; malloc_number++ ", CSTLString_c_str(memalloc_info->sizeof_type), CSTLString_c_str(memalloc_info->size),
				CSTLString_c_str(variable), CSTLString_c_str(variable));
	}
	//そうでない場合は、標準のmalloc_number関数として記述する
	else{
		CSTLString_printf(statement, 0, "malloc(sizeof(%s)*(%s)) ; malloc_flag_%d_%s = malloc_number ; malloc_number++ ", CSTLString_c_str(memalloc_info->sizeof_type), CSTLString_c_str(memalloc_info->size),
		offset_level_counter, CSTLString_c_str(variable));
	}

	//検証式の追加
	ValidateStatementList_push_back_ref(validate_statement_list,
		new_VALIDATE_STATEMENT(
			getNewValidateStatementID(validate_statement_list, call_function),
			MODIFY_VS,
			VALIDATE_NOTUSED,
			statement,
			call_function
		)
	);

	CSTLString_delete(astalist);
}

/**
for文の末尾の情報から、検証式を取得し、検証式リストに入れる。
@param validate_statement_list 取得した検証式が格納するところ
@param for_information_list for文に関する情報のリスト
@param function_information_list 関数に関する情報のリスト
@param vtlist 対象の変数リスト
@param validate_variable_list 検証用変数リスト
@param ignore_ast_list ポインタでの位置が検証済みである、IDENTIFIERを無視するためのASTのアドレスリスト
@param undefined_control_check 未定義な処理を行っていないかどうかを検証するための式を生成するかどうか １：生成する ０：生成しない
@param zero_divition_check 0で割っていないかどうかを検証するための式を生成するかどうか　１：生成する　０：生成しない
@param array_unbound_check 配列が範囲外を参照していないかどうかを検証するための式を生成するかどうか　１：生成する　０：生成しない
@param free_violation_check メモリ解放関係で不正な処理を行っていないかどうかを検証するための式を生成するかどうか　１：生成する　０：生成しない

@return なし
*/
void getValidateStatementFromForIteration(ValidateStatementList *validate_statement_list, ForInformationList *for_information_list,
										FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,ValidateVariableList *validate_variable_list,
										ASTPOINTER_LIST *ignore_ast_list, int undefined_control_check,int zero_divition_check,int array_unbound_check,
										int free_violation_check){
	//for文の末尾の情報を取得する
	ForInformation *target_for_information = ForInformationList_data(ForInformationList_rbegin(for_information_list));

	//for文の初期式の情報から、検証式を生成させる
	getValidateStatementFromAssignStatement(target_for_information->init_expression, function_information_list, vtlist, validate_variable_list, validate_statement_list, ignore_ast_list,
											target_for_information->init_expression, undefined_control_check, zero_divition_check, array_unbound_check, free_violation_check);
	//for文の増分式の情報から、検証式を生成させる
	getValidateStatementFromAssignStatement(target_for_information->inc_dec_expression, function_information_list, vtlist, validate_variable_list, validate_statement_list, ignore_ast_list,
											target_for_information->inc_dec_expression, undefined_control_check, zero_divition_check, array_unbound_check, free_violation_check);

}

/**
ポインタ演算式後の内容を検証用変数に反映するための検証式を追加する。

@param validate_statement_list 検証式リスト
@param left_array_offset_list 左辺値の配列オフセットリスト
@param right_array_offset_list 右辺式の配列オフセットリスト
@param right_expression 右辺式へのＡＳＴアドレス
@param a_op_flag 代入演算子が何かを示すフラグ 0:=,1:+=,2:-=,3:*=,4:/=,5:%=,6:<<=,7:>>=,8:&=,9:|=,10:^=
@return なし
*/
void getValidateStatementFromPointerOperator(ValidateStatementList *validate_statement_list,ARRAY_OFFSET_LIST *left_array_offset_list,ARRAY_OFFSET_LIST *right_array_offset_list, AST *right_expression, int a_op_flag){
	//アドレス演算後の基本的な位置
	CSTLString *basis_location_out = CSTLString_new();
	CSTLString *left_variable_name = CSTLString_new();
	CSTLString *right_variable_name = CSTLString_new();

	//配列オフセットの内容に対するイテレータ
	OFFSET_LISTIterator off_list_i;
	//追加する検証式の内容
	CSTLString *statement;

	int left_offset_level;
	int right_offset_level;

	int right_array_counter;

	int validate_statement_id;

	//右辺式からbasis_locationを求める
	getBasisLocationFromAssignmentExpression(basis_location_out, left_array_offset_list,
										  right_array_offset_list, right_expression, a_op_flag);
	#ifdef DEBUG_MODE
		printf("basis_location = \"%s\"\n",CSTLString_c_str(basis_location_out));
	#endif

	//basis_locationがなんらかの式を取得できたとき
	if(CSTLString_size(basis_location_out) > 0){
		//左辺式から、一番頭であるポインタのオフセットを求める
		ARRAY_OFFSET *left_array_offset = ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(left_array_offset_list));
		//右辺値から、演算後のポインタレベルが最大である変数のオフセット情報へのアドレスを求める
		ARRAY_OFFSET *right_array_offset;
		//もし、右辺値から、演算後のポインタレベルが最大値が0でない場合
		if(maxOffsetLevelFromArrayOffsetList(right_array_offset_list) != 0){
			//右辺値から、演算後のポインタレベルが最大である変数のオフセット情報へのアドレスを求める
			right_array_offset = maxOffsetLevelAddressFromArrayOffsetList(right_array_offset_list);
		}
		//そうでない場合で、代入演算子が+=か-=が来ている場合
		else if(a_op_flag == PLUS_EQUAL || a_op_flag == MINUS_EQUAL){
			//左辺値の配列オフセットリストを入れる
			right_array_offset = ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(left_array_offset_list));
		}
		//上記外の場合はエラーを出力し、強制終了させる
		else{
			fprintf(stderr,"#%s#:%d:Invalid Pointer Operation!!\n", getFileName(),left_array_offset->target_statement->line);
			exit(1);
		}

		//左辺の変数名を取得する
		createArrayExpression(left_variable_name, left_array_offset, OFFSET_LIST_size(left_array_offset->offset_list));
		//右辺の変数名を取得する
		createArrayExpression(right_variable_name, right_array_offset, OFFSET_LIST_size(right_array_offset->offset_list));

		left_offset_level = OFFSET_LIST_size(left_array_offset->offset_list) + right_array_offset->anpasand_flag + 1;
		right_offset_level = OFFSET_LIST_size(right_array_offset->offset_list) - right_array_offset->anpasand_flag + 1;

		statement = CSTLString_new();
		//右辺値で、アドレス演算子を含めた場合は、第一レベルに関しては、次のように代入させる
		//配列サイズ：１、基本位置：０、静的変数
		if(right_array_offset->anpasand_flag == 1){

			CSTLString_printf(statement, 1, "max_size_%d_%s = malloc(sizeof(int)); *max_size_%d_%s = 1; ", left_offset_level - 1, CSTLString_c_str(left_variable_name)
					, left_offset_level - 1, CSTLString_c_str(left_variable_name));
			CSTLString_printf(statement, 1, "basis_location_%d_%s = %s; ", left_offset_level - 1, CSTLString_c_str(left_variable_name), CSTLString_c_str(basis_location_out));
			CSTLString_printf(statement, 1, "defined_%d_%s = malloc(sizeof(int)); *defined_%d_%s = 1; ", left_offset_level - 1, CSTLString_c_str(left_variable_name),
					left_offset_level - 1, CSTLString_c_str(left_variable_name));
			CSTLString_printf(statement, 1, "malloc_flag_%d_%s = malloc(sizeof(int)); *malloc_flag_%d_%s = 0; ", left_offset_level - 1, CSTLString_c_str(left_variable_name)
					, left_offset_level - 1, CSTLString_c_str(left_variable_name));

			right_offset_level++;

			while(left_offset_level <= left_array_offset->pointer_level + left_array_offset->array_level){

				CSTLString_printf(statement, 1, "max_size_%d_%s = &max_size_%d_%s; ", left_offset_level, CSTLString_c_str(left_variable_name), right_offset_level, CSTLString_c_str(right_variable_name));
				CSTLString_printf(statement, 1, "basis_location_%d_%s = &basis_location_%d_%s; ", left_offset_level, CSTLString_c_str(left_variable_name), right_offset_level, CSTLString_c_str(right_variable_name));
				CSTLString_printf(statement, 1, "defined_%d_%s = &defined_%d_%s; ", left_offset_level, CSTLString_c_str(left_variable_name), right_offset_level, CSTLString_c_str(right_variable_name));
				CSTLString_printf(statement, 1, "malloc_flag_%d_%s = &malloc_flag_%d_%s; ", left_offset_level, CSTLString_c_str(left_variable_name), right_offset_level, CSTLString_c_str(right_variable_name));

				left_offset_level++;
				right_offset_level++;
			}
		}
		//そうでない場合
		else{
			//もし、左辺値と右辺値が完全一致した場合は、basis_locationのみを変更させる
			if(CSTLString_compare(left_variable_name, right_variable_name) == 0){
				CSTLString_printf(statement, 1, "basis_location_%d_%s = %s; ", left_offset_level, CSTLString_c_str(left_variable_name), CSTLString_c_str(basis_location_out));
			}else{
				CSTLString_printf(statement, 1, "max_size_%d_%s = max_size_%d_%s; ", left_offset_level, CSTLString_c_str(left_variable_name), right_offset_level, CSTLString_c_str(right_variable_name));
				CSTLString_printf(statement, 1, "basis_location_%d_%s = %s; ", left_offset_level, CSTLString_c_str(left_variable_name), CSTLString_c_str(basis_location_out));
				CSTLString_printf(statement, 1, "defined_%d_%s = defined_%d_%s; ", left_offset_level, CSTLString_c_str(left_variable_name), right_offset_level, CSTLString_c_str(right_variable_name));
				CSTLString_printf(statement, 1, "malloc_flag_%d_%s = malloc_flag_%d_%s; ", left_offset_level, CSTLString_c_str(left_variable_name), right_offset_level, CSTLString_c_str(right_variable_name));

				left_offset_level++;
				right_offset_level++;

				while(left_offset_level <= left_array_offset->pointer_level + left_array_offset->array_level){
					CSTLString_printf(statement, 1, "max_size_%d_%s = max_size_%d_%s; ", left_offset_level, CSTLString_c_str(left_variable_name), right_offset_level, CSTLString_c_str(right_variable_name));
					CSTLString_printf(statement, 1, "basis_location_%d_%s = basis_location_%d_%s; ", left_offset_level, CSTLString_c_str(left_variable_name), right_offset_level, CSTLString_c_str(right_variable_name));
					CSTLString_printf(statement, 1, "defined_%d_%s = defined_%d_%s; ", left_offset_level, CSTLString_c_str(left_variable_name), right_offset_level, CSTLString_c_str(right_variable_name));
					CSTLString_printf(statement, 1, "malloc_flag_%d_%s = malloc_flag_%d_%s; ", left_offset_level, CSTLString_c_str(left_variable_name), right_offset_level, CSTLString_c_str(right_variable_name));

					left_offset_level++;
					right_offset_level++;
				}
			}

		}

		//IDを付加する
		validate_statement_id = getNewValidateStatementID(validate_statement_list, left_array_offset->target_statement);

		//検証式リストに追加
		ValidateStatementList_push_back_ref(validate_statement_list, new_VALIDATE_STATEMENT( validate_statement_id, 1, VALIDATE_NOTUSED, statement, left_array_offset->target_statement));

	}
	//アドレス演算後の基本的な位置を削除する
	CSTLString_delete(basis_location_out);
}

/**
式から、関数呼出を探しだし、関数呼出に対する検証式を追加する。

@param root 探索対象のASTノード
@param validate_statement_list 検証式リスト
@param left_array_offset_list 左辺値の配列オフセットリスト
@param right_array_offset_list 右辺式の配列オフセットリスト
@param function_information_list 関数に関する情報リスト

@return なし
 */
void getValidateStatementFromCallFunction(AST *root, ValidateStatementList *validate_statement_list, ARRAY_OFFSET_LIST *left_array_offset_list,
		ARRAY_OFFSET_LIST *right_array_offset_list, FUNCTION_INFORMATION_LIST *function_information_list){
	CSTLString *function_name;

	CSTLString *call_function_statement;

	FUNCTION_INFORMATION *function_information;

	PARAM_INFORMATION_LISTIterator p_info_i;

	ARRAY_OFFSET *main_array_offset;

	CSTLString *basis_location_expr;

	CSTLString *array_content;

	CSTLString *astalisk;

	int arg_num;

	int level, out_level;

	int success_flag = FALSE;

	AST *argument;

	ASTListIterator ast_p;


	//関数呼出を探索し、見つけた場合
	if(CSTLString_compare_with_char(root->name, "call_function") == 0){
		//関数名を取得する
		function_name = CSTLString_new();
		getStringFromAST(function_name, ASTLIST_ITERATOR_1(root));

		//関数呼び出しに対応する関数定義の情報を読み出す
		function_information = searchFUNCTION_INFORMATION(function_name, function_information_list);

		//関数定義の読み出しに成功し、標準ライブラリ関数でない場合
		if(function_information != NULL && function_information->function_node != NULL){
			//関数呼出で置き換える検証式を初期化する
			call_function_statement = CSTLString_new();

			//既存の関数呼出を取得し、終わり括弧を削除する
			getStringFromAST(call_function_statement, root);
			CSTLString_pop_back(call_function_statement);

			//第一引数から読みだす
			for(arg_num = 1 , p_info_i = PARAM_INFORMATION_LIST_begin(function_information->param_information_list);
				p_info_i != PARAM_INFORMATION_LIST_end(function_information->param_information_list);
				arg_num++, p_info_i = PARAM_INFORMATION_LIST_next(p_info_i)){
				//関数定義の情報から、引数のポインタレベルと配列レベルの合計が１以上の場合
				if(PARAM_INFORMATION_LIST_data(p_info_i)->array_level +
				   PARAM_INFORMATION_LIST_data(p_info_i)->pointer_level
						>= 1){
					//引数へのASTノードを取得し、失敗した場合探索を終了させる
					argument = NULL;
					getArgumentAST(&argument,root,arg_num);
					if(argument == NULL){
						break;
					}

					//検証式の生成に成功したフラグを立てる
					success_flag = TRUE;

					//その引数のメインとなる変数を引っ張り出す
					if(right_array_offset_list != NULL){
						main_array_offset = searchOffsetLevelAddressFromArrayOffsetList(argument, right_array_offset_list,
								PARAM_INFORMATION_LIST_data(p_info_i)->pointer_level,
								PARAM_INFORMATION_LIST_data(p_info_i)->array_level);
					}else{
						main_array_offset = searchOffsetLevelAddressFromArrayOffsetList(argument, left_array_offset_list,
								PARAM_INFORMATION_LIST_data(p_info_i)->pointer_level,
								PARAM_INFORMATION_LIST_data(p_info_i)->array_level);
					}
					//メインとなる引数の取得に成功した場合
					if(main_array_offset != NULL){

						level = PARAM_INFORMATION_LIST_data(p_info_i)->array_level +
								   PARAM_INFORMATION_LIST_data(p_info_i)->pointer_level;

						//オフセット情報から配列式を生成する
						array_content = CSTLString_new();
						createValidateVariableArrayExpression(array_content, main_array_offset);

						//アドレス演算子を挟んでいる場合は、ダミー変数を関数呼出の検証式に追加する。
						if(main_array_offset->anpasand_flag == 1){
							CSTLString_printf(call_function_statement, 1, "&d_max_size, d_basis_location, &d_defined, &d_malloc_flag");
						}
						//そうでない場合
						else{

							//引数の式からbasis_location式を生成する
							basis_location_expr = CSTLString_new();
							getBasisLocationFromExpression(basis_location_expr, main_array_offset, argument);
							//検証用変数を追加する。
							CSTLString_printf(call_function_statement, 1, "max_size_%d_%s%s, %s, defined_%d_%s%s, malloc_flag_%d_%s%s",
									level, CSTLString_c_str(main_array_offset->variable_name), CSTLString_c_str(array_content),
									CSTLString_c_str(basis_location_expr),
									level, CSTLString_c_str(main_array_offset->variable_name), CSTLString_c_str(array_content),
									level, CSTLString_c_str(main_array_offset->variable_name), CSTLString_c_str(array_content));
						}
						astalisk = CSTLString_new();
						CSTLString_assign(astalisk, "*");
						//レベル２以降の検証用変数を関数呼び出しに追加する
						for(out_level = 2 ; out_level <= PARAM_INFORMATION_LIST_data(p_info_i)->array_level +
						   PARAM_INFORMATION_LIST_data(p_info_i)->pointer_level; out_level++){
							CSTLString_printf(call_function_statement, 1, ", %smax_size_%d_%s%s, %sbasis_location_%d_%s%s, %sdefined_%d_%s%s, %smalloc_flag_%d_%s%s",
									CSTLString_c_str(astalisk), level + out_level - 1, CSTLString_c_str(main_array_offset->variable_name), CSTLString_c_str(array_content),
									CSTLString_c_str(astalisk), level + out_level - 1, CSTLString_c_str(main_array_offset->variable_name), CSTLString_c_str(array_content),
									CSTLString_c_str(astalisk), level + out_level - 1, CSTLString_c_str(main_array_offset->variable_name), CSTLString_c_str(array_content),
									CSTLString_c_str(astalisk), level + out_level - 1, CSTLString_c_str(main_array_offset->variable_name), CSTLString_c_str(array_content));
						}


						CSTLString_delete(array_content);
					}
				}
			}
			//終わりかっこを継ぎ足す
			CSTLString_printf(call_function_statement, 1, ")");

			//検証式が完全に完成できた場合
			if(success_flag){
				//置き換える検証式を検証式リストに追加する
				ValidateStatementList_push_back_ref(validate_statement_list,
						new_VALIDATE_STATEMENT(
								getNewValidateStatementID(validate_statement_list, root),
								MODIFY_VS,
								VALIDATE_NOTUSED,
								call_function_statement,
								root)
							);
			}
			//そうでなければ、検証式の式を削除する
			else{
				CSTLString_delete(call_function_statement);
			}
		}
	}

	//子ノードについても同じ処理を行う
	for(ast_p = ASTList_begin(root->children);
		ast_p != ASTList_end(root->children);
		ast_p = ASTList_next(ast_p)){
		getValidateStatementFromCallFunction(ASTList_data(ast_p), validate_statement_list,
				left_array_offset_list, right_array_offset_list, function_information_list);
	}
}

/**
ポインタ演算式に対して、ポインタ演算における基本的な位置の式を文字列として求め、outputに入れる。
@param output 出力先のCSTL文字列
@param left_array_offset_list 左辺値の配列オフセットリスト
@param right_array_offset_list 右辺式の配列オフセットリスト
@param right_expression_ast 右辺式へのASTアドレス
@param a_op_flag 代入演算子が何かを示すフラグ 0:=,1:+=,2:-=,3:*=,4:/=,5:%=,6:<<=,7:>>=,8:&=,9:|=,10:^=

@return なし

*/
void getBasisLocationFromAssignmentExpression(CSTLString *output, ARRAY_OFFSET_LIST *left_array_offset_list,
											  ARRAY_OFFSET_LIST *right_array_offset_list, AST *right_expression_ast, int a_op_flag){
	//左辺値のポインタレベル
	int left_pointer_level;

	int right_pointer_level;

	OFFSET_LISTIterator off_list_i;

	ARRAY_OFFSET *left_array_offset = ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(left_array_offset_list));

	int offset_level_counter;

	CSTLString *variable;

	//左辺値の配列オフセットリストの最初に対するポインタレベルを求める
	left_pointer_level = getOffsetLevelFromArrayOffset(left_array_offset);
	//左辺値のポインタレベルが１以上の場合（すなわち、ポインタ演算式の場合）
	if(left_pointer_level >= 1){
			//右辺式全体の最大ポインタレベルを求める
			right_pointer_level = maxOffsetLevelFromArrayOffsetList(right_array_offset_list);

			//右辺式全体の最大ポインタレベルである配列オフセットがNULLで左辺値と右辺式のポインタレベルが等しい場合
			if(left_pointer_level == right_pointer_level){
				//右辺式全体の最大ポインタレベルである配列オフセットへのアドレス
				ARRAY_OFFSET *right_pointer_array_offset = maxOffsetLevelAddressFromArrayOffsetList(right_array_offset_list);
				//もし、代入演算子が=でなければエラーを出力し、強制終了させる

				//右辺式からアドレスの基本的な位置の式を求める。
				CSTLString_assign(output, "");
				getBasisLocationFromExpression(output, right_pointer_array_offset, right_expression_ast);

				//もし、&フラグが立っていてなおかつ、配列オフセットにオフセットデータが存在するなら、配列オフセットの末尾のデータを追加する
				if(right_pointer_array_offset->anpasand_flag == 1 && OFFSET_LIST_size(right_pointer_array_offset->offset_list) != 0){
					CSTLString_printf(output, 1, " + ( %s )", *OFFSET_LIST_data(OFFSET_LIST_rbegin(right_pointer_array_offset->offset_list)));
				}
			}
			//もし、右辺式全体の最大ポインタレベルが0である場合
			else if(right_pointer_level == 0){
				//もし、代入演算子が+=の場合
				if(a_op_flag == PLUS_EQUAL){


					//右辺式を取得する
					CSTLString *right_expression = CSTLString_new();
					getStringFromAST(right_expression, right_expression_ast);

					variable = CSTLString_new();
					CSTLString_assign(variable, CSTLString_c_str(ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(left_array_offset_list))->variable_name));
					//配列オフセットリストから配列式を生成し、追加する
					offset_level_counter = OFFSET_LIST_size(ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(left_array_offset_list))->offset_list);
					createArrayExpression(variable, ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(left_array_offset_list)), offset_level_counter);


					//次の形式で代入させるbasis_location_左辺式のオフセットレベル_左辺式の変数名[配列] + (右辺式)
					if(offset_level_counter == 1){

						CSTLString_printf(output, 0, "basis_location_1_%s + ( %s )",
							CSTLString_c_str(ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(left_array_offset_list))->variable_name),
									CSTLString_c_str(right_expression));

					}else{

						CSTLString_printf(output, 0, "basis_location_%d_%s + ( %s )",
								offset_level_counter, CSTLString_c_str(variable),
										CSTLString_c_str(right_expression));


					}


					CSTLString_delete(right_expression);
					CSTLString_delete(variable);

				}
				//もし、代入演算子が-=の場合
				else if(a_op_flag == MINUS_EQUAL){

					//右辺式を取得する
					CSTLString *right_expression = CSTLString_new();

					getStringFromAST(right_expression, right_expression_ast);

					variable = CSTLString_new();
					CSTLString_assign(variable, CSTLString_c_str(ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(left_array_offset_list))->variable_name));
					//配列オフセットリストから機能を生成する
					offset_level_counter = OFFSET_LIST_size(ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(left_array_offset_list))->offset_list);
					createArrayExpression(variable, ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(left_array_offset_list)), offset_level_counter);


					//次の形式で代入させるbasis_location_左辺式のオフセットレベル_左辺式の変数名[配列] - (右辺式)
					if(offset_level_counter == 1){
						CSTLString_printf(output, 0, "basis_location_1_%s - ( %s )",
								CSTLString_c_str(ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(left_array_offset_list))->variable_name),
										CSTLString_c_str(right_expression));
					}else{
						CSTLString_printf(output, 0, "basis_location_%d_%s%s - ( %s )",
								offset_level_counter,CSTLString_c_str(variable) , CSTLString_c_str(right_expression));
					}


					CSTLString_delete(variable);
				}
				//上記以外の場合は、エラーを出力し、強制終了させる。
				else{
					fprintf(stderr,"#%s#:%d:Invalid pointer operation!", getFileName(), right_expression_ast->line);
					exit(1);
				}
			}
			//上記以外の場合は、エラーを出力し、強制終了させる。
			else{
				fprintf(stderr,"#%s#:%d:Invalid pointer operation!", getFileName(), right_expression_ast->line);
				exit(1);
			}
	}


}

/**
getBasisLocationFromExpressionの内部処理
@param output 出力先のCSTL文字列
@param array_offset 指定した識別子の配列オフセット
@param expression_ast 指定した式へのASTアドレス
*/
void getBasisLocationFromExpression_Internal(CSTLString *output, ARRAY_OFFSET *array_offset, AST *expression_ast){


	ASTListIterator ast_iterator;
	OFFSET_LISTIterator off_list_i;

	int counter;

	//もし、直接参照や配列参照またはアドレス参照を見つけた場合
	if(CSTLString_compare_with_char(expression_ast->name, "direct_ref") == 0 ||
		CSTLString_compare_with_char(expression_ast->name, "array_access") == 0 ||
		CSTLString_compare_with_char(expression_ast->name, "address_ref") == 0){
			//もし、array_offsetの対象としているASTアドレスを見つけられた場合
			if(findASTAddress(expression_ast, array_offset->variable_address) == 1){
				//もし、ポインタレベルもしくは、配列レベルが１以上の場合は、その変数のbasis_locationを入れる
				if(array_offset->pointer_level >= 1 || array_offset->array_level >= 1){

					CSTLString_printf(output, 1, "basis_location_%d_%s", 1 + OFFSET_LIST_size(array_offset->offset_list) - array_offset->anpasand_flag, CSTLString_c_str(array_offset->variable_name));

					for(counter = 0, off_list_i = OFFSET_LIST_begin(array_offset->offset_list);
						counter < OFFSET_LIST_size(array_offset->offset_list) - array_offset->anpasand_flag && off_list_i != OFFSET_LIST_end(array_offset->offset_list);
						counter++, off_list_i = OFFSET_LIST_next(off_list_i)){
						CSTLString_printf(output, 1, "[ %s ]", *OFFSET_LIST_data(off_list_i));
					}

					CSTLString_append(output, " ");
				}
				//そうでない場合は０にする
				else{
					CSTLString_append(output, "0 ");
				}
			}
			//そうでなければ、ASTの子ノードも参照させる
			else{

				for(ast_iterator = ASTList_begin(expression_ast->children);
					ast_iterator != ASTList_end(expression_ast->children);
					ast_iterator = ASTList_next(ast_iterator)){

					getBasisLocationFromExpression_Internal( output, array_offset, ASTList_data(ast_iterator));

				}
			}
	}
	//もし、識別子である場合
	else if(CSTLString_compare_with_char(expression_ast->name, "IDENTIFIER") == 0){
		//もし、その識別子のASTノードが、array_offsetの対象としているASTアドレスであるなら、それを0に変える
		if(expression_ast == array_offset->variable_address){
				//もし、ポインタレベルもしくは、配列レベルが１以上の場合は、その変数のbasis_location_1を入れる
				if(array_offset->pointer_level >= 1 || array_offset->array_level >= 1){

					CSTLString_printf(output, 1, "basis_location_%d_%s", 1 + OFFSET_LIST_size(array_offset->offset_list) - array_offset->anpasand_flag, CSTLString_c_str(array_offset->variable_name));

					for(counter = 0, off_list_i = OFFSET_LIST_begin(array_offset->offset_list);
						counter < OFFSET_LIST_size(array_offset->offset_list) - array_offset->anpasand_flag && off_list_i != OFFSET_LIST_end(array_offset->offset_list);
						counter++, off_list_i = OFFSET_LIST_next(off_list_i)){
						CSTLString_printf(output, 1, "[ %s ]", *OFFSET_LIST_data(off_list_i));
					}

					CSTLString_append(output, " ");
				}else{
					CSTLString_append(output, "0 ");
				}
		}
		//そうでなければ、その変数自体を出力する
		else{
			CSTLString_append(output, CSTLString_c_str(expression_ast->content));
			CSTLString_append(output, " ");
		}
	}
	//リーフノードである場合はそのまま出力させる
	else if(ASTList_size(expression_ast->children) == 0){
		CSTLString_append(output, CSTLString_c_str(expression_ast->content));
		CSTLString_append(output, " ");
	}
	//上記以外の場合
	else{
		//ASTの子ノードも参照させる
		for(ast_iterator = ASTList_begin(expression_ast->children);
			ast_iterator != ASTList_end(expression_ast->children);
			ast_iterator = ASTList_next(ast_iterator)){

			getBasisLocationFromExpression_Internal( output, array_offset, ASTList_data(ast_iterator));

		}
	}
}

/**
指定した式expression_astから、ポインタ演算における基本的な位置の式を文字列として求め、outputに入れる。このとき、array_offsetを見つけたらそれに該当する式を０に変換する。
@param output 出力先のCSTL文字列
@param array_offset 指定した識別子の配列オフセット
@param expression_ast 指定した式へのASTアドレス
@return なし
*/
void getBasisLocationFromExpression(CSTLString *output, ARRAY_OFFSET *array_offset, AST *expression_ast){
	getBasisLocationFromExpression_Internal(output, array_offset, expression_ast);

	//文字列の末尾が半角スペースのとき、それを削除する
	if(CSTLString_size(output) > 0 && *CSTLString_at(output, CSTLString_size(output) - 1) == ' '){
		CSTLString_pop_back(output);
	}
}

/**
メモリ確保関係の情報memalloc_infoや配列やポインタのオフセット情報array_offset_listから検証式を生成し、validate_statement_listに追加する。

@param variable_statement_list 生成先の検証式リスト
@param memalloc_info メモリ確保関係の情報
@param array_offset_list 配列やポインタのオフセット情報
@param validate_variable_list 検証用変数リスト

@return なし
*/
void createValidateStatementForMallocAction(ValidateStatementList *validate_statement_list, MEMALLOC_INFO *memalloc_info,
										ARRAY_OFFSET_LIST *array_offset_list,ValidateVariableList *validate_variable_list){

	//array_offset_listのデータ
	ARRAY_OFFSET *array_offset = ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(array_offset_list));
	//array_offsetのオフセットリストで参照するのに使用するイテレータ
	OFFSET_LISTIterator off_list_i;
	//validate_variableに対するイテレータ
	ValidateVariableListIterator validate_variable_iterator;
	//array_offset_listからオフセットの深さを取得する。
	int array_offset_depth = OFFSET_LIST_size(array_offset->offset_list);

	//ポインタレベル
	int pointer_level;

	int i;

	for(validate_variable_iterator = ValidateVariableList_begin(validate_variable_list);
		validate_variable_iterator != ValidateVariableList_end(validate_variable_list);
		validate_variable_iterator = ValidateVariableList_next(validate_variable_iterator)){

			//検証用のオフセットレベルがオフセットの深さより大きい場合
			if(ValidateVariableList_data(validate_variable_iterator)->offset_level > array_offset_depth){
				//array_offsetの変数名と一致する検証用変数を見つけ、なおかつarray_offsetの位置している式の行番号が検証用変数の有効範囲に入っている場合
				if(CSTLString_compare(array_offset->variable_name, ValidateVariableList_data(validate_variable_iterator)->target_variable_name) == 0 &&
					ValidateVariableList_data(validate_variable_iterator)->enable_start <= array_offset->target_statement->line &&
					array_offset->target_statement->line <= ValidateVariableList_data(validate_variable_iterator)->enable_end
					) {
						//追加する検証式のデータ
						ValidateStatement *new_validate_statement;

						//validate_statement_listの識別番号
						int validate_statement_list_id;

						int offset_level_counter;

						CSTLString *statement = CSTLString_new();

						CSTLString *variable = CSTLString_new();
						//検証用変数名を取得
						CSTLString_printf(variable, 0, "%s", CSTLString_c_str(ValidateVariableList_data(validate_variable_iterator)->variable_name));
						//配列オフセットから配列式を生成し、追加する
						createValidateVariableArrayExpression(variable, array_offset);

						//検証式のオフセットレベルが、実際の配列のオフセットレベル＋１と等しい場合（すなわち、左辺の値と同じようなオフセットレベルと同じ場合）
						if(ValidateVariableList_data(validate_variable_iterator)->offset_level == array_offset_depth + 1){
							//もしmax_size系（動的配列の数を示すもの）の場合
							if(CSTLString_find(variable, "max_size_", 0) == 0){
								//もし、オフセットレベルが２以上の場合は、必ず動的に変数を取得してから値を入れる
								if(ValidateVariableList_data(validate_variable_iterator)->offset_level >= 2){
									CSTLString_printf(statement, 1, "%s = malloc(sizeof(int)); ",CSTLString_c_str(variable));
								}
								CSTLString_printf(statement, 1,"*%s = %s;", CSTLString_c_str(variable), CSTLString_c_str(memalloc_info->size));

							}
							//もしbasis_location系（配列の位置を示すもの）の場合
							else if(CSTLString_find(variable, "basis_location_", 0) == 0){

								CSTLString_printf(statement, 1,"%s = 0;",CSTLString_c_str(variable));

							}
							//もしdefined系（ポインタが何らかの変数のアドレスを設定しているかを示すもの）の場合
							else if(CSTLString_find(variable, "defined_", 0) == 0){
								//もし、オフセットレベルが２以上の場合は、必ず動的に変数を取得してから値を入れる
								if(ValidateVariableList_data(validate_variable_iterator)->offset_level >= 2){
									CSTLString_printf(statement, 1, "%s = malloc(sizeof(int)); ",CSTLString_c_str(variable));
								}
								CSTLString_printf(statement, 1,"*%s = 1;", CSTLString_c_str(variable));

							}
							//もしmalloc_flag_系（ポインタが動的に割り当てられているかを示すもの）の場合
							else if(CSTLString_find(variable, "malloc_flag_", 0) == 0){
								//もし、オフセットレベルが２以上の場合は、必ず動的に変数を取得してから値を入れる
								if(ValidateVariableList_data(validate_variable_iterator)->offset_level >= 2){
									CSTLString_printf(statement, 1, "%s = malloc(sizeof(int)); ",CSTLString_c_str(variable));
								}
								CSTLString_printf(statement, 1,"*%s = 1;", CSTLString_c_str(variable));


							}else{
								fprintf(stderr,"不正な検証式です。\n");
								exit(1);
							}
						}
						//そうでない場合
						else{
							//malloc関数で検証式に対して新しい領域を確保する。
							if(CSTLString_find(variable, "basis_location_", 0) != CSTL_NPOS){
								CSTLString_printf(statement, 1,"%s = malloc((%s)*sizeof(int", CSTLString_c_str(variable), CSTLString_c_str(memalloc_info->size));
							}else{
								CSTLString_printf(statement, 1,"%s = malloc((%s)*sizeof(int*", CSTLString_c_str(variable), CSTLString_c_str(memalloc_info->size));
							}
							//ポインタ記号を追加する。
							for(i = array_offset_depth + 2; i < ValidateVariableList_data(validate_variable_iterator)->offset_level;
								i++){
								CSTLString_printf(statement, 1,"*");
							}
							//関数を閉じる
							CSTLString_printf(statement, 1,"));");
						}

						//validate_statement_listから新しい識別番号を取得する
						validate_statement_list_id = getNewValidateStatementID(validate_statement_list, array_offset->target_statement);
						//追加する検証式の生成
						new_validate_statement = new_VALIDATE_STATEMENT(validate_statement_list_id, 1, VALIDATE_NOTUSED, statement, array_offset->target_statement);
						ValidateStatementList_push_back_ref(validate_statement_list, new_validate_statement);

						CSTLString_delete(variable);

				}
			}
	}


}

/**
指定した配列オフセットリストarrya_offset_listから、インクリメントおよびデクリメント式を含んでいたら、
それに応じてbasis_locationに反映させるための検証式を生成し、validate_statement_listに追加する。

@param validate_statement_list 追加先の検証式
@param array_offset_list 配列オフセットリスト

@return なし

*/
void createValidateStatemenFromIncDecExpr(ValidateStatementList *validate_statement_list, ARRAY_OFFSET_LIST *array_offset_list){

	int validate_statement_list_id;
	ValidateStatement *new_validate_statement;

	//配列オフセットリストから、値を取る
	ARRAY_OFFSET *target_array_offset = ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(array_offset_list));

	//演算後のオフセットレベルを求める
	int pointer_level = getOffsetLevelFromArrayOffset(target_array_offset);

	//演算後のオフセットレベルが1以上の場合で、インクリメントおよびデクリメントのいずれかを経由している場合
	if(pointer_level >= 1 && target_array_offset->inc_dec_flag != NOT_INC_DEC){


		//それに応じてbasis_locationに反映させるための検証式を生成させる

		//デクリメント式である場合
		if(target_array_offset->inc_dec_flag == VIA_DEC){
			CSTLString *statement = CSTLString_new();

			CSTLString_printf(statement, 0, "basis_location_%d_%s = basis_location_%d_%s - 1; ", pointer_level,
			 CSTLString_c_str(target_array_offset->variable_name), pointer_level, CSTLString_c_str(target_array_offset->variable_name));

			//validate_statement_listから新しい識別番号を取得する
			validate_statement_list_id = getNewValidateStatementID(validate_statement_list, target_array_offset->target_statement);
			//追加する検証式の生成
			new_validate_statement = new_VALIDATE_STATEMENT(validate_statement_list_id, 1, VALIDATE_NOTUSED, statement, target_array_offset->target_statement);
			ValidateStatementList_push_back_ref(validate_statement_list, new_validate_statement);

		}

		//インクリメント式である場合
		else if(target_array_offset->inc_dec_flag == VIA_INC){
			CSTLString *statement = CSTLString_new();

			CSTLString_printf(statement, 0, "basis_location_%d_%s = basis_location_%d_%s + 1; ", pointer_level,
			 CSTLString_c_str(target_array_offset->variable_name), pointer_level, CSTLString_c_str(target_array_offset->variable_name));

			//validate_statement_listから新しい識別番号を取得する
			validate_statement_list_id = getNewValidateStatementID(validate_statement_list, target_array_offset->target_statement);
			//追加する検証式の生成
			new_validate_statement = new_VALIDATE_STATEMENT(validate_statement_list_id, 1, VALIDATE_NOTUSED, statement, target_array_offset->target_statement);
			ValidateStatementList_push_back_ref(validate_statement_list, new_validate_statement);

		}

		//それ以外はエラーとして出力し強制終了させる
		else{
			fprintf(stderr, "Unexpect Inclement Declement Flag\n");
			exit(1);
		}

	}



}
/**
メモリ解放関係の情報freememinfoから検証式を生成し、validate_statement_listに追加する。

@param variable_statement_list 生成先の検証式リスト
@param freememinfo メモリ確保関係の情報
@param validate_variable_list 検証用変数リスト

@return なし
*/
void createValidateStatementForFreeAction(ValidateStatementList *validate_statement_list, FREEMEMINFO *freememinfo,
				ValidateVariableList *validate_variable_list){
	//freememinfoのfree_variableに関する配列オフセット
	ARRAY_OFFSET *array_offset = ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(freememinfo->free_variable));
	//array_offsetのオフセットリストで参照するのに使用するイテレータ
	OFFSET_LISTIterator off_list_i;
	//validate_variableに対するイテレータ
	ValidateVariableListIterator validate_variable_iterator;
	//array_offset_listからオフセットの深さを取得する。
	int array_offset_depth = OFFSET_LIST_size(array_offset->offset_list);

	//ポインタレベル
	int pointer_level;

	int i;

	for(validate_variable_iterator = ValidateVariableList_begin(validate_variable_list);
		validate_variable_iterator != ValidateVariableList_end(validate_variable_list);
		validate_variable_iterator = ValidateVariableList_next(validate_variable_iterator)){

			//検証用のオフセットレベルがオフセットの深さより大きい場合
			if(ValidateVariableList_data(validate_variable_iterator)->offset_level > array_offset_depth){
				//array_offsetの変数名と一致する検証用変数を見つけ、なおかつarray_offsetの位置している式の行番号が検証用変数の有効範囲に入っている場合
				if(CSTLString_compare(array_offset->variable_name, ValidateVariableList_data(validate_variable_iterator)->target_variable_name) == 0 &&
					ValidateVariableList_data(validate_variable_iterator)->enable_start <= array_offset->target_statement->line &&
					array_offset->target_statement->line <= ValidateVariableList_data(validate_variable_iterator)->enable_end){
						//追加する検証式のデータ
						ValidateStatement *new_validate_statement;

						//validate_statement_listの識別番号
						int validate_statement_list_id;
						CSTLString *free_target_variable_name = CSTLString_new();
						CSTLString *statement = CSTLString_new();
						//検証用変数名を取得
						CSTLString_printf(free_target_variable_name, 0, "%s", CSTLString_c_str(ValidateVariableList_data(validate_variable_iterator)->variable_name));
						//ポインタと配列の記号を削除する
						deletePointerAndArraySynbol(free_target_variable_name);
						//オフセット情報を配列として追加挿入する
						for(off_list_i = OFFSET_LIST_begin(array_offset->offset_list);
							off_list_i != OFFSET_LIST_end(array_offset->offset_list);
							off_list_i = OFFSET_LIST_next(off_list_i)){
							CSTLString_printf(free_target_variable_name, 1, "[ %s ]", *OFFSET_LIST_data(off_list_i));
						}
						//検証式のオフセットレベルが、実際の配列のオフセットレベル＋１と等しい場合（すなわち、左辺の値と同じようなオフセットレベルと同じ場合）
						if(ValidateVariableList_data(validate_variable_iterator)->offset_level == array_offset_depth + 1){
							//もしmax_size系（動的配列の数を示すもの）の場合
							if(CSTLString_find(free_target_variable_name, "max_size_", 0)  == 0){
								CSTLString_printf(statement, 0,"*%s = 0; ", CSTLString_c_str(free_target_variable_name));


							}
							//もしbasis_location系（配列の位置を示すもの）の場合
							else if(CSTLString_find(free_target_variable_name, "basis_location_", 0)  == 0){

								CSTLString_printf(statement, 0,"%s = 0; ", CSTLString_c_str(free_target_variable_name));

							}
							//もしdefined系（ポインタが何らかの変数のアドレスを設定しているかを示すもの）の場合
							else if(CSTLString_find(free_target_variable_name, "defined_", 0)  == 0){
								//もし、検証用変数のオフセットレベルが１のときは、直接参照演算子を付ける
								CSTLString_printf(statement, 0,"*%s = 0; ", CSTLString_c_str(free_target_variable_name));


							}
							//もしmalloc_flag_系（ポインタが動的に割り当てられているかを示すもの）の場合
							else if(CSTLString_find(free_target_variable_name, "malloc_flag_", 0) == 0){
								//もし、検証用変数のオフセットレベルが１のときは、直接参照演算子を付ける
								CSTLString_printf(statement, 0,"*%s = 0; ", CSTLString_c_str(free_target_variable_name));


							}else{
								fprintf(stderr,"不正な検証式です。\n");
								exit(1);
							}
						}

						//validate_statement_listから新しい識別番号を取得する
						validate_statement_list_id = getNewValidateStatementID(validate_statement_list, array_offset->target_statement);
						//追加する検証式の生成
						new_validate_statement = new_VALIDATE_STATEMENT(validate_statement_list_id, 1, VALIDATE_NOTUSED, statement, array_offset->target_statement);
						ValidateStatementList_push_back_ref(validate_statement_list, new_validate_statement);

				}
			}
	}
}

/**
変数定義リストで、配列生成時の検証用変数の更新するための検証式を作成し、validate_statement_listに追加する。
また、検証用変数リストvalidate_variable_listに、配列のオフセットを生成するのに使用する変数vviterator_2～vviterator_n（nは配列の最大次元数）を生成し、追加する。
@param validate_variable_list 検証用変数リスト
@param validate_statement_list 追加先の検証式
@param variable_table_list 変数テーブルリスト
@param function_information_list 関数定義に関する情報リスト
@return なし
*/
void createValidateStatementFromArrayDefine(ValidateVariableList *validate_variable_list, ValidateStatementList *validate_statement_list, VARIABLE_TABLE_LIST *variable_table_list
					,FUNCTION_INFORMATION_LIST *function_information_list){
	VARIABLE_TABLE_LISTIterator vtlist_i;

	int max_array_offset = 0, tmp_offset_size;

	int iterator;

	char variable_name[STRLEN];

	int validate_statement_id;

	CSTLString *global_v_name;

	CSTLString *main_function;

	CSTLString *call_initialize;

	FUNCTION_INFORMATION *main_function_information;

	AST * target_ast;

	for(vtlist_i = VARIABLE_TABLE_LIST_begin(variable_table_list);
		vtlist_i != VARIABLE_TABLE_LIST_end(variable_table_list);
		vtlist_i = VARIABLE_TABLE_LIST_next(vtlist_i)){
			OFFSET_LIST *offset_list = OFFSET_LIST_new();

			//変数リストから配列のオフセットリストを取得する
			getOFFSET_LISTFromVariableTable(offset_list, VARIABLE_TABLE_LIST_data(vtlist_i));

			//変数リスト内の最大数の配列のオフセット数を求める
			tmp_offset_size = OFFSET_LIST_size(offset_list);
			if(max_array_offset < tmp_offset_size){
				max_array_offset = tmp_offset_size;
			}

			if(tmp_offset_size > 0){
				//配列のオフセットリストをもとに検証式を生成する
				CSTLString *output = CSTLString_new();

				//グローバル変数の場合はこの検証式を関数化する。
				if(VARIABLE_TABLE_LIST_data(vtlist_i)->declaration_location_address->block_level == 0){
					global_v_name = CSTLString_new();
					CSTLString_assign(global_v_name, CSTLString_c_str(VARIABLE_TABLE_LIST_data(vtlist_i)->variable_name));
					deletePointerAndArraySynbol(global_v_name);

					CSTLString_printf(output, 1, "void initializer_%s(void) {", CSTLString_c_str(global_v_name));

				}
				ArrayOffsetToValidateStatement(output, validate_variable_list, VARIABLE_TABLE_LIST_data(vtlist_i), offset_list);
				//グローバル変数の場合はこの検証式を関数化する。
				if(VARIABLE_TABLE_LIST_data(vtlist_i)->declaration_location_address->block_level == 0){
					CSTLString_printf(output, 1, "}");

					//関数リストから、main関数を取得する。
					main_function = CSTLString_new();
					CSTLString_assign(main_function, "main");
					main_function_information = searchFUNCTION_INFORMATION(main_function,function_information_list);

					//main関数のブロック内にこの初期化関数呼び出しを追加する。
					if(main_function_information != NULL){
						//main関数にこのグローバル変数の初期処理を追加する。
						call_initialize = CSTLString_new();
						CSTLString_printf(call_initialize, 0, "initializer_%s (); ", CSTLString_c_str(global_v_name));

						//関数定義のノードから、ブロックの始まりへのASTノードを取得する。
						if(CSTLString_compare_with_char(main_function_information->function_node->name, "function_definition_type_a") == 0){
							target_ast = ASTLIST_ITERATOR_1(ASTLIST_ITERATOR_4(main_function_information->function_node));
						}else if(CSTLString_compare_with_char(main_function_information->function_node->name, "function_definition_type_b") == 0){
							target_ast = ASTLIST_ITERATOR_1(ASTLIST_ITERATOR_3(main_function_information->function_node));
						}else{
							fprintf(stderr, "不正なノード:%s", CSTLString_c_str(main_function_information->function_node->name));
							exit(1);
						}


						ValidateStatementList_push_back_ref(validate_statement_list, new_VALIDATE_STATEMENT( getNewValidateStatementID(validate_statement_list, target_ast), MODIFY_VS, VALIDATE_NOTUSED, call_initialize , target_ast));
					}

					CSTLString_delete(global_v_name);

				}

				//IDを付加する
				validate_statement_id = getNewValidateStatementID(validate_statement_list, VARIABLE_TABLE_LIST_data(vtlist_i)->declaration_location_address);

				//検証式リストに追加
				ValidateStatementList_push_back_ref(validate_statement_list, new_VALIDATE_STATEMENT( validate_statement_id, 1, VALIDATE_NOTUSED, output, VARIABLE_TABLE_LIST_data(vtlist_i)->declaration_location_address));


			}

			//オフセットリストを除外する
			deleteOFFSET_LIST(offset_list);
		}


	//検証用変数リストvalidate_variable_listに、配列のオフセットを生成するのに使用する変数vviterator_2～vviterator_n（nは配列の最大次元数）を生成し、追加する。
	for( iterator = 2; iterator <= max_array_offset; iterator++){
				//配列のオフセットを生成するのに使用する検証用の変数を生成する
				sprintf(variable_name, "vviterator_%d", iterator);

				ValidateVariableList_push_back_ref( validate_variable_list,

					new_VALIDATE_VARIABLE_with_char(VALIDATE_NOTUSED,
													1,
													INT_MAX,
													1,
													0,
													0,
													"int",
													variable_name,
													"null",
													1
					)
					);

	}
}

/**
変数定義リストでポインタ変数に対する検証用変数を更新するための検証式を作成し、validate_statement_listに追加する。
@param validate_statement_list 追加先の検証式
@param variable_table_list 変数テーブルリスト
@param function_information_list 関数定義に関する情報リスト

@return なし
*/
void createVaridateStatementFromPointerDefine( ValidateStatementList *validate_statement_list, VARIABLE_TABLE_LIST *variable_table_list, FUNCTION_INFORMATION_LIST *function_information_list){
	int array_level, pointer_level;

	VARIABLE_TABLE_LISTIterator vtlist_i;

	CSTLString *variable_name = CSTLString_new();
	CSTLString *statement;

	int validate_statement_id;

	FUNCTION_INFORMATION *main_function_information;
	CSTLString *main_function;
	CSTLString *call_initialize;
	AST *target_ast;


	for(vtlist_i = VARIABLE_TABLE_LIST_begin(variable_table_list);
		vtlist_i != VARIABLE_TABLE_LIST_end(variable_table_list);
		vtlist_i = VARIABLE_TABLE_LIST_next(vtlist_i)){

		//ポインタレベルおよび配列レベルを取得する
		getPointerLevelAndArrayLevelFromVARIABLE_TABLE(VARIABLE_TABLE_LIST_data(vtlist_i), &pointer_level, &array_level);

		//もし、ポインタレベルが１以上で、かつ配列レベルが0である場合
		if(pointer_level >= 1 && array_level == 0){
			//ポインタや配列記号を削除するすることで、変数名を取得する
			CSTLString_assign(variable_name, CSTLString_c_str(VARIABLE_TABLE_LIST_data(vtlist_i)->variable_name));
			deletePointerAndArraySynbol(variable_name);

			statement = CSTLString_new();

			//ポインタの第一層目のmax_size・basis_location・defined・malloc_flagに対する式を生成する
			//グローバル変数の場合は、関数化する。
			if(VARIABLE_TABLE_LIST_data(vtlist_i)->declaration_location_address->block_level == 0){
				CSTLString_printf(statement, 1, "void initializer_%s(void) {", CSTLString_c_str(variable_name));
			}
			//第一層目のmax_sizeの値は0にする。
			CSTLString_printf(statement, 1, "max_size_1_%s = malloc(sizeof(int)); *max_size_1_%s = 0;", CSTLString_c_str(variable_name), CSTLString_c_str(variable_name));
			//第一層目のbasis_locationは0にする。
			CSTLString_printf(statement, 1, "basis_location_1_%s = 0; ", CSTLString_c_str(variable_name));
			//第一層目のdefinedの値は0にする。
			CSTLString_printf(statement, 1, "defined_1_%s = malloc(sizeof(int));  *defined_1_%s = 0;", CSTLString_c_str(variable_name), CSTLString_c_str(variable_name));
			//第一層目のmalloc_flagの値は0にする。
			CSTLString_printf(statement, 1, "malloc_flag_1_%s = malloc(sizeof(int)); *malloc_flag_1_%s = 0;", CSTLString_c_str(variable_name), CSTLString_c_str(variable_name));

			if(VARIABLE_TABLE_LIST_data(vtlist_i)->declaration_location_address->block_level == 0){
				CSTLString_printf(statement, 1, "}", CSTLString_c_str(variable_name));
				//グローバル変数の場合はこの検証式を関数化する。
				if(VARIABLE_TABLE_LIST_data(vtlist_i)->declaration_location_address->block_level == 0){
					CSTLString_printf(statement, 1, "}");

					//関数リストから、main関数を取得する。
					main_function = CSTLString_new();
					CSTLString_assign(main_function, "main");
					main_function_information = searchFUNCTION_INFORMATION(main_function,function_information_list);

					//main関数のブロック内にこの初期化関数呼び出しを追加する。
					if(main_function_information != NULL){
						//main関数にこのグローバル変数の初期処理を追加する。
						call_initialize = CSTLString_new();
						CSTLString_printf(call_initialize, 0, "initializer_%s (); ", CSTLString_c_str(variable_name));

						//関数定義のノードから、ブロックの始まりへのASTノードを取得する。
						if(CSTLString_compare_with_char(main_function_information->function_node->name, "function_definition_type_a") == 0){
							target_ast = ASTLIST_ITERATOR_1(ASTLIST_ITERATOR_4(main_function_information->function_node));
						}else if(CSTLString_compare_with_char(main_function_information->function_node->name, "function_definition_type_b") == 0){
							target_ast = ASTLIST_ITERATOR_1(ASTLIST_ITERATOR_3(main_function_information->function_node));
						}else{
							fprintf(stderr, "不正なノード:%s", CSTLString_c_str(main_function_information->function_node->name));
							exit(1);
						}


						ValidateStatementList_push_back_ref(validate_statement_list, new_VALIDATE_STATEMENT( getNewValidateStatementID(validate_statement_list, target_ast), MODIFY_VS, VALIDATE_NOTUSED, call_initialize , target_ast));
					}

				}
			}

			//IDを付加する
			validate_statement_id = getNewValidateStatementID(validate_statement_list, VARIABLE_TABLE_LIST_data(vtlist_i)->declaration_location_address);

			//検証式リストに追加
			ValidateStatementList_push_back_ref(validate_statement_list, new_VALIDATE_STATEMENT( validate_statement_id, 1, VALIDATE_NOTUSED, statement, VARIABLE_TABLE_LIST_data(vtlist_i)->declaration_location_address));

		}

	}

	CSTLString_delete(variable_name);

}

/**
配列やポインタなどのオフセット情報のリストarray_offset_listから、配列の範囲外参照のチェックをするための検証式
や、未定義状態で処理をチェックするための検証式を生成し、validate_statement_listへ追加する。

@param validate_statement_list 追加先の検証式リスト
@param array_offset_list 配列やポインタなどのオフセット情報のリスト
@param array_unbound_check 配列が範囲外を参照していないかどうかを検証するための式を生成するかどうか　１：生成する　０：生成しない
@param undefined_control_check 未定義な処理を行っていないかどうかを検証するための式を生成するかどうか １：生成する ０：生成しない
@return なし
*/
void createCheckUnboundAndUndefineOperationCheck(ValidateStatementList *validate_statement_list, ARRAY_OFFSET_LIST *array_offset_list, int array_unbound_check, int undefined_control_check){
	ARRAY_OFFSET_LISTIterator aoff_list_i;

	int array_offset_level;

	int offset_level_counter;

	OFFSET_LISTIterator off_list_i;

	if(array_unbound_check || undefined_control_check){

		//array_offset_listの情報は、最後のほうに最下位レベルのポインタおよび配列参照があるので、末尾から探索する
		for(aoff_list_i = ARRAY_OFFSET_LIST_rbegin(array_offset_list);
			aoff_list_i != ARRAY_OFFSET_LIST_rend(array_offset_list);
			aoff_list_i = ARRAY_OFFSET_LIST_prev(aoff_list_i)){

				//オフセットレベルの取得
				array_offset_level = OFFSET_LIST_size(ARRAY_OFFSET_LIST_data(aoff_list_i)->offset_list);

				//オフセットレベルが0を超える場合（すなわち、オフセット情報が存在する場合）
				if(array_offset_level > 0){

					//配列の形を保持する情報（処理中で使用される）
					CSTLString *array_string = CSTLString_new();
					CSTLString *basis_location_content = CSTLString_new();
					CSTLString_assign(array_string, "");
					CSTLString_assign(basis_location_content, "");

					//オフセット情報を参照する
					for(offset_level_counter = 1, off_list_i = OFFSET_LIST_begin(ARRAY_OFFSET_LIST_data(aoff_list_i)->offset_list);
						off_list_i != OFFSET_LIST_end(ARRAY_OFFSET_LIST_data(aoff_list_i)->offset_list);
						offset_level_counter++, off_list_i = OFFSET_LIST_next(off_list_i)){
							int is_expression_flag = isExpression(*OFFSET_LIST_data(off_list_i));
							//検証式を入れる文字列情報
							CSTLString *statement = CSTLString_new();

							//未定義処理チェックフラグが成り立っている場合、
							//レベルごとの未定義処理の検証式を生成する。未定義処理の検証式の形式は以下の通りである。
							//if(defined_階層_変数名 == 0 && max_size_階層_変数名 == 0){
							//	printf("#ファイル名#:行数: detected undefine pointer access in variable 変数名);
							//	assert(0);
							//	リターン式;
							//}
							if(undefined_control_check){

								CSTLString_printf(statement,0,"if(*defined_%d_%s%s == 0 && *malloc_flag_%d_%s%s == 0){",
											 offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string),
											 offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string)
										);

								CSTLString_printf(statement,1,"printf(\"#%s#:%d: detected undefine pointer access in variable %s\"); ",getFileName(), ARRAY_OFFSET_LIST_data(aoff_list_i)->target_statement->line, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name));

								CSTLString_printf(statement, 1, "assert(0);");

								//リターン命令の返却型に応じる変更(もし、void型であれば、「return;」にする)
								if(CSTLString_compare_with_char(ARRAY_OFFSET_LIST_data(aoff_list_i)->target_statement->return_type, "void") == 0){
									CSTLString_printf(statement, 1, "return; ");
								}else{
									CSTLString_printf(statement, 1, "return 1; ");
								}

								CSTLString_printf(statement, 1, "} ");

							}

							//配列範囲外チェックフラグが成り立っていた場合、
							//レベルごとの配列範囲外参照の検証式を生成する。配列範囲外参照の式の形式は以下の通りである
							//if(0 > 式 + 基本位置 || 式 + 基本位置 < 対象変数の配列長){
							//	printf("#ファイル名#:行数: detected unbound access in variable 変数名 basis_location = %d 式 = %d\n", basis_location, 式);
							//	assert(0);
							//	リターン式;
							//}
							if(array_unbound_check){
									CSTLString_printf(statement,1,"if(0 > %s + basis_location_%d_%s%s || %s + basis_location_%d_%s%s >= *max_size_%d_%s%s){",
												 *OFFSET_LIST_data(off_list_i), offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string),
												 *OFFSET_LIST_data(off_list_i), offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string),
												 offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string));

								CSTLString_printf(statement,1,"printf(\"#%s#:%d:detected unbound access in variable %s ",getFileName(), ARRAY_OFFSET_LIST_data(aoff_list_i)->target_statement->line, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name));

								//basis_locationの内容も出力する
								CSTLString_printf(statement,1," basis_location = %%d ");

								//もし、オフセットの内容が式であれば、式＝値という形で出力する
								if(is_expression_flag == 1){
									CSTLString_printf(statement,1,"(%s = %%d)\\n\"", *OFFSET_LIST_data(off_list_i));
									//basis_locationの内容を含めた引数の内容を入れる
									CSTLString_printf(statement,1,", basis_location_%d_%s%s, %s",offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string) , *OFFSET_LIST_data(off_list_i));
								}

								//そうでなければ、値という形で出力する
								else{
									CSTLString_printf(statement,1,"(%s)\\n\"", *OFFSET_LIST_data(off_list_i));
									//basis_locationの内容の引数の内容を入れる
									CSTLString_printf(statement,1,", basis_location_%d_%s%s", offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string));
								}
								CSTLString_printf(statement, 1, "); ");

								CSTLString_printf(statement, 1, "assert(0);");

								//リターン命令の返却型に応じる変更(もし、void型であれば、「return;」にする)
								if(CSTLString_compare_with_char(ARRAY_OFFSET_LIST_data(aoff_list_i)->target_statement->return_type, "void") == 0){
									CSTLString_printf(statement, 1, "return; ");
								}else{
									CSTLString_printf(statement, 1, "return 1; ");
								}

								CSTLString_printf(statement, 1, "}");
							}
							//検証式の追加
							ValidateStatementList_push_back_ref(validate_statement_list,
								new_VALIDATE_STATEMENT(
									getNewValidateStatementID(validate_statement_list, ARRAY_OFFSET_LIST_data(aoff_list_i)->target_statement),
									0,
									VALIDATE_NOTUSED,
									statement,
									ARRAY_OFFSET_LIST_data(aoff_list_i)->target_statement
								)
							);

							//次のレベルのための配列を生成する。
							CSTLString_printf(basis_location_content, 0, "basis_location_%d_%s%s", offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string));
							CSTLString_printf(array_string, 1," [ %s + %s ]", *OFFSET_LIST_data(off_list_i), (char*)CSTLString_c_str(basis_location_content));


					}

					CSTLString_delete(array_string);
					CSTLString_delete(basis_location_content);

				}


			}
		}


}

/**
ArrayOffsetToVaridateStatementの内部処理
@param output 出力する検証式
@param validate_variable_list 検証用変数リスト
@param variaなしble_table 対象の変数データ
@param offset_list オフセットリスト
@param offset_level 今参照しているオフセットレベル

@return なし
*/
void ArrayOffsetToVaridateStatement_Internal(CSTLString* output, ValidateVariableList *validate_variable_list, VARIABLE_TABLE *variable_table, OFFSET_LIST *offset_list, int *offset_level){
	ValidateVariableListIterator vvlist_i;
	OFFSET_LISTIterator off_list_i;
	int iterator;
	if(*offset_level <= OFFSET_LIST_size(offset_list)){

		//オフセット情報の取得
		char *offset_info;
		for(iterator = 1, off_list_i = OFFSET_LIST_begin(offset_list);
			iterator < *offset_level && off_list_i != OFFSET_LIST_end(offset_list);
			iterator++, off_list_i = OFFSET_LIST_next(off_list_i));

		offset_info = *OFFSET_LIST_data(off_list_i);

		if(*offset_level > 1){
			CSTLString_printf( output, 1, "for(vviterator_%d = 0; vviterator_%d < %s; vviterator_%d++){ ", *offset_level, *offset_level, offset_info, *offset_level);
		}

		for(vvlist_i = ValidateVariableList_begin(validate_variable_list);
			vvlist_i != ValidateVariableList_end(validate_variable_list);
			vvlist_i = ValidateVariableList_next(vvlist_i)){
				//検証用のオフセットレベルがオフセットの深さより大きい場合
				if(ValidateVariableList_data(vvlist_i)->offset_level >= *offset_level){

					CSTLString *variable_name = CSTLString_new();
					CSTLString_printf(variable_name, 0, "%s", CSTLString_c_str(variable_table->variable_name));
					deletePointerAndArraySynbol(variable_name);

					//array_offsetの変数名と一致する検証用変数を見つけ、なおかつ対象変数の有効範囲が検証用変数の有効範囲が一致した場合
					if(CSTLString_compare(variable_name, ValidateVariableList_data(vvlist_i)->target_variable_name) == 0 &&
						ValidateVariableList_data(vvlist_i)->enable_start == variable_table->enable_start  &&
						variable_table->enable_end == ValidateVariableList_data(vvlist_i)->enable_end){
							CSTLString *validate_variable = CSTLString_new();
							//検証用変数名を取得
							CSTLString_printf(validate_variable, 0, "%s", CSTLString_c_str(ValidateVariableList_data(vvlist_i)->variable_name));
							//ポインタと配列の記号を削除する
							deletePointerAndArraySynbol(validate_variable);

							//検証式の設定
							//もし、basis_locationから始まる式でなければ、次のように式を追加する
							//検証変数名 = malloc(sizeof(int)); *検証変数名
							if(ValidateVariableList_data(vvlist_i)->offset_level == *offset_level &&
									CSTLString_find(validate_variable, "basis_location", 0) == CSTL_NPOS){
								CSTLString_printf(output, 1, "%s", CSTLString_c_str(validate_variable));
								//二次元目以降は、配列参照の記号を入れる
								if(*offset_level > 1){
									for(iterator = 2; iterator <= *offset_level; iterator++){
										CSTLString_printf(output, 1, "[vviterator_%d]", iterator);
									}
								}
								CSTLString_printf(output, 1, " = malloc(sizeof(int)); *%s",  CSTLString_c_str(validate_variable));
							}else{
								CSTLString_printf(output, 1, "%s", CSTLString_c_str(validate_variable));
							}
							//二次元目以降は、配列参照の記号を入れる
							if(*offset_level > 1){
								for(iterator = 2; iterator <= *offset_level; iterator++){
									CSTLString_printf(output, 1, "[vviterator_%d]", iterator);
								}
							}

							//検証式のオフセットレベルが、実際の配列のオフセットレベルと等しい場合（すなわち、左辺の値と同じようなオフセットレベルと同じ場合）
							if(ValidateVariableList_data(vvlist_i)->offset_level == *offset_level){
								//もしmax_size系（動的配列の数を示すもの）の場合
								if(CSTLString_find(validate_variable, "max_size_", 0) == 0){

									CSTLString_printf(output, 1," = %s; ", offset_info);

								}
								//もしbasis_location系（配列の位置を示すもの）の場合
								else if(CSTLString_find(validate_variable, "basis_location_", 0) == 0){

									CSTLString_printf(output, 1," = 0; ");

								}
								//もしdefined系（ポインタが何らかの変数のアドレスを設定しているかを示すもの）の場合
								else if(CSTLString_find(validate_variable, "defined_", 0) == 0){

									CSTLString_printf(output, 1," = 1; ");

								}
								//もしmalloc_flag_系（ポインタが動的に割り当てられているかを示すもの）の場合
								else if(CSTLString_find(validate_variable, "malloc_flag_", 0) == 0){

									CSTLString_printf(output, 1," = 0; ");

								}else{
									fprintf(stderr,"不正な検証式です。\n");
									exit(1);
								}
							}
							//そうでない場合
							else{
								//basis_location系の場合は通常に追加する
								if(CSTLString_find(validate_variable, "basis_location_", 0) == 0){
									//malloc関数で検証式に対して新しい領域を確保する。
									CSTLString_printf(output, 1," = malloc((%s)*sizeof(int", offset_info);
								}
								//basis_location系以外の場合はアスタリスクを1つ多くする
								else{
									//malloc関数で検証式に対して新しい領域を確保する。
									CSTLString_printf(output, 1," = malloc((%s)*sizeof(int*", offset_info);

								}
								//ポインタ記号を追加する。
								for(iterator = *offset_level + 2; iterator <= ValidateVariableList_data(vvlist_i)->offset_level;
									iterator++){
										CSTLString_printf(output, 1,"*");
								}
								//関数を閉じる
								CSTLString_printf(output, 1,")); ");
							}

							CSTLString_delete(validate_variable);
					}

					CSTLString_delete(variable_name);
				}
		}
		*offset_level = *offset_level + 1;
		ArrayOffsetToVaridateStatement_Internal(output, validate_variable_list, variable_table, offset_list, offset_level);
		*offset_level = *offset_level - 1;
		if(*offset_level > 1){
			CSTLString_printf( output, 1, "} ");
		}

	}

}

/**
配列のオフセットリストを基に、検証式を作成する。
@param output 出力する検証式
@param validate_variable_list 検証用変数リスト
@param variable_table 対象の変数データ
@param offset_list オフセットリスト

@return なし
*/
void ArrayOffsetToValidateStatement(CSTLString* output, ValidateVariableList *validate_variable_list, VARIABLE_TABLE *variable_table, OFFSET_LIST *offset_list){
	int offset_level = 1;
	ArrayOffsetToVaridateStatement_Internal(output, validate_variable_list, variable_table, offset_list, &offset_level);
}


/**
メモリ解放関係の情報freememinfoから、free関数に関する違反行為を行っていないかどうかをチェックするための検証式を生成し、validate_statement_listへ追加する。

@param validate_statement_list 追加先の検証式リスト
@param freememinfo メモリ解放関係の情報

@return なし
*/
void createViolentFreeOperation(ValidateStatementList *validate_statement_list, FREEMEMINFO *freememinfo){
	//メモリ解放対象の変数の配列オフセット情報を取り出す
	ARRAY_OFFSET *target_free_variable = ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(freememinfo->free_variable));

	//作成する検証式
	CSTLString *statement = CSTLString_new();

	//変数の配列オフセット情報から、配列を作り出す。
	int offset_level_counter;
	OFFSET_LISTIterator off_list_i;
	CSTLString *variable = CSTLString_new();

	//配列を保持する情報
	CSTLString *array_string = CSTLString_new();
	CSTLString *basis_location_content = CSTLString_new();
	//変数名の取得
	CSTLString_assign(variable, CSTLString_c_str(target_free_variable->variable_name));

	//指定した次元または、この配列オフセットが持っている次元まで配列式として出力する
	for(offset_level_counter = 1, off_list_i = OFFSET_LIST_begin(target_free_variable->offset_list);
		off_list_i != OFFSET_LIST_end(target_free_variable->offset_list);
		offset_level_counter++, off_list_i = OFFSET_LIST_next(off_list_i)){


		//配列を生成し、追加する。
		CSTLString_printf(basis_location_content, 0, "basis_location_%d_%s%s", offset_level_counter, (char*)CSTLString_c_str(target_free_variable->variable_name), (char*)CSTLString_c_str(array_string));
		CSTLString_printf(array_string, 1," [ %s + %s ]", *OFFSET_LIST_data(off_list_i), (char*)CSTLString_c_str(basis_location_content));

		CSTLString_printf(variable, 1, "%s", CSTLString_c_str(array_string));
	}
	//ここから、チェックするための変数を作成する
	//if(*malloc_flag_階層_変数名 == 0) { printf("ソースファイル名Detected violent of free operation in variable 変数名"); assert(0); リターン処理; }

	CSTLString_printf(statement, 0, "if(*malloc_flag_%d_%s == 0) { printf(\"#%s#:%d:Detected violent of free operation in variable %s\"); assert(0); ",
	 OFFSET_LIST_size(target_free_variable->offset_list) + 1, CSTLString_c_str(variable), getFileName(), target_free_variable->target_statement->line,  CSTLString_c_str(target_free_variable->variable_name));

	//リターン命令の返却型に応じる変更(もし、void型であれば、「return;」にする)
	if(CSTLString_compare_with_char(target_free_variable->target_statement->return_type, "void") == 0){
		CSTLString_printf(statement, 1, "return; ");
	}else{
		CSTLString_printf(statement, 1, "return 1; ");
	}

	CSTLString_printf(statement, 1, "}");

	//検証式の追加
	ValidateStatementList_push_back_ref(validate_statement_list,
		new_VALIDATE_STATEMENT(
			getNewValidateStatementID(validate_statement_list,target_free_variable->target_statement),
			CHECK_VS,
			VALIDATE_NOTUSED,
			statement,
			target_free_variable->target_statement
		)
	);
}

/**
除算および剰余式の情報から、ゼロ除算および剰余になっていないかどうかの検証式を生成する。
@param validate_statement_list 格納先の検証式リスト
@param divition_information_list 対象の除算および剰余式の情報

@return なし
*/
void createZeroDivitionCheck(ValidateStatementList *validate_statement_list, DIVITION_INFORMATION_LIST *divition_information_list){
	//除算および剰余式に関するイテレータ
	DIVITION_INFORMATION_LISTIterator di_i;
	//除算および剰余式内の各識別子に対するイテレータ
	ARRAY_OFFSET_LISTIterator aoff_list_i;

	for(di_i = DIVITION_INFORMATION_LIST_rbegin(divition_information_list);
		di_i != DIVITION_INFORMATION_LIST_rend(divition_information_list);
		di_i = DIVITION_INFORMATION_LIST_prev(di_i)){
			//式に関するCSTL文字列を生成
			CSTLString *statement = CSTLString_new();
			CSTLString *identifires_list = CSTLString_new();
			CSTLString *parameter_list = CSTLString_new();
			CSTLString *output = CSTLString_new();
			//次のような式を生成する
			//if( (式) == 0 ){ printf("#ファイル名#:行数:detected zero (divition/mod) operation in expression 式"); assert(0); リターン式; }
			CSTLString_printf(statement, 0, "if( (%s) == 0 ){ printf(\"#%s#:%d:detected zero ", CSTLString_c_str(DIVITION_INFORMATION_LIST_data(di_i)->statement),
				getFileName(), DIVITION_INFORMATION_LIST_data(di_i)->target_expression->line);

			//式のタイプが除算か剰余算によってメッセージを変える
			if(DIVITION_INFORMATION_LIST_data(di_i)->type == TYPE_DIV){
				CSTLString_printf(statement, 1, "division ");
			}else{
				CSTLString_printf(statement, 1, "mod ");
			}
			CSTLString_printf(statement, 1, "oparation in expression %s ", CSTLString_c_str(DIVITION_INFORMATION_LIST_data(di_i)->statement));

			//配列オフセットリストから各識別子の情報を出力させ、式に追加していく
			for(aoff_list_i = ARRAY_OFFSET_LIST_begin(DIVITION_INFORMATION_LIST_data(di_i)->identifiers);
				aoff_list_i != ARRAY_OFFSET_LIST_end(DIVITION_INFORMATION_LIST_data(di_i)->identifiers);
				aoff_list_i = ARRAY_OFFSET_LIST_next(aoff_list_i)){
					createArrayExpression(output, ARRAY_OFFSET_LIST_data(aoff_list_i), INT_MAX);
					CSTLString_printf(identifires_list, 1, "%s = %%d", CSTLString_c_str(output));
					//識別子情報の最後でなければ、カンマ区切りする
					if(ARRAY_OFFSET_LIST_next(aoff_list_i) != ARRAY_OFFSET_LIST_end(DIVITION_INFORMATION_LIST_data(di_i)->identifiers)){
						CSTLString_printf(identifires_list, 1,", ");
					}

					CSTLString_printf(parameter_list, 1, ", %s", CSTLString_c_str(output));

				}
			CSTLString_printf(statement, 1, "( %s )\"%s); assert(0);", CSTLString_c_str(identifires_list), CSTLString_c_str(parameter_list));

			//リターン命令の返却型に応じる変更(もし、void型であれば、「return;」にする)
			if(CSTLString_compare_with_char(DIVITION_INFORMATION_LIST_data(di_i)->target_expression->return_type, "void") == 0){
				CSTLString_printf(statement, 1, "return; ");
			}else{
				CSTLString_printf(statement, 1, "return 1; ");
			}

			CSTLString_printf(statement, 1, "}");

			//生成された検証式の追加
			ValidateStatementList_push_back_ref(validate_statement_list,
				new_VALIDATE_STATEMENT(
					getNewValidateStatementID(validate_statement_list, DIVITION_INFORMATION_LIST_data(di_i)->target_expression),
					CHECK_VS,
					VALIDATE_NOTUSED,
					statement,
					DIVITION_INFORMATION_LIST_data(di_i)->target_expression
				)
			);

			CSTLString_delete(identifires_list);
			CSTLString_delete(parameter_list);
			CSTLString_delete(output);
		}
}
/**
検証式リストvalidate_statement_listから、target_statementと同じASTのアドレスを持ったものを探し出し、それを基に重複しないようにするための新しい検証式の識別番号を取得する。
新しい検証式を作るにはこの関数から新しい識別番号を取得すること。

@param validate_statement_list 対象の検証式リスト
@param target_statement 対象の検証式から確認するためのASTのアドレス

@return 新しい識別番号を出力する。すでに同じASTのアドレスを持っている検証式がなければ０を返す。
*/
int getNewValidateStatementID(ValidateStatementList *validate_statement_list, AST *target_statement){
	//対象の検証リストを参照するためのイテレータ
	ValidateStatementListIterator vslist_i;

	//新しい識別番号のための変数
	int new_id = 0;

	for(vslist_i = ValidateStatementList_begin(validate_statement_list);
		vslist_i != ValidateStatementList_end(validate_statement_list);
		vslist_i = ValidateStatementList_next(vslist_i)){
			//すでに同じASTのアドレスを持ったものを見つければ、new_idをカウントする。
			if(ValidateStatementList_data(vslist_i)->target_statement == target_statement){
				new_id++;
			}
	}

	return new_id;
}

/**
代入式の左辺値について、検証式に必要な情報を取得する。
@param left_expression 左辺値に関するASTノード
@param function_information_list 関数に関する情報のリスト
@param vtlist 検証対象の式をマークするための変数リスト
@param ignore_ast_list ポインタでの位置が検証済みである、IDENTIFIERを無視するためのASTのアドレスリスト
@param array_offset_list 各ポインタおよび配列ごとのオフセットのリスト
@param target_expression この左辺式の上位に位置するASTノード
@param switch_mode 直接アクセスおよび配列アクセスを探すか、IDENTIFIERを探すかどうかのスイッチフラグ ０：両方さがす　１：direct_refやarray_accessのみ探す
@return なし
*/
void getLeftAssignmentInfo(AST *left_expression, FUNCTION_INFORMATION_LIST *function_information_list,
		VARIABLE_TABLE_LIST *vtlist, ASTPOINTER_LIST *ignore_ast_list, ARRAY_OFFSET_LIST * array_offset_list,
		AST *target_expression, int *switch_mode){
	ASTListIterator p;
	int pointer_level, array_level;
	//direct_refおよびarray_accessを見つけたら、１次以降のレベルを確認する
	if(CSTLString_compare_with_char(left_expression->name, "direct_ref") == 0 ||
		CSTLString_compare_with_char(left_expression->name, "array_access") == 0){
		ARRAY_OFFSET *array_offset = NULL;
		//ポインタおよび配列変数の各次元のオフセットを求める
		getPointerArrayOffset(left_expression, function_information_list, vtlist, 0, ignore_ast_list, &array_offset, target_expression, NOT_VIA_ANPASAND, NOT_INC_DEC);

		//DEBUG_MODEが有効な時ポインタおよび配列変数の各次元のオフセットの情報を出力する
		#ifdef DEBUG_MODE
			if(array_offset != NULL){
				printARRAY_OFFSET(array_offset);
			}
		#endif
		//ポインタおよび配列変数の各次元のオフセットの情報が取得できた場合、これに関する情報をこの情報のリストへ入れる
		if(array_offset != NULL){
			ARRAY_OFFSET_LIST_push_back_ref(array_offset_list, array_offset);
		}
		//スイッチフラグを１にする
		*switch_mode = 1;
	}
	//スイッチフラグが０であり、IDENTIFIERが見つかった場合
	else if(*switch_mode == 0 && CSTLString_compare_with_char(left_expression->name, "IDENTIFIER") == 0 ){
		//オフセット情報がないarray_offsetを作成する。
		ARRAY_OFFSET *array_offset;
		VARIABLE_TABLE *variable_table_data;
		OFFSET_LIST *offset_list = OFFSET_LIST_new();
		CSTLString *target_name = CSTLString_new();
		int ignore_flag;

		//指定したIDLISTと名前から最も該当する変数テーブルへのアドレスを取得する
		variable_table_data = searchVARIABLE_TABLE_LIST(left_expression->idlist, left_expression->content, vtlist);
		if(variable_table_data != NULL){
			//指定したノードleft_expressionが、ignore_ast_listに存在しないかどうか調べる
			ignore_flag = checkIgnoreASTList(left_expression, ignore_ast_list);

			//もし、存在しなければ、配列オフセットリスト
			if(ignore_flag == FAILED){
				getPointerLevelAndArrayLevelFromVARIABLE_TABLE(variable_table_data, &pointer_level, &array_level);

				CSTLString_assign(target_name, CSTLString_c_str(left_expression->content));

				array_offset = new_ARRAY_OFFSET(target_name, target_expression, left_expression, offset_list, pointer_level, array_level, NOT_VIA_ANPASAND, NOT_INC_DEC);

				//DEBUG_MODEが有効な時ポインタおよび配列変数の各次元のオフセットの情報を出力する
				#ifdef DEBUG_MODE
					if(array_offset != NULL){
						printARRAY_OFFSET(array_offset);
					}
				#endif

				//それをarray_offset_listに追加する
				ARRAY_OFFSET_LIST_push_back_ref(array_offset_list, array_offset);
			}
		}else{
			fprintf(stderr,"#%s#:%d: variable %s is undeclarated!!\n",getFileName(), left_expression->line, CSTLString_c_str(left_expression->content));
			exit(1);
		}

	}//インクリメント演算子が来た場合は、望ましくない処理として強制終了させる
	else if(CSTLString_compare_with_char(left_expression->name, "inc_expr") == 0 ||
		CSTLString_compare_with_char(left_expression->name, "inc_after_expr") == 0){

			fprintf(stderr,"#%s#:%d: exist inclement operator in left expression!!\n",getFileName(), left_expression->line);
			exit(1);
	}
	//デクリメント演算子が来た場合は、望ましくない処理として強制終了させる
	else if(CSTLString_compare_with_char(left_expression->name, "dec_expr") == 0 ||
		CSTLString_compare_with_char(left_expression->name, "dec_after_expr") == 0){
			fprintf(stderr,"#%s#:%d: exist declement operator in left expression!!\n",getFileName(), left_expression->line);
			exit(1);

	}
	//子ASTノードを参照する
	for(p = ASTList_begin(left_expression->children);
		p != ASTList_end(left_expression->children);
		p = ASTList_next(p)){
			getLeftAssignmentInfo(ASTList_data(p), function_information_list, vtlist, ignore_ast_list, array_offset_list, target_expression, switch_mode);
	}

}

/**
代入式の右辺式について、検証式に必要な情報を取得する。
@param root 右辺式に関するASTノード
@param function_information_list 関数に関する情報のリスト
@param vtlist メモリ確保情報を取得するのに必要なプログラム変数リスト
@param memalloc_info malloc関係の情報が出力される
@param array_offset_list 左辺式上にあるポインタ参照に対するオフセットリスト
@param ignore_ast_list 同じ位置のポインタが来ても無視するためのリスト
@param target_statement この計算式を属しているASTノードへのアドレス（基本的にexpression_statementであるノードが入る）

@return なし
*/
void getRightAssignmentInfo(AST *root, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist, MEMALLOC_INFO **memalloc_info,
	 ARRAY_OFFSET_LIST *array_offset_list, ASTPOINTER_LIST *ignore_ast_list, AST *target_statement){
	//ASTの子ノードを参照させるためのイテレータ
	ASTListIterator ast_iterator;

	//関数呼び出しを見つけた場合
	if(CSTLString_compare_with_char(root->name, "call_function") == 0){
		//メモリ割り当て関係の関数の解析し、sizeofの型とその時のサイズを取得する
		*memalloc_info = memoryAllocationAnarysis(root, vtlist);
	}else if(CSTLString_compare_with_char(root->name, "direct_ref") == 0 ||
			CSTLString_compare_with_char(root->name, "array_access") == 0 ){
		//ポインタや配列のオフセットリストを取得する
		int offset_level = 0;
		ARRAY_OFFSET *array_offset = NULL;
		getPointerArrayOffset(root, function_information_list, vtlist, offset_level, ignore_ast_list, &array_offset, target_statement, NOT_VIA_ANPASAND, NOT_INC_DEC);

		//DEBUG_MODEが有効な時ポインタおよび配列変数の各次元のオフセットの情報を出力する
		#ifdef DEBUG_MODE
			if(array_offset != NULL){
				printARRAY_OFFSET(array_offset);
			}
		#endif

		//何らかの配列オフセットリストを取得できたら、array_offset_listへプッシュバックする
		if(array_offset != NULL){
			ARRAY_OFFSET_LIST_push_back_ref(array_offset_list, array_offset);
		}
	}
	//アドレス演算子が来た場合は、アドレス演算子を通した配列オフセットリストを取得する
	else if(CSTLString_compare_with_char(root->name, "address_ref") == 0){
		getArrayOffsetInAnpasandInfo(root, function_information_list, vtlist,
							array_offset_list, ignore_ast_list, target_statement);
	}
	//インクリメント演算子が来た場合は、望ましくない処理として強制終了させる
	//理由：副作用を持つ代入式に、副作用を持つ式が入っていることは望ましくないから
	else if(CSTLString_compare_with_char(root->name, "inc_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "inc_after_expr") == 0){

			fprintf(stderr,"#%s#:%d: exist increment operator in right assign expression!!\n",getFileName(), root->line);
			exit(1);
	}
	//デクリメント演算子が来た場合は、望ましくない処理として強制終了させる
	//理由：副作用を持つ代入式に、副作用を持つ式が入っていることは望ましくないから
	else if(CSTLString_compare_with_char(root->name, "dec_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "dec_after_expr") == 0){
			fprintf(stderr,"#%s#:%d: exist increment operator in right assign expression!!\n",getFileName(), root->line);
			exit(1);

	}
	//代入式が来た場合は、望ましくない処理として強制終了させる
	else if(CSTLString_compare_with_char(root->name, "assignment_expression") == 0){
		fprintf(stderr,"#%s#:%d: exist assignment expression in right assign expression!!\n",getFileName(), root->line);
		exit(1);

	}
	//もし、IDENTIFIER（識別子）を見つけた場合
	else if(CSTLString_compare_with_char(root->name, "IDENTIFIER") == 0){
		//オフセット情報がないarray_offsetを作成する。
		ARRAY_OFFSET *array_offset = NULL;
		VARIABLE_TABLE *variable_table_data;
		OFFSET_LIST *offset_list = OFFSET_LIST_new();
		CSTLString *target_name = CSTLString_new();
		//指定したノードrootが、ignore_ast_listに存在しないかどうか調べるためのフラグ
		int ignore_flag;
		//該当する変数のポインタもしくは配列の次元を調べる。
		int pointer_level, array_level;
		//指定したIDLISTと名前から最も該当する変数テーブルへのアドレスを取得する
		variable_table_data = searchVARIABLE_TABLE_LIST(root->idlist, root->content, vtlist);
		//もし、該当する変数を見つかった場合
		if(variable_table_data != NULL){
			//指定したノードrootが、ignore_ast_listに存在しないかどうか調べる
			ignore_flag = checkIgnoreASTList(root, ignore_ast_list);

			//もし、存在しなければ、配列オフセットリストに追加する
			if(ignore_flag == FAILED){
				getPointerLevelAndArrayLevelFromVARIABLE_TABLE(variable_table_data, &pointer_level, &array_level);

				CSTLString_assign(target_name, CSTLString_c_str(root->content));

				array_offset = new_ARRAY_OFFSET(target_name, target_statement, root, offset_list, pointer_level, array_level, NOT_VIA_ANPASAND, NOT_INC_DEC);

				//DEBUG_MODEが有効な時ポインタおよび配列変数の各次元のオフセットの情報を出力する
				#ifdef DEBUG_MODE
					if(array_offset != NULL){
						printARRAY_OFFSET(array_offset);
					}
				#endif

				//それをarray_offset_listに追加する
				ARRAY_OFFSET_LIST_push_back_ref(array_offset_list, array_offset);
			}

		}
	}

	//ASTの子ノードも参照させる
	for(ast_iterator = ASTList_begin(root->children);
		ast_iterator != ASTList_end(root->children);
		ast_iterator = ASTList_next(ast_iterator)){

		getRightAssignmentInfo( ASTList_data(ast_iterator), function_information_list, vtlist, memalloc_info, array_offset_list, ignore_ast_list, target_statement);

	}
}


/**
指定した検証式リストvalidate_statement_listから、検証式のリストの内容を出力する。
@param validate_statement_list 出力する検証式リスト

@return なし
*/
void printValidateStatementList(ValidateStatementList *validate_statement_list){

	ValidateStatementListIterator vslist_i;

	int vslist_counter = 0;
	printf("------ValidateStatementList_INFO------\n\n");

	for(vslist_i = ValidateStatementList_begin(validate_statement_list);
		vslist_i != ValidateStatementList_end(validate_statement_list);
		vslist_i = ValidateStatementList_next(vslist_i)){

		printf("------VARIDATE_STATEMENT_%d------\n\n", vslist_counter);
		printf("TARGET_AST_LIST_LINE = \"%d\"\n", ValidateStatementList_data(vslist_i)->target_statement->line);
		printf("TARGET_AST_NAME = \"%s\"\n", (char*)CSTLString_c_str(ValidateStatementList_data(vslist_i)->target_statement->name));

		if(ValidateStatementList_data(vslist_i)->check_or_modify == 0){
			printf("TYPE = \"CHECK\"\n");
		}else{
			printf("TYPE = \"MODIFY_VARIDATE_VARIABLE\"\n");
		}

		printf("VARIDATE_ID = \"%d\"\n", ValidateStatementList_data(vslist_i)->target_id);

		printf("USED = \"%d\"\n", ValidateStatementList_data(vslist_i)->used);

		printf("STATEMENT = \"%s\"\n", CSTLString_c_str(ValidateStatementList_data(vslist_i)->statement));

		printf("---------------------------------\n\n");

		vslist_counter++;

	}

	printf("----------------------------------------\n\n");

}

/**
fprintProgramDataWithVaridateStatementの内部処理。

@param output 出力先のファイル構造体
@param root プログラムへのASTノード
@param validate_variable_list 検証用変数リスト
@param validate_statement_list 検証式リスト
@param for_information_list for文に関する情報のリスト
@param line 記憶維持するプログラムの行数

@return なし
*/
void fprintProgramDataWithVaridateStatement_Internal(FILE *output, AST *root, ValidateVariableList *validate_variable_list,
 ValidateStatementList *validate_statement_list, ForInformationList *for_information_list, int *line){
	ASTListIterator p;
	ValidateVariableListIterator vvlist_i;


	//変数のブロックID
	int block_id;
	//変数のブロックレベル
	int block_level;

	//プログラムである場合は、プログラム共通の検証用変数を出力する
	if(CSTLString_compare_with_char(root->name, "program") == 0){
		//検証用変数リストを参照する
		for(vvlist_i = ValidateVariableList_begin(validate_variable_list);
			vvlist_i != ValidateVariableList_end(validate_variable_list);
			vvlist_i = ValidateVariableList_next(vvlist_i)){
				//未使用状態のブロックIDとブロックレベルが両方とも０である検証用変数を全て出力する
				if(ValidateVariableList_data(vvlist_i)->used == 0 && ValidateVariableList_data(vvlist_i)->block_level == 0 && ValidateVariableList_data(vvlist_i)->block_id == 0){
					fprintf(output, "%s %s ; ", (char*)CSTLString_c_str(ValidateVariableList_data(vvlist_i)->type), (char*)CSTLString_c_str(ValidateVariableList_data(vvlist_i)->variable_name));
					//この検証用変数は使用済みにする
					ValidateVariableList_data(vvlist_i)->used = 1;
				}
			}
		//ASTノードが子ASTノードの情報を持っていたら、子ASTノードについて再帰的に参照させる
		for(p = ASTList_begin(root->children); p != ASTList_end(root->children); p = ASTList_next(p)){
			fprintProgramDataWithVaridateStatement_Internal(output, ASTList_data(p), validate_variable_list, validate_statement_list, for_information_list, line);
		}
	}
	//リーフノード（子ASTノードの数が0のASTノード）の場合
	else if(ASTList_size(root->children) == 0){
		//ASTノードの行数と引数の行数がかみ合わないとき、改行を出力させ、出力する行数を調整する
		while(*line < root->line){
			fprintf(output, "\n");
			*line = *line + 1;
		}

		//ASTノードの内容を出力させる
		fprintf(output, "%s ",CSTLString_c_str(root->content));

		//ブロックの開始を示す記号が来たら、検証用変数リストから必要な検証用変数を出力する
		if(CSTLString_compare_with_char(root->name, "{") == 0){

			//ブロックレベルごとのIDを取得する
			block_id = root->block_id;
			//ブロックレベルを取得する
			block_level = root->block_level;

			//検証用変数リストを参照する
			for(vvlist_i = ValidateVariableList_begin(validate_variable_list);
				vvlist_i != ValidateVariableList_end(validate_variable_list);
				vvlist_i = ValidateVariableList_next(vvlist_i)){
				//未使用状態で、宣言位置・ブロックID・ブロックレベルが一致する検証用変数を出力する
				if(ValidateVariableList_data(vvlist_i)->used == 0 && root->line == ValidateVariableList_data(vvlist_i)->declaration_location
					&& ValidateVariableList_data(vvlist_i)->block_id == block_id && ValidateVariableList_data(vvlist_i)->block_level == block_level){
					fprintf(output, "%s %s ; ", (char*)CSTLString_c_str(ValidateVariableList_data(vvlist_i)->type), (char*)CSTLString_c_str(ValidateVariableList_data(vvlist_i)->variable_name));
					//この検証用変数は使用済みにする
					ValidateVariableList_data(vvlist_i)->used = 1;
				}
			}

			//ブロック開始時に対する検証式の追加
			fprintValidateStatement(output, validate_statement_list, root, MODIFY_VS, FALSE);
		}
	}
	//普通の式の場合の処理
	else if(CSTLString_compare_with_char(root->name, "expression_statement") == 0 ||
		CSTLString_compare_with_char(root->name, "declaration_with_init") == 0){


		//ASTノードの行数と引数の行数がかみ合わないとき、改行を出力させ、出力する行数を調整する
		while(*line < root->line){
			fprintf(output, "\n");
			*line = *line + 1;
		}

		//該当するexpression_statementに対するチェック用検証式を全て出力させる
		fprintValidateStatement(output, validate_statement_list, root, CHECK_VS, FALSE);

		//ASTノードが子ASTノードの情報を持っていたら、子ASTノードについて再帰的に参照させる
		for(p = ASTList_begin(root->children); p != ASTList_end(root->children); p = ASTList_next(p)){
			fprintProgramDataWithVaridateStatement_Internal(output, ASTList_data(p), validate_variable_list, validate_statement_list, for_information_list, line);
		}

		//該当するexpression_statementに対する検証式変更用の検証式を全て出力させる
		fprintValidateStatement(output, validate_statement_list, root, MODIFY_VS, FALSE);

		//式自体を出力させる。
		CSTLString *c = CSTLString_new();
		getStringFromAST(c,root);
		CSTLString_replace_string(c,"\"","\\\"");
		CSTLString_replace_string(c,"%","%%");
		fprintf(output, "printf(\"%s\\n\");\n", CSTLString_c_str(c));

	}
	//for文系統が来た場合、whileの形に直しながら、検証式を入れていく
	else if(CSTLString_compare_with_char(root->name, "for_statement_type_a") == 0 ||
		CSTLString_compare_with_char(root->name, "for_statement_type_b") == 0 ||
		CSTLString_compare_with_char(root->name, "for_statement_type_c") == 0 ||
		CSTLString_compare_with_char(root->name, "for_statement_type_d") == 0){

		//式の出力に使用するためのCSTLString
		CSTLString *statement = CSTLString_new();
		//当てはまるfor文の情報を取得する
		ForInformation *for_information = searchFOR_INFORMATION_FromAST(for_information_list, root);

		//ASTノードの行数と引数の行数がかみ合わないとき、改行を出力させ、出力する行数を調整する
		while(*line < for_information->init_expression->line){
			fprintf(output, "\n");
			*line = *line + 1;
		}
		//まず初期式をチェック式および検証用変数の編集式を含ませて出力させる
		getStringFromAST(statement, for_information->init_expression);
		fprintValidateStatement(output, validate_statement_list, for_information->init_expression, CHECK_VS, FALSE);
		fprintf(output, "%s ", CSTLString_c_str(statement));
		fprintValidateStatement(output, validate_statement_list, for_information->init_expression, MODIFY_VS, FALSE);


		//次に条件式を" while(条件式){for文内の式 " の形式にする
		CSTLString_assign(statement, "");
		getStringFromAST(statement, for_information->continue_condition);
		//セミコロンは余分なので削除する
		CSTLString_replace_string(statement, ";", "");
		fprintf(output, "while( %s ) {", CSTLString_c_str(statement));

		//for文内の式は再帰的に呼び出す
		fprintProgramDataWithVaridateStatement_Internal(output, for_information->statement, validate_variable_list, validate_statement_list, for_information_list, line);

		//最後に増分式があれば、それをチェック式および検証用変数の編集式を含ませて出力させる
		if(for_information->inc_dec_expression != NULL){
			CSTLString_assign(statement, "");
			getStringFromAST(statement, for_information->inc_dec_expression);
			fprintValidateStatement(output, validate_statement_list, for_information->inc_dec_expression, CHECK_VS, FALSE);
			fprintf(output, "\n%s ; ", CSTLString_c_str(statement));
			fprintValidateStatement(output, validate_statement_list, for_information->inc_dec_expression, MODIFY_VS, FALSE);
		}

		//大かっこで区切って終了
		fprintf(output, "} ");
		CSTLString_delete(statement);
	}
	//if文、switch文、while文、do-while文が来た場合
	else if(CSTLString_compare_with_char(root->name, "if_statement") == 0 ||
		CSTLString_compare_with_char(root->name, "switch_statement") == 0 ||
		CSTLString_compare_with_char(root->name, "while_statement") == 0 ||
		CSTLString_compare_with_char(root->name, "dowhile_statement") == 0){
		//ASTノードが子ASTノードの情報を持っていたら、子ASTノードについて再帰的に参照させる
		for(p = ASTList_begin(root->children);
			CSTLString_compare_with_char(ASTList_data(p)->name, "statement") != 0 &&
			p != ASTList_end(root->children);
			p = ASTList_next(p)){
			fprintProgramDataWithVaridateStatement_Internal(output, ASTList_data(p), validate_variable_list, validate_statement_list, for_information_list, line);
		}
		//statementが来た場合
		if(CSTLString_compare_with_char(ASTList_data(p)->name, "statement") == 0){
			//ブロック付きの命令でない場合
			if(CSTLString_compare_with_char(ASTLIST_ITERATOR_1(ASTList_data(p))->name, "compound_statement_a") != 0 &&
			CSTLString_compare_with_char(ASTLIST_ITERATOR_1(ASTList_data(p))->name, "compound_statement_a") != 0){
				//かっこを追加したうえ、追加させる
				fprintf(output, "{ ");
				fprintProgramDataWithVaridateStatement_Internal(output, ASTList_data(p), validate_variable_list, validate_statement_list, for_information_list, line);
				fprintf(output, "} ");
			}
			//ブロック付きの場合
			else{
				fprintProgramDataWithVaridateStatement_Internal(output, ASTList_data(p), validate_variable_list, validate_statement_list, for_information_list, line);
			}
		}
		//statement以降に文章があれば、それも再帰的に出力させる
		if(p != ASTList_end(root->children)){
			for(p = ASTList_next(p);
				p != ASTList_end(root->children);
				p = ASTList_next(p)){
				fprintProgramDataWithVaridateStatement_Internal(output, ASTList_data(p), validate_variable_list, validate_statement_list, for_information_list, line);
			}
		}

	}
	//if-else文が来た場合
	else if(CSTLString_compare_with_char(root->name, "ifelse_statement") == 0){
		p = ASTList_begin(root->children);
		while(p != ASTList_end(root->children)){
			//ASTノードが子ASTノードの情報を持っていたら、子ASTノードについて再帰的に参照させる
			for(;
				CSTLString_compare_with_char(ASTList_data(p)->name, "statement") != 0 &&
				p != ASTList_end(root->children);
				p = ASTList_next(p)){
				fprintProgramDataWithVaridateStatement_Internal(output, ASTList_data(p), validate_variable_list, validate_statement_list, for_information_list, line);
			}
			//statementが来た場合
			if(CSTLString_compare_with_char(ASTList_data(p)->name, "statement") == 0){
				//ブロック付きの命令でない場合
				if(CSTLString_compare_with_char(ASTLIST_ITERATOR_1(ASTList_data(p))->name, "compound_statement_a") != 0 &&
				CSTLString_compare_with_char(ASTLIST_ITERATOR_1(ASTList_data(p))->name, "compound_statement_a") != 0){
					//かっこを追加したうえ、追加させる
					//fprintf(output, "{ ");
					fprintProgramDataWithVaridateStatement_Internal(output, ASTList_data(p), validate_variable_list, validate_statement_list, for_information_list, line);
					//fprintf(output, "} ");
				}
				//ブロック付きの場合
				else{
					fprintProgramDataWithVaridateStatement_Internal(output, ASTList_data(p), validate_variable_list, validate_statement_list, for_information_list, line);
				}
				//このときも１つずらす
				p = ASTList_next(p);
			}else{
				break;
			}
		}
	}
	//もし関数呼び出しが来た場合
	/*
	else if(CSTLString_compare_with_char(root->name, "call_function") == 0){
		//検証式を探すためのイテレータ
		ValidateStatementListIterator vs_i;
		//関数変更型の検証式を格納するための検証式
		VALIDATE_STATEMENT* change_function = NULL;

		//ここで、関数変更型の検証式が存在するかどうか調べる
		for(vs_i = ValidateStatementList_begin(validate_statement_list);
			vs_i != ValidateStatementList_end(validate_statement_list);
			vs_i = ValidateStatementList_next(vs_i)){

				//もし該当する未使用の関数変更型の検証式が存在するならば、その検証式を取得し、使用済みにした上、探索を終了させる
				if(ValidateStatementList_data(vs_i)->used == VALIDATE_NOTUSED && ValidateStatementList_data(vs_i)->target_statement == root){
					change_function = ValidateStatementList_data(vs_i);
					change_function->used = VALIDATE_USED;
					break;
				}
			}

		//もし関数変更型の検証式が見つかった場合は、その関数として出力させる
		if(change_function != NULL){
			fprintf(output, "%s", CSTLString_c_str(change_function->statement));
		}else{
			//ASTノードが子ASTノードの情報を持っていたら、子ASTノードについて再帰的に参照させる
			for(p = ASTList_begin(root->children); p != ASTList_end(root->children); p = ASTList_next(p)){
				fprintProgramDataWithVaridateStatement_Internal(output, ASTList_data(p), validate_variable_list, validate_statement_list, for_information_list, line);
			}
		}
	}*/
	else{
		//ASTノードが子ASTノードの情報を持っていたら、子ASTノードについて再帰的に参照させる
		for(p = ASTList_begin(root->children); p != ASTList_end(root->children); p = ASTList_next(p)){
			fprintProgramDataWithVaridateStatement_Internal(output, ASTList_data(p), validate_variable_list, validate_statement_list, for_information_list, line);
		}
	}
}

/**
検証式リストとともにプログラムデータを出力する。

@param root プログラムへのASTノード
@param validate_variable_list 検証用変数リスト
@param validate_statement_list 検証式リスト
@param for_information_list for文に関する情報のリスト

@return なし
*/
void printProgramDataWithValidateStatement(AST *root, ValidateVariableList *validate_variable_list, ValidateStatementList *validate_statement_list, ForInformationList *for_information_list){

	int line = 1;

	fprintProgramDataWithVaridateStatement_Internal(stdout, root, validate_variable_list, validate_statement_list, for_information_list, &line);

}

/**
検証式リストや検証用変数をもとにプログラムデータを生成し、指定したファイルoutputに出力する。

@param output 出力先のファイル構造体
@param root プログラムへのASTノード
@param validate_variable_list 検証用変数リスト
@param validate_statement_list 検証式リスト
@param for_information_list for文に関する情報のリスト

@return なし
*/
void fprintProgramDataWithValidateStatement(FILE *output, AST *root, ValidateVariableList *validate_variable_list, ValidateStatementList *validate_statement_list, ForInformationList *for_information_list){
	if(output != NULL){
		int line = 1;
		fprintProgramDataWithVaridateStatement_Internal(output, root, validate_variable_list, validate_statement_list, for_information_list, &line);
	}
	//もし、ファイル構造体がNULLである場合はエラーを出力したうえ、強制終了させる
	else{
		fprintf(stderr,"Input File is unexists or invalid!!\n");
		exit(1);
	}
}

/**
式に対応する検証式を出力させる。

@param output 出力先のファイル構造体
@param validate_statement_list 出力対象の検証式リスト
@param target_ast 対象のASTノード
@param check_or_modify 検証式をチェックするタイプか、プログラムを元に編集するタイプかを判断するフラグ。０：チェックするタイプ、１：編集するタイプ
@param allow_output_used_statement 使用済みの検証式も含めて出力するかどうかのフラグ　０：出力しない　１：出力する

@return なし
*/
void fprintValidateStatement(FILE *output, ValidateStatementList *validate_statement_list, AST *target_ast, int check_or_modify, int allow_output_used_statement){

	int output_id;
	ValidateStatement *output_validate_statement;
	ValidateStatementListIterator vslist_i;

	//もし、使用済みの検証式も出力する場合は、使用済みの検証式をすべて未使用に変更する。
	if(allow_output_used_statement){
		for(vslist_i = ValidateStatementList_begin(validate_statement_list);
			vslist_i != ValidateStatementList_end(validate_statement_list);
			vslist_i = ValidateStatementList_next(vslist_i)){

				if( ValidateStatementList_data(vslist_i)->used == VALIDATE_USED &&
					ValidateStatementList_data(vslist_i)->target_statement == target_ast &&
					ValidateStatementList_data(vslist_i)->check_or_modify == check_or_modify &&
					output_id > ValidateStatementList_data(vslist_i)->target_id ){
						ValidateStatementList_data(vslist_i)->used = VALIDATE_NOTUSED;
					}
		}
	}
	//未使用の検証式があるまで、ずっと出力させる
	while(1){
		ValidateStatement *output_validate_statement;
		output_id = INT_MAX;
		//未使用で、target_idが最も小さい検証式を探し出し、出力する
		for(vslist_i = ValidateStatementList_begin(validate_statement_list);
			vslist_i != ValidateStatementList_end(validate_statement_list);
			vslist_i = ValidateStatementList_next(vslist_i)){

				if( ValidateStatementList_data(vslist_i)->used == VALIDATE_NOTUSED &&
					ValidateStatementList_data(vslist_i)->target_statement == target_ast &&
					ValidateStatementList_data(vslist_i)->check_or_modify == check_or_modify &&
					output_id > ValidateStatementList_data(vslist_i)->target_id ){
						output_id = ValidateStatementList_data(vslist_i)->target_id;
						output_validate_statement = ValidateStatementList_data(vslist_i);
					}
		}
		//もし、output_idが初期状態でない場合（すなわちなんらかの検証式を見つけ出した場合)は検証式を出力させる
		if(output_id != INT_MAX){
			fprintf(output, "%s ", (char*)CSTLString_c_str(output_validate_statement->statement));
			//この検証式は使用済みにする
			output_validate_statement->used = VALIDATE_USED;
		}else{
			break;
		}
	}
}
/**
式に対応する検証式をassert(0); を削除したうえ出力させる。

@param output 出力先のファイル構造体
@param validate_statement_list 出力対象の検証式リスト
@param target_ast 対象のASTノード
@param check_or_modify 検証式をチェックするタイプか、プログラムを元に編集するタイプかを判断するフラグ。０：チェックするタイプ、１：編集するタイプ
@param allow_output_used_statement 使用済みの検証式も含めて出力するかどうかのフラグ　０：出力しない　１：出力する

@return なし
*/
void fprintValidateStatement_not_assert(FILE *output, ValidateStatementList *validate_statement_list, AST *target_ast, int check_or_modify, int allow_output_used_statement){

	int output_id;
	ValidateStatement *output_validate_statement;
	ValidateStatementListIterator vslist_i;

	CSTLString *output_validate_statement_string = CSTLString_new();

	//もし、使用済みの検証式も出力する場合は、使用済みの検証式をすべて未使用に変更する。
	if(allow_output_used_statement){
		for(vslist_i = ValidateStatementList_begin(validate_statement_list);
			vslist_i != ValidateStatementList_end(validate_statement_list);
			vslist_i = ValidateStatementList_next(vslist_i)){

				if( ValidateStatementList_data(vslist_i)->used == VALIDATE_USED &&
					ValidateStatementList_data(vslist_i)->target_statement == target_ast &&
					ValidateStatementList_data(vslist_i)->check_or_modify == check_or_modify &&
					output_id > ValidateStatementList_data(vslist_i)->target_id ){
						ValidateStatementList_data(vslist_i)->used = VALIDATE_NOTUSED;
					}
		}
	}
	//未使用の検証式があるまで、ずっと出力させる
	while(1){
		ValidateStatement *output_validate_statement;
		output_id = INT_MAX;
		//未使用で、target_idが最も小さい検証式を探し出し、出力する
		for(vslist_i = ValidateStatementList_begin(validate_statement_list);
			vslist_i != ValidateStatementList_end(validate_statement_list);
			vslist_i = ValidateStatementList_next(vslist_i)){

				if( ValidateStatementList_data(vslist_i)->used == VALIDATE_NOTUSED &&
					ValidateStatementList_data(vslist_i)->target_statement == target_ast &&
					ValidateStatementList_data(vslist_i)->check_or_modify == check_or_modify &&
					output_id > ValidateStatementList_data(vslist_i)->target_id ){
						output_id = ValidateStatementList_data(vslist_i)->target_id;
						output_validate_statement = ValidateStatementList_data(vslist_i);
					}
		}
		//もし、output_idが初期状態でない場合（すなわちなんらかの検証式を見つけ出した場合)は検証式を出力させる
		if(output_id != INT_MAX){
			//出力したい検証式を文字列として取得する
			CSTLString_assign(output_validate_statement_string,
					CSTLString_c_str(output_validate_statement->statement));

			//assert(0);を削除したうえ、出力させる
			CSTLString_replace_string(output_validate_statement_string, ASSERT_STRING, "");
			fprintf(output, "%s ", (char*)CSTLString_c_str(output_validate_statement_string));
			//この検証式は使用済みにする
			output_validate_statement->used = VALIDATE_USED;
		}else{
			break;
		}
	}

	CSTLString_delete(output_validate_statement_string);
}

/**
プログラムスライシング情報の変数定義をもとに、検証用変数リストの出力を設定する。
@param validate_variable_list 検証用変数リスト
@param expr_slicing_list プログラムスライシング情報のリスト

@return なし
 */
void setValidateVariableFromExprSlicing(ValidateVariableList *validate_variable_list, EXPR_SLICING_LIST *expr_slicing_list){
	EXPR_SLICING_LISTIterator e_i;

	ValidateVariableListIterator vvlist_i;

	CSTLString *variable_name;
	AST *declaration_node;

	//検証用変数リストを逐次取得し、プログラムスライシング側の変数宣言に対応するかどうかチェックする
	for(e_i = EXPR_SLICING_LIST_begin(expr_slicing_list);
		e_i != EXPR_SLICING_LIST_end(expr_slicing_list);
		e_i = EXPR_SLICING_LIST_next(e_i)){

		//もし、変数宣言である場合
		if(CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "declaration_with_init") == 0 ||
				CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "declarator") == 0){
			//変数名を取得する
			variable_name = ARRAY_OFFSET_LIST_front(EXPR_SLICING_LIST_data(e_i)->target_variable)->variable_name;

			//宣言先を取得する
			declaration_node = EXPR_SLICING_LIST_data(e_i)->expression;
			//プログラムスライシング側の変数宣言に対応していることがわかれば、その変数の使用状態を０とし、使用できるようにする
			for(vvlist_i = ValidateVariableList_begin(validate_variable_list);
				vvlist_i != ValidateVariableList_end(validate_variable_list);
				vvlist_i = ValidateVariableList_next(vvlist_i)){
					if(CSTLString_compare(ValidateVariableList_data(vvlist_i)->target_variable_name, variable_name) == 0 &&
							ValidateVariableList_data(vvlist_i)->block_id == declaration_node->block_id &&
							ValidateVariableList_data(vvlist_i)->block_level == declaration_node->block_level){
						ValidateVariableList_data(vvlist_i)->used = 0;
					}
			}
		}

		//子ノードにも同じ探索を行う
		setValidateVariableFromExprSlicing(validate_variable_list, EXPR_SLICING_LIST_data(e_i)->children1);
		setValidateVariableFromExprSlicing(validate_variable_list, EXPR_SLICING_LIST_data(e_i)->children2);
	}
}

/**
fprintProgramDataWithPSIVaridateStatementの内部処理である。

@param output 出力する先のファイル
@param expr_slicing_list プログラムスライシング情報
@param validate_variable_list 検証用変数リスト
@param validate_statement_list 検証式リスト
@param for_information_list for文に関する情報
@param check_target_ast チェック検証式の対象へのASTノード
@param line 出力に用いる行数

@return なし
 */
void fprintProgramDataWithPSIVaridateStatement_Internal(FILE *output, EXPR_SLICING_LIST *expr_slicing_list, ValidateStatementList *validate_statement_list,
			ValidateVariableList *validate_variable_list, ForInformationList *for_information_list, AST *check_target_ast, int *line){
	EXPR_SLICING_LISTIterator e_i;
	AST *block_start, *block_end;
	ValidateVariableListIterator vvlist_i;
	//プログラムスライシングに関係する情報を出力させる。
	for(e_i = EXPR_SLICING_LIST_begin(expr_slicing_list);
		e_i != EXPR_SLICING_LIST_end(expr_slicing_list);
		e_i = EXPR_SLICING_LIST_next(e_i)){
		//プログラムスライシングのフラグが立っているのみ出力処理を行う
		if(EXPR_SLICING_LIST_data(e_i)->flag == 1){
			//for文の場合
			if(CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "for_statement_type_a") == 0 ||
				CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "for_statement_type_b") == 0 ||
				CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "for_statement_type_c") == 0 ||
				CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "for_statement_type_d") == 0){
				//式の出力に使用するためのCSTLString
				CSTLString *statement = CSTLString_new();
				//当てはまるfor文の情報を取得する
				ForInformation *for_information = searchFOR_INFORMATION_FromAST(for_information_list, EXPR_SLICING_LIST_data(e_i)->expression);

				//ASTノードの行数と引数の行数がかみ合わないとき、改行を出力させ、出力する行数を調整する
				while(*line < for_information->init_expression->line){
					fprintf(output, "\n");
					*line = *line + 1;
				}
				//まず初期式についてのチェック用および検証用変数の編集用の検証式出力させる
				//チェック式についてはcheck_target_astと一致するASTノードの場合のみ出力させる
				getStringFromAST(statement, for_information->init_expression);
				if(EXPR_SLICING_LIST_data(e_i)->expression == check_target_ast){
					fprintValidateStatement(output, validate_statement_list, for_information->init_expression, CHECK_VS, FALSE);
				}else{
					fprintValidateStatement_not_assert(output, validate_statement_list, for_information->init_expression, CHECK_VS, FALSE);
				}
				fprintf(output, "%s ", CSTLString_c_str(statement));
				fprintValidateStatement(output, validate_statement_list, for_information->init_expression, MODIFY_VS, FALSE);


				//次に条件式を" while(条件式){for文内の式 " の形式にする
				CSTLString_assign(statement, "");
				getStringFromAST(statement, for_information->continue_condition);
				//セミコロンは余分なので削除する
				CSTLString_replace_string(statement, ";", "");
				fprintf(output, "while( %s ) {", CSTLString_c_str(statement));

				//for文内の式は再帰的に呼び出す
				fprintProgramDataWithPSIVaridateStatement_Internal(output, EXPR_SLICING_LIST_data(e_i)->children1, validate_statement_list,
						validate_variable_list, for_information_list, check_target_ast, line);

				//最後に増分式があれば、それをチェック式および検証用変数の編集式を含ませて出力させる
				//チェック式についてはcheck_target_astと一致するASTノードの場合のみ出力させる
				if(for_information->inc_dec_expression != NULL){
					CSTLString_assign(statement, "");
					getStringFromAST(statement, for_information->inc_dec_expression);
					if(EXPR_SLICING_LIST_data(e_i)->expression == check_target_ast){
						fprintValidateStatement(output, validate_statement_list, for_information->inc_dec_expression, CHECK_VS, FALSE);
					}else{
						fprintValidateStatement_not_assert(output, validate_statement_list, for_information->inc_dec_expression, CHECK_VS, FALSE);
					}
					fprintf(output, "\n%s ; ", CSTLString_c_str(statement));
					fprintValidateStatement(output, validate_statement_list, for_information->inc_dec_expression, MODIFY_VS, FALSE);
				}

				//大かっこで区切って終了
				fprintf(output, "} ");
				CSTLString_delete(statement);
			}
			//if_else文の場合
			else if(CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "ifelse_statement") == 0){
				//1番目のノード(if部分)からstatement部分まで出力させる
				fprintfStatement(output, EXPR_SLICING_LIST_data(e_i)->expression, line, 1, &block_start, &block_end);
				//ローカル変数に対する検証用変数を出力させる
				if(block_start != NULL){
					for(vvlist_i = ValidateVariableList_begin(validate_variable_list);
						vvlist_i != ValidateVariableList_end(validate_variable_list);
						vvlist_i = ValidateVariableList_next(vvlist_i)){
						//未使用状態で、宣言位置・ブロックID・ブロックレベルが一致する検証用変数を出力する
						if(ValidateVariableList_data(vvlist_i)->used == 0 && block_start->line == ValidateVariableList_data(vvlist_i)->declaration_location
							&& ValidateVariableList_data(vvlist_i)->block_id == block_start->block_id && ValidateVariableList_data(vvlist_i)->block_level == block_start->block_level){
							fprintf(output, "%s %s ; ", (char*)CSTLString_c_str(ValidateVariableList_data(vvlist_i)->type), (char*)CSTLString_c_str(ValidateVariableList_data(vvlist_i)->variable_name));
							//この検証用変数は使用済みにする
							ValidateVariableList_data(vvlist_i)->used = 1;
						}
					}
				}
				//プログラムスライシングの子ノードを参照する
				fprintProgramDataWithPSIVaridateStatement_Internal(output, EXPR_SLICING_LIST_data(e_i)->children1, validate_statement_list,
						validate_variable_list, for_information_list, check_target_ast, line);
				//ブロックで構成されている場合は終わりの"}"を追加で出力させる
				if(block_end != NULL){
					fprintDataFromAST(output, block_end, line);
				}
				//３番目のノード(else部分)からstatement部分まで出力させる
				fprintfStatement(output, EXPR_SLICING_LIST_data(e_i)->expression, line, 3, &block_start, &block_end);
				//ローカル変数に対する検証用変数を出力させる
				if(block_start != NULL){
					for(vvlist_i = ValidateVariableList_begin(validate_variable_list);
						vvlist_i != ValidateVariableList_end(validate_variable_list);
						vvlist_i = ValidateVariableList_next(vvlist_i)){
						//未使用状態で、宣言位置・ブロックID・ブロックレベルが一致する検証用変数を出力する
						if(ValidateVariableList_data(vvlist_i)->used == 0 && block_start->line == ValidateVariableList_data(vvlist_i)->declaration_location
							&& ValidateVariableList_data(vvlist_i)->block_id == block_start->block_id && ValidateVariableList_data(vvlist_i)->block_level == block_start->block_level){
							fprintf(output, "%s %s ; ", (char*)CSTLString_c_str(ValidateVariableList_data(vvlist_i)->type), (char*)CSTLString_c_str(ValidateVariableList_data(vvlist_i)->variable_name));
							//この検証用変数は使用済みにする
							ValidateVariableList_data(vvlist_i)->used = 1;
						}
					}
				}
				//プログラムスライシングの子ノードを参照する
				fprintProgramDataWithPSIVaridateStatement_Internal(output, EXPR_SLICING_LIST_data(e_i)->children2, validate_statement_list,
						validate_variable_list, for_information_list, check_target_ast, line);
				//ブロックで構成されている場合は終わりの"}"を追加で出力させる
				if(block_end != NULL){
					fprintDataFromAST(output, block_end, line);
				}
			}
			//以下のような子ノード持ちのものである場合
			//関数定義,if文、while文,do_while式,switch式,ラベル式
			else if(EXPR_SLICING_LIST_size(EXPR_SLICING_LIST_data(e_i)->children1) > 0){
				//1番目の子ノードからstatement部分まで出力させる
				fprintfStatement(output, EXPR_SLICING_LIST_data(e_i)->expression, line, 1, &block_start, &block_end);
				//ローカル変数に対する検証用変数を出力させる
				if(block_start != NULL){
					for(vvlist_i = ValidateVariableList_begin(validate_variable_list);
						vvlist_i != ValidateVariableList_end(validate_variable_list);
						vvlist_i = ValidateVariableList_next(vvlist_i)){
						//未使用状態で、宣言位置・ブロックID・ブロックレベルが一致する検証用変数を出力する
						if(ValidateVariableList_data(vvlist_i)->used == 0 && block_start->line == ValidateVariableList_data(vvlist_i)->declaration_location
							&& ValidateVariableList_data(vvlist_i)->block_id == block_start->block_id && ValidateVariableList_data(vvlist_i)->block_level == block_start->block_level){
							fprintf(output, "%s %s ; ", (char*)CSTLString_c_str(ValidateVariableList_data(vvlist_i)->type), (char*)CSTLString_c_str(ValidateVariableList_data(vvlist_i)->variable_name));
							//この検証用変数は使用済みにする
							ValidateVariableList_data(vvlist_i)->used = 1;
						}
					}
				}

				//ブロック開始時に対する検証式の追加
				fprintValidateStatement(output, validate_statement_list, block_start, MODIFY_VS, FALSE);

				//プログラムスライシングの子ノードを参照する
				fprintProgramDataWithPSIVaridateStatement_Internal(output, EXPR_SLICING_LIST_data(e_i)->children1, validate_statement_list,
						validate_variable_list, for_information_list, check_target_ast, line);
				//ブロックで構成されている場合は終わりの"}"を追加で出力させる
				if(block_end != NULL){
					fprintDataFromAST(output, block_end, line);
				}
			}
			//上記以外の式の場合
			else{
				//式に対して、チェック式および検証用変数の編集式を含ませて出力させる
				//チェック式についてはcheck_target_astと一致するASTノードの場合のみ出力させる
				if(EXPR_SLICING_LIST_data(e_i)->expression == check_target_ast){
					fprintValidateStatement(output, validate_statement_list, EXPR_SLICING_LIST_data(e_i)->expression, CHECK_VS, FALSE);
				}else{
					fprintValidateStatement_not_assert(output, validate_statement_list, EXPR_SLICING_LIST_data(e_i)->expression, CHECK_VS, FALSE);
				}
				fprintDataFromAST(output, EXPR_SLICING_LIST_data(e_i)->expression, line);
				fprintValidateStatement(output, validate_statement_list, EXPR_SLICING_LIST_data(e_i)->expression, MODIFY_VS, FALSE);
			}
		}
	}
}


/**
プログラムスライシング情報をもとに検証式を追加しながら出力させる。

@param output 出力する先のファイル
@param expr_slicing_list プログラムスライシング情報
@param validate_variable_list 検証用変数リスト
@param validate_statement_list 検証式リスト
@param for_information_list for文に関する情報
@param check_target_ast チェック検証式の対象へのASTノード

@return なし
 */
void fprintProgramDataWithPSIVaridateStatement(FILE *output, EXPR_SLICING_LIST *expr_slicing_list, ValidateStatementList *validate_statement_list,
			ValidateVariableList *validate_variable_list, ForInformationList *for_information_list, AST *check_target_ast){

	ValidateVariableListIterator vvlist_i;

	//すべての検証用変数リストをすべて使用状態にする
	for(vvlist_i = ValidateVariableList_begin(validate_variable_list);
		vvlist_i != ValidateVariableList_end(validate_variable_list);
		vvlist_i = ValidateVariableList_next(vvlist_i)){
		ValidateVariableList_data(vvlist_i)->used = 1;
	}
	//プログラムスライシング情報の変数定義をもとに、検証用変数リストの出力を設定する
	setValidateVariableFromExprSlicing(validate_variable_list, expr_slicing_list);

	//グローバル変数に対する検証用変数リストを出力させる
	for(vvlist_i = ValidateVariableList_begin(validate_variable_list);
		vvlist_i != ValidateVariableList_end(validate_variable_list);
		vvlist_i = ValidateVariableList_next(vvlist_i)){
			//未使用状態のブロックIDとブロックレベルが両方とも０である検証用変数を全て出力する
			if(ValidateVariableList_data(vvlist_i)->used == 0 && ValidateVariableList_data(vvlist_i)->block_level == 0 && ValidateVariableList_data(vvlist_i)->block_id == 0){
				fprintf(output, "%s %s ; ", (char*)CSTLString_c_str(ValidateVariableList_data(vvlist_i)->type), (char*)CSTLString_c_str(ValidateVariableList_data(vvlist_i)->variable_name));
				//この検証用変数は使用済みにする
				ValidateVariableList_data(vvlist_i)->used = 1;
			}
		}

	//プログラムスライシング情報をもとに、検証式を追加しながら出力させる
	int line = 1;
	fprintProgramDataWithPSIVaridateStatement_Internal(output, expr_slicing_list, validate_statement_list,
			validate_variable_list,for_information_list, check_target_ast, &line);

}


/**
プログラムをチェック式ごとにプログラムスライシングと検証式付加を行ったファイルを生成する。
@param expr_slicing_list プログラムスライシング情報
@param validate_variable_list 検証用変数リスト
@param validate_statement_list 検証式リスト
@param for_information_list for文に関する情報
@param include_list インクルードリスト

@return なし
 */
void createValidateStatementAdderFileEachCheck(EXPR_SLICING_LIST *expr_slicing_list, ValidateStatementList *validate_statement_list,
		ValidateVariableList *validate_variable_list, ForInformationList *for_information_list, INCLUDE_LIST *include_list){

	ASTPOINTER_LIST *astpointer_list = ASTPOINTER_LIST_new();
	ASTPOINTER_LISTIterator a_i;

	int file_counter;

	CSTLString *file_name = CSTLString_new();

	FILE *output;

	//検証式のチェック式のASTノードリストを取得する
	getASTList_FromValidateStatementList(validate_statement_list, astpointer_list);

	for(file_counter = 0, a_i = ASTPOINTER_LIST_begin(astpointer_list);
		a_i != ASTPOINTER_LIST_end(astpointer_list);
		file_counter++, a_i = ASTPOINTER_LIST_next(a_i)){
		//プログラムスライシングの状態を初期化する
		initExprSlicingListFlag(expr_slicing_list);

		//そのASTノードをもとにプログラムスライシングを行う
		startStaticSlicing(*ASTPOINTER_LIST_data(a_i), expr_slicing_list);

		//出力したいファイル名を指定する
		CSTLString_printf(file_name, 0, "%s_%d.c", getFileName(), file_counter);

		//ファイルを開ける
		output = fopen(CSTLString_c_str(file_name), "w");

		//すべての検証式リストの使用状態を未使用状態に初期化する
		initVaridateStatement_flag(validate_statement_list);

		//プログラムスライシング情報に基づいて、検証式を出力させる
		fprintProgramDataWithPSIVaridateStatement(output, expr_slicing_list, validate_statement_list,
				validate_variable_list, for_information_list, *ASTPOINTER_LIST_data(a_i));

		//ファイルを閉じる
		fclose(output);

		//インクルードリストからインクルードを追加する
		addIncludeDataFromFile((char*)CSTLString_c_str(file_name), include_list);
	}

	CSTLString_delete(file_name);
}

int compare_validate_statement_list_ast(const void *a, const void *b){

	int flag = ((ValidateStatement*)a)->target_statement - ((ValidateStatement*)b)->target_statement;

	if(flag != 0){
		return ((ValidateStatement*)a)->target_statement->line - ((ValidateStatement*)b)->target_statement->line;
	}else{
		return flag;
	}
}

/**
検証式リストをASTノードごとにソートする。
@param validate_statement_list ソート対象の検証式リスト
*/
void validateStatementListSort(ValidateStatementList *validate_statement_list){
	ValidateStatementList_sort(validate_statement_list, compare_validate_statement_list_ast);
}

/**
検証式リストのチェック式から、ASTノードを取り出し、ASTリストとしてまとめる。
@param validate_statement_list 取り出し先の検証式リスト
@param ast_node_list まとめる先のASTノードリスト

@return なし
 */
void getASTList_FromValidateStatementList(ValidateStatementList *validate_statement_list, ASTPOINTER_LIST *ast_node_list){
	AST *tmp;
	ValidateStatementListIterator vs_list;
	//検証式リストを探索する
	for(vs_list = ValidateStatementList_begin(validate_statement_list);
		vs_list != ValidateStatementList_end(validate_statement_list);
		vs_list = ValidateStatementList_next(vs_list)){

		//もし、tmpが未定義か異なる値が出た場合
		if(tmp == NULL || ValidateStatementList_data(vs_list)->check_or_modify == CHECK_VS &&
				tmp != ValidateStatementList_data(vs_list)->target_statement){
			tmp = ValidateStatementList_data(vs_list)->target_statement;
			ASTPOINTER_LIST_push_back(ast_node_list, tmp);
		}
	}
}
