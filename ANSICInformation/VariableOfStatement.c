/*
 * VariableOfStatement.c
 *
 *  Created on: 2012/06/13
 *      Author: fken-2
 */
#include "VariableOfStatement.h"
#include "PointerArrayControl.h"
#include "xmlWriter/XmlWriter.h"
#include<stdio.h>
CSTL_LIST_IMPLEMENT(VariableOfStatementList, VariableOfStatement)

VariableOfStatementList *global;

VariableOfStatement *VariableOfStatement_new(AST *target_expression, ARRAY_OFFSET_LIST *left_variable_info,
		ARRAY_OFFSET_LIST *right_variable_info){
	VariableOfStatement *new = malloc(sizeof(VariableOfStatement));

	new->target_expression = target_expression;
	new->left_variable_info = left_variable_info;
	new->right_variable_info = right_variable_info;

	return new;
}

void initializeVariableOfStatementList(){
	global = VariableOfStatementList_new();
}

VariableOfStatementList *getVariableOfStetementList(){
	return global;
}

void addVariableOfStatementList(VariableOfStatement *self){
	VariableOfStatementList_push_back_ref(global, self);
}

void printVariableOfStatementList(){
	VariableOfStatementListIterator vos_i;
	int cnt = 1;
	for(vos_i = ValidateStatementList_begin(global);
		vos_i != VariableOfStatementList_end(global);
		vos_i = VariableOfStatementList_next(vos_i)){
		printf("====Variable of statement no.%3d====\n",cnt);
		printARRAY_OFFSET_LIST(VariableOfStatementList_data(vos_i)->left_variable_info);
		printARRAY_OFFSET_LIST(VariableOfStatementList_data(vos_i)->right_variable_info);
		printf("======================================\n");
	}
}
