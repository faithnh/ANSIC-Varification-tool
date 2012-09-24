#include"ExpressionStatementPSI.h"
#include"../ANSICInformation/SubEffectCheck.h"
#include"../ANSICInformation/ANSIC_CODE.h"

#include<stdio.h>
#include<stdlib.h>

//代入演算子が何かというフラグ0:=,1:+=,2:-=,3:*=,4:/=,5:%=,6:<<=,7:>>=,8:&=,9:|=,10:^=
#define EQUAL 0
#define PLUS_EQUAL 1
#define MINUS_EQUAL 2
#define MUL_EQUAL 3
#define DIV_EQUAL 4
#define MOD_EQUAL 5
#define LEFT_EQUAL 6
#define RIGHT_EQUAL 7
#define AND_EQUAL 8
#define OR_EQUAL 9
#define XOR_EQUAL 10

#define STRLEN 100

/**
式全般のASTノードexpression_statementから、関数に対するプログラムスライシングを抽出し、
プログラムスライシングリストexpr_slicing_listに追加する。

@param expr_slicing_list 追加先のプログラムスライシングリストexpr_slicing_list
@param expression_statement 式全般に関するASTノード
@param parent ノードを追加するときの親ノード
@param vtlist 変数テーブルリスト
@param function_information_list 関数に関する情報リスト
@param ignore_ast_list 重複防止のために無視するノードリスト
@param target_statement expression_statementを指し示すノード

@return なし
 */
void getExpressionStatementPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *expression_statement, EXPR_SLICING *parent,
		VARIABLE_TABLE_LIST *vtlist, FUNCTION_INFORMATION_LIST *function_information_list, ASTPOINTER_LIST *ignore_ast_list,
		AST *target_statement){

	//children1,children2の初期型
	EXPR_SLICING_LIST *children1 = EXPR_SLICING_LIST_new();
	EXPR_SLICING_LIST *children2 = EXPR_SLICING_LIST_new();
	//左辺値における各次元のポインタや配列のオフセットに関する情報のリスト
	ARRAY_OFFSET_LIST * target_variable = ARRAY_OFFSET_LIST_new();

	//右辺式における各次元のポインタや配列のオフセットに関する情報のリスト
	ARRAY_OFFSET_LIST * dependences = ARRAY_OFFSET_LIST_new();

	//代入式から配列オフセットリストの登録を行う
	getASI_ARRAY_OFFSET_LIST(expression_statement, target_variable, dependences, function_information_list, vtlist, ignore_ast_list, target_statement, 1);

	//インクリメントやデクリメントの式がdependenceで見つかったら、target_variableにコピーする。
	registerIncDecVariable(dependences, target_variable);

	//新しいプログラムスライシングデータ
	EXPR_SLICING *new_expr_slicing = new_EXPR_SLICING(EXPR_SLICING_LIST_size(expr_slicing_list) + 1, target_statement,target_variable,dependences, children1, children2, parent);
	EXPR_SLICING_LIST_push_back_ref(expr_slicing_list,new_expr_slicing);
}

/**
getASI_ARRAY_OFFSET_LISTの内部処理である

@param root オフセットリストに該当するASTノード
@param target_variable 左辺式のポインタおよび配列のオフセット情報のリスト
@param dependences 右辺式のポインタおよび配列のオフセット情報のリスト
@param function_information_list 関数に関する情報リスト
@param vtlist 検証対象の式をマークするための変数リスト
@param ignore_ast_list 配列オフセットリストの重複登録を防止するための、IDENTIFIERを無視するためのASTのアドレスリスト
@param target_statement 検証式の対象となるステートメント
@return なし
*/
void getASI_ARRAY_OFFSET_LIST_Internal(AST *root, ARRAY_OFFSET_LIST *target_variable, ARRAY_OFFSET_LIST *dependences, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
		ASTPOINTER_LIST *ignore_ast_list, AST *target_statement){

	ASTListIterator ast_i;
	//assignment_expressionを見つけた場合
	if(CSTLString_compare_with_char(root->name, "assignment_expression") == 0){
		//左辺および右辺の対象の変数および依存関係の変数を求める
		getARRAY_OFFSET_LIST(ASTLIST_ITERATOR_1(root), target_variable, function_information_list, vtlist, ignore_ast_list, root);

		//関数についての対象の変数および依存関係の変数を取得する
		getInputFunctionPSI(ASTLIST_ITERATOR_3(root), target_variable, dependences, function_information_list, vtlist, ignore_ast_list, target_statement);
		getARRAY_OFFSET_LIST(ASTLIST_ITERATOR_3(root), dependences, function_information_list, vtlist, ignore_ast_list, root);
		//左辺式の2番目以降の配列オフセット情報を右辺式のオフセットリストを取得する
		moveArrayOffsetList(target_variable, dependences, 1);
		//代入式のタイプを求める
		int a_op_flag = getAssignment_TYPE(root);
		//a_op_flagが=以外の場合は、右辺式のオフセットリストには両辺の式のオフセットリストを取得する
		if(a_op_flag != EQUAL){
			//右辺に来ている左辺のノードをコピーする
			copyArrayOffsetList(target_variable, dependences, 0);
		}
	}else if(CSTLString_compare_with_char(root->name, "t_assignment_expression") == 0){
		//関数についての対象の変数および依存関係の変数を取得する
		getInputFunctionPSI(root, target_variable, dependences, function_information_list, vtlist, ignore_ast_list, target_statement);
		getARRAY_OFFSET_LIST(root, dependences, function_information_list, vtlist, ignore_ast_list, target_statement);
	}else{
		//子ノードを参照させる
		for(ast_i = ASTList_begin(root->children);
			ast_i != ASTList_end(root->children);
			ast_i = ASTList_next(ast_i)){

			getASI_ARRAY_OFFSET_LIST_Internal(ASTList_data(ast_i), target_variable, dependences,
					function_information_list, vtlist, ignore_ast_list, target_statement);
		}
	}
}

