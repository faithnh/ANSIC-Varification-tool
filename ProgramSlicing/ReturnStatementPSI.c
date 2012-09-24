
#include <stdio.h>
#include<stdlib.h>
#include "ReturnStatementPSI.h"

/**
return����AST�m�[�hexpression_statement����A�֐��ɑ΂���v���O�����X���C�V���O�𒊏o���A
�v���O�����X���C�V���O���X�gexpr_slicing_list�ɒǉ�����B

@param expr_slicing_list �ǉ���̃v���O�����X���C�V���O���X�gexpr_slicing_list
@param return_statement GOTO�Acontinue�Abreak���Ɋւ���AST�m�[�h
@param parent �m�[�h��ǉ�����Ƃ��̐e�m�[�h
@param vtlist �ϐ��e�[�u�����X�g
@param function_information_list �֐��Ɋւ����񃊃X�g
@param ignore_ast_list �d���h�~�̂��߂ɖ�������m�[�h���X�g

@return �Ȃ�
 */
void getReturnStatementPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *return_statement, EXPR_SLICING *parent,
		VARIABLE_TABLE_LIST *vtlist, FUNCTION_INFORMATION_LIST *function_information_list, ASTPOINTER_LIST *ignore_ast_list){

	//������Ԃ̑Ώەϐ�����шˑ��ϐ��𐶐�����
	ARRAY_OFFSET_LIST *target_variable = ARRAY_OFFSET_LIST_new();
	ARRAY_OFFSET_LIST *dependences =ARRAY_OFFSET_LIST_new();

	//������Ԃ�children1, children2�𐶐�����
	EXPR_SLICING_LIST *children1 = EXPR_SLICING_LIST_new();
	EXPR_SLICING_LIST *children2 = EXPR_SLICING_LIST_new();

	//return���������ꍇ
	if(CSTLString_compare_with_char(return_statement->name, "return_statement") == 0);
	//�l�����return���������ꍇ
	else if(CSTLString_compare_with_char(return_statement->name, "return_expr_statement") == 0){
		getASI_ARRAY_OFFSET_LIST(ASTLIST_ITERATOR_2(return_statement),target_variable, dependences, function_information_list, vtlist, ignore_ast_list, return_statement, 0);
	}else{
		fprintf(stderr,"�s���ȃm�[�h%s�������܂���",CSTLString_c_str(return_statement->name));
		exit(1);
	}

	//�v���O�����X���C�V���O���X�g�ɒǉ�����
	EXPR_SLICING_LIST_push_back_ref(expr_slicing_list, new_EXPR_SLICING(EXPR_SLICING_LIST_size(expr_slicing_list) + 1, return_statement, target_variable, dependences, children1, children2, parent));

}
