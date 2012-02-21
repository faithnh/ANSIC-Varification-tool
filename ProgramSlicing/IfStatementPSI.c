
#include"IfStatementPSI.h"

#include"../ANSICInformation/ANSIC_CODE.h"
#include"ExpressionStatementPSI.h"

/**
if文もしくは、ifとelse文のASTノードif_statementから、関数に対するプログラムスライシングを抽出し、
プログラムスライシングリストexpr_slicing_listに追加する。

@param expr_slicing_list 追加先のプログラムスライシングリスト
@param if_statement if文もしくは、ifとelse文に関するASTノード
@param parent ノードを追加するときの親ノード
@param vtlist 変数テーブルリスト
@param function_information_list 関数に関する情報リスト
@param ignore_ast_list 重複防止のために無視するノードリスト

@return なし
 */
EXPR_SLICING *getIfStatementPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *if_statement, EXPR_SLICING *parent,
		VARIABLE_TABLE_LIST *vtlist, FUNCTION_INFORMATION_LIST *function_information_list, ASTPOINTER_LIST *ignore_ast_list){

	EXPR_SLICING *output_children = NULL;
	//children1,children2を両方生成
	EXPR_SLICING_LIST *children1 = EXPR_SLICING_LIST_new();
	EXPR_SLICING_LIST *children2 = EXPR_SLICING_LIST_new();
	//もし、単体のif文かifとelse文の組み合わせのASTノードが来た場合
	if(CSTLString_compare_with_char(if_statement->name, "if_statement") == 0 ||
		CSTLString_compare_with_char(if_statement->name,"ifelse_statement") == 0){
		//対象の変数リストを生成
		ARRAY_OFFSET_LIST *target_variable = ARRAY_OFFSET_LIST_new();

		//if文内の条件式から、依存関係のリストを求める(このとき、副作用式は禁止にする)
		ARRAY_OFFSET_LIST *dependences = ARRAY_OFFSET_LIST_new();
		getASI_ARRAY_OFFSET_LIST(ASTLIST_ITERATOR_3(if_statement),target_variable, dependences, function_information_list, vtlist, ignore_ast_list, if_statement, 0);


		//新しいスライシングに関する情報を生成する、スライシングリストに追加する
		EXPR_SLICING_LIST_push_back_ref(expr_slicing_list,
				new_EXPR_SLICING(EXPR_SLICING_LIST_size(expr_slicing_list) + 1,
						if_statement, target_variable, dependences, children1, children2, parent));

		//追加したスライシング情報を取得する
		output_children = EXPR_SLICING_LIST_data(EXPR_SLICING_LIST_rbegin(expr_slicing_list));
	}else{
		fprintf(stderr,"不正なノード%sを見つけました",CSTLString_c_str(if_statement->name));
		exit(1);
	}

	return output_children;

}
