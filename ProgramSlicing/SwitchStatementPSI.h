/*!
  @brief ���̃t�@�C����Switch Statement Program Slicing Information�̗��ł���B
  switch������A�v���O�����X���C�V���O�Ɋւ�����𒊏o���邽�߂̖��߂��܂܂�Ă���B

  @file SwitchStatementPSI.h
  @author faithnh
 */

#ifndef SWITCHSTATEMENTPSI_H_
#define SWITCHSTATEMENTPSI_H_

#include"ProgramSlicingInformation.h"
#include"../ANSICInformation/FunctionInformation.h"
#include"../ANSICInformation/Synbol.h"

/**
switch����AST�m�[�hswitch_statement����A�֐��ɑ΂���v���O�����X���C�V���O�𒊏o���A
�v���O�����X���C�V���O���X�gexpr_slicing_list�ɒǉ�����B

@param expr_slicing_list �ǉ���̃v���O�����X���C�V���O���X�gexpr_slicing_list
@param switch_statement switch���Ɋւ���AST�m�[�h
@param parent �m�[�h��ǉ�����Ƃ��̐e�m�[�h
@param vtlist �ϐ��e�[�u�����X�g
@param function_information_list �֐��Ɋւ����񃊃X�g
@param ignore_ast_list �d���h�~�̂��߂ɖ�������m�[�h���X�g

@return �Ȃ�
 */
EXPR_SLICING *getSwicthStatementPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *switch_statement, EXPR_SLICING *parent,
		VARIABLE_TABLE_LIST *vtlist, FUNCTION_INFORMATION_LIST *function_information_list, ASTPOINTER_LIST *ignore_ast_list);

#endif /* IFSTATEMENTPSI_H_ */
