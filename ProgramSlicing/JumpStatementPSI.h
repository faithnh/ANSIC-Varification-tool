/*!
  @brief ���̃t�@�C���� Jump Statement Program Slicing Information�̗��ł���B
  GOTO�Acontinue�Abreak������A�v���O�����X���C�V���O�Ɋւ�����𒊏o���邽�߂̖��߂��܂܂�Ă���B

  @file JumpStatementPSI.h
  @author faithnh
 */

#ifndef JUMPSTATEMENTPSI_H_
#define JUMPSTATEMENTPSI_H_

#include"ProgramSlicingInformation.h"
#include"../ANSICInformation/FunctionInformation.h"
#include"../ANSICInformation/Synbol.h"

/**
GOTO�Acontinue�Abreak����AST�m�[�hexpression_statement����A�֐��ɑ΂���v���O�����X���C�V���O�𒊏o���A
�v���O�����X���C�V���O���X�gexpr_slicing_list�ɒǉ�����B

@param expr_slicing_list �ǉ���̃v���O�����X���C�V���O���X�gexpr_slicing_list
@param jump_statement GOTO�Acontinue�Abreak���Ɋւ���AST�m�[�h
@param parent �m�[�h��ǉ�����Ƃ��̐e�m�[�h

@return �Ȃ�
 */
void getJumpStatementPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *jump_statement, EXPR_SLICING *parent);

#endif /* GOTOSTATEMENTPSI_H_ */
