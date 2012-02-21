/*!
  @brief これはC言語プログラム上から、不具合を検証するための検証式や検証用に使用する変数などを追加するための命令が含まれている。

  @file Varidate_statement.h
  @author faithnh
 */
#ifndef VARIDATE_STATEMENT_HEADDER
#define VARIDATE_STATEMENT_HEADDER

#include <cstl/list.h>

#include"Synbol.h"

#include"PointerArrayControl.h"
#include"MemallocInfo.h"
#include"FreeMemInfo.h"
#include "ForInformation.h"
#include "DivitionInformation.h"
#include "PreProcess.h"

#include"../ProgramSlicing/ProgramSlicingInformation.h"
/**
ポインタや配列変数に対する検証用の変数リストを作成するための構造体である。
*/
typedef struct validate_variable {
	int used;					///この検証用の変数が使用しているかどうかのフラグ 1:使用 0:未使用
	int enable_start;			///この変数の有効範囲（ブロックでの）の開始行数を示す
	int enable_end;				///この変数の有効範囲（ブロックでの）の終了行数を示す
	int declaration_location;	///この変数を宣言する行数を示す
	int block_level;			///この変数を宣言するブロックレベルを示す（０ならグローバル変数・１なら関数内と示す）
	int block_id;				///この変数を宣言するブロックIDを示す（同ブロックレベルで別のブロックを識別するための番号）
	CSTLString *type;			///この変数の型
	CSTLString *variable_name;	///この変数名
	CSTLString *target_variable_name; ///この変数の検証対象となる変数名
	int offset_level;			///この変数の配列やポインタの次元レベル
} ValidateVariable;

CSTL_LIST_INTERFACE(ValidateVariableList, ValidateVariable);

/**
実際に検証式として挿入するための情報である。
*/
typedef struct validate_statement {
	int target_id;			///この検証式の識別ID(どの順序でこの検証式を入れていくかを確認するためのID)
	int check_or_modify;	///検証式をチェックするタイプか、プログラムを元に編集するタイプかを判断するフラグ。０：チェックするタイプ、１：編集するタイプ
	int used;				///この検証式は使用しているかどうかのフラグ 1:使用 0:未使用
	CSTLString *statement;	///この検証式の内容
	AST *target_statement;	///この検証式のターゲットとなるASTノードへのアドレス
} ValidateStatement;

CSTL_LIST_INTERFACE(ValidateStatementList, ValidateStatement);


/**
実際に検証式として挿入するための情報を生成する。
@param target_id この検証式の識別ID(どの順序でこの検証式を入れていくかを確認するためのID)
@param check_or_modify 検証式をチェックするタイプか、プログラムを元に編集するタイプかを判断するフラグ。０：チェックするタイプ、１：編集するタイプ
@param used この検証式は使用しているかどうかのフラグ 1:使用 0:未使用
@param statement この検証式の内容
@param target_statement この検証式のターゲットとなるASTノードへのアドレス

@return 実際に検証式として挿入するための情報へのアドレスを返す。
*/
ValidateStatement *new_VALIDATE_STATEMENT_char(int target_id, int check_or_modify, int used, char *statement, AST *target_statement);

/**
実際に検証式として挿入するための情報を生成する。
@param target_id この検証式の識別ID(どの順序でこの検証式を入れていくかを確認するためのID)
@param check_or_modify 検証式をチェックするタイプか、プログラムを元に編集するタイプかを判断するフラグ。０：チェックするタイプ、１：編集するタイプ
@param used この検証式は使用しているかどうかのフラグ 1:使用 0:未使用
@param statement この検証式の内容
@param target_statement この検証式のターゲットとなるASTノードへのアドレス

@return 実際に検証式として挿入するための情報へのアドレスを返す。
*/
ValidateStatement *new_VALIDATE_STATEMENT(int target_id, int check_or_modify, int used, CSTLString *statement, AST *target_statement);

