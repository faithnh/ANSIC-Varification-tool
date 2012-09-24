/*!
  @brief このファイルは整数スタックに関する操作をするための命令が含まれている。
  このファイルで使用される主な用途として、C言語ソースファイルにおけるブロックレベルを設定するのに使用される。
  @file Stack_int.h
  @author faithnh
 */


#ifndef STACK_INT_HEADDER
#define STACK_INT_HEADDER

#include <cstl/vector.h>

CSTL_VECTOR_INTERFACE(STACK_INT, int)

/**
対象の整数スタックstack_intから、指定したインデックスの内容を出力する。インデックスが範囲外である場合は、そのサイズ分まで確保し、0を返す。

@param stack_int 対象の整数スタック
@param index 対象の座標

@return 指定したインデックスでの整数スタックの値を出力する。インデックスが範囲外である場合は0を返す。
*/
int STACK_INT_at_and_alloc(STACK_INT *stack_int, int index);

/**
対象の整数スタックstack_intから、指定したインデックスの内容をインクリメントする。
@param stack_int 対象の整数スタック
@param index 指定したインデックス
@return インクリメントに成功したかどうかを示す。成功した場合は１、そうでない場合は０を返す。
*/
int STACK_INT_inclement_at(STACK_INT *stack_int, int index);

#endif
