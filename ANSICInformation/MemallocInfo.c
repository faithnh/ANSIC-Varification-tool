#include "MemallocInfo.h"

//文字列の長さ
#define STRLEN 256

//sizeofで中身だけをとるために除外するリストの数
#define EXCEPT_SIZEOF_SIZE 3

//成功した場合
#define SUCCESS 1
//失敗した場合
#define FAILED 0

/**
メモリ割り当てに関する情報を格納するための構造体のデータを生成させる。
@param sizeof_type		sizeofの型名
@param realloc_target	realloc時のターゲットタイプ
@param size				malloc時のサイズ

@return メモリ割り当てに関する情報を格納するための構造体へのアドレスを返す。
*/
MEMALLOC_INFO *new_MEMALLOC_INFO_char(char *sizeof_type, ARRAY_OFFSET_LIST *realloc_target, char *size){
	CSTLString *sizeof_type_cstl = CSTLString_new();
	CSTLString_assign(sizeof_type_cstl, sizeof_type);

	CSTLString *size_cstl = CSTLString_new();
	CSTLString_assign(size_cstl, size);

	return new_MEMALLOC_INFO(sizeof_type_cstl, realloc_target, size_cstl);
}

/**
メモリ割り当てに関する情報を格納するための構造体のデータを生成させる。
@param sizeof_type		sizeofの型名
@param realloc_target	realloc時のターゲットタイプ
@param size				malloc時のサイズ

@return メモリ割り当てに関する情報を格納するための構造体へのアドレスを返す。
*/
MEMALLOC_INFO *new_MEMALLOC_INFO(CSTLString *sizeof_type, ARRAY_OFFSET_LIST *realloc_target, CSTLString *size){
	//新しいメモリ割り当てに関する情報を生成する
	MEMALLOC_INFO *new_memalloc_info = (MEMALLOC_INFO*)malloc(sizeof(MEMALLOC_INFO));

	//必要な情報を代入していく
	new_memalloc_info->sizeof_type = sizeof_type;
	new_memalloc_info->realloc_target = realloc_target;
	new_memalloc_info->size = size;

	//新しいメモリ割り当てに関する情報へのアドレスを返す
	return new_memalloc_info;
}

/**
指定されたASTノードからメモリ確保関係の関数に関する情報を取得する。
@param root 指定されたASTノード
@param vtlist reallocでreallocのターゲット情報のオフセット情報を取得するのに必要なプログラムの変数リスト
@return メモリ確保関係の構造体へのアドレスを返す。
*/
MEMALLOC_INFO *memoryAllocationAnarysis(AST *root, VARIABLE_TABLE_LIST *vtlist){

		MEMALLOC_INFO *memalloc_info = NULL;

		CSTLString *sizeof_type = CSTLString_new();
		CSTLString *constant = CSTLString_new();
		ARRAY_OFFSET_LIST *realloc_target = ARRAY_OFFSET_LIST_new();

		//呼び出した関数名を取得する
		CSTLString *function_name = CSTLString_new();
		getStringFromAST(function_name, ASTList_data(ASTList_begin(root->children)));

		//呼び出した関数名がmallocである場合
		if(CSTLString_compare_with_char(function_name, "malloc") == 0){

			//mallocの情報を取得する
			getMallocInformation(root, sizeof_type, constant);

			memalloc_info = new_MEMALLOC_INFO_char((char *)CSTLString_c_str(sizeof_type), realloc_target, (char *)CSTLString_c_str(constant));
		}
		//呼び出した関数名がcallocである場合
		else if(CSTLString_compare_with_char(function_name, "calloc") == 0){
			//mallocの情報を取得する
			getCallocInformation(root, sizeof_type, constant);

			memalloc_info = new_MEMALLOC_INFO_char((char *)CSTLString_c_str(sizeof_type), realloc_target, (char *)CSTLString_c_str(constant));
		}
		//呼び出した関数名がreallocである場合
		else if(CSTLString_compare_with_char(function_name, "realloc") == 0){
			//reallocの情報を取得する
			getReallocInformation(root, vtlist, sizeof_type, constant, realloc_target);

			memalloc_info = new_MEMALLOC_INFO_char((char *)CSTLString_c_str(sizeof_type), realloc_target , (char *)CSTLString_c_str(constant));
		}
		CSTLString_delete(function_name);

		return memalloc_info;
}


