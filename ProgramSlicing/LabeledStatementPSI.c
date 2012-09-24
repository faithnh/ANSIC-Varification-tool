#include <stdio.h>
#include<stdlib.h>
#include "LabeledStatementPSI.h"

/**
goto���x�����Acase���x�����Adefault���x������AST�m�[�hexpression_statement����A�֐��ɑ΂���v���O�����X���C�V���O�𒊏o���A
�v���O�����X���C�V���O���X�gexpr_slicing_list�ɒǉ�����B

@param expr_slicing_list �ǉ���̃v���O�����X���C�V���O���X�gexpr_slicing_list
@param labeled_statement   goto���x�����Acase���x�����Adefault���x�����Ɋւ���AST�m�[�h
@param parent �m�[�h��ǉ�����Ƃ��̐e�m�[�h
@param vtlist �ϐ��e�[�u�����X�g
@param function_information_list �֐��Ɋւ����񃊃X�g
@param ignore_ast_list �d���h�~�̂��߂ɖ�������m�[�h���X�g

@return �Ȃ�
 */
EXPR_SLICING *getLabeledStatementPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *labeled_statement, EXPR_SLICING *parent,
		VARIABLE_TABLE_LIST *vtlist, FUNCTION_INFORMATION_LIST *function_information_list, ASTPOINTER_LIST *ignore_ast_list){

	//�V�����v���O�����X���C�V���O���
	EXPR_SLICING *new_expr_slicing = NULL;

	//������Ԃ̑Ώەϐ�����шˑ��ϐ��𐶐�����
	ARRAY_OFFSET_LIST *target_variable = ARRAY_OFFSET_LIST_new();
	ARRAY_OFFSET_LIST *dependences =ARRAY_OFFSET_LIST_new();

	//������Ԃ�children1, children2�𐶐�����
	EXPR_SLICING_LIST *children1 = EXPR_SLICING_LIST_new();
	EXPR_SLICING_LIST *children2 = EXPR_SLICING_LIST_new();

	//goto���x�����Adefault���x�������o�Ă����ꍇ
	if(CSTLString_compare_with_char(labeled_statement->name, "goto_labeled_statement") == 0 ||
			CSTLString_compare_with_char(labeled_statement->name, "default_labeled_statement") == 0){

		//�V�����X���C�V���O�Ɋւ�����𐶐�����A�X���C�V���O���X�g�ɒǉ�����
		EXPR_SLICING_LIST_push_back_ref(expr_slicing_list,
				new_EXPR_SLICING(EXPR_SLICING_LIST_size(expr_slicing_list) + 1,
						labeled_statement, target_variable, dependences, children1, children2, parent));

		//�ǉ������X���C�V���O�����擾����
		new_expr_slicing = EXPR_SLICING_LIST_data(EXPR_SLICING_LIST_rbegin(expr_slicing_list));

	}
	//case���x�������o�Ă����ꍇ
	else if(CSTLString_compare_with_char(labeled_statement->name, "case_labeled_statement") == 0){

		//�V�����X���C�V���O�Ɋւ�����𐶐�����
		getASI_ARRAY_OFFSET_LIST(ASTLIST_ITERATOR_2(labeled_statement),target_variable, dependences, function_information_list, vtlist, ignore_ast_list, labeled_statement, 0);

		//�V�����X���C�V���O�Ɋւ�����𐶐�����A�X���C�V���O���X�g�ɒǉ�����
		EXPR_SLICING_LIST_push_back_ref(expr_slicing_list,
				new_EXPR_SLICING(EXPR_SLICING_LIST_size(expr_slicing_list) + 1,
						labeled_statement, target_variable, dependences, children1, children2, parent));

		//�ǉ������X���C�V���O�����擾����
		new_expr_slicing = EXPR_SLICING_LIST_data(EXPR_SLICING_LIST_rbegin(expr_slicing_list));
	}
	else{
		fprintf(stderr,"�s���ȃm�[�h%s�������܂���",CSTLString_c_str(labeled_statement->name));
		exit(1);
	}

	return new_expr_slicing;
}
