#include"ProgramSlicing.h"

#include"FunctionPSI.h"
#include"ExpressionStatementPSI.h"
#include"DeclarationPSI.h"
#include"IfStatementPSI.h"
#include"ForStatementPSI.h"
#include"WhileStatementPSI.h"
#include"JumpStatementPSI.h"
#include"SwitchStatementPSI.h"
#include"LabeledStatementPSI.h"
#include"ReturnStatementPSI.h"

#include"../ANSICInformation/ANSIC_CODE.h"

#include<stdlib.h>

//データ依存関係の生成で、命令を見つけたかどうかを判定するためのフラグ
#define NOT_FIND 0					//0:命令を見つけていない
#define FIND_EXPR 1					//1:命令を見つけた

//データ依存関係の変数を見つけたかどうかのフラグ
#define NOT_FIND_DD 0
#define FIND_DD 1

//真か偽かの判定
#define TRUE 1
#define FALSE 0

/**
指定したプログラムＡＳＴノードから次のようなノードを取得し、
そこからスライシングを行うための構造体リストexpr_slicing_listを生成する。
function_definition_type_a、function_definition_type_b、
expression_statement、declaration_with_init、if_statement、ifelse_statement、switch_statement、while_statement、
dowhile_statement、for_statement_type_a、for_statement_type_b、for_statement_type_c、for_statement_type_d、
goto_statement、continue_statement、break_statement、return_statement、return_expr_statement
goto_labeled_statement、case_labeled_statement、default_labeled_statement

@param root 指定したプログラムＡＳＴノード
@param expr_slicing_list スライシングを行うための構造体
@param parent 親のスライシングデータ
@param vtlist 変数テーブルリスト
@param function_information_list 関数に関する情報のリスト
@return なし
*/
void *createStatementNodeList(AST *root, EXPR_SLICING_LIST *expr_slicing_list, EXPR_SLICING *parent,
		VARIABLE_TABLE_LIST *vtlist, FUNCTION_INFORMATION_LIST *function_information_list){
	ASTListIterator ast_p;
	EXPR_SLICING *new_expr_slicing;

	//function_definition_type_a、function_definition_type_bが出てきた場合
	if(CSTLString_compare_with_char(root->name,"function_definition_type_a") == 0 ||
		CSTLString_compare_with_char(root->name,"function_definition_type_b") == 0){
		//関数に関するプログラムスライシング情報を取得する
		new_expr_slicing = getFunctionPSI(expr_slicing_list, root, parent);

		//子ノードをたどる
		createStatementNodeList(ASTLIST_ITERATOR_3(root), new_expr_slicing->children1,
				new_expr_slicing,
				vtlist, function_information_list);


	}

	//expression_statementが出てきた場合
	else if(CSTLString_compare_with_char(root->name,"expression_statement") == 0 ){
		//重複防止の無視するASTリストを新規作成する
		ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();
		//式全般に関するプログラムスライシング情報を取得する
		getExpressionStatementPSI(expr_slicing_list, root, parent, vtlist, function_information_list, ignore_ast_list, root);

		//重複防止の無視するASTリストを削除する
		ASTPOINTER_LIST_clear(ignore_ast_list);
		ASTPOINTER_LIST_delete(ignore_ast_list);
	}

	//declaration_with_initが出てきた場合
	else if(CSTLString_compare_with_char(root->name,"declaration_with_init") == 0 ){
		//重複防止の無視するASTリストを新規作成する
		ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();
		//宣言全般に関するプログラムスライシング情報を取得する
		getDeclarationtPSI(expr_slicing_list, root, parent, vtlist, function_information_list, ignore_ast_list, root);


	}

	//if_statementが出てきた場合
	else if(CSTLString_compare_with_char(root->name,"if_statement") == 0){
		//重複防止の無視するASTリストを新規作成する
		ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();

		//if文に関するプログラムスライシング情報を取得する
		new_expr_slicing = getIfStatementPSI(expr_slicing_list, root, parent, vtlist, function_information_list, ignore_ast_list);

		//重複防止の無視するASTリストを削除する
		ASTPOINTER_LIST_clear(ignore_ast_list);
		ASTPOINTER_LIST_delete(ignore_ast_list);

		//ifブロック内の子ノードをたどる
		createStatementNodeList(ASTLIST_ITERATOR_5(root), new_expr_slicing->children1,
				new_expr_slicing,
				vtlist, function_information_list);
	}

	//ifelse_statementが出てきた場合
	else if(CSTLString_compare_with_char(root->name,"ifelse_statement") == 0){
		//重複防止の無視するASTリストを新規作成する
		ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();

		//ifelse文に関するプログラムスライシング情報を取得する
		new_expr_slicing = getIfStatementPSI(expr_slicing_list, root, parent, vtlist, function_information_list, ignore_ast_list);

		//重複防止の無視するASTリストを削除する
		ASTPOINTER_LIST_clear(ignore_ast_list);
		ASTPOINTER_LIST_delete(ignore_ast_list);

		//ifブロック内の子ノードをたどる
		createStatementNodeList(ASTLIST_ITERATOR_5(root), new_expr_slicing->children1,
				new_expr_slicing,
				vtlist, function_information_list);
		//elseブロック内の子ノードをたどる
		createStatementNodeList(ASTLIST_ITERATOR_7(root), new_expr_slicing->children2,
				new_expr_slicing,
				vtlist, function_information_list);
	}

	//switch_statementが出てきた場合
	else if(CSTLString_compare_with_char(root->name,"switch_statement") == 0 ){
		//重複防止の無視するASTリストを新規作成する
		ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();

		//switch文に関するプログラムスライシング情報を取得する
		new_expr_slicing = getSwicthStatementPSI(expr_slicing_list, root, parent, vtlist, function_information_list, ignore_ast_list);

		//重複防止の無視するASTリストを削除する
		ASTPOINTER_LIST_clear(ignore_ast_list);
		ASTPOINTER_LIST_delete(ignore_ast_list);

		//switchブロック内の子ノードをたどる
		createStatementNodeList(ASTLIST_ITERATOR_5(root), new_expr_slicing->children1,
				new_expr_slicing,
				vtlist, function_information_list);
	}

	//while_statementが出てきた場合
	else if(CSTLString_compare_with_char(root->name,"while_statement") == 0 ){
		//重複防止の無視するASTリストを新規作成する
		ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();

		//while文に関するプログラムスライシング情報を取得する
		new_expr_slicing = getWhileStatementPSI(expr_slicing_list, root, parent, vtlist, function_information_list, ignore_ast_list);

		//重複防止の無視するASTリストを削除する
		ASTPOINTER_LIST_clear(ignore_ast_list);
		ASTPOINTER_LIST_delete(ignore_ast_list);

		//whileブロック内の子ノードをたどる
		createStatementNodeList(ASTLIST_ITERATOR_5(root), new_expr_slicing->children1,
				new_expr_slicing,
				vtlist, function_information_list);
	}

	//dowhile_statementが出てきた場合
	else if(CSTLString_compare_with_char(root->name,"dowhile_statement") == 0 ){
		//重複防止の無視するASTリストを新規作成する
		ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();

		//dowhile文に関するプログラムスライシング情報を取得する
		new_expr_slicing = getWhileStatementPSI(expr_slicing_list, root, parent, vtlist, function_information_list, ignore_ast_list);

		//重複防止の無視するASTリストを削除する
		ASTPOINTER_LIST_clear(ignore_ast_list);
		ASTPOINTER_LIST_delete(ignore_ast_list);

		//doブロック内の子ノードをたどる
		createStatementNodeList(ASTLIST_ITERATOR_2(root), new_expr_slicing->children1,
				new_expr_slicing,
				vtlist, function_information_list);
	}

	//for_statement_type_a、for_statement_type_bが出てきた場合
	else if(CSTLString_compare_with_char(root->name,"for_statement_type_a") == 0 ){
		//重複防止の無視するASTリストを新規作成する
		ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();

		//for文に関するプログラムスライシング情報を取得する
		new_expr_slicing = getForStatementPSI(expr_slicing_list, root, parent, vtlist, function_information_list, ignore_ast_list);

		//重複防止の無視するASTリストを削除する
		ASTPOINTER_LIST_clear(ignore_ast_list);
		ASTPOINTER_LIST_delete(ignore_ast_list);

		//forブロック内の子ノードをたどる
		createStatementNodeList(ASTLIST_ITERATOR_6(root), new_expr_slicing->children1,
				new_expr_slicing,
				vtlist, function_information_list);

	}else if(CSTLString_compare_with_char(root->name,"for_statement_type_b") == 0 ){
		//重複防止の無視するASTリストを新規作成する
		ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();

		//for文に関するプログラムスライシング情報を取得する
		new_expr_slicing = getForStatementPSI(expr_slicing_list, root, parent, vtlist, function_information_list, ignore_ast_list);

		//重複防止の無視するASTリストを削除する
		ASTPOINTER_LIST_clear(ignore_ast_list);
		ASTPOINTER_LIST_delete(ignore_ast_list);

		//forブロック内の子ノードをたどる
		createStatementNodeList(ASTLIST_ITERATOR_7(root), new_expr_slicing->children1,
				new_expr_slicing,
				vtlist, function_information_list);
	}

	//for_statement_type_c、for_statement_type_dが出てきた場合、望ましくない処理としてエラーを出力し、強制終了させる
	else if(CSTLString_compare_with_char(root->name,"for_statement_type_c") == 0 ||
			CSTLString_compare_with_char(root->name,"for_statement_type_d") == 0 ){
		fprintf(stderr,"#%s#:%d:Don't Declaration In For Statement!!", getFileName(), ASTLIST_ITERATOR_1(root)->line);
		exit(1);
	}

	//goto_statementが出てきた場合
	else if(CSTLString_compare_with_char(root->name,"goto_statement") == 0 ){
		//goto文に関するプログラムスライシング情報を取得する
		getJumpStatementPSI(expr_slicing_list, root, parent);
	}

	//continue_statementが出てきた場合
	else if(CSTLString_compare_with_char(root->name,"continue_statement") == 0 ){
		//continue文に関するプログラムスライシング情報を取得する
		getJumpStatementPSI(expr_slicing_list, root, parent);
	}

	//break_statementが出てきた場合
	else if(CSTLString_compare_with_char(root->name,"break_statement") == 0 ){
		//break文に関するプログラムスライシング情報を取得する
		getJumpStatementPSI(expr_slicing_list, root, parent);
	}
	//return_statement、return_expr_statementが出てきた場合
	else if(CSTLString_compare_with_char(root->name,"return_statement") == 0 ||
		CSTLString_compare_with_char(root->name,"return_expr_statement") == 0){
		//重複防止の無視するASTリストを新規作成する
		ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();

		//return文に関するプログラムスライシング情報を取得する
		getReturnStatementPSI(expr_slicing_list, root, parent, vtlist, function_information_list, ignore_ast_list);

		//重複防止の無視するASTリストを削除する
		ASTPOINTER_LIST_clear(ignore_ast_list);
		ASTPOINTER_LIST_delete(ignore_ast_list);
	}
	//goto_labeled_statement、default_labeled_statementが出てきた場合
	else if(CSTLString_compare_with_char(root->name,"goto_labeled_statement") == 0 ||
			CSTLString_compare_with_char(root->name,"default_labeled_statement") == 0 ){
		//重複防止の無視するASTリストを新規作成する
		ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();

		//gotoラベル文やdefaultラベル文に関するプログラムスライシング情報を取得する
		new_expr_slicing = getLabeledStatementPSI(expr_slicing_list, root, parent,
				vtlist, function_information_list, ignore_ast_list);

		//重複防止の無視するASTリストを削除する
		ASTPOINTER_LIST_clear(ignore_ast_list);
		ASTPOINTER_LIST_delete(ignore_ast_list);

		//gotoラベル文やdefaultラベル文後のstatementの子ノードをたどる
		createStatementNodeList(ASTLIST_ITERATOR_3(root), new_expr_slicing->children1,
				new_expr_slicing,
				vtlist, function_information_list);
	}
	//case_labeled_statementが出てきた場合
	else if(CSTLString_compare_with_char(root->name,"case_labeled_statement") == 0 ){
		//重複防止の無視するASTリストを新規作成する
		ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();

		//caseラベル文に関するプログラムスライシング情報を取得する
		new_expr_slicing = getLabeledStatementPSI(expr_slicing_list, root, parent,
				vtlist, function_information_list, ignore_ast_list);

		//重複防止の無視するASTリストを削除する
		ASTPOINTER_LIST_clear(ignore_ast_list);
		ASTPOINTER_LIST_delete(ignore_ast_list);

		//caseラベル文後のstatementの子ノードをたどる
		createStatementNodeList(ASTLIST_ITERATOR_4(root), new_expr_slicing->children1,
				new_expr_slicing,
				vtlist, function_information_list);
	}
	else{
		//子ノードをたどる
		for(ast_p = ASTList_begin(root->children);
			ast_p != ASTList_end(root->children);
			ast_p = ASTList_next(ast_p)){
				createStatementNodeList(ASTList_data(ast_p), expr_slicing_list, parent, vtlist, function_information_list);
		}
	}
}

