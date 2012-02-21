#include"ProgramSlicingInformation.h"
#include"../ANSICInformation/ANSIC_CODE.h"
#include<stdlib.h>

CSTL_LIST_IMPLEMENT(DD_INFORMATION_LIST, DD_INFORMATION)

CSTL_LIST_IMPLEMENT(EXPR_SLICING_LIST, struct expr_slicing)

/**
スライシングを行うための構造体を生成する。
@param expr_slicing_number 対象の式に対するAST番号
@param expression 対象の式へのＡＳＴノード
@param target_variable 変数のオフセットリスト
@param dependences 依存関係の配列オフセットリスト
@param children1 ifやwhile、forに対するスライシングリスト
@param children2 else文に対するスライシングリスト
@param parent 親をたどるためのノード

@return 生成されたスライシングを行うための構造体へのアドレスを返す

*/
EXPR_SLICING *new_EXPR_SLICING(int expr_slicing_number, AST *expression, ARRAY_OFFSET_LIST *target_variable,
		ARRAY_OFFSET_LIST *dependences,EXPR_SLICING_LIST *children1, EXPR_SLICING_LIST *children2,
		EXPR_SLICING *parent ){
	EXPR_SLICING *new_expr_slicing = (EXPR_SLICING*)malloc(sizeof(EXPR_SLICING));

	//もし生成するのに成功した場合
	if(new_expr_slicing != NULL){
		//引数にある情報を入れる
		new_expr_slicing->expr_slicing_number = expr_slicing_number;
		new_expr_slicing->expression = expression;
		new_expr_slicing->target_variable = target_variable;
		new_expr_slicing->dependences = dependences;
		new_expr_slicing->children1 = children1;
		new_expr_slicing->children2 = children2;
		new_expr_slicing->parent = parent;

		//DDリスト（データ依存関係のリスト）は初期化だけしておく
		new_expr_slicing->dd_list = DD_INFORMATION_LIST_new();
		//使用しているかどうかを示すフラグは必ず0(未使用状態)にしておく
		new_expr_slicing->flag = 0;
	}
	//新しいスライシングを行うための構造体を生成するために確保するのに失敗した場合はメモリ不足としてエラーを出し強制終了させる
	else{
		fprintf(stderr,"メモリ不足です!\n");
		exit(1);
	}

	return new_expr_slicing;
}

/**
データ依存関係に関する情報を生成する。
@param dd_variable_name データ依存関係に関する変数名
@param *dd_target データ依存関係のターゲットとなる命令

@return 生成されたデータ依存関係に関する情報の構造体へのアドレスを返す

*/
DD_INFORMATION *new_DD_INFORMATION(CSTLString *dd_variable_name, EXPR_SLICING *dd_target){
	DD_INFORMATION *new_dd_information = (DD_INFORMATION*)malloc(sizeof(DD_INFORMATION));

	//もし生成するのに成功した場合
	if(new_dd_information != NULL){
		new_dd_information->dd_variable_name = dd_variable_name;
		new_dd_information->dd_target = dd_target;
	}
	//生成に失敗した場合はメモリ不足としてエラーを出力し、強制終了させる
	else{
		fprintf(stderr,"メモリ不足です!\n");
		exit(1);
	}

	return new_dd_information;

}

/**
指定したデータ依存関係のリストから、指定された変数名が存在するか調べる。

@param variable_name 指定された変数名
@param dd_information_list 指定したデータ依存関係のリスト
@param find_dd_informaiton 見つけた場合に返すデータ依存関係の情報
@return 存在する場合は１、そうでない場合は０を返す
 */
int searchDD(CSTLString *variable_name, DD_INFORMATION_LIST *dd_information_list, DD_INFORMATION **find_dd_informaiton){
	int find_flag = 0;

	DD_INFORMATION_LISTIterator dd_i;
	//データ依存関係を探索する
	for(dd_i = DD_INFORMATION_LIST_begin(dd_information_list);
		dd_i != DD_INFORMATION_LIST_end(dd_information_list);
		dd_i = DD_INFORMATION_LIST_next(dd_i)){

		//もし、変数宣言の対象の変数から指定された変数名を見つけられたら、１を設定し、探索を終了させる
		if(searchARRAY_OFFSET_LIST(DD_INFORMATION_LIST_data(dd_i)->dd_target->target_variable, variable_name) != NULL){
			find_flag = 1;
			*find_dd_informaiton = DD_INFORMATION_LIST_data(dd_i);
			break;
		}

	}

	return find_flag;
}
/**
指定したプログラムスライシング情報のデータ依存関係から、指定された変数名である変数宣言が存在するか調べる。

@param variable_name 指定された変数名
@param expr_slicing 指定したプログラムスライシング情報のデータ

@return 存在する場合は１、そうでない場合は０を返す。
 */
