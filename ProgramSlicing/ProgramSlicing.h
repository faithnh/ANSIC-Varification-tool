/*!
  @brief ���̃t�@�C���̓v���O�����X���C�V���O���s�����߂̖��߂��܂܂�Ă���B
  �w�肵�����ʎq������эs�������邱�ƂŁA����Ɋ�Â��ăv���O�����X���C�V���O���s���B
  @file ProgramSlicing.h
  @author faithnh
 */
#ifndef PROGRAM_SLICING_HEADDER
#define PROGRAM_SLICING_HEADDER

#include"../ANSICInformation/AST.h"
#include"../ANSICInformation/PointerArrayControl.h"
#include"../ANSICInformation/FunctionInformation.h"
#include"../ANSICInformation/Synbol.h"

#include"ProgramSlicingInformation.h"
#include<cstl/list.h>

/**
�w�肵���v���O�����`�r�s�m�[�h���玟�̂悤�ȃm�[�h���擾���A
��������X���C�V���O���s�����߂̍\���̃��X�gexpr_slicing_list�𐶐�����B
function_definition_type_a�Afunction_definition_type_b�A
expression_statement�Adeclaration_with_init�Aif_statement�Aifelse_statement�Aswitch_statement�Awhile_statement�A
dowhile_statement�Afor_statement_type_a�Afor_statement_type_b�Afor_statement_type_c�Afor_statement_type_d�A
goto_statement�Acontinue_statement�Abreak_statement�Areturn_statement�Areturn_expr_statement
goto_labeled_statement�Acase_labeled_statement�Adefault_labeled_statement

@param root �w�肵���v���O�����`�r�s�m�[�h
@param expr_slicing_list �X���C�V���O���s�����߂̍\����
@param parent �e�̃X���C�V���O�f�[�^
@param vtlist �ϐ��e�[�u�����X�g
@param function_information_list �֐��Ɋւ�����̃��X�g

@return �Ȃ�
*/
void *createStatementNodeList(AST *root, EXPR_SLICING_LIST *expr_slicing_list, EXPR_SLICING *parent,
		VARIABLE_TABLE_LIST *vtlist, FUNCTION_INFORMATION_LIST *function_information_list);

/**
�w�肵���Ώۂ̖��߂ƃO���[�o���ϐ��Ɋւ��ăf�[�^�ˑ��֌W�����邩�ǂ������ׂ�B
���݂���΁A�O���[�o���ϐ��錾�ɑ΂��āA�f�[�^�ˑ��֌W�Ƃ��Č��т���B

@param expr_slicing �w�肵���Ώۂ̖���
@param program_expr_slicing_list �v���O�����S�̂̃X���C�V���O���X�g

@return �Ȃ�
 */

void createDD_list_in_global(EXPR_SLICING *expr_slicing, EXPR_SLICING_LIST *program_expr_slicing_list);

/**
�w�肵���Ώۂ̖��߂ɑ΂��āA�f�[�^�ˑ��֌W�̖��߂�T���A���̖��߂����т���B

@param expr_slicing �w�肵���Ώۂ̖���

@return �Ȃ�
 */
void createDD_list(EXPR_SLICING *expr_slicing);
/**
�v���O�����X���C�V���O���X�g���̂��ׂĂ̖��߂ɑ΂��A�f�[�^�ˑ��֌W�̖��߂�T���A���̖��߂����т���B

@param expr_slicing_list �w�肵���Ώۂ̃v���O�����X���C�V���O���X�g
@param function_information_list �֐��Ɋւ����񃊃X�g
@param program_expr_slicing_list �v���O�����S�̂ւ̃X���C�V���O���X�g
@return �Ȃ�
 */
void createDD_listAll(EXPR_SLICING_LIST *expr_slicing_list, FUNCTION_INFORMATION_LIST *function_information_list,
		EXPR_SLICING_LIST *program_expr_slicing_list);

/**
�֐��Ăяo������A�Ăяo���Ă���֐��ւ̃f�[�^�ˑ��֌W�𐶐�����B

@param expr_slicing �֐��Ăяo�����܂܂�Ă��鏈����
@param expr_slicing_list �v���O�����S�̂̃v���O�����X���C�V���O���X�g
@param function_information_list �֐��Ɋւ����񃊃X�g

@return �Ȃ�
 */
void createDD_list_in_Function(EXPR_SLICING *expr_slicing, EXPR_SLICING_LIST *expr_slicing_list,
		FUNCTION_INFORMATION_LIST *function_information_list);

/**
�֐��ւ̃X���C�V���O���ɑ΂��āA�����������ˑ��֌W�Ƃ��ėp���Ă��閽�߂�T���A������w�肵���v���O�����X���C�V���O
�̃f�[�^�ˑ��֌W�Ƃ��Ēǉ�����B

@param expr_slicing �֐��Ăяo���̃v���O�����X���C�V���O
@param argument_name ��������
@param function_definition_expr_slicing �֐��錾�ւ̃v���O�����X���C�V���O

@return �Ȃ�
 */

void createDD_list_in_argument(EXPR_SLICING *expr_slicing, CSTLString *argument_name,
		EXPR_SLICING *function_definition_expr_slicing);

/**
�w�肵�����ʎq�̖��߂ɑ΂��ăX�^�e�B�b�N�X���C�V���O�������s���B

@param expr_slicing �w�肵�����߂ɑ΂���v���O�����X���C�V���O���

@return �Ȃ�

*/
void staticSlicing(EXPR_SLICING *expr_slicing);

/**
�w�肵�����߂ւ�AST�m�[�h�Ɋ�Â���expr_slicing_list�ɑ΂��ăX�^�e�B�b�N�X���C�V���O�������s���B

@param inst_ast �w�肵�����߂ւ�AST�m�[�h
@param expr_slicing_list �X�^�e�B�b�N�X���C�V���O�������s�����߂̍\���̃��X�g

@return �����������ǂ�����ԋp����B�@�P�F�����@�O�F���s

*/
int startStaticSlicing(AST *inst_ast, EXPR_SLICING_LIST *expr_slicing_list);

#endif
