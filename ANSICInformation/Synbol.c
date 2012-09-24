#include "Synbol.h"
#include "../Library/Stack_int.h"

CSTL_LIST_IMPLEMENT(TYPEDEF_TABLE_LIST, TYPEDEF_TABLE);
CSTL_LIST_IMPLEMENT(STRUCT_TABLE_LIST, STRUCT_TABLE);
CSTL_LIST_IMPLEMENT(VARIABLE_TABLE_LIST, VARIABLE_TABLE);

#define NOT_DEFINE_LINE -1
#define INIT_MAX_LINE -1
#define PROGRAM_START_LINE 1
#define NOT_DEFINE_BLOCK_LEVEL -1
#define NOT_DEFINE_BLOCK_ID -1
/**
新しいtypedefテーブルのデータを生成させる。
@param target_type typedefの対象の型
@param change_type typedefで割り当てた後の新しい型名
@return 新しく生成されたtypedefテーブルのデータへのアドレスが返される。
*/
TYPEDEF_TABLE *new_TYPEDEF_TABLE(CSTLString *target_type, CSTLString *change_type){
	//typedefテーブルの生成
	TYPEDEF_TABLE* new_typedef_table = (TYPEDEF_TABLE*)malloc(sizeof(TYPEDEF_TABLE));

	//typedefテーブルに、typedefの対象の型や、割り当てた後の新しい型名を入れる
	new_typedef_table->target_type = target_type;

	new_typedef_table->change_type = change_type;

	//typedefテーブルのデータのアドレスを返す
	return new_typedef_table;
}
/**
新しい変数テーブルのデータを生成させる。
@param enable_start この変数の有効範囲の始まりの行数
@param enable_end この変数の有効範囲の終わりの行数
@param declaration_location_address この変数を宣言した場所を示すASTのアドレス
@param block_level この変数のブロックレベル（グローバル変数なら０とし、関数の中での定義なら１、その関数内のfor文などのブロック文ないでの宣言なら２とする）
@param block_id ブロックごとのID（基本的には0から始り、ブロックレベル２が２回目にくると、１となる）
@param idlist ブロックごとのID（これは変数スコープを識別するために使用する）
@param type 型名
@param variable_name 変数名
@param initializer 初期定義式へのASTノード

@return 新しく生成された変数テーブルのデータへのアドレスが返される。
*/
VARIABLE_TABLE *new_VARIABLE_TABLE(int enable_start, int enable_end, AST* declaration_location_address,
								   int block_level ,int block_id, IDLIST *idlist, CSTLString *type, CSTLString *variable_name, AST *initializer){
	//変数テーブルの生成
	VARIABLE_TABLE *new_variable_table = (VARIABLE_TABLE*)malloc(sizeof(VARIABLE_TABLE));

	//変数テーブルに、変数の有効範囲の始まり、終わり、型名、変数名を入れる
	new_variable_table->enable_start = enable_start;

	new_variable_table->enable_end = enable_end;

	new_variable_table->declaration_location_address = declaration_location_address;

	new_variable_table->block_level = block_level;

	new_variable_table->block_id = block_id;

	new_variable_table->idlist = idlist;

	new_variable_table->type = type;

	new_variable_table->variable_name = variable_name;

	new_variable_table->initiarizer = initializer;

	//変数テーブルのデータのアドレスを返す
	return new_variable_table;
}

/**
新しい構造体テーブルのデータを生成させる。
@param line 行数
@param type 型名
@param struct_name 構造体名(structかunionのいずれか）
@param member_list メンバリスト(変数テーブルより）
@return 新しく生成された構造体テーブルのデータへのアドレスが返される。
*/
STRUCT_TABLE *new_STRUCT_TABLE(int line, CSTLString *type, CSTLString *struct_name, VARIABLE_TABLE_LIST *member_list){
	//構造体テーブルの生成
	STRUCT_TABLE *new_struct_table = (STRUCT_TABLE*)malloc(sizeof(STRUCT_TABLE));

	//構造体テーブルに、行数、型名、構造体名、メンバリストを入れる
	new_struct_table->line = line;

	new_struct_table->type = type;

	new_struct_table->struct_name = struct_name;

	new_struct_table->member_list = member_list;

	//構造体テーブルのデータのアドレスを返す
	return new_struct_table;
}
/**
新しい構造体テーブルのデータを生成させる(char文字列対応)。
@param line 行数
@param type 型名(structかunionのいずれか）
@param struct_name 構造体の名前
@param member_list メンバリスト(変数テーブルより）
@return 新しく生成された構造体テーブルのデータへのアドレスが返される。
*/
STRUCT_TABLE *new_STRUCT_TABLE_with_char(int line, char *type, char *struct_name, VARIABLE_TABLE_LIST *member_list){
	//CSTLString属性の型名と構造体の名前を設定する
	CSTLString *CSTLtype = CSTLString_new();
	CSTLString *CSTLstruct_name = CSTLString_new();

	CSTLString_assign(CSTLtype, type);
	CSTLString_assign(CSTLstruct_name, struct_name);

	//構造体テーブルの生成
	STRUCT_TABLE *new_struct_table = new_STRUCT_TABLE(line, CSTLtype, CSTLstruct_name, member_list);

	//構造体テーブルのデータのアドレスを返す
	return new_struct_table;
}

