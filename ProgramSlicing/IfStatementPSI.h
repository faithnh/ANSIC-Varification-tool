/*!
  @brief ���̃t�@�C����If Statement Program Slicing Information�̗��ł���B
  if���������́Aif��else������A�v���O�����X���C�V���O�Ɋւ�����𒊏o���邽�߂̖��߂��܂܂�Ă���B

  @file IfStatementPSI.h
  @author faithnh
 */

#ifndef IFSTATEMENTPSI_H_
#define IFSTATEMENTPSI_H_

#include"ProgramSlicingInformation.h"
#include"../ANSICInformation/FunctionInformation.h"
#include"../ANSICInformation/Synbol.h"

/**
if���������́Aif��else����AST�m�[�hif_statement����A�֐��ɑ΂���v���O�����X���C�V���O�𒊏o���A
�v���O�����X���C�V���O���X�gexpr_slicing_list�ɒǉ�����B

@param expr_slicing_list �ǉ���̃v���O�����X���C�V���O���X�gexpr_slicing_list
@param if_statement if���������́Aif��else���Ɋւ���AST�m�[�h
@param parent �m�[�h��ǉ�����Ƃ��̐e�m�[�h
@param vtlist �ϐ��e�[�u�����X�g
@param function_information_list �֐��Ɋւ����񃊃X�g
@param ignore_ast_list �d���h�~�̂��߂ɖ�������m�[�h���X�g

@return �Ȃ�
 */
EXPR_SLICING *getIfStatementPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *if_statement, EXPR_SLICING *parent,
		VARIABLE_TABLE_LIST *vtlist, FUNCTION_INFORMATION_LIST *function_information_list, ASTPOINTER_LIST *ignore_ast_list);

#endif /* IFSTATEMENTPSI_H_ */
