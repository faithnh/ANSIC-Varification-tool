/*!
  @brief このファイルはExpression Statement Program Slicing Informationの略である。
  式全般から、プログラムスライシングに関する情報を抽出するための命令が含まれている。

  @file ExpressionStatementPSI.h
  @author faithnh
 */

#ifndef EXPRESSIONSTATEMENTPSI_H_
#define EXPRESSIONSTATEMENTPSI_H_

#include"ProgramSlicingInformation.h"
#include"../ANSICInformation/FunctionInformation.h"
#include"../ANSICInformation/Synbol.h"


/**
式全般のASTノードexpression_statementから、関数に対するプログラムスライシングを抽出し、
プログラムスライシングリストexpr_slicing_listに追加する。

@param expr_slicing_list 追加先のプログラムスライシングリストexpr_slicing_list
@param expression_statement 式全般に関するASTノード
@param parent ノードを追加するときの親ノード
@param vtlist 変数テーブルリスト
@param function_information_list 関数に関する情報リスト
@param ignore_ast_list 重複防止のために無視するノードリスト
@param target_statement expression_statementを指し示すノード

@return なし
 */
void getExpressionStatementPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *expression_statement, EXPR_SLICING *parent,
		VARIABLE_TABLE_LIST *vtlist, FUNCTION_INFORMATION_LIST *function_information_list, ASTPOINTER_LIST *ignore_ast_list,
		AST *target_statement);

/**
call_functionのASTノードから入力関係の関数を探し出し、これらの引数の変数をすべて、対象変数として登録する。
@param root 対象のASTノード
@param target_variable 対象の変数の配列オフセット情報リスト
@param dependences 依存関係の配列オフセット情報リスト
@param function_information_list 関数に関する情報リスト
@param vtlist 検証式の式をマークするための変数リスト
@param ignore_ast_list 配列オフセットリストの重複登録を防止するための、IDENTIFIERを無視するためのASTのアドレスリスト
@param target_statement 検証式の対象となるステートメント

@return なし
 */
void getInputFunctionPSI(AST *root, ARRAY_OFFSET_LIST *target_variable, ARRAY_OFFSET_LIST *dependences, FUNCTION_INFORMATION_LIST *function_information_list,
		VARIABLE_TABLE_LIST *vtlist, ASTPOINTER_LIST *ignore_ast_list, AST *target_statement);

/**
expression_statementおよび、expressionに相当するノードから、対象の変数および依存関係の配列オフセットリストを取得する。

@param root オフセットリストに該当するASTノード
@param target_variable 左辺式のポインタおよび配列のオフセット情報のリスト
@param dependences 右辺式のポインタおよび配列のオフセット情報のリスト
@param function_information_list 関数に関する情報リスト
@param vtlist 検証対象の式をマークするための変数リスト
@param ignore_ast_list ポインタでの位置が検証済みである、IDENTIFIERを無視するためのASTのアドレスリスト
@param target_statement 検証式の対象となるステートメント
@param allow_side_effect 副作用式を許すかどうかのフラグ　１：許す ０：許さない
@return なし
*/
void getASI_ARRAY_OFFSET_LIST(AST *root, ARRAY_OFFSET_LIST *left_array_offset_list, ARRAY_OFFSET_LIST *right_array_offset_list, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
						  ASTPOINTER_LIST *ignore_ast_list, AST *target_statement, int allow_side_effect);

/**
参照先のASTノードが指定した関数呼び出しcall_functionである配列オフセットリストargument_listに対して、
指定した引数の番号argument_numberを以下の形で付加する。

名前　→　名前#引数番号

@param argument_list 付加対象の配列オフセットリスト
@param arg_num 引数
@param call_function 関数呼び出しに対するASTノード

@return なし
 */
void setARGUMENT_NUMBER( ARRAY_OFFSET_LIST *argument_list, int arg_num, AST *call_function);
#endif /* EXPRESSIONSTATEMENTPSI_H_ */
