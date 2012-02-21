#include"Return_Info.h"

#include<stdio.h>
#include<stdlib.h>

/**
���^�[�����߂Ɋւ�����𐶐�������B
@param target_expression ���^�[�����ߎ��̂ւ̃m�[�h�ւ̃A�h���X
@param return_array_offset_list ���^�[�����߂ŕ\�L���ꂽ���̔z��I�t�Z�b�g���X�g

@return �������ꂽ���^�[�����߂Ɋւ�����ւ̃A�h���X��Ԃ��B
*/
RETURN_INFO *new_RETURN_INFO(AST *target_expression, ARRAY_OFFSET_LIST *return_array_offset_list){
	RETURN_INFO *new_return_info = (RETURN_INFO*)malloc(sizeof(RETURN_INFO));

	if(new_return_info == NULL){
		fprintf(stderr, "�������s��\n");
		exit(1);
	}else{
		new_return_info->target_expression = target_expression;
		new_return_info->return_array_offset_list = return_array_offset_list;
	}

	return new_return_info;

}
