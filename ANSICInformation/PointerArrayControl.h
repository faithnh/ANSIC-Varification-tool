/*!
  @brief このファイルは、C言語プログラム上の複雑な配列参照および直接参照による演算を各次元の配列オフセット情報として格納するための命令が含まれている。
  各次元の配列オフセット情報とは各次元において、どの部分を指しているかという式に関する情報のことである。
  @file PointerArrayControl.h
  @author faithnh
 */

#ifndef POINTER_ARRAY_CONTROL_HEADDER
#define POINTER_ARRAY_CONTROL_HEADDER

#include <cstl/list.h>
#include"../Library/CSTLString.h"
#include"AST.h"
#include"Synbol.h"

#include"FunctionInformation.h"

CSTL_LIST_INTERFACE(OFFSET_LIST, char *);

/**
配列やポインタの各次元のオフセット関係を格納するための構造体である。配列オフセットと呼ばれる。
*/
typedef struct array_offset {
	CSTLString *variable_name;				///変数名
	AST *target_statement;					///ターゲットのstatement(ここではexpression_statementなどが入る)
	AST *variable_address;				///この変数名が指しているASTアドレス
	int pointer_level;			///この変数のポインタレベル
	int array_level;			///この変数の配列レベル
	int anpasand_flag;			///この変数はアンパサンドを挟んでいるかどうかのフラグ　１：挟んでいる　０：挟んでいない
	int inc_dec_flag;			///この変数はインクリメントおよびデクリメントが含まれているかどうかのフラグ　０：含んでいない　１：インクリメントが含まれている　２：デクリメントが含まれている
	OFFSET_LIST *offset_list;	///各次元のオフセット
} ARRAY_OFFSET;

CSTL_LIST_INTERFACE(ARRAY_OFFSET_LIST, ARRAY_OFFSET);

CSTL_LIST_INTERFACE(ASTPOINTER_LIST, AST *);

/**
配列やポインタの各次元のオフセット関係を格納するための構造体のデータを生成させる。
@param variable_name 変数名
@param target_statement ターゲットのstatement
@param variable_address この変数名が指しているASTアドレス
@param offset_list 各次元のオフセット
@param pointer_level この変数のポインタレベル
@param array_level この変数の配列レベル
@param anpasand_flag アンパサンドを挟んでいるかどうかのフラグ　１：挟んでいる　０：挟んでいない
@param inc_dec_flag インクリメントおよびデクリメントが含まれているかどうかのフラグ　０：含んでいない　１：インクリメントが含まれている　２：デクリメントが含まれている

@return 配列やポインタの各次元のオフセットに関する構造体へのアドレスを返す
*/
ARRAY_OFFSET *new_ARRAY_OFFSET_char(char *variable_name, AST *target_statement, AST *variable_address,
									OFFSET_LIST *offset_list, int pointer_level, int array_level, int anpasand_flag, int inc_dec_flag);

/**
配列やポインタの各次元のオフセット関係を格納するための構造体のデータを生成させる。
@param variable_name 変数名
@param target_statement ターゲットのstatement
@param variable_address この変数名が指しているASTアドレス
@param offset_list 各次元のオフセット
@param pointer_level この変数のポインタレベル
@param array_level この変数の配列レベル
@param anpasand_flag この変数はアンパサンドを挟んでいるかどうかのフラグ　１：挟んでいる　０：挟んでいない
@param inc_dec_flag インクリメントおよびデクリメントが含まれているかどうかのフラグ　０：含んでいない　１：インクリメントが含まれている　２：デクリメントが含まれている

@return 配列やポインタの各次元のオフセットに関する構造体へのアドレスを返す。
*/
ARRAY_OFFSET *new_ARRAY_OFFSET(	CSTLString *variable_name, AST *target_statement, AST *variable_address,
							   OFFSET_LIST *offset_list, int pointer_level, int array_level, int anpasand_flag, int inc_dec_flag);

/**
任意の文字列を、動的変数としてオフセットリストに追加する。
@param offset_list 対象のオフセットリスト
@param string 任意の文字列

@return なし
 */
void OFFSET_LIST_push_back_alloc(OFFSET_LIST *offset_list, char *string);