/**
新しいtypedefテーブルのデータを生成させる(char文字列対応)。
@param target_type typedefの対象の型
@param change_type typedefで割り当てた後の新しい型名
@return 新しく生成されたtypedefテーブルのデータへのアドレスが返される。
*/
TYPEDEF_TABLE *new_TYPEDEF_TABLE_with_char(char *target_type, char *change_type){

	//CSTLString属性のtypedefの対象の型とtypedefで割り当てた後の新しい型名を設定する
	CSTLString *CSTLtarget_type = CSTLString_new();
	CSTLString *CSTLchange_type = CSTLString_new();

	CSTLString_assign(CSTLtarget_type, target_type);
	CSTLString_assign(CSTLchange_type, change_type);

	//typedefテーブルの生成
	TYPEDEF_TABLE *new_typedef_table = new_TYPEDEF_TABLE(CSTLtarget_type, CSTLchange_type);

	//typedefテーブルのデータのアドレスを返す
	return new_typedef_table;
}

/**
新しい変数テーブルのデータを生成させる(char文字列対応)。
@param enable_start この変数の有効範囲の始まりの行数
@param enable_end この変数の有効範囲の終わりの行数
@param declaration_location_address この変数を宣言した場所を示すASTのアドレス
@param block_level この変数のブロックレベル（グローバル変数なら０とし、関数の中での定義なら１、その関数内のfor文などのブロック文ないでの宣言なら２とする）
@param block_id ブロックごとのID（基本的には0から始り、ブロックレベル２が２回目にくると、１となる）
@param idlist ブロックごとのID（これは変数スコープを識別するために使用する）
@param type 型名
@param variable_name 変数名
@param initializer 初期定義式へのASTノード

@return 新しく生成された変数テーブルのデータへのアドレスが返される。
*/
VARIABLE_TABLE *new_VARIABLE_TABLE_with_char(int enable_start, int enable_end, AST* declaration_location_address,
								   int block_level ,int block_id,IDLIST *idlist, char *type, char *variable_name, AST *initializer){

	//CSTLString属性の型名と変数名を設定する
	CSTLString *CSTLtype = CSTLString_new();
	CSTLString *CSTLvariable_name = CSTLString_new();

	CSTLString_assign(CSTLtype, type);
	CSTLString_assign(CSTLvariable_name, variable_name);

	//変数テーブルの生成
	VARIABLE_TABLE *new_variable_table = new_VARIABLE_TABLE(enable_start, enable_end, declaration_location_address, block_level, block_id, idlist, CSTLtype, CSTLvariable_name, initializer);


	//変数テーブルのデータのアドレスを返す
	return new_variable_table;
}

/**
指定したASTノードから参照し、もしtypedef宣言の場合は、typedefテーブルに入れる。
@param typedef_table_list typedefテーブル
@param typelist 型リストへのASTノード
@param identifier 識別へのASTノード
@return なし
*/
void getTYPEDEF_TABLE_DATA(TYPEDEF_TABLE_LIST *typedef_table_list, AST *typelist, AST *identifier){
	CSTLString *identifier_str;
	//除外リスト
	char except_list[4][256] = { "{", "}", "struct_declaration_list", "enumerator_list"};
	//typelistのASTから型名に関する文字列の情報を取得する
	CSTLString *typelist_str = CSTLString_new();
	getStringFromASTEnableExcept(typelist_str, typelist, 4, except_list);

	//もし、型名に関する情報にtypedefが含まれた場合
	if(CSTLString_find(typelist_str, "typedef", 0) != CSTL_NPOS){
		//identifierのASTから割り当て後の変数名を取得する
		identifier_str = CSTLString_new();
		getStringFromAST(identifier_str, identifier);

		//型名に関する文字列の情報から、typedefを取り除く
		CSTLString_replace_string(typelist_str,"typedef ","");
		//取得した、型名に関する文字列の情報と、割り当て後の変数名を登録したtypedefテーブルのデータを作成する
		TYPEDEF_TABLE *new_typedef_table = new_TYPEDEF_TABLE(typelist_str, identifier_str);
		//作成したtypedefテーブルのデータをtypedefテーブルに入れる
		TYPEDEF_TABLE_LIST_push_back_ref(typedef_table_list, new_typedef_table);
	}
}

/**
指定したtypedefテーブルのリストから参照し、指定されたトークンに一致するようなtypedefテーブルデータが存在するかどうか調べる。
もし、見つければ、内容が指定されたトークンで、名前がTYPE_NAMEであるASTノードを生成し、それへのアドレスを返す。
見つけられなければ、名前がIDENTIFIERであるASTノードを生成し、それへのアドレスを返す。
@param typedef_table_list 指定したtypedefテーブルのリスト
@param token 指定されたトークン
@param line 指定された行数
@return 生成されたASTノードへのアドレスを返す。
*/