/**
createDD_listの内部処理である。対象の命令parent_expr_slicingの範囲で、
依存関係の変数に関係する命令を見つけたら、その命令をデータ依存関係リストに追加する。

@param parent_expr_slicing 対象の命令範囲parent_expr_slicing
@param expr_slicing 調べる対象の命令
@param exception_variable_list 除外する変数リスト
@param invest_flag 調べるかどうかのフラグ　１:有効　０：無効

@return なし
 */
void createDD_list_Internal(EXPR_SLICING *parent_expr_slicing, EXPR_SLICING *expr_slicing, ARRAY_OFFSET_LIST *exception_variable_list, int *find_expr_flag){
	EXPR_SLICING_LISTIterator e_i;
	ARRAY_OFFSET_LISTIterator a_i;
	int find_flag = NOT_FIND;
	//データ依存関係の命令の候補
	DD_INFORMATION *candidate_dd_info = NULL;
	DD_INFORMATION_LIST *candidate_dd_list = DD_INFORMATION_LIST_new();
	//繰り返し系命令の場合は以下の処理を行う
	if(CSTLString_compare_with_char(parent_expr_slicing->expression->name, "for_statement_type_a") == 0 ||
		CSTLString_compare_with_char(parent_expr_slicing->expression->name, "for_statement_type_b") == 0 ||
		CSTLString_compare_with_char(parent_expr_slicing->expression->name, "while_statement") == 0 ||
		CSTLString_compare_with_char(parent_expr_slicing->expression->name, "dowhile_statement") == 0 )
	{
		int find_expr_in_iteration_flag = FALSE;
		//children1を探索し、該当の命令が見つかるかどうかを調べる
		for(e_i = EXPR_SLICING_LIST_rbegin(parent_expr_slicing->children1);
			e_i != EXPR_SLICING_LIST_rend(parent_expr_slicing->children1);
			e_i = EXPR_SLICING_LIST_prev(e_i)){

			if(EXPR_SLICING_LIST_data(e_i) == expr_slicing){
				find_expr_in_iteration_flag = TRUE;

				break;
			}

		}
		//もし、for文内で該当の命令が見つかった場合
		if(find_expr_in_iteration_flag){

			*find_expr_flag = FIND_EXPR;

			//children1を逆順に探索する
			for(;
				e_i != EXPR_SLICING_LIST_rend(parent_expr_slicing->children1);
				e_i = EXPR_SLICING_LIST_prev(e_i)){

				createDD_list_Internal(EXPR_SLICING_LIST_data(e_i), expr_slicing, exception_variable_list, find_expr_flag);

				find_flag = NOT_FIND_DD;
				if(EXPR_SLICING_LIST_data(e_i) != expr_slicing){
					for(a_i = ARRAY_OFFSET_LIST_begin(expr_slicing->dependences);
						a_i != ARRAY_OFFSET_LIST_end(expr_slicing->dependences);
						a_i = ARRAY_OFFSET_LIST_next(a_i)){

						if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable,
								ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL &&
								searchARRAY_OFFSET_LIST(exception_variable_list,
								ARRAY_OFFSET_LIST_data(a_i)->variable_name) == NULL){
							find_flag = FIND_DD;
							break;
						}
					}

					if(find_flag == FIND_DD){
						//もし、データ依存関係に関係する変数とかぶっているものが見つからなければ、追加する
						if(searchDD(ARRAY_OFFSET_LIST_data(a_i)->variable_name, candidate_dd_list, &candidate_dd_info) == 0){
							DD_INFORMATION_LIST_push_back_ref(candidate_dd_list, new_DD_INFORMATION(ARRAY_OFFSET_LIST_data(a_i)->variable_name,EXPR_SLICING_LIST_data(e_i)));
						}
					}
				}

			}
			//children1を逆順に探索する
			for(e_i = EXPR_SLICING_LIST_rbegin(parent_expr_slicing->children1);
				EXPR_SLICING_LIST_data(e_i) != expr_slicing;
				e_i = EXPR_SLICING_LIST_prev(e_i)){

				createDD_list_Internal(EXPR_SLICING_LIST_data(e_i), expr_slicing, exception_variable_list, find_expr_flag);

				find_flag = NOT_FIND_DD;
				if(EXPR_SLICING_LIST_data(e_i) != expr_slicing){
					for(a_i = ARRAY_OFFSET_LIST_begin(expr_slicing->dependences);
						a_i != ARRAY_OFFSET_LIST_end(expr_slicing->dependences);
						a_i = ARRAY_OFFSET_LIST_next(a_i)){

						if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable,
								ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL &&
								searchARRAY_OFFSET_LIST(exception_variable_list,
								ARRAY_OFFSET_LIST_data(a_i)->variable_name) == NULL){
							find_flag = FIND_DD;
							break;
						}
					}

					if(find_flag == FIND_DD){
						//もし、データ依存関係に関係する変数とかぶっているものが見つからなければ、追加する
						if(searchDD(ARRAY_OFFSET_LIST_data(a_i)->variable_name, candidate_dd_list, &candidate_dd_info) == 0){
							DD_INFORMATION_LIST_push_back_ref(candidate_dd_list, new_DD_INFORMATION(ARRAY_OFFSET_LIST_data(a_i)->variable_name,EXPR_SLICING_LIST_data(e_i)));
						}
					}
				}

			}
			//データ依存関係のリストを追加する
			if(DD_INFORMATION_LIST_size(candidate_dd_list) != 0){
				DD_INFORMATION_LIST_splice(expr_slicing->dd_list, DD_INFORMATION_LIST_end(expr_slicing->dd_list),
						candidate_dd_list, DD_INFORMATION_LIST_begin(candidate_dd_list), DD_INFORMATION_LIST_end(candidate_dd_list));
			}


		}
		//そうでない場合は普通に逆順に探索する
		else{
			for(e_i = EXPR_SLICING_LIST_rbegin(parent_expr_slicing->children1);
				e_i != EXPR_SLICING_LIST_rend(parent_expr_slicing->children1);
				e_i = EXPR_SLICING_LIST_prev(e_i)){

				createDD_list_Internal(EXPR_SLICING_LIST_data(e_i), expr_slicing, exception_variable_list, find_expr_flag);

				if(*find_expr_flag == NOT_FIND){
					if(EXPR_SLICING_LIST_data(e_i) == expr_slicing){
						*find_expr_flag = FIND_EXPR;
					}
				}
				//調べている命令が宣言か引数宣言であれば、
				//対象の命令の依存関係や対象の変数にデータ依存関係があるかどうか調べる
				else if((*find_expr_flag != NOT_FIND && CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "declaration_with_init") == 0) ||
						CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "declarator") == 0){
					for(a_i = ARRAY_OFFSET_LIST_begin(expr_slicing->target_variable);
						a_i != ARRAY_OFFSET_LIST_end(expr_slicing->target_variable);
						a_i = ARRAY_OFFSET_LIST_next(a_i)){

						if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable,
								ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL){
							DD_INFORMATION_LIST_push_back_ref(expr_slicing->dd_list, new_DD_INFORMATION(ARRAY_OFFSET_LIST_data(a_i)->variable_name, EXPR_SLICING_LIST_data(e_i)));
							find_flag = FIND_DD;

							break;
						}
					}
					for(a_i = ARRAY_OFFSET_LIST_begin(expr_slicing->dependences);
						a_i != ARRAY_OFFSET_LIST_end(expr_slicing->dependences);
						a_i = ARRAY_OFFSET_LIST_next(a_i)){

						if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable,
								ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL){
							DD_INFORMATION_LIST_push_back_ref(expr_slicing->dd_list, new_DD_INFORMATION(ARRAY_OFFSET_LIST_data(a_i)->variable_name, EXPR_SLICING_LIST_data(e_i)));
							find_flag = FIND_DD;

							break;
						}
					}
				}
				//宣言や引数宣言でなければ、対象の直前の命令１つに対してデータ依存関係を結ぶ
				else{
					for(a_i = ARRAY_OFFSET_LIST_begin(expr_slicing->dependences);
						a_i != ARRAY_OFFSET_LIST_end(expr_slicing->dependences);
						a_i = ARRAY_OFFSET_LIST_next(a_i)){
						//依存関係の変数が、対象の変数に存在し、除外リストに載っていない場合
						if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable,
								ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL &&
								searchARRAY_OFFSET_LIST(exception_variable_list,
								ARRAY_OFFSET_LIST_data(a_i)->variable_name) == NULL){

							//ダブりが存在しない場合は候補として追加する
							if(searchDD(ARRAY_OFFSET_LIST_data(a_i)->variable_name, candidate_dd_list, &candidate_dd_info) == 0){
								DD_INFORMATION_LIST_push_back_ref(candidate_dd_list, new_DD_INFORMATION(ARRAY_OFFSET_LIST_data(a_i)->variable_name, EXPR_SLICING_LIST_data(e_i)));
								find_flag = FIND_DD;
								break;
							}
						}
					}
				}

			}
			//データ依存関係のリストを追加する
			if(DD_INFORMATION_LIST_size(candidate_dd_list) != 0){
				DD_INFORMATION_LIST_splice(expr_slicing->dd_list, DD_INFORMATION_LIST_end(expr_slicing->dd_list),
						candidate_dd_list, DD_INFORMATION_LIST_begin(candidate_dd_list), DD_INFORMATION_LIST_end(candidate_dd_list));
			}
		}

	//繰り返し命令でない場合は、以下の処理を実行する
	}else{
		//children2から逆順に探索する
		for(e_i = EXPR_SLICING_LIST_rbegin(parent_expr_slicing->children2);
			e_i != EXPR_SLICING_LIST_rend(parent_expr_slicing->children2);
			e_i = EXPR_SLICING_LIST_prev(e_i)){

			createDD_list_Internal(EXPR_SLICING_LIST_data(e_i), expr_slicing, exception_variable_list, find_expr_flag);

			if(*find_expr_flag == NOT_FIND){
				if(EXPR_SLICING_LIST_data(e_i) == expr_slicing){
					*find_expr_flag = FIND_EXPR;
				}
			}
			//調べている命令が宣言か引数宣言であれば、
			//対象の命令の依存関係や対象の変数にデータ依存関係があるかどうか調べる
			else if((*find_expr_flag != NOT_FIND && CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "declaration_with_init") == 0) ||
					CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "declarator") == 0){
				for(a_i = ARRAY_OFFSET_LIST_begin(expr_slicing->target_variable);
					a_i != ARRAY_OFFSET_LIST_end(expr_slicing->target_variable);
					a_i = ARRAY_OFFSET_LIST_next(a_i)){

					if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable,
							ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL){
						DD_INFORMATION_LIST_push_back_ref(expr_slicing->dd_list, new_DD_INFORMATION(ARRAY_OFFSET_LIST_data(a_i)->variable_name, EXPR_SLICING_LIST_data(e_i)));
						find_flag = FIND_DD;
						break;
					}
				}
				for(a_i = ARRAY_OFFSET_LIST_begin(expr_slicing->dependences);
					a_i != ARRAY_OFFSET_LIST_end(expr_slicing->dependences);
					a_i = ARRAY_OFFSET_LIST_next(a_i)){

					if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable,
							ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL){
						DD_INFORMATION_LIST_push_back_ref(expr_slicing->dd_list, new_DD_INFORMATION(ARRAY_OFFSET_LIST_data(a_i)->variable_name, EXPR_SLICING_LIST_data(e_i)));
						find_flag = FIND_DD;
						break;
					}
				}
			}
			//宣言や引数宣言でなければ、対象の直前の命令１つに対してデータ依存関係を結ぶ
			/*else if(find_flag == NOT_FIND_DD){

				for(a_i = ARRAY_OFFSET_LIST_begin(expr_slicing->dependences);
					a_i != ARRAY_OFFSET_LIST_end(expr_slicing->dependences);
					a_i = ARRAY_OFFSET_LIST_next(a_i)){

					if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable,
							ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL &&
							searchARRAY_OFFSET_LIST(exception_variable_list,
							ARRAY_OFFSET_LIST_data(a_i)->variable_name) == NULL){
						DD_INFORMATION_LIST_push_back_ref(expr_slicing->dd_list, new_DD_INFORMATION(ARRAY_OFFSET_LIST_data(a_i)->variable_name, EXPR_SLICING_LIST_data(e_i)));
						find_flag = FIND_DD;
						break;
					}
				}
			}*/
			//宣言や引数宣言でなければ、対象の直前の命令１つに対してデータ依存関係を結ぶ
			else{
				for(a_i = ARRAY_OFFSET_LIST_begin(expr_slicing->dependences);
					a_i != ARRAY_OFFSET_LIST_end(expr_slicing->dependences);
					a_i = ARRAY_OFFSET_LIST_next(a_i)){
					//依存関係の変数が、対象の変数に存在し、除外リストに載っていない場合
					if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable,
							ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL &&
							searchARRAY_OFFSET_LIST(exception_variable_list,
							ARRAY_OFFSET_LIST_data(a_i)->variable_name) == NULL){

						//ダブりが存在しない場合は候補として追加する
						if(searchDD(ARRAY_OFFSET_LIST_data(a_i)->variable_name, candidate_dd_list, &candidate_dd_info) == 0){
							DD_INFORMATION_LIST_push_back_ref(candidate_dd_list, new_DD_INFORMATION(ARRAY_OFFSET_LIST_data(a_i)->variable_name, EXPR_SLICING_LIST_data(e_i)));
							find_flag = FIND_DD;
							break;
						}
					}
				}
			}

		}

		find_flag = NOT_FIND_DD;

		//次にchildren1を逆順に探索する
		for(e_i = EXPR_SLICING_LIST_rbegin(parent_expr_slicing->children1);
			e_i != EXPR_SLICING_LIST_rend(parent_expr_slicing->children1);
			e_i = EXPR_SLICING_LIST_prev(e_i)){

			createDD_list_Internal(EXPR_SLICING_LIST_data(e_i), expr_slicing, exception_variable_list, find_expr_flag);
			//もし、対象の命令を見つかっていない状態の場合は、対象の命令を見つけるまで探す
			if(*find_expr_flag == NOT_FIND){
				if(EXPR_SLICING_LIST_data(e_i) == expr_slicing){
					*find_expr_flag = FIND_EXPR;
				}
			}
			//調べている命令が宣言か引数宣言であれば、
			//対象の命令の依存関係や対象の変数にデータ依存関係があるかどうか調べる
			else if((*find_expr_flag != NOT_FIND && CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "declaration_with_init") == 0) ||
					CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "declarator") == 0){
				for(a_i = ARRAY_OFFSET_LIST_begin(expr_slicing->target_variable);
					a_i != ARRAY_OFFSET_LIST_end(expr_slicing->target_variable);
					a_i = ARRAY_OFFSET_LIST_next(a_i)){

					if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable,
							ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL){
						DD_INFORMATION_LIST_push_back_ref(expr_slicing->dd_list, new_DD_INFORMATION(ARRAY_OFFSET_LIST_data(a_i)->variable_name, EXPR_SLICING_LIST_data(e_i)));
						find_flag = FIND_DD;
						break;
					}
				}
				for(a_i = ARRAY_OFFSET_LIST_begin(expr_slicing->dependences);
					a_i != ARRAY_OFFSET_LIST_end(expr_slicing->dependences);
					a_i = ARRAY_OFFSET_LIST_next(a_i)){

					if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable,
							ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL){
						DD_INFORMATION_LIST_push_back_ref(expr_slicing->dd_list, new_DD_INFORMATION(ARRAY_OFFSET_LIST_data(a_i)->variable_name, EXPR_SLICING_LIST_data(e_i)));
						find_flag = FIND_DD;
						break;
					}
				}
			}
			//宣言や引数宣言でなければ、対象の直前の命令１つに対してデータ依存関係を結ぶ
			else{
				for(a_i = ARRAY_OFFSET_LIST_begin(expr_slicing->dependences);
					a_i != ARRAY_OFFSET_LIST_end(expr_slicing->dependences);
					a_i = ARRAY_OFFSET_LIST_next(a_i)){
					//依存関係の変数が、対象の変数に存在し、除外リストに載っていない場合
					if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable,
							ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL &&
							searchARRAY_OFFSET_LIST(exception_variable_list,
							ARRAY_OFFSET_LIST_data(a_i)->variable_name) == NULL){

						//ダブりが存在しない場合は候補として追加する
						if(searchDD(ARRAY_OFFSET_LIST_data(a_i)->variable_name, candidate_dd_list, &candidate_dd_info) == 0){
							DD_INFORMATION_LIST_push_back_ref(candidate_dd_list, new_DD_INFORMATION(ARRAY_OFFSET_LIST_data(a_i)->variable_name, EXPR_SLICING_LIST_data(e_i)));
							find_flag = FIND_DD;
							break;
						}
					}
				}
			}

		}

		//データ依存関係のリストを追加する
		if(DD_INFORMATION_LIST_size(candidate_dd_list) != 0){
			DD_INFORMATION_LIST_splice(expr_slicing->dd_list, DD_INFORMATION_LIST_end(expr_slicing->dd_list),
					candidate_dd_list, DD_INFORMATION_LIST_begin(candidate_dd_list), DD_INFORMATION_LIST_end(candidate_dd_list));
		}
	}

}
/**
指定した対象の命令とグローバル変数宣言に関してデータ依存関係があるかどうか調べる。
存在すれば、グローバル変数宣言に対して、データ依存関係として結びつける

@param expr_slicing 指定した対象の命令
@param program_expr_slicing_list プログラム全体のスライシングリスト

@return なし
 */