/**
新しい検証用変数テーブルのデータを生成させる。
@param used この検証用変数テーブルを使用したかどうか
@param enable_start この変数の有効範囲の始まりの行数
@param enable_end この変数の有効範囲の終わりの行数
@param declaration_location この変数を宣言した場所の行数
@param block_level この変数のブロックレベル（グローバル変数なら０とし、関数の中での定義なら１、その関数内のfor文などのブロック文ないでの宣言なら２とする）
@param block_id ブロックごとのID（基本的には0から始り、ブロックレベル２が２回目にくると、１となる）
@param type 型名
@param variable_name 変数名
@param target_variable_name 検証対象の変数名
@param offset_level この変数の配列やポインタの次元レベル

@return 新しく生成された検証用変数のデータへのアドレスが返される。
*/
ValidateVariable *new_VALIDATE_VARIABLE(int used, int enable_start, int enable_end, int declaration_location,
								   int block_level ,int block_id, CSTLString *type, CSTLString *variable_name, CSTLString *target_variable_name, int offset_level);

/**
新しい検証用変数テーブルのデータを生成させる(char対応版)。
@param used この検証用変数テーブルを使用したかどうか
@param enable_start この変数の有効範囲の始まりの行数
@param enable_end この変数の有効範囲の終わりの行数
@param declaration_location この変数を宣言した場所の行数
@param block_level この変数のブロックレベル（グローバル変数なら０とし、関数の中での定義なら１、その関数内のfor文などのブロック文ないでの宣言なら２とする）
@param block_id ブロックごとのID（基本的には0から始り、ブロックレベル２が２回目にくると、１となる）
@param type 型名
@param variable_name 変数名
@param target_variable_name 検証対象の変数名
@param offset_level この変数の配列やポインタの次元レベル

@return 新しく生成された検証用変数のデータへのアドレスが返される。
*/
ValidateVariable *new_VALIDATE_VARIABLE_with_char(int used, int enable_start, int enable_end, int declaration_location,
								   int block_level ,int block_id, char *type, char *variable_name, char *target_variable_name, int offset_level);

/**
検証式リストの使用フラグを未使用状態に初期化する。
@param validate_statement_list *初期化対象の検証式リスト

@return なし
 */
void initVaridateStatement_flag(ValidateStatementList *validate_statement_list);

/**
プログラムの変数リストをもとにプログラムの検証用の変数を設定する。
@param variable_table_list プログラムの変数リスト
@param validate_variable 検証用の変数リスト
@return なし
*/
void getValidate_Variable(VARIABLE_TABLE_LIST *variable_table_list, ValidateVariableList *validate_variable);

/**
検証用変数テーブルのリストの内容を出力させる。
@param validate_variable_list 出力対象の検証用変数テーブルのリスト
@return なし

*/
void printValidateVariableList(ValidateVariableList *validate_variable_list);

/**
基本的な検証式の生成を行う。
@param root 検証式生成対象のASTノード
@param function_informaiton_list 関数に関する情報のリスト
@param vtlist 検証対象の式をマークするための変数リスト
@param validate_variable_list 検証用変数リスト
@param validate_statement_list 取得した検証式が格納するところ
@param for_information_list for文に関する情報
@param undefined_control_check 未定義な処理（未定義ポインタの参照など）を行っていないかどうかを検証するための式を生成するかどうか １：生成する ０：生成しない
@param zero_divition_check 0で割っていないかどうかを検証するための式を生成するかどうか　１：生成する　０：生成しない
@param array_unbound_check 配列が範囲外を参照していないかどうかを検証するための式を生成するかどうか　１：生成する　０：生成しない
@param free_violation_check メモリ解放関係で不正な処理を行っていないかどうかを検証するための式を生成するかどうか　１：生成する　０：生成しない

@return なし
*/
void createValidateStatement(AST * root, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist, ValidateVariableList *validate_variable_list,
											ValidateStatementList *validate_statement_list, ForInformationList *for_information_list, int undefined_control_check,
											int zero_divition_check, int array_unbound_check, int free_violation_check);