/**
malloc関数に関する情報を取得する。
@param root
@param sizeof_type sizeofでの型
@param constant sizeof以外での式（すなわち確保している型に対するサイズに相当する）

@return なし
*/
void getMallocInformation(AST *root, CSTLString *sizeof_type, CSTLString *constant)
{
	//sizeofが正しくつかわれているかどうかのフラグ
	int valid_sizeof_flag;
	//引数内のASTノード情報を取得する
	AST *argument;
	getArgumentAST(&argument, root, 1);
	//sizeofを探し、型を取得する。このとき、sizeofが２種類ある場合（sizeofに不都合がある場合）は0を返し、そうでない場合は1を返す
	valid_sizeof_flag = searchSizeof(sizeof_type, argument);

	//sizeofの定義に不都合がなければ
	if(valid_sizeof_flag){
		//式から、サイズを示す式を取得する
		getMallocMaxsize(constant, argument);
		//もし、sizeofの型が何も取得できなかった場合はnullとする。
		if(CSTLString_size(sizeof_type) == 0){
			CSTLString_assign(sizeof_type, "null");
		}
	}
	//sizeofに不都合な使い方をしている場合
	else{
		//不正なmallocの使い方であるとエラーを出力し、強制終了させる
		fprintf(stderr,"line:%d:Invalid malloc", root->line);
		exit(1);
	}

}
/**
calloc関数に関する情報を取得する。
@param root
@param sizeof_type sizeofでの型
@param constant sizeof以外での式（すなわち確保している型に対するサイズに相当する）

@return なし
*/
void getCallocInformation(AST *root, CSTLString *sizeof_type, CSTLString *constant)
{
	char exception_sizeof[][STRLEN] = {"sizeof","(",")"};

	//第二引数からsizeof_typeを取得する
	getArgumentStringEnableExcept(sizeof_type, root, 2, EXCEPT_SIZEOF_SIZE, exception_sizeof);

	//第一引数からconstantを取得する
	getArgumentString(constant, root, 1);

}

/**
realloc関数に関する情報を取得する。
@param root 対象のASTノード
@param vtlist 対象のプログラムの変数リスト
@param sizeof_type sizeofでの型
@param constant sizeof以外での式（すなわち確保している型に対するサイズに相当する）
@param realloc_target reallocが対象とするオフセット情報

@return なし
*/
void getReallocInformation(AST *root,VARIABLE_TABLE_LIST *vtlist, CSTLString *sizeof_type, CSTLString *constant, ARRAY_OFFSET_LIST *realloc_target){
	//第一、第二引数のAST
	AST *argument1, *argument2;
	//sizeofが正しくつかわれているかどうかのフラグ
	int valid_sizeof_flag;

	//realloc_targetでオフセットリストを取得するときに、重複したオフセット情報の取得を防止するためのASTアドレスリストを生成する
	ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();
	//switch_modeを使用するための変数（これも重複したオフセット情報の取得を防止するためにある）
	int switch_mode = 0;

	//関数のASTノードrootから第一引数からASTを取得し、realloc_targetにおけるオフセット情報を取得する
	getArgumentAST(&argument1, root, 1);
	getArgumentOffsetInfo:(argument1, vtlist, ignore_ast_list, realloc_target, root, &switch_mode);
	//関数のASTノードrootから第二引数のASTを取得
	getArgumentAST(&argument2, root, 2);

	//第二引数の式からsizeofを探し、型を取得する。このとき、sizeofが２種類ある場合（sizeofに不都合がある場合）は0を返し、そうでない場合は1を返す
	valid_sizeof_flag = searchSizeof(sizeof_type, argument2);

	//sizeofの定義に不都合がなければ
	if(valid_sizeof_flag){
		//第二引数の式から、サイズを示す式を取得する
		getMallocMaxsize(constant, argument2);
		//もし、sizeofの型が何も取得できなかった場合はnullとする。
		if(CSTLString_size(sizeof_type) == 0){
			CSTLString_assign(sizeof_type, "null");
		}
	}
	//sizeofに不都合な使い方をしている場合
	else{
		//不正なmallocの使い方であるとエラーを出力し、強制終了させる
		fprintf(stderr,"line:%d:Invalid realloc", root->line);
		exit(1);
	}

	//ignore_ast_listの解放
	ASTPOINTER_LIST_delete(ignore_ast_list);

}

