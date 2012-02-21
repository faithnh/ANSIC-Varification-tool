/*!
  @brief ���̃t�@�C����Function Program Slicing Information�̗��ł���B
  �֐���`����A�v���O�����X���C�V���O�Ɋւ�����𒊏o���邽�߂̖��߂��܂܂�Ă���B

  @file FunctionPSI.h
  @author faithnh
 */
#ifndef FUNCTION_PS_INFORMATION_HEADDER
#define FUNCTION_PS_INFORMATION_HEADDER

#include"ProgramSlicingInformation.h"

/**
�֐���`��AST�m�[�hfunction_definition����A�֐��ɑ΂���v���O�����X���C�V���O�𒊏o���A
�v���O�����X���C�V���O���X�gexpr_slicing_list�ɒǉ�����B

@param expr_slicing_list �ǉ���̃v���O�����X���C�V���O���X�gexpr_slicing_list
@param function_definition �֐���`�Ɋւ���AST�m�[�h
@param parent �m�[�h��ǉ�����Ƃ��̐e�m�[�h

@return �ǉ������֐��̃X���C�V���O�ւ̃A�h���X��Ԃ�
 */
EXPR_SLICING *getFunctionPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *function_definition, EXPR_SLICING *parent);

/**
�p�����[�^���X�g�Ɋւ���AST�m�[�hparameter_node����֐���`�̃v���O�����X���C�V���O���X�gexpr_slicing_list�Ɋi�[���Ă���

@param expr_slicing �֐���`�̃v���O�����X���C�V���O
@param parameter_node �e�p�����[�^�̒�`���X�g
@param basis_parameter_node �p�����[�^���w��AST�m�[�h

@return �Ȃ�
 */
void getParameterPSI(EXPR_SLICING *expr_slicing, AST *parameter_node, AST *basis_parameter_node);
#endif
