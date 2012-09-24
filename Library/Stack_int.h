/*!
  @brief ���̃t�@�C���͐����X�^�b�N�Ɋւ��鑀������邽�߂̖��߂��܂܂�Ă���B
  ���̃t�@�C���Ŏg�p������ȗp�r�Ƃ��āAC����\�[�X�t�@�C���ɂ�����u���b�N���x����ݒ肷��̂Ɏg�p�����B
  @file Stack_int.h
  @author faithnh
 */


#ifndef STACK_INT_HEADDER
#define STACK_INT_HEADDER

#include <cstl/vector.h>

CSTL_VECTOR_INTERFACE(STACK_INT, int)

/**
�Ώۂ̐����X�^�b�Nstack_int����A�w�肵���C���f�b�N�X�̓��e���o�͂���B�C���f�b�N�X���͈͊O�ł���ꍇ�́A���̃T�C�Y���܂Ŋm�ۂ��A0��Ԃ��B

@param stack_int �Ώۂ̐����X�^�b�N
@param index �Ώۂ̍��W

@return �w�肵���C���f�b�N�X�ł̐����X�^�b�N�̒l���o�͂���B�C���f�b�N�X���͈͊O�ł���ꍇ��0��Ԃ��B
*/
int STACK_INT_at_and_alloc(STACK_INT *stack_int, int index);

/**
�Ώۂ̐����X�^�b�Nstack_int����A�w�肵���C���f�b�N�X�̓��e���C���N�������g����B
@param stack_int �Ώۂ̐����X�^�b�N
@param index �w�肵���C���f�b�N�X
@return �C���N�������g�ɐ����������ǂ����������B���������ꍇ�͂P�A�����łȂ��ꍇ�͂O��Ԃ��B
*/
int STACK_INT_inclement_at(STACK_INT *stack_int, int index);

#endif
