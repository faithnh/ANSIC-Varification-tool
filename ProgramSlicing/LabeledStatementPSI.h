/*!
  @brief ���̃t�@�C���� Labeled Statement Program Slicing Information�̗��ł���B
  goto���x�����Acase���x�����Adefault���x��������A�v���O�����X���C�V���O�Ɋւ�����𒊏o���邽�߂̖��߂��܂܂�Ă���B

  @file LabeledStatementPSI.h
  @author faithnh
 */

#ifndef JUMPSTATEMENTPSI_H_
#define JUMPSTATEMENTPSI_H_

#include"ProgramSlicingInformation.h"
#include"../ANSICInformation/FunctionInformation.h"
#include"../ANSICInformation/Synbol.h"

/**
goto���x�����Acase���x�����Adefault���x������AST�m�[�hexpression_statement����A�֐��ɑ΂���v���O�����X���C�V���O�𒊏o���A
�v���O�����X���C�V���O���X�gexpr_slicing_list�ɒǉ�����B

@param expr_slicing_list �ǉ���̃v���O�����X���C�V���O���X�gexpr_slicing_list
@param labeled_statement   goto���x�����Acase���x�����Adefault���x�����Ɋւ���AST�m�[�h
@param parent �m�[�h��ǉ�����Ƃ��̐e�m�[�h
@param vtlist �ϐ��e�[�u�����X�g
@param function_information_list �֐��Ɋւ����񃊃X�g
@param ignore_ast_list �d���h�~�̂��߂ɖ�������m�[�h���X�g

@return �Ȃ�
 */
EXPR_SLICING *getLabeledStatementPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *labeled_statement, EXPR_SLICING *parent,
		VARIABLE_TABLE_LIST *vtlist, FUNCTION_INFORMATION_LIST *function_information_list, ASTPOINTER_LIST *ignore_ast_list);

#endif /* GOTOSTATEMENTPSI_H_ */
