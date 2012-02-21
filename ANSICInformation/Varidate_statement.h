/*!
  @brief �����C����v���O�����ォ��A�s������؂��邽�߂̌��؎��⌟�ؗp�Ɏg�p����ϐ��Ȃǂ�ǉ����邽�߂̖��߂��܂܂�Ă���B

  @file Varidate_statement.h
  @author faithnh
 */
#ifndef VARIDATE_STATEMENT_HEADDER
#define VARIDATE_STATEMENT_HEADDER

#include <cstl/list.h>

#include"Synbol.h"

#include"PointerArrayControl.h"
#include"MemallocInfo.h"
#include"FreeMemInfo.h"
#include "ForInformation.h"
#include "DivitionInformation.h"
#include "PreProcess.h"

#include"../ProgramSlicing/ProgramSlicingInformation.h"
/**
�|�C���^��z��ϐ��ɑ΂��錟�ؗp�̕ϐ����X�g���쐬���邽�߂̍\���̂ł���B
*/
typedef struct validate_variable {
	int used;					///���̌��ؗp�̕ϐ����g�p���Ă��邩�ǂ����̃t���O 1:�g�p 0:���g�p
	int enable_start;			///���̕ϐ��̗L���͈́i�u���b�N�ł́j�̊J�n�s��������
	int enable_end;				///���̕ϐ��̗L���͈́i�u���b�N�ł́j�̏I���s��������
	int declaration_location;	///���̕ϐ���錾����s��������
	int block_level;			///���̕ϐ���錾����u���b�N���x���������i�O�Ȃ�O���[�o���ϐ��E�P�Ȃ�֐����Ǝ����j
	int block_id;				///���̕ϐ���錾����u���b�NID�������i���u���b�N���x���ŕʂ̃u���b�N�����ʂ��邽�߂̔ԍ��j
	CSTLString *type;			///���̕ϐ��̌^
	CSTLString *variable_name;	///���̕ϐ���
	CSTLString *target_variable_name; ///���̕ϐ��̌��ؑΏۂƂȂ�ϐ���
	int offset_level;			///���̕ϐ��̔z���|�C���^�̎������x��
} ValidateVariable;

CSTL_LIST_INTERFACE(ValidateVariableList, ValidateVariable);

/**
���ۂɌ��؎��Ƃ��đ}�����邽�߂̏��ł���B
*/
typedef struct validate_statement {
	int target_id;			///���̌��؎��̎���ID(�ǂ̏����ł��̌��؎������Ă��������m�F���邽�߂�ID)
	int check_or_modify;	///���؎����`�F�b�N����^�C�v���A�v���O���������ɕҏW����^�C�v���𔻒f����t���O�B�O�F�`�F�b�N����^�C�v�A�P�F�ҏW����^�C�v
	int used;				///���̌��؎��͎g�p���Ă��邩�ǂ����̃t���O 1:�g�p 0:���g�p
	CSTLString *statement;	///���̌��؎��̓��e
	AST *target_statement;	///���̌��؎��̃^�[�Q�b�g�ƂȂ�AST�m�[�h�ւ̃A�h���X
} ValidateStatement;

CSTL_LIST_INTERFACE(ValidateStatementList, ValidateStatement);


/**
���ۂɌ��؎��Ƃ��đ}�����邽�߂̏��𐶐�����B
@param target_id ���̌��؎��̎���ID(�ǂ̏����ł��̌��؎������Ă��������m�F���邽�߂�ID)
@param check_or_modify ���؎����`�F�b�N����^�C�v���A�v���O���������ɕҏW����^�C�v���𔻒f����t���O�B�O�F�`�F�b�N����^�C�v�A�P�F�ҏW����^�C�v
@param used ���̌��؎��͎g�p���Ă��邩�ǂ����̃t���O 1:�g�p 0:���g�p
@param statement ���̌��؎��̓��e
@param target_statement ���̌��؎��̃^�[�Q�b�g�ƂȂ�AST�m�[�h�ւ̃A�h���X

@return ���ۂɌ��؎��Ƃ��đ}�����邽�߂̏��ւ̃A�h���X��Ԃ��B
*/
ValidateStatement *new_VALIDATE_STATEMENT_char(int target_id, int check_or_modify, int used, char *statement, AST *target_statement);

