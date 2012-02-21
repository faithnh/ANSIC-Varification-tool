#include"ForStatementPSI.h"

#include"../ANSICInformation/ANSIC_CODE.h"
#include"ExpressionStatementPSI.h"

/**
for����AST�m�[�hfor_statement����A�֐��ɑ΂���v���O�����X���C�V���O�𒊏o���A
�v���O�����X���C�V���O���X�gexpr_slicing_list�ɒǉ�����B

@param expr_slicing_list �ǉ���̃v���O�����X���C�V���O���X�gexpr_slicing_list
@param for_statement for���Ɋւ���AST�m�[�h
@param parent �m�[�h��ǉ�����Ƃ��̐e�m�[�h
@param vtlist �ϐ��e�[�u�����X�g
@param function_information_list �֐��Ɋւ����񃊃X�g
@param ignore_ast_list �d���h�~�̂��߂ɖ�������m�[�h���X�g

@return �Ȃ�
 */

EXPR_SLICING *getForStatementPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *for_statement, EXPR_SLICING *parent,
		VARIABLE_TABLE_LIST *vtlist, FUNCTION_INFORMATION_LIST *function_information_list, ASTPOINTER_LIST *ignore_ast_list){
	EXPR_SLICING *output_children = NULL;
		//children1,children2�𗼕�����
		EXPR_SLICING_LIST *children1 = EXPR_SLICING_LIST_new();
		EXPR_SLICING_LIST *children2 = EXPR_SLICING_LIST_new();
		//�Ώۂ̕ϐ����X�g�𐶐�
		ARRAY_OFFSET_LIST *target_variable = ARRAY_OFFSET_LIST_new();

		//for���̎�����A�ˑ��֌W�̃��X�g�����߂�
		ARRAY_OFFSET_LIST *dependences = ARRAY_OFFSET_LIST_new();
		//�����Afor_statement_type_a�������ꍇ
		if(CSTLString_compare_with_char(for_statement->name, "for_statement_type_a") == 0){
			getASI_ARRAY_OFFSET_LIST(ASTLIST_ITERATOR_3(for_statement) ,target_variable, dependences, function_information_list, vtlist, ignore_ast_list, for_statement, 1);
			getASI_ARRAY_OFFSET_LIST(ASTLIST_ITERATOR_4(for_statement) ,target_variable, dependences, function_information_list, vtlist, ignore_ast_list, for_statement, 0);
		}

		//�����Afor_statement_type_b�������ꍇ
		else if(CSTLString_compare_with_char(for_statement->name, "for_statement_type_b") == 0){
			getASI_ARRAY_OFFSET_LIST(ASTLIST_ITERATOR_3(for_statement) ,target_variable, dependences, function_information_list, vtlist, ignore_ast_list, for_statement, 1);
			getASI_ARRAY_OFFSET_LIST(ASTLIST_ITERATOR_4(for_statement) ,target_variable, dependences, function_information_list, vtlist, ignore_ast_list, for_statement, 0);
			getASI_ARRAY_OFFSET_LIST(ASTLIST_ITERATOR_5(for_statement) ,target_variable, dependences, function_information_list, vtlist, ignore_ast_list, for_statement, 1);			//�V�����X���C�V���O�Ɋւ�����𐶐�����

		}
		//��L�O�̏ꍇ�́A�s���ȃm�[�h�Ƃ��ăG���[���o�͂�����
		else{
			fprintf(stderr,"�s���ȃm�[�h%s�������܂���",CSTLString_c_str(for_statement->name));
			exit(1);
		}

		//�ˑ��֌W�̕ϐ��ɑ΂��āA�Ώۂ̕ϐ��ɓ��Ă͂܂�ϐ������ׂč폜����
		minusArrayOffsetList(dependences, target_variable);

		//�V�����X���C�V���O�Ɋւ�����𐶐�����
		output_children = new_EXPR_SLICING(EXPR_SLICING_LIST_size(expr_slicing_list) + 1, for_statement, target_variable, dependences, children1, children2, parent);

		//�V�����������ꂽ�X���C�V���O�Ɋւ�������X���C�V���O���X�g�ɒǉ�����
		EXPR_SLICING_LIST_push_back_ref(expr_slicing_list, output_children);

	return output_children;


}