void createDD_list_in_global(EXPR_SLICING *expr_slicing, EXPR_SLICING_LIST *program_expr_slicing_list){

	EXPR_SLICING_LISTIterator e_i;

	ARRAY_OFFSET_LISTIterator a_i;

	int find_flag;

	//プログラム全体のスライシングリストからグローバル変数宣言が存在するかどうか探索する
	for(e_i = EXPR_SLICING_LIST_begin(program_expr_slicing_list);
		e_i != EXPR_SLICING_LIST_end(program_expr_slicing_list);
		e_i = EXPR_SLICING_LIST_next(e_i)){

		find_flag = 0;

		//スライシング情報の関わっているASTノード名がdeclaration_with_initである、すなわちグローバル変数宣言である場合
		if(CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "declaration_with_init") == 0){
			//グローバル変数宣言の対象の変数について調べる
			for(a_i = ARRAY_OFFSET_LIST_begin(EXPR_SLICING_LIST_data(e_i)->target_variable);
				a_i != ARRAY_OFFSET_LIST_end(EXPR_SLICING_LIST_data(e_i)->target_variable);
				a_i = ARRAY_OFFSET_LIST_next(a_i)){

				//指定された命令の対象の変数か依存関係が、グローバル変数宣言に対してデータ依存関係がある場合
				if(searchARRAY_OFFSET_LIST(expr_slicing->target_variable, ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL ||
						searchARRAY_OFFSET_LIST(expr_slicing->dependences, ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL){

					//もし、データ依存関係からグローバル変数名と同じである、ローカル変数宣言が存在しない場合、
					//グローバル変数宣言をデータ依存関係として追加する
					if(searchDeclarationDD(ARRAY_OFFSET_LIST_data(a_i)->variable_name, expr_slicing) == 0){
						DD_INFORMATION_LIST_push_back_ref(expr_slicing->dd_list, new_DD_INFORMATION(ARRAY_OFFSET_LIST_data(a_i)->variable_name, EXPR_SLICING_LIST_data(e_i)));
						break;
					}
				}
			}
		}
	}

}
/**
指定した対象の命令に対して、データ依存関係の命令を探し、その命令を結びつける。

@param expr_slicing 指定した対象の命令

@return なし
 */
void createDD_list(EXPR_SLICING *expr_slicing){
	//対象の命令に関する対象範囲を設定する
	EXPR_SLICING *parent_expr_slicing = expr_slicing->parent;

	ARRAY_OFFSET_LIST *exception_variable_list = ARRAY_OFFSET_LIST_new();
	//ルートノードまたは、関数呼び出しになるまで親を再帰的に呼び出す
	while(parent_expr_slicing != NULL && CSTLString_compare_with_char(parent_expr_slicing->expression->name, "function_definition_type_a") != 0
			&& CSTLString_compare_with_char(parent_expr_slicing->expression->name, "function_definition_type_b") != 0){
		//もし、for文を見つけた場合は、for文内の対象の変数をデータ依存関係の除外リストに入れる
		if(CSTLString_compare_with_char(parent_expr_slicing->expression->name, "for_statement_type_a") == 0 ||
				CSTLString_compare_with_char(parent_expr_slicing->expression->name, "for_statement_type_a") == 0){
			copyArrayOffsetList(parent_expr_slicing->target_variable, exception_variable_list, 0);
		}
		parent_expr_slicing = parent_expr_slicing->parent;

	}

	if(parent_expr_slicing != NULL && ( CSTLString_compare_with_char(parent_expr_slicing->expression->name, "function_definition_type_a") != 0
			|| CSTLString_compare_with_char(parent_expr_slicing->expression->name, "function_definition_type_b") != 0) ){
		int invest_flag = NOT_FIND;
		//この関数の範囲で逆順で再帰的に探索し、依存関係の変数に関係する命令を見つけたら、その命令をデータ依存関係リストに追加する。
		createDD_list_Internal(parent_expr_slicing, expr_slicing, exception_variable_list, &invest_flag);
	}

	ARRAY_OFFSET_LIST_delete(exception_variable_list);
}

/**
プログラムスライシングリスト中のすべての命令に対し、データ依存関係の命令を探し、その命令を結びつける。


@param expr_slicing_list 指定した対象のプログラムスライシングリスト
@param function_information_list 関数に関する情報リスト
@param program_expr_slicing_list プログラム全体へのスライシングリスト
@return なし
 */
void createDD_listAll(EXPR_SLICING_LIST *expr_slicing_list, FUNCTION_INFORMATION_LIST *function_information_list,
		EXPR_SLICING_LIST *program_expr_slicing_list){
	EXPR_SLICING_LISTIterator e_i;
	//対象の命令に関する対象範囲を設定する
	//children1を探索し、該当の命令が見つかるかどうかを調べる
	for(e_i = EXPR_SLICING_LIST_begin(expr_slicing_list);
		e_i != EXPR_SLICING_LIST_end(expr_slicing_list);
		e_i = EXPR_SLICING_LIST_next(e_i)){

		//もし、対象の変数や依存関係の変数が存在する命令ならば、データ依存関係を探し、その命令に結びつける
		if(ARRAY_OFFSET_LIST_size(EXPR_SLICING_LIST_data(e_i)->target_variable) > 0 ||
				ARRAY_OFFSET_LIST_size(EXPR_SLICING_LIST_data(e_i)->dependences) > 0){

			//関数呼出から呼び出している関数へのデータ依存関係を探し出し、その命令を結びつける
			createDD_list_in_Function(EXPR_SLICING_LIST_data(e_i), program_expr_slicing_list,
					function_information_list);

			//対象の命令に対するデータ依存関係を探し出し、その命令を結びつける
			createDD_list(EXPR_SLICING_LIST_data(e_i));

			//グローバル変数に対して、データ依存関係を探し出し、その命令を結びつける
			createDD_list_in_global(EXPR_SLICING_LIST_data(e_i), program_expr_slicing_list);
		}

		createDD_listAll(EXPR_SLICING_LIST_data(e_i)->children1,function_information_list, program_expr_slicing_list);
		createDD_listAll(EXPR_SLICING_LIST_data(e_i)->children2,function_information_list, program_expr_slicing_list);
	}
}

/**
関数呼び出しから、呼び出している関数へのデータ依存関係を生成する。

@param expr_slicing 関数呼び出しが含まれている処理名
@param expr_slicing_list プログラム全体のプログラムスライシングリスト
@param function_information_list 関数に関する情報リスト

@return なし
 */
void createDD_list_in_Function(EXPR_SLICING *expr_slicing, EXPR_SLICING_LIST *expr_slicing_list,
		FUNCTION_INFORMATION_LIST *function_information_list){

	ARRAY_OFFSET_LISTIterator a_i;
	EXPR_SLICING *search_expr_slicing;
	CSTLString *target_function_name = CSTLString_new();
	CSTLString *argument_number_str = CSTLString_new();
	int argument_number;
	CSTLString *argument_name = CSTLString_new();

	FUNCTION_INFORMATION *function_information;
	PARAM_INFORMATION_LISTIterator p_i;
	int p_counter;
	//expr_slicingの対象の変数および依存関係をすべて探す
	for(a_i = ARRAY_OFFSET_LIST_begin(expr_slicing->target_variable);
		a_i != ARRAY_OFFSET_LIST_end(expr_slicing->target_variable);
		a_i = ARRAY_OFFSET_LIST_next(a_i)){

		//もし、対象の変数が関数呼び出しの引数の場合
		if(CSTLString_compare_with_char(ARRAY_OFFSET_LIST_data(a_i)->target_statement->name, "call_function") == 0){
			//関数名を取り出す
			getStringFromAST(target_function_name, ASTLIST_ITERATOR_1(ARRAY_OFFSET_LIST_data(a_i)->target_statement));

			//expr_slicing_listから、関数呼び出しに対応する関数へのプログラムスライシング情報を取り出す
			search_expr_slicing = searchFunctionPSI(target_function_name, expr_slicing_list);

			//関数呼び出しに対応する関数へのプログラムスライシング情報の取り出しに成功した場合
			if(search_expr_slicing != NULL){

				//引数番号を取り出す
				CSTLString_assign(argument_number_str, CSTLString_c_str(ARRAY_OFFSET_LIST_data(a_i)->variable_name));
				CSTLString_erase(argument_number_str, 0, CSTLString_find(argument_number_str, "#", 0) + 1);
				argument_number = atoi(CSTLString_c_str(argument_number_str));

				//関数呼び出しのASTノードから、仮引数名を取り出す
				function_information = searchFUNCTION_INFORMATION(target_function_name, function_information_list);

				for(p_counter = 0, p_i = PARAM_INFORMATION_LIST_begin(function_information->param_information_list);
					p_i != PARAM_INFORMATION_LIST_end(function_information->param_information_list);
					p_counter++, p_i = PARAM_INFORMATION_LIST_next(p_i)){
					if(p_counter == argument_number){
						CSTLString_assign(argument_name, CSTLString_c_str(PARAM_INFORMATION_LIST_data(p_i)->param_name));
						break;
					}
				}

				//その関数へのスライシングに対して、仮引数名に対するデータ依存関係をexpr_slicingに設定する
				createDD_list_in_argument(expr_slicing, argument_name, search_expr_slicing);
			}
		}
	}

	CSTLString_delete(target_function_name);
	CSTLString_delete(argument_number_str);
	CSTLString_delete(argument_name);
}

/**
関数へのスライシング情報に対して、仮引数名が依存関係として用いている命令を探し、それを指定したプログラムスライシング
のデータ依存関係として追加する。

@param expr_slicing 関数呼び出しのプログラムスライシング
@param argument_name 仮引数名
@param function_definition_expr_slicing 関数宣言へのプログラムスライシング

@return なし
 */
void createDD_list_in_argument(EXPR_SLICING *expr_slicing, CSTLString *argument_name,
		EXPR_SLICING *function_definition_expr_slicing){

	EXPR_SLICING_LISTIterator e_i;

	CSTLString *target_variable;
	DD_INFORMATION *dd_information;

	//expr_slicingのchildren2を末尾から探索する
	for(e_i = EXPR_SLICING_LIST_rbegin(function_definition_expr_slicing->children2);
		e_i != EXPR_SLICING_LIST_rend(function_definition_expr_slicing->children2);
		e_i = EXPR_SLICING_LIST_prev(e_i)){

		createDD_list_in_argument(expr_slicing, argument_name, EXPR_SLICING_LIST_data(e_i));

		//もし、仮引数名が用いられている命令を見つけたら、expr_slicingのデータ依存関係として追加する
		if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable, argument_name) != NULL){

			target_variable = CSTLString_new();
			CSTLString_assign(target_variable, CSTLString_c_str(argument_name));

			dd_information = new_DD_INFORMATION(target_variable, EXPR_SLICING_LIST_data(e_i));
			DD_INFORMATION_LIST_push_back_ref(expr_slicing->dd_list, dd_information);
			break;
		}
	}
	//expr_slicingのchildren1を末尾から探索する
	for(e_i = EXPR_SLICING_LIST_rbegin(function_definition_expr_slicing->children1);
		e_i != EXPR_SLICING_LIST_rend(function_definition_expr_slicing->children1);
		e_i = EXPR_SLICING_LIST_prev(e_i)){

		createDD_list_in_argument(expr_slicing, argument_name, EXPR_SLICING_LIST_data(e_i));

		//もし、仮引数名が用いられている命令を見つけたら、expr_slicingのデータ依存関係として追加する
		if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable, argument_name) != NULL){
			target_variable = CSTLString_new();
			CSTLString_assign(target_variable, CSTLString_c_str(argument_name));

			dd_information = new_DD_INFORMATION(target_variable, EXPR_SLICING_LIST_data(e_i));
			DD_INFORMATION_LIST_push_back_ref(expr_slicing->dd_list, dd_information);
			break;
		}

	}

}