/**
���ۂɌ��؎��Ƃ��đ}�����邽�߂̏��𐶐�����B
@param target_id ���̌��؎��̎���ID(�ǂ̏����ł��̌��؎������Ă��������m�F���邽�߂�ID)
@param check_or_modify ���؎����`�F�b�N����^�C�v���A�v���O���������ɕҏW����^�C�v���𔻒f����t���O�B�O�F�`�F�b�N����^�C�v�A�P�F�ҏW����^�C�v
@param used ���̌��؎��͎g�p���Ă��邩�ǂ����̃t���O 1:�g�p 0:���g�p
@param statement ���̌��؎��̓��e
@param target_statement ���̌��؎��̃^�[�Q�b�g�ƂȂ�AST�m�[�h�ւ̃A�h���X

@return ���ۂɌ��؎��Ƃ��đ}�����邽�߂̏��ւ̃A�h���X��Ԃ��B
*/
ValidateStatement *new_VALIDATE_STATEMENT(int target_id, int check_or_modify, int used, CSTLString *statement, AST *target_statement);

/**
�V�������ؗp�ϐ��e�[�u���̃f�[�^�𐶐�������B
@param used ���̌��ؗp�ϐ��e�[�u�����g�p�������ǂ���
@param enable_start ���̕ϐ��̗L���͈͂̎n�܂�̍s��
@param enable_end ���̕ϐ��̗L���͈͂̏I���̍s��
@param declaration_location ���̕ϐ���錾�����ꏊ�̍s��
@param block_level ���̕ϐ��̃u���b�N���x���i�O���[�o���ϐ��Ȃ�O�Ƃ��A�֐��̒��ł̒�`�Ȃ�P�A���̊֐�����for���Ȃǂ̃u���b�N���Ȃ��ł̐錾�Ȃ�Q�Ƃ���j
@param block_id �u���b�N���Ƃ�ID�i��{�I�ɂ�0����n��A�u���b�N���x���Q���Q��ڂɂ���ƁA�P�ƂȂ�j
@param type �^��
@param variable_name �ϐ���
@param target_variable_name ���ؑΏۂ̕ϐ���
@param offset_level ���̕ϐ��̔z���|�C���^�̎������x��

@return �V�����������ꂽ���ؗp�ϐ��̃f�[�^�ւ̃A�h���X���Ԃ����B
*/
ValidateVariable *new_VALIDATE_VARIABLE(int used, int enable_start, int enable_end, int declaration_location,
								   int block_level ,int block_id, CSTLString *type, CSTLString *variable_name, CSTLString *target_variable_name, int offset_level);

/**
�V�������ؗp�ϐ��e�[�u���̃f�[�^�𐶐�������(char�Ή���)�B
@param used ���̌��ؗp�ϐ��e�[�u�����g�p�������ǂ���
@param enable_start ���̕ϐ��̗L���͈͂̎n�܂�̍s��
@param enable_end ���̕ϐ��̗L���͈͂̏I���̍s��
@param declaration_location ���̕ϐ���錾�����ꏊ�̍s��
@param block_level ���̕ϐ��̃u���b�N���x���i�O���[�o���ϐ��Ȃ�O�Ƃ��A�֐��̒��ł̒�`�Ȃ�P�A���̊֐�����for���Ȃǂ̃u���b�N���Ȃ��ł̐錾�Ȃ�Q�Ƃ���j
@param block_id �u���b�N���Ƃ�ID�i��{�I�ɂ�0����n��A�u���b�N���x���Q���Q��ڂɂ���ƁA�P�ƂȂ�j
@param type �^��
@param variable_name �ϐ���
@param target_variable_name ���ؑΏۂ̕ϐ���
@param offset_level ���̕ϐ��̔z���|�C���^�̎������x��

@return �V�����������ꂽ���ؗp�ϐ��̃f�[�^�ւ̃A�h���X���Ԃ����B
*/
ValidateVariable *new_VALIDATE_VARIABLE_with_char(int used, int enable_start, int enable_end, int declaration_location,
								   int block_level ,int block_id, char *type, char *variable_name, char *target_variable_name, int offset_level);

/**
���؎����X�g�̎g�p�t���O�𖢎g�p��Ԃɏ���������B
@param validate_statement_list *�������Ώۂ̌��؎����X�g

@return �Ȃ�
 */
void initVaridateStatement_flag(ValidateStatementList *validate_statement_list);

/**
�v���O�����̕ϐ����X�g�����ƂɃv���O�����̌��ؗp�̕ϐ���ݒ肷��B
@param variable_table_list �v���O�����̕ϐ����X�g
@param validate_variable ���ؗp�̕ϐ����X�g
@return �Ȃ�
*/
void getValidate_Variable(VARIABLE_TABLE_LIST *variable_table_list, ValidateVariableList *validate_variable);

