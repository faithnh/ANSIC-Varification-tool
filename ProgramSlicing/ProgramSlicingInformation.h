/*!
  @brief ���̃t�@�C���̓v���O�����X���C�V���O�Ɋւ��������舵�����߂��܂܂�Ă���B
  @file ProgramSlicingInformation.h
  @author faithnh
 */
#ifndef PROGRAM_SLICING_INFORMATION_HEADDER
#define PROGRAM_SLICING_INFORMATION_HEADDER

#include"../ANSICInformation/AST.h"
#include"../ANSICInformation/PointerArrayControl.h"
#include<cstl/list.h>

/**
�f�[�^�ˑ��֌W�̏��
 */

struct dd_information;

CSTL_LIST_INTERFACE(DD_INFORMATION_LIST, struct dd_information)

/**
�X���C�V���O���s�����߂̊e�������Ƃ̑Ώەϐ��E�ˑ��֌W������킵���\���̂ł���B
*/
struct expr_slicing;

CSTL_LIST_INTERFACE(EXPR_SLICING_LIST, struct expr_slicing);

typedef struct expr_slicing{
	int expr_slicing_number;		///�v���O�����X���C�V���O�Ɋ��蓖�Ă���u���b�N���Ɣԍ�
	AST *expression;				///�Ώۂ̎��ւ̂`�r�s�m�[�h
	DD_INFORMATION_LIST *dd_list;		///�ˑ��֌W���X�g
	ARRAY_OFFSET_LIST *target_variable;	///�ϐ��̃I�t�Z�b�g���X�g
	ARRAY_OFFSET_LIST *dependences;		///�ˑ��֌W�̔z��I�t�Z�b�g���X�g
	EXPR_SLICING_LIST *children1;	///if��while�Afor�ɑ΂���X���C�V���O���X�g
	EXPR_SLICING_LIST *children2;	///else���ɑ΂���X���C�V���O���X�g
	struct expr_slicing *parent;			///�e�����ǂ邽�߂̃m�[�h
	int flag;						///���̏������g�p���邩�ǂ����̃t���O �P�F�g�p���� �O�F�g�p���Ȃ�

} EXPR_SLICING;

typedef struct dd_information{
	CSTLString *dd_variable_name;	//�f�[�^�ˑ��֌W�Ɋւ���ϐ���
	EXPR_SLICING *dd_target;		//�f�[�^�ˑ��֌W�̃^�[�Q�b�g�ƂȂ閽��
} DD_INFORMATION;


/**
�X���C�V���O���s�����߂̍\���̂𐶐�����B
@param expr_slicing_number �Ώۂ̎��ɑ΂���AST�ԍ�
@param expression �Ώۂ̎��ւ̂`�r�s�m�[�h
@param target_variable �ϐ��̃I�t�Z�b�g���X�g
@param dependences �ˑ��֌W�̔z��I�t�Z�b�g���X�g
@param children1 if��while�Afor�ɑ΂���X���C�V���O���X�g
@param children2 else���ɑ΂���X���C�V���O���X�g
@param parent �e�����ǂ邽�߂̃m�[�h

@return �������ꂽ�X���C�V���O���s�����߂̍\���̂ւ̃A�h���X��Ԃ��B

*/
EXPR_SLICING *new_EXPR_SLICING(int expr_slicing_number, AST *expression, ARRAY_OFFSET_LIST *target_variable,
		ARRAY_OFFSET_LIST *dependences,EXPR_SLICING_LIST *children1, EXPR_SLICING_LIST *children2,
		EXPR_SLICING *parent );

/**
�f�[�^�ˑ��֌W�Ɋւ�����𐶐�����B
@param dd_variable_name �f�[�^�ˑ��֌W�Ɋւ���ϐ���
@param *dd_target �f�[�^�ˑ��֌W�̃^�[�Q�b�g�ƂȂ閽��

@return �������ꂽ�f�[�^�ˑ��֌W�Ɋւ�����̍\���̂ւ̃A�h���X��Ԃ��B

*/
DD_INFORMATION *new_DD_INFORMATION(CSTLString *dd_variable_name, EXPR_SLICING *dd_target);
/**
�w�肵���f�[�^�ˑ��֌W�̃��X�g����A�w�肳�ꂽ�ϐ��������݂��邩���ׂ�B

@param variable_name �w�肳�ꂽ�ϐ���
@param dd_information_list �w�肵���f�[�^�ˑ��֌W�̃��X�g
@param find_dd_informaiton �������ꍇ�ɕԂ��f�[�^�ˑ��֌W�̏��
@return ���݂���ꍇ�͂P�A�����łȂ��ꍇ�͂O��Ԃ��B
 */