/**
指定した式のASTに対して、sizeofを探索し、その型名をsizeof_typeで取得する。もし、式に異なる２種類のsizeof定義があれば、探索フラグは失敗する。
また、見つからなければ、sizeof_typeは何も指定していないままの状態である。
@param sizeof_type 出力するsizeofの型名
@param root 探索対象の式へのASTノード
@return なし
*/
int searchSizeof(CSTLString *sizeof_type, AST *root){
	//ASTの子ノードを参照させるためのイテレータ
	ASTListIterator ast_iterator;
	char exception_sizeof[EXCEPT_SIZEOF_SIZE][STRLEN] = {"sizeof","(",")"};
	int flag = SUCCESS;

	if(CSTLString_compare_with_char(root->name, "sizeof_expression") == 0){
		//sizeofのタイプを取得する
		CSTLString *tmp_sizeof_type = CSTLString_new();
		getStringFromASTEnableExcept(tmp_sizeof_type ,root, EXCEPT_SIZEOF_SIZE, exception_sizeof);

		//二度目の定義ではない場合（初回は何も定義していないので、文字列の長さが０である）、sizeofの型を定義する
		if(CSTLString_size(sizeof_type)==0 ){
			CSTLString_assign(sizeof_type, CSTLString_c_str(tmp_sizeof_type));
		}
		//二度目の定義である場合
		else{
			//同じ型名の定義である場合は、エラーとして終了させる
			if(CSTLString_compare(tmp_sizeof_type, sizeof_type) != 0){
				CSTLString_delete(tmp_sizeof_type);
				return FAILED;
			}
		}
		CSTLString_delete(tmp_sizeof_type);

	}

	//ASTの子ノードも参照させる
	for(ast_iterator = ASTList_begin(root->children);
		ast_iterator != ASTList_end(root->children);
		ast_iterator = ASTList_next(ast_iterator)){

		flag = searchSizeof(sizeof_type, ASTList_data(ast_iterator));
		if(flag == FAILED){
			break;
		}
	}
	return flag;
}
/**
getMallocMaxsizeの内部処理

@param constant 取得するsizeof以外での式（すなわち確保している型に対するサイズに相当する）
@param root mallocなどの関数内の式へのASTノード
@return なし
*/
void getMallocMaxsize_Internal(CSTLString *constant,AST *root){
	//ASTの子ノードを参照させるためのイテレータ
	ASTListIterator ast_iterator;

	//sizeof_expressionである場合は、その部分は１に直し、それより下位は参照しない
	if(CSTLString_compare_with_char(root->name, "sizeof_expression") == 0){
		CSTLString_append(constant, "1 ");
		return;
	}
	//そうでない場合
	else{
		//もし、リーフノードである場合（子ASTノードを持っていない場合）
		if(ASTList_size(root->children) == 0){
			//リーフノードの中身を追加する
			CSTLString_append(constant, CSTLString_c_str(root->content));
			CSTLString_append(constant, " ");
		}
	}

	//ASTの子ノードも参照させる
	for(ast_iterator = ASTList_begin(root->children);
		ast_iterator != ASTList_end(root->children);
		ast_iterator = ASTList_next(ast_iterator)){

		getMallocMaxsize_Internal(constant, ASTList_data(ast_iterator));

	}
}
/**
mallocなどの関数内の式から、確保したサイズを示す式を取得する。これは、sizeof(型)を１に書き直しながら、式を出力させることで行っている。

@param constant 取得するsizeof以外での式（すなわち確保している型に対するサイズに相当する）
@param root mallocなどの関数内の式へのASTノード
@return なし
*/
void getMallocMaxsize(CSTLString *constant,AST *root){
	//constantの中身を空にする
	CSTLString_assign(constant, "");
	//sizeofを1に変換しながら、rootより下位のノードの情報を取得する
	getMallocMaxsize_Internal(constant, root);

	//もし、最後に半角スペースが入っていたら削除する
	if(CSTLString_size(constant) > 0 && *CSTLString_at(constant, CSTLString_size(constant) - 1) == ' '){
		CSTLString_pop_back(constant);
	}
}

/*
指定したメモリ確保情報memalloc_infoの内容を出力する。

@param memalloc_info 出力対象のメモリ確保情報

@return なし
*/
void printMEMALLOC_INFO(MEMALLOC_INFO *memalloc_info){
	printf("------MALLOC_OFFSET_INFO------\n\n");
	printf("SIZEOF_TYPE = \"%s\"\n",CSTLString_c_str(memalloc_info->sizeof_type));
	printf("------REALLOC_TARGET_TYPE_INFO-----\n\n");
	printARRAY_OFFSET_LIST(memalloc_info->realloc_target);
	printf("-----------------------------------\n\n");
	printf("SIZE = \"%s\"\n",CSTLString_c_str(memalloc_info->size));
	printf("------------------------------\n\n");

}
