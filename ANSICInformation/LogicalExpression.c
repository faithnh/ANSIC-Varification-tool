/*
 * LogicalExpression.c
 *
 *  Created on: 2012/06/07
 *      Author: fken-2
 */

#include "LogicalExpression.h"
#include "ANSIC_CODE.h"

CSTL_LIST_IMPLEMENT(LogicalExpressionList, LogicalExpression);

LogicalExpression *LogicalExpression_new(){
	LogicalExpression *new = malloc(sizeof(LogicalExpression));
	new->expr = CSTLString_new();
	new->false = 0x0;
	new->true = 0x0;
	new->validation = CSTLString_new();
	return new;
}

int compareLogicalExpressionList(const void *a, const void *b){
	return ((LogicalExpression*)a)->idx - ((LogicalExpression*)b)->idx;
}

void generateLogicalExpressionInternal(AST *root, LogicalExpressionList *logical_expression_list, int *count,
	FUNCTION_INFORMATION_LIST *function_information_list,VARIABLE_TABLE_LIST *vtlist, ASTPOINTER_LIST *ignore_ast_list,
	int undefined_control_check,int array_unbound_check, int zero_divition_flag){
	//orの場合
	if(CSTLString_compare_with_char(root->name, "log_or_expr") == 0){
		LogicalExpressionList *first = LogicalExpressionList_new();
		LogicalExpressionList *second = LogicalExpressionList_new();
		LogicalExpressionListIterator i;
		//１つ目の式をみる
		generateLogicalExpressionInternal(ASTLIST_ITERATOR_1(root), first, count,
				function_information_list, vtlist,
				ignore_ast_list, undefined_control_check, array_unbound_check, zero_divition_flag);
		//２つ目の式をみる
		generateLogicalExpressionInternal(ASTLIST_ITERATOR_3(root), second, count,
				function_information_list, vtlist,
				ignore_ast_list, undefined_control_check, array_unbound_check, zero_divition_flag);

		//式番号の各々の否定しているところに次の番号を追加する。
		for(i = LogicalExpressionList_begin(first);
			i != LogicalExpressionList_end(first);
			i = LogicalExpressionList_next(i)){
			if( LogicalExpressionList_data(i)->false == 0x0){
				LogicalExpressionList_data(i)->false = LogicalExpressionList_front(second);
			}
		}
		LogicalExpressionList_merge(logical_expression_list, first, compareLogicalExpressionList);
		LogicalExpressionList_merge(logical_expression_list, second, compareLogicalExpressionList);

	}//andの場合
	else if(CSTLString_compare_with_char(root->name, "log_and_expr") == 0){
		LogicalExpressionList *first = LogicalExpressionList_new();
		LogicalExpressionList *second = LogicalExpressionList_new();
		LogicalExpressionListIterator i;
		//１つ目の式をみる
		generateLogicalExpressionInternal(ASTLIST_ITERATOR_1(root), first, count,
				function_information_list, vtlist,
				ignore_ast_list, undefined_control_check, array_unbound_check, zero_divition_flag);
		//２つ目の式をみる
		generateLogicalExpressionInternal(ASTLIST_ITERATOR_3(root), second, count,
				function_information_list, vtlist,
				ignore_ast_list, undefined_control_check, array_unbound_check, zero_divition_flag);

		//式番号の各々の否定しているところに次の番号を追加する。
		for(i = LogicalExpressionList_begin(first);
			i != LogicalExpressionList_end(first);
			i = LogicalExpressionList_next(i)){
			if( LogicalExpressionList_data(i)->true == 0x0){
				LogicalExpressionList_data(i)->true = LogicalExpressionList_front(second);
			}
		}
		LogicalExpressionList_merge(logical_expression_list, first, compareLogicalExpressionList);
		LogicalExpressionList_merge(logical_expression_list, second, compareLogicalExpressionList);
	}
	//式の場合
	else if(CSTLString_compare_with_char(root->name, "or_expr") == 0 ||
			CSTLString_compare_with_char(root->name, "xor_expr") == 0 ||
			CSTLString_compare_with_char(root->name, "and_expr") == 0 ||
			CSTLString_compare_with_char(root->name, "eq_expr") == 0 ||
			CSTLString_compare_with_char(root->name, "ne_expr") == 0 ||
			CSTLString_compare_with_char(root->name, "lethan_expr") == 0 ||
			CSTLString_compare_with_char(root->name, "gethan_expr") == 0 ||
			CSTLString_compare_with_char(root->name, "leeq_expr") == 0 ||
			CSTLString_compare_with_char(root->name, "geeq_expr") == 0 ||
			CSTLString_compare_with_char(root->name, "left_expr") == 0 ||
			CSTLString_compare_with_char(root->name, "right_expr") == 0 ||
			CSTLString_compare_with_char(root->name, "plus_expr") == 0 ||
			CSTLString_compare_with_char(root->name, "mul_expr") == 0 ||
			CSTLString_compare_with_char(root->name, "div_expr") == 0 ||
			CSTLString_compare_with_char(root->name, "mod_expr") == 0){
		//式データを作成し、リストに格納する
		LogicalExpression *logical_expression = LogicalExpression_new();
		ARRAY_OFFSET_LIST *a_off_list = ARRAY_OFFSET_LIST_new();
		ARRAY_OFFSET_LISTIterator *a_off_list_i;

		getStringFromAST(logical_expression->expr, root);
		//配列範囲外のチェック式の生成
		getARRAY_OFFSET_LIST(root, a_off_list, function_information_list, vtlist, ignore_ast_list, root);
		for( a_off_list_i = ARRAY_OFFSET_LIST_begin(a_off_list);
			a_off_list_i != ARRAY_OFFSET_LIST_end(a_off_list);
			a_off_list_i = ARRAY_OFFSET_LIST_next(a_off_list_i)){
			writeArrayCheck(logical_expression->validation, a_off_list_i, undefined_control_check, array_unbound_check);
		}

		if(zero_divition_flag == 1){
			DIVITION_INFORMATION_LIST *divition_information_list = DIVITION_INFORMATION_LIST_new();
			DIVITION_INFORMATION_LISTIterator di_i;
			//除算および剰余算に関する情報を格納させ、それをもとにゼロ除算の式を生成
			getDIVITION_INFORMATION_LIST(root, function_information_list, vtlist, divition_information_list, root, ignore_ast_list);
			for(di_i = DIVITION_INFORMATION_LIST_rbegin(divition_information_list);
				di_i != DIVITION_INFORMATION_LIST_rend(divition_information_list);
				di_i = DIVITION_INFORMATION_LIST_prev(di_i)){
				writeZeroCheck(logical_expression->validation, di_i);
			}
		}
		logical_expression->idx = *count;
		*count = *count + 1;
		LogicalExpressionList_push_back_ref(logical_expression_list, logical_expression);
	}
	else if(CSTLString_compare_with_char(root->name, "t_all_expression") == 0){
		if(getASTwithString(root, "log_or_expr", -1) == 0x0 &&
			getASTwithString(root, "log_and_expr", -1) == 0x0){
			//式データを作成し、リストに格納する
			LogicalExpression *logical_expression = LogicalExpression_new();
			ARRAY_OFFSET_LIST *a_off_list = ARRAY_OFFSET_LIST_new();
			ARRAY_OFFSET_LISTIterator *a_off_list_i;
			getStringFromAST(logical_expression->expr, root);

			//配列範囲外のチェック式の生成
			getARRAY_OFFSET_LIST(root, a_off_list, function_information_list, vtlist, ignore_ast_list, root);
			for( a_off_list_i = ARRAY_OFFSET_LIST_begin(a_off_list);
				a_off_list_i != ARRAY_OFFSET_LIST_end(a_off_list);
				a_off_list_i = ARRAY_OFFSET_LIST_next(a_off_list_i)){
				writeArrayCheck(logical_expression->validation, a_off_list_i, undefined_control_check, array_unbound_check);
			}
			if(zero_divition_flag == 1){
				DIVITION_INFORMATION_LIST *divition_information_list = DIVITION_INFORMATION_LIST_new();
				DIVITION_INFORMATION_LISTIterator di_i;
				//除算および剰余算に関する情報を格納させ、それをもとにゼロ除算の式を生成
				getDIVITION_INFORMATION_LIST(root, function_information_list, vtlist, divition_information_list, root, ignore_ast_list);
				for(di_i = DIVITION_INFORMATION_LIST_rbegin(divition_information_list);
					di_i != DIVITION_INFORMATION_LIST_rend(divition_information_list);
					di_i = DIVITION_INFORMATION_LIST_prev(di_i)){
					writeZeroCheck(logical_expression->validation, di_i);
				}
			}
			logical_expression->idx = *count;
			*count = *count + 1;
			LogicalExpressionList_push_back_ref(logical_expression_list, logical_expression);
		}else{
			//再帰的にアクセスする
			ASTListIterator p;
			for(p = ASTList_begin(root->children); p != ASTList_end(root->children); p = ASTList_next(p)){
				generateLogicalExpressionInternal(ASTList_data(p), logical_expression_list, count,
						function_information_list, vtlist,
						ignore_ast_list, undefined_control_check, array_unbound_check, zero_divition_flag);
			}
		}
	}
	//上記以外
	else{
		//再帰的にアクセスする
		ASTListIterator p;
		for(p = ASTList_begin(root->children); p != ASTList_end(root->children); p = ASTList_next(p)){
			generateLogicalExpressionInternal(ASTList_data(p), logical_expression_list, count,
					function_information_list, vtlist,
					ignore_ast_list, undefined_control_check, array_unbound_check, zero_divition_flag);
		}
	}
}

