/*!
  @brief このファイルは構文解析を通せるように、GccでC言語にプリプロセス（前処理）をさせるための命令が含まれている。
  このファイルでできることとしては、#includeをコメントアウトすることで省いて、プリプロセスを掛けることができる。
  @file PreProcess.h
  @author faithnh
 */

#ifndef PRE_PROCESS_HEADDER
#define PRE_PROCESS_HEADDER

#include<cstl/list.h>
#include"../Library/CSTLString.h"
/**
インクルードファイルに関する情報が格納される。これは、検証式付加時にインクルードファイルを付加するのに使用する。
*/
typedef struct include_data{
	CSTLString *include_data;	///includeファイルの名前
	int line;					///その行数
} INCLUDE_DATA;

CSTL_LIST_INTERFACE(INCLUDE_LIST, INCLUDE_DATA)


/**
新しいインクルードファイルを生成する。
@param include_data includeファイルの名前
@param line その行数
*/
INCLUDE_DATA *new_INCLUDE_DATA(CSTLString *include_data, int line);

/**
実行させたいソースにプリプロセッサをかける。プリプロセッサのかけたファイルはファイル名_out_pre.cとして出力される。
@param source_file_name 実行させたいソースファイル名

@return 成功したかどうかを示す　成功した場合は１をかえし、そうでない場合は０を返す。
*/
int preProcesser(char *source_file_name);

/**
"#include"にコメントをかけておく。コメントアウトをかけた結果はファイル名_out.cとして出力される。
@param source_file_name 対象のソースファイル名

@return 成功したかどうかを示す　成功した場合は１をかえし、そうでない場合は０を返す。
*/
int includeComment(char *source_file_name);

/**
プログラムの始まりを示す位置まですべて削除する。
@param source_file_name 対象のソースファイル名

@return 成功したかどうかを示す　成功した場合は１をかえし、そうでない場合は０を返す。
*/
int adjustProgramStart(char *source_file_name);

/**
"#include"にコメントをかけたもののみを取り出し、取りだしたものをインクルードファイルのリストinclude_listにいれる。
@param file_name 開くファイル名
@param include_list インクルードリスト

@return なし
*/
void readIncludeDataFromFile(char *file_name, INCLUDE_LIST *include_list);

/**
インクルードリストを基に、対象のファイルにインクルードを追加する。
@param file_name 開くファイル名
@param include_list インクルードリスト

@return なし
*/
void addIncludeDataFromFile(char *file_name, INCLUDE_LIST *include_list);

#endif
