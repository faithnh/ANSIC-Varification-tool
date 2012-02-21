/*!
  @brief このファイルはプログラムスライシングに関する情報を取り扱う命令が含まれている。
  @file ProgramSlicingInformation.h
  @author faithnh
 */
#ifndef PROGRAM_SLICING_INFORMATION_HEADDER
#define PROGRAM_SLICING_INFORMATION_HEADDER

#include"../ANSICInformation/AST.h"
#include"../ANSICInformation/PointerArrayControl.h"
#include<cstl/list.h>

/**
データ依存関係の情報
 */

struct dd_information;

CSTL_LIST_INTERFACE(DD_INFORMATION_LIST, struct dd_information)

/**
スライシングを行うための各処理ごとの対象変数・依存関係をあらわした構造体である。
*/
struct expr_slicing;

CSTL_LIST_INTERFACE(EXPR_SLICING_LIST, struct expr_slicing);

typedef struct expr_slicing{
	int expr_slicing_number;		///プログラムスライシングに割り当てられるブロックごと番号
	AST *expression;				///対象の式へのＡＳＴノード
	DD_INFORMATION_LIST *dd_list;		///依存関係リスト
	ARRAY_OFFSET_LIST *target_variable;	///変数のオフセットリスト
	ARRAY_OFFSET_LIST *dependences;		///依存関係の配列オフセットリスト
	EXPR_SLICING_LIST *children1;	///ifやwhile、forに対するスライシングリスト
	EXPR_SLICING_LIST *children2;	///else文に対するスライシングリスト
	struct expr_slicing *parent;			///親をたどるためのノード
	int flag;						///この処理を使用するかどうかのフラグ １：使用する ０：使用しない

} EXPR_SLICING;

typedef struct dd_information{
	CSTLString *dd_variable_name;	//データ依存関係に関する変数名
	EXPR_SLICING *dd_target;		//データ依存関係のターゲットとなる命令
} DD_INFORMATION;


/**
スライシングを行うための構造体を生成する。
@param expr_slicing_number 対象の式に対するAST番号
@param expression 対象の式へのＡＳＴノード
@param target_variable 変数のオフセットリスト
@param dependences 依存関係の配列オフセットリスト
@param children1 ifやwhile、forに対するスライシングリスト
@param children2 else文に対するスライシングリスト
@param parent 親をたどるためのノード

@return 生成されたスライシングを行うための構造体へのアドレスを返す。

*/
EXPR_SLICING *new_EXPR_SLICING(int expr_slicing_number, AST *expression, ARRAY_OFFSET_LIST *target_variable,
		ARRAY_OFFSET_LIST *dependences,EXPR_SLICING_LIST *children1, EXPR_SLICING_LIST *children2,
		EXPR_SLICING *parent );

/**
データ依存関係に関する情報を生成する。
@param dd_variable_name データ依存関係に関する変数名
@param *dd_target データ依存関係のターゲットとなる命令

@return 生成されたデータ依存関係に関する情報の構造体へのアドレスを返す。

*/
DD_INFORMATION *new_DD_INFORMATION(CSTLString *dd_variable_name, EXPR_SLICING *dd_target);
/**
指定したデータ依存関係のリストから、指定された変数名が存在するか調べる。

@param variable_name 指定された変数名
@param dd_information_list 指定したデータ依存関係のリスト
@param find_dd_informaiton 見つけた場合に返すデータ依存関係の情報
@return 存在する場合は１、そうでない場合は０を返す。
 */
int searchDD(CSTLString *variable_name, DD_INFORMATION_LIST *dd_information_list, DD_INFORMATION **find_dd_informaiton);
/**
指定したプログラムスライシング情報のデータ依存関係から、指定された変数名である変数宣言が存在するか調べる。

@param variable_name 指定された変数名
@param expr_slicing 指定したプログラムスライシング情報のデータ

@return 存在する場合は１、そうでない場合は０を返す。
 */
int searchDeclarationDD(CSTLString *variable_name, EXPR_SLICING *expr_slicing);

/**
プログラムスライシングのflagを初期化する。
@param expr_slicing_list 対象のプログラムスライシング情報のリスト

@return なし
 */
void initExprSlicingListFlag(EXPR_SLICING_LIST *expr_slicing_list);
/**
プログラム全体のプログラムスライシングリストexpr_slicing_listから、
関数呼び出しに対応する関数定義のプログラムスライシング情報を取得する。

@param function_name 関数名
@param expr_slicing_list プログラム全体のプログラムスライシングリスト

@return 取得に成功した場合、関数呼び出しに対応する関数定義へのプログラムスライシング情報を返す、失敗した場合はNULLを返す
 */
EXPR_SLICING *searchFunctionPSI(CSTLString *function_name, EXPR_SLICING_LIST *expr_slicing_list);

/**
関数内で扱うグローバル変数を抽出し、配列オフセットリストとして抽出する。

@param output_global_variable_list 抽出先の配列オフセットリスト
@param function_expr_slicing_list 関数呼び出しに対するプログラムスライシングリスト
@param global_variable_list グローバル変数一覧を示す配列オフセットリスト

@return なし
 */
void getFunctionGrobalVariable(ARRAY_OFFSET_LIST *output_global_variable_list, EXPR_SLICING_LIST *function_expr_slicing_list,
		ARRAY_OFFSET_LIST *global_variable_list);

/**
対象のプログラムスライシングリストから、変数宣言部分を抽出し、配列オフセット情報として抽出する。

@param global_variable_list グローバル変数一覧を示す配列オフセットリスト
@param program_expr_slicing_list プログラム全体のプログラムスライシングリスト

@return なし
 */
void getVariableDeclarationFromEXPR_SLICING_LIST(ARRAY_OFFSET_LIST *global_variable_list, EXPR_SLICING_LIST *program_expr_slicing_list);

/**
関数呼び出しから、取り扱うグローバル変数を抽出し、対象の変数一覧に追加していく。
@param expr_slicing_list 追加対象のプログラムスライシングリスト
@param program_expr_slicing_list プログラム全体のプログラムスライシングリスト

 */
void setGlobalVariable(EXPR_SLICING_LIST *expr_slicing_list, EXPR_SLICING_LIST *program_expr_slicing_list);

/**
スライシングに関する情報リストexpr_slicing_listを出力させる。

@param expr_slicing_list スライシングに関する情報リスト

@return なし
 */
void print_EXPR_SLICING_LIST(EXPR_SLICING_LIST *expr_slicing_list);

/**
スライシングに関する情報リストexpr_slicing_listをツリー形式で出力させる。

@param expr_slicing_list スライシングに関する情報リスト
@param program_slicing_mode プログラムスライシング後のモードにするかどうかのフラグ　１：有効　０：無効
@return なし
 */
void print_tree_EXPR_SLICING_LIST(EXPR_SLICING_LIST *expr_slicing_list, int program_slicing_mode);

/**
dependencesでインクリメントやデクリメントのフラグが立っている変数を見つけたら、それをtarget_variableに登録する。

@param dependences インクリメントやデクリメントを探す対象の依存変数
@param target_variable 登録先の定義対象変数

@return なし
 */
void registerIncDecVariable(ARRAY_OFFSET_LIST *dependences, ARRAY_OFFSET_LIST *target_variable);
#endif
