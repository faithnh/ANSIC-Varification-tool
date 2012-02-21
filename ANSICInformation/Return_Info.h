/*!
  @brief ����̓��^�[�����߂Ɋւ�������擾���邽�߂̖��߂��܂܂�Ă���B

  @file Return_Info.h
  @author faithnh
 */
#ifndef RETURN_INFO_HEADDER
#define RETURN_INFO_HEADDER

#include"PointerArrayControl.h"

/**
���^�[�����߂Ɋւ����񂪊܂܂�Ă���B
*/
typedef struct return_info{
	AST *target_expression; ///���^�[�����ߎ��̂ւ̃m�[�h�ւ̃A�h���X
	ARRAY_OFFSET_LIST *return_array_offset_list; ///���^�[�����߂ŕ\�L���ꂽ���̔z��I�t�Z�b�g���X�g
} RETURN_INFO;

/**
���^�[�����߂Ɋւ�����𐶐�������B
@param target_expression ���^�[�����ߎ��̂ւ̃m�[�h�ւ̃A�h���X
@param return_array_offset_list ���^�[�����߂ŕ\�L���ꂽ���̔z��I�t�Z�b�g���X�g

@return �������ꂽ���^�[�����߂Ɋւ�����ւ̃A�h���X��Ԃ��B
*/
RETURN_INFO *new_RETURN_INFO(AST *target_expression, ARRAY_OFFSET_LIST *return_array_offset_list);

#endif