/**
call_functionのASTノードから入出力関係の関数を探し出し、これらの引数の変数をすべて、対象変数として登録する。
@param root 対象のASTノード
@param target_variable 対象の変数の配列オフセット情報リスト
@param dependences 依存関係の配列オフセット情報リスト
@param function_information_list 関数に関する情報リスト
@param vtlist 検証式の式をマークするための変数リスト
@param ignore_ast_list 配列オフセットリストの重複登録を防止するための、IDENTIFIERを無視するためのASTのアドレスリスト
@param target_statement 検証式の対象となるステートメント

@return なし
 */
void getInputFunctionPSI(AST *root, ARRAY_OFFSET_LIST *target_variable, ARRAY_OFFSET_LIST *dependences, FUNCTION_INFORMATION_LIST *function_information_list,
		VARIABLE_TABLE_LIST *vtlist, ASTPOINTER_LIST *ignore_ast_list, AST *target_statement){

	ASTListIterator ast_i;
	FUNCTION_INFORMATION *function_information;

	if(CSTLString_compare_with_char(root->name, "call_function") == 0){
		//関数名を取得する
		CSTLString *function_name = CSTLString_new();
		getStringFromAST(function_name, ASTLIST_ITERATOR_1(root));

		//関数名が以下の名前であるかどうか調べ、そうであれば、これらの関数内の引数をすべて、対象変数として取得する。
		function_information = searchFUNCTION_INFORMATION(function_name, function_information_list);
		if(function_information != NULL){
			//関数呼び出しのＡＳＴノードからすべての引数を呼び出し、関数情報に対応している入出力型に従って、
			//対象の変数や依存関係の変数に追加する
			int argument_counter = 1;
			AST *argument;
			ARRAY_OFFSET_LIST *tmp;
			PARAM_INFORMATION_LISTIterator p_info_i = PARAM_INFORMATION_LIST_begin(function_information->param_information_list);
			while(getArgumentAST(&argument, root, argument_counter) != 0){
				//ここで、引数情報が範囲外参照を起こした場合はエラーを出力し、強制終了させる。
				if(p_info_i == PARAM_INFORMATION_LIST_end(function_information->param_information_list)){
					fprintf(stderr, "#%s#:%d:Too argument in function %s!", getFileName(), root->line, CSTLString_c_str(function_name));
					exit(1);
				}else{
					switch(PARAM_INFORMATION_LIST_data(p_info_i)->in_out_flag){
					case PARAM_IN_TYPE:
						get_ARRAY_OFFSET_LISTIgnoreASTNAME(argument, dependences,
								function_information_list, vtlist, ignore_ast_list, root, root->name);
						//引数内として含まれている配列オフセット情報に対して、引数番号を付加させる
						setARGUMENT_NUMBER( dependences, argument_counter, root);
						break;
					case PARAM_OUT_TYPE:
						get_ARRAY_OFFSET_LISTIgnoreASTNAME(argument, target_variable,
								function_information_list, vtlist, ignore_ast_list, root, root->name);
						//引数内として含まれている配列オフセット情報に対して、引数番号を付加させる
						setARGUMENT_NUMBER( target_variable, argument_counter, root);
						break;
					case PARAM_INOUT_TYPE:
						//仮の配列オフセットリストを生成し、そこに変数情報を取得する
						tmp = ARRAY_OFFSET_LIST_new();
						get_ARRAY_OFFSET_LISTIgnoreASTNAME(argument, tmp,
								function_information_list, vtlist, ignore_ast_list, root, root->name);

						//取得した配列オフセット情報を、対象の引数情報および依存関係の引数に移動させる
						copyArrayOffsetList(tmp, target_variable, 0);
						moveArrayOffsetList(tmp, dependences, 0);

						//仮の配列オフセットリストを削除する
						ARRAY_OFFSET_LIST_clear(tmp);
						ARRAY_OFFSET_LIST_delete(tmp);

						//引数内として含まれている配列オフセット情報に対して、引数番号を付加させる
						setARGUMENT_NUMBER( target_variable, argument_counter, root);
						setARGUMENT_NUMBER( dependences, argument_counter, root);
						break;
					default:
						fprintf(stderr, "不正な引数タイプです！\n");
						exit(1);
					}
				}


				//可変長変数を示すものがこなければ、次の引数情報を呼び出す。
				if(CSTLString_compare_with_char(PARAM_INFORMATION_LIST_data(p_info_i)->param_type, "valist") != 0 ||
						CSTLString_compare_with_char(PARAM_INFORMATION_LIST_data(p_info_i)->param_name, "...") != 0){
					p_info_i = PARAM_INFORMATION_LIST_next(p_info_i);
				}
				argument_counter++;
			}
		}
		CSTLString_delete(function_name);
	}

	//子ノードを参照させる
	for(ast_i = ASTList_begin(root->children);
		ast_i != ASTList_end(root->children);
		ast_i = ASTList_next(ast_i)){

		getInputFunctionPSI(ASTList_data(ast_i), target_variable, dependences,
				function_information_list, vtlist, ignore_ast_list, target_statement);
	}

}