/**
���ؗp�ϐ��e�[�u���̃��X�g�̓��e���o�͂�����B
@param validate_variable_list �o�͑Ώۂ̌��ؗp�ϐ��e�[�u���̃��X�g
@return �Ȃ�

*/
void printValidateVariableList(ValidateVariableList *validate_variable_list);

/**
��{�I�Ȍ��؎��̐������s���B
@param root ���؎������Ώۂ�AST�m�[�h
@param function_informaiton_list �֐��Ɋւ�����̃��X�g
@param vtlist ���ؑΏۂ̎����}�[�N���邽�߂̕ϐ����X�g
@param validate_variable_list ���ؗp�ϐ����X�g
@param validate_statement_list �擾�������؎����i�[����Ƃ���
@param for_information_list for���Ɋւ�����
@param undefined_control_check ����`�ȏ����i����`�|�C���^�̎Q�ƂȂǁj���s���Ă��Ȃ����ǂ��������؂��邽�߂̎��𐶐����邩�ǂ��� �P�F�������� �O�F�������Ȃ�
@param zero_divition_check 0�Ŋ����Ă��Ȃ����ǂ��������؂��邽�߂̎��𐶐����邩�ǂ����@�P�F��������@�O�F�������Ȃ�
@param array_unbound_check �z�񂪔͈͊O���Q�Ƃ��Ă��Ȃ����ǂ��������؂��邽�߂̎��𐶐����邩�ǂ����@�P�F��������@�O�F�������Ȃ�
@param free_violation_check ����������֌W�ŕs���ȏ������s���Ă��Ȃ����ǂ��������؂��邽�߂̎��𐶐����邩�ǂ����@�P�F��������@�O�F�������Ȃ�

@return �Ȃ�
*/
void createValidateStatement(AST * root, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist, ValidateVariableList *validate_variable_list,
											ValidateStatementList *validate_statement_list, ForInformationList *for_information_list, int undefined_control_check,
											int zero_divition_check, int array_unbound_check, int free_violation_check);

/**
�w�肵��AST�m�[�hroot����Ainit_declarator��T�������A��������VARIDATE_STATEMENT�Ɋւ�������擾����B
@param root �w�肵���m�[�h
@param function_information_list �֐��Ɋւ�����̃��X�g
@param vtlist �Ώۂ̕ϐ����X�g
@param validate_variable_list ���ؗp�ϐ����X�g
@param validate_statement_list �擾�������؎����i�[����Ƃ���
@param ignore_ast_list �|�C���^�ł̈ʒu�����؍ς݂ł���AIDENTIFIER�𖳎����邽�߂�AST�̃A�h���X���X�g
@param target_expression assign_expression�������Ă���expression_statement
@param undefined_control_check ����`�ȏ������s���Ă��Ȃ����ǂ��������؂��邽�߂̎��𐶐����邩�ǂ��� �P�F�������� �O�F�������Ȃ�
@param zero_divition_check 0�Ŋ����Ă��Ȃ����ǂ��������؂��邽�߂̎��𐶐����邩�ǂ����@�P�F��������@�O�F�������Ȃ�
@param array_unbound_check �z�񂪔͈͊O���Q�Ƃ��Ă��Ȃ����ǂ��������؂��邽�߂̎��𐶐����邩�ǂ����@�P�F��������@�O�F�������Ȃ�

@return �Ȃ�
*/
void getValidateStatementFromInitializer(AST *root, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
											ValidateVariableList *validate_variable_list,ValidateStatementList *validate_statement_list, ASTPOINTER_LIST *ignore_ast_list,
											AST *target_expression, int undefined_control_check, int zero_divition_check, int array_unbound_check);

/**
malloc�p���ʔԍ���t�����邽�߂̊֐��ɕϊ����邽�߂̌��؎���ǉ�������B
@param validate_statement_list �ǉ���̌��؎����X�g
@param call_function �֐��Ăяo���ɑ΂���m�[�h
@param right_array_offset_list ���Ӓl�Ɋւ���z��I�t�Z�b�g���X�g
@param memalloc_info �������m�ۏ��

@return �Ȃ�
*/
void getValidateStatementFromMallocNumber(ValidateStatementList *validate_statement_list, AST *call_function, ARRAY_OFFSET_LIST* right_array_offset_list, MEMALLOC_INFO *memalloc_info);

