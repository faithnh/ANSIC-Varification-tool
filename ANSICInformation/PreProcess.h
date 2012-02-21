/*!
  @brief ���̃t�@�C���͍\����͂�ʂ���悤�ɁAGcc��C����Ƀv���v���Z�X�i�O�����j�������邽�߂̖��߂��܂܂�Ă���B
  ���̃t�@�C���łł��邱�ƂƂ��ẮA#include���R�����g�A�E�g���邱�ƂŏȂ��āA�v���v���Z�X���|���邱�Ƃ��ł���B
  @file PreProcess.h
  @author faithnh
 */

#ifndef PRE_PROCESS_HEADDER
#define PRE_PROCESS_HEADDER

#include<cstl/list.h>
#include"../Library/CSTLString.h"
/**
�C���N���[�h�t�@�C���Ɋւ����񂪊i�[�����B����́A���؎��t�����ɃC���N���[�h�t�@�C����t������̂Ɏg�p����B
*/
typedef struct include_data{
	CSTLString *include_data;	///include�t�@�C���̖��O
	int line;					///���̍s��
} INCLUDE_DATA;

CSTL_LIST_INTERFACE(INCLUDE_LIST, INCLUDE_DATA)


/**
�V�����C���N���[�h�t�@�C���𐶐�����B
@param include_data include�t�@�C���̖��O
@param line ���̍s��
*/
INCLUDE_DATA *new_INCLUDE_DATA(CSTLString *include_data, int line);

/**
���s���������\�[�X�Ƀv���v���Z�b�T��������B�v���v���Z�b�T�̂������t�@�C���̓t�@�C����_out_pre.c�Ƃ��ďo�͂����B
@param source_file_name ���s���������\�[�X�t�@�C����

@return �����������ǂ����������@���������ꍇ�͂P���������A�����łȂ��ꍇ�͂O��Ԃ��B
*/
int preProcesser(char *source_file_name);

/**
"#include"�ɃR�����g�������Ă����B�R�����g�A�E�g�����������ʂ̓t�@�C����_out.c�Ƃ��ďo�͂����B
@param source_file_name �Ώۂ̃\�[�X�t�@�C����

@return �����������ǂ����������@���������ꍇ�͂P���������A�����łȂ��ꍇ�͂O��Ԃ��B
*/
int includeComment(char *source_file_name);

/**
�v���O�����̎n�܂�������ʒu�܂ł��ׂč폜����B
@param source_file_name �Ώۂ̃\�[�X�t�@�C����

@return �����������ǂ����������@���������ꍇ�͂P���������A�����łȂ��ꍇ�͂O��Ԃ��B
*/
int adjustProgramStart(char *source_file_name);

/**
"#include"�ɃR�����g�����������݂̂̂����o���A��肾�������̂��C���N���[�h�t�@�C���̃��X�ginclude_list�ɂ����B
@param file_name �J���t�@�C����
@param include_list �C���N���[�h���X�g

@return �Ȃ�
*/
void readIncludeDataFromFile(char *file_name, INCLUDE_LIST *include_list);

/**
�C���N���[�h���X�g����ɁA�Ώۂ̃t�@�C���ɃC���N���[�h��ǉ�����B
@param file_name �J���t�@�C����
@param include_list �C���N���[�h���X�g

@return �Ȃ�
*/
void addIncludeDataFromFile(char *file_name, INCLUDE_LIST *include_list);

#endif