/**
指定したASTノードrootから、init_declaratorを探しだし、そこからVARIDATE_STATEMENTに関する情報を取得する。
@param root 指定したノード
@param function_information_list 関数に関する情報のリスト
@param vtlist 対象の変数リスト
@param validate_variable_list 検証用変数リスト
@param validate_statement_list 取得した検証式が格納するところ
@param ignore_ast_list ポインタでの位置が検証済みである、IDENTIFIERを無視するためのASTのアドレスリスト
@param target_expression assign_expressionが属しているexpression_statement
@param undefined_control_check 未定義な処理を行っていないかどうかを検証するための式を生成するかどうか １：生成する ０：生成しない
@param zero_divition_check 0で割っていないかどうかを検証するための式を生成するかどうか　１：生成する　０：生成しない
@param array_unbound_check 配列が範囲外を参照していないかどうかを検証するための式を生成するかどうか　１：生成する　０：生成しない

@return なし
*/
void getValidateStatementFromInitializer(AST *root, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
											ValidateVariableList *validate_variable_list,ValidateStatementList *validate_statement_list, ASTPOINTER_LIST *ignore_ast_list,
											AST *target_expression, int undefined_control_check, int zero_divition_check, int array_unbound_check);

/**
malloc用識別番号を付加するための関数に変換するための検証式を追加させる。
@param validate_statement_list 追加先の検証式リスト
@param call_function 関数呼び出しに対するノード
@param right_array_offset_list 左辺値に関する配列オフセットリスト
@param memalloc_info メモリ確保情報

@return なし
*/
void getValidateStatementFromMallocNumber(ValidateStatementList *validate_statement_list, AST *call_function, ARRAY_OFFSET_LIST* right_array_offset_list, MEMALLOC_INFO *memalloc_info);

/**
for文の末尾の情報から、検証式を取得し、検証式リストに入れる。
@param validate_statement_list 取得した検証式が格納するところ
@param for_information_list for文に関する情報のリスト
@param function_information_list 関数に関する情報のリスト
@param vtlist 対象の変数リスト
@param validate_variable_list 検証用変数リスト
@param ignore_ast_list ポインタでの位置が検証済みである、IDENTIFIERを無視するためのASTのアドレスリスト
@param undefined_control_check 未定義な処理を行っていないかどうかを検証するための式を生成するかどうか １：生成する ０：生成しない
@param zero_divition_check 0で割っていないかどうかを検証するための式を生成するかどうか　１：生成する　０：生成しない
@param array_unbound_check 配列が範囲外を参照していないかどうかを検証するための式を生成するかどうか　１：生成する　０：生成しない
@param free_violation_check メモリ解放関係で不正な処理を行っていないかどうかを検証するための式を生成するかどうか　１：生成する　０：生成しない

@return なし
*/
void getValidateStatementFromForIteration(ValidateStatementList *validate_statement_list, ForInformationList *for_information_list,
										FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,ValidateVariableList *validate_variable_list,
										ASTPOINTER_LIST *ignore_ast_list, int undefined_control_check,int zero_divition_check,int array_unbound_check,
										int free_violation_check);