void generateLogicalExpression(AST *root, LogicalExpressionList *logical_expression_list,
		FUNCTION_INFORMATION_LIST *function_information_list,VARIABLE_TABLE_LIST *vtlist,ASTPOINTER_LIST *ignore_ast_list,
		int undefined_control_check,int array_unbound_check, int zero_divition_flag){
	int count = 0;
	generateLogicalExpressionInternal(root, logical_expression_list, &count, function_information_list, vtlist,
			ignore_ast_list, undefined_control_check, array_unbound_check, zero_divition_flag);
}

void LogicalExpressionList_print(LogicalExpressionList *logical_expression_list){
	LogicalExpressionListIterator i;
	for( i = LogicalExpressionList_begin(logical_expression_list);
		i != LogicalExpressionList_end(logical_expression_list);
		i = LogicalExpressionList_next(i)){
		printf("##############################################\n");
		printf("# idx = %d\n", LogicalExpressionList_data(i)->idx);
		if(LogicalExpressionList_data(i)->true != 0x0){
			printf("# true = %d\n", LogicalExpressionList_data(i)->true->idx);
		}else{
			printf("# true = NULL\n");
		}
		if(LogicalExpressionList_data(i)->false != 0x0){
			printf("# false = %d\n", LogicalExpressionList_data(i)->false->idx);
		}else{
			printf("# false = NULL\n");
		}
		printf("#expr = %s\n", CSTLString_c_str(LogicalExpressionList_data(i)->expr));
	}
	printf("##############################################\n");
}

void getStringFromLogicalInternal(CSTLString *output, LogicalExpression *logical_expression, int tab){
	CSTLString_printf(output, 1, "%s\n", CSTLString_c_str(logical_expression->validation));
	CSTLString_printf(output, 1, "if ( %s ) {\n", CSTLString_c_str(logical_expression->expr));
	if(logical_expression->true != 0x0){
		getStringFromLogicalInternal(output, logical_expression->true, tab + 1);
	}
	CSTLString_printf(output, 1, "}");
	if(logical_expression->false != 0x0){
		CSTLString_printf(output, 1, "else{\n");
		getStringFromLogicalInternal(output, logical_expression->false, tab + 1);
		CSTLString_printf(output, 1, "}\n");
	}else{
		CSTLString_printf(output, 1, "\n");
	}

}

void getStringFromLogical(CSTLString *output, LogicalExpression *logical_expression){
	getStringFromLogicalInternal(output, logical_expression, 0);
}
