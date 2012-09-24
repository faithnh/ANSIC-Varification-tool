/*!
  @brief このファイルはFunction Program Slicing Informationの略である。
  関数定義から、プログラムスライシングに関する情報を抽出するための命令が含まれている。

  @file FunctionPSI.h
  @author faithnh
 */
#ifndef FUNCTION_PS_INFORMATION_HEADDER
#define FUNCTION_PS_INFORMATION_HEADDER

#include"ProgramSlicingInformation.h"

/**
関数定義のASTノードfunction_definitionから、関数に対するプログラムスライシングを抽出し、
プログラムスライシングリストexpr_slicing_listに追加する。

@param expr_slicing_list 追加先のプログラムスライシングリストexpr_slicing_list
@param function_definition 関数定義に関するASTノード
@param parent ノードを追加するときの親ノード

@return 追加した関数のスライシングへのアドレスを返す
 */
EXPR_SLICING *getFunctionPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *function_definition, EXPR_SLICING *parent);

/**
パラメータリストに関するASTノードparameter_nodeから関数定義のプログラムスライシングリストexpr_slicing_listに格納していく

@param expr_slicing 関数定義のプログラムスライシング
@param parameter_node 各パラメータの定義リスト
@param basis_parameter_node パラメータを指すASTノード

@return なし
 */
void getParameterPSI(EXPR_SLICING *expr_slicing, AST *parameter_node, AST *basis_parameter_node);
#endif
