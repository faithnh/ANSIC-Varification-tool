#include"FunctionInformation.h"
#include<stdlib.h>
#include<stdio.h>

#include"ANSIC_CODE.h"

CSTL_LIST_IMPLEMENT(PARAM_INFORMATION_LIST, PARAM_INFORMATION)

CSTL_LIST_IMPLEMENT(FUNCTION_INFORMATION_LIST, FUNCTION_INFORMATION)

#define LINE 65536
#define LENGTH 4096

#define FUNCTION_DEFINE_INPUTED 2
#define PARAMETER_DEFINE_INPUTED 3
/**
関数に関する情報を生成する。

@param function_node 対象の関数へのノード
@param return_type 返却値のタイプ
@param function_name 関数名
@param param_information_list パラメータに関する情報

@return 生成された関数に関する情報へのアドレスを返す。
 */
FUNCTION_INFORMATION *new_FUNCTION_INFORMATION(AST *function_node, CSTLString *return_type,
			CSTLString *function_name, PARAM_INFORMATION_LIST *param_information_list){
	FUNCTION_INFORMATION *new_function_information = (FUNCTION_INFORMATION*)malloc(sizeof(FUNCTION_INFORMATION));

	if(new_function_information == NULL){
		fprintf(stderr, "メモリ不足です\n");
		exit(1);
	}else{
		new_function_information->function_node = function_node;
		new_function_information->return_type = return_type;
		new_function_information->function_name = function_name;
		new_function_information->param_information_list = param_information_list;
	}

	return new_function_information;
}

/**
パラメータに関する情報を生成する。

@param param_type パラメータの型
@param param_name パラメータの名前
@param array_level 配列のレベル
@param pointer_level ポインタのレベル
@param in_out_flag 入力型か出力型かの判定　１：入力　０：出力　２：入出力

@return 生成されたパラメータに関する情報へのアドレスを返す。
 */

PARAM_INFORMATION *new_PARAM_INFORMATION(CSTLString *param_type, CSTLString *param_name,
			int array_level, int pointer_level, int in_out_flag){
	PARAM_INFORMATION *new_param_information = (PARAM_INFORMATION*)malloc(sizeof(PARAM_INFORMATION));

	if(new_param_information == NULL){
		fprintf(stderr, "メモリ不足です\n");
		exit(1);
	}else{
		new_param_information->param_type = param_type;
		new_param_information->param_name = param_name;
		new_param_information->array_level = array_level;
		new_param_information->pointer_level = pointer_level;
		new_param_information->in_out_flag = in_out_flag;
	}

	return new_param_information;
}

/**
指定したプログラムのASTノードから関数定義を探し、それに基づいて関数に関する情報を生成し、それらのリストfunction_information_list
に登録する。

@param function_information_list 登録先の関数に関する情報のリスト
@param root 指定したプログラムのASTノード

@return なし
 */
void getFunctionInformation(FUNCTION_INFORMATION_LIST *function_information_list, AST *root){
	ASTListIterator ast_p;
	AST *enable_start, *enable_end;
	//もし、function_definition_type_bを見つけられたら以下の操作を行う
	if(CSTLString_compare_with_char(root->name, "function_definition_type_b") == 0){
		//返却値および関数名を定義する
		CSTLString *return_type = CSTLString_new();
		CSTLString *function_name = CSTLString_new();

		//関数のパラメータ情報を取得する
		PARAM_INFORMATION_LIST *param_information_list = PARAM_INFORMATION_LIST_new();
		getParamInformationFromFunctionDifinition(ASTLIST_ITERATOR_2(root), param_information_list);

		//返却値および関数名を取得する
		getStringFromAST(return_type, ASTLIST_ITERATOR_1(root));
		getStringFromAST(function_name, ASTLIST_ITERATOR_2(root));
		//関数名から、パラメータ定義の部分を削除する
		deleteParameterDefine(function_name);


		FUNCTION_INFORMATION_LIST_push_back_ref(function_information_list, new_FUNCTION_INFORMATION(root, return_type, function_name, param_information_list));
	}
	//ASTに子ASTノードを持っている場合は、子ASTノードについても同じ探索を行う。
	for(ast_p = ASTList_begin(root->children); ast_p != ASTList_end(root->children); ast_p = ASTList_next(ast_p)){
		//再帰的にstruct_or_union_specifier定義が来た場合は、そこは探索させないようにする。
		if(CSTLString_compare_with_char(ASTList_data(ast_p)->name, "struct_or_union_specifier") != 0){
			getFunctionInformation(function_information_list, ASTList_data(ast_p));
		}
	}
}

