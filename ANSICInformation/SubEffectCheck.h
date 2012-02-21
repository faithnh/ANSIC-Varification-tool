/*!
  @brief このファイルには副作用式のチェックする関数や代入式のタイプを求める命令が含まれている。

  @file SubEffectCheck.h
  @author faithnh
 */
#ifndef SUBEFFECTCHECK_HEADDER
#define SUBEFFECTCHECK_HEADDER

#include"AST.h"
/**
指定されたASTノードnodeから、副作用式(インクリメント式・デクリメント式・代入式)が含まれているかどうかチェックする。

@param node 対象のASTノード

@return 含まれていた式がインクリメント式の場合１、デクリメント式の場合２、代入式の場合３とする。含まれていない場合は０を返す。
 */

int checkContainSubEffectStatement(AST *node);

/**
代入式のタイプを出力させる。

@param assignment_expression_list 代入式に関するASTノードのリスト

@return 代入式のタイプに応じた値を返却する。 0:=,1:+=,2:-=,3:*=,4:/=,5:%=,6:<<=,7:>>=,8:&=,9:|=,10:^=
 */
int getAssignment_TYPE(AST *assignment_expression_list);
#endif
