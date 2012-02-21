/*!
  @brief ���̃t�@�C���́Afor���[�v�Ɋւ�������W�߂邽�߂̖��߂��܂܂�Ă���

  @file ForInformation.h
  @author faithnh
 */
#ifndef FORINFORMATION_HEADDER_FILE
#define FORINFORMATION_HEADDER_FILE

#include "AST.h"
#include <cstl/list.h>
/**
for���̏������E�p�����E�����������for�����S�̂̎��ւ̃m�[�h���i�[�����B
����́A���؎��t���c�[����for����while���Ɏg�p�����B
*/
typedef struct for_information{
	AST *target_expression; ///����for�����̂ւ�AST�m�[�h
	AST *init_expression; ///�������ւ�AST�m�[�h
	AST *continue_condition; ///�p�����ւ�AST�m�[�h
	AST *inc_dec_expression; ///�������ւ�AST�m�[�h
	AST *statement; ///for�����S�̂̎��ւ�AST�m�[�h
} ForInformation;

/**
����́AFOR_INFORMATION�̎������m���߂�
*/
CSTL_LIST_INTERFACE(ForInformationList, ForInformation)

/**
for���Ɋւ�����FOR_INFORMATION�𐶐�����B
@param target_expression ����for�����̂̏��
@param init_expression ������
@param continue_condition �p����
@param inc_dec_expression ������
AST *statement for�����̑S�̂̎����w��
@return �������ꂽFOR_INFORMATION�ւ̃A�h���X��Ԃ��B

*/
ForInformation *new_FOR_INFORMATION(AST *target_expression, AST *init_expression, AST *continue_condition, AST *inc_dec_expression, AST *statement);

/**
for���Ɋւ�����̃��X�gfor_information_list���o�͂���B
@param for_information_list for���Ɋւ�����̃��X�g

@return �Ȃ�
*/
void print_FOR_INFORMATION_LIST(ForInformationList *for_information_list);

/**
for���Ɋւ�����̃��X�gfor_information_list����A�w�肵��AST�m�[�h�ɑΉ��������̂��o�͂�����B
@param for_information_list �����Ώۂ�for���Ɋւ�����̃��X�g
@param target_ast ��������AST

@return �}�b�`�������̂�������΁A����ɑΉ��������̂ւ̃A�h���X���o�͂�����B������Ȃ��ꍇ��NULL��Ԃ��B
*/
ForInformation *searchFOR_INFORMATION_FromAST(ForInformationList *for_information_list, AST *target_ast);

/**
for_iteration��AST�m�[�h����Afor���Ɋւ�����̃��X�g���擾����B

@param for_information_list for���Ɋւ�����̃��X�g
@param for_iteration_ast for���Ɋւ�����̃��X�g

@return �Ȃ�
*/
void getFOR_INFORMATION_LIST(ForInformationList *for_information_list, AST *for_iteration_ast);

#endif
