/*
 * LogicalExpression.h
 *
 *  Created on: 2012/06/07
 *      Author: fken-2
 */

#ifndef LOGICALEXPRESSION_H_
#define LOGICALEXPRESSION_H_
#include<cstl/list.h>
#include "../Library/CSTLString.h"
#include "AST.h"
#include "FunctionInformation.h"
#include "Varidate_statement.h"
#include "PointerArrayControl.h"

typedef struct logical_expression{
	struct logical_expression *true;
	struct logical_expression *false;
	CSTLString *expr;
	CSTLString *validation;
	int idx;
} LogicalExpression;

CSTL_LIST_INTERFACE(LogicalExpressionList, LogicalExpression);

LogicalExpression *LogicalExpression_new();

void generateLogicalExpression(AST *root, LogicalExpressionList *logical_expression_list,
		FUNCTION_INFORMATION_LIST *function_information_list,VARIABLE_TABLE_LIST *vtlist,ASTPOINTER_LIST *ignore_ast_list,
		int undefined_control_check,int array_unbound_check, int zero_divition_flag);

void LogicalExpressionList_print(LogicalExpressionList *logical_expression_list);

void getStringFromLogical(CSTLString *output, LogicalExpression *logical_expression);
#endif /* LOGICALEXPRESSION_H_ */
