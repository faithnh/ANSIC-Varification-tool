/*!
  @brief これは簡潔化のために変数定義を分割させるためのものである。
　例：int a,b = 1; → int a; int b = 1;
  @file DivitionDeclarator.h
  @author faithnh
 */

#ifndef DIVITIONDECLARATOR_H_
#define DIVITIONDECLARATOR_H_

#include"AST.h"
#include"Synbol.h"
/**
変数定義を分割させた状態で出力させる。
　例：int a,b = 1; → int a; int b = 1;
@param output 出力先のファイル構造体
@param programAST プログラムに対するAST
@param variable_table_list 変数テーブル

@return なし
 */
void OutputSourceAfterDivitionDeclarator(FILE *output, AST *programAST, VARIABLE_TABLE_LIST *variable_table_list);

#endif /* DIVITIONDECLARATOR_H_ */
