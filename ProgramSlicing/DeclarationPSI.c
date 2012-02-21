#include "DeclarationPSI.h"

#include "../ANSICInformation/ANSIC_CODE.h"

/**
宣言式のASTノードdeclarationからプログラムスライシングを抽出し、
プログラムスライシングリストexpr_slicing_listに追加する。

@param expr_slicing_list 追加先のプログラムスライシングリストexpr_slicing_list
@param declaration 式全般に関するASTノード
@param parent ノードを追加するときの親ノード
@param vtlist 変数テーブルリスト
@param function_information_list 関数に関する情報リスト
@param ignore_ast_list 重複防止のために無視するノードリスト
@param target_statement expression_statementを指し示すノード

@return なし
 */
void getVariableDeclarationtPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *declaration, EXPR_SLICING *parent,
		VARIABLE_TABLE_LIST *vtlist, FUNCTION_INFORMATION_LIST *function_information_list, ASTPOINTER_LIST *ignore_ast_list,
		AST *target_statement){

	//ASTの子ノードを参照させるためのイテレータ
	ASTListIterator ast_iterator;

	//代入式を見つけた場合
	if(CSTLString_compare_with_char(declaration->name, "init_declarator") == 0){
		EXPR_SLICING_LIST *children1 = EXPR_SLICING_LIST_new();
		EXPR_SLICING_LIST *children2 = EXPR_SLICING_LIST_new();

		//変数の定義に対するノードにおける各次元のポインタや配列のオフセットに関する情報のリスト
		ARRAY_OFFSET_LIST * declarator_array_offset_list = ARRAY_OFFSET_LIST_new();

		//初期の式における各次元のポインタや配列のオフセットに関する情報のリスト
		ARRAY_OFFSET_LIST * initializer_array_offset_list = ARRAY_OFFSET_LIST_new();

		AST *declarator_expression = getASTwithString(ASTLIST_ITERATOR_1(declaration), "IDENTIFIER", -1);

		AST *initializer_expression = ASTLIST_ITERATOR_3(declaration);

		//変数テーブルから、変数の定義に対するノードに該当する情報を探し、それに対する配列オフセット情報を取得する。（子ノードの１番目の参照）
		getDeclaratorArrayOffset(declarator_array_offset_list, declarator_expression, target_statement, vtlist);
		//初期の式について、配列オフセットリストを取得する（子ノードの３番目の参照）
		getARRAY_OFFSET_LIST(initializer_expression, initializer_array_offset_list,
				function_information_list, vtlist, ignore_ast_list, target_statement);

		//スライシングリストに追加する
		EXPR_SLICING_LIST_push_back_ref(expr_slicing_list, new_EXPR_SLICING(EXPR_SLICING_LIST_size(expr_slicing_list) + 1, target_statement,
				declarator_array_offset_list,initializer_array_offset_list, children1, children2, parent));

	}else if(CSTLString_compare_with_char(declaration->name, "t_init_declarator") == 0){
		EXPR_SLICING_LIST *children1 = EXPR_SLICING_LIST_new();
		EXPR_SLICING_LIST *children2 = EXPR_SLICING_LIST_new();

		//変数の定義に対するノードにおける各次元のポインタや配列のオフセットに関する情報のリスト
		ARRAY_OFFSET_LIST * declarator_array_offset_list = ARRAY_OFFSET_LIST_new();

		//初期の式における各次元のポインタや配列のオフセットに関する情報のリスト
		ARRAY_OFFSET_LIST * dependences = ARRAY_OFFSET_LIST_new();

		AST *declarator_expression = getASTwithString(ASTLIST_ITERATOR_1(declaration), "IDENTIFIER", -1);

		//変数テーブルから、変数の定義に対するノードに該当する情報を探し、それに対する配列オフセット情報を取得する。（子ノードの１番目の参照）
		getDeclaratorArrayOffset(declarator_array_offset_list, declarator_expression, target_statement, vtlist);

		//スライシングリストに追加する
		EXPR_SLICING_LIST_push_back_ref(expr_slicing_list, new_EXPR_SLICING(EXPR_SLICING_LIST_size(expr_slicing_list) + 1, target_statement,
				declarator_array_offset_list,dependences, children1, children2, parent));
	}
	else{
		//ASTの子ノードも参照させる
		for(ast_iterator = ASTList_begin(declaration->children);
			ast_iterator != ASTList_end(declaration->children);
			ast_iterator = ASTList_next(ast_iterator)){

			getVariableDeclarationtPSI(expr_slicing_list , ASTList_data(ast_iterator), parent,
					vtlist, function_information_list, ignore_ast_list, target_statement);

		}
	}
}

