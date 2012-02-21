/*!
  @brief このファイルは関数に関する情報を取得するための命令が含まれている。
  @file FunctionInformation.h
  @author faithnh

 */

#ifndef FUNCTION_INFORMATION_HEADDER
#define FUNCTION_INFORMATION_HEADDER

#include<cstl/list.h>
#include"../Library/CSTLString.h"
#include"AST.h"

//パラメータが入出力タイプか入力タイプか出力タイプかを示す
#define PARAM_INOUT_TYPE 2
#define PARAM_IN_TYPE 1
#define PARAM_OUT_TYPE 0

/**
引数に関する情報
 */
typedef struct param_information{
	CSTLString *param_type; ///パラメータの型
	CSTLString *param_name; ///パラメータの名前
	int array_level;		///配列のレベル
	int pointer_level;		///ポインタのレベル
	int in_out_flag; 		///入力型か出力型かの判定　１：入力　０：出力　２：入出力
} PARAM_INFORMATION;

CSTL_LIST_INTERFACE(PARAM_INFORMATION_LIST, PARAM_INFORMATION)

/**
関数に関する情報。関数からの検証式の生成などに用いる。
 */
typedef struct function_information{
	AST *function_node;								///関数定義のASTノードへのアドレス
	CSTLString *return_type;						///返却値の型（const intなどと表記される)
	CSTLString *function_name;						///関数名(*funcなどと表記される）
	PARAM_INFORMATION_LIST *param_information_list;	///この関数の引数リスト
} FUNCTION_INFORMATION;



CSTL_LIST_INTERFACE(FUNCTION_INFORMATION_LIST, FUNCTION_INFORMATION)

/**
関数に関する情報を生成する。

@param function_node 対象の関数へのノード
@param return_type 返却値のタイプ
@param function_name 関数名
@param param_information_list パラメータに関する情報

@return 生成された関数に関する情報へのアドレスを返す。
 */
FUNCTION_INFORMATION *new_FUNCTION_INFORMATION(AST *function_node, CSTLString *return_type, CSTLString *function_name, PARAM_INFORMATION_LIST *param_information_list);


/**
パラメータに関する情報を生成する。

@param param_type パラメータの型
@param param_name パラメータの名前
@param array_level 配列のレベル
@param pointer_level ポインタのレベル
@param in_out_flag 入力型か出力型かの判定　１：入力　０：出力　２：入出力

@return 生成されたパラメータに関する情報へのアドレスを返す。
 */

PARAM_INFORMATION *new_PARAM_INFORMATION(CSTLString *param_type, CSTLString *param_name,
			int array_level, int pointer_level, int in_out_flag);

/**
指定したプログラムのASTノードから関数定義を探し、それに基づいて関数に関する情報を生成し、それらのリストfunction_information_list
に登録する。

@param function_information_list 登録先の関数に関する情報のリスト
@param root 指定したプログラムのASTノード

@return なし
 */
void getFunctionInformation(FUNCTION_INFORMATION_LIST *function_information_list, AST *root);

/**
指定したファイル名file_nameで定義された関数に関する情報を関数に関する情報のリストfunction_information_listに設定する。
@param function_information_list 登録先の関数に関する情報のリスト
@param file_name 指定したファイル名

@return なし
 */
void getFunctionInformationFromFile(FUNCTION_INFORMATION_LIST *function_information_list, char* file_name);

/**
指定した関数の定義自体から、パラメータ定義などを削除する。

@param target_string 対象の関数の定義自体の文字列

@return なし
 */
void deleteParameterDefine(CSTLString *target_string);


/**
関数に関する情報リストの内容を出力させる。
@param function_information_list 出力対象の関数に関する情報リスト

@return なし
*/

void printFUNCTION_INFORMATION_LIST(FUNCTION_INFORMATION_LIST *function_information_list);

/**
関数に関する情報リストから、指定した関数名を探し、それに関する構造体へのアドレスを返す。

@param target_function_name 指定した関数名
@param function_information_list 検索対象の関数に関する情報リスト

@return 見つかった場合はその関数に関する構造体へのアドレスを返す。みつからなければ、NULLを返す。
 */

FUNCTION_INFORMATION *searchFUNCTION_INFORMATION(CSTLString *target_function_name, FUNCTION_INFORMATION_LIST *function_information_list);

/**
指定した関数名が関数に関する情報リストから探し、ポインタレベルを返す。
@param target_function_name 指定した関数名
@param function_information_list 検索対象の関数に関する情報リスト

@return 見つかった場合はその関数のポインタレベルを返す、そうでない場合は-1を返す。
 */

int getPointerLevelFromFUNCTION_INFORMATION_LIST(CSTLString *target_function_name, FUNCTION_INFORMATION_LIST *function_information_list);

/**
パラメータリストを示すノードparam_info_nodeから、パラメータの情報を取得し、param_information_listに登録する。

@param param_info_node パラメータリストを示すノード
@param param_information_list 登録先のパラメータ情報リスト

@return なし
 */
void getParamInformationFromFunctionDifinition(AST *param_info_node, PARAM_INFORMATION_LIST *param_information_list);

/**
パラメータのポインタレベル・配列レベルおよび型名から、このパラメータは入力型か出力型か判定する。

@param param_type パラメータの型名
@param pointer_level ポインタのレベル
@param array_level 配列のレベル

@return 入力型ならば１、出力型ならば０を返す。
 */
int getIN_OUT_FLAG(CSTLString *param_type, int pointer_level, int array_level);
#endif