/**
指定したASTノードrootから、assign_expressionを探しだし、そこからVARIDATE_STATEMENTに関する情報を取得する。
@param root 指定したノード
@param function_information_list 関数に関する情報のリスト
@param vtlist 対象の変数リスト
@param validate_variable_list 検証用変数リスト
@param validate_statement_list 取得した検証式が格納するところ
@param ignore_ast_list ポインタでの位置が検証済みである、IDENTIFIERを無視するためのASTのアドレスリスト
@param target_expression assign_expressionが属しているexpression_statement
@param undefined_control_check 未定義な処理（未定義ポインタの参照など）を行っていないかどうかを検証するための式を生成するかどうか １：生成する ０：生成しない
@param zero_divition_check 0で割っていないかどうかを検証するための式を生成するかどうか　１：生成する　０：生成しない
@param array_unbound_check 配列が範囲外を参照していないかどうかを検証するための式を生成するかどうか　１：生成する　０：生成しない
@param free_violation_check メモリ解放関係で不正な処理を行っていないかどうかを検証するための式を生成するかどうか　１：生成する　０：生成しない

@return なし
*/
void getValidateStatementFromAssignStatement(AST *root, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
											ValidateVariableList *validate_variable_list,
											ValidateStatementList *validate_statement_list, ASTPOINTER_LIST *ignore_ast_list,
											AST *target_expression, int undefined_control_check, int zero_divition_check, int array_unbound_check
											, int free_violation_check);

/**
ポインタ演算式後の内容を検証用変数に反映するための検証式を追加する。

@param validate_statement_list 検証式リスト
@param left_array_offset_list 左辺値の配列オフセットリスト
@param right_array_offset_list 右辺式の配列オフセットリスト
@param right_expression 右辺式へのＡＳＴアドレス
@param a_op_flag 代入演算子が何かを示すフラグ 0:=,1:+=,2:-=,3:*=,4:/=,5:%=,6:<<=,7:>>=,8:&=,9:|=,10:^=
@return なし
*/
void getValidateStatementFromPointerOperator(ValidateStatementList *validate_statement_list,ARRAY_OFFSET_LIST *left_array_offset_list,ARRAY_OFFSET_LIST *right_array_offset_list, AST *right_expression, int a_op_flag);

/**
式から、関数呼出を探しだし、関数呼出に対する検証式を追加する。

@param root 探索対象のASTノード
@param validate_statement_list 検証式リスト
@param left_array_offset_list 左辺値の配列オフセットリスト
@param right_array_offset_list 右辺式の配列オフセットリスト
@param function_information_list 関数に関する情報リスト

@return なし
 */
void getValidateStatementFromCallFunction(AST *root, ValidateStatementList *validate_statement_list, ARRAY_OFFSET_LIST *left_array_offset_list,
		ARRAY_OFFSET_LIST *right_array_offset_list, FUNCTION_INFORMATION_LIST *function_information_list);

/**
ポインタ演算式に対して、ポインタ演算における基本的な位置の式を文字列として求め、outputに入れる。
@param output 出力先のCSTL文字列
@param left_array_offset_list 左辺値の配列オフセットリスト
@param right_array_offset_list 右辺式の配列オフセットリスト
@param right_expression_ast 右辺式へのASTアドレス
@param a_op_flag 代入演算子が何かを示すフラグ 0:=,1:+=,2:-=,3:*=,4:/=,5:%=,6:<<=,7:>>=,8:&=,9:|=,10:^=

@return なし

*/
void getBasisLocationFromAssignmentExpression(CSTLString *output, ARRAY_OFFSET_LIST *left_array_offset_list,
											  ARRAY_OFFSET_LIST *right_array_offset_list, AST *right_expression_ast, int a_op_flag);


/**
指定した式expression_astから、ポインタ演算における基本的な位置の式を文字列として求め、outputに入れる。このとき、array_offsetを見つけたらそれに該当する式を０に変換する。
@param output 出力先のCSTL文字列
@param array_offset 指定した識別子の配列オフセット
@param expression_ast 指定した式へのASTアドレス
@return なし
*/
void getBasisLocationFromExpression(CSTLString *output, ARRAY_OFFSET *array_offset, AST *expression_ast);