AST *getTYPEDEFfromAST(TYPEDEF_TABLE_LIST *typedef_table_list, char *token, int line){
	//指定されたトークンと一致するようなtypedefテーブルデータが存在するかどうかのフラグ
	int find_typedef_type = 0;

	//新しいASTノード
	AST* new_ast_node;
	//指定したtypedefテーブルのリストから、指定されたトークンに一致するようなtypedefテーブルデータが存在するかどうか調べる。
	TYPEDEF_TABLE_LISTIterator p;
	for(p = TYPEDEF_TABLE_LIST_begin(typedef_table_list); p != TYPEDEF_TABLE_LIST_end(typedef_table_list); p = TYPEDEF_TABLE_LIST_next(p)){
		//存在すれば、存在するというフラグを返し、調べる作業を終わらせる。
		if(CSTLString_compare_with_char((TYPEDEF_TABLE_LIST_data(p))->change_type, token) == 0){
			find_typedef_type = 1;
			break;
		}
	}

	//存在するかどうかのフラグを調べ、もし存在すれば、名前がTYPE_NAMEであり、内容が指定されたトークンのようなASTノードを生成する。
	if(find_typedef_type == 1){
		new_ast_node = new_AST("TYPE_NAME", token, line);
	}
	//存在しなければ、名前がIDENTIFIERであり、内容が指定されたトークンのようなASTノードを生成する。
	else{
		new_ast_node = new_AST("IDENTIFIER", token, line);
	}
	//生成されたASTノードへのアドレスを返却する。
	return new_ast_node;

}

/**
typedefテーブルのリストに登録されているものを出力させる。

@param typedef_table_list 出力対象のtypedefテーブルのリスト
@return なし
*/
void printTYPEDEF_TABLE_LIST(TYPEDEF_TABLE_LIST *typedef_table_list){
	TYPEDEF_TABLE_LISTIterator p;
	int counter = 1;
	printf("---------------TYPEDEF_TABLE---------------\n\n");
	//typedefテーブルのリストを全て参照する。
	for(p = TYPEDEF_TABLE_LIST_begin(typedef_table_list); p != TYPEDEF_TABLE_LIST_end(typedef_table_list); p = TYPEDEF_TABLE_LIST_next(p)){
		//target_type change_typeの順に出力させる。
		printf("---------------TYPEDEF_%d_INFO---------------\n\n", counter);
		printf("TYPEDEF_%d_TARGET_TYPE = \"%s\"\n", counter, CSTLString_c_str(TYPEDEF_TABLE_LIST_data(p)->target_type));
		printf("TYPEDEF_%d_CHANGE_TYPE = \"%s\"\n\n", counter, CSTLString_c_str(TYPEDEF_TABLE_LIST_data(p)->change_type));
		counter++;
	}
	printf("--------------------------------------------\n\n");
}

/** 指定されたASTノードから、構造体テーブルリストに構造体データを登録させる。
@param struct_table_list 登録先の構造体テーブルリスト
@param ast_data 指定されたASTノード
@return なし

*/
void getSTRUCT_TABLE_DATA(STRUCT_TABLE_LIST *struct_table_list, AST *ast_data){
	ASTListIterator ast_p;

	//探索の途中で、struct_or_union_specifierを見つけられたら、構造体データの登録作業を行う
	if(CSTLString_compare_with_char(ast_data->name, "struct_or_union_specifier") == 0){
			//構造体データを生成する
			fflush(stdout);
			getSTRUCT_DATA(ast_data, struct_table_list);

	}
	//ASTに子ASTノードを持っている場合は、子ASTノードについても同じ探索を行う。
	for(ast_p = ASTList_begin(ast_data->children); ast_p != ASTList_end(ast_data->children); ast_p = ASTList_next(ast_p)){
		getSTRUCT_TABLE_DATA(struct_table_list,ASTList_data(ast_p));
	}

}

/** 構造体テーブルリストに同じ定義がないかどうかを調べる。
@param struct_table_list 検索対象の構造体テーブルリスト
@param target 検索する文字列
@return 見つけられたら、１を返し、そうでなければ０を返す。
*/
int find_STRUCT_TABLE_DATA(STRUCT_TABLE_LIST *struct_table_list, CSTLString *target){
	STRUCT_TABLE_LISTIterator stlist_p;
	int find_flag = 0;
	for(stlist_p = STRUCT_TABLE_LIST_begin(struct_table_list) ;
		stlist_p != STRUCT_TABLE_LIST_end(struct_table_list) ;
		stlist_p = STRUCT_TABLE_LIST_next(stlist_p)){

			if(CSTLString_find(STRUCT_TABLE_LIST_data(stlist_p)->struct_name, CSTLString_c_str(target), 0) != CSTL_NPOS){
				find_flag = 1;
				break;
			}
	}

	return find_flag;
}

/** 指定されたASTノードから、構造体データを作成させ、構造体テーブルのリストへ登録させる。
@param ast_data 指定されたASTノード
@param struct_table_data 登録先の構造体テーブルリスト
@return なし

*/
void getSTRUCT_DATA(AST *ast_data, STRUCT_TABLE_LIST *struct_table_data){
	//構造体の名前と型へのASTを取得する。
	AST *struct_name = ASTList_data(ASTList_next(ASTList_begin(ast_data->children)));
	AST *type = ASTList_data(ASTList_begin(ast_data->children));

	STRUCT_TABLE *struct_data;
	//構造体テーブルのリストから、すでに同じ定義がないかどうか調べる。同じ定義がなければ、構造体データを生成する処理を行う。
	if(find_STRUCT_TABLE_DATA(struct_table_data, struct_name->content) == 0){
		//structテーブルのリストに登録するためのデータ（以下構造体データ）を１つ生成させる。
		struct_data = (STRUCT_TABLE*)malloc(sizeof(STRUCT_TABLE));

		//struct_or_union_specifierの初めはstructかunionが必ずくるので、構造体データのtypeとして登録する。
		CSTLString *type_str = CSTLString_new();
		getStringFromAST(type_str,type);
		struct_data->type = type_str;
		//2つ目はIDENTIFIERが来るはずなので、構造体データのstruct_nameとして登録する
		CSTLString *struct_name_str = CSTLString_new();
		getStringFromAST(struct_name_str,struct_name);
		struct_data->struct_name = struct_name_str;
		struct_data->member_list = VARIABLE_TABLE_LIST_new();
		//メンバ登録作業を行う
		getMemberList(struct_data->member_list, ast_data);

		//最終的に作成された構造体データは構造体テーブルのリストへ登録する
		STRUCT_TABLE_LIST_push_back_ref(struct_table_data, struct_data);
	}
}

