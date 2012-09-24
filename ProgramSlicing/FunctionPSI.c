#include"FunctionPSI.h"

#include<stdio.h>
#include<stdlib.h>

#include"../Library/CSTLString.h"

#include"../ANSICInformation/ANSIC_CODE.h"

/**
関数定義のASTノードfunction_definitionから、関数に対するプログラムスライシングを抽出し、
プログラムスライシングリストexpr_slicing_listに追加する。

@param expr_slicing_list 追加先のプログラムスライシングリストexpr_slicing_list
@param function_definition 関数定義に関するASTノード
@param parent ノードを追加するときの親ノード

@return 追加した関数のスライシングへのアドレスを返す
 */
EXPR_SLICING *getFunctionPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *function_definition, EXPR_SLICING *parent){
	//新しいプログラムスライシングデータ
	EXPR_SLICING *new_expr_slicing = NULL;
	//関数名を取得した場合
	if(CSTLString_compare_with_char(function_definition->name,"function_definition_type_b") == 0){
		//定義リスト、依存リスト、子データリスト１、子データリスト２が初期状態にしておく
		ARRAY_OFFSET_LIST *target_variable = ARRAY_OFFSET_LIST_new();
		ARRAY_OFFSET_LIST *dependences =  ARRAY_OFFSET_LIST_new();
		EXPR_SLICING_LIST *children1 = EXPR_SLICING_LIST_new();
		EXPR_SLICING_LIST *children2 = EXPR_SLICING_LIST_new();

		//親ノードが自分のスライシングリストを指しているスライシングノードを生成し、スライシングリストに登録する
		EXPR_SLICING_LIST_push_back_ref(expr_slicing_list,
				new_EXPR_SLICING(EXPR_SLICING_LIST_size(expr_slicing_list) + 1, function_definition, target_variable,
						dependences, children1, children2, parent));

		//登録した末尾を取得する
		new_expr_slicing = EXPR_SLICING_LIST_data(EXPR_SLICING_LIST_rbegin(expr_slicing_list));

		//関数呼び出しからパラメータを探し出し、新しいプログラムスライシングの子ノードとして登録する
		getParameterPSI(new_expr_slicing, ASTLIST_ITERATOR_2(function_definition), ASTLIST_ITERATOR_2(function_definition));




	}else{
		fprintf(stderr,"不正なノード%sを見つけました",CSTLString_c_str(function_definition->name));
		exit(1);
	}

	return new_expr_slicing;
}

/**
パラメータリストに関するASTノードparameter_nodeから関数定義のプログラムスライシングリストexpr_slicing_listに格納していく

@param expr_slicing 関数定義のプログラムスライシング
@param parameter_node 各パラメータの定義リスト
@param basis_parameter_node パラメータを指すASTノード

@return なし
 */
void getParameterPSI(EXPR_SLICING *expr_slicing, AST *parameter_node, AST *basis_parameter_node){
	ASTListIterator ast_p;
	//もし、parameter_declaration_with_declaratorを見つけられたら以下の操作を行う
	if(CSTLString_compare_with_char(parameter_node->name, "parameter_declaration_with_declarator") == 0){
		//変数名・ポインタレベル・配列レベル
		CSTLString *variable_name = CSTLString_new();
		int pointer_level, array_level;

		//変数名を取得する
		getStringFromAST(variable_name, ASTLIST_ITERATOR_2(parameter_node));
		//変数名からポインタレベル・配列レベルを取得する
		getPointerLevelAndArrayLevel(variable_name, &pointer_level, &array_level);
		//変数名から、ポインタや配列を示す記号をすべて削除する
		deletePointerAndArraySynbol(variable_name);
		//定義リスト、依存リスト、子データリスト１、子データリスト２が初期状態にしておく
		ARRAY_OFFSET_LIST *target_variable = ARRAY_OFFSET_LIST_new();
		ARRAY_OFFSET_LIST *dependences =  ARRAY_OFFSET_LIST_new();
		EXPR_SLICING_LIST *children1 = EXPR_SLICING_LIST_new();
		EXPR_SLICING_LIST *children2 = EXPR_SLICING_LIST_new();

		//定義リストにパラメータの内容を登録する
		ARRAY_OFFSET_LIST_push_back_ref(target_variable, new_ARRAY_OFFSET(variable_name, basis_parameter_node, parameter_node, OFFSET_LIST_new(), pointer_level, array_level, 0, 0));

		EXPR_SLICING_LIST_push_back_ref(expr_slicing->children1, new_EXPR_SLICING(EXPR_SLICING_LIST_size(expr_slicing->children1) + 1, basis_parameter_node,target_variable, dependences, children1, children2, expr_slicing));

		//パラメータは常に使用するようにフラグを立てておく
		EXPR_SLICING_LIST_data(EXPR_SLICING_LIST_rbegin(expr_slicing->children1))->flag = 1;
	}else{
		//子ノードをたどる
		for(ast_p = ASTList_begin(parameter_node->children);
			ast_p != ASTList_end(parameter_node->children);
			ast_p = ASTList_next(ast_p)){
			getParameterPSI(expr_slicing, ASTList_data(ast_p), basis_parameter_node);
		}
	}
}
