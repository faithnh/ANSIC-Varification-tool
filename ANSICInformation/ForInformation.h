/*!
  @brief このファイルは、forループに関する情報を集めるための命令が含まれている

  @file ForInformation.h
  @author faithnh
 */
#ifndef FORINFORMATION_HEADDER_FILE
#define FORINFORMATION_HEADDER_FILE

#include "AST.h"
#include <cstl/list.h>
/**
for文の初期式・継続式・増分式およびfor文内全体の式へのノードが格納される。
これは、検証式付加ツールでfor文をwhile文に使用される。
*/
typedef struct for_information{
	AST *target_expression; ///このfor文自体へのASTノード
	AST *init_expression; ///初期式へのASTノード
	AST *continue_condition; ///継続式へのASTノード
	AST *inc_dec_expression; ///増分式へのASTノード
	AST *statement; ///for文内全体の式へのASTノード
} ForInformation;

/**
これは、FOR_INFORMATIONの実装を確かめる
*/
CSTL_LIST_INTERFACE(ForInformationList, ForInformation)

/**
for文に関する情報FOR_INFORMATIONを生成する。
@param target_expression このfor文自体の情報
@param init_expression 初期式
@param continue_condition 継続式
@param inc_dec_expression 増分式
AST *statement for文内の全体の式を指す
@return 生成されたFOR_INFORMATIONへのアドレスを返す。

*/
ForInformation *new_FOR_INFORMATION(AST *target_expression, AST *init_expression, AST *continue_condition, AST *inc_dec_expression, AST *statement);

/**
for文に関する情報のリストfor_information_listを出力する。
@param for_information_list for文に関する情報のリスト

@return なし
*/
void print_FOR_INFORMATION_LIST(ForInformationList *for_information_list);

/**
for文に関する情報のリストfor_information_listから、指定したASTノードに対応したものを出力させる。
@param for_information_list 検索対象のfor文に関する情報のリスト
@param target_ast 検索するAST

@return マッチしたものが見つかれば、それに対応したものへのアドレスを出力させる。見つからない場合はNULLを返す。
*/
ForInformation *searchFOR_INFORMATION_FromAST(ForInformationList *for_information_list, AST *target_ast);

/**
for_iterationのASTノードから、for文に関する情報のリストを取得する。

@param for_information_list for文に関する情報のリスト
@param for_iteration_ast for文に関する情報のリスト

@return なし
*/
void getFOR_INFORMATION_LIST(ForInformationList *for_information_list, AST *for_iteration_ast);

#endif