/** 指定されたASTノードから、メンバリストを生成する。
@param member_list 登録対象のメンバリスト
@param ast_data 指定されたASTノード
@return 作成された構造体データへのアドレスを返却する。

*/
void getMemberList(VARIABLE_TABLE_LIST *member_list, AST *ast_data){
	//メンバの定義を探す。すなわち、stract_declarationを探す。
	ASTListIterator ast_p;
	//除外リスト
	char except_list[4][256] = { "{", "}", "struct_declaration_list", "enumerator_list"};
	//もし、stract_declarationを見つけられたら以下の操作を行う
	if(CSTLString_compare_with_char(ast_data->name, "struct_declaration") == 0){

		//1つ目はタイプが来るはずなので、これから宣言するnew_typeとして登録する。
		CSTLString *new_type = CSTLString_new();
		getStringFromASTEnableExcept(new_type, ASTList_data(ASTList_begin(ast_data->children)), 4, except_list);
		//declaratorを探し、それを見つけたら指定した型の変数としてメンバリストに登録する
		//変数の有効範囲もしくはブロックレベル関係はすべて無効である（構造体テーブルでは不要なため）
		//また、メンバに対するASTアドレスは不要なので設定しない（NULLにする）
		getDeclaratorFromAST(CSTLString_c_str(new_type), ast_data, member_list,
			NOT_DEFINE_LINE, NOT_DEFINE_LINE, NOT_DEFINE_BLOCK_LEVEL, NOT_DEFINE_BLOCK_ID, NULL);

		//new_typeを開放する。
		CSTLString_delete(new_type);
	}

	//ASTに子ASTノードを持っている場合は、子ASTノードについても同じ探索を行う。
	for(ast_p = ASTList_begin(ast_data->children); ast_p != ASTList_end(ast_data->children); ast_p = ASTList_next(ast_p)){
		//再帰的にstruct_or_union_specifier定義が来た場合は、そこは探索させないようにする。
		if(CSTLString_compare_with_char(ASTList_data(ast_p)->name, "struct_or_union_specifier") != 0){
			getMemberList(member_list,ASTList_data(ast_p));
		}
	}

}

/** 指定されたASTノードから、declaratorを探し、それを見つけたら指定した型の変数として変数リストに登録する。
@param type 指定した型
@param ast_data 指定されたASTノード
@param member_list 登録先の変数リスト
@param enable_start 変数スコープの有効範囲の開始
@param enable_end 変数スコープの有効範囲の終わり
@param block_level この変数のブロックレベル
@param block_id ブロックを識別するための識別番号
@param declaration_location_address この宣言自体のASTへのアドレス(検証式の生成に必要)

@return なし
*/
void getDeclaratorFromAST(char const *type, AST *ast_data, VARIABLE_TABLE_LIST *member_list,
						  int enable_start, int enable_end ,int block_level, int block_id, AST* declaration_location_address){
	ASTListIterator ast_p;
	VARIABLE_TABLE *variable_data;


	//もし、declaratorを見つけられたら以下の操作を行う
	if(CSTLString_compare_with_char(ast_data->name, "t_init_declarator") == 0){
		//メンバ宣言として登録するためのデータ（以下メンバ宣言データ）を１つ生成する。
		CSTLString *CSTLtype = CSTLString_new();
		CSTLString_assign(CSTLtype, type);
		//変数名を取得する
		CSTLString *CSTLvariable_name = CSTLString_new();
		getStringFromAST(CSTLvariable_name, ast_data);

		//この宣言自体のアドレスがNULLでなければ、それについての登録を行う
		if(declaration_location_address != NULL){
			variable_data = new_VARIABLE_TABLE(enable_start, enable_end, declaration_location_address , block_level, block_id, declaration_location_address->idlist, CSTLtype, CSTLvariable_name, NULL);
		}else{
			variable_data = new_VARIABLE_TABLE(enable_start, enable_end, declaration_location_address , block_level, block_id, NULL, CSTLtype, CSTLvariable_name, NULL);
		}
		//メンバリストに登録する
		VARIABLE_TABLE_LIST_push_back_ref(member_list, variable_data);
	}else if(CSTLString_compare_with_char(ast_data->name, "init_declarator") == 0){
			//メンバ宣言として登録するためのデータ（以下メンバ宣言データ）を１つ生成する。
			CSTLString *CSTLtype = CSTLString_new();
			CSTLString_assign(CSTLtype, type);
			//変数名を取得する
			CSTLString *CSTLvariable_name = CSTLString_new();
			getStringFromAST(CSTLvariable_name, ASTList_data(ASTList_begin(ast_data->children)));

		//この宣言自体のアドレスがNULLでなければ、それについての登録を行う
		if(declaration_location_address != NULL){
			variable_data = new_VARIABLE_TABLE(enable_start, enable_end, declaration_location_address ,
					block_level, block_id, declaration_location_address->idlist, CSTLtype, CSTLvariable_name,
					ASTList_data(ASTList_next(ASTList_next(ASTList_begin(ast_data->children)))));
		}else{
			variable_data = new_VARIABLE_TABLE(enable_start, enable_end, declaration_location_address ,
					block_level, block_id, NULL, CSTLtype, CSTLvariable_name,
					ASTList_data(ASTList_next(ASTList_next(ASTList_begin(ast_data->children)))));
		}
		//メンバリストに登録する
		VARIABLE_TABLE_LIST_push_back_ref(member_list, variable_data);
	}
	//ASTに子ASTノードを持っている場合は、子ASTノードについても同じ探索を行う。
	for(ast_p = ASTList_begin(ast_data->children); ast_p != ASTList_end(ast_data->children); ast_p = ASTList_next(ast_p)){
		//再帰的にstruct_or_union_specifier定義が来た場合は、そこは探索させないようにする。
		if(CSTLString_compare_with_char(ASTList_data(ast_p)->name, "struct_or_union_specifier") != 0){
			getDeclaratorFromAST(type, ASTList_data(ast_p), member_list,
						  enable_start, enable_end ,block_level, block_id, declaration_location_address);
		}
	}
}

