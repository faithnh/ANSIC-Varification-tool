
#include"IfStatementPSI.h"

#include"../ANSICInformation/ANSIC_CODE.h"
#include"ExpressionStatementPSI.h"

/**
while����DoWhile����AST�m�[�hwhile_statement����A�֐��ɑ΂���v���O�����X���C�V���O�𒊏o���A
�v���O�����X���C�V���O���X�gexpr_slicing_list�ɒǉ�����B

@param expr_slicing_list �ǉ���̃v���O�����X���C�V���O���X�gexpr_slicing_list
@param while_statement if���������́Aif��else���Ɋւ���AST�m�[�h
@param parent �m�[�h��ǉ�����Ƃ��̐e�m�[�h
@param vtlist �ϐ��e�[�u�����X�g
@param function_information_list �֐��Ɋւ����񃊃X�g
@param ignore_ast_list �d���h�~�̂��߂ɖ�������m�[�h���X�g

@return �Ȃ�
 */
EXPR_SLICING *getWhileStatementPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *while_statement, EXPR_SLICING *parent,
		VARIABLE_TABLE_LIST *vtlist, FUNCTION_INFORMATION_LIST *function_information_list, ASTPOINTER_LIST *ignore_ast_list){

	EXPR_SLICING *output_children = NULL;
	//children1,children2�𗼕�����
	EXPR_SLICING_LIST *children1 = EXPR_SLICING_LIST_new();
	EXPR_SLICING_LIST *children2 = EXPR_SLICING_LIST_new();
	//�Ώۂ̕ϐ����X�g�𐶐�
	ARRAY_OFFSET_LIST *target_variable = ARRAY_OFFSET_LIST_new();

	//while�����̏���������A�ˑ��֌W�̃��X�g�����߂�(���̂Ƃ��A����p���͋֎~�ɂ���)
	ARRAY_OFFSET_LIST *dependences = ARRAY_OFFSET_LIST_new();

	//�����Awhile��������AST�m�[�h�������ꍇ
	if(CSTLString_compare_with_char(while_statement->name, "while_statement") == 0){

		getASI_ARRAY_OFFSET_LIST(ASTLIST_ITERATOR_3(while_statement),target_variable, dependences,
				function_information_list, vtlist, ignore_ast_list, while_statement, 0);

	}
	//�����Ado_while��������AST�m�[�h�������ꍇ
	else if(CSTLString_compare_with_char(while_statement->name, "dowhile_statement") == 0){
		getASI_ARRAY_OFFSET_LIST(ASTLIST_ITERATOR_5(while_statement),target_variable, dependences,
				function_information_list, vtlist, ignore_ast_list, while_statement, 0);
	}else{
		fprintf(stderr,"�s���ȃm�[�h%s�������܂���",CSTLString_c_str(while_statement->name));
		exit(1);
	}

	//�V�����X���C�V���O�Ɋւ�����𐶐�����A�X���C�V���O���X�g�ɒǉ�����
	EXPR_SLICING_LIST_push_back_ref(expr_slicing_list,
			new_EXPR_SLICING(EXPR_SLICING_LIST_size(expr_slicing_list) + 1, while_statement,
					target_variable, dependences, children1, children2, parent));

	//�ǉ������X���C�V���O�����擾����
	output_children = EXPR_SLICING_LIST_data(EXPR_SLICING_LIST_rbegin(expr_slicing_list));

	return output_children;

}