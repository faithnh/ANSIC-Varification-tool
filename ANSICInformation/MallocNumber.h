/*!
  @brief これはどのmalloc用識別番号を付加する関数を生成するための命令が含まれている。

  @file MallocNumber.h
  @author faithnh
 */
#ifndef MALLOC_NUMBER_HEADDER
#define MALLOC_NUMBER_HEADDER

#include"../Library/CSTLString.h"
#include"PreProcess.h"
/**
malloc用識別番号付加関数をカレントディレクトリ上に生成させる。
@param target_directory 作成するディレクトリ先

@return なし
*/
void generateMallocNumber(CSTLString *target_directory);

/**
インクルード情報にmalloc用識別番号付加関数が含まれているヘッダーファイルを追加させる。。
@param include_list インクルード情報へのリスト

@return なし
*/
void insertMallocNumberHeadder(INCLUDE_LIST *include_list);
#endif
