/*!
  @brief ���̃t�@�C���́A���̕ϐ���C����v���O������̂ǂ̃u���b�N�ɐ錾���Ă��邩�ǂ������m�F���邽�߂̏��𐶐����邽�߂̖��߂��܂܂�Ă���B

  @file IdList.h
  @author faithnh

 */

#ifndef IDLIST_HEADDER
#define IDLIST_HEADDER

#include "Stack_int.h"
#include <cstl/list.h>

CSTL_LIST_INTERFACE(IDLIST, int)

/**
���IDLIST target1,target2���r���A���̏�Ԃł���΁A�P��Ԃ��B�����łȂ���΂O��Ԃ��B
target2�̈�ԍŏ��̃��X�g�̒l��0�ł���B
target2�̃��X�g���̒l���S�āAtarget1�̃��X�g���̒l�ƈ�v����ꍇ

@param target1 ��r�Ώۂ�IDLIST�P
@param target2 ��r�Ώۂ�IDLIST�Q

@return ��r���ď�L�����ɂȂ�ƂP��Ԃ��A�����łȂ���΁A�O��Ԃ��B
*/
int IDLIST_compare_with(IDLIST *target1, IDLIST *target2);

/**
�����X�^�b�N�̓��esource����ꂽ���Ώۂ�IDLISTdest�֓����B

@param dest �Ώۂ�IDLIST
@param source ����鐮���X�^�b�N���e
@param num �����X�^�b�N�ɓ���鐔

@return �Ȃ�
*/
void SET_STACK_INTToIDLIST(IDLIST *dest, STACK_INT *source, int num);

/**
IDLIST�̓��e���o�͂���B

@param idlist �o�͑Ώۂ�IDLIST
@param new_line_flag ���s���邩�ǂ����̃t���O�@1�F���s����@�O�F���s���Ȃ�
@return �Ȃ�
*/
void printIDLIST(IDLIST *idlist,int new_line_flag);

#endif