int searchDeclarationDD(CSTLString *variable_name, EXPR_SLICING *expr_slicing){
	int find_flag = 0;

	DD_INFORMATION_LISTIterator dd_i;
	//データ依存関係を探索する
	for(dd_i = DD_INFORMATION_LIST_begin(expr_slicing->dd_list);
		dd_i != DD_INFORMATION_LIST_end(expr_slicing->dd_list);
		dd_i = DD_INFORMATION_LIST_next(dd_i)){

		//変数宣言または引数宣言を見つけた場合
		if(CSTLString_compare_with_char(DD_INFORMATION_LIST_data(dd_i)->dd_target->expression->name, "declaration_with_init") == 0 ||
				CSTLString_compare_with_char(DD_INFORMATION_LIST_data(dd_i)->dd_target->expression->name, "declarator") == 0){
			//もし、変数宣言の対象の変数から指定された変数名を見つけられたら、１を設定し、探索を終了させる
			if(searchARRAY_OFFSET_LIST(DD_INFORMATION_LIST_data(dd_i)->dd_target->target_variable, variable_name) != NULL){
				find_flag = 1;
				break;
			}

		}

	}

	return find_flag;
}

/**
プログラムスライシングのflagを初期化する。
@param expr_slicing_list 対象のプログラムスライシング情報のリスト

@return なし
 */
void initExprSlicingListFlag(EXPR_SLICING_LIST *expr_slicing_list){
	EXPR_SLICING_LISTIterator e_i;
	//プログラムスライシングリスト情報から１つずつ参照する
	for(e_i = EXPR_SLICING_LIST_begin(expr_slicing_list);
		e_i != EXPR_SLICING_LIST_end(expr_slicing_list);
		e_i = EXPR_SLICING_LIST_next(e_i)){

		//flagを0にする
		EXPR_SLICING_LIST_data(e_i)->flag = 0;

		//children1,children2についても同じ処理を行う
		initExprSlicingListFlag(EXPR_SLICING_LIST_data(e_i)->children1);
		initExprSlicingListFlag(EXPR_SLICING_LIST_data(e_i)->children2);

	}

}

/**
プログラム全体のプログラムスライシングリストexpr_slicing_listから、
関数呼び出しに対応する関数定義のプログラムスライシング情報を取得する。

@param function_name 関数名
@param expr_slicing_list プログラム全体のプログラムスライシングリスト

@return 取得に成功した場合、関数呼び出しに対応する関数定義へのプログラムスライシング情報を返す、失敗した場合はNULLを返す。
 */
EXPR_SLICING *searchFunctionPSI(CSTLString *function_name, EXPR_SLICING_LIST *expr_slicing_list){
	EXPR_SLICING *result = NULL;

	EXPR_SLICING_LISTIterator e_i;
	CSTLString *epsi_function_name = CSTLString_new();

	//プログラム全体のプログラムスライシングリストを探索する
	for(e_i = EXPR_SLICING_LIST_begin(expr_slicing_list);
		e_i != EXPR_SLICING_LIST_end(expr_slicing_list);
		e_i = EXPR_SLICING_LIST_next(e_i)){

		//もし、関数定義のプログラムスライシング情報を見つけた場合
		if(CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "function_definition_type_b") == 0){


			//関数名を取得する
			getStringFromAST(epsi_function_name, ASTLIST_ITERATOR_2(EXPR_SLICING_LIST_data(e_i)->expression));
			//関数名からパラメータなどの余分な情報を削除する
			deleteParameterDefine(epsi_function_name);
			//取得した関数名が、探したい関数名である場合はそのプログラムスライシング情報を取得し、探索を終了させる
			if(CSTLString_compare(epsi_function_name, function_name) == 0){
				result = EXPR_SLICING_LIST_data(e_i);
				break;
			}
		}
	}

	return result;
}

