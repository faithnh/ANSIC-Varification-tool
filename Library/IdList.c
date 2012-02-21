#include "IdList.h"
#include<stdio.h>

CSTL_LIST_IMPLEMENT(IDLIST, int)


/**
���IDLIST target1,target2���r���A���̏�Ԃł���΁A�P��Ԃ��B�����łȂ���΂O��Ԃ��B
target2�̈�ԍŏ��̃��X�g�̒l��0�ł���B
target2�̃��X�g���̒l���S�āAtarget1�̃��X�g���̒l�ƈ�v����ꍇ

@param target1 ��r�Ώۂ�IDLIST�P
@param target2 ��r�Ώۂ�IDLIST�Q

@return ��r���ď�L�����ɂȂ�ƂP��Ԃ��A�����łȂ���΁A�O��Ԃ��B
*/
int IDLIST_compare_with(IDLIST *target1, IDLIST *target2){
	int success_flag = 1;

	IDLISTIterator ti1,ti2;

	if(*IDLIST_data(IDLIST_begin(target2)) != 0){
		for(ti1 = IDLIST_begin(target1), ti2 = IDLIST_begin(target2);
			ti1 != IDLIST_end(target1) && ti2 != IDLIST_end(target2);
			ti1 = IDLIST_next(ti1), ti2 = IDLIST_next(ti2)){
			//�r���ň�v���Ȃ��ꍇ�́A�O�ɂ��A�I������B
			if(*IDLIST_data(ti1) != *IDLIST_data(ti2)){
				success_flag = 0;
				break;
			}
		}

		if(ti1 == IDLIST_end(target1) && ti2 != IDLIST_end(target2)){
			success_flag = 0;
		}
	}

	return success_flag;

}

/**
�����X�^�b�N�̓��esource����ꂽ���Ώۂ�IDLISTdest�֓����B

@param dest �Ώۂ�IDLIST
@param source ����鐮���X�^�b�N���e
@param num �����X�^�b�N�ɓ���鐔

@return �Ȃ�
*/
void SET_STACK_INTToIDLIST(IDLIST *dest, STACK_INT *source, int num){
	//IDLIST�̓��e��������
	IDLIST_clear(dest);

	//�����X�^�b�N�̓��e���Ȃ���΁A0�݂̂�IDLIST�֓����B
	if(num == 0){
		IDLIST_push_back(dest, 0);
	}else{
		int si_loc;
		for(si_loc = 0; si_loc < num; si_loc++){
			//1���x���ڂł���ꍇ�́A�����X�^�b�N�̓����Ă���f�[�^�{1��IDLIST�֓����B
			if(si_loc == 0){
				IDLIST_push_back(dest, *STACK_INT_at(source, si_loc) + 1);
			}
			//�����łȂ��ꍇ�́A�����X�^�b�N�̓����Ă���f�[�^��IDLIST�֓����
			else{
				IDLIST_push_back(dest, *STACK_INT_at(source, si_loc));
			}
		}
	}
}


/**
IDLIST�̓��e���o�͂���B

@param idlist �o�͑Ώۂ�IDLIST
@param new_line_flag ���s���邩�ǂ����̃t���O�@1�F���s����@�O�F���s���Ȃ�
@return �Ȃ�
*/
void printIDLIST(IDLIST *idlist,int new_line_flag){
	IDLISTIterator idlist_i;

	for(idlist_i = IDLIST_begin(idlist);
		idlist_i != IDLIST_end(idlist);
		idlist_i = IDLIST_next(idlist_i)){
			//�u�l1-�l2-...-�ln�v�̌`�ŏo�͂���
			printf("%d",*IDLIST_data(idlist_i));
			if(IDLIST_next(idlist_i) != IDLIST_end(idlist)){
				printf("-");
			}
		}

	//���s�t���O�������Ă�������s����
	if(new_line_flag == 1){
		printf("\n");
	}
}