/**
指定したファイル名file_nameで定義された関数に関する情報を関数に関する情報のリストfunction_information_listに設定する。
@param function_information_list 登録先の関数に関する情報のリスト
@param file_name 指定したファイル名

@return なし
 */
void getFunctionInformationFromFile(FUNCTION_INFORMATION_LIST *function_information_list, char* file_name){
	FILE *open;

	char type[LENGTH],name[LENGTH];
	char param_type[LENGTH],param_name[LENGTH];
	char in_out_flag_str[LENGTH];
	CSTLString *CSTL_function_type;
	CSTLString *CSTL_function_name;
	CSTLString *CSTL_param_type;
	CSTLString *CSTL_param_name;
	CSTLString *CSTL_in_out_flag_str = CSTLString_new();
	PARAM_INFORMATION_LIST *param_information_list;
	int file_pos;
	int pointer_level, array_level;
	int in_out_flag;
	fpos_t fpos;
	char input_char;
	open = fopen(file_name, "r");

	int scanf_count;


	if(open == NULL){
		fprintf(stderr,"指定したファイル:%sが開けられません。", file_name);
		exit(1);
	}else{
		//ファイルの終了まで、返却値の型と関数名を取得する
		while(1){
			scanf_count = fscanf(open, "%[^,],%[^,\n]",type, name);
			if(scanf_count == EOF){
				break;
			}else if(scanf_count != FUNCTION_DEFINE_INPUTED){
				fprintf(stderr,"入力フォーマット返却型,関数名,が不正です！\n");
				exit(1);
			}
			//関数の返却型と名前を取得する
			CSTL_function_type = CSTLString_new();
			CSTLString_assign(CSTL_function_type, type);
			CSTL_function_name = CSTLString_new();
			CSTLString_assign(CSTL_function_name, name);


			//パラメータリストを初期化する
			param_information_list = PARAM_INFORMATION_LIST_new();

			//任意にパラメータを取得する
			if(fgetc(open) == ','){
				while(1){
					if(fscanf(open, "%[^:\n]:%[^:\n]:%[^,\n\0]", param_type, param_name,in_out_flag_str) != PARAMETER_DEFINE_INPUTED){
						fprintf(stderr,"入力フォーマット型名:変数名:入出力属性が不正です！\n");
						exit(1);
					}


					//パラメータの型名を取得する
					CSTL_param_type = CSTLString_new();
					CSTLString_assign(CSTL_param_type, param_type);
					CSTLString_ltrim(CSTL_param_type);

					//パラメータの変数名を取得する
					CSTL_param_name = CSTLString_new();
					CSTLString_assign(CSTL_param_name, param_name);
					CSTLString_ltrim(CSTL_param_name);

					//入力か出力かの文字列を取得する
					CSTLString_assign(CSTL_in_out_flag_str, in_out_flag_str);

					//\r記号が含まれていたらそれを\0に置き換える。
					CSTLString_replace_string(CSTL_in_out_flag_str, "\r", "\0");
					//空白文字を削除する
					CSTLString_replace_string(CSTL_in_out_flag_str, " ", "");

					//ポインタレベルおよび配列レベルを取得する
					getPointerLevelAndArrayLevel(CSTL_param_name, &pointer_level, &array_level);

					//パラメータの変数名から、ポインタおよび配列を示す記号を削除する
					deletePointerAndArraySynbol(CSTL_param_name);

					//パラメータの型名およびポインタレベル・配列レベルからこのパラメータは入力型か出力型か判断する
					if(CSTLString_compare_with_char(CSTL_in_out_flag_str, "IN") == 0){
						in_out_flag = PARAM_IN_TYPE;
					}else if(CSTLString_compare_with_char(CSTL_in_out_flag_str, "OUT") == 0){
						in_out_flag = PARAM_OUT_TYPE;
					}else if(CSTLString_compare_with_char(CSTL_in_out_flag_str, "IN_OUT") == 0){
						in_out_flag = PARAM_INOUT_TYPE;
					}else{
						fprintf(stderr, "入力・出力タイプ%sが不正です！\n", CSTLString_c_str(CSTL_in_out_flag_str));
						exit(1);
					}

					//パラメータリストにいれる
					PARAM_INFORMATION_LIST_push_back_ref(param_information_list,
							new_PARAM_INFORMATION(CSTL_param_type, CSTL_param_name, array_level, pointer_level, in_out_flag));
					//ファイルから読み込んだ1文字前の文字が改行かEOFであれば、終了する
					input_char = fgetc(open);
					if(input_char == '\n' ||input_char == EOF){
						break;
					}

				}
			}

			//関数リストに追加する
			FUNCTION_INFORMATION_LIST_push_back_ref(function_information_list,
					new_FUNCTION_INFORMATION(NULL, CSTL_function_type, CSTL_function_name, param_information_list));
		}
		fclose(open);


	}
	CSTLString_delete(CSTL_in_out_flag_str);
}

