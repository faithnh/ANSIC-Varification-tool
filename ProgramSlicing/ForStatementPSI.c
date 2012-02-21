#include"ForStatementPSI.h"

#include"../ANSICInformation/ANSIC_CODE.h"
#include"ExpressionStatementPSI.h"

/**
for文のASTノードfor_statementから、関数に対するプログラムスライシングを抽出し、
プログラムスライシングリストexpr_slicing_listに追加する。

@param expr_slicing_list 追加先のプログラムスライシングリストexpr_slicing_list
@param for_statement for文に関するASTノード
@param parent ノードを追加するときの親ノード
@param vtlist 変数テーブルリスト
@param function_information_list 関数に関する情報リスト
@param ignore_ast_list 重複防止のために無視するノードリスト

@return なし
 */

EXPR_SLICING *getForStatementPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *for_statement, EXPR_SLICING *parent,
		VARIABLE_TABLE_LIST *vtlist, FUNCTION_INFORMATION_LIST *function_information_list, ASTPOINTER_LIST *ignore_ast_list){
	EXPR_SLICING *output_children = NULL;
		//children1,children2を両方生成
		EXPR_SLICING_LIST *children1 = EXPR_SLICING_LIST_new();
		EXPR_SLICING_LIST *children2 = EXPR_SLICING_LIST_new();
		//対象の変数リストを生成
		ARRAY_OFFSET_LIST *target_variable = ARRAY_OFFSET_LIST_new();

		//for文の式から、依存関係のリストを求める
		ARRAY_OFFSET_LIST *dependences = ARRAY_OFFSET_LIST_new();
		//もし、for_statement_type_aが来た場合
		if(CSTLString_compare_with_char(for_statement->name, "for_statement_type_a") == 0){
			getASI_ARRAY_OFFSET_LIST(ASTLIST_ITERATOR_3(for_statement) ,target_variable, dependences, function_information_list, vtlist, ignore_ast_list, for_statement, 1);
			getASI_ARRAY_OFFSET_LIST(ASTLIST_ITERATOR_4(for_statement) ,target_variable, dependences, function_information_list, vtlist, ignore_ast_list, for_statement, 0);
		}

		//もし、for_statement_type_bが来た場合
		else if(CSTLString_compare_with_char(for_statement->name, "for_statement_type_b") == 0){
			getASI_ARRAY_OFFSET_LIST(ASTLIST_ITERATOR_3(for_statement) ,target_variable, dependences, function_information_list, vtlist, ignore_ast_list, for_statement, 1);
			getASI_ARRAY_OFFSET_LIST(ASTLIST_ITERATOR_4(for_statement) ,target_variable, dependences, function_information_list, vtlist, ignore_ast_list, for_statement, 0);
			getASI_ARRAY_OFFSET_LIST(ASTLIST_ITERATOR_5(for_statement) ,target_variable, dependences, function_information_list, vtlist, ignore_ast_list, for_statement, 1);			//新しいスライシングに関する情報を生成する

		}
		//上記外の場合は、不正なノードとしてエラーを出力させる
		else{
			fprintf(stderr,"不正なノード%sを見つけました",CSTLString_c_str(for_statement->name));
			exit(1);
		}

		//依存関係の変数に対して、対象の変数に当てはまる変数をすべて削除する
		minusArrayOffsetList(dependences, target_variable);

		//新しいスライシングに関する情報を生成する
		output_children = new_EXPR_SLICING(EXPR_SLICING_LIST_size(expr_slicing_list) + 1, for_statement, target_variable, dependences, children1, children2, parent);

		//新しく生成されたスライシングに関する情報をスライシングリストに追加する
		EXPR_SLICING_LIST_push_back_ref(expr_slicing_list, output_children);

	return output_children;


}