int searchDD(CSTLString *variable_name, DD_INFORMATION_LIST *dd_information_list, DD_INFORMATION **find_dd_informaiton);
/**
�w�肵���v���O�����X���C�V���O���̃f�[�^�ˑ��֌W����A�w�肳�ꂽ�ϐ����ł���ϐ��錾�����݂��邩���ׂ�B

@param variable_name �w�肳�ꂽ�ϐ���
@param expr_slicing �w�肵���v���O�����X���C�V���O���̃f�[�^

@return ���݂���ꍇ�͂P�A�����łȂ��ꍇ�͂O��Ԃ��B
 */
int searchDeclarationDD(CSTLString *variable_name, EXPR_SLICING *expr_slicing);

/**
�v���O�����X���C�V���O��flag������������B
@param expr_slicing_list �Ώۂ̃v���O�����X���C�V���O���̃��X�g

@return �Ȃ�
 */
void initExprSlicingListFlag(EXPR_SLICING_LIST *expr_slicing_list);
/**
�v���O�����S�̂̃v���O�����X���C�V���O���X�gexpr_slicing_list����A
�֐��Ăяo���ɑΉ�����֐���`�̃v���O�����X���C�V���O�����擾����B

@param function_name �֐���
@param expr_slicing_list �v���O�����S�̂̃v���O�����X���C�V���O���X�g

@return �擾�ɐ��������ꍇ�A�֐��Ăяo���ɑΉ�����֐���`�ւ̃v���O�����X���C�V���O����Ԃ��A���s�����ꍇ��NULL��Ԃ�
 */
EXPR_SLICING *searchFunctionPSI(CSTLString *function_name, EXPR_SLICING_LIST *expr_slicing_list);

/**
�֐����ň����O���[�o���ϐ��𒊏o���A�z��I�t�Z�b�g���X�g�Ƃ��Ē��o����B

@param output_global_variable_list ���o��̔z��I�t�Z�b�g���X�g
@param function_expr_slicing_list �֐��Ăяo���ɑ΂���v���O�����X���C�V���O���X�g
@param global_variable_list �O���[�o���ϐ��ꗗ�������z��I�t�Z�b�g���X�g

@return �Ȃ�
 */
void getFunctionGrobalVariable(ARRAY_OFFSET_LIST *output_global_variable_list, EXPR_SLICING_LIST *function_expr_slicing_list,
		ARRAY_OFFSET_LIST *global_variable_list);

/**
�Ώۂ̃v���O�����X���C�V���O���X�g����A�ϐ��錾�����𒊏o���A�z��I�t�Z�b�g���Ƃ��Ē��o����B

@param global_variable_list �O���[�o���ϐ��ꗗ�������z��I�t�Z�b�g���X�g
@param program_expr_slicing_list �v���O�����S�̂̃v���O�����X���C�V���O���X�g

@return �Ȃ�
 */
void getVariableDeclarationFromEXPR_SLICING_LIST(ARRAY_OFFSET_LIST *global_variable_list, EXPR_SLICING_LIST *program_expr_slicing_list);

/**
�֐��Ăяo������A��舵���O���[�o���ϐ��𒊏o���A�Ώۂ̕ϐ��ꗗ�ɒǉ����Ă����B
@param expr_slicing_list �ǉ��Ώۂ̃v���O�����X���C�V���O���X�g
@param program_expr_slicing_list �v���O�����S�̂̃v���O�����X���C�V���O���X�g

 */
void setGlobalVariable(EXPR_SLICING_LIST *expr_slicing_list, EXPR_SLICING_LIST *program_expr_slicing_list);

/**
�X���C�V���O�Ɋւ����񃊃X�gexpr_slicing_list���o�͂�����B

@param expr_slicing_list �X���C�V���O�Ɋւ����񃊃X�g

@return �Ȃ�
 */
void print_EXPR_SLICING_LIST(EXPR_SLICING_LIST *expr_slicing_list);

/**
�X���C�V���O�Ɋւ����񃊃X�gexpr_slicing_list���c���[�`���ŏo�͂�����B

@param expr_slicing_list �X���C�V���O�Ɋւ����񃊃X�g
@param program_slicing_mode �v���O�����X���C�V���O��̃��[�h�ɂ��邩�ǂ����̃t���O�@�P�F�L���@�O�F����
@return �Ȃ�
 */
void print_tree_EXPR_SLICING_LIST(EXPR_SLICING_LIST *expr_slicing_list, int program_slicing_mode);

/**
dependences�ŃC���N�������g��f�N�������g�̃t���O�������Ă���ϐ�����������A�����target_variable�ɓo�^����B

@param dependences �C���N�������g��f�N�������g��T���Ώۂ̈ˑ��ϐ�
@param target_variable �o�^��̒�`�Ώەϐ�

@return �Ȃ�
 */
void registerIncDecVariable(ARRAY_OFFSET_LIST *dependences, ARRAY_OFFSET_LIST *target_variable);
#endif
