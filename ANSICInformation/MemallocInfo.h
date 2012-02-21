/*!
  @brief ���̃t�@�C���̓������m�ۊ֌W�̊֐�����A�������m�ۊ֌W�Ɋւ�������i�[���邽�߂̖��߂��܂܂�Ă���B
  ��̓I�ɂ́AC����v���O������ɂ���Amalloc�Ecalloc�Erealloc�ȂǂƂ������֐�����A�m�ۂ��Ă���sizeof�̌^�Erealloc�g�p���őΏۂƂ��Ă���ϐ��E�m�ۂ��Ă���T�C�Y���擾����B

  @file MemallocInfo.h
  @author faithnh

 */
#ifndef MEMALLOC_INFO_HEADDER
#define MEMALLOC_INFO_HEADDER

#include"PointerArrayControl.h"
#include"AST.h"
#include"Synbol.h"

/**
���������蓖�ĂɊւ�������i�[���邽�߂̍\���́B
*/
typedef struct memory_allocation_info{
	CSTLString *sizeof_type;	///sizeof�̌^��
	ARRAY_OFFSET_LIST *realloc_target;	///realloc���̃^�[�Q�b�g�ϐ��̔z��I�t�Z�b�g���X�g
	CSTLString *size;			///malloc���̃T�C�Y
} MEMALLOC_INFO;

/**
���������蓖�ĂɊւ�������i�[���邽�߂̍\���̂̃f�[�^�𐶐�������B
@param sizeof_type		sizeof�̌^��
@param realloc_target	realloc���̃^�[�Q�b�g�^�C�v
@param size				malloc���̃T�C�Y

@return ���������蓖�ĂɊւ�������i�[���邽�߂̍\���̂ւ̃A�h���X��Ԃ��B
*/
MEMALLOC_INFO *new_MEMALLOC_INFO_char(char *sizeof_type, ARRAY_OFFSET_LIST *realloc_target, char *size);

/**
���������蓖�ĂɊւ�������i�[���邽�߂̍\���̂̃f�[�^�𐶐�������B
@param sizeof_type		sizeof�̌^��
@param realloc_target	realloc���̃^�[�Q�b�g�^�C�v
@param size				malloc���̃T�C�Y

@return ���������蓖�ĂɊւ�������i�[���邽�߂̍\���̂ւ̃A�h���X��Ԃ��B
*/
MEMALLOC_INFO *new_MEMALLOC_INFO(CSTLString *sizeof_type, ARRAY_OFFSET_LIST *realloc_target, CSTLString *size);

/**
�w�肳�ꂽAST�m�[�h���烁�����m�ۊ֌W�̊֐��Ɋւ�������擾����B
@param root �w�肳�ꂽAST�m�[�h
@param vtlist realloc��realloc�̃^�[�Q�b�g���̃I�t�Z�b�g�����擾����̂ɕK�v�ȃv���O�����̕ϐ����X�g
@return �������m�ۊ֌W�̍\���̂ւ̃A�h���X��Ԃ��B
*/
MEMALLOC_INFO *memoryAllocationAnarysis(AST *root, VARIABLE_TABLE_LIST *vtlist);

/**
malloc�֐��Ɋւ�������擾����
@param root
@param sizeof_type sizeof�ł̌^
@param constant sizeof�ȊO�ł̎��i���Ȃ킿�m�ۂ��Ă���^�ɑ΂���T�C�Y�ɑ�������j

@return �Ȃ�
*/
void getMallocInformation(AST *root, CSTLString *sizeof_type, CSTLString *constant);

/**
calloc�֐��Ɋւ�������擾����B
@param root
@param sizeof_type sizeof�ł̌^
@param constant sizeof�ȊO�ł̎��i���Ȃ킿�m�ۂ��Ă���^�ɑ΂���T�C�Y�ɑ�������j

@return �Ȃ�
*/
void getCallocInformation(AST *root, CSTLString *sizeof_type, CSTLString *constant);

/**
realloc�֐��Ɋւ�������擾����B
@param root �Ώۂ�AST�m�[�h
@param vtlist �Ώۂ̃v���O�����̕ϐ����X�g
@param sizeof_type sizeof�ł̌^
@param constant sizeof�ȊO�ł̎��i���Ȃ킿�m�ۂ��Ă���^�ɑ΂���T�C�Y�ɑ�������j
@param realloc_target realloc���ΏۂƂ���I�t�Z�b�g���

@return �Ȃ�
*/
void getReallocInformation(AST *root,VARIABLE_TABLE_LIST *vtlist, CSTLString *sizeof_type, CSTLString *constant, ARRAY_OFFSET_LIST *realloc_target);

/**
�w�肵������AST�ɑ΂��āAsizeof��T�����A���̌^����sizeof_type�Ŏ擾����B�����A���ɈقȂ�Q��ނ�sizeof��`������΁A�T���t���O�͎��s����B
�܂��A������Ȃ���΁Asizeof_type�͉����w�肵�Ă��Ȃ��܂܂̏�Ԃł���B
@param sizeof_type �o�͂���sizeof�̌^��
@param root �T���Ώۂ̎��ւ�AST�m�[�h
@return �Ȃ�
*/
int searchSizeof(CSTLString *sizeof_type, AST *root);

/**
malloc�Ȃǂ̊֐����̎�����A�m�ۂ����T�C�Y�����������擾����B����́Asizeof(�^)���P�ɏ��������Ȃ���A�����o�͂����邱�Ƃōs���Ă���B

@param constant �擾����sizeof�ȊO�ł̎��i���Ȃ킿�m�ۂ��Ă���^�ɑ΂���T�C�Y�ɑ�������j
@param root malloc�Ȃǂ̊֐����̎��ւ�AST�m�[�h
@return �Ȃ�
*/
void getMallocMaxsize(CSTLString *constant,AST *root);


/*
�w�肵���������m�ۏ��memalloc_info�̓��e���o�͂���B

@param memalloc_info �o�͑Ώۂ̃������m�ۏ��

@return �Ȃ�
*/
void printMEMALLOC_INFO(MEMALLOC_INFO *memalloc_info);


#endif