/**
for���̖����̏�񂩂�A���؎����擾���A���؎����X�g�ɓ����B
@param validate_statement_list �擾�������؎����i�[����Ƃ���
@param for_information_list for���Ɋւ�����̃��X�g
@param function_information_list �֐��Ɋւ�����̃��X�g
@param vtlist �Ώۂ̕ϐ����X�g
@param validate_variable_list ���ؗp�ϐ����X�g
@param ignore_ast_list �|�C���^�ł̈ʒu�����؍ς݂ł���AIDENTIFIER�𖳎����邽�߂�AST�̃A�h���X���X�g
@param undefined_control_check ����`�ȏ������s���Ă��Ȃ����ǂ��������؂��邽�߂̎��𐶐����邩�ǂ��� �P�F�������� �O�F�������Ȃ�
@param zero_divition_check 0�Ŋ����Ă��Ȃ����ǂ��������؂��邽�߂̎��𐶐����邩�ǂ����@�P�F��������@�O�F�������Ȃ�
@param array_unbound_check �z�񂪔͈͊O���Q�Ƃ��Ă��Ȃ����ǂ��������؂��邽�߂̎��𐶐����邩�ǂ����@�P�F��������@�O�F�������Ȃ�
@param free_violation_check ����������֌W�ŕs���ȏ������s���Ă��Ȃ����ǂ��������؂��邽�߂̎��𐶐����邩�ǂ����@�P�F��������@�O�F�������Ȃ�

@return �Ȃ�
*/
void getValidateStatementFromForIteration(ValidateStatementList *validate_statement_list, ForInformationList *for_information_list,
										FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,ValidateVariableList *validate_variable_list,
										ASTPOINTER_LIST *ignore_ast_list, int undefined_control_check,int zero_divition_check,int array_unbound_check,
										int free_violation_check);


/**
�w�肵��AST�m�[�hroot����Aassign_expression��T�������A��������VARIDATE_STATEMENT�Ɋւ�������擾����B
@param root �w�肵���m�[�h
@param function_information_list �֐��Ɋւ�����̃��X�g
@param vtlist �Ώۂ̕ϐ����X�g
@param validate_variable_list ���ؗp�ϐ����X�g
@param validate_statement_list �擾�������؎����i�[����Ƃ���
@param ignore_ast_list �|�C���^�ł̈ʒu�����؍ς݂ł���AIDENTIFIER�𖳎����邽�߂�AST�̃A�h���X���X�g
@param target_expression assign_expression�������Ă���expression_statement
@param undefined_control_check ����`�ȏ����i����`�|�C���^�̎Q�ƂȂǁj���s���Ă��Ȃ����ǂ��������؂��邽�߂̎��𐶐����邩�ǂ��� �P�F�������� �O�F�������Ȃ�
@param zero_divition_check 0�Ŋ����Ă��Ȃ����ǂ��������؂��邽�߂̎��𐶐����邩�ǂ����@�P�F��������@�O�F�������Ȃ�
@param array_unbound_check �z�񂪔͈͊O���Q�Ƃ��Ă��Ȃ����ǂ��������؂��邽�߂̎��𐶐����邩�ǂ����@�P�F��������@�O�F�������Ȃ�
@param free_violation_check ����������֌W�ŕs���ȏ������s���Ă��Ȃ����ǂ��������؂��邽�߂̎��𐶐����邩�ǂ����@�P�F��������@�O�F�������Ȃ�

@return �Ȃ�
*/
void getValidateStatementFromAssignStatement(AST *root, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
											ValidateVariableList *validate_variable_list,
											ValidateStatementList *validate_statement_list, ASTPOINTER_LIST *ignore_ast_list,
											AST *target_expression, int undefined_control_check, int zero_divition_check, int array_unbound_check
											, int free_violation_check);

/**
�|�C���^���Z����̓��e�����ؗp�ϐ��ɔ��f���邽�߂̌��؎���ǉ�����B

@param validate_statement_list ���؎����X�g
@param left_array_offset_list ���Ӓl�̔z��I�t�Z�b�g���X�g
@param right_array_offset_list �E�ӎ��̔z��I�t�Z�b�g���X�g
@param right_expression �E�ӎ��ւ̂`�r�s�A�h���X
@param a_op_flag ������Z�q�������������t���O 0:=,1:+=,2:-=,3:*=,4:/=,5:%=,6:<<=,7:>>=,8:&=,9:|=,10:^=
@return �Ȃ�
*/
void getValidateStatementFromPointerOperator(ValidateStatementList *validate_statement_list,ARRAY_OFFSET_LIST *left_array_offset_list,ARRAY_OFFSET_LIST *right_array_offset_list, AST *right_expression, int a_op_flag);

/**
������A�֐��ďo��T�������A�֐��ďo�ɑ΂��錟�؎���ǉ�����B

@param root �T���Ώۂ�AST�m�[�h
@param validate_statement_list ���؎����X�g
@param left_array_offset_list ���Ӓl�̔z��I�t�Z�b�g���X�g
@param right_array_offset_list �E�ӎ��̔z��I�t�Z�b�g���X�g
@param function_information_list �֐��Ɋւ����񃊃X�g

@return �Ȃ�
 */
void getValidateStatementFromCallFunction(AST *root, ValidateStatementList *validate_statement_list, ARRAY_OFFSET_LIST *left_array_offset_list,
		ARRAY_OFFSET_LIST *right_array_offset_list, FUNCTION_INFORMATION_LIST *function_information_list);

/**
�|�C���^���Z���ɑ΂��āA�|�C���^���Z�ɂ������{�I�Ȉʒu�̎��𕶎���Ƃ��ċ��߁Aoutput�ɓ����B
@param output �o�͐��CSTL������
@param left_array_offset_list ���Ӓl�̔z��I�t�Z�b�g���X�g
@param right_array_offset_list �E�ӎ��̔z��I�t�Z�b�g���X�g
@param right_expression_ast �E�ӎ��ւ�AST�A�h���X
@param a_op_flag ������Z�q�������������t���O 0:=,1:+=,2:-=,3:*=,4:/=,5:%=,6:<<=,7:>>=,8:&=,9:|=,10:^=

@return �Ȃ�

*/
void getBasisLocationFromAssignmentExpression(CSTLString *output, ARRAY_OFFSET_LIST *left_array_offset_list,
											  ARRAY_OFFSET_LIST *right_array_offset_list, AST *right_expression_ast, int a_op_flag);


/**
�w�肵����expression_ast����A�|�C���^���Z�ɂ������{�I�Ȉʒu�̎��𕶎���Ƃ��ċ��߁Aoutput�ɓ����B���̂Ƃ��Aarray_offset���������炻��ɊY�����鎮���O�ɕϊ�����B
@param output �o�͐��CSTL������
@param array_offset �w�肵�����ʎq�̔z��I�t�Z�b�g
@param expression_ast �w�肵�����ւ�AST�A�h���X
@return �Ȃ�
*/
void getBasisLocationFromExpression(CSTLString *output, ARRAY_OFFSET *array_offset, AST *expression_ast);

/**
�������m�ۊ֌W�̏��memalloc_info��z���|�C���^�̃I�t�Z�b�g���array_offset_list���猟�؎��𐶐����AValidateStatementList�ɒǉ�����B

@param variable_statement_list ������̌��؎����X�g
@param memalloc_info �������m�ۊ֌W�̏��
@param array_offset_list �z���|�C���^�̃I�t�Z�b�g���
@param ValidateVariableList ���ؗp�ϐ����X�g

@return �Ȃ�
*/
void createValidateStatementForMallocAction(ValidateStatementList *validate_statement_list, MEMALLOC_INFO *memalloc_info,
										ARRAY_OFFSET_LIST *array_offset_list,ValidateVariableList *validate_variable_list);

/**
�w�肵���z��I�t�Z�b�garrya_offset_list����A�C���N�������g����уf�N�������g�����܂�ł�����A
����ɉ�����basis_location�ɔ��f�����邽�߂̌��؎��𐶐����AValidateStatementList�ɒǉ�����B

@param validate_statement_list �ǉ���̌��؎�
@param array_offset_list �z��I�t�Z�b�g���X�g

@return �Ȃ�

*/
void createValidateStatemenFromIncDecExpr(ValidateStatementList *validate_statement_list, ARRAY_OFFSET_LIST *array_offset_list);

/**
����������֌W�̏��freememinfo���猟�؎��𐶐����AValidateStatementList�ɒǉ�����B

@param variable_statement_list ������̌��؎����X�g
@param freememinfo �������m�ۊ֌W�̏��
@param ValidateVariableList ���ؗp�ϐ����X�g

@return �Ȃ�
*/
void createValidateStatementForFreeAction(ValidateStatementList *validate_statement_list, FREEMEMINFO *freememinfo,
				ValidateVariableList *validate_variable_list);
