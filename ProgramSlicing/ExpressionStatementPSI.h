/*!
  @brief ���̃t�@�C����Expression Statement Program Slicing Information�̗��ł���B
  ���S�ʂ���A�v���O�����X���C�V���O�Ɋւ�����𒊏o���邽�߂̖��߂��܂܂�Ă���B

  @file ExpressionStatementPSI.h
  @author faithnh
 */

#ifndef EXPRESSIONSTATEMENTPSI_H_
#define EXPRESSIONSTATEMENTPSI_H_

#include"ProgramSlicingInformation.h"
#include"../ANSICInformation/FunctionInformation.h"
#include"../ANSICInformation/Synbol.h"


/**
���S�ʂ�AST�m�[�hexpression_statement����A�֐��ɑ΂���v���O�����X���C�V���O�𒊏o���A
�v���O�����X���C�V���O���X�gexpr_slicing_list�ɒǉ�����B

@param expr_slicing_list �ǉ���̃v���O�����X���C�V���O���X�gexpr_slicing_list
@param expression_statement ���S�ʂɊւ���AST�m�[�h
@param parent �m�[�h��ǉ�����Ƃ��̐e�m�[�h
@param vtlist �ϐ��e�[�u�����X�g
@param function_information_list �֐��Ɋւ����񃊃X�g
@param ignore_ast_list �d���h�~�̂��߂ɖ�������m�[�h���X�g
@param target_statement expression_statement���w�������m�[�h

@return �Ȃ�
 */
void getExpressionStatementPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *expression_statement, EXPR_SLICING *parent,
		VARIABLE_TABLE_LIST *vtlist, FUNCTION_INFORMATION_LIST *function_information_list, ASTPOINTER_LIST *ignore_ast_list,
		AST *target_statement);

/**
call_function��AST�m�[�h������͊֌W�̊֐���T���o���A�����̈����̕ϐ������ׂāA�Ώەϐ��Ƃ��ēo�^����B
@param root �Ώۂ�AST�m�[�h
@param target_variable �Ώۂ̕ϐ��̔z��I�t�Z�b�g��񃊃X�g
@param dependences �ˑ��֌W�̔z��I�t�Z�b�g��񃊃X�g
@param function_information_list �֐��Ɋւ����񃊃X�g
@param vtlist ���؎��̎����}�[�N���邽�߂̕ϐ����X�g
@param ignore_ast_list �z��I�t�Z�b�g���X�g�̏d���o�^��h�~���邽�߂́AIDENTIFIER�𖳎����邽�߂�AST�̃A�h���X���X�g
@param target_statement ���؎��̑ΏۂƂȂ�X�e�[�g�����g

@return �Ȃ�
 */
void getInputFunctionPSI(AST *root, ARRAY_OFFSET_LIST *target_variable, ARRAY_OFFSET_LIST *dependences, FUNCTION_INFORMATION_LIST *function_information_list,
		VARIABLE_TABLE_LIST *vtlist, ASTPOINTER_LIST *ignore_ast_list, AST *target_statement);

/**
expression_statement����сAexpression�ɑ�������m�[�h����A�Ώۂ̕ϐ�����шˑ��֌W�̔z��I�t�Z�b�g���X�g���擾����B

@param root �I�t�Z�b�g���X�g�ɊY������AST�m�[�h
@param target_variable ���ӎ��̃|�C���^����єz��̃I�t�Z�b�g���̃��X�g
@param dependences �E�ӎ��̃|�C���^����єz��̃I�t�Z�b�g���̃��X�g
@param function_information_list �֐��Ɋւ����񃊃X�g
@param vtlist ���ؑΏۂ̎����}�[�N���邽�߂̕ϐ����X�g
@param ignore_ast_list �|�C���^�ł̈ʒu�����؍ς݂ł���AIDENTIFIER�𖳎����邽�߂�AST�̃A�h���X���X�g
@param target_statement ���؎��̑ΏۂƂȂ�X�e�[�g�����g
@param allow_side_effect ����p�����������ǂ����̃t���O�@�P�F���� �O�F�����Ȃ�
@return �Ȃ�
*/
void getASI_ARRAY_OFFSET_LIST(AST *root, ARRAY_OFFSET_LIST *left_array_offset_list, ARRAY_OFFSET_LIST *right_array_offset_list, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
						  ASTPOINTER_LIST *ignore_ast_list, AST *target_statement, int allow_side_effect);

/**
�Q�Ɛ��AST�m�[�h���w�肵���֐��Ăяo��call_function�ł���z��I�t�Z�b�g���X�gargument_list�ɑ΂��āA
�w�肵�������̔ԍ�argument_number���ȉ��̌`�ŕt������B

���O�@���@���O#�����ԍ�

@param argument_list �t���Ώۂ̔z��I�t�Z�b�g���X�g
@param arg_num ����
@param call_function �֐��Ăяo���ɑ΂���AST�m�[�h

@return �Ȃ�
 */
void setARGUMENT_NUMBER( ARRAY_OFFSET_LIST *argument_list, int arg_num, AST *call_function);
#endif /* EXPRESSIONSTATEMENTPSI_H_ */
