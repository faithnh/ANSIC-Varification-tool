/*!
  @brief このファイルは、除算・剰余算を検出するために使用するのに必要な情報を取得するための命令が含まれている。

  @file DivitionInformation.h
  @author faithnh
 */

 #ifndef DIVITION_INFORMATION_HEADDER
 #define DIVITION_INFORMATION_HEADDER

 #include<cstl/list.h>
 #include"AST.h"
 #include"Synbol.h"
 #include"../Library/CSTLString.h"
 #include"PointerArrayControl.h"
#include"FunctionInformation.h"
 /**
 除算および剰余算に関する情報を格納する。
 */
 typedef struct divition_information{
	AST *target_expression; ///対象の式
	int type; ///除算か剰余かどうかのタイプ　０：除算式　１：剰余式
	CSTLString *statement; ///除算および剰余以下の式
	ARRAY_OFFSET_LIST *identifiers; ///式内の識別子一覧
 } DIVITION_INFORMATION;

 /**
 DIVITION_INFORMATIONのリスト
 */
 CSTL_LIST_INTERFACE(DIVITION_INFORMATION_LIST, DIVITION_INFORMATION)

 /**
 除算および剰余算に関する情報を生成する。

 @param target_expression 対象の式へのASTノードのアドレス
 @param type 除算か剰余かどうかのタイプ　０：除算式　１：剰余式
 @param statement 除算および剰余以下の式
 @param identifiers 式内の識別子一覧

 @return 生成された情報へのアドレスが返される
 */
 DIVITION_INFORMATION *new_DIVITION_INFORMATION(AST *target_expression, int type, CSTLString *statement, ARRAY_OFFSET_LIST *identifiers);

 /**
 除算および剰余算に関する情報を生成する。

 @param target_expression 対象の式へのASTノードのアドレス
 @param type 除算か剰余かどうかのタイプ　０：除算式　１：剰余式
 @param statement 除算および剰余以下の式
 @param identifiers 式内の識別子一覧

 @return 生成された情報へのアドレスが返される
 */
 DIVITION_INFORMATION *new_DIVITION_INFORMATION_char(AST *target_expression, int type, char *statement, ARRAY_OFFSET_LIST *identifiers);

 /**
 指定された式から、div_exprおよびmod_exprを見つけ、それ以下の式を除算および剰余残に関する情報に格納する

 @param expression_ast 指定された式へのASTノードのアドレス
 @param function_information_list 関数に関する情報のリスト
 @param vtlist 変数テーブルリスト
 @param divition_information_list 除算および剰余算に関する情報を格納するためのリスト
 @param target_expression 対象の式へのASTノードのアドレス
 @param ignore_ast_list 重複防止のために使用するASTノードへのリスト

 @return なし
 */
 void getDIVITION_INFORMATION_LIST(AST *expression_ast, FUNCTION_INFORMATION_LIST *function_information_list,
		 VARIABLE_TABLE_LIST *vtlist, DIVITION_INFORMATION_LIST *divition_information_list, AST *target_expression,
		 ASTPOINTER_LIST *ignore_ast_list);

 /**
 除算および剰余算に関する情報のリストの内容を出力させる

 @param divition_information_list 除算および剰余算に関する情報のリスト

 @return なし
 */
 void printDIVITION_INFORMATION_LIST(DIVITION_INFORMATION_LIST *divition_information_list);
 #endif
