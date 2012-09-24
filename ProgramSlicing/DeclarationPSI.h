/*!
  @brief このファイルはDeclaration Statement Program Slicing Informationの略である。
  宣言式から、プログラムスライシングに関する情報を抽出するための命令が含まれている。

  @file DeclarationPSI.h
  @author faithnh
 */

#ifndef DECLARATIONPSI_H_
#define DECLARATIONPSI_H_

#include"ProgramSlicingInformation.h"
#include"../ANSICInformation/FunctionInformation.h"
#include"../ANSICInformation/Synbol.h"

/**
宣言式のASTノードdeclarationから、関数に対するプログラムスライシングを抽出し、
プログラムスライシングリストexpr_slicing_listに追加する。

@param expr_slicing_list 追加先のプログラムスライシングリストexpr_slicing_list
@param declaration 式全般に関するASTノード
@param parent ノードを追加するときの親ノード
@param vtlist 変数テーブルリスト
@param function_information_list 関数に関する情報リスト
@param ignore_ast_list 重複防止のために無視するノードリスト
@param target_statement expression_statementを指し示すノード
@return なし
 */
void getDeclarationtPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *declaration, EXPR_SLICING *parent,
		VARIABLE_TABLE_LIST *vtlist, FUNCTION_INFORMATION_LIST *function_information_list, ASTPOINTER_LIST *ignore_ast_list,
		AST *target_statement);

#endif /* DECLARATIONPSI_H_ */