/**
expression_statementおよび、expressionに相当するノードから、対象の変数および依存関係の配列オフセットリストを取得する。

@param root オフセットリストに該当するASTノード
@param target_variable 左辺式のポインタおよび配列のオフセット情報のリスト
@param dependences 右辺式のポインタおよび配列のオフセット情報のリスト
@param function_information_list 関数に関する情報リスト
@param vtlist 検証対象の式をマークするための変数リスト
@param ignore_ast_list ポインタでの位置が検証済みである、IDENTIFIERを無視するためのASTのアドレスリスト
@param target_statement 検証式の対象となるステートメント
@param allow_side_effect 副作用式を許すかどうかのフラグ　１：許す ０：許さない
@return なし
*/
void getASI_ARRAY_OFFSET_LIST(AST *root, ARRAY_OFFSET_LIST *target_variable, ARRAY_OFFSET_LIST *dependences, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
						  ASTPOINTER_LIST *ignore_ast_list, AST *target_statement, int allow_side_effect){
	//副作用式を許さない状態で、副作用式を見つけた場合
	if(allow_side_effect == 0 && checkContainSubEffectStatement(root) != 0){
		fprintf(stderr,"#%s#:%d:NOT ALLOW SUB EFFECT EXPRESSION!!", getFileName(), root->line);
		exit(1);
	}
	//expression_statementおよび、expressionに相当するノードから、対象の変数および依存関係の配列オフセットリストを取得する
	getASI_ARRAY_OFFSET_LIST_Internal(root, target_variable, dependences,
		function_information_list, vtlist, ignore_ast_list, target_statement);
}

/**
参照先のASTノードが指定した関数呼び出しcall_functionである配列オフセットリストargument_listに対して、
指定した引数の番号argument_numberを以下の形で付加する。

名前　→　名前#引数番号

@param argument_list 付加対象の配列オフセットリスト
@param arg_num 引数
@param call_function 関数呼び出しに対するASTノード

@return なし
 */
void setARGUMENT_NUMBER( ARRAY_OFFSET_LIST *argument_list, int arg_num, AST *call_function){

	ARRAY_OFFSET_LISTIterator a_i;

	//引数として代入するもの
	char number[STRLEN];
	snprintf(number, STRLEN, "#%d", arg_num);

	//配列オフセットリストをすべて探索する
	for(a_i = ARRAY_OFFSET_LIST_begin(argument_list);
		a_i != ARRAY_OFFSET_LIST_end(argument_list);
		a_i = ARRAY_OFFSET_LIST_next(a_i)){
		//参照先のASTノードが関数呼び出しに対するASTノードと等しい場合
		if(ARRAY_OFFSET_LIST_data(a_i)->target_statement == call_function){
			//#の文字が含まれていなければ、#引数番号を加える
			if(CSTLString_find(ARRAY_OFFSET_LIST_data(a_i)->variable_name, "#", 0) == CSTL_NPOS){
				CSTLString_append(ARRAY_OFFSET_LIST_data(a_i)->variable_name, number);

			}
		}

	}
}