/**
メモリ確保関係の情報memalloc_infoや配列やポインタのオフセット情報array_offset_listから検証式を生成し、ValidateStatementListに追加する。

@param variable_statement_list 生成先の検証式リスト
@param memalloc_info メモリ確保関係の情報
@param array_offset_list 配列やポインタのオフセット情報
@param ValidateVariableList 検証用変数リスト

@return なし
*/
void createValidateStatementForMallocAction(ValidateStatementList *validate_statement_list, MEMALLOC_INFO *memalloc_info,
										ARRAY_OFFSET_LIST *array_offset_list,ValidateVariableList *validate_variable_list);

/**
指定した配列オフセットarrya_offset_listから、インクリメントおよびデクリメント式を含んでいたら、
それに応じてbasis_locationに反映させるための検証式を生成し、ValidateStatementListに追加する。

@param validate_statement_list 追加先の検証式
@param array_offset_list 配列オフセットリスト

@return なし

*/
void createValidateStatemenFromIncDecExpr(ValidateStatementList *validate_statement_list, ARRAY_OFFSET_LIST *array_offset_list);

/**
メモリ解放関係の情報freememinfoから検証式を生成し、ValidateStatementListに追加する。

@param variable_statement_list 生成先の検証式リスト
@param freememinfo メモリ確保関係の情報
@param ValidateVariableList 検証用変数リスト

@return なし
*/
void createValidateStatementForFreeAction(ValidateStatementList *validate_statement_list, FREEMEMINFO *freememinfo,
				ValidateVariableList *validate_variable_list);
/**
変数定義リストで、配列生成時の検証用変数の更新するための検証式を作成し、validate_statement_listに追加する。
また、検証用変数リストvalidate_variable_listに、配列のオフセットを生成するのに使用する変数vviterator_2～vviterator_n（nは配列の最大次元数）を生成し、追加する。
@param validate_variable_list 検証用変数リスト
@param validate_statement_list 追加先の検証式
@param variable_table_list 変数テーブルリスト
@param function_information_list 関数定義に関する情報リスト
@return なし
*/
void createValidateStatementFromArrayDefine(ValidateVariableList *validate_variable_list, ValidateStatementList *validate_statement_list, VARIABLE_TABLE_LIST *variable_table_list
					,FUNCTION_INFORMATION_LIST *function_information_list);

/**
変数定義リストでポインタ変数に対する検証用変数を更新するための検証式を作成し、validate_statement_listに追加する。
@param validate_statement_list 追加先の検証式
@param variable_table_list 変数テーブルリスト
@param function_information_list 関数定義に関する情報リスト

@return なし
*/
void createVaridateStatementFromPointerDefine( ValidateStatementList *validate_statement_list, VARIABLE_TABLE_LIST *variable_table_list,
			FUNCTION_INFORMATION_LIST *function_information_list);

/**
配列のオフセットリストを基に、検証式を作成する。
@param output 出力する検証式
@param ValidateVariableList 検証用変数リスト
@param variable_table 対象の変数データ
@param offset_list オフセットリスト

@return なし
*/
void ArrayOffsetToValidateStatement(CSTLString* output, ValidateVariableList *validate_variable_list, VARIABLE_TABLE *variable_table, OFFSET_LIST *offset_list);

/**
配列やポインタなどのオフセット情報のリストarray_offset_listから、配列の範囲外参照のチェックをするための検証式
や、未定義状態で処理をチェックするための検証式を生成し、ValidateStatementListへ追加する。

@param validate_statement_list 追加先の検証式リスト
@param array_offset_list 配列やポインタなどのオフセット情報のリスト
@param array_unbound_check 配列が範囲外を参照していないかどうかを検証するための式を生成するかどうか　１：生成する　０：生成しない
@param undefined_control_check 未定義な処理を行っていないかどうかを検証するための式を生成するかどうか １：生成する ０：生成しない
@return なし
*/
void createCheckUnboundAndUndefineOperationCheck(ValidateStatementList *validate_statement_list, ARRAY_OFFSET_LIST *array_offset_list, int array_unbound_check, int undefined_control_check);

