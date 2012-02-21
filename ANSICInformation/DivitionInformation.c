 #include"DivitionInformation.h"
 #include<stdio.h>
 #include<stdlib.h>

 #define ASTLIST_ITERATOR_1(target) ASTList_data(ASTList_begin(target->children))
 #define ASTLIST_ITERATOR_2(target) ASTList_data(ASTList_next(ASTList_begin(target->children)))
 #define ASTLIST_ITERATOR_3(target) ASTList_data(ASTList_next(ASTList_next(ASTList_begin(target->children))))

//除算か剰余算かどうかのフラグ
#define TYPE_DIV 0
#define TYPE_MOD 1

 /**
 DIVITION_INFORMATIONのリスト
 */
 CSTL_LIST_IMPLEMENT(DIVITION_INFORMATION_LIST, DIVITION_INFORMATION)

 /**
 除算および剰余算に関する情報を生成する。

 @param target_expression 対象の式へのASTノードのアドレス
 @param type 除算か剰余かどうかのタイプ　０：除算式　１：剰余式
 @param statement 除算および剰余以下の式
 @param identifiers 式内の識別子一覧

 @return 生成された情報へのアドレスが返される
 */
 DIVITION_INFORMATION *new_DIVITION_INFORMATION(AST *target_expression, int type, CSTLString *statement, ARRAY_OFFSET_LIST *identifiers){
	//除算および剰余算に関する情報を新たに生成する
	DIVITION_INFORMATION *new_divition_information = (DIVITION_INFORMATION*)malloc(sizeof(DIVITION_INFORMATION));

	//もし生成に失敗した場合はメモリ不足としてエラーを返し強制終了させる
	if(new_divition_information == NULL){
		fprintf(stderr, "メモリ不足です\n");
		exit(1);
	}
	//生成に成功したら、必要な情報を入れていく
	else{
		new_divition_information->target_expression = target_expression;
		new_divition_information->type = type;
		new_divition_information->statement = statement;
		new_divition_information->identifiers = identifiers;
	}
	return new_divition_information;
 }

 /**
 除算および剰余算に関する情報を生成する。

 @param target_expression 対象の式へのASTノードのアドレス
 @param type 除算か剰余かどうかのタイプ　０：除算式　１：剰余式
 @param statement 除算および剰余以下の式
 @param identifiers 式内の識別子一覧

 @return 生成された情報へのアドレスが返される
 */
 DIVITION_INFORMATION *new_DIVITION_INFORMATION_char(AST *target_expression, int type, char *statement, ARRAY_OFFSET_LIST *identifiers){
	//statementに関するCSTL文字列を生成し、statementの内容を代入する
	CSTLString *statement_cstl = CSTLString_new();
	CSTLString_assign(statement_cstl, statement);

	//新たな除算および剰余算に関する情報を生成する
	return new_DIVITION_INFORMATION(target_expression, type, statement_cstl, identifiers);
 }

 /**
 指定された式から、div_exprおよびmod_exprを見つけ、それ以下の式を除算および剰余残に関する情報に格納する

 @param expression_ast 指定された式へのASTノードのアドレス
 @param function_information_list 関数に関する情報のリスト
 @param vtlist 変数テーブルリスト
 @param divition_information_list 除算および剰余算に関する情報を格納するためのリスト
 @param target_expression 対象の式へのASTノードのアドレス
 @param ignore_ast_list 重複防止のために使用するASTノードへのリスト

 @return なし
 */
 void getDIVITION_INFORMATION_LIST(AST *expression_ast, FUNCTION_INFORMATION_LIST *function_information_list,
		 VARIABLE_TABLE_LIST *vtlist, DIVITION_INFORMATION_LIST *divition_information_list, AST *target_expression,
		 ASTPOINTER_LIST *ignore_ast_list){
	ASTListIterator ast_i;



	//もし、除算を示すノードを見つけたら
	if(CSTLString_compare_with_char(expression_ast->name, "div_expr") == 0){
		//指定されたexpression_astがignore_ast_listに存在しないかどうかを調べ、見つからなければ追加する
		if(checkIgnoreASTList(expression_ast, ignore_ast_list) == 0){
			//式内の識別子リスト
			ARRAY_OFFSET_LIST *identifiers = ARRAY_OFFSET_LIST_new();

			//無視リスト
			ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();
			//右辺式の式を取得する
			CSTLString *statement = CSTLString_new();
			getStringFromAST(statement, ASTLIST_ITERATOR_3(expression_ast));

			//IDENTIFIERとポインタ演算式ともに探すようにする
			int switch_mode = 0;
			getArgumentOffsetInfo(ASTLIST_ITERATOR_3(expression_ast), function_information_list, vtlist, ignore_ast_list, identifiers, target_expression, &switch_mode);

			//除算および剰余算に関する情報としてリストに追加する
			DIVITION_INFORMATION_LIST_push_back_ref( divition_information_list,
				new_DIVITION_INFORMATION(target_expression, TYPE_DIV, statement, identifiers)
				);

			//無視リストを削除させる
			ASTPOINTER_LIST_clear(ignore_ast_list);
			ASTPOINTER_LIST_delete(ignore_ast_list);
		}
	}

	//もし、剰余算を示すノードを見つけたら
	else if(CSTLString_compare_with_char(expression_ast->name, "mod_expr") == 0){
		//指定されたexpression_astがignore_ast_listに存在しないかどうかを調べ、見つからなければ追加する
		if(checkIgnoreASTList(expression_ast, ignore_ast_list) == 0){
			//式内の識別子リスト
			ARRAY_OFFSET_LIST *identifiers = ARRAY_OFFSET_LIST_new();

			//無視リスト
			ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();
			//右辺式の式を取得する
			CSTLString *statement = CSTLString_new();
			getStringFromAST(statement, ASTLIST_ITERATOR_3(expression_ast));

			//IDENTIFIERとポインタ演算式ともに探すようにする
			int switch_mode = 0;
			getArgumentOffsetInfo(ASTLIST_ITERATOR_3(expression_ast), function_information_list, vtlist, ignore_ast_list, identifiers, target_expression, &switch_mode);

			//除算および剰余算に関する情報としてリストに追加する
			DIVITION_INFORMATION_LIST_push_back_ref( divition_information_list,
				new_DIVITION_INFORMATION(target_expression, TYPE_MOD, statement, identifiers)
				);

			//無視リストを削除させる
			ASTPOINTER_LIST_clear(ignore_ast_list);
			ASTPOINTER_LIST_delete(ignore_ast_list);
		}
	}

	//子ASTノードも参照する
	for(ast_i = ASTList_begin(expression_ast->children);
		ast_i != ASTList_end(expression_ast->children);
		ast_i = ASTList_next(ast_i)){
			getDIVITION_INFORMATION_LIST(ASTList_data(ast_i), function_information_list, vtlist, divition_information_list, target_expression, ignore_ast_list);
		}
 }

 /**
 除算および剰余算に関する情報のリストの内容を出力させる

 @param divition_information_list 除算および剰余算に関する情報のリスト

 @return なし
 */
 void printDIVITION_INFORMATION_LIST(DIVITION_INFORMATION_LIST *divition_information_list){
 	//除算および剰余式に関するイテレータ
	DIVITION_INFORMATION_LISTIterator di_i;

	int counter;

	for(counter = 1, di_i = DIVITION_INFORMATION_LIST_rbegin(divition_information_list);
		di_i != DIVITION_INFORMATION_LIST_rend(divition_information_list);
		counter++, di_i = DIVITION_INFORMATION_LIST_prev(di_i)){

			printf("---DIVITION_INFOMATION_%d---\n\n", counter);
			printf("TARGET_LINE = \"%d\"\n", DIVITION_INFORMATION_LIST_data(di_i)->target_expression->line);
			printf("TYPE = ");
			//除算か剰余算かによって適切なタイプを出力させる
			if(DIVITION_INFORMATION_LIST_data(di_i)->type == TYPE_DIV){
				printf("\"DIVITION\"\n");
			}else{
				printf("\"MOD\"\n");
			}
			printf("STATEMENT = \"%s\"\n\n",CSTLString_c_str(DIVITION_INFORMATION_LIST_data(di_i)->statement));
			printf("----------------------------\n\n");

		}
 }
