/*!
  @brief これはリターン命令に関する情報を取得するための命令が含まれている。

  @file Return_Info.h
  @author faithnh
 */
#ifndef RETURN_INFO_HEADDER
#define RETURN_INFO_HEADDER

#include"PointerArrayControl.h"

/**
リターン命令に関する情報が含まれている。
*/
typedef struct return_info{
	AST *target_expression; ///リターン命令自体へのノードへのアドレス
	ARRAY_OFFSET_LIST *return_array_offset_list; ///リターン命令で表記された式の配列オフセットリスト
} RETURN_INFO;

/**
リターン命令に関する情報を生成させる。
@param target_expression リターン命令自体へのノードへのアドレス
@param return_array_offset_list リターン命令で表記された式の配列オフセットリスト

@return 生成されたリターン命令に関する情報へのアドレスを返す。
*/
RETURN_INFO *new_RETURN_INFO(AST *target_expression, ARRAY_OFFSET_LIST *return_array_offset_list);

#endif