/**
メモリ解放関係の情報freememinfoから、free関数に関する違反行為を行っていないかどうかをチェックするための検証式を生成し、ValidateStatementListへ追加する。

@param validate_statement_list 追加先の検証式リスト
@param freememinfo メモリ解放関係の情報

@return なし
*/
void createViolentFreeOperation(ValidateStatementList *validate_statement_list, FREEMEMINFO *freememinfo);

/**
除算および剰余式の情報から、ゼロ除算および剰余になっていないかどうかの検証式を生成する。
@param validate_statement_list 格納先の検証式リスト
@param divition_information_list 対象の除算および剰余式の情報

@return なし
*/
void createZeroDivitionCheck(ValidateStatementList *validate_statement_list, DIVITION_INFORMATION_LIST *divition_information_list);
/**
検証式リストValidateStatementListから、target_statementと同じASTのアドレスを持ったものを探し出し、それを基に重複しないようにするための新しい検証式の識別番号を取得する。
新しい検証式を作るにはこの関数から新しい識別番号を取得すること。

@param validate_statement_list 対象の検証式リスト
@param target_statement 対象の検証式から確認するためのASTのアドレス

@return 新しい識別番号を出力する。すでに同じASTのアドレスを持っている検証式がなければ０を返す。
*/
int getNewValidateStatementID(ValidateStatementList *validate_statement_list, AST *target_statement);

/**
代入式の左辺値について、検証式に必要な情報を取得する。
@param left_expression 左辺値に関するASTノード
@param function_information_list 関数に関する情報のリスト
@param vtlist 検証対象の式をマークするための変数リスト
@param ignore_ast_list ポインタでの位置が検証済みである、IDENTIFIERを無視するためのASTのアドレスリスト
@param array_offset_list 各ポインタおよび配列ごとのオフセットのリスト
@param target_expression この左辺式の上位に位置するASTノード
@param switch_mode 直接アクセスおよび配列アクセスを探すか、IDENTIFIERを探すかどうかのスイッチフラグ ０：両方さがす　１：direct_refやarray_accessのみ探す
@return なし
*/
void getLeftAssignmentInfo(AST *left_expression, FUNCTION_INFORMATION_LIST *function_information_list,
		VARIABLE_TABLE_LIST *vtlist, ASTPOINTER_LIST *ignore_ast_list, ARRAY_OFFSET_LIST * array_offset_list,
		AST *target_expression, int *switch_mode);

/**
代入式の右辺式について、検証式に必要な情報を取得する。
@param root 右辺式に関するASTノード
@param function_information_list 関数に関する情報のリスト
@param vtlist メモリ確保情報を取得するのに必要なプログラム変数リスト
@param memalloc_info malloc関係の情報が出力される
@param array_offset_list 左辺式上にあるポインタ参照に対するオフセットリスト
@param ignore_ast_list 同じ位置のポインタが来ても無視するためのリスト
@param target_statement この計算式を属しているASTノードへのアドレス（基本的にexpression_statementであるノードが入る）

@return なし
*/
void getRightAssignmentInfo(AST *root, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist, MEMALLOC_INFO **memalloc_info,
	 ARRAY_OFFSET_LIST *array_offset_list, ASTPOINTER_LIST *ignore_ast_list, AST *target_statement);

/**
検証式リストとともにプログラムデータを出力する。

@param root プログラムへのASTノード
@param validate_variable_list 検証用変数リスト
@param validate_statement_list 検証式リスト
@param for_information_list for文に関する情報のリスト

@return なし
*/
void printProgramDataWithValidateStatement(AST *root, ValidateVariableList *validate_variable_list, ValidateStatementList *validate_statement_list, ForInformationList *for_information_list);

