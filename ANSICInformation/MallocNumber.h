/*!
  @brief ����͂ǂ�malloc�p���ʔԍ���t������֐��𐶐����邽�߂̖��߂��܂܂�Ă���B

  @file MallocNumber.h
  @author faithnh
 */
#ifndef MALLOC_NUMBER_HEADDER
#define MALLOC_NUMBER_HEADDER

#include"../Library/CSTLString.h"
#include"PreProcess.h"
/**
malloc�p���ʔԍ��t���֐����J�����g�f�B���N�g����ɐ���������B
@param target_directory �쐬����f�B���N�g����

@return �Ȃ�
*/
void generateMallocNumber(CSTLString *target_directory);

/**
�C���N���[�h����malloc�p���ʔԍ��t���֐����܂܂�Ă���w�b�_�[�t�@�C����ǉ�������B�B
@param include_list �C���N���[�h���ւ̃��X�g

@return �Ȃ�
*/
void insertMallocNumberHeadder(INCLUDE_LIST *include_list);
#endif