/**
�ϐ���`���X�g�ŁA�z�񐶐����̌��ؗp�ϐ��̍X�V���邽�߂̌��؎����쐬���Avalidate_statement_list�ɒǉ�����B
�܂��A���ؗp�ϐ����X�gvalidate_variable_list�ɁA�z��̃I�t�Z�b�g�𐶐�����̂Ɏg�p����ϐ�vviterator_2�`vviterator_n�in�͔z��̍ő原�����j�𐶐����A�ǉ�����B
@param validate_variable_list ���ؗp�ϐ����X�g
@param validate_statement_list �ǉ���̌��؎�
@param variable_table_list �ϐ��e�[�u�����X�g
@param function_information_list �֐���`�Ɋւ����񃊃X�g
@return �Ȃ�
*/
void createValidateStatementFromArrayDefine(ValidateVariableList *validate_variable_list, ValidateStatementList *validate_statement_list, VARIABLE_TABLE_LIST *variable_table_list
					,FUNCTION_INFORMATION_LIST *function_information_list);

/**
�ϐ���`���X�g�Ń|�C���^�ϐ��ɑ΂��錟�ؗp�ϐ����X�V���邽�߂̌��؎����쐬���Avalidate_statement_list�ɒǉ�����B
@param validate_statement_list �ǉ���̌��؎�
@param variable_table_list �ϐ��e�[�u�����X�g
@param function_information_list �֐���`�Ɋւ����񃊃X�g

@return �Ȃ�
*/
void createVaridateStatementFromPointerDefine( ValidateStatementList *validate_statement_list, VARIABLE_TABLE_LIST *variable_table_list,
			FUNCTION_INFORMATION_LIST *function_information_list);

/**
�z��̃I�t�Z�b�g���X�g����ɁA���؎����쐬����B
@param output �o�͂��錟�؎�
@param ValidateVariableList ���ؗp�ϐ����X�g
@param variable_table �Ώۂ̕ϐ��f�[�^
@param offset_list �I�t�Z�b�g���X�g

@return �Ȃ�
*/
void ArrayOffsetToValidateStatement(CSTLString* output, ValidateVariableList *validate_variable_list, VARIABLE_TABLE *variable_table, OFFSET_LIST *offset_list);

/**
�z���|�C���^�Ȃǂ̃I�t�Z�b�g���̃��X�garray_offset_list����A�z��͈̔͊O�Q�Ƃ̃`�F�b�N�����邽�߂̌��؎�
��A����`��Ԃŏ������`�F�b�N���邽�߂̌��؎��𐶐����AValidateStatementList�֒ǉ�����B

@param validate_statement_list �ǉ���̌��؎����X�g
@param array_offset_list �z���|�C���^�Ȃǂ̃I�t�Z�b�g���̃��X�g
@param array_unbound_check �z�񂪔͈͊O���Q�Ƃ��Ă��Ȃ����ǂ��������؂��邽�߂̎��𐶐����邩�ǂ����@�P�F��������@�O�F�������Ȃ�
@param undefined_control_check ����`�ȏ������s���Ă��Ȃ����ǂ��������؂��邽�߂̎��𐶐����邩�ǂ��� �P�F�������� �O�F�������Ȃ�
@return �Ȃ�
*/
void createCheckUnboundAndUndefineOperationCheck(ValidateStatementList *validate_statement_list, ARRAY_OFFSET_LIST *array_offset_list, int array_unbound_check, int undefined_control_check);

/**
����������֌W�̏��freememinfo����Afree�֐��Ɋւ���ᔽ�s�ׂ��s���Ă��Ȃ����ǂ������`�F�b�N���邽�߂̌��؎��𐶐����AValidateStatementList�֒ǉ�����B

@param validate_statement_list �ǉ���̌��؎����X�g
@param freememinfo ����������֌W�̏��

@return �Ȃ�
*/
void createViolentFreeOperation(ValidateStatementList *validate_statement_list, FREEMEMINFO *freememinfo);

