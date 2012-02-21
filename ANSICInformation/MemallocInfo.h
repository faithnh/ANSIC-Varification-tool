/*!
  @brief このファイルはメモリ確保関係の関数から、メモリ確保関係に関する情報を格納するための命令が含まれている。
  具体的には、C言語プログラム上にある、malloc・calloc・reallocなどといった関数から、確保しているsizeofの型・realloc使用時で対象としている変数・確保しているサイズを取得する。

  @file MemallocInfo.h
  @author faithnh

 */
#ifndef MEMALLOC_INFO_HEADDER
#define MEMALLOC_INFO_HEADDER

#include"PointerArrayControl.h"
#include"AST.h"
#include"Synbol.h"

/**
メモリ割り当てに関する情報を格納するための構造体。
*/
typedef struct memory_allocation_info{
	CSTLString *sizeof_type;	///sizeofの型名
	ARRAY_OFFSET_LIST *realloc_target;	///realloc時のターゲット変数の配列オフセットリスト
	CSTLString *size;			///malloc時のサイズ
} MEMALLOC_INFO;

/**
メモリ割り当てに関する情報を格納するための構造体のデータを生成させる。
@param sizeof_type		sizeofの型名
@param realloc_target	realloc時のターゲットタイプ
@param size				malloc時のサイズ

@return メモリ割り当てに関する情報を格納するための構造体へのアドレスを返す。
*/
MEMALLOC_INFO *new_MEMALLOC_INFO_char(char *sizeof_type, ARRAY_OFFSET_LIST *realloc_target, char *size);

/**
メモリ割り当てに関する情報を格納するための構造体のデータを生成させる。
@param sizeof_type		sizeofの型名
@param realloc_target	realloc時のターゲットタイプ
@param size				malloc時のサイズ

@return メモリ割り当てに関する情報を格納するための構造体へのアドレスを返す。
*/
MEMALLOC_INFO *new_MEMALLOC_INFO(CSTLString *sizeof_type, ARRAY_OFFSET_LIST *realloc_target, CSTLString *size);

/**
指定されたASTノードからメモリ確保関係の関数に関する情報を取得する。
@param root 指定されたASTノード
@param vtlist reallocでreallocのターゲット情報のオフセット情報を取得するのに必要なプログラムの変数リスト
@return メモリ確保関係の構造体へのアドレスを返す。
*/
MEMALLOC_INFO *memoryAllocationAnarysis(AST *root, VARIABLE_TABLE_LIST *vtlist);

/**
malloc関数に関する情報を取得する
@param root
@param sizeof_type sizeofでの型
@param constant sizeof以外での式（すなわち確保している型に対するサイズに相当する）

@return なし
*/
void getMallocInformation(AST *root, CSTLString *sizeof_type, CSTLString *constant);

/**
calloc関数に関する情報を取得する。
@param root
@param sizeof_type sizeofでの型
@param constant sizeof以外での式（すなわち確保している型に対するサイズに相当する）

@return なし
*/
void getCallocInformation(AST *root, CSTLString *sizeof_type, CSTLString *constant);

/**
realloc関数に関する情報を取得する。
@param root 対象のASTノード
@param vtlist 対象のプログラムの変数リスト
@param sizeof_type sizeofでの型
@param constant sizeof以外での式（すなわち確保している型に対するサイズに相当する）
@param realloc_target reallocが対象とするオフセット情報

@return なし
*/
void getReallocInformation(AST *root,VARIABLE_TABLE_LIST *vtlist, CSTLString *sizeof_type, CSTLString *constant, ARRAY_OFFSET_LIST *realloc_target);

/**
指定した式のASTに対して、sizeofを探索し、その型名をsizeof_typeで取得する。もし、式に異なる２種類のsizeof定義があれば、探索フラグは失敗する。
また、見つからなければ、sizeof_typeは何も指定していないままの状態である。
@param sizeof_type 出力するsizeofの型名
@param root 探索対象の式へのASTノード
@return なし
*/
int searchSizeof(CSTLString *sizeof_type, AST *root);

/**
mallocなどの関数内の式から、確保したサイズを示す式を取得する。これは、sizeof(型)を１に書き直しながら、式を出力させることで行っている。

@param constant 取得するsizeof以外での式（すなわち確保している型に対するサイズに相当する）
@param root mallocなどの関数内の式へのASTノード
@return なし
*/
void getMallocMaxsize(CSTLString *constant,AST *root);


/*
指定したメモリ確保情報memalloc_infoの内容を出力する。

@param memalloc_info 出力対象のメモリ確保情報

@return なし
*/
void printMEMALLOC_INFO(MEMALLOC_INFO *memalloc_info);


#endif
