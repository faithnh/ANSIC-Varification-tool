/*!
  @brief ���̃t�@�C���͊֐��Ɋւ�������擾���邽�߂̖��߂��܂܂�Ă���B
  @file FunctionInformation.h
  @author faithnh

 */

#ifndef FUNCTION_INFORMATION_HEADDER
#define FUNCTION_INFORMATION_HEADDER

#include<cstl/list.h>
#include"../Library/CSTLString.h"
#include"AST.h"

//�p�����[�^�����o�̓^�C�v�����̓^�C�v���o�̓^�C�v��������
#define PARAM_INOUT_TYPE 2
#define PARAM_IN_TYPE 1
#define PARAM_OUT_TYPE 0

/**
�����Ɋւ�����
 */
typedef struct param_information{
	CSTLString *param_type; ///�p�����[�^�̌^
	CSTLString *param_name; ///�p�����[�^�̖��O
	int array_level;		///�z��̃��x��
	int pointer_level;		///�|�C���^�̃��x��
	int in_out_flag; 		///���͌^���o�͌^���̔���@�P�F���́@�O�F�o�́@�Q�F���o��
} PARAM_INFORMATION;

CSTL_LIST_INTERFACE(PARAM_INFORMATION_LIST, PARAM_INFORMATION)

/**
�֐��Ɋւ�����B�֐�����̌��؎��̐����Ȃǂɗp����B
 */
typedef struct function_information{
	AST *function_node;								///�֐���`��AST�m�[�h�ւ̃A�h���X
	CSTLString *return_type;						///�ԋp�l�̌^�iconst int�Ȃǂƕ\�L�����)
	CSTLString *function_name;						///�֐���(*func�Ȃǂƕ\�L�����j
	PARAM_INFORMATION_LIST *param_information_list;	///���̊֐��̈������X�g
} FUNCTION_INFORMATION;



CSTL_LIST_INTERFACE(FUNCTION_INFORMATION_LIST, FUNCTION_INFORMATION)

/**
�֐��Ɋւ�����𐶐�����B

@param function_node �Ώۂ̊֐��ւ̃m�[�h
@param return_type �ԋp�l�̃^�C�v
@param function_name �֐���
@param param_information_list �p�����[�^�Ɋւ�����

@return �������ꂽ�֐��Ɋւ�����ւ̃A�h���X��Ԃ��B
 */
FUNCTION_INFORMATION *new_FUNCTION_INFORMATION(AST *function_node, CSTLString *return_type, CSTLString *function_name, PARAM_INFORMATION_LIST *param_information_list);


/**
�p�����[�^�Ɋւ�����𐶐�����B

@param param_type �p�����[�^�̌^
@param param_name �p�����[�^�̖��O
@param array_level �z��̃��x��
@param pointer_level �|�C���^�̃��x��
@param in_out_flag ���͌^���o�͌^���̔���@�P�F���́@�O�F�o�́@�Q�F���o��

@return �������ꂽ�p�����[�^�Ɋւ�����ւ̃A�h���X��Ԃ��B
 */

PARAM_INFORMATION *new_PARAM_INFORMATION(CSTLString *param_type, CSTLString *param_name,
			int array_level, int pointer_level, int in_out_flag);

/**
�w�肵���v���O������AST�m�[�h����֐���`��T���A����Ɋ�Â��Ċ֐��Ɋւ�����𐶐����A�����̃��X�gfunction_information_list
�ɓo�^����B

@param function_information_list �o�^��̊֐��Ɋւ�����̃��X�g
@param root �w�肵���v���O������AST�m�[�h

@return �Ȃ�
 */
void getFunctionInformation(FUNCTION_INFORMATION_LIST *function_information_list, AST *root);

/**
�w�肵���t�@�C����file_name�Œ�`���ꂽ�֐��Ɋւ�������֐��Ɋւ�����̃��X�gfunction_information_list�ɐݒ肷��B
@param function_information_list �o�^��̊֐��Ɋւ�����̃��X�g
@param file_name �w�肵���t�@�C����

@return �Ȃ�
 */
void getFunctionInformationFromFile(FUNCTION_INFORMATION_LIST *function_information_list, char* file_name);

/**
�w�肵���֐��̒�`���̂���A�p�����[�^��`�Ȃǂ��폜����B

@param target_string �Ώۂ̊֐��̒�`���̂̕�����

@return �Ȃ�
 */
void deleteParameterDefine(CSTLString *target_string);


/**
�֐��Ɋւ����񃊃X�g�̓��e���o�͂�����B
@param function_information_list �o�͑Ώۂ̊֐��Ɋւ����񃊃X�g

@return �Ȃ�
*/

void printFUNCTION_INFORMATION_LIST(FUNCTION_INFORMATION_LIST *function_information_list);

/**
�֐��Ɋւ����񃊃X�g����A�w�肵���֐�����T���A����Ɋւ���\���̂ւ̃A�h���X��Ԃ��B

@param target_function_name �w�肵���֐���
@param function_information_list �����Ώۂ̊֐��Ɋւ����񃊃X�g

@return ���������ꍇ�͂��̊֐��Ɋւ���\���̂ւ̃A�h���X��Ԃ��B�݂���Ȃ���΁ANULL��Ԃ��B
 */

FUNCTION_INFORMATION *searchFUNCTION_INFORMATION(CSTLString *target_function_name, FUNCTION_INFORMATION_LIST *function_information_list);

/**
�w�肵���֐������֐��Ɋւ����񃊃X�g����T���A�|�C���^���x����Ԃ��B
@param target_function_name �w�肵���֐���
@param function_information_list �����Ώۂ̊֐��Ɋւ����񃊃X�g

@return ���������ꍇ�͂��̊֐��̃|�C���^���x����Ԃ��A�����łȂ��ꍇ��-1��Ԃ��B
 */

int getPointerLevelFromFUNCTION_INFORMATION_LIST(CSTLString *target_function_name, FUNCTION_INFORMATION_LIST *function_information_list);

/**
�p�����[�^���X�g�������m�[�hparam_info_node����A�p�����[�^�̏����擾���Aparam_information_list�ɓo�^����B

@param param_info_node �p�����[�^���X�g�������m�[�h
@param param_information_list �o�^��̃p�����[�^��񃊃X�g

@return �Ȃ�
 */
void getParamInformationFromFunctionDifinition(AST *param_info_node, PARAM_INFORMATION_LIST *param_information_list);

/**
�p�����[�^�̃|�C���^���x���E�z�񃌃x������ь^������A���̃p�����[�^�͓��͌^���o�͌^�����肷��B

@param param_type �p�����[�^�̌^��
@param pointer_level �|�C���^�̃��x��
@param array_level �z��̃��x��

@return ���͌^�Ȃ�΂P�A�o�͌^�Ȃ�΂O��Ԃ��B
 */
int getIN_OUT_FLAG(CSTLString *param_type, int pointer_level, int array_level);
#endif