/**
検証式リストや検証用変数をもとにプログラムデータを生成し、指定したファイルoutputに出力する。

@param output 出力先のファイル構造体
@param root プログラムへのASTノード
@param validate_variable_list 検証用変数リスト
@param validate_statement_list 検証式リスト
@param for_information_list for文に関する情報のリスト

@return なし
*/
void fprintProgramDataWithValidateStatement(FILE *output, AST *root, ValidateVariableList *validate_variable_list, ValidateStatementList *validate_statement_list, ForInformationList *for_information_list);

/**
式に対応する検証式を出力させる。

@param output 出力先のファイル構造体
@param validate_statement_list 出力対象の検証式リスト
@param target_ast 対象のASTノード
@param check_or_modify 検証式をチェックするタイプか、プログラムを元に編集するタイプかを判断するフラグ。０：チェックするタイプ、１：編集するタイプ
@param allow_output_used_statement 使用済みの検証式も含めて出力するかどうかのフラグ　０：出力しない　１：出力する

@return なし
*/
void fprintValidateStatement(FILE *output, ValidateStatementList *validate_statement_list, AST *target_ast, int check_or_modify, int allow_output_used_statement);

/**
式に対応する検証式をassert(0); を削除したうえ出力させる。

@param output 出力先のファイル構造体
@param validate_statement_list 出力対象の検証式リスト
@param target_ast 対象のASTノード
@param check_or_modify 検証式をチェックするタイプか、プログラムを元に編集するタイプかを判断するフラグ。０：チェックするタイプ、１：編集するタイプ
@param allow_output_used_statement 使用済みの検証式も含めて出力するかどうかのフラグ　０：出力しない　１：出力する

@return なし
*/
void fprintValidateStatement_not_assert(FILE *output, ValidateStatementList *validate_statement_list, AST *target_ast, int check_or_modify, int allow_output_used_statement);
/**
プログラムスライシング情報の変数定義をもとに、検証用変数リストの出力を設定する。
@param validate_variable_list 検証用変数リスト
@param expr_slicing_list プログラムスライシング情報のリスト

@return なし
 */
void setValidateVariableFromExprSlicing(ValidateVariableList *validate_variable_list, EXPR_SLICING_LIST *expr_slicing_list);

/**
プログラムスライシング情報をもとに検証式を追加しながら出力させる。

@param output 出力する先のファイル
@param expr_slicing_list プログラムスライシング情報
@param validate_variable_list 検証用変数リスト
@param validate_statement_list 検証式リスト
@param for_information_list for文に関する情報
@param check_target_ast チェック検証式の対象へのASTノード

@return なし
 */
void fprintProgramDataWithPSIVaridateStatement(FILE *output, EXPR_SLICING_LIST *expr_slicing_list, ValidateStatementList *validate_statement_list,
			ValidateVariableList *validate_variable_list, ForInformationList *for_information_list, AST *check_target_ast);

/**
プログラムをチェック式ごとにプログラムスライシングと検証式付加を行ったファイルを生成する。
@param expr_slicing_list プログラムスライシング情報
@param validate_variable_list 検証用変数リスト
@param validate_statement_list 検証式リスト
@param for_information_list for文に関する情報
@param include_list インクルードリスト

@return なし
 */

void createValidateStatementAdderFileEachCheck(EXPR_SLICING_LIST *expr_slicing_list, ValidateStatementList *validate_statement_list,
		ValidateVariableList *validate_variable_list, ForInformationList *for_information_list, INCLUDE_LIST *include_list);

/**
検証式リストをASTノードごとにソートする。
@param validate_statement_list ソート対象の検証式リスト


@return なし
*/
void ValidateStatementList_sort_ast(ValidateStatementList *validate_statement_list);

/**
検証式リストのチェック式から、ASTノードを取り出し、ASTリストとしてまとめる。
@param validate_statement_list 取り出し先の検証式リスト
@param ast_node_list まとめる先のASTノードリスト

@return なし
 */
void getASTList_FromValidateStatementList(ValidateStatementList *validate_statement_list, ASTPOINTER_LIST *ast_node_list);

#endif
