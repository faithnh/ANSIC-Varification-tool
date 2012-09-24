/*!
  @brief このファイルはSwitch Statement Program Slicing Informationの略である。
  switch文から、プログラムスライシングに関する情報を抽出するための命令が含まれている。

  @file SwitchStatementPSI.h
  @author faithnh
 */

#ifndef SWITCHSTATEMENTPSI_H_
#define SWITCHSTATEMENTPSI_H_

#include"ProgramSlicingInformation.h"
#include"../ANSICInformation/FunctionInformation.h"
#include"../ANSICInformation/Synbol.h"

/**
switch文のASTノードswitch_statementから、関数に対するプログラムスライシングを抽出し、
プログラムスライシングリストexpr_slicing_listに追加する。

@param expr_slicing_list 追加先のプログラムスライシングリストexpr_slicing_list
@param switch_statement switch文に関するASTノード
@param parent ノードを追加するときの親ノード
@param vtlist 変数テーブルリスト
@param function_information_list 関数に関する情報リスト
@param ignore_ast_list 重複防止のために無視するノードリスト

@return なし
 */
EXPR_SLICING *getSwicthStatementPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *switch_statement, EXPR_SLICING *parent,
		VARIABLE_TABLE_LIST *vtlist, FUNCTION_INFORMATION_LIST *function_information_list, ASTPOINTER_LIST *ignore_ast_list);

#endif /* IFSTATEMENTPSI_H_ */
