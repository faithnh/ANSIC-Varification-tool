/*!
  @brief このファイルは Jump Statement Program Slicing Informationの略である。
  GOTO、continue、break文から、プログラムスライシングに関する情報を抽出するための命令が含まれている。

  @file JumpStatementPSI.h
  @author faithnh
 */

#ifndef JUMPSTATEMENTPSI_H_
#define JUMPSTATEMENTPSI_H_

#include"ProgramSlicingInformation.h"
#include"../ANSICInformation/FunctionInformation.h"
#include"../ANSICInformation/Synbol.h"

/**
GOTO、continue、break文のASTノードexpression_statementから、関数に対するプログラムスライシングを抽出し、
プログラムスライシングリストexpr_slicing_listに追加する。

@param expr_slicing_list 追加先のプログラムスライシングリストexpr_slicing_list
@param jump_statement GOTO、continue、break文に関するASTノード
@param parent ノードを追加するときの親ノード

@return なし
 */
void getJumpStatementPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *jump_statement, EXPR_SLICING *parent);

#endif /* GOTOSTATEMENTPSI_H_ */