/**
関数内で扱うグローバル変数を抽出し、配列オフセットリストとして抽出する。

@param output_global_variable_list 抽出先の配列オフセットリスト
@param function_expr_slicing_list 関数呼び出しに対するプログラムスライシングリスト
@param global_variable_list グローバル変数一覧を示す配列オフセットリスト

@return なし
 */
void getFunctionGrobalVariable(ARRAY_OFFSET_LIST *output_global_variable_list, EXPR_SLICING_LIST *function_expr_slicing_list,
	ARRAY_OFFSET_LIST *global_variable_list){

	ARRAY_OFFSET_LIST *tmp_global_variable_list;
	ARRAY_OFFSET_LIST *local_variable_list;

	EXPR_SLICING_LISTIterator e_i;
	ARRAY_OFFSET_LISTIterator a_i;

	//もし、プログラムスライシングリストの命令が存在する場合
	if(EXPR_SLICING_LIST_size(function_expr_slicing_list) != 0){
		//関数内のグローバル変数をコピーする
		tmp_global_variable_list = ARRAY_OFFSET_LIST_new();
		copyArrayOffsetList(global_variable_list, tmp_global_variable_list, 0);

		//対象命令内のプログラムスライシングリストからローカル変数情報を抽出する
		local_variable_list = ARRAY_OFFSET_LIST_new();
		getVariableDeclarationFromEXPR_SLICING_LIST(local_variable_list, function_expr_slicing_list);

		//ローカル変数と重複するような変数を削除する
		minusArrayOffsetList(tmp_global_variable_list, local_variable_list);

		//ローカル変数を除いた、グローバル変数の情報が存在すれば、スライシングリスト内の命令を探索する
		if(ARRAY_OFFSET_LIST_size(tmp_global_variable_list) > 0){
			for(e_i = EXPR_SLICING_LIST_begin(function_expr_slicing_list);
				e_i != EXPR_SLICING_LIST_end(function_expr_slicing_list);
				e_i = EXPR_SLICING_LIST_next(e_i)){

				//対象の変数からグローバル変数が含まれているかどうか探索する
				for(a_i = ARRAY_OFFSET_LIST_begin(EXPR_SLICING_LIST_data(e_i)->target_variable);
						a_i != ARRAY_OFFSET_LIST_end(EXPR_SLICING_LIST_data(e_i)->target_variable);
						a_i = ARRAY_OFFSET_LIST_next(a_i)){
					//対象の変数からグローバル変数を見つけられた場合
					if(searchARRAY_OFFSET_LIST(tmp_global_variable_list, ARRAY_OFFSET_LIST_data(a_i)->variable_name)){
						//重複しないようにout_global_variable_listに追加する
						ARRAY_OFFSET_LIST_push_back_ref_not_dup(output_global_variable_list, ARRAY_OFFSET_LIST_data(a_i));
					}
				}

				//スライシング情報の子ノードも探索する
				getFunctionGrobalVariable(output_global_variable_list, EXPR_SLICING_LIST_data(e_i)->children1,
						tmp_global_variable_list);
				getFunctionGrobalVariable(output_global_variable_list, EXPR_SLICING_LIST_data(e_i)->children2,
						tmp_global_variable_list);

			}
		}

		ARRAY_OFFSET_LIST_clear(tmp_global_variable_list);
		ARRAY_OFFSET_LIST_delete(tmp_global_variable_list);
		ARRAY_OFFSET_LIST_clear(local_variable_list);
		ARRAY_OFFSET_LIST_delete(local_variable_list);
	}


}

/**
対象のプログラムスライシングリストから、変数宣言部分を抽出し、配列オフセット情報として抽出する。

@param global_variable_list グローバル変数一覧を示す配列オフセットリスト
@param program_expr_slicing_list プログラム全体のプログラムスライシングリスト

@return なし
 */
