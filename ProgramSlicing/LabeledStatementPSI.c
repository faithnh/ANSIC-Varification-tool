#include <stdio.h>
#include<stdlib.h>
#include "LabeledStatementPSI.h"

/**
gotoラベル文、caseラベル文、defaultラベル文のASTノードexpression_statementから、関数に対するプログラムスライシングを抽出し、
プログラムスライシングリストexpr_slicing_listに追加する。

@param expr_slicing_list 追加先のプログラムスライシングリストexpr_slicing_list
@param labeled_statement   gotoラベル文、caseラベル文、defaultラベル文に関するASTノード
@param parent ノードを追加するときの親ノード
@param vtlist 変数テーブルリスト
@param function_information_list 関数に関する情報リスト
@param ignore_ast_list 重複防止のために無視するノードリスト

@return なし
 */
EXPR_SLICING *getLabeledStatementPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *labeled_statement, EXPR_SLICING *parent,
		VARIABLE_TABLE_LIST *vtlist, FUNCTION_INFORMATION_LIST *function_information_list, ASTPOINTER_LIST *ignore_ast_list){

	//新しいプログラムスライシング情報
	EXPR_SLICING *new_expr_slicing = NULL;

	//初期状態の対象変数および依存変数を生成する
	ARRAY_OFFSET_LIST *target_variable = ARRAY_OFFSET_LIST_new();
	ARRAY_OFFSET_LIST *dependences =ARRAY_OFFSET_LIST_new();

	//初期状態のchildren1, children2を生成する
	EXPR_SLICING_LIST *children1 = EXPR_SLICING_LIST_new();
	EXPR_SLICING_LIST *children2 = EXPR_SLICING_LIST_new();

	//gotoラベル文、defaultラベル文が出てきた場合
	if(CSTLString_compare_with_char(labeled_statement->name, "goto_labeled_statement") == 0 ||
			CSTLString_compare_with_char(labeled_statement->name, "default_labeled_statement") == 0){

		//新しいスライシングに関する情報を生成する、スライシングリストに追加する
		EXPR_SLICING_LIST_push_back_ref(expr_slicing_list,
				new_EXPR_SLICING(EXPR_SLICING_LIST_size(expr_slicing_list) + 1,
						labeled_statement, target_variable, dependences, children1, children2, parent));

		//追加したスライシング情報を取得する
		new_expr_slicing = EXPR_SLICING_LIST_data(EXPR_SLICING_LIST_rbegin(expr_slicing_list));

	}
	//caseラベル文が出てきた場合
	else if(CSTLString_compare_with_char(labeled_statement->name, "case_labeled_statement") == 0){

		//新しいスライシングに関する情報を生成する
		getASI_ARRAY_OFFSET_LIST(ASTLIST_ITERATOR_2(labeled_statement),target_variable, dependences, function_information_list, vtlist, ignore_ast_list, labeled_statement, 0);

		//新しいスライシングに関する情報を生成する、スライシングリストに追加する
		EXPR_SLICING_LIST_push_back_ref(expr_slicing_list,
				new_EXPR_SLICING(EXPR_SLICING_LIST_size(expr_slicing_list) + 1,
						labeled_statement, target_variable, dependences, children1, children2, parent));

		//追加したスライシング情報を取得する
		new_expr_slicing = EXPR_SLICING_LIST_data(EXPR_SLICING_LIST_rbegin(expr_slicing_list));
	}
	else{
		fprintf(stderr,"不正なノード%sを見つけました",CSTLString_c_str(labeled_statement->name));
		exit(1);
	}

	return new_expr_slicing;
}