/**
構造体テーブルのリストの内容を出力させる。
@param struct_table_list 出力対象の構造体テーブルのリスト
@return なし

*/
void printSTRUCT_TABLE_LIST(STRUCT_TABLE_LIST *struct_table_list){
	STRUCT_TABLE_LISTIterator stlist_p;
	VARIABLE_TABLE_LISTIterator member_p;
	//メンバを数えるためのカウンタ
	int member_counter;
	//構造体を数えるためのカウンタ
	int struct_counter = 1;
	printf("---------------STRUCT_TABLE---------------\n\n");
	//構造体テーブルのリストをすべて参照する
	for(stlist_p = STRUCT_TABLE_LIST_begin(struct_table_list) ;
		stlist_p != STRUCT_TABLE_LIST_end(struct_table_list) ;
		stlist_p = STRUCT_TABLE_LIST_next(stlist_p)){
			printf("---------------STRUCT_%d_INFO---------------\n\n", struct_counter);
			//構造体のタイプ(structかunion）と名前を表示させる
			printf("STRUCT%d_TYPE = \"%s\"\n", struct_counter, CSTLString_c_str(STRUCT_TABLE_LIST_data(stlist_p)->type));
			//構造体の名前を表示させる
			printf("STRUCT%d_NAME = \"%s\"\n", struct_counter, CSTLString_c_str(STRUCT_TABLE_LIST_data(stlist_p)->struct_name));
			printf("\n");
			member_counter = 1;
			//構造体にあるメンバリストを参照する
			for(member_p = VARIABLE_TABLE_LIST_begin(STRUCT_TABLE_LIST_data(stlist_p)->member_list) ;
				member_p != VARIABLE_TABLE_LIST_end(STRUCT_TABLE_LIST_data(stlist_p)->member_list) ;
				member_p = VARIABLE_TABLE_LIST_next(member_p)){
					//メンバのタイプ（型名）と名前を表示させる
					printf("\tMEMBER%d_TYPE = \"%s\"\n", member_counter, CSTLString_c_str(VARIABLE_TABLE_LIST_data(member_p)->type));
					printf("\tMEMBER%d_NAME = \"%s\"\n", member_counter, CSTLString_c_str(VARIABLE_TABLE_LIST_data(member_p)->variable_name));
					printf("\n");
					member_counter++;
			}

		struct_counter++;

	}

	printf("------------------------------------------\n\n");
}

/**
getVARIABLE_TABLE_LISTの内部処理である。
@param variable_table_list 変数テーブルのリスト
@param ast_data 対象のASTノード
@param line_stack 行数のスタック（変数のスコープを反映させるために使用する）
@param max_line プログラムの最大行数（変数のスコープに反映させるために使用する）

@return なし
*/

