/*
 * VariableOfStatement.h
 *
 *  Created on: 2012/06/13
 *      Author: fken-2
 */

#ifndef VARIABLEOFSTATEMENT_H_
#define VARIABLEOFSTATEMENT_H_
#include<cstl/list.h>
#include"PointerArrayControl.h"
#include"AST.h"

typedef struct variable_of_statement{
	AST *target_expression;
	ARRAY_OFFSET_LIST *left_variable_info;
	ARRAY_OFFSET_LIST *right_variable_info;
} VariableOfStatement;

CSTL_LIST_INTERFACE(VariableOfStatementList, VariableOfStatement)

VariableOfStatement *VariableOfStatement_new(AST *target_expression, ARRAY_OFFSET_LIST *left_variable_info,
				ARRAY_OFFSET_LIST *right_variable_info);

void initializeVariableOfStatementList();

VariableOfStatementList *getVariableOfStetementList();

void addVariableOfStatementList(VariableOfStatement *self);

#endif /* VARIABLEOFSTATEMENT_H_ */