void getVariableDeclarationFromEXPR_SLICING_LIST(ARRAY_OFFSET_LIST *global_variable_list, EXPR_SLICING_LIST *program_expr_slicing_list){
	EXPR_SLICING_LISTIterator e_i;

	//全体を探索する
	for(e_i = EXPR_SLICING_LIST_begin(program_expr_slicing_list);
		e_i != EXPR_SLICING_LIST_end(program_expr_slicing_list);
		e_i = EXPR_SLICING_LIST_next(e_i)){

		//もし、decralation_with_initという変数宣言を見つけた場合、その対象の変数をもとに、配列オフセット情報にコピーする
		if(CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "declaration_with_init") == 0 ||
				CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "declarator") == 0){
			copyArrayOffsetList(EXPR_SLICING_LIST_data(e_i)->target_variable, global_variable_list, 0);
		}
	}
}

/**
setGrobalVariableの内部処理。関数内のグローバル変数を抽出し、対象の変数に追加させる。

@param expr_slicing_list 追加対象のプログラムスライシングリスト
@param program_expr_slicing_list プログラム全体のプログラムスライシングリスト
@param global_variable_list グローバル変数リスト

@return なし
 */
void setGrobalVariable_Internal(EXPR_SLICING_LIST *expr_slicing_list, EXPR_SLICING_LIST *program_expr_slicing_list,
	ARRAY_OFFSET_LIST *global_variable_list){

	EXPR_SLICING_LISTIterator e_i;

	ARRAY_OFFSET_LISTIterator a_i;

	EXPR_SLICING *search_expr_slicing;

	CSTLString *function_name = CSTLString_new();

	//プログラムスライシングを調べていく
	for(e_i = EXPR_SLICING_LIST_begin(expr_slicing_list);
		e_i != EXPR_SLICING_LIST_end(expr_slicing_list);
		e_i = EXPR_SLICING_LIST_next(e_i)){

		//対象の変数を調べていく
		for(a_i = ARRAY_OFFSET_LIST_begin(EXPR_SLICING_LIST_data(e_i)->target_variable);
				a_i != ARRAY_OFFSET_LIST_end(EXPR_SLICING_LIST_data(e_i)->target_variable);
				a_i = ARRAY_OFFSET_LIST_next(a_i)){

			//関数呼び出し関係の命令を見つけた場合
			if(CSTLString_compare_with_char(ARRAY_OFFSET_LIST_data(a_i)->target_statement->name, "call_function") == 0){
				//関数名を取り出す
				getStringFromAST(function_name, ASTLIST_ITERATOR_1(ARRAY_OFFSET_LIST_data(a_i)->target_statement));

				//expr_slicing_listから、関数呼び出しに対応する関数へのプログラムスライシング情報を取り出す
				search_expr_slicing = searchFunctionPSI(function_name, program_expr_slicing_list);

				//もし、見つかれば関数定義内で扱うグローバル変数を抽出し、対象の変数に追加させる
				if(search_expr_slicing != NULL){
					getFunctionGrobalVariable(EXPR_SLICING_LIST_data(e_i)->target_variable, search_expr_slicing->children1, global_variable_list);
				}
			}
		}

		//依存関係の変数を調べていく
		for(a_i = ARRAY_OFFSET_LIST_begin(EXPR_SLICING_LIST_data(e_i)->dependences);
				a_i != ARRAY_OFFSET_LIST_end(EXPR_SLICING_LIST_data(e_i)->dependences);
				a_i = ARRAY_OFFSET_LIST_next(a_i)){

			//関数呼び出し関係の命令を見つけた場合
			if(CSTLString_compare_with_char(ARRAY_OFFSET_LIST_data(a_i)->target_statement->name, "call_function") == 0){
				//関数名を取り出す
				getStringFromAST(function_name, ASTLIST_ITERATOR_1(ARRAY_OFFSET_LIST_data(a_i)->target_statement));

				//expr_slicing_listから、関数呼び出しに対応する関数へのプログラムスライシング情報を取り出す
				search_expr_slicing = searchFunctionPSI(function_name, program_expr_slicing_list);

				//もし、見つかれば関数定義内で扱うグローバル変数を抽出し、対象の変数に追加させる
				if(search_expr_slicing != NULL){
					getFunctionGrobalVariable(EXPR_SLICING_LIST_data(e_i)->target_variable, search_expr_slicing->children1, global_variable_list);
				}
			}
		}

		//子ノードも探索する
		setGrobalVariable_Internal(EXPR_SLICING_LIST_data(e_i)->children1, program_expr_slicing_list, global_variable_list);
		setGrobalVariable_Internal(EXPR_SLICING_LIST_data(e_i)->children2, program_expr_slicing_list, global_variable_list);
	}

	CSTLString_delete(function_name);
}