/**
指定した関数の定義自体から、パラメータ定義などを削除する。

@param target_string 対象の関数の定義自体の文字列

@return なし
 */
void deleteParameterDefine(CSTLString *target_string){
	int i;
	//パラメータを示すフラグ
	int parameter_flag = 0;

	for(i = 0; i < CSTLString_size(target_string);){
		//パラメータを示すフラグが立っていないとき
		if(parameter_flag == 0){
			//パラメータの開始を示すマークが来た場合は、その文字を削除して、フラグを立てる
			if(*CSTLString_at(target_string,i) == '('){
				CSTLString_erase(target_string, i, 1);
				parameter_flag = 1;
			}else if(*CSTLString_at(target_string,i) == ' '){
				CSTLString_erase(target_string, i, 1);

			}
			//それ以外の場合は、一文字進める
			else{
				i++;
			}
		}
		//パラメータを示すフラグが立っているとき
		else{
			//パラメータの終わりを示すマークが来た場合は、その文字を削除したうえ、フラグを下げる
			if(*CSTLString_at(target_string,i) == ')'){
				CSTLString_erase(target_string, i, 1);
				parameter_flag = 0;
			}
			//それ以外の場合は削除していく
			else{
				CSTLString_erase(target_string, i, 1);
			}
		}

	}
}
/**
関数に関する情報リストの内容を出力させる。
@param function_information_list 出力対象の関数に関する情報リスト

@return なし
*/

void printFUNCTION_INFORMATION_LIST(FUNCTION_INFORMATION_LIST *function_information_list){
	FUNCTION_INFORMATION_LISTIterator f_info_list;
	PARAM_INFORMATION_LISTIterator p_info_list;
	int f_counter;
	for(f_counter = 1, f_info_list = FUNCTION_INFORMATION_LIST_begin(function_information_list);
		f_info_list != FUNCTION_INFORMATION_LIST_end(function_information_list);
		f_counter++, f_info_list = FUNCTION_INFORMATION_LIST_next(f_info_list)){

		//関数に関する情報の内容を出力する
		printf("-------FUNCTION_INFORMATION_%d-------\n\n",f_counter);
		if(FUNCTION_INFORMATION_LIST_data(f_info_list)->function_node != NULL){
			printf("FUNCTION_LINE = %d\n", FUNCTION_INFORMATION_LIST_data(f_info_list)->function_node->line);
		}
		printf("RETURN_TYPE = \"%s\"\n", CSTLString_c_str(FUNCTION_INFORMATION_LIST_data(f_info_list)->return_type));
		printf("FUNCTION_NAME = \"%s\"\n", CSTLString_c_str(FUNCTION_INFORMATION_LIST_data(f_info_list)->function_name));
		//変数情報を出力させる
		for(p_info_list = PARAM_INFORMATION_LIST_begin(FUNCTION_INFORMATION_LIST_data(f_info_list)->param_information_list);
			p_info_list != PARAM_INFORMATION_LIST_end(FUNCTION_INFORMATION_LIST_data(f_info_list)->param_information_list);
			p_info_list = PARAM_INFORMATION_LIST_next(p_info_list)){

			//パラメータの型名・名前・ポインタレベル・配列レベル・入出力属性の順に出力させる
			printf("%s %s POINTER_LEVEL = %d a_level = %d io_type = ", CSTLString_c_str(PARAM_INFORMATION_LIST_data(p_info_list)->param_type),
					CSTLString_c_str(PARAM_INFORMATION_LIST_data(p_info_list)->param_name), PARAM_INFORMATION_LIST_data(p_info_list)->pointer_level,
					PARAM_INFORMATION_LIST_data(p_info_list)->array_level);

			//パラメータの入出力属性を出力させる
			if(PARAM_INFORMATION_LIST_data(p_info_list)->in_out_flag == PARAM_IN_TYPE){
				printf("IN\n");
			}else if(PARAM_INFORMATION_LIST_data(p_info_list)->in_out_flag == PARAM_OUT_TYPE){
				printf("OUT\n");
			}else if(PARAM_INFORMATION_LIST_data(p_info_list)->in_out_flag == PARAM_INOUT_TYPE){
				printf("IN_OUT\n");
			}else{
				printf("NOT_DEFINE!");
			}
		}
		printf("-------------------------------------\n\n");
	}
}