/**
指定した識別子の命令に対してスタティックスライシング処理を行う。

@param expr_slicing 指定した命令に対するプログラムスライシング情報

@return なし

*/
void staticSlicing(EXPR_SLICING *expr_slicing){
	//もし、命令がNULLではなく、使用するかどうかのフラグが立っていなかった場合、そのフラグを立てる
	if(expr_slicing != NULL && expr_slicing->flag == 0){
		DD_INFORMATION_LISTIterator dd_e_i;
		//この命令を使用する
		expr_slicing->flag = 1;
		//親をたどる
		staticSlicing(expr_slicing->parent);

		//データ依存関係リストに従って命令をたどる
		for(dd_e_i = DD_INFORMATION_LIST_rbegin(expr_slicing->dd_list);
				dd_e_i != DD_INFORMATION_LIST_rend(expr_slicing->dd_list);
				dd_e_i = DD_INFORMATION_LIST_prev(dd_e_i)){
			staticSlicing(DD_INFORMATION_LIST_data(dd_e_i)->dd_target);
		}

	}

}

/**
指定した命令へのASTノードに基づいてexpr_slicing_listに対してスタティックスライシング処理を行う。

@param inst_ast 指定した命令へのASTノード
@param expr_slicing_list スタティックスライシング処理を行うための構造体リスト

@return 成功したかどうかを返却する。　１：成功　０：失敗

*/
int startStaticSlicing(AST *inst_ast, EXPR_SLICING_LIST *expr_slicing_list){
	EXPR_SLICING_LISTIterator e_i;
	//ASTノードから、スライシング処理に関係する場所を検索する
	int success_flag = 0;

	for(e_i = EXPR_SLICING_LIST_begin(expr_slicing_list);
		success_flag == 0 && e_i != EXPR_SLICING_LIST_end(expr_slicing_list);
		e_i = EXPR_SLICING_LIST_next(e_i)){

		//プログラムスライシング情報に登録されているASTノードと一致すれば、それに対してプログラムスライシング処理を行う
		if(EXPR_SLICING_LIST_data(e_i)->expression == inst_ast){
			staticSlicing(EXPR_SLICING_LIST_data(e_i));
			success_flag = 1;
			break;
		}
		//そうでなければ、プログラムスライシングの子ノードも参照する
		else{

			success_flag = startStaticSlicing(inst_ast, EXPR_SLICING_LIST_data(e_i)->children1);
			if(success_flag){
				break;
			}

			success_flag = startStaticSlicing(inst_ast, EXPR_SLICING_LIST_data(e_i)->children2);
			if(success_flag){
				break;
			}

		}
	}

	return success_flag;
}