void getVARIABLE_TABLE_LIST_Internal(VARIABLE_TABLE_LIST *variable_table_list, AST *ast_data, STACK_INT *line_stack, int *max_line)
{
	ASTListIterator ast_p;
	VARIABLE_TABLE_LISTIterator vtlist;
	VARIABLE_TABLE *variable_data;
	int start_line;
	int end_line;
	int block_level;
	int block_id;
	CSTLString *type;

	//除外リスト
	char except_list[4][256] = { "{", "}", "struct_declaration_list", "enumerator_list"};
	//ノードごとに行数を比較・更新することで、プログラムの最大の行数を取得する。
	if(*max_line < ast_data->line){
		*max_line = ast_data->line;
	}

	//もし、declaration_with_initを見つけられたら以下の操作を行う
	if(CSTLString_compare_with_char(ast_data->name, "declaration_with_init") == 0){
		//先に型名を取得し、typedefでないかどうか確かめる
		type = CSTLString_new();
		getStringFromASTEnableExcept(type, ASTList_data(ASTList_begin(ast_data->children)), 4, except_list);
		//typedefが見つからない場合の処理
		if(CSTLString_find(type, "typedef", 0) == CSTL_NPOS){

			//ブロックidの指定（グローバルの場合は常に0とし、そうでない場合は、ブロックレベルの現れた回数を入力する。
			if(!STACK_INT_empty(line_stack)){
				start_line = *STACK_INT_at(line_stack, STACK_INT_size(line_stack) - 1);
			}else{
				start_line = PROGRAM_START_LINE;
			}

			block_id = ast_data->block_id;
			//ブロックレベルの指定（グローバルなら０、何らかの関数のなかでは１、その中のfor文とかのブロック文内では２と指定する）
			block_level = ast_data->block_level;

			//Declaratorを探し出し、変数テーブルのリストに登録していく
			getDeclaratorFromAST(CSTLString_c_str(type), ASTList_data(ASTList_next(ASTList_begin(ast_data->children))),
				variable_table_list, start_line, NOT_DEFINE_LINE , block_level, block_id, ast_data);
		}else{
			//取得した型名の文字列を破棄する。
			CSTLString_delete(type);
		}

	}
	//プログラム途中で、"{"が現れた場合、ブロックレベルを上げる
	else if(CSTLString_compare_with_char(ast_data->name, "{") == 0){
		//ブロックの行数をプッシュバックする
		STACK_INT_push_back(line_stack, ast_data->line);

	}

	else if(CSTLString_compare_with_char(ast_data->name, "}") == 0){

		if(!STACK_INT_empty(line_stack)){
			start_line = *STACK_INT_back(line_stack);
		}else{
			start_line = PROGRAM_START_LINE;
		}
		end_line = ast_data->line;
		STACK_INT_pop_back(line_stack);

		for(vtlist = VARIABLE_TABLE_LIST_begin(variable_table_list);
			vtlist != VARIABLE_TABLE_LIST_end(variable_table_list);
			vtlist = VARIABLE_TABLE_LIST_next(vtlist)){
				if(VARIABLE_TABLE_LIST_data(vtlist)->enable_start == start_line){
						VARIABLE_TABLE_LIST_data(vtlist)->enable_end = end_line;
				}
		}
	}


	//ASTに子ASTノードを持っている場合は、子ASTノードについても同じ探索を行う。
	for(ast_p = ASTList_begin(ast_data->children); ast_p != ASTList_end(ast_data->children); ast_p = ASTList_next(ast_p)){
		//再帰的にstruct_or_union_specifier定義が来た場合は、そこは探索させないようにする。
		if(CSTLString_compare_with_char(ASTList_data(ast_p)->name, "struct_or_union_specifier") != 0){
			getVARIABLE_TABLE_LIST_Internal(variable_table_list, ASTList_data(ast_p), line_stack, max_line);
		}
	}
}
/**
対象のASTノードから変数テーブルのリストを登録する。
@param variable_table_list 変数テーブルのリスト
@param ast_data 対象のASTノード

@return なし
*/

void getVARIABLE_TABLE_LIST(VARIABLE_TABLE_LIST *variable_table_list, AST *ast_data)
{
	VARIABLE_TABLE_LISTIterator vtlist;
	//ブロック単位の行スタックの配置
	STACK_INT *line_stack = STACK_INT_new();

	//プログラムの最大行数
	int max_line = -1;
	getVARIABLE_TABLE_LIST_Internal(variable_table_list, ast_data, line_stack, &max_line);
	//ブロック単位の行スタックの破棄
	STACK_INT_delete(line_stack);
	//変数リストのスコープの終わりがNOT_DEFINE_LINEであるものをすべてプログラムの最大行にする。
	for(vtlist = VARIABLE_TABLE_LIST_begin(variable_table_list);
	vtlist != VARIABLE_TABLE_LIST_end(variable_table_list);
	vtlist = VARIABLE_TABLE_LIST_next(vtlist)){
		if(VARIABLE_TABLE_LIST_data(vtlist)->enable_end == NOT_DEFINE_LINE){
			VARIABLE_TABLE_LIST_data(vtlist)->enable_end = max_line;
		}
	}
}

/**
関数のパラメータリストを示すASTノードから、parameter_declarationを見つけ、そこから変数テーブルのリストに登録させる。
@param variable_table_list 変数テーブルのリスト
@param ast_data 対象のASTノード
@param enable_start 有効範囲の開始
@param enable_end 有効範囲の終了
@return なし
*/
void getParameterData(VARIABLE_TABLE_LIST *variable_table_list, AST *ast_data, AST *enable_start, AST *enable_end){
	ASTListIterator ast_p;
	VARIABLE_TABLE_LISTIterator vtlist;
	VARIABLE_TABLE *variable_data;
	CSTLString *type;
	CSTLString *name;
	//除外リスト
	char except_list[4][256] = { "{", "}", "struct_declaration_list", "enumerator_list"};

	//もし、parameter_declaration_with_declaratorを見つけられたら以下の操作を行う
	if(CSTLString_compare_with_char(ast_data->name, "parameter_declaration_with_declarator") == 0){
		//先に型名を取得し、typedefでないかどうか確かめる
		type = CSTLString_new();
		getStringFromASTEnableExcept(type, ASTList_data(ASTList_begin(ast_data->children)), 4, except_list);
		//typedefが見つからない場合の処理
		if(CSTLString_find(type, "typedef", 0) == CSTL_NPOS){

			name = CSTLString_new();
			getStringFromAST(name, ASTList_data(ASTList_next(ASTList_begin(ast_data->children))));

			variable_data = new_VARIABLE_TABLE(enable_start->line, enable_end->line, enable_start,
			 enable_start->block_level, enable_start->block_id, enable_start->idlist, type, name, NULL);

			VARIABLE_TABLE_LIST_push_back_ref(variable_table_list, variable_data);
		}else{
			//取得した型名の文字列を破棄する。
			CSTLString_delete(type);
		}
	}

	//ASTに子ASTノードを持っている場合は、子ASTノードについても同じ探索を行う。
	for(ast_p = ASTList_begin(ast_data->children); ast_p != ASTList_end(ast_data->children); ast_p = ASTList_next(ast_p)){
		//再帰的にstruct_or_union_specifier定義が来た場合は、そこは探索させないようにする。
		if(CSTLString_compare_with_char(ASTList_data(ast_p)->name, "struct_or_union_specifier") != 0){
			getParameterData(variable_table_list, ASTList_data(ast_p), enable_start, enable_end);
		}
	}

}

