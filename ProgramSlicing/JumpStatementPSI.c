#include <stdio.h>
#include<stdlib.h>
#include "JumpStatementPSI.h"

/**
GOTO、continue、break文のASTノードexpression_statementから、関数に対するプログラムスライシングを抽出し、
プログラムスライシングリストexpr_slicing_listに追加する。

@param expr_slicing_list 追加先のプログラムスライシングリストexpr_slicing_list
@param jump_statement GOTO、continue、break文に関するASTノード
@param parent ノードを追加するときの親ノード

@return なし
 */
void getJumpStatementPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *jump_statement, EXPR_SLICING *parent){

	//GOTO、continue、break文が出てきた場合
	if(CSTLString_compare_with_char(jump_statement->name, "goto_statement") == 0 ||
			CSTLString_compare_with_char(jump_statement->name, "continue_statement") == 0 ||
			CSTLString_compare_with_char(jump_statement->name, "break_statement") == 0 ){


	//初期状態の対象変数および依存変数を生成する
	ARRAY_OFFSET_LIST *target_variable = ARRAY_OFFSET_LIST_new();
	ARRAY_OFFSET_LIST *dependences =ARRAY_OFFSET_LIST_new();

	//初期状態のchildren1, children2を生成する
	EXPR_SLICING_LIST *children1 = EXPR_SLICING_LIST_new();
	EXPR_SLICING_LIST *children2 = EXPR_SLICING_LIST_new();

	//プログラムスライシングリストに追加する
	EXPR_SLICING_LIST_push_back_ref(expr_slicing_list, new_EXPR_SLICING(EXPR_SLICING_LIST_size(expr_slicing_list) + 1, jump_statement, target_variable, dependences, children1, children2, parent));

	}else{
		fprintf(stderr,"不正なノード%sを見つけました",CSTLString_c_str(jump_statement->name));
		exit(1);
	}
}
