/*!
  @brief このファイルは、構文解析によって生成された抽象構文木（AST）から、変数・typedefテーブル・構造体テーブルを
  生成させるための命令が含まれている。
  とくに、typedefテーブルの生成は、C言語の構文解析では必須な処理である。

  @file Synbol.h
  @author faithnh

 */
#ifndef C_SYNBOL_HEADDER
#define C_SYNBOL_HEADDER

#include <stdio.h>
#include <cstl/list.h>

#include"../Library/CSTLString.h"
#include "../Library/IdList.h"
#include "AST.h"

/**
型定義に関する情報で、BISONによる構文解析時の型定義の認識に用いられる。
 */
typedef struct typedef_table {
	CSTLString *target_type;	///対象の型定義
	CSTLString *change_type;	///型定義で使用する型名
} TYPEDEF_TABLE;

/**
プログラム中の変数に関する情報であり、検証式生成時に変数を識別するのに用いられる。
 */
typedef struct variable_table {
	int enable_start;					///この変数が有効である開始の行数
	int enable_end;						///この変数が有効である終了の行数
	AST *declaration_location_address;	///この変数の宣言をしているASTノードへのアドレス
	int block_level;					///この変数が宣言しているブロックレベル(グローバル変数なら０、関数内のローカル変数なら１となる）
	int block_id;						///この変数が宣言している各々のブロックの識別子
	IDLIST *idlist;						///この変数が宣言しているブロックレベルおよび識別子の両方に関する情報で、変数スコープを識別するのに使用される。
	CSTLString *type;					///この変数の型
	CSTLString *variable_name;			///この変数の名前
	AST *initiarizer;					///初期定義式に対するASTノードへのアドレス
} VARIABLE_TABLE;

CSTL_LIST_INTERFACE(VARIABLE_TABLE_LIST, VARIABLE_TABLE);

/**
構造体に関する情報であり、プログラム中の構造体の識別するのに用いられる。
 */
typedef struct struct_table{
	int line;				///行数
	CSTLString *type;		///構造体のタイプ union:共同体 struct:構造体
	CSTLString *struct_name;///構造体の名前
	VARIABLE_TABLE_LIST *member_list;	///構造体のメンバに関する変数情報
} STRUCT_TABLE;

CSTL_LIST_INTERFACE(TYPEDEF_TABLE_LIST, TYPEDEF_TABLE);
CSTL_LIST_INTERFACE(STRUCT_TABLE_LIST, STRUCT_TABLE);
/**
新しいtypedefテーブルのデータを生成させる。
@param target_type typedefの対象の型
@param change_type typedefで割り当てた後の新しい型名
@return 新しく生成されたtypedefテーブルのデータへのアドレスが返される。
*/
TYPEDEF_TABLE *new_TYPEDEF_TABLE(CSTLString *target_type, CSTLString *change_type);
/**
新しい変数テーブルのデータを生成させる。
@param enable_start この変数の有効範囲の始まりの行数
@param enable_end この変数の有効範囲の終わりの行数
@param declaration_location_address この変数を宣言した場所を示すASTのアドレス
@param block_level この変数のブロックレベル（グローバル変数なら０とし、関数の中での定義なら１、その関数内のfor文などのブロック文ないでの宣言なら２とする）
@param block_id ブロックごとのID（基本的には0から始り、ブロックレベル２が２回目にくると、１となる）
@param idlist ブロックごとのID（これは変数スコープを識別するために使用する）
@param type 型名
@param variable_name 変数名
@param initializer 初期定義式へのASTノード

@return 新しく生成された変数テーブルのデータへのアドレスが返される。
*/
VARIABLE_TABLE *new_VARIABLE_TABLE(int enable_start, int enable_end, AST* declaration_location_address,
								   int block_level ,int block_id, IDLIST *idlist, CSTLString *type, CSTLString *variable_name, AST *initializer);

/**
新しい構造体テーブルのデータを生成させる(char文字列対応)。
@param line 行数
@param type 型名(structかunionのいずれか）
@param struct_name 構造体の名前
@param member_list メンバリスト(変数テーブルより）
@return 新しく生成された構造体テーブルのデータへのアドレスが返される。
*/
STRUCT_TABLE *new_STRUCT_TABLE_with_char(int line, char *type, char *struct_name, VARIABLE_TABLE_LIST *member_list);