/**
関数呼び出しから、取り扱うグローバル変数を抽出し、対象の変数一覧に追加していく。
@param expr_slicing_list 追加対象のプログラムスライシングリスト
@param program_expr_slicing_list プログラム全体のプログラムスライシングリスト

@return なし
 */
void setGlobalVariable(EXPR_SLICING_LIST *expr_slicing_list, EXPR_SLICING_LIST *program_expr_slicing_list){
	ARRAY_OFFSET_LIST *global_variable_list = ARRAY_OFFSET_LIST_new();

	//グローバル変数リストを抽出させる
	getVariableDeclarationFromEXPR_SLICING_LIST(global_variable_list, program_expr_slicing_list);

	//関数呼び出しから、取り扱うグローバル変数を抽出し、対象の変数に追加していく
	setGrobalVariable_Internal(expr_slicing_list, program_expr_slicing_list, global_variable_list);

	ARRAY_OFFSET_LIST_delete(global_variable_list);
}

/**
スライシングに関する情報リストexpr_slicing_listを出力させる。

@param expr_slicing_list スライシングに関する情報リスト

@return なし
 */
void print_EXPR_SLICING_LIST(EXPR_SLICING_LIST *expr_slicing_list){

	EXPR_SLICING_LISTIterator el_i;
	DD_INFORMATION_LISTIterator dd_el_i;
	ARRAY_OFFSET_LISTIterator aoff_i;
	//スライシングリストを１つ１つ探索する
	for(el_i = EXPR_SLICING_LIST_begin(expr_slicing_list);
		el_i != EXPR_SLICING_LIST_end(expr_slicing_list);
		el_i = EXPR_SLICING_LIST_next(el_i)){

		//スライシングのタイプ・位置（行数）・対象の変数・依存関係の変数を出力させる
		printf("--------------------------------------------\n");

		printf("SLICING_TYPE = %s\n",CSTLString_c_str(EXPR_SLICING_LIST_data(el_i)->expression->name));
		printf("LOCATION = %d\n", EXPR_SLICING_LIST_data(el_i)->expression->line);

		//対象の変数を「TARGET_VARIABLE = 変数1, 変数2, ...」と出力させる
		printf("TARGET_VARIABLE = ");
		for(aoff_i = ARRAY_OFFSET_LIST_begin(EXPR_SLICING_LIST_data(el_i)->target_variable);
			aoff_i != ARRAY_OFFSET_LIST_end(EXPR_SLICING_LIST_data(el_i)->target_variable);
			aoff_i = ARRAY_OFFSET_LIST_next(aoff_i)){

				printf("%s", CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_i)->variable_name));
				if(ARRAY_OFFSET_LIST_next(aoff_i) != ARRAY_OFFSET_LIST_end(EXPR_SLICING_LIST_data(el_i)->target_variable)){
					printf(", ");
				}
			}
		printf("\n");

		//対象の変数を「DEPENDENCES = 変数1, 変数2, ...」と出力させる
		printf("DEPENDENCES = ");
		for(aoff_i = ARRAY_OFFSET_LIST_begin(EXPR_SLICING_LIST_data(el_i)->dependences);
			aoff_i != ARRAY_OFFSET_LIST_end(EXPR_SLICING_LIST_data(el_i)->dependences);
			aoff_i = ARRAY_OFFSET_LIST_next(aoff_i)){

				printf("%s", CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_i)->variable_name));
				if(ARRAY_OFFSET_LIST_next(aoff_i) != ARRAY_OFFSET_LIST_end(EXPR_SLICING_LIST_data(el_i)->dependences)){
					printf(", ");
				}
			}
		printf("\n");

		//データ依存関係を出力させる
		for(dd_el_i = DD_INFORMATION_LIST_rbegin(EXPR_SLICING_LIST_data(el_i)->dd_list);
				dd_el_i != DD_INFORMATION_LIST_rend(EXPR_SLICING_LIST_data(el_i)->dd_list);
				dd_el_i = DD_INFORMATION_LIST_prev(dd_el_i)){
			printf("j・%s %s line = %d\t",CSTLString_c_str(DD_INFORMATION_LIST_data(dd_el_i)->dd_variable_name),CSTLString_c_str(DD_INFORMATION_LIST_data(dd_el_i)->dd_target->expression->name), DD_INFORMATION_LIST_data(dd_el_i)->dd_target->expression->line);
			//対象の変数を「変数1, 変数2, ...」と出力させる
			if(ARRAY_OFFSET_LIST_size(DD_INFORMATION_LIST_data(dd_el_i)->dd_target->target_variable) > 0){
				for(aoff_i = ARRAY_OFFSET_LIST_begin(DD_INFORMATION_LIST_data(dd_el_i)->dd_target->target_variable);
					aoff_i != ARRAY_OFFSET_LIST_end(DD_INFORMATION_LIST_data(dd_el_i)->dd_target->target_variable);
					aoff_i = ARRAY_OFFSET_LIST_next(aoff_i)){

						printf("%s", CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_i)->variable_name));
						if(ARRAY_OFFSET_LIST_next(aoff_i) != ARRAY_OFFSET_LIST_end(DD_INFORMATION_LIST_data(dd_el_i)->dd_target->target_variable)){
							printf(", ");
						}
				}
			}else{
				printf("NOTHING");
			}
			//依存関係の変数を「変数1, 変数2, ...」と出力させる
			printf("\t");
			if(ARRAY_OFFSET_LIST_size(DD_INFORMATION_LIST_data(dd_el_i)->dd_target->dependences) > 0){
				for(aoff_i = ARRAY_OFFSET_LIST_begin(DD_INFORMATION_LIST_data(dd_el_i)->dd_target->dependences);
					aoff_i != ARRAY_OFFSET_LIST_end(DD_INFORMATION_LIST_data(dd_el_i)->dd_target->dependences);
					aoff_i = ARRAY_OFFSET_LIST_next(aoff_i)){

						printf("%s", CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_i)->variable_name));
						if(ARRAY_OFFSET_LIST_next(aoff_i) != ARRAY_OFFSET_LIST_end(DD_INFORMATION_LIST_data(dd_el_i)->dd_target->dependences)){
							printf(", ");
						}
				}
			}else{
				printf("NOTHING");
			}
			printf("\n");
		}
		printf("--------------------------------------------\n\n");

		//子ノードも探索させる
		print_EXPR_SLICING_LIST(EXPR_SLICING_LIST_data(el_i)->children1);
		print_EXPR_SLICING_LIST(EXPR_SLICING_LIST_data(el_i)->children2);
	}

}
/**
print_tree_EXPR_SLICING_LISTの内部処理である。

@param expr_slicing_list スライシングに関する情報リスト
@param tree_level ツリーのレベル
@param program_slicing_mode プログラムスライシング後のモードにするかどうかのフラグ　１：有効　０：無効

@return なし
 */
