
#include"DivitionDeclarator.h"
#include"../Library/CSTLString.h"

#include<stdio.h>
#include<stdlib.h>
/**
OutputSourceAfterDivitionDeclaratorの内部処理である
@param output 出力先のファイル構造体
@param programAST プログラムに対するAST
@param variable_table_list 変数テーブル
@param line 処理中の行数

@return なし
 */
void OutputSourceAfterDivitionDeclarator_Internal(FILE *output, AST *programAST, VARIABLE_TABLE_LIST *variable_table_list, int *line){

	ASTListIterator p;

	VARIABLE_TABLE_LISTIterator vi_list_i;

	//変数テーブルにある定義式を見つけたかどうかのフラグ
	int find_flag;

	//decralation_with_initを見つけた場合
	if(CSTLString_compare_with_char(programAST->name, "declaration_with_init") == 0){
		//変数テーブルにある定義式を見つけていない状態にしておく
		find_flag = 0;

		for(vi_list_i = VARIABLE_TABLE_LIST_begin(variable_table_list);
			vi_list_i != VARIABLE_TABLE_LIST_end(variable_table_list);
			vi_list_i = VARIABLE_TABLE_LIST_next(vi_list_i)){

				//もし、変数テーブルリストにある初期定義式と一致した場合
				if(VARIABLE_TABLE_LIST_data(vi_list_i)->declaration_location_address == programAST){

					//変数テーブルにある定義式を見つけた状態にしておく
					find_flag = 1;

					//ASTノードの行数と引数の行数がかみ合わないとき、改行を出力させ、出力する行数を調整する
					while(*line < programAST->line){
						fprintf(output, "\n");
						*line = *line + 1;
					}

					//初期定義式が存在する場合
					if(VARIABLE_TABLE_LIST_data(vi_list_i)->initiarizer != NULL){
						//初期定義式を取得する
						CSTLString *init_expr = CSTLString_new();
						getStringFromAST(init_expr, VARIABLE_TABLE_LIST_data(vi_list_i)->initiarizer);

						//「型名 変数名 = 初期定義式;」という形で出力する
						fprintf(output, "%s %s = %s ; ",CSTLString_c_str(VARIABLE_TABLE_LIST_data(vi_list_i)->type),
								CSTLString_c_str(VARIABLE_TABLE_LIST_data(vi_list_i)->variable_name),
								CSTLString_c_str(init_expr));
						CSTLString_delete(init_expr);
					}else{
						//「型名 変数名;」という形で出力する
						fprintf(output, "%s %s ; ",CSTLString_c_str(VARIABLE_TABLE_LIST_data(vi_list_i)->type),
								CSTLString_c_str(VARIABLE_TABLE_LIST_data(vi_list_i)->variable_name));
					}

				}
		}

		//変数テーブルにある定義式を見つけていない状態である場合は、子ノードを探索しておく
		if(find_flag == 0){
			for(p = ASTList_begin(programAST->children); p != ASTList_end(programAST->children); p = ASTList_next(p)){
				OutputSourceAfterDivitionDeclarator_Internal(output, ASTList_data(p), variable_table_list, line);
			}
		}
	}
	//リーフノード（子ASTノードの数が0のASTノード）の場合
	else if(ASTList_size(programAST->children) == 0){
		//ASTノードの行数と引数の行数がかみ合わないとき、改行を出力させ、出力する行数を調整する
		while(*line < programAST->line){
			fprintf(output, "\n");
			*line = *line + 1;
		}
		//ASTノードの内容を出力させる
		fprintf(output, "%s ",CSTLString_c_str(programAST->content));
	}
	else{
		//ASTノードが子ASTノードの情報を持っていたら、子ASTノードについて再帰的に参照させる
		for(p = ASTList_begin(programAST->children); p != ASTList_end(programAST->children); p = ASTList_next(p)){
			OutputSourceAfterDivitionDeclarator_Internal(output, ASTList_data(p), variable_table_list, line);
		}
	}
}

/**
変数定義を分割させた状態で出力させる。
　例：int a,b = 1; → int a; int b = 1;
@param output 出力先のファイル構造体
@param programAST プログラムに対するAST
@param variable_table_list 変数テーブル

@return なし
 */
void OutputSourceAfterDivitionDeclarator(FILE *output, AST *programAST, VARIABLE_TABLE_LIST *variable_table_list){

	int line = 1;

	OutputSourceAfterDivitionDeclarator_Internal(output,programAST,variable_table_list,&line);
}