/**
ポインタおよび配列変数の各次元のオフセットとなる式を求める。
@param root 左辺値に関するASTノード
@param function_information_list 関数に関する情報リスト
@param vtlist 検証対象の式をマークするための変数リスト
@param offset_level オフセットレベルを計算するためのところ。基本的に０を入力する。１以上入力すれば、それが最下位レベルとなる。
@param ignore_ast_list ポインタでの位置が検証済みである、IDENTIFIERを無視するためのASTのアドレスリスト
@param array_offset ポインタおよび配列のオフセット情報
@param target_statement 検証式の対象となるステートメント
@param anpasand_flag アンパサンドを挟んでいるかどうかのフラグ　１：挟んでいる　0：挟んでいない
@param inc_dec_flag インクリメントおよびデクリメントが含まれているかどうかのフラグ　０：含んでいない　１：インクリメントが含まれている　２：デクリメントが含まれている
@return なし
*/
int getPointerArrayOffset(AST *root, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist, int offset_level,
	ASTPOINTER_LIST *ignore_ast_list, ARRAY_OFFSET **array_offset, AST *target_statement, int anpasand_flag, int inc_dec_flag);

/**
ポインタおよび配列変数の各次元のオフセットリストを取得する。
@param root オフセットリストに該当するASTノード
@param array_offset_list ポインタおよび配列のオフセット情報のリスト
@param function_information_list 関数に関する情報リスト
@param vtlist 検証対象の式をマークするための変数リスト
@param ignore_ast_list ポインタでの位置が検証済みである、IDENTIFIERを無視するためのASTのアドレスリスト
@param target_statement 検証式の対象となるステートメント
@return なし
*/
void getARRAY_OFFSET_LIST(AST *root, ARRAY_OFFSET_LIST *array_offset_list, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
						  ASTPOINTER_LIST *ignore_ast_list, AST *target_statement);
/**
ポインタおよび配列変数の各次元のオフセットリストを取得する。また、無視をする対象のノードを設定可能である。
@param root オフセットリストに該当するASTノード
@param array_offset_list ポインタおよび配列のオフセット情報のリスト
@param function_information_list 関数に関する情報リスト
@param vtlist 検証対象の式をマークするための変数リスト
@param ignore_ast_list ポインタでの位置が検証済みである、IDENTIFIERを無視するためのASTのアドレスリスト
@param target_statement 検証式の対象となるステートメント
@param ignore_ast_name 無視をするＡＳＴ名
@return なし
*/
void get_ARRAY_OFFSET_LISTIgnoreASTNAME(AST *root, ARRAY_OFFSET_LIST *array_offset_list, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
		  ASTPOINTER_LIST *ignore_ast_list, AST *target_statement, CSTLString *ignore_ast_name);
/**
address_refであるノード内を探索し、それに対するアドレス参照や、識別子を探し出し、見つけたら配列オフセットリストarray_offset_listへ入れる。
@param root 右辺式に関するASTノード
@param function_information_list 関数に関する情報のリスト
@param vtlist メモリ確保情報を取得するのに必要なプログラム変数リスト
@param array_offset_list 左辺式上にあるポインタ参照に対するオフセットリスト
@param ignore_ast_list 同じ位置のポインタが来ても無視するためのリスト
@param target_statement この計算式を属しているASTノードへのアドレス（基本的にexpression_statementであるノードが入る）

@return なし
*/
void getArrayOffsetInAnpasandInfo(AST *root,FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
							ARRAY_OFFSET_LIST *array_offset_list, ASTPOINTER_LIST *ignore_ast_list, AST *target_statement);

/**
inc_exprやdec_exprなどのインクリメントやデクリメント式であるノード内を探索し、それに対するアドレス参照や、識別子を探し出し、見つけたら配列オフセットリストarray_offset_listへ入れる。
@param root inc_exprやdec_exprなどのインクリメントやデクリメント式に関するASTノード
@param function_information_list 関数に関する情報のリスト
@param vtlist メモリ確保情報を取得するのに必要なプログラム変数リスト
@param array_offset_list 左辺式上にあるポインタ参照に対するオフセットリスト
@param ignore_ast_list 同じ位置のポインタが来ても無視するためのリスト
@param target_statement この計算式を属しているASTノードへのアドレス（基本的にexpression_statementであるノードが入る）
@param inc_dec_flag インクリメントおよびデクリメントが含まれているかどうかのフラグ　１：インクリメントが含まれている　２：デクリメントが含まれている

@return なし
*/
void getArrayOffsetInIncDecInfo(AST *root, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
								ARRAY_OFFSET_LIST *array_offset_list, ASTPOINTER_LIST *ignore_ast_list, AST *target_statement, int inc_dec_flag);