/**
新しいtypedefテーブルのデータを生成させる(char文字列対応)。
@param target_type typedefの対象の型
@param change_type typedefで割り当てた後の新しい型名
@return 新しく生成されたtypedefテーブルのデータへのアドレスが返される。
*/
TYPEDEF_TABLE *new_TYPEDEF_TABLE_with_char(char *target_type, char *change_type);
/**
新しい変数テーブルのデータを生成させる(char文字列対応)。
@param enable_start この変数の有効範囲の始まりの行数
@param enable_end この変数の有効範囲の終わりの行数
@param declaration_location_address この変数を宣言した場所を示すASTのアドレス
@param block_level この変数のブロックレベル（グローバル変数なら０とし、関数の中での定義なら１、その関数内のfor文などのブロック文ないでの宣言なら２とする）
@param block_id ブロックごとのID（基本的には0から始り、ブロックレベル２が２回目にくると、１となる）
@param idlist ブロックごとのID（これは変数スコープを識別するために使用する）
@param type 型名
@param variable_name 変数名
@param initializer 初期定義式へのASTノード

@return 新しく生成された変数テーブルのデータへのアドレスが返される。
*/
VARIABLE_TABLE *new_VARIABLE_TABLE_with_char(int enable_start, int enable_end, AST* declaration_location_address,
								   int block_level ,int block_id,IDLIST *idlist, char *type, char *variable_name, AST *initializer);

/**
新しい構造体テーブルのデータを生成させる。
@param line 行数
@param type 型名(structかunionのいずれか）
@param struct_name 構造体の名前
@param member_list メンバリスト(変数テーブルより）
@return 新しく生成された構造体テーブルのデータへのアドレスが返される。
*/
STRUCT_TABLE *new_STRUCT_TABLE(int line, CSTLString *type, CSTLString *struct_name, VARIABLE_TABLE_LIST *member_list);

/**
指定したASTノードから参照し、もしtypedef宣言の場合は、typedefテーブルに入れる。
@param typedef_table_list typedefテーブル
@param typelist 型リストへのASTノード
@param identifier 識別へのASTノード
@return なし
*/
void getTYPEDEF_TABLE_DATA(TYPEDEF_TABLE_LIST *typedef_table_list, AST *typelist, AST *identifier);

/**
指定したtypedefテーブルのリストから参照し、指定されたトークンに一致するようなtypedefテーブルデータが存在するかどうか調べる。
もし、見つければ、内容が指定されたトークンで、名前がTYPE_NAMEであるASTノードを生成し、それへのアドレスを返す。
@param typedef_table_list 指定したtypedefテーブルのリスト
@param token 指定されたトークン
@return 生成されたASTノードへのアドレスを返す。
*/
AST *getTYPEDEFfromAST(TYPEDEF_TABLE_LIST *typedef_table_list, char *token, int line);
/**
typedefテーブルのリストに登録されているものを、次のような形式で出力させる。

target_type change_type

@param typedef_table_list 出力対象のtypedefテーブルのリスト
@return なし
*/
void printTYPEDEF_TABLE_LIST(TYPEDEF_TABLE_LIST *typedef_table_list);

/** 指定されたASTノードから、構造体テーブルリストに構造体データを登録させる。
@param struct_table_list 登録先の構造体テーブルリスト
@param ast_data 指定されたASTノード
@return なし

*/
void getSTRUCT_TABLE_DATA(STRUCT_TABLE_LIST *struct_table_list, AST *ast_data);

/** 構造体テーブルリストに同じ定義がないかどうかを調べる。
@param struct_table_list 検索対象の構造体テーブルリスト
@param target 検索する文字列
@return 見つけられたら、１を返し、そうでなければ０を返す。
*/
int find_STRUCT_TABLE_DATA(STRUCT_TABLE_LIST *struct_table_list, CSTLString *target);

/** 指定されたASTノードから、構造体データを作成させ、構造体テーブルのリストへ登録させる。
@param ast_data 指定されたASTノード
@param struct_table_data 登録先の構造体テーブルリスト
@return なし

*/
void getSTRUCT_DATA(AST *ast_data, STRUCT_TABLE_LIST *struct_table_data);

/** 指定されたASTノードから、メンバリストを生成する。
@param member_list 登録対象のメンバリスト
@param ast_data 指定されたASTノード
@return 作成された構造体データへのアドレスを返却する

*/
void getMemberList(VARIABLE_TABLE_LIST *member_list, AST *ast_data);