/**
関数に関する情報リストから、指定した関数名を探し、それに関する構造体へのアドレスを返す。

@param target_function_name 指定した関数名
@param function_information_list 検索対象の関数に関する情報リスト

@return 見つかった場合はその関数に関する構造体へのアドレスを返す。みつからなければ、NULLを返す。
 */

FUNCTION_INFORMATION *searchFUNCTION_INFORMATION(CSTLString *target_function_name, FUNCTION_INFORMATION_LIST *function_information_list){
	FUNCTION_INFORMATION_LISTIterator f_info_list;
	//関数に関する情報リストから取得される関数名
	CSTLString *function_name = CSTLString_new();
	int output_pointer_level, output_array_level;

	for(f_info_list = FUNCTION_INFORMATION_LIST_begin(function_information_list);
		f_info_list != FUNCTION_INFORMATION_LIST_end(function_information_list);
		f_info_list = FUNCTION_INFORMATION_LIST_next(f_info_list)){

		//関数に関する情報リストから関数名を取得する
		CSTLString_assign(function_name, CSTLString_c_str(FUNCTION_INFORMATION_LIST_data(f_info_list)->function_name));

		//関数名から余分なポインタや配列記号を削除する
		deletePointerAndArraySynbol(function_name);

		//もし、関数名が一致した場合はポインタレベルを返す
		if(CSTLString_compare(target_function_name, function_name) == 0){
			return FUNCTION_INFORMATION_LIST_data(f_info_list);
		}
	}

	return NULL;
}

/**
指定した関数名が関数に関する情報リストから探し、ポインタレベルを返す。
@param target_function_name 指定した関数名
@param function_information_list 検索対象の関数に関する情報リスト

@return 見つかった場合はその関数のポインタレベルを返す。そうでない場合は-1を返す。
 */

int getPointerLevelFromFUNCTION_INFORMATION_LIST(CSTLString *target_function_name, FUNCTION_INFORMATION_LIST *function_information_list){
	FUNCTION_INFORMATION_LISTIterator f_info_list;
	//関数に関する情報リストから取得される関数名
	CSTLString *function_name = CSTLString_new();
	int output_pointer_level, output_array_level;
	int f_counter;
	for(f_counter = 1, f_info_list = FUNCTION_INFORMATION_LIST_begin(function_information_list);
		f_info_list != FUNCTION_INFORMATION_LIST_end(function_information_list);
		f_counter++, f_info_list = FUNCTION_INFORMATION_LIST_next(f_info_list)){

		//関数に関する情報リストから関数名を取得する
		CSTLString_assign(function_name, CSTLString_c_str(FUNCTION_INFORMATION_LIST_data(f_info_list)->function_name));
		//関数名からポインタレベルを取得する
		getPointerLevelAndArrayLevel(function_name,&output_pointer_level,&output_array_level);

		//関数名から余分なポインタや配列記号を削除する
		deletePointerAndArraySynbol(function_name);

		//もし、関数名が一致した場合はポインタレベルを返す
		if(CSTLString_compare(target_function_name, function_name) == 0){
			return output_pointer_level;
		}
	}

	return -1;
}
/**
パラメータリストを示すノードparam_info_nodeから、パラメータの情報を取得し、param_information_listに登録する。

@param param_info_node パラメータリストを示すノード
@param param_information_list 登録先のパラメータ情報リスト

@return なし
 */