void print_tree_EXPR_SLICING_LIST_internal(EXPR_SLICING_LIST *expr_slicing_list,int tree_level, int program_slicing_mode){
	EXPR_SLICING_LISTIterator el_i;
	ARRAY_OFFSET_LISTIterator aoff_i;

	//スライシングリストを１つ１つ探索する

	for(el_i = EXPR_SLICING_LIST_begin(expr_slicing_list);
		el_i != EXPR_SLICING_LIST_end(expr_slicing_list);
		el_i = EXPR_SLICING_LIST_next(el_i)){

		//プログラムスライシング後のモードになっているときは、スライシング後のデータとして使用するもの以外は
		//スライシングのタイプ・位置（行数）・対象の変数・依存関係の変数を出力させない
		if(program_slicing_mode == 0 || EXPR_SLICING_LIST_data(el_i)->flag == 1){
			int i;
			for(i = 0; i < tree_level; i++){
				printf("　");
			}
			printf("・%p %d %s line = %d\t", EXPR_SLICING_LIST_data(el_i), EXPR_SLICING_LIST_data(el_i)->expr_slicing_number,
					CSTLString_c_str(EXPR_SLICING_LIST_data(el_i)->expression->name),
					EXPR_SLICING_LIST_data(el_i)->expression->line);
			//対象の変数を「変数1, 変数2, ...」と出力させる
			if(ARRAY_OFFSET_LIST_size(EXPR_SLICING_LIST_data(el_i)->target_variable) > 0){
				for(aoff_i = ARRAY_OFFSET_LIST_begin(EXPR_SLICING_LIST_data(el_i)->target_variable);
					aoff_i != ARRAY_OFFSET_LIST_end(EXPR_SLICING_LIST_data(el_i)->target_variable);
					aoff_i = ARRAY_OFFSET_LIST_next(aoff_i)){

						printf("%s", CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_i)->variable_name));
						if(ARRAY_OFFSET_LIST_next(aoff_i) != ARRAY_OFFSET_LIST_end(EXPR_SLICING_LIST_data(el_i)->target_variable)){
							printf(", ");
						}
				}
			}else{
				printf("NOTHING");
			}
			//依存関係の変数を「変数1, 変数2, ...」と出力させる
			printf("\t");
			if(ARRAY_OFFSET_LIST_size(EXPR_SLICING_LIST_data(el_i)->dependences) > 0){
				for(aoff_i = ARRAY_OFFSET_LIST_begin(EXPR_SLICING_LIST_data(el_i)->dependences);
					aoff_i != ARRAY_OFFSET_LIST_end(EXPR_SLICING_LIST_data(el_i)->dependences);
					aoff_i = ARRAY_OFFSET_LIST_next(aoff_i)){

						printf("%s", CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_i)->variable_name));
						if(ARRAY_OFFSET_LIST_next(aoff_i) != ARRAY_OFFSET_LIST_end(EXPR_SLICING_LIST_data(el_i)->dependences)){
							printf(", ");
						}
				}
			}else{
				printf("NOTHING");
			}
			//データ依存関係の数を出力させる
			printf("\tDD_LIST = %d", DD_INFORMATION_LIST_size(EXPR_SLICING_LIST_data(el_i)->dd_list));
			printf("\n");

			//子ノードも探索させる
			print_tree_EXPR_SLICING_LIST_internal(EXPR_SLICING_LIST_data(el_i)->children1, tree_level + 1, program_slicing_mode);
			print_tree_EXPR_SLICING_LIST_internal(EXPR_SLICING_LIST_data(el_i)->children2, tree_level + 1, program_slicing_mode);
		}


	}

}