/**
型定義式のASTノードtypedef_declarationからプログラムスライシングを抽出し、
プログラムスライシングリストexpr_slicing_listに追加する。

@param expr_slicing_list 追加先のプログラムスライシングリストexpr_slicing_list
@param declaration 式全般に関するASTノード
@param parent ノードを追加するときの親ノード

@return なし
 */
void getTypedefDeclarationtPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *typedef_declaration, EXPR_SLICING *parent){
	//children1,children2を生成する（なにも入れない）
	EXPR_SLICING_LIST *children1 = EXPR_SLICING_LIST_new();
	EXPR_SLICING_LIST *children2 = EXPR_SLICING_LIST_new();

	//変数の定義に対するノードにおける各次元のポインタや配列のオフセットに関する情報のリスト（なにもいれない）
	ARRAY_OFFSET_LIST * target_variable = ARRAY_OFFSET_LIST_new();

	//初期の式における各次元のポインタや配列のオフセットに関する情報のリスト（なにもいれない）
	ARRAY_OFFSET_LIST * dependences = ARRAY_OFFSET_LIST_new();

	//スライシング情報を生成する
	EXPR_SLICING *new_expr_slicing = new_EXPR_SLICING(EXPR_SLICING_LIST_size(expr_slicing_list) + 1, typedef_declaration,
			target_variable, dependences, children1, children2, parent);

	//このスライシング情報は常に使用可能にする
	new_expr_slicing->flag = 1;

	//生成したスライシング情報をスライシングリストに追加する
	EXPR_SLICING_LIST_push_back_ref(expr_slicing_list, new_expr_slicing);
}

/**
宣言式のASTノードdeclarationから、関数に対するプログラムスライシングを抽出し、
プログラムスライシングリストexpr_slicing_listに追加する。

@param expr_slicing_list 追加先のプログラムスライシングリストexpr_slicing_list
@param declaration 式全般に関するASTノード
@param parent ノードを追加するときの親ノード
@param vtlist 変数テーブルリスト
@param function_information_list 関数に関する情報リスト
@param ignore_ast_list 重複防止のために無視するノードリスト
@param target_statement expression_statementを指し示すノード
@return なし
 */
void getDeclarationtPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *declaration, EXPR_SLICING *parent,
		VARIABLE_TABLE_LIST *vtlist, FUNCTION_INFORMATION_LIST *function_information_list, ASTPOINTER_LIST *ignore_ast_list,
		AST *target_statement){
	CSTLString *type = CSTLString_new();

	//型名を取得する
	getStringFromAST(type, ASTLIST_ITERATOR_1(declaration));

	//もし、型名にtypedefが含まれていた場合、型定義とみなし、スライシング情報を取得する
	if(CSTLString_find(type, "typedef", 0) != CSTL_NPOS){
		getTypedefDeclarationtPSI(expr_slicing_list, declaration, parent);
	}

	//typedefが含まれていなければ、変数宣言とみなし、スライシング情報を取得する
	else{
		getVariableDeclarationtPSI(expr_slicing_list, declaration, parent, vtlist,
				function_information_list, ignore_ast_list, target_statement);

	}

	CSTLString_delete(type);

}
