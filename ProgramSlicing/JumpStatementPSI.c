#include <stdio.h>
#include<stdlib.h>
#include "JumpStatementPSI.h"

/**
GOTO�Acontinue�Abreak����AST�m�[�hexpression_statement����A�֐��ɑ΂���v���O�����X���C�V���O�𒊏o���A
�v���O�����X���C�V���O���X�gexpr_slicing_list�ɒǉ�����B

@param expr_slicing_list �ǉ���̃v���O�����X���C�V���O���X�gexpr_slicing_list
@param jump_statement GOTO�Acontinue�Abreak���Ɋւ���AST�m�[�h
@param parent �m�[�h��ǉ�����Ƃ��̐e�m�[�h

@return �Ȃ�
 */
void getJumpStatementPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *jump_statement, EXPR_SLICING *parent){

	//GOTO�Acontinue�Abreak�����o�Ă����ꍇ
	if(CSTLString_compare_with_char(jump_statement->name, "goto_statement") == 0 ||
			CSTLString_compare_with_char(jump_statement->name, "continue_statement") == 0 ||
			CSTLString_compare_with_char(jump_statement->name, "break_statement") == 0 ){


	//������Ԃ̑Ώەϐ�����шˑ��ϐ��𐶐�����
	ARRAY_OFFSET_LIST *target_variable = ARRAY_OFFSET_LIST_new();
	ARRAY_OFFSET_LIST *dependences =ARRAY_OFFSET_LIST_new();

	//������Ԃ�children1, children2�𐶐�����
	EXPR_SLICING_LIST *children1 = EXPR_SLICING_LIST_new();
	EXPR_SLICING_LIST *children2 = EXPR_SLICING_LIST_new();

	//�v���O�����X���C�V���O���X�g�ɒǉ�����
	EXPR_SLICING_LIST_push_back_ref(expr_slicing_list, new_EXPR_SLICING(EXPR_SLICING_LIST_size(expr_slicing_list) + 1, jump_statement, target_variable, dependences, children1, children2, parent));

	}else{
		fprintf(stderr,"�s���ȃm�[�h%s�������܂���",CSTLString_c_str(jump_statement->name));
		exit(1);
	}
}