void getParamInformationFromFunctionDifinition(AST *param_info_node, PARAM_INFORMATION_LIST *param_information_list){

	ASTListIterator ast_p;
	PARAM_INFORMATION *param_information;
	CSTLString *type;
	CSTLString *name;
	int array_level, pointer_level;
	int in_out_flag;
	//除外リスト
	char except_list[4][256] = { "{", "}", "struct_declaration_list", "enumerator_list"};

	//もし、parameter_declaration_with_declaratorを見つけられたら以下の操作を行う
	if(CSTLString_compare_with_char(param_info_node->name, "parameter_declaration_with_declarator") == 0){
		//先に型名を取得し、typedefでないかどうか確かめる
		type = CSTLString_new();
		getStringFromASTEnableExcept(type, ASTLIST_ITERATOR_1(param_info_node), 4, except_list);

		//typedefが見つからない場合の処理
		if(CSTLString_find(type, "typedef", 0) == CSTL_NPOS){
			//パラメータの変数名を取得する
			name = CSTLString_new();
			getStringFromAST(name, ASTLIST_ITERATOR_2(param_info_node));

			//ポインタレベルおよび配列レベルを取得する
			getPointerLevelAndArrayLevel(name, &pointer_level, &array_level);

			//パラメータの変数名から、ポインタおよび配列を示す記号を削除する
			deletePointerAndArraySynbol(name);

			//パラメータの型名およびポインタレベル・配列レベルからこのパラメータは入力型か出力型か判断する
			in_out_flag = getIN_OUT_FLAG(type, pointer_level, array_level);

			//新たにパラメータを生成し、パラメータリストparam_information_listに追加する
			param_information = new_PARAM_INFORMATION(type, name, array_level, pointer_level, in_out_flag);
			PARAM_INFORMATION_LIST_push_back_ref(param_information_list, param_information);
		}else{
			//取得した型名の文字列を破棄する。
			CSTLString_delete(type);
		}
	}

	//ASTに子ASTノードを持っている場合は、子ASTノードについても同じ探索を行う。
	for(ast_p = ASTList_begin(param_info_node->children); ast_p != ASTList_end(param_info_node->children); ast_p = ASTList_next(ast_p)){
		//再帰的にstruct_or_union_specifier定義が来た場合は、そこは探索させないようにする。
		if(CSTLString_compare_with_char(ASTList_data(ast_p)->name, "struct_or_union_specifier") != 0){
			getParamInformationFromFunctionDifinition(ASTList_data(ast_p), param_information_list);
		}
	}
}

/**
パラメータのポインタレベル・配列レベルおよび型名から、このパラメータは入力型か出力型か判定する。

@param param_type パラメータの型名
@param pointer_level ポインタのレベル
@param array_level 配列のレベル

@return 入力型ならば１、出力型ならば０を返す。
 */
int getIN_OUT_FLAG(CSTLString *param_type, int pointer_level, int array_level){
	//入力型か出力型かのフラグ
	int in_out_flag;

	//パラメータの型名にconstキーワードが含まれていた場合は、入力型とする
	if(CSTLString_find(param_type, "const", 0) != CSTL_NPOS){
		in_out_flag = PARAM_IN_TYPE;
	}
	//そうではなく、ポインタレベルおよび配列レベルが１以上ならば、出力型とする。そうでなければ入力型とする。
	else if(pointer_level > 0 || array_level > 0){
		in_out_flag = PARAM_OUT_TYPE;
	}else{
		in_out_flag = PARAM_IN_TYPE;
	}

	return in_out_flag;
}
