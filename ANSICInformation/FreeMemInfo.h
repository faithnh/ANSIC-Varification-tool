/*!
  @brief このファイルは、メモリ解放関係の関数から、メモリ解放関係の情報を取得する命令が含まれている。
  具体的には、C言語プログラム上にあるfree関数から、どの変数が解放されているかどうかについて取得する。

  @file FreeMemInfo.h
  @author faithnh

 */

 #ifndef FREEMEMINFO_HEADDER
 #define FREEMEMINFO_HEADDER

 #include "PointerArrayControl.h"
 #include "FunctionInformation.h"

/**
メモリ確保関係に関係する変数が含まれる。これは、メモリ解放関数の挙動に合わせて検証式を追加するために用いる。
 */
 typedef struct freemem_info{
	ARRAY_OFFSET_LIST * free_variable; ///解放先の変数に関するオフセットリスト
 } FREEMEMINFO;

 /**
 新しいメモリ解放関係の情報を生成する。

 @param free_variable 新しい解放先の変数に関するオフセットリスト

 @return 新しく生成されたメモリ解放関係の情報へのアドレスを返す。
 */
 FREEMEMINFO * new_FREEMEMINFO(ARRAY_OFFSET_LIST *free_variable);


 /**
 対象の関数へのASTノードからfree関数を見つけ、それに関する情報を取得する。

 @param freememinfo 取得先のメモリ解放関係の情報
 @param call_function 対象の関数へのASTノード
 @param function_information_list 関数に関する情報のリスト
 @param vtlist 変数テーブルの情報
 @param target_statement 対象の関数が位置している式へのASTノード

 @return なし
 */

 void getFreememInfo(FREEMEMINFO **freememinfo, AST *call_function, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist, AST *target_statement);

 /**
 指定したメモリ解放関係の情報を出力する。

 @param freememinfo 出力するメモリ解放関係の情報

 @return なし
 */
 void printFREEMEMINFO(FREEMEMINFO *freememinfo);

 #endif