/**
ポインタのオフセットの検証対象となっている変数を示すASTノードtargetから、間接的にどの関係の中に位置しているかどうかを調べ、そのノードのアドレスoutputとして返す。
このとき、targetより明らかに上位であるASTノードrootを設定しなければならない。
また、outputがminus_exprの場合はそのポインタよりひとつ下が左辺か右辺かどうかを調べるために、
そのポインタの一つ下のノードをoutput2へ代入する。

@param target 検証対象となっている変数
@param root 検証対象のノード
@param output 出力される間接的に関係しているノードへのアドレス
@param output2 outputがminus_exprの場合、minus_exprより1つ下のノードがここに代入される
@return 検索が成功したかどうかのフラグ。成功した場合は１、そうでない場合は０を返す。

@return なし
*/
int getUpperExpressionRelationNode(AST *target, AST *root, AST **output, AST **output2);

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
primary_expressionとして指定したASTノードrootから、その次の下位である次のノード名を探し出し、そのアドレスをoutputへ出力させ、1を返す。

minus_expr, plus_expr, array_access, direct_ref, IDENTIFIER, primary_expression

なお、outputの内容をNULLにすることで、rootより下位のノードからが検索の対象となる。
また、ポインタ計算の関係上、+-演算演算子を示すようなものやCONSTANT(定数）が来た場合のみ、-1を返す。
見つからない場合は0である。

@param root 指定したASTノード
@param output 上記の見つけたノードへのアドレス

@return 上記の条件で値を返却する。

*/
int searchExpressionOrPointeArrayOrIden(AST *root, AST **output);

/**
direct_refとして指定したASTノードrootから、その次の下位である次のノード名を探し出し、そのアドレスをoutputへ出力させ、1を返す。

IDENTIFIER array_access, direct_ref, IDENTIFIER, primary_expression
inc_after_expression, inc_expr, dec_after_expr, inc_expr
assignment_expression

なお、outputの内容をNULLにすることで、rootより下位のノードからが検索の対象となる。
見つからない場合は0である。

@param root 指定したASTノード
@param output 上記の見つけたノードへのアドレス

@return 上記の条件で値を返却する。

*/
int searchPointerAccessOrIdentifierOrPrimary(AST *root, AST **output);

/**
direct_refとして指定したASTノードrootから、以下のノードを探しだし、それをASTリストoutputとして取得する。

IDENTIFIER array_access, direct_ref, IDENTIFIER, primary_expression

なお、outputの内容をNULLにすることで、rootより下位のノードからが検索の対象となる。
見つからない場合は0である。

@param root 指定したASTノード
@param output 上記の見つけたノードへのアドレス
@param getSize 取得した値のサイズを返すための変数。見つからない場合は0にされる。

@return なし
*/
void getPointerAccessOrIdentifierList(AST *root, AST ***output, int *getSize);

/**
識別子の名前を一致する変数を変数リストから探す。このとき、一致する変数を調べたら、ポインタと配列の次元も調べ、オフセットレベル以上であれば、
見つけたことになり、１を返す。そうでなければ、０を返す。また、ignore_ast_listは無視するIDENTIFIERのASTのアドレスリストを見つけるたびに登録
される。もし、ignore_ast_listに登録されているノードなら、それは無視される。また、見つけるのに成功した場合、その該当する変数の配列レベルやポ
インタのレベルも返す。

@param identifier 識別子の名前
@param offset_level オフセットレベル
@param variable_table_list 変数テーブルリスト
@param ignore_ast_list ポインタでの位置が検証済みである、IDENTIFIERを無視するためのASTのアドレスリスト
@param pointer_level 変数リストから見つけた変数のポインタレベル
@param array_level 変数リストから見つけた変数の配列レベル

@return 識別子の名前およびオフセットレベルが条件を満たしていれば１を返し、そうでなければ０を返す。
*/
int checkIdentifierPointerArrayLevel(AST *identifier,int offset_level, VARIABLE_TABLE_LIST *variable_table_list,
 ASTPOINTER_LIST *ignore_ast_list, int *pointer_level, int *array_level);

/**
関数呼び出しを示すASTノードが、登録されている関数に関する情報に含まれているかどうかを調べ、もし、その関数のポインタレベルがオフセットレベルと一致
した場合は、エラーを出力し、強制終了させる。
@param call_function 関数呼び出しを示すASTノード
@param offset_level オフセットレベル
@param function_information_list 関数に関する情報のリスト

@return なし
 */
void checkCallFunction(AST *call_function, int offset_level, FUNCTION_INFORMATION_LIST *function_information_list);

/**
指定したASTノードast_dataがASTアドレスリストignore_ast_listに存在するかどうかを調べる。存在する場合は１をかえす。
存在しない場合は、ast_dataのアドレスをignore_ast_listに追加した上、0を返す。
@param ast_data 指定したASTノード
@param ignore_ast_list 調べる対象のASTアドレスリスト

@return 存在する場合は１を返し、そうでない場合は０を返す
*/
int checkIgnoreASTList(AST *ast_data, ASTPOINTER_LIST *ignore_ast_list);

/**
ポインタのオフセットの検証対象となっている変数を示すASTノードtargetから、間接的にどの関係の中に位置しているかどうかを調べ、そのノードのアドレスoutputとして返す。
このとき、targetより明らかに上位であるASTノードrootを設定しなければならない。
また、outputがminus_exprの場合はそのポインタよりひとつ下が左辺か右辺かどうかを調べるために、
そのポインタの一つ下のノードをoutput2へ代入する。

@param target 検証対象となっている変数
@param root 検証対象のノード
@param output 出力される間接的に関係しているノードへのアドレス
@param output2 outputがminus_exprの場合、minus_exprより1つ下のノードがここに代入される
@return 検索が成功したかどうかのフラグ。成功した場合は１、そうでない場合は０を返す。
*/
int getUpperExpressionRelationNode(AST *target, AST *root, AST **output, AST **output2);


/*
指定した各次元の配列やポインタのオフセットリストarray_offsetの内容を出力する。

@param array_offset 出力対象の各次元の配列やポインタのオフセットリスト

@return なし
*/
void printARRAY_OFFSET(ARRAY_OFFSET *array_offset);

/*
指定した各次元の配列やポインタのオフセットリストarray_offsetの内容を出力する。

@param array_offset_list 出力対象の各次元の配列やポインタのオフセット情報のリスト

@return なし
*/
void printARRAY_OFFSET_LIST(ARRAY_OFFSET_LIST *array_offset_list);

/**
変数テーブルデータvariable_tableからオフセットリストoffset_listを生成する。

@param offset_list 生成先のオフセットリスト
@param variable_table 変数テーブルデータ

@return なし
*/
void getOFFSET_LISTFromVariableTable(OFFSET_LIST *offset_list, VARIABLE_TABLE *variable_table);

/**
オフセットリストoffset_listの中身を完全に解放させる。

@param offset_list

@return なし
*/
void deleteOFFSET_LIST(OFFSET_LIST *offset_list);

/**
指定した配列オフセットから、演算後のポインタレベルを求める。演算後のポインタレベルはつぎのとおりである。
演算後のポインタレベル＝この変数の配列とポインタレベルの合計値＋アンパサンドフラグ（挟んでいるなら１、そうでない場合は０）－この配列オフセット内のオフセットリスト
@param array_offset 指定した配列オフセット

@return 求めた演算後のポインタレベルを返す
*/
int getOffsetLevelFromArrayOffset(ARRAY_OFFSET *array_offset);

/**
指定した配列オフセットリストでの演算後のポインタレベルの最大レベルである配列オフセットのアドレスを求める。配列オフセットが空の場合はNULLを代入する。
@param array_offset_list 指定した配列オフセットリスト

@return 求めた演算後のポインタレベルが最大である配列オフセットのアドレスを返す
*/
ARRAY_OFFSET *maxOffsetLevelAddressFromArrayOffsetList(ARRAY_OFFSET_LIST *array_offset_list);

/**
対象のASTノードから、演算後のポインタレベルが指定されたポインタレベルと配列レベルの合計と一致するような
変数の配列オフセットを指定された配列オフセットリストから探し出し、見つかったらアドレスを取得する。

@param root 対象のASTノード
@param array_offset_list 対象の配列オフセットリスト
@param pointer_level 指定するポインタレベル
@param array_level 指定する配列レベル

@return 演算後のポインタレベルと指定されたポインタレベルと配列レベルの合計が一致するような変数を返す。失敗した場合はNULLを返す。
 */

ARRAY_OFFSET *searchOffsetLevelAddressFromArrayOffsetList(AST *root, ARRAY_OFFSET_LIST *array_offset_list,
		int pointer_level, int array_level);
/**
指定した配列オフセットリストでの演算後のポインタレベルの最大レベルを求める。配列オフセットが空の場合は０を代入する。
@param array_offset_list 指定した配列オフセットリスト

@return 求めた演算後のポインタレベルを返す。
*/
int maxOffsetLevelFromArrayOffsetList(ARRAY_OFFSET_LIST *array_offset_list);

/**
指定した式から、必要なオフセット情報を取得する。
@param expression 指定した式に関するASTノード
@param function_information_list 関数に関する情報のリスト
@param vtlist 検証対象の式をマークするための変数リスト
@param ignore_ast_list ポインタでの位置が検証済みである、IDENTIFIERを無視するためのASTのアドレスリスト
@param array_offset_list 各ポインタおよび配列ごとのオフセットのリスト
@param target_expression この左辺式の上位に位置するASTノード
@param switch_mode 直接アクセスおよび配列アクセスを探すか、IDENTIFIERを探すかどうかのスイッチフラグ ０：両方さがす　１：direct_refやarray_accessのみ探す
@param allow_subeffect 副作用の式を許すかどうかのフラグ １：許す ０：許さない
@return なし
*/
void getExpressionOffsetInfo(AST *expression, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist, ASTPOINTER_LIST *ignore_ast_list,
 ARRAY_OFFSET_LIST * array_offset_list, AST *target_expression, int *switch_mode, int allow_subeffect);

/**
指定した引数から、必要なオフセット情報を取得する。
@param argument 指定した引数に関するASTノード
@param function_information_list 関数に関する情報のリスト
@param vtlist 検証対象の式をマークするための変数リスト
@param ignore_ast_list ポインタでの位置が検証済みである、IDENTIFIERを無視するためのASTのアドレスリスト
@param array_offset_list 各ポインタおよび配列ごとのオフセットのリスト
@param target_expression この左辺式の上位に位置するASTノード
@param switch_mode 直接アクセスおよび配列アクセスを探すか、IDENTIFIERを探すかどうかのスイッチフラグ ０：両方さがす　１：direct_refやarray_accessのみ探す
@return なし
*/
void getArgumentOffsetInfo(AST *argument, FUNCTION_INFORMATION_LIST *function_information_list,
		VARIABLE_TABLE_LIST *vtlist, ASTPOINTER_LIST *ignore_ast_list, ARRAY_OFFSET_LIST * array_offset_list,
		AST *target_expression, int *switch_mode);

/**
指定した式から、必要なオフセット情報を取得する。これは副作用の式を許す。
@param expression 指定した式に関するASTノード
@param function_information_list 関数に関する情報のリスト
@param vtlist 検証対象の式をマークするための変数リスト
@param ignore_ast_list ポインタでの位置が検証済みである、IDENTIFIERを無視するためのASTのアドレスリスト
@param array_offset_list 各ポインタおよび配列ごとのオフセットのリスト
@param target_expression この左辺式の上位に位置するASTノード
@param switch_mode 直接アクセスおよび配列アクセスを探すか、IDENTIFIERを探すかどうかのスイッチフラグ ０：両方さがす　１：direct_refやarray_accessのみ探す
@return なし
*/
void getSingleExpressionOffsetInfo(AST *expression, FUNCTION_INFORMATION_LIST *function_information_list,
		VARIABLE_TABLE_LIST *vtlist, ASTPOINTER_LIST *ignore_ast_list,
 ARRAY_OFFSET_LIST * array_offset_list, AST *target_expression, int *switch_mode);
/**
配列オフセット情報から、任意の次元までの配列式を生成する。

@param output 配列式を生成される文字列
@param array_offset 対象の配列オフセット
@param output_level 出力したい次元(このとき、配列オフセットを超える値を入れた場合は、配列オフセットが次元までの配列式を出力する)

@return なし
*/

void createArrayExpression(CSTLString *output, ARRAY_OFFSET *array_offset, int output_level);

/**
配列オフセット情報から、検証用変数に使われる配列式を生成し、オフセットレベルを返す。
@param output 生成先の文字列
@param array_offset 対象の配列オフセット

@return 配列オフセット情報から生成されたオフセットレベルを返す
 */
int createValidateVariableArrayExpression(CSTLString *output, ARRAY_OFFSET *array_offset);

/**
配列オフセットリストfromlist内のmove_start以降のデータをすべて、もう一方の配列オフセットリストtolistに移動させる。
@param fromlist 移動もとの配列オフセットリスト
@param tolist 移動先の配列オフセットリスト
@param move_start 移動させたいデータの位置(先頭から０番目とする)

@return なし
 */
void moveArrayOffsetList(ARRAY_OFFSET_LIST *fromlist, ARRAY_OFFSET_LIST *tolist, int move_start);

/**
配列オフセットリストfromlist内のmove_start以降のデータをすべて、もう一方の配列オフセットリストtolistにコピーさせる。
@param fromlist コピー元の配列オフセットリスト
@param tolist コピー先の配列オフセットリスト
@param move_start 移動させたいデータの位置(先頭から０番目とする)

@return なし
 */
void copyArrayOffsetList(ARRAY_OFFSET_LIST *fromlist, ARRAY_OFFSET_LIST *tolist, int move_start);

/**
変数テーブルから、変数の定義に対するノードに該当する情報を探し、それに対する配列オフセット情報を取得する。
@param declarator_array_offset_list 取得先の配列オフセット情報
@param declarator_expression 変数定義までのASTアドレス
@param target_expression 対象のdeclarator_with_initへのASTアドレス
@param vtlist 調べる先の変数テーブル

@return なし
*/
void getDeclaratorArrayOffset(ARRAY_OFFSET_LIST *declarator_array_offset_list, AST *declarator_expression, AST *target_expression, VARIABLE_TABLE_LIST *vtlist);

/**
配列オフセットリストarray_offset_listから、指定した変数名を探索し、
見つかればその変数名へのアドレスを返す。

@param array_offset_list 探索対象の配列オフセットリスト
@param name 探索したい変数名

@return 見つかれば変数名へのアドレスを返す。そうでなければNULLを返す。
 */
ARRAY_OFFSET *searchARRAY_OFFSET_LIST(ARRAY_OFFSET_LIST *array_offset_list, CSTLString *name);

/**
対象の配列オフセットリストtarget_array_offset_listに対して、対象から取り除きたい
配列オフセットリストdelete_array_offset_listの名前に該当する配列オフセット情報を
削除する。

@param target_array_offset_list 対象の配列オフセットリスト
@param delete_array_offset_list 対象から取り除きたい配列オフセットリスト

@return なし
 */
void minusArrayOffsetList(ARRAY_OFFSET_LIST *target_array_offset_list, ARRAY_OFFSET_LIST *delete_array_offset_list);

/**
配列オフセットリストに配列オフセット情報を追加する。ただし、変数名が重複するのであれば、追加しない。

@param target_array_offset_list 追加先の配列オフセットリスト
@param array_offset 追加する配列オフセット情報

@return なし
 */
void ARRAY_OFFSET_LIST_push_back_ref_not_dup(ARRAY_OFFSET_LIST *target_array_offset_list, ARRAY_OFFSET *array_offset);

/**
ASTのポインタリストの内容を出力させる。

@param astpointer_list ASTのポインタリスト

@return なし
 */
void printASTPOINTER_LIST(ASTPOINTER_LIST *astpointer_list);
#endif
