/*!
  @brief このファイルは、ANSICのソースコードを省略させるためのマクロ文が含まれている

  @file ANSIC_CODE.h
  @author faithnh

 */

#ifndef ANSIC_CODE_H_
#define ANSIC_CODE_H_

#include"AST.h"
/**
対象のASTノードの１番目の子ノードの取得する。

@param target 対象のASTノード

@return 対象のASTノードの１番目の子ノードが返される。
 */
inline AST *ASTLIST_ITERATOR_1(AST *target);
/**
対象のASTノードの２番目の子ノードの取得する。

@param target 対象のASTノード

@return 対象のASTノードの２番目の子ノードが返される。
 */
inline AST *ASTLIST_ITERATOR_2(AST *target);
/**
対象のASTノードの３番目の子ノードの取得する。

@param target 対象のASTノード

@return 対象のASTノードの３番目の子ノードが返される。
 */
inline AST *ASTLIST_ITERATOR_3(AST *target);
/**
対象のASTノードの４番目の子ノードの取得する。

@param target 対象のASTノード

@return 対象のASTノードの４番目の子ノードが返される。
 */
inline AST *ASTLIST_ITERATOR_4(AST *target);
/**
対象のASTノードの５番目の子ノードの取得する。

@param target 対象のASTノード

@return 対象のASTノードの５番目の子ノードが返される。
 */
inline AST *ASTLIST_ITERATOR_5(AST *target);
/**
対象のASTノードの６番目の子ノードの取得する。

@param target 対象のASTノード

@return 対象のASTノードの６番目の子ノードが返される。
 */
inline AST *ASTLIST_ITERATOR_6(AST *target);
/**
対象のASTノードの７番目の子ノードの取得する。

@param target 対象のASTノード

@return 対象のASTノードの７番目の子ノードが返される。
 */
inline AST *ASTLIST_ITERATOR_7(AST *target);

#endif /* ANSIC_CODE_H_ */
