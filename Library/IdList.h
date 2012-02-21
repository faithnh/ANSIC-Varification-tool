/*!
  @brief このファイルは、この変数はC言語プログラム上のどのブロックに宣言しているかどうかを確認するための情報を生成するための命令が含まれている。

  @file IdList.h
  @author faithnh

 */

#ifndef IDLIST_HEADDER
#define IDLIST_HEADDER

#include "Stack_int.h"
#include <cstl/list.h>

CSTL_LIST_INTERFACE(IDLIST, int)

/**
二つのIDLIST target1,target2を比較し、次の状態であれば、１を返す。そうでなければ０を返す。
target2の一番最初のリストの値が0である。
target2のリスト内の値が全て、target1のリスト内の値と一致する場合

@param target1 比較対象のIDLIST１
@param target2 比較対象のIDLIST２

@return 比較して上記道理になると１を返し、そうでなければ、０を返す。
*/
int IDLIST_compare_with(IDLIST *target1, IDLIST *target2);

/**
整数スタックの内容sourceを入れたい対象のIDLISTdestへ入れる。

@param dest 対象のIDLIST
@param source 入れる整数スタック内容
@param num 整数スタックに入れる数

@return なし
*/
void SET_STACK_INTToIDLIST(IDLIST *dest, STACK_INT *source, int num);

/**
IDLISTの内容を出力する。

@param idlist 出力対象のIDLIST
@param new_line_flag 改行するかどうかのフラグ　1：改行する　０：改行しない
@return なし
*/
void printIDLIST(IDLIST *idlist,int new_line_flag);

#endif
