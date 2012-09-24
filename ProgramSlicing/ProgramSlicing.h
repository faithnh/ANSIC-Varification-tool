/*!
  @brief このファイルはプログラムスライシングを行うための命令が含まれている。
  指定した識別子名および行数を入れることで、それに基づいてプログラムスライシングを行う。
  @file ProgramSlicing.h
  @author faithnh
 */
#ifndef PROGRAM_SLICING_HEADDER
#define PROGRAM_SLICING_HEADDER

#include"../ANSICInformation/AST.h"
#include"../ANSICInformation/PointerArrayControl.h"
#include"../ANSICInformation/FunctionInformation.h"
#include"../ANSICInformation/Synbol.h"

#include"ProgramSlicingInformation.h"
#include<cstl/list.h>

/**
指定したプログラムＡＳＴノードから次のようなノードを取得し、
そこからスライシングを行うための構造体リストexpr_slicing_listを生成する。
function_definition_type_a、function_definition_type_b、
expression_statement、declaration_with_init、if_statement、ifelse_statement、switch_statement、while_statement、
dowhile_statement、for_statement_type_a、for_statement_type_b、for_statement_type_c、for_statement_type_d、
goto_statement、continue_statement、break_statement、return_statement、return_expr_statement
goto_labeled_statement、case_labeled_statement、default_labeled_statement

@param root 指定したプログラムＡＳＴノード
@param expr_slicing_list スライシングを行うための構造体
@param parent 親のスライシングデータ
@param vtlist 変数テーブルリスト
@param function_information_list 関数に関する情報のリスト

@return なし
*/
void *createStatementNodeList(AST *root, EXPR_SLICING_LIST *expr_slicing_list, EXPR_SLICING *parent,
		VARIABLE_TABLE_LIST *vtlist, FUNCTION_INFORMATION_LIST *function_information_list);

/**
指定した対象の命令とグローバル変数に関してデータ依存関係があるかどうか調べる。
存在すれば、グローバル変数宣言に対して、データ依存関係として結びつける。

@param expr_slicing 指定した対象の命令
@param program_expr_slicing_list プログラム全体のスライシングリスト

@return なし
 */

void createDD_list_in_global(EXPR_SLICING *expr_slicing, EXPR_SLICING_LIST *program_expr_slicing_list);

/**
指定した対象の命令に対して、データ依存関係の命令を探し、その命令を結びつける。

@param expr_slicing 指定した対象の命令

@return なし
 */
void createDD_list(EXPR_SLICING *expr_slicing);
/**
プログラムスライシングリスト中のすべての命令に対し、データ依存関係の命令を探し、その命令を結びつける。

@param expr_slicing_list 指定した対象のプログラムスライシングリスト
@param function_information_list 関数に関する情報リスト
@param program_expr_slicing_list プログラム全体へのスライシングリスト
@return なし
 */
void createDD_listAll(EXPR_SLICING_LIST *expr_slicing_list, FUNCTION_INFORMATION_LIST *function_information_list,
		EXPR_SLICING_LIST *program_expr_slicing_list);

/**
関数呼び出しから、呼び出している関数へのデータ依存関係を生成する。

@param expr_slicing 関数呼び出しが含まれている処理名
@param expr_slicing_list プログラム全体のプログラムスライシングリスト
@param function_information_list 関数に関する情報リスト

@return なし
 */
void createDD_list_in_Function(EXPR_SLICING *expr_slicing, EXPR_SLICING_LIST *expr_slicing_list,
		FUNCTION_INFORMATION_LIST *function_information_list);

/**
関数へのスライシング情報に対して、仮引数名が依存関係として用いている命令を探し、それを指定したプログラムスライシング
のデータ依存関係として追加する。

@param expr_slicing 関数呼び出しのプログラムスライシング
@param argument_name 仮引数名
@param function_definition_expr_slicing 関数宣言へのプログラムスライシング

@return なし
 */

void createDD_list_in_argument(EXPR_SLICING *expr_slicing, CSTLString *argument_name,
		EXPR_SLICING *function_definition_expr_slicing);

/**
指定した識別子の命令に対してスタティックスライシング処理を行う。

@param expr_slicing 指定した命令に対するプログラムスライシング情報

@return なし

*/
void staticSlicing(EXPR_SLICING *expr_slicing);

/**
指定した命令へのASTノードに基づいてexpr_slicing_listに対してスタティックスライシング処理を行う。

@param inst_ast 指定した命令へのASTノード
@param expr_slicing_list スタティックスライシング処理を行うための構造体リスト

@return 成功したかどうかを返却する。　１：成功　０：失敗

*/
int startStaticSlicing(AST *inst_ast, EXPR_SLICING_LIST *expr_slicing_list);

#endif