/**
対象のASTノードから関数を探し、関数内の引数を変数テーブルのリストに登録する。
@param variable_table_list 変数テーブルのリスト
@param ast_data 対象のASTノード
@return なし
*/
void getParameterVARIABLE_TABLE_LIST(VARIABLE_TABLE_LIST *variable_table_list, AST *ast_data){
	ASTListIterator ast_p;
	AST *enable_start, *enable_end;
	//もし、function_definition_type_bを見つけられたら以下の操作を行う
	if(CSTLString_compare_with_char(ast_data->name, "function_definition_type_b") == 0){
		enable_start = ASTList_data(ASTList_next(ASTList_next(ASTList_begin(ast_data->children))));
		enable_end = ASTList_data(ASTList_next(ASTList_next(ASTList_begin(ast_data->children))));
		enable_start = ASTList_data(ASTList_begin(enable_start->children));
		enable_end = ASTList_data(ASTList_next(ASTList_next(ASTList_begin(enable_end->children))));

		getParameterData(variable_table_list,ASTList_data(ASTList_next(ASTList_begin(ast_data->children))), enable_start, enable_end);
	}
	//ASTに子ASTノードを持っている場合は、子ASTノードについても同じ探索を行う。
	for(ast_p = ASTList_begin(ast_data->children); ast_p != ASTList_end(ast_data->children); ast_p = ASTList_next(ast_p)){
		//再帰的にstruct_or_union_specifier定義が来た場合は、そこは探索させないようにする。
		if(CSTLString_compare_with_char(ASTList_data(ast_p)->name, "struct_or_union_specifier") != 0){
			getParameterVARIABLE_TABLE_LIST(variable_table_list, ASTList_data(ast_p));
		}
	}
}

/**
変数テーブルのリストの内容を出力させる。
@param variable_table_list 出力対象の変数テーブルのリスト
@return なし

*/
void printVARIABLE_TABLE_LIST(VARIABLE_TABLE_LIST *variable_table_list)
{
	VARIABLE_TABLE_LISTIterator vtlist;
	int counter = 1;

	printf("---------------VARIABLE_TABLE---------------\n\n");

	for(vtlist = VARIABLE_TABLE_LIST_begin(variable_table_list);
	vtlist != VARIABLE_TABLE_LIST_end(variable_table_list);
	vtlist = VARIABLE_TABLE_LIST_next(vtlist)){
		printf("---------------VARIABLE_%d_INFO---------------\n\n", counter);
		printf("VARIABLE_%d_TYPE = \"%s\"\n", counter, CSTLString_c_str(VARIABLE_TABLE_LIST_data(vtlist)->type));
		printf("VARIABLE_%d_NAME = \"%s\"\n", counter, CSTLString_c_str(VARIABLE_TABLE_LIST_data(vtlist)->variable_name));
		printf("VARIABLE_%d_ENABLE_START = \"%d\"\n", counter, VARIABLE_TABLE_LIST_data(vtlist)->enable_start);
		printf("VARIABLE_%d_ENABLE_END = \"%d\"\n", counter, VARIABLE_TABLE_LIST_data(vtlist)->enable_end);
		printf("VARIABLE_%d_DECLARATION_LOCATION = \"%d\"\n", counter, VARIABLE_TABLE_LIST_data(vtlist)->declaration_location_address->line);
		printf("VARIABLE_%d_BLOCK_LEVEL = \"%d\"\n", counter, VARIABLE_TABLE_LIST_data(vtlist)->block_level);
		printf("VARIABLE_%d_BLOCK_ID = \"%d\"",counter, VARIABLE_TABLE_LIST_data(vtlist)->block_id);
		printf("VARIABLE_%d_IDLIST = \"",counter);
		printIDLIST(VARIABLE_TABLE_LIST_data(vtlist)->idlist, 0);
		printf("\"\n");
		counter++;
	}
	printf("--------------------------------------------\n\n");
}

/**
変数テーブルから、ポインタの次元および配列の次元を取得する。
@param variable_table_data 変数テーブルのリスト
@param output_pointer_level 出力されるポインタレベル
@param output_array_level 出力される配列レベル
@return なし
*/
void getPointerLevelAndArrayLevelFromVARIABLE_TABLE(VARIABLE_TABLE *variable_table_data, int *output_pointer_level, int *output_array_level){
	getPointerLevelAndArrayLevel(variable_table_data->variable_name, output_pointer_level, output_array_level);
}