/**
���Z����я�]���̏�񂩂�A�[�����Z����я�]�ɂȂ��Ă��Ȃ����ǂ����̌��؎��𐶐�����B
@param validate_statement_list �i�[��̌��؎����X�g
@param divition_information_list �Ώۂ̏��Z����я�]���̏��

@return �Ȃ�
*/
void createZeroDivitionCheck(ValidateStatementList *validate_statement_list, DIVITION_INFORMATION_LIST *divition_information_list);
/**
���؎����X�gValidateStatementList����Atarget_statement�Ɠ���AST�̃A�h���X�����������̂�T���o���A�������ɏd�����Ȃ��悤�ɂ��邽�߂̐V�������؎��̎��ʔԍ����擾����B
�V�������؎������ɂ͂��̊֐�����V�������ʔԍ����擾���邱�ƁB

@param validate_statement_list �Ώۂ̌��؎����X�g
@param target_statement �Ώۂ̌��؎�����m�F���邽�߂�AST�̃A�h���X

@return �V�������ʔԍ����o�͂���B���łɓ���AST�̃A�h���X�������Ă��錟�؎����Ȃ���΂O��Ԃ��B
*/
int getNewValidateStatementID(ValidateStatementList *validate_statement_list, AST *target_statement);

/**
������̍��Ӓl�ɂ��āA���؎��ɕK�v�ȏ����擾����B
@param left_expression ���Ӓl�Ɋւ���AST�m�[�h
@param function_information_list �֐��Ɋւ�����̃��X�g
@param vtlist ���ؑΏۂ̎����}�[�N���邽�߂̕ϐ����X�g
@param ignore_ast_list �|�C���^�ł̈ʒu�����؍ς݂ł���AIDENTIFIER�𖳎����邽�߂�AST�̃A�h���X���X�g
@param array_offset_list �e�|�C���^����єz�񂲂Ƃ̃I�t�Z�b�g�̃��X�g
@param target_expression ���̍��ӎ��̏�ʂɈʒu����AST�m�[�h
@param switch_mode ���ڃA�N�Z�X����єz��A�N�Z�X��T�����AIDENTIFIER��T�����ǂ����̃X�C�b�`�t���O �O�F�����������@�P�Fdirect_ref��array_access�̂ݒT��
@return �Ȃ�
*/
void getLeftAssignmentInfo(AST *left_expression, FUNCTION_INFORMATION_LIST *function_information_list,
		VARIABLE_TABLE_LIST *vtlist, ASTPOINTER_LIST *ignore_ast_list, ARRAY_OFFSET_LIST * array_offset_list,
		AST *target_expression, int *switch_mode);

/**
������̉E�ӎ��ɂ��āA���؎��ɕK�v�ȏ����擾����B
@param root �E�ӎ��Ɋւ���AST�m�[�h
@param function_information_list �֐��Ɋւ�����̃��X�g
@param vtlist �������m�ۏ����擾����̂ɕK�v�ȃv���O�����ϐ����X�g
@param memalloc_info malloc�֌W�̏�񂪏o�͂����
@param array_offset_list ���ӎ���ɂ���|�C���^�Q�Ƃɑ΂���I�t�Z�b�g���X�g
@param ignore_ast_list �����ʒu�̃|�C���^�����Ă��������邽�߂̃��X�g
@param target_statement ���̌v�Z���𑮂��Ă���AST�m�[�h�ւ̃A�h���X�i��{�I��expression_statement�ł���m�[�h������j

@return �Ȃ�
*/
void getRightAssignmentInfo(AST *root, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist, MEMALLOC_INFO **memalloc_info,
	 ARRAY_OFFSET_LIST *array_offset_list, ASTPOINTER_LIST *ignore_ast_list, AST *target_statement);

/**
���؎����X�g�ƂƂ��Ƀv���O�����f�[�^���o�͂���B

@param root �v���O�����ւ�AST�m�[�h
@param validate_variable_list ���ؗp�ϐ����X�g
@param validate_statement_list ���؎����X�g
@param for_information_list for���Ɋւ�����̃��X�g

@return �Ȃ�
*/
void printProgramDataWithValidateStatement(AST *root, ValidateVariableList *validate_variable_list, ValidateStatementList *validate_statement_list, ForInformationList *for_information_list);

/**
���؎����X�g�⌟�ؗp�ϐ������ƂɃv���O�����f�[�^�𐶐����A�w�肵���t�@�C��output�ɏo�͂���B

@param output �o�͐�̃t�@�C���\����
@param root �v���O�����ւ�AST�m�[�h
@param validate_variable_list ���ؗp�ϐ����X�g
@param validate_statement_list ���؎����X�g
@param for_information_list for���Ɋւ�����̃��X�g

@return �Ȃ�
*/
void fprintProgramDataWithValidateStatement(FILE *output, AST *root, ValidateVariableList *validate_variable_list, ValidateStatementList *validate_statement_list, ForInformationList *for_information_list);