/** 指定されたASTノードから、declaratorを探し、それを見つけたら指定した型の変数として変数リストに登録する。
@param type 指定した型
@param ast_data 指定されたASTノード
@param member_list 登録先の変数リスト
@param enable_start 変数スコープの有効範囲の開始
@param enable_end 変数スコープの有効範囲の終わり
@param block_level この変数のブロックレベル
@param block_id ブロックを識別するための識別番号
@param declaration_location_address この宣言自体のASTへのアドレス(検証式の生成に必要)

@return なし
*/
void getDeclaratorFromAST(char const *type, AST *ast_data, VARIABLE_TABLE_LIST *member_list,
						  int enable_start, int enable_end ,int block_level, int block_id, AST* declaration_location_address);

/**
構造体テーブルのリストの内容を出力させる。
@param struct_table_list 出力対象の構造体テーブルのリスト
@return なし

*/
void printSTRUCT_TABLE_LIST(STRUCT_TABLE_LIST *struct_table_list);

/**
対象のASTノードから変数テーブルのリストを登録する。
@param variable_table_list 変数テーブルのリスト
@param ast_data 対象のASTノード

@return なし
*/
void getVARIABLE_TABLE_LIST(VARIABLE_TABLE_LIST *variable_table_list, AST *ast_data);

/**
関数のパラメータリストを示すASTノードから、parameter_declarationを見つけ、そこから変数テーブルのリストに登録させる。
@param variable_table_list 変数テーブルのリスト
@param ast_data 対象のASTノード
@param enable_start 有効範囲の開始を示すASTノードのアドレス
@param enable_end 有効範囲の終了を示すASTノードのアドレス
@return なし
*/
void getParameterData(VARIABLE_TABLE_LIST *variable_table_list, AST *ast_data, AST *enable_start, AST *enable_end);

/**
対象のASTノードから関数を探し、関数内の引数を変数テーブルのリストに登録する。
@param variable_table_list 変数テーブルのリスト
@param ast_data 対象のASTノード
@return なし
*/
void getParameterVARIABLE_TABLE_LIST(VARIABLE_TABLE_LIST *variable_table_list, AST *ast_data);
/**
変数テーブルのリストの内容を出力させる。
@param variable_table_list 出力対象の変数テーブルのリスト
@return なし

*/
void printVARIABLE_TABLE_LIST(VARIABLE_TABLE_LIST *variable_table_list);

/**
変数テーブルから、ポインタの次元および配列の次元を取得する。
@param variable_table_data 変数テーブルのリスト
@param output_pointer_level 出力されるポインタレベル
@param output_array_level 出力される配列レベル
@return なし
*/
void getPointerLevelAndArrayLevelFromVARIABLE_TABLE(VARIABLE_TABLE *variable_table_data, int *output_pointer_level, int *output_array_level);

/**
対象の識別子のポインタの次元および配列の次元を取得する。
@param target_identifier 対象の識別子
@param output_pointer_level 出力されるポインタレベル
@param output_array_level 出力される配列レベル
@return なし
*/
void getPointerLevelAndArrayLevel(CSTLString *target_identifier, int *output_pointer_level, int *output_array_level);


/**
変数テーブルリストvariable_table_listから、指定した変数スコープのIDLIST target_idlistとtarget_stringに該当ような変数テーブルへのアドレスを返す。

@param target_idlist 指定した変数スコープのIDLIST
@param target_string 対象の変数名
@param variable_table_list 変数テーブルリスト

@return 上記の処理から見つけた変数テーブルへのアドレスを返す。見つからなければNULLを返す。
*/
VARIABLE_TABLE *searchVARIABLE_TABLE_LIST(IDLIST *target_idlist, CSTLString *target_string, VARIABLE_TABLE_LIST* variable_table_list);

/**
変数名から配列およびポインタを示す記号を全て削除する。
@param target 変更対象の変数名
@return なし
*/
void deletePointerAndArraySynbol(CSTLString *target);

/**
変数名からポインタを示す記号のみ全て削除する。
@param target 変更対象の変数名
@return なし
*/
void deletePointer(CSTLString *target);

/**
変数情報から型名を含んだものを文字列で出力させる
@param variable_name 変数名
@param variable_table 対象の変数情報
@return 取得した文字列を返す
 */
CSTLString *getTypeOfVariable(CSTLString *variable_name , VARIABLE_TABLE *variable_table);
#endif