/**
対象の識別子のポインタの次元および配列の次元を取得する。
@param target_identifier 対象の識別子
@param output_pointer_level 出力されるポインタレベル
@param output_array_level 出力される配列レベル
@return なし
*/
void getPointerLevelAndArrayLevel(CSTLString *target_identifier, int *output_pointer_level, int *output_array_level){
	int i;

	*output_pointer_level = 0;
	*output_array_level = 0;
	//変数名の文字列を調べる
	for(i = 0; i < CSTLString_size(target_identifier); i++){
		//配列を示す'['が来た場合は、配列の次元を増やす
		if(*CSTLString_at(target_identifier, i) == '['){
			*output_array_level = *output_array_level + 1;
		}
		//ポインタを示す'*'が来た場合は、ポインタの次元を増やす
		else if(*CSTLString_at(target_identifier, i) == '*'){
			*output_pointer_level = *output_pointer_level + 1;
		}
	}
}
/**
変数テーブルリストvariable_table_listから、指定した変数スコープのIDLIST target_idlistとtarget_stringに該当ような変数テーブルへのアドレスを返す。

@param target_idlist 指定した変数スコープのIDLIST
@param target_string 対象の変数名
@param variable_table_list 変数テーブルリスト

@return 上記の処理から見つけた変数テーブルへのアドレスを返す。見つからなければNULLを返す。
*/
VARIABLE_TABLE *searchVARIABLE_TABLE_LIST(IDLIST *target_idlist, CSTLString *target_string, VARIABLE_TABLE_LIST* variable_table_list){
	VARIABLE_TABLE_LISTIterator vi;

	//変数テーブルデータ
	VARIABLE_TABLE *variable_table_data = NULL;

	CSTLString *target = CSTLString_new();

	for(vi = VARIABLE_TABLE_LIST_begin(variable_table_list);
		vi != VARIABLE_TABLE_LIST_end(variable_table_list);
		vi = VARIABLE_TABLE_LIST_next(vi)){

		//元の変数名と比較
		CSTLString_assign(target, CSTLString_c_str(VARIABLE_TABLE_LIST_data(vi)->variable_name));
		//指定した変数名と比較するためにポインタや配列を示す記号を全て削除する
		deletePointerAndArraySynbol(target);

		//指定した変数名と変数リストの変数の名前が一致し、変数スコープ内に収まっているとき
		if(CSTLString_compare(target_string, target) == 0 &&
			IDLIST_compare_with(target_idlist, VARIABLE_TABLE_LIST_data(vi)->idlist) == 1){

			//すでに見つかっていない場合は変数テーブルデータに設定する
			if(variable_table_data == NULL){
				variable_table_data = VARIABLE_TABLE_LIST_data(vi);
			}
			//すでに設定していて、ブロックレベルが高ければ、変数テーブルデータに設定する
			else if(variable_table_data->block_level < VARIABLE_TABLE_LIST_data(vi)->block_level){
				variable_table_data = VARIABLE_TABLE_LIST_data(vi);
			}
		}

	}

	return variable_table_data;
}


/**
変数名から配列およびポインタを示す記号を全て削除する。
@param target 変更対象の変数名
@return なし
*/
void deletePointerAndArraySynbol(CSTLString *target){
	int i;
	//配列の中であるフラグ
	int array_flag = 0;
	i = 0;
	//文字列全体を探索
	while(i < CSTLString_size(target)){
		//配列の中であるフラグが立っていない（配列の中ではない）場合
		if(array_flag == 0){
			//もし、半角スペースかポインタを示すアスタリスクを見つけたらその文字を削除する
			//また、丸カッコが来ても削除させる
			if(*CSTLString_at(target, i) == ' ' || *CSTLString_at(target, i) == '*' ||
			 *CSTLString_at(target, i) == '(' || *CSTLString_at(target, i) == ')'){
				CSTLString_erase(target, i, 1);
				continue;
			}
			//配列の始まりを示す記号を見つけたら、配列の中であるフラグが立て、その文字を削除する
			else if(*CSTLString_at(target, i) == '[' ){
				CSTLString_erase(target, i, 1);
				array_flag = 1;
				continue;
			}
			//削除されていない場合のみ、次の文字へ移動する
			i++;
		}
		//配列の中であるフラグが立っている（配列の中である）場合
		else{
			//配列の終わりを示す記号が見つかれば、配列の中であるフラグが下げる
			if(*CSTLString_at(target, i) == ']' ){
				array_flag = 0;
			}
			//配列の終わりを示す記号を見つけるまでずっと文字を削除する
			CSTLString_erase(target, i, 1);
			continue;
		}
	}
}

/**
変数名からポインタを示す記号のみ全て削除する。
@param target 変更対象の変数名
@return なし
*/
void deletePointer(CSTLString *target){
	CSTLString_replace_string(target, "* ", "");
}

CSTLString *getTypeOfVariable(CSTLString *variable_name , VARIABLE_TABLE *variable_table){
	CSTLString *output = CSTLString_new();
	CSTLString_assign(output, CSTLString_c_str(variable_table->variable_name));
	size_t idx = CSTLString_find(output, CSTLString_c_str(variable_name), 0);
	CSTLString_replace_len(output, idx, CSTLString_size(variable_name),
			CSTLString_c_str(variable_table->type), CSTLString_size(variable_table->type));

	return output;
}