/**
���ɑΉ����錟�؎����o�͂�����B

@param output �o�͐�̃t�@�C���\����
@param validate_statement_list �o�͑Ώۂ̌��؎����X�g
@param target_ast �Ώۂ�AST�m�[�h
@param check_or_modify ���؎����`�F�b�N����^�C�v���A�v���O���������ɕҏW����^�C�v���𔻒f����t���O�B�O�F�`�F�b�N����^�C�v�A�P�F�ҏW����^�C�v
@param allow_output_used_statement �g�p�ς݂̌��؎����܂߂ďo�͂��邩�ǂ����̃t���O�@�O�F�o�͂��Ȃ��@�P�F�o�͂���

@return �Ȃ�
*/
void fprintValidateStatement(FILE *output, ValidateStatementList *validate_statement_list, AST *target_ast, int check_or_modify, int allow_output_used_statement);

/**
���ɑΉ����錟�؎���assert(0); ���폜���������o�͂�����B

@param output �o�͐�̃t�@�C���\����
@param validate_statement_list �o�͑Ώۂ̌��؎����X�g
@param target_ast �Ώۂ�AST�m�[�h
@param check_or_modify ���؎����`�F�b�N����^�C�v���A�v���O���������ɕҏW����^�C�v���𔻒f����t���O�B�O�F�`�F�b�N����^�C�v�A�P�F�ҏW����^�C�v
@param allow_output_used_statement �g�p�ς݂̌��؎����܂߂ďo�͂��邩�ǂ����̃t���O�@�O�F�o�͂��Ȃ��@�P�F�o�͂���

@return �Ȃ�
*/
void fprintValidateStatement_not_assert(FILE *output, ValidateStatementList *validate_statement_list, AST *target_ast, int check_or_modify, int allow_output_used_statement);
/**
�v���O�����X���C�V���O���̕ϐ���`�����ƂɁA���ؗp�ϐ����X�g�̏o�͂�ݒ肷��B
@param validate_variable_list ���ؗp�ϐ����X�g
@param expr_slicing_list �v���O�����X���C�V���O���̃��X�g

@return �Ȃ�
 */
void setValidateVariableFromExprSlicing(ValidateVariableList *validate_variable_list, EXPR_SLICING_LIST *expr_slicing_list);

/**
�v���O�����X���C�V���O�������ƂɌ��؎���ǉ����Ȃ���o�͂�����B

@param output �o�͂����̃t�@�C��
@param expr_slicing_list �v���O�����X���C�V���O���
@param validate_variable_list ���ؗp�ϐ����X�g
@param validate_statement_list ���؎����X�g
@param for_information_list for���Ɋւ�����
@param check_target_ast �`�F�b�N���؎��̑Ώۂւ�AST�m�[�h

@return �Ȃ�
 */
void fprintProgramDataWithPSIVaridateStatement(FILE *output, EXPR_SLICING_LIST *expr_slicing_list, ValidateStatementList *validate_statement_list,
			ValidateVariableList *validate_variable_list, ForInformationList *for_information_list, AST *check_target_ast);

/**
�v���O�������`�F�b�N�����ƂɃv���O�����X���C�V���O�ƌ��؎��t�����s�����t�@�C���𐶐�����B
@param expr_slicing_list �v���O�����X���C�V���O���
@param validate_variable_list ���ؗp�ϐ����X�g
@param validate_statement_list ���؎����X�g
@param for_information_list for���Ɋւ�����
@param include_list �C���N���[�h���X�g

@return �Ȃ�
 */

void createValidateStatementAdderFileEachCheck(EXPR_SLICING_LIST *expr_slicing_list, ValidateStatementList *validate_statement_list,
		ValidateVariableList *validate_variable_list, ForInformationList *for_information_list, INCLUDE_LIST *include_list);

/**
���؎����X�g��AST�m�[�h���ƂɃ\�[�g����B
@param validate_statement_list �\�[�g�Ώۂ̌��؎����X�g


@return �Ȃ�
*/
void ValidateStatementList_sort_ast(ValidateStatementList *validate_statement_list);

/**
���؎����X�g�̃`�F�b�N������AAST�m�[�h�����o���AAST���X�g�Ƃ��Ă܂Ƃ߂�B
@param validate_statement_list ���o����̌��؎����X�g
@param ast_node_list �܂Ƃ߂���AST�m�[�h���X�g

@return �Ȃ�
 */
void getASTList_FromValidateStatementList(ValidateStatementList *validate_statement_list, ASTPOINTER_LIST *ast_node_list);

#endif
