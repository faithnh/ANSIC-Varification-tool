#include "Stack_int.h"

CSTL_VECTOR_IMPLEMENT(STACK_INT, int)

/**
�Ώۂ̐����X�^�b�Nstack_int����A�w�肵���C���f�b�N�X�̓��e���o�͂���B�C���f�b�N�X���͈͊O�ł���ꍇ�́A���̃T�C�Y���܂Ŋm�ۂ��A0��Ԃ��B

@param stack_int �Ώۂ̐����X�^�b�N
@param index �Ώۂ̍��W

@return �w�肵���C���f�b�N�X�ł̐����X�^�b�N�̒l���o�͂���B�C���f�b�N�X���͈͊O�ł���ꍇ��0��Ԃ��B
*/
int STACK_INT_at_and_alloc(STACK_INT *stack_int, int index){
	int ret_val;
	//�����A�w�肵���C���f�b�N�X�͐����X�^�b�N�͈͓̔��ł���ꍇ
	if(STACK_INT_size(stack_int) > index){
		ret_val = *STACK_INT_at(stack_int, index);
	}
	//�͈͊O�ł���ꍇ�́A���̃T�C�Y���܂Ŋm�ۂ��A0��Ԃ�
	else{
		while(STACK_INT_size(stack_int) <= index){
			STACK_INT_push_back(stack_int, 0);
		}
		ret_val = 0;
	}

	return ret_val;
}

/**
�Ώۂ̐����X�^�b�Nstack_int����A�w�肵���C���f�b�N�X�̓��e���C���N�������g����B
@param stack_int �Ώۂ̐����X�^�b�N
@param index �w�肵���C���f�b�N�X
@return �C���N�������g�ɐ����������ǂ����������B���������ꍇ�͂P�A�����łȂ��ꍇ�͂O��Ԃ��B
*/
int STACK_INT_inclement_at(STACK_INT *stack_int, int index){
		int ret_val;
	//�����A�w�肵���C���f�b�N�X�͐����X�^�b�N�͈͓̔��ł���ꍇ
	if(STACK_INT_size(stack_int) > index){
		//�w�肵���C���f�b�N�X�̓��e���C���N�������g����
		*STACK_INT_at(stack_int, index) = *STACK_INT_at(stack_int, index) + 1;
		ret_val = 1;
	}
	//�͈͊O�ł���ꍇ�́A0��Ԃ��B
	else{

		ret_val = 0;
	}

	return ret_val;
}