/**
スライシングに関する情報リストexpr_slicing_listをツリー形式で出力させる。

@param expr_slicing_list スライシングに関する情報リスト
@param program_slicing_mode プログラムスライシング後のモードにするかどうかのフラグ　１：有効　０：無効
@return なし
 */
void print_tree_EXPR_SLICING_LIST(EXPR_SLICING_LIST *expr_slicing_list, int program_slicing_mode){

	int tree_level = 1;
	printf("・PROGRAM_START\n");
	print_tree_EXPR_SLICING_LIST_internal(expr_slicing_list, tree_level, program_slicing_mode);

}

/**
dependencesでインクリメントやデクリメントのフラグが立っている変数を見つけたら、それをtarget_variableに登録する。

@param dependences インクリメントやデクリメントを探す対象の依存変数
@param target_variable 登録先の定義対象変数

@return なし
 */
void registerIncDecVariable(ARRAY_OFFSET_LIST *dependences, ARRAY_OFFSET_LIST *target_variable){
	ARRAY_OFFSET_LISTIterator a_i;

	//依存変数のリストから、インクリメントやデクリメントのフラグが立っている変数を探す
	for(a_i = ARRAY_OFFSET_LIST_begin(dependences);
		a_i != ARRAY_OFFSET_LIST_end(dependences);
		a_i = ARRAY_OFFSET_LIST_next(a_i)){
		//インクリメントやデクリメントのフラグが立っている変数を見つけたら、それをtarget_variableに登録する。
		if(ARRAY_OFFSET_LIST_data(a_i)->inc_dec_flag != 0){
			ARRAY_OFFSET_LIST_push_back(target_variable, *ARRAY_OFFSET_LIST_data(a_i));
		}
	}
}
