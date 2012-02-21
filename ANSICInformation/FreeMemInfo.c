 #include "FreeMemInfo.h"

 /**
 新しいメモリ解放関係の情報を生成する。

 @param free_variable 新しい解放先の変数に関するオフセットリスト

 @return 新しく生成されたメモリ解放関係の情報へのアドレスを返す。
 */
 FREEMEMINFO * new_FREEMEMINFO(ARRAY_OFFSET_LIST *free_variable){
	FREEMEMINFO *new_freememinfo = (FREEMEMINFO*)malloc(sizeof(FREEMEMINFO));

	new_freememinfo->free_variable = free_variable;

	return new_freememinfo;
 }

 /**
 対象の関数へのASTノードからfree関数を見つけ、それに関する情報を取得する。

 @param freememinfo 取得先のメモリ解放関係の情報
 @param call_function 対象の関数へのASTノード
 @param function_information_list 関数に関する情報のリスト
 @param vtlist 変数テーブルの情報
 @param target_statement 対象の関数が位置している式へのASTノード

 @return なし
 */

 void getFreememInfo(FREEMEMINFO **freememinfo, AST *call_function, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist, AST *target_statement){

	//関数名を取得する
	//呼び出した関数名を取得する
	CSTLString *function_name = CSTLString_new();
	getStringFromAST(function_name, ASTList_data(ASTList_begin(call_function->children)));
	//もし関数名がfreeである場合
	if(CSTLString_compare_with_char(function_name, "free") == 0){
		//無視するためのASTノードリスト
		ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();

		ARRAY_OFFSET_LIST *freemem_argument_info = ARRAY_OFFSET_LIST_new();

		int switch_mode = 0;
		//freeの第一引数を取得する。
		AST *argument1;
		getArgumentAST(&argument1, call_function, 1);
		//第一引数の内容から、メモリ解放関係の情報を取得する
		getArgumentOffsetInfo(argument1, function_information_list, vtlist, ignore_ast_list, freemem_argument_info, target_statement, &switch_mode);

		//もし、何らか修得できた場合
		if(ARRAY_OFFSET_LIST_size(freemem_argument_info) > 0){
			*freememinfo = new_FREEMEMINFO(freemem_argument_info);
		}
	}
 }

 /**
 指定したメモリ解放関係の情報を出力する。

 @param freememinfo 出力するメモリ解放関係の情報

 @return なし
 */
 void printFREEMEMINFO(FREEMEMINFO *freememinfo){
	printf("------FREE_INFO------\n\n");
	printARRAY_OFFSET_LIST(freememinfo->free_variable);
	printf("---------------------\n\n");
 }
