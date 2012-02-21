#include "Varidate_statement.h"
#include "../Library/Stack_int.h"
#include "../Library/StoreInformation.h"
#include "ANSIC_CODE.h"
#include <stdio.h>
#include<limits.h>

//�f�o�b�O���[�h
#define DEBUG_MODE


//������̒���
#define STRLEN 256

//VARIDATE�Ŏg�p�����Ƃ����t���O�̒l
#define VALIDATE_USED 1
//VARIDATE�Ŏg�p���Ă��Ȃ��Ƃ����t���O�̒l
#define VALIDATE_NOTUSED 0
//���I�z��������^�C�v
#define MALLOC_DYNAMIC_ARRAY_MODE 1
//�P��̒l�������^�C�v
#define MALLOC_SINGLE_MODE 2
//����������Ă͂܂�Ȃ��^�C�v
#define MALLOC_UNDEF_TYPE 0

//�A���p�T���h�L���i�A�h���X���Z�q�j���o�R���Ă��邩�ۂ��������L��
#define VIA_ANPASAND 1
#define NOT_VIA_ANPASAND 0

//�C���N�������g���f�N�������g���܂܂�Ă��邩�ǂ����������t���O
#define NOT_INC_DEC 0
#define VIA_INC 1
#define VIA_DEC 2

//�o�͂���^�C�v�����؎��ҏW�^�C�v���`�F�b�N�^�C�v���������t���O
#define CHECK_VS 0
#define MODIFY_VS 1

//���������ꍇ
#define SUCCESS 1
//���s�����ꍇ
#define FAILED 0

//���Z����]�Z���ǂ����̃t���O
#define TYPE_DIV 0
#define TYPE_MOD 1

//������Z�q�������Ƃ����t���O0:=,1:+=,2:-=,3:*=,4:/=,5:%=,6:<<=,7:>>=,8:&=,9:|=,10:^=
#define EQUAL 0
#define PLUS_EQUAL 1
#define MINUS_EQUAL 2
#define MUL_EQUAL 3
#define DIV_EQUAL 4
#define MOD_EQUAL 5
#define LEFT_EQUAL 6
#define RIGHT_EQUAL 7
#define AND_EQUAL 8
#define OR_EQUAL 9
#define XOR_EQUAL 10

//�����U��
#define TRUE 1
#define FALSE 0

//assert(0);
#define ASSERT_STRING "assert(0);"

CSTL_LIST_IMPLEMENT(ValidateVariableList, ValidateVariable);

CSTL_LIST_IMPLEMENT(ValidateStatementList, ValidateStatement);

/**
���ۂɌ��؎��Ƃ��đ}�����邽�߂̏��𐶐�����B
@param target_id ���̌��؎��̎���ID(�ǂ̏����ł��̌��؎������Ă��������m�F���邽�߂�ID)
@param check_or_modify ���؎����`�F�b�N����^�C�v���A�v���O���������ɕҏW����^�C�v���𔻒f����t���O�B�O�F�`�F�b�N����^�C�v�A�P�F�ҏW����^�C�v
@param used ���̌��؎��͎g�p���Ă��邩�ǂ����̃t���O 1:�g�p 0:���g�p
@param statement ���̌��؎��̓��e
@param target_statement ���̌��؎��̃^�[�Q�b�g�ƂȂ�AST�m�[�h�ւ̃A�h���X

@return ���ۂɌ��؎��Ƃ��đ}�����邽�߂̏��ւ̃A�h���X��Ԃ��B
*/
ValidateStatement *new_VALIDATE_STATEMENT_char(int target_id, int check_or_modify, int used, char *statement, AST *target_statement){

	CSTLString *statement_cstl = CSTLString_new();
	CSTLString_assign(statement_cstl, statement);

	return new_VALIDATE_STATEMENT(target_id, check_or_modify, used, statement_cstl, target_statement);
}

/**
���ۂɌ��؎��Ƃ��đ}�����邽�߂̏��𐶐�����B
@param target_id ���̌��؎��̎���ID(�ǂ̏����ł��̌��؎������Ă��������m�F���邽�߂�ID)
@param check_or_modify ���؎����`�F�b�N����^�C�v���A�v���O���������ɕҏW����^�C�v���𔻒f����t���O�B�O�F�`�F�b�N����^�C�v�A�P�F�ҏW����^�C�v
@param used ���̌��؎��͎g�p���Ă��邩�ǂ����̃t���O 1:�g�p 0:���g�p
@param statement ���̌��؎��̓��e
@param target_statement ���̌��؎��̃^�[�Q�b�g�ƂȂ�AST�m�[�h�ւ̃A�h���X

@return ���ۂɌ��؎��Ƃ��đ}�����邽�߂̏��ւ̃A�h���X��Ԃ��B
*/
ValidateStatement *new_VALIDATE_STATEMENT(int target_id, int check_or_modify, int used, CSTLString *statement, AST *target_statement){
	//���ۂɌ��؎��Ƃ��đ}�����邽�߂̏��𐶐�����
	ValidateStatement* new_validate_statement = (ValidateStatement*)malloc(sizeof(ValidateStatement));

	//�K�v�ȏ��������Ă���
	new_validate_statement->target_id = target_id;
	new_validate_statement->check_or_modify = check_or_modify;
	new_validate_statement->used = used;
	new_validate_statement->statement = statement;
	new_validate_statement->target_statement = target_statement;

	//���ۂɌ��؎��Ƃ��đ}�����邽�߂̏��ւ̃A�h���X��Ԃ�
	return new_validate_statement;
}

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
								   int block_level ,int block_id, CSTLString *type, CSTLString *variable_name, CSTLString *target_variable_name, int offset_level){
	//�V�������ؗp�ϐ��f�[�^�𐶐�����
	ValidateVariable *new_validate_variable_data = (ValidateVariable*)malloc(sizeof(ValidateVariable));

	//���ؗp�ϐ��f�[�^�ɕK�v�ȃf�[�^��ݒ肷��
	new_validate_variable_data->used = used;
	new_validate_variable_data->enable_start = enable_start;
	new_validate_variable_data->enable_end = enable_end;
	new_validate_variable_data->declaration_location = declaration_location;
	new_validate_variable_data->block_level = block_level;
	new_validate_variable_data->block_id = block_id;
	new_validate_variable_data->type = type;
	new_validate_variable_data->variable_name = variable_name;
	new_validate_variable_data->target_variable_name = target_variable_name;
	new_validate_variable_data->offset_level = offset_level;

	//�V�����������ꂽ���ؗp�ϐ��̃f�[�^�ւ̃A�h���X���Ԃ����
	return new_validate_variable_data;
}

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
								   int block_level ,int block_id, char *type, char *variable_name, char *target_variable_name, int offset_level){
	//CSTLString�����̌^���A�ϐ����A���ؑΏۂ̕ϐ�����ݒ肷��
	CSTLString *CSTLtype = CSTLString_new();
	CSTLString *CSTLvariable_name = CSTLString_new();
	CSTLString *CSTLtarget_variable_name = CSTLString_new();

	CSTLString_assign(CSTLtype, type);
	CSTLString_assign(CSTLvariable_name, variable_name);
	CSTLString_assign(CSTLtarget_variable_name, target_variable_name);

	//�V�������ؗp�ϐ��f�[�^�𐶐�����
	ValidateVariable *new_validate_variable_data = new_VALIDATE_VARIABLE(used, enable_start, enable_end, declaration_location,
									block_level , block_id, CSTLtype, CSTLvariable_name, CSTLtarget_variable_name, offset_level);

	//�V�����������ꂽ���ؗp�ϐ��̃f�[�^�ւ̃A�h���X���Ԃ����
	return new_validate_variable_data;
}

/**
���؎����X�g�̎g�p�t���O�𖢎g�p��Ԃɏ���������B
@param validate_statement_list *�������Ώۂ̌��؎����X�g

@return �Ȃ�
 */
void initVaridateStatement_flag(ValidateStatementList *validate_statement_list){
	ValidateStatementListIterator vs_list_i;

	//���ׂĂ̌��؎����X�g�̎g�p�t���O�𖢎g�p��Ԃɏ���������
	for(vs_list_i = ValidateStatementList_begin(validate_statement_list);
		vs_list_i != ValidateStatementList_end(validate_statement_list);
		vs_list_i = ValidateStatementList_next(vs_list_i)){
			ValidateStatementList_data(vs_list_i)->used = VALIDATE_NOTUSED;
		}
}

/**
�v���O�����̕ϐ����X�g�����ƂɃv���O�����̌��ؗp�̕ϐ���ݒ肷��B
@param variable_table_list �v���O�����̕ϐ����X�g
@param validate_variable ���ؗp�̕ϐ����X�g
@return �Ȃ�
*/
void getValidate_Variable(VARIABLE_TABLE_LIST *variable_table_list, ValidateVariableList *validate_variable)
{
	VARIABLE_TABLE_LISTIterator valist;
	//�|�C���^�̎����A�z��̎��������߂�
	int pointer_level, array_level;
	int i,j;

	//���؎��̕ϐ�����ݒ肳����̂Ɏg�p����
	char variable_name[STRLEN];
	//���ؑΏۂ̕ϐ�����ݒ肳����̂Ɏg�p����
	char variable_table_lists_name_char[STRLEN];

	CSTLString *astalisk = CSTLString_new();
	CSTLString *variable_table_lists_name = CSTLString_new();

	//�|�C���^�Ŏn�߂鎟���̃I�t�Z�b�g
	int pointer_start_offset=0;

	//���ؗp�ϐ��Ƃ���malloc�̎��ʔԍ���t�����邽�߂̕ϐ����`����
	/*ValidateVariableList_push_back_ref( validate_variable,

	new_VALIDATE_VARIABLE_with_char(VALIDATE_NOTUSED,
									1,
									INT_MAX,
									1,
									0,
									0,
									"int",
									"malloc_number = 1",
									"null",
									1
	)
	);*/

	//�v���O�����̕ϐ����X�g�����ׂĎQ�Ƃ�����
	for(valist = VARIABLE_TABLE_LIST_begin(variable_table_list);
		valist != VARIABLE_TABLE_LIST_end(variable_table_list);
		valist = VARIABLE_TABLE_LIST_next(valist)){
			//���ؑΏۂ̕ϐ������擾����
			CSTLString_assign(variable_table_lists_name,CSTLString_c_str(VARIABLE_TABLE_LIST_data(valist)->variable_name));
			//���ؑΏۂ̕ϐ�������|�C���^��z��������L�������ׂď�������
			deletePointerAndArraySynbol(variable_table_lists_name);
			//���ؑΏۂ̕ϐ�����ݒ肷�邽�߂̕�����z��ɓ���Ă���
			sprintf(variable_table_lists_name_char, "%s", CSTLString_c_str(variable_table_lists_name));
			//���ؑΏۂ̕ϐ�������|�C���^�̎�������сA�z��̎������v�Z����
			getPointerLevelAndArrayLevelFromVARIABLE_TABLE(VARIABLE_TABLE_LIST_data(valist), &pointer_level, &array_level);



			//���؂��邽�߂̕ϐ��Ƀ|�C���^�L�������邽�߂ɐ�������
			//�i����̓_�u���|�C���^�ȍ~�́A�i�[���Ă���ꏊ���قȂ�ƁA�i�[�ł���|�C���^�̐����ς��邱�Ƃ��ł��邽�߁A
			//���̊K�w���̏�Ԃ����؂ł���悤�ɂ��邽�߂ɕK�v�ł���B)
			CSTLString_assign(astalisk,"");

			for(i = 1; i <= pointer_level + array_level; i++){

				//�|�C���^�z��̋��e�͈́i���Ȃ킿�z��̑傫���j���������ؗp�̕ϐ��𐶐�����

				sprintf(variable_name, "*%smax_size_%d_%s", CSTLString_c_str(astalisk), i, variable_table_lists_name_char);

				ValidateVariableList_push_back_ref( validate_variable,

					new_VALIDATE_VARIABLE_with_char(VALIDATE_NOTUSED,
													VARIABLE_TABLE_LIST_data(valist)->enable_start,
													VARIABLE_TABLE_LIST_data(valist)->enable_end,
													VARIABLE_TABLE_LIST_data(valist)->enable_start,
													VARIABLE_TABLE_LIST_data(valist)->block_level,
													VARIABLE_TABLE_LIST_data(valist)->block_id,
													"int",
													variable_name,
													variable_table_lists_name_char,
													i
					)
					);

				//�|�C���^�������ݎ����Ă���z��̈ʒu���������ؗp�̕ϐ��𐶐�����
				sprintf(variable_name, "%sbasis_location_%d_%s", CSTLString_c_str(astalisk), i, variable_table_lists_name_char);

				ValidateVariableList_push_back_ref( validate_variable,

					new_VALIDATE_VARIABLE_with_char(VALIDATE_NOTUSED,
													VARIABLE_TABLE_LIST_data(valist)->enable_start,
													VARIABLE_TABLE_LIST_data(valist)->enable_end,
													VARIABLE_TABLE_LIST_data(valist)->enable_start,
													VARIABLE_TABLE_LIST_data(valist)->block_level,
													VARIABLE_TABLE_LIST_data(valist)->block_id,
													"int",
													variable_name,
													variable_table_lists_name_char,
													i
					)
					);

				//�|�C���^�����I�E�ÓI�ȕϐ����킸�A�h���X���ݒ肳��Ă��邩�ǂ����������߂̌��ؗp�̕ϐ��𐶐�����
				sprintf(variable_name, "*%sdefined_%d_%s", CSTLString_c_str(astalisk), i, variable_table_lists_name_char);

				ValidateVariableList_push_back_ref( validate_variable,

					new_VALIDATE_VARIABLE_with_char(VALIDATE_NOTUSED,
													VARIABLE_TABLE_LIST_data(valist)->enable_start,
													VARIABLE_TABLE_LIST_data(valist)->enable_end,
													VARIABLE_TABLE_LIST_data(valist)->enable_start,
													VARIABLE_TABLE_LIST_data(valist)->block_level,
													VARIABLE_TABLE_LIST_data(valist)->block_id,
													"int",
													variable_name,
													variable_table_lists_name_char,
													i
					)
					);

				//�|�C���^�����I�ȕϐ��̃A�h���X���ݒ肳��Ă��邩�ǂ������������߂̌��ؗp�̕ϐ��𐶐�����
				sprintf(variable_name, "*%smalloc_flag_%d_%s", CSTLString_c_str(astalisk), i, variable_table_lists_name_char);


				ValidateVariableList_push_back_ref( validate_variable,

					new_VALIDATE_VARIABLE_with_char(VALIDATE_NOTUSED,
													VARIABLE_TABLE_LIST_data(valist)->enable_start,
													VARIABLE_TABLE_LIST_data(valist)->enable_end,
													VARIABLE_TABLE_LIST_data(valist)->enable_start,
													VARIABLE_TABLE_LIST_data(valist)->block_level,
													VARIABLE_TABLE_LIST_data(valist)->block_id,
													"int",
													variable_name,
													variable_table_lists_name_char,
													i
					)
					);

				//�|�C���^�������A�X�^���X�N��ǉ�������
				CSTLString_append(astalisk, "*");
			}

	}
	//�A�X�^���X�N������������������������������
	CSTLString_delete(astalisk);
	//���ؑΏۂ̕ϐ������擾���邽�߂Ɏg�p����������̃����������������
	CSTLString_delete(variable_table_lists_name);
}

/**
���ؗp�ϐ��e�[�u���̃��X�g�̓��e���o�͂�����B
@param validate_variable_list �o�͑Ώۂ̌��ؗp�ϐ��e�[�u���̃��X�g
@return �Ȃ�

*/
void printValidateVariableList(ValidateVariableList *validate_variable_list){
	ValidateVariableListIterator vtlist;
	int counter = 1;

	printf("---------------VARIDATE_VARIABLE_TABLE---------------\n\n");

	for(vtlist = ValidateVariableList_begin(validate_variable_list);
	vtlist != ValidateVariableList_end(validate_variable_list);
	vtlist = ValidateVariableList_next(vtlist)){
		printf("---------------VARIDATE_VARIABLE_%d_INFO---------------\n\n", counter);
		printf("VARIDATE_VARIABLE_%d_USED = \"%d\"\n", counter, ValidateVariableList_data(vtlist)->used);
		printf("VARIDATE_VARIABLE_%d_TYPE = \"%s\"\n", counter, CSTLString_c_str(ValidateVariableList_data(vtlist)->type));
		printf("VARIDATE_VARIABLE_%d_NAME = \"%s\"\n", counter, CSTLString_c_str(ValidateVariableList_data(vtlist)->variable_name));
		printf("VARIDATE_VARIABLE_%d_TARGET_VARIABLE_NAME = \"%s\"\n", counter, CSTLString_c_str(ValidateVariableList_data(vtlist)->target_variable_name));
		printf("VARIDATE_VARIABLE_%d_ENABLE_START = \"%d\"\n", counter, ValidateVariableList_data(vtlist)->enable_start);
		printf("VARIDATE_VARIABLE_%d_ENABLE_END = \"%d\"\n", counter, ValidateVariableList_data(vtlist)->enable_end);
		printf("VARIDATE_VARIABLE_%d_DECLARATION_LOCATION = \"%d\"\n", counter, ValidateVariableList_data(vtlist)->declaration_location);
		printf("VARIDATE_VARIABLE_%d_BLOCK_LEVEL = \"%d\"\n", counter, ValidateVariableList_data(vtlist)->block_level);
		printf("VARIDATE_VARIABLE_%d_BLOCK_ID = \"%d\"\n\n", counter, ValidateVariableList_data(vtlist)->block_id);
		printf("VARIDATE_VARIABLE_%d_OFFSET_LEVEL = \"%d\"\n\n", counter, ValidateVariableList_data(vtlist)->offset_level);
		counter++;
	}
	printf("--------------------------------------------\n\n");
}

/**
��{�I�Ȍ��؎��̐������s���B
@param root ���؎������Ώۂ�AST�m�[�h
@param function_informaiton_list �֐��Ɋւ�����̃��X�g
@param vtlist ���ؑΏۂ̎����}�[�N���邽�߂̕ϐ����X�g
@param validate_statement_list ���ؗp�ϐ����X�g
@param validate_variable_list �擾�������؎����i�[����Ƃ���
@param for_information_list for���Ɋւ�����
@param undefined_control_check ����`�ȏ����i����`�|�C���^�̎Q�ƂȂǁj���s���Ă��Ȃ����ǂ��������؂��邽�߂̎��𐶐����邩�ǂ��� �P�F�������� �O�F�������Ȃ�
@param zero_divition_check 0�Ŋ����Ă��Ȃ����ǂ��������؂��邽�߂̎��𐶐����邩�ǂ����@�P�F��������@�O�F�������Ȃ�
@param array_unbound_check �z�񂪔͈͊O���Q�Ƃ��Ă��Ȃ����ǂ��������؂��邽�߂̎��𐶐����邩�ǂ����@�P�F��������@�O�F�������Ȃ�
@param free_violation_check ����������֌W�ŕs���ȏ������s���Ă��Ȃ����ǂ��������؂��邽�߂̎��𐶐����邩�ǂ����@�P�F��������@�O�F�������Ȃ�

@return �Ȃ�
*/
void createValidateStatement(AST * root, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist, ValidateVariableList *validate_variable_list,
											ValidateStatementList *validate_statement_list, ForInformationList *for_information_list, int undefined_control_check,
											int zero_divition_check, int array_unbound_check, int free_violation_check){
	//AST�̎q�m�[�h���Q�Ƃ����邽�߂̃C�e���[�^
	ASTListIterator ast_iterator;
	//�|�C���^�ł̈ʒu�����؍ς݂ł���AIDENTIFIER�𖳎����邽�߂�AST�̃A�h���X���X�g
	ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();
	//���̎w�W�ƂȂ�expression_statement��������ꂽ��
	if(CSTLString_compare_with_char(root->name, "expression_statement") == 0){
		//�w�肵���m�[�h����A�������T���o���A���̌��ؓ��e��validate_statement_list�֓����B
		getValidateStatementFromAssignStatement(root, function_information_list, vtlist, validate_variable_list, validate_statement_list, ignore_ast_list,
												root, undefined_control_check, zero_divition_check, array_unbound_check, free_violation_check);

	}
	//�ϐ��̒�`�ł���ꍇ
	else if(CSTLString_compare_with_char(root->name, "declaration_with_init") == 0){
		//�ϐ��̏�����`�������o���A����Ɋ�Â��Č��ؓ��e��validate_statement_list�֓����B
		getValidateStatementFromInitializer(root, function_information_list, vtlist, validate_variable_list, validate_statement_list, ignore_ast_list,
											root, undefined_control_check, zero_divition_check, array_unbound_check);
	}
	//for���n���������ꍇ
	else if(CSTLString_compare_with_char(root->name, "for_statement_type_a") == 0 ||
		CSTLString_compare_with_char(root->name, "for_statement_type_b") == 0 ||
		CSTLString_compare_with_char(root->name, "for_statement_type_c") == 0 ||
		CSTLString_compare_with_char(root->name, "for_statement_type_d") == 0){

		//for���Ɋւ�������擾����
		getFOR_INFORMATION_LIST(for_information_list, root);

		//for���̖����̏�񂩂�A���؎����擾���A���؎����X�g�ɓ����
		getValidateStatementFromForIteration(validate_statement_list, for_information_list, function_information_list, vtlist, validate_variable_list, ignore_ast_list,
			undefined_control_check, zero_divition_check, array_unbound_check , free_violation_check);
	}


	//AST�̎q�m�[�h���Q�Ƃ�����
	for(ast_iterator = ASTList_begin(root->children);
		ast_iterator != ASTList_end(root->children);
		ast_iterator = ASTList_next(ast_iterator)){

		createValidateStatement( ASTList_data(ast_iterator), function_information_list, vtlist,validate_variable_list,
				validate_statement_list, for_information_list, undefined_control_check, zero_divition_check, array_unbound_check, free_violation_check);

	}
}

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
											, int free_violation_check){
	//AST�̎q�m�[�h���Q�Ƃ����邽�߂̃C�e���[�^
	ASTListIterator ast_iterator;
	int mode = 0;

	//��������������ꍇ
	if(CSTLString_compare_with_char(root->name, "assignment_expression") == 0){
		int a_op_flag;

		//malloc�֌W�̏��
		MEMALLOC_INFO * memalloc_info = NULL;
		//���Ӓl�ɂ�����e�����̃|�C���^��z��̃I�t�Z�b�g�Ɋւ�����̃��X�g
		ARRAY_OFFSET_LIST * left_array_offset_list = ARRAY_OFFSET_LIST_new();

		//�E�ӎ��ɂ�����e�����̃|�C���^��z��̃I�t�Z�b�g�Ɋւ�����̃��X�g
		ARRAY_OFFSET_LIST * right_array_offset_list = ARRAY_OFFSET_LIST_new();

		AST *left_expression = ASTList_data(ASTList_begin(root->children));

		AST *right_expression = ASTList_data(ASTList_next(ASTList_next(ASTList_begin(root->children))));

		//���Z����я�]�Ɋւ����񃊃X�g
		DIVITION_INFORMATION_LIST *divition_information_list = DIVITION_INFORMATION_LIST_new();

		//������̃^�C�v���擾����
		a_op_flag = getAssignment_TYPE(root);

		//������̍��Ӓl�ɂ��ĒT��������i�q�m�[�h�̂P�Ԗڂ̎Q�Ɓj
		getLeftAssignmentInfo(left_expression , function_information_list, vtlist, ignore_ast_list, left_array_offset_list, target_expression, &mode);
		//������̉E�ӎ��ɂ��ĒT��������i�q�m�[�h�̂R�Ԗڂ̎Q�Ɓj
		getRightAssignmentInfo(right_expression, function_information_list, vtlist, &memalloc_info, right_array_offset_list, ignore_ast_list, target_expression);

		//�E�ӎ�����A���Z����я�]�Z�Ɋւ�������i�[������
		getDIVITION_INFORMATION_LIST(right_expression, function_information_list, vtlist, divition_information_list, target_expression, ignore_ast_list);

		//DEBUG_MODE���L���Ȏ��������m�ۊ֌W�̏����o�͂���
		#ifdef DEBUG_MODE
			if(memalloc_info != NULL){
				printMEMALLOC_INFO(memalloc_info);
			}
		#endif

		//�����Amalloc_info���牽�炩�̏����擾�ł����ꍇ
		if(memalloc_info != NULL){
			//malloc_info��left_array_offset_list���猟�؎��𐶐�����
			createValidateStatementForMallocAction(validate_statement_list, memalloc_info, left_array_offset_list, validate_variable_list);

			//�֐��Ăяo����T���A���̎��̊֐�����malloc�܂���calloc�̏ꍇ��malloc�p���ʔԍ������邽�߂̕ϐ��𐶐�������
			AST *call_function = NULL;
			CSTLString *function_name = CSTLString_new();

			call_function = getASTwithString(right_expression, "call_function", -1);

			getStringFromAST(function_name, ASTList_data(ASTList_begin(call_function->children)));

			if(call_function != NULL && (CSTLString_compare_with_char(function_name, "malloc") == 0 ||
				CSTLString_compare_with_char(function_name, "calloc") == 0)){

				getValidateStatementFromMallocNumber(validate_statement_list, call_function, left_array_offset_list, memalloc_info);

			}

			CSTLString_delete(function_name);
		}

		//�����Aarray_unbound_check���L���ɂȂ��Ă����ꍇ�A�z��͈̔͊O�Q�Ƃ����؂��邽�߂̌��؎���ǉ�����

		//���Ӓl�ɑ΂���z��͈͊O�Q�Ƃ����؂��邽�߂̌��؎���ǉ�����
		if(ARRAY_OFFSET_LIST_size(left_array_offset_list) > 0){
			createCheckUnboundAndUndefineOperationCheck(validate_statement_list, left_array_offset_list, array_unbound_check, undefined_control_check);
		}
		//�E�ӎ��ɑ΂���z��͈͊O�Q�Ƃ����؂��邽�߂̌��؎���ǉ�����
		if(ARRAY_OFFSET_LIST_size(right_array_offset_list) > 0){
			createCheckUnboundAndUndefineOperationCheck(validate_statement_list, right_array_offset_list, array_unbound_check, undefined_control_check);
		}


		//�[�����Z�̃t���O�������Ă����ꍇ�́A�[�����Z����я�]���Ȃ����ǂ������`�F�b�N���邽�߂̌��؎���ǉ�����
		if(zero_divition_check == 1){
			createZeroDivitionCheck(validate_statement_list, divition_information_list);
		}
		//�����Amemalloc_info�����炩���擾�����ꍇ�A���̓��e���J������
		if(memalloc_info != NULL){
			free(memalloc_info);
		}
		//memalloc_info�����݂����A�Ȃ������ӂɂȂ�炩�̃I�t�Z�b�g��񂪂���΁A�|�C���^���Z����̓��e�����ؗp�ϐ��ɔ��f���邽�߂̌��؎���ǉ�����
		else if(ARRAY_OFFSET_LIST_size(left_array_offset_list) > 0 && ARRAY_OFFSET_LIST_size(left_array_offset_list) > 0){
			getValidateStatementFromPointerOperator(validate_statement_list, left_array_offset_list, right_array_offset_list, right_expression, a_op_flag);
		}

		//�e�����̃|�C���^��z��̃I�t�Z�b�g�Ɋւ�����̃��X�g���폜����
		ARRAY_OFFSET_LIST_clear(left_array_offset_list);
		ARRAY_OFFSET_LIST_delete(left_array_offset_list);
		ARRAY_OFFSET_LIST_clear(right_array_offset_list);
		ARRAY_OFFSET_LIST_delete(right_array_offset_list);

		//���Z����я�]�Z�Ɋւ�����̃��X�g���폜����
		DIVITION_INFORMATION_LIST_clear(divition_information_list);
		DIVITION_INFORMATION_LIST_delete(divition_information_list);


	}
	//t_assignment_expression(�P��̎�)�������ꍇ
	else if(CSTLString_compare_with_char(root->name, "t_assignment_expression") == 0){
		//���Z����я�]�Ɋւ����񃊃X�g
		DIVITION_INFORMATION_LIST *divition_information_list = DIVITION_INFORMATION_LIST_new();

		//�P��̎�����A�I�t�Z�b�g���X�g���擾����
		ARRAY_OFFSET_LIST *array_offset_list = ARRAY_OFFSET_LIST_new();
		getARRAY_OFFSET_LIST(root, array_offset_list, function_information_list, vtlist, ignore_ast_list, target_expression);

		//������A���Z����я�]�Z�Ɋւ�������i�[������
		getDIVITION_INFORMATION_LIST(root, function_information_list, vtlist, divition_information_list, target_expression, ignore_ast_list);

		//�z��͈͊O�̃`�F�b�N�����Ă���ꍇ

		if(ARRAY_OFFSET_LIST_size(array_offset_list) > 0){
			createCheckUnboundAndUndefineOperationCheck(validate_statement_list, array_offset_list, array_unbound_check, undefined_control_check);
		}


		//�[�����Z�̃t���O�������Ă����ꍇ�́A�[�����Z����я�]���Ȃ����ǂ������`�F�b�N���邽�߂̌��؎���ǉ�����
		if(zero_divition_check == 1){
			createZeroDivitionCheck(validate_statement_list, divition_information_list);
		}

		//�C���N�������g��f�N�������g�ɑ΂��āA���؎����擾����B
		if(ARRAY_OFFSET_LIST_size(array_offset_list) > 0){
			createValidateStatemenFromIncDecExpr(validate_statement_list, array_offset_list);
		}
		ARRAY_OFFSET_LIST_clear(array_offset_list);
		ARRAY_OFFSET_LIST_delete(array_offset_list);

		//���Z����я�]�Z�Ɋւ�����̃��X�g���폜����
		DIVITION_INFORMATION_LIST_clear(divition_information_list);
		DIVITION_INFORMATION_LIST_delete(divition_information_list);
	}
	//call_function�������ꍇ
	else if(CSTLString_compare_with_char(root->name, "call_function") == 0){
		FREEMEMINFO *freememinfo = NULL;

		getFreememInfo(&freememinfo, root, function_information_list, vtlist, target_expression);

		//�����Afree����֌W�̏�񂪂�����A�o�͂���
		#ifdef DEBUG_MODE
			if(freememinfo != NULL){
				printFREEMEMINFO(freememinfo);
			}
		#endif
		//�����A����������֌W�̏�񂪎擾�ł����ꍇ
		if(freememinfo != NULL){
			//free_violation_flag���L���ł���ꍇ
			if(free_violation_check == 1){
				//����������֐�free�ŋ֎~�s�ׂ��s���Ă��Ȃ����ǂ����m�F���邽�߂̌��؎��𐶐�����
				createViolentFreeOperation(validate_statement_list, freememinfo);
			}
			//����������֌W�̏�񂩂猟�؎��𐶐�����
			createValidateStatementForFreeAction(validate_statement_list, freememinfo, validate_variable_list);

		}
	}

	//AST�̎q�m�[�h���Q�Ƃ�����
	for(ast_iterator = ASTList_begin(root->children);
		ast_iterator != ASTList_end(root->children);
		ast_iterator = ASTList_next(ast_iterator)){

		getValidateStatementFromAssignStatement( ASTList_data(ast_iterator), function_information_list, vtlist, validate_variable_list, validate_statement_list, ignore_ast_list
												, target_expression, undefined_control_check, zero_divition_check, array_unbound_check, free_violation_check);

	}
}

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
											AST *target_expression, int undefined_control_check, int zero_divition_check, int array_unbound_check){
	//AST�̎q�m�[�h���Q�Ƃ����邽�߂̃C�e���[�^
	ASTListIterator ast_iterator;
	int mode = 0;

	//��������������ꍇ
	if(CSTLString_compare_with_char(root->name, "init_declarator") == 0){

		//������̃t���O�ƕ�����
		int a_op_flag;

		CSTLString *a_op_string = CSTLString_new();

		//malloc�֌W�̏��
		MEMALLOC_INFO * memalloc_info = NULL;
		//�ϐ��̒�`�ɑ΂���m�[�h�ɂ�����e�����̃|�C���^��z��̃I�t�Z�b�g�Ɋւ�����̃��X�g
		ARRAY_OFFSET_LIST * declarator_array_offset_list = ARRAY_OFFSET_LIST_new();

		//�����̎��ɂ�����e�����̃|�C���^��z��̃I�t�Z�b�g�Ɋւ�����̃��X�g
		ARRAY_OFFSET_LIST * initializer_array_offset_list = ARRAY_OFFSET_LIST_new();

		AST *declarator_expression = getASTwithString(ASTList_data(ASTList_begin(root->children)), "IDENTIFIER", -1);

		AST *initializer_expression = ASTList_data(ASTList_next(ASTList_next(ASTList_begin(root->children))));

		//�ϐ��e�[�u������A�ϐ��̒�`�ɑ΂���m�[�h�ɊY���������T���A����ɑ΂���z��I�t�Z�b�g�����擾����B�i�q�m�[�h�̂P�Ԗڂ̎Q�Ɓj
		getDeclaratorArrayOffset(declarator_array_offset_list, declarator_expression, target_expression, vtlist);
		//�����̎��ɂ��ĒT��������i�q�m�[�h�̂R�Ԗڂ̎Q�Ɓj
		getRightAssignmentInfo(initializer_expression, function_information_list, vtlist, &memalloc_info, initializer_array_offset_list, ignore_ast_list, target_expression);

		//������Z�q���擾����
		getStringFromAST(a_op_string, ASTList_data(ASTList_next(ASTList_begin(root->children))));

		//����=�̏ꍇ
		if(CSTLString_compare_with_char(a_op_string, "=") == 0){
					a_op_flag = EQUAL;
		}
		//����ȊO�̏ꍇ�́A�G���[���o�͂��A�����I��������
		else{
			fprintf(stderr,"#%s#:%d:Don't Assignment Operator %s!!",
					getFileName(), ASTList_data(ASTList_next(ASTList_begin(root->children)))->line, CSTLString_c_str(a_op_string));
			exit(1);
		}
		CSTLString_delete(a_op_string);

		//DEBUG_MODE���L���Ȏ��������m�ۊ֌W�̏����o�͂���
		#ifdef DEBUG_MODE
			if(memalloc_info != NULL){
				printMEMALLOC_INFO(memalloc_info);
			}
		#endif

		//�����Amalloc_info���牽�炩�̏����擾�ł����ꍇ
		if(memalloc_info != NULL){
			//malloc_info��declarator_array_offset_list���猟�؎��𐶐�����
			createValidateStatementForMallocAction(validate_statement_list, memalloc_info, declarator_array_offset_list, validate_variable_list);

			//�֐��Ăяo����T���A���̎��̊֐�����malloc�܂���calloc�̏ꍇ��malloc�p���ʔԍ������邽�߂̕ϐ��𐶐�������
			AST *call_function = NULL;
			CSTLString *function_name = CSTLString_new();

			call_function = getASTwithString(initializer_expression, "call_function", -1);

			getStringFromAST(function_name, ASTList_data(ASTList_begin(call_function->children)));

			if(call_function != NULL && (CSTLString_compare_with_char(function_name, "malloc") == 0 ||
				CSTLString_compare_with_char(function_name, "calloc") == 0)){

				getValidateStatementFromMallocNumber(validate_statement_list, call_function, declarator_array_offset_list, memalloc_info);

			}
			CSTLString_delete(function_name);
		}


		//�����̎��ɑ΂���z��͈͊O�Q�Ƃ����؂��邽�߂̌��؎���ǉ�����
		if(ARRAY_OFFSET_LIST_size(initializer_array_offset_list) > 0){
			createCheckUnboundAndUndefineOperationCheck(validate_statement_list, initializer_array_offset_list, array_unbound_check, undefined_control_check);
		}


		//�����Amemalloc_info�����炩���擾�����ꍇ�A���̓��e���J������
		if(memalloc_info != NULL){
			free(memalloc_info);
		}

		//plus_minus_flag��0�ɂ���B
		//memalloc_info�����݂����A�Ȃ������ӂɂȂ�炩�̃I�t�Z�b�g��񂪂���΁A�|�C���^���Z����̓��e�����ؗp�ϐ��ɔ��f���邽�߂̌��؎���ǉ�����
		else if(ARRAY_OFFSET_LIST_size(declarator_array_offset_list) > 0 && ARRAY_OFFSET_LIST_size(initializer_array_offset_list) > 0){
			getValidateStatementFromPointerOperator(validate_statement_list, declarator_array_offset_list, initializer_array_offset_list, initializer_expression, a_op_flag);
		}

		//�e�����̃|�C���^��z��̃I�t�Z�b�g�Ɋւ�����̃��X�g���폜����
		ARRAY_OFFSET_LIST_clear(declarator_array_offset_list);
		ARRAY_OFFSET_LIST_delete(declarator_array_offset_list);
		ARRAY_OFFSET_LIST_clear(initializer_array_offset_list);
		ARRAY_OFFSET_LIST_delete(initializer_array_offset_list);


	}

	//AST�̎q�m�[�h���Q�Ƃ�����
	for(ast_iterator = ASTList_begin(root->children);
		ast_iterator != ASTList_end(root->children);
		ast_iterator = ASTList_next(ast_iterator)){

		getValidateStatementFromInitializer( ASTList_data(ast_iterator), function_information_list, vtlist, validate_variable_list, validate_statement_list, ignore_ast_list
												, target_expression, undefined_control_check, zero_divition_check, array_unbound_check);

	}
}

/**
malloc�p���ʔԍ���t�����邽�߂̊֐��ɕϊ����邽�߂̌��؎���ǉ�������B
@param validate_statement_list �ǉ���̌��؎����X�g
@param call_function �֐��Ăяo���ɑ΂���m�[�h
@param right_array_offset_list ���Ӓl�Ɋւ���z��I�t�Z�b�g���X�g
@param memalloc_info �������m�ۏ��

@return �Ȃ�
*/
void getValidateStatementFromMallocNumber(ValidateStatementList *validate_statement_list, AST *call_function, ARRAY_OFFSET_LIST* right_array_offset_list, MEMALLOC_INFO *memalloc_info){
	CSTLString *statement = CSTLString_new();
	CSTLString *variable = CSTLString_new();
	CSTLString *astalist = CSTLString_new();

	int offset_level_counter;

	ARRAY_OFFSET *array_offset = ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(right_array_offset_list));
	OFFSET_LISTIterator off_list_i;

	//�ϐ������擾����
	CSTLString_assign(variable, CSTLString_c_str(array_offset->variable_name));
	//�z��I�t�Z�b�g���X�g���猟�ؗp�ϐ��̔z�񎮂𐶐�����
	offset_level_counter = createValidateVariableArrayExpression(variable, array_offset);

	//�I�t�Z�b�g���x�����P�̏ꍇ�́A���x���P��p��malloc_number�֐��Ƃ��ċL�q����
	if(offset_level_counter == 1){
		CSTLString_printf(statement, 0, "malloc(sizeof(%s)*(%s)) ; malloc_flag_1_%s = malloc(sizeof(int)) ; *malloc_flag_1_%s = malloc_number ; malloc_number++ ", CSTLString_c_str(memalloc_info->sizeof_type), CSTLString_c_str(memalloc_info->size),
				CSTLString_c_str(variable), CSTLString_c_str(variable));
	}
	//�����łȂ��ꍇ�́A�W����malloc_number�֐��Ƃ��ċL�q����
	else{
		CSTLString_printf(statement, 0, "malloc(sizeof(%s)*(%s)) ; malloc_flag_%d_%s = malloc_number ; malloc_number++ ", CSTLString_c_str(memalloc_info->sizeof_type), CSTLString_c_str(memalloc_info->size),
		offset_level_counter, CSTLString_c_str(variable));
	}

	//���؎��̒ǉ�
	ValidateStatementList_push_back_ref(validate_statement_list,
		new_VALIDATE_STATEMENT(
			getNewValidateStatementID(validate_statement_list, call_function),
			MODIFY_VS,
			VALIDATE_NOTUSED,
			statement,
			call_function
		)
	);

	CSTLString_delete(astalist);
}

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
										int free_violation_check){
	//for���̖����̏����擾����
	ForInformation *target_for_information = ForInformationList_data(ForInformationList_rbegin(for_information_list));

	//for���̏������̏�񂩂�A���؎��𐶐�������
	getValidateStatementFromAssignStatement(target_for_information->init_expression, function_information_list, vtlist, validate_variable_list, validate_statement_list, ignore_ast_list,
											target_for_information->init_expression, undefined_control_check, zero_divition_check, array_unbound_check, free_violation_check);
	//for���̑������̏�񂩂�A���؎��𐶐�������
	getValidateStatementFromAssignStatement(target_for_information->inc_dec_expression, function_information_list, vtlist, validate_variable_list, validate_statement_list, ignore_ast_list,
											target_for_information->inc_dec_expression, undefined_control_check, zero_divition_check, array_unbound_check, free_violation_check);

}

/**
�|�C���^���Z����̓��e�����ؗp�ϐ��ɔ��f���邽�߂̌��؎���ǉ�����B

@param validate_statement_list ���؎����X�g
@param left_array_offset_list ���Ӓl�̔z��I�t�Z�b�g���X�g
@param right_array_offset_list �E�ӎ��̔z��I�t�Z�b�g���X�g
@param right_expression �E�ӎ��ւ̂`�r�s�A�h���X
@param a_op_flag ������Z�q�������������t���O 0:=,1:+=,2:-=,3:*=,4:/=,5:%=,6:<<=,7:>>=,8:&=,9:|=,10:^=
@return �Ȃ�
*/
void getValidateStatementFromPointerOperator(ValidateStatementList *validate_statement_list,ARRAY_OFFSET_LIST *left_array_offset_list,ARRAY_OFFSET_LIST *right_array_offset_list, AST *right_expression, int a_op_flag){
	//�A�h���X���Z��̊�{�I�Ȉʒu
	CSTLString *basis_location_out = CSTLString_new();
	CSTLString *left_variable_name = CSTLString_new();
	CSTLString *right_variable_name = CSTLString_new();

	//�z��I�t�Z�b�g�̓��e�ɑ΂���C�e���[�^
	OFFSET_LISTIterator off_list_i;
	//�ǉ����錟�؎��̓��e
	CSTLString *statement;

	int left_offset_level;
	int right_offset_level;

	int right_array_counter;

	int validate_statement_id;

	//�E�ӎ�����basis_location�����߂�
	getBasisLocationFromAssignmentExpression(basis_location_out, left_array_offset_list,
										  right_array_offset_list, right_expression, a_op_flag);
	#ifdef DEBUG_MODE
		printf("basis_location = \"%s\"\n",CSTLString_c_str(basis_location_out));
	#endif

	//basis_location���Ȃ�炩�̎����擾�ł����Ƃ�
	if(CSTLString_size(basis_location_out) > 0){
		//���ӎ�����A��ԓ��ł���|�C���^�̃I�t�Z�b�g�����߂�
		ARRAY_OFFSET *left_array_offset = ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(left_array_offset_list));
		//�E�Ӓl����A���Z��̃|�C���^���x�����ő�ł���ϐ��̃I�t�Z�b�g���ւ̃A�h���X�����߂�
		ARRAY_OFFSET *right_array_offset;
		//�����A�E�Ӓl����A���Z��̃|�C���^���x�����ő�l��0�łȂ��ꍇ
		if(maxOffsetLevelFromArrayOffsetList(right_array_offset_list) != 0){
			//�E�Ӓl����A���Z��̃|�C���^���x�����ő�ł���ϐ��̃I�t�Z�b�g���ւ̃A�h���X�����߂�
			right_array_offset = maxOffsetLevelAddressFromArrayOffsetList(right_array_offset_list);
		}
		//�����łȂ��ꍇ�ŁA������Z�q��+=��-=�����Ă���ꍇ
		else if(a_op_flag == PLUS_EQUAL || a_op_flag == MINUS_EQUAL){
			//���Ӓl�̔z��I�t�Z�b�g���X�g������
			right_array_offset = ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(left_array_offset_list));
		}
		//��L�O�̏ꍇ�̓G���[���o�͂��A�����I��������
		else{
			fprintf(stderr,"#%s#:%d:Invalid Pointer Operation!!\n", getFileName(),left_array_offset->target_statement->line);
			exit(1);
		}

		//���ӂ̕ϐ������擾����
		createArrayExpression(left_variable_name, left_array_offset, OFFSET_LIST_size(left_array_offset->offset_list));
		//�E�ӂ̕ϐ������擾����
		createArrayExpression(right_variable_name, right_array_offset, OFFSET_LIST_size(right_array_offset->offset_list));

		left_offset_level = OFFSET_LIST_size(left_array_offset->offset_list) + right_array_offset->anpasand_flag + 1;
		right_offset_level = OFFSET_LIST_size(right_array_offset->offset_list) - right_array_offset->anpasand_flag + 1;

		statement = CSTLString_new();
		//�E�Ӓl�ŁA�A�h���X���Z�q���܂߂��ꍇ�́A��ꃌ�x���Ɋւ��ẮA���̂悤�ɑ��������
		//�z��T�C�Y�F�P�A��{�ʒu�F�O�A�ÓI�ϐ�
		if(right_array_offset->anpasand_flag == 1){

			CSTLString_printf(statement, 1, "max_size_%d_%s = malloc(sizeof(int)); *max_size_%d_%s = 1; ", left_offset_level - 1, CSTLString_c_str(left_variable_name)
					, left_offset_level - 1, CSTLString_c_str(left_variable_name));
			CSTLString_printf(statement, 1, "basis_location_%d_%s = %s; ", left_offset_level - 1, CSTLString_c_str(left_variable_name), CSTLString_c_str(basis_location_out));
			CSTLString_printf(statement, 1, "defined_%d_%s = malloc(sizeof(int)); *defined_%d_%s = 1; ", left_offset_level - 1, CSTLString_c_str(left_variable_name),
					left_offset_level - 1, CSTLString_c_str(left_variable_name));
			CSTLString_printf(statement, 1, "malloc_flag_%d_%s = malloc(sizeof(int)); *malloc_flag_%d_%s = 0; ", left_offset_level - 1, CSTLString_c_str(left_variable_name)
					, left_offset_level - 1, CSTLString_c_str(left_variable_name));

			right_offset_level++;

			while(left_offset_level <= left_array_offset->pointer_level + left_array_offset->array_level){

				CSTLString_printf(statement, 1, "max_size_%d_%s = &max_size_%d_%s; ", left_offset_level, CSTLString_c_str(left_variable_name), right_offset_level, CSTLString_c_str(right_variable_name));
				CSTLString_printf(statement, 1, "basis_location_%d_%s = &basis_location_%d_%s; ", left_offset_level, CSTLString_c_str(left_variable_name), right_offset_level, CSTLString_c_str(right_variable_name));
				CSTLString_printf(statement, 1, "defined_%d_%s = &defined_%d_%s; ", left_offset_level, CSTLString_c_str(left_variable_name), right_offset_level, CSTLString_c_str(right_variable_name));
				CSTLString_printf(statement, 1, "malloc_flag_%d_%s = &malloc_flag_%d_%s; ", left_offset_level, CSTLString_c_str(left_variable_name), right_offset_level, CSTLString_c_str(right_variable_name));

				left_offset_level++;
				right_offset_level++;
			}
		}
		//�����łȂ��ꍇ
		else{
			//�����A���Ӓl�ƉE�Ӓl�����S��v�����ꍇ�́Abasis_location�݂̂�ύX������
			if(CSTLString_compare(left_variable_name, right_variable_name) == 0){
				CSTLString_printf(statement, 1, "basis_location_%d_%s = %s; ", left_offset_level, CSTLString_c_str(left_variable_name), CSTLString_c_str(basis_location_out));
			}else{
				CSTLString_printf(statement, 1, "max_size_%d_%s = max_size_%d_%s; ", left_offset_level, CSTLString_c_str(left_variable_name), right_offset_level, CSTLString_c_str(right_variable_name));
				CSTLString_printf(statement, 1, "basis_location_%d_%s = %s; ", left_offset_level, CSTLString_c_str(left_variable_name), CSTLString_c_str(basis_location_out));
				CSTLString_printf(statement, 1, "defined_%d_%s = defined_%d_%s; ", left_offset_level, CSTLString_c_str(left_variable_name), right_offset_level, CSTLString_c_str(right_variable_name));
				CSTLString_printf(statement, 1, "malloc_flag_%d_%s = malloc_flag_%d_%s; ", left_offset_level, CSTLString_c_str(left_variable_name), right_offset_level, CSTLString_c_str(right_variable_name));

				left_offset_level++;
				right_offset_level++;

				while(left_offset_level <= left_array_offset->pointer_level + left_array_offset->array_level){
					CSTLString_printf(statement, 1, "max_size_%d_%s = max_size_%d_%s; ", left_offset_level, CSTLString_c_str(left_variable_name), right_offset_level, CSTLString_c_str(right_variable_name));
					CSTLString_printf(statement, 1, "basis_location_%d_%s = basis_location_%d_%s; ", left_offset_level, CSTLString_c_str(left_variable_name), right_offset_level, CSTLString_c_str(right_variable_name));
					CSTLString_printf(statement, 1, "defined_%d_%s = defined_%d_%s; ", left_offset_level, CSTLString_c_str(left_variable_name), right_offset_level, CSTLString_c_str(right_variable_name));
					CSTLString_printf(statement, 1, "malloc_flag_%d_%s = malloc_flag_%d_%s; ", left_offset_level, CSTLString_c_str(left_variable_name), right_offset_level, CSTLString_c_str(right_variable_name));

					left_offset_level++;
					right_offset_level++;
				}
			}

		}

		//ID��t������
		validate_statement_id = getNewValidateStatementID(validate_statement_list, left_array_offset->target_statement);

		//���؎����X�g�ɒǉ�
		ValidateStatementList_push_back_ref(validate_statement_list, new_VALIDATE_STATEMENT( validate_statement_id, 1, VALIDATE_NOTUSED, statement, left_array_offset->target_statement));

	}
	//�A�h���X���Z��̊�{�I�Ȉʒu���폜����
	CSTLString_delete(basis_location_out);
}

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
		ARRAY_OFFSET_LIST *right_array_offset_list, FUNCTION_INFORMATION_LIST *function_information_list){
	CSTLString *function_name;

	CSTLString *call_function_statement;

	FUNCTION_INFORMATION *function_information;

	PARAM_INFORMATION_LISTIterator p_info_i;

	ARRAY_OFFSET *main_array_offset;

	CSTLString *basis_location_expr;

	CSTLString *array_content;

	CSTLString *astalisk;

	int arg_num;

	int level, out_level;

	int success_flag = FALSE;

	AST *argument;

	ASTListIterator ast_p;


	//�֐��ďo��T�����A�������ꍇ
	if(CSTLString_compare_with_char(root->name, "call_function") == 0){
		//�֐������擾����
		function_name = CSTLString_new();
		getStringFromAST(function_name, ASTLIST_ITERATOR_1(root));

		//�֐��Ăяo���ɑΉ�����֐���`�̏���ǂݏo��
		function_information = searchFUNCTION_INFORMATION(function_name, function_information_list);

		//�֐���`�̓ǂݏo���ɐ������A�W�����C�u�����֐��łȂ��ꍇ
		if(function_information != NULL && function_information->function_node != NULL){
			//�֐��ďo�Œu�������錟�؎�������������
			call_function_statement = CSTLString_new();

			//�����̊֐��ďo���擾���A�I��芇�ʂ��폜����
			getStringFromAST(call_function_statement, root);
			CSTLString_pop_back(call_function_statement);

			//����������ǂ݂���
			for(arg_num = 1 , p_info_i = PARAM_INFORMATION_LIST_begin(function_information->param_information_list);
				p_info_i != PARAM_INFORMATION_LIST_end(function_information->param_information_list);
				arg_num++, p_info_i = PARAM_INFORMATION_LIST_next(p_info_i)){
				//�֐���`�̏�񂩂�A�����̃|�C���^���x���Ɣz�񃌃x���̍��v���P�ȏ�̏ꍇ
				if(PARAM_INFORMATION_LIST_data(p_info_i)->array_level +
				   PARAM_INFORMATION_LIST_data(p_info_i)->pointer_level
						>= 1){
					//�����ւ�AST�m�[�h���擾���A���s�����ꍇ�T�����I��������
					argument = NULL;
					getArgumentAST(&argument,root,arg_num);
					if(argument == NULL){
						break;
					}

					//���؎��̐����ɐ��������t���O�𗧂Ă�
					success_flag = TRUE;

					//���̈����̃��C���ƂȂ�ϐ�����������o��
					if(right_array_offset_list != NULL){
						main_array_offset = searchOffsetLevelAddressFromArrayOffsetList(argument, right_array_offset_list,
								PARAM_INFORMATION_LIST_data(p_info_i)->pointer_level,
								PARAM_INFORMATION_LIST_data(p_info_i)->array_level);
					}else{
						main_array_offset = searchOffsetLevelAddressFromArrayOffsetList(argument, left_array_offset_list,
								PARAM_INFORMATION_LIST_data(p_info_i)->pointer_level,
								PARAM_INFORMATION_LIST_data(p_info_i)->array_level);
					}
					//���C���ƂȂ�����̎擾�ɐ��������ꍇ
					if(main_array_offset != NULL){

						level = PARAM_INFORMATION_LIST_data(p_info_i)->array_level +
								   PARAM_INFORMATION_LIST_data(p_info_i)->pointer_level;

						//�I�t�Z�b�g��񂩂�z�񎮂𐶐�����
						array_content = CSTLString_new();
						createValidateVariableArrayExpression(array_content, main_array_offset);

						//�A�h���X���Z�q������ł���ꍇ�́A�_�~�[�ϐ����֐��ďo�̌��؎��ɒǉ�����B
						if(main_array_offset->anpasand_flag == 1){
							CSTLString_printf(call_function_statement, 1, "&d_max_size, d_basis_location, &d_defined, &d_malloc_flag");
						}
						//�����łȂ��ꍇ
						else{

							//�����̎�����basis_location���𐶐�����
							basis_location_expr = CSTLString_new();
							getBasisLocationFromExpression(basis_location_expr, main_array_offset, argument);
							//���ؗp�ϐ���ǉ�����B
							CSTLString_printf(call_function_statement, 1, "max_size_%d_%s%s, %s, defined_%d_%s%s, malloc_flag_%d_%s%s",
									level, CSTLString_c_str(main_array_offset->variable_name), CSTLString_c_str(array_content),
									CSTLString_c_str(basis_location_expr),
									level, CSTLString_c_str(main_array_offset->variable_name), CSTLString_c_str(array_content),
									level, CSTLString_c_str(main_array_offset->variable_name), CSTLString_c_str(array_content));
						}
						astalisk = CSTLString_new();
						CSTLString_assign(astalisk, "*");
						//���x���Q�ȍ~�̌��ؗp�ϐ����֐��Ăяo���ɒǉ�����
						for(out_level = 2 ; out_level <= PARAM_INFORMATION_LIST_data(p_info_i)->array_level +
						   PARAM_INFORMATION_LIST_data(p_info_i)->pointer_level; out_level++){
							CSTLString_printf(call_function_statement, 1, ", %smax_size_%d_%s%s, %sbasis_location_%d_%s%s, %sdefined_%d_%s%s, %smalloc_flag_%d_%s%s",
									CSTLString_c_str(astalisk), level + out_level - 1, CSTLString_c_str(main_array_offset->variable_name), CSTLString_c_str(array_content),
									CSTLString_c_str(astalisk), level + out_level - 1, CSTLString_c_str(main_array_offset->variable_name), CSTLString_c_str(array_content),
									CSTLString_c_str(astalisk), level + out_level - 1, CSTLString_c_str(main_array_offset->variable_name), CSTLString_c_str(array_content),
									CSTLString_c_str(astalisk), level + out_level - 1, CSTLString_c_str(main_array_offset->variable_name), CSTLString_c_str(array_content));
						}


						CSTLString_delete(array_content);
					}
				}
			}
			//�I��肩�������p������
			CSTLString_printf(call_function_statement, 1, ")");

			//���؎������S�Ɋ����ł����ꍇ
			if(success_flag){
				//�u�������錟�؎������؎����X�g�ɒǉ�����
				ValidateStatementList_push_back_ref(validate_statement_list,
						new_VALIDATE_STATEMENT(
								getNewValidateStatementID(validate_statement_list, root),
								MODIFY_VS,
								VALIDATE_NOTUSED,
								call_function_statement,
								root)
							);
			}
			//�����łȂ���΁A���؎��̎����폜����
			else{
				CSTLString_delete(call_function_statement);
			}
		}
	}

	//�q�m�[�h�ɂ��Ă������������s��
	for(ast_p = ASTList_begin(root->children);
		ast_p != ASTList_end(root->children);
		ast_p = ASTList_next(ast_p)){
		getValidateStatementFromCallFunction(ASTList_data(ast_p), validate_statement_list,
				left_array_offset_list, right_array_offset_list, function_information_list);
	}
}

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
											  ARRAY_OFFSET_LIST *right_array_offset_list, AST *right_expression_ast, int a_op_flag){
	//���Ӓl�̃|�C���^���x��
	int left_pointer_level;

	int right_pointer_level;

	OFFSET_LISTIterator off_list_i;

	ARRAY_OFFSET *left_array_offset = ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(left_array_offset_list));

	int offset_level_counter;

	CSTLString *variable;

	//���Ӓl�̔z��I�t�Z�b�g���X�g�̍ŏ��ɑ΂���|�C���^���x�������߂�
	left_pointer_level = getOffsetLevelFromArrayOffset(left_array_offset);
	//���Ӓl�̃|�C���^���x�����P�ȏ�̏ꍇ�i���Ȃ킿�A�|�C���^���Z���̏ꍇ�j
	if(left_pointer_level >= 1){
			//�E�ӎ��S�̂̍ő�|�C���^���x�������߂�
			right_pointer_level = maxOffsetLevelFromArrayOffsetList(right_array_offset_list);

			//�E�ӎ��S�̂̍ő�|�C���^���x���ł���z��I�t�Z�b�g��NULL�ō��Ӓl�ƉE�ӎ��̃|�C���^���x�����������ꍇ
			if(left_pointer_level == right_pointer_level){
				//�E�ӎ��S�̂̍ő�|�C���^���x���ł���z��I�t�Z�b�g�ւ̃A�h���X
				ARRAY_OFFSET *right_pointer_array_offset = maxOffsetLevelAddressFromArrayOffsetList(right_array_offset_list);
				//�����A������Z�q��=�łȂ���΃G���[���o�͂��A�����I��������

				//�E�ӎ�����A�h���X�̊�{�I�Ȉʒu�̎������߂�B
				CSTLString_assign(output, "");
				getBasisLocationFromExpression(output, right_pointer_array_offset, right_expression_ast);

				//�����A&�t���O�������Ă��ĂȂ����A�z��I�t�Z�b�g�ɃI�t�Z�b�g�f�[�^�����݂���Ȃ�A�z��I�t�Z�b�g�̖����̃f�[�^��ǉ�����
				if(right_pointer_array_offset->anpasand_flag == 1 && OFFSET_LIST_size(right_pointer_array_offset->offset_list) != 0){
					CSTLString_printf(output, 1, " + ( %s )", *OFFSET_LIST_data(OFFSET_LIST_rbegin(right_pointer_array_offset->offset_list)));
				}
			}
			//�����A�E�ӎ��S�̂̍ő�|�C���^���x����0�ł���ꍇ
			else if(right_pointer_level == 0){
				//�����A������Z�q��+=�̏ꍇ
				if(a_op_flag == PLUS_EQUAL){


					//�E�ӎ����擾����
					CSTLString *right_expression = CSTLString_new();
					getStringFromAST(right_expression, right_expression_ast);

					variable = CSTLString_new();
					CSTLString_assign(variable, CSTLString_c_str(ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(left_array_offset_list))->variable_name));
					//�z��I�t�Z�b�g���X�g����z�񎮂𐶐����A�ǉ�����
					offset_level_counter = OFFSET_LIST_size(ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(left_array_offset_list))->offset_list);
					createArrayExpression(variable, ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(left_array_offset_list)), offset_level_counter);


					//���̌`���ő��������basis_location_���ӎ��̃I�t�Z�b�g���x��_���ӎ��̕ϐ���[�z��] + (�E�ӎ�)
					if(offset_level_counter == 1){

						CSTLString_printf(output, 0, "basis_location_1_%s + ( %s )",
							CSTLString_c_str(ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(left_array_offset_list))->variable_name),
									CSTLString_c_str(right_expression));

					}else{

						CSTLString_printf(output, 0, "basis_location_%d_%s + ( %s )",
								offset_level_counter, CSTLString_c_str(variable),
										CSTLString_c_str(right_expression));


					}


					CSTLString_delete(right_expression);
					CSTLString_delete(variable);

				}
				//�����A������Z�q��-=�̏ꍇ
				else if(a_op_flag == MINUS_EQUAL){

					//�E�ӎ����擾����
					CSTLString *right_expression = CSTLString_new();

					getStringFromAST(right_expression, right_expression_ast);

					variable = CSTLString_new();
					CSTLString_assign(variable, CSTLString_c_str(ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(left_array_offset_list))->variable_name));
					//�z��I�t�Z�b�g���X�g����@�\�𐶐�����
					offset_level_counter = OFFSET_LIST_size(ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(left_array_offset_list))->offset_list);
					createArrayExpression(variable, ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(left_array_offset_list)), offset_level_counter);


					//���̌`���ő��������basis_location_���ӎ��̃I�t�Z�b�g���x��_���ӎ��̕ϐ���[�z��] - (�E�ӎ�)
					if(offset_level_counter == 1){
						CSTLString_printf(output, 0, "basis_location_1_%s - ( %s )",
								CSTLString_c_str(ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(left_array_offset_list))->variable_name),
										CSTLString_c_str(right_expression));
					}else{
						CSTLString_printf(output, 0, "basis_location_%d_%s%s - ( %s )",
								offset_level_counter,CSTLString_c_str(variable) , CSTLString_c_str(right_expression));
					}


					CSTLString_delete(variable);
				}
				//��L�ȊO�̏ꍇ�́A�G���[���o�͂��A�����I��������B
				else{
					fprintf(stderr,"#%s#:%d:Invalid pointer operation!", getFileName(), right_expression_ast->line);
					exit(1);
				}
			}
			//��L�ȊO�̏ꍇ�́A�G���[���o�͂��A�����I��������B
			else{
				fprintf(stderr,"#%s#:%d:Invalid pointer operation!", getFileName(), right_expression_ast->line);
				exit(1);
			}
	}


}

/**
getBasisLocationFromExpression�̓�������
@param output �o�͐��CSTL������
@param array_offset �w�肵�����ʎq�̔z��I�t�Z�b�g
@param expression_ast �w�肵�����ւ�AST�A�h���X
*/
void getBasisLocationFromExpression_Internal(CSTLString *output, ARRAY_OFFSET *array_offset, AST *expression_ast){


	ASTListIterator ast_iterator;
	OFFSET_LISTIterator off_list_i;

	int counter;

	//�����A���ڎQ�Ƃ�z��Q�Ƃ܂��̓A�h���X�Q�Ƃ��������ꍇ
	if(CSTLString_compare_with_char(expression_ast->name, "direct_ref") == 0 ||
		CSTLString_compare_with_char(expression_ast->name, "array_access") == 0 ||
		CSTLString_compare_with_char(expression_ast->name, "address_ref") == 0){
			//�����Aarray_offset�̑ΏۂƂ��Ă���AST�A�h���X��������ꂽ�ꍇ
			if(findASTAddress(expression_ast, array_offset->variable_address) == 1){
				//�����A�|�C���^���x���������́A�z�񃌃x�����P�ȏ�̏ꍇ�́A���̕ϐ���basis_location������
				if(array_offset->pointer_level >= 1 || array_offset->array_level >= 1){

					CSTLString_printf(output, 1, "basis_location_%d_%s", 1 + OFFSET_LIST_size(array_offset->offset_list) - array_offset->anpasand_flag, CSTLString_c_str(array_offset->variable_name));

					for(counter = 0, off_list_i = OFFSET_LIST_begin(array_offset->offset_list);
						counter < OFFSET_LIST_size(array_offset->offset_list) - array_offset->anpasand_flag && off_list_i != OFFSET_LIST_end(array_offset->offset_list);
						counter++, off_list_i = OFFSET_LIST_next(off_list_i)){
						CSTLString_printf(output, 1, "[ %s ]", *OFFSET_LIST_data(off_list_i));
					}

					CSTLString_append(output, " ");
				}
				//�����łȂ��ꍇ�͂O�ɂ���
				else{
					CSTLString_append(output, "0 ");
				}
			}
			//�����łȂ���΁AAST�̎q�m�[�h���Q�Ƃ�����
			else{

				for(ast_iterator = ASTList_begin(expression_ast->children);
					ast_iterator != ASTList_end(expression_ast->children);
					ast_iterator = ASTList_next(ast_iterator)){

					getBasisLocationFromExpression_Internal( output, array_offset, ASTList_data(ast_iterator));

				}
			}
	}
	//�����A���ʎq�ł���ꍇ
	else if(CSTLString_compare_with_char(expression_ast->name, "IDENTIFIER") == 0){
		//�����A���̎��ʎq��AST�m�[�h���Aarray_offset�̑ΏۂƂ��Ă���AST�A�h���X�ł���Ȃ�A�����0�ɕς���
		if(expression_ast == array_offset->variable_address){
				//�����A�|�C���^���x���������́A�z�񃌃x�����P�ȏ�̏ꍇ�́A���̕ϐ���basis_location_1������
				if(array_offset->pointer_level >= 1 || array_offset->array_level >= 1){

					CSTLString_printf(output, 1, "basis_location_%d_%s", 1 + OFFSET_LIST_size(array_offset->offset_list) - array_offset->anpasand_flag, CSTLString_c_str(array_offset->variable_name));

					for(counter = 0, off_list_i = OFFSET_LIST_begin(array_offset->offset_list);
						counter < OFFSET_LIST_size(array_offset->offset_list) - array_offset->anpasand_flag && off_list_i != OFFSET_LIST_end(array_offset->offset_list);
						counter++, off_list_i = OFFSET_LIST_next(off_list_i)){
						CSTLString_printf(output, 1, "[ %s ]", *OFFSET_LIST_data(off_list_i));
					}

					CSTLString_append(output, " ");
				}else{
					CSTLString_append(output, "0 ");
				}
		}
		//�����łȂ���΁A���̕ϐ����̂��o�͂���
		else{
			CSTLString_append(output, CSTLString_c_str(expression_ast->content));
			CSTLString_append(output, " ");
		}
	}
	//���[�t�m�[�h�ł���ꍇ�͂��̂܂܏o�͂�����
	else if(ASTList_size(expression_ast->children) == 0){
		CSTLString_append(output, CSTLString_c_str(expression_ast->content));
		CSTLString_append(output, " ");
	}
	//��L�ȊO�̏ꍇ
	else{
		//AST�̎q�m�[�h���Q�Ƃ�����
		for(ast_iterator = ASTList_begin(expression_ast->children);
			ast_iterator != ASTList_end(expression_ast->children);
			ast_iterator = ASTList_next(ast_iterator)){

			getBasisLocationFromExpression_Internal( output, array_offset, ASTList_data(ast_iterator));

		}
	}
}

/**
�w�肵����expression_ast����A�|�C���^���Z�ɂ������{�I�Ȉʒu�̎��𕶎���Ƃ��ċ��߁Aoutput�ɓ����B���̂Ƃ��Aarray_offset���������炻��ɊY�����鎮���O�ɕϊ�����B
@param output �o�͐��CSTL������
@param array_offset �w�肵�����ʎq�̔z��I�t�Z�b�g
@param expression_ast �w�肵�����ւ�AST�A�h���X
@return �Ȃ�
*/
void getBasisLocationFromExpression(CSTLString *output, ARRAY_OFFSET *array_offset, AST *expression_ast){
	getBasisLocationFromExpression_Internal(output, array_offset, expression_ast);

	//������̖��������p�X�y�[�X�̂Ƃ��A������폜����
	if(CSTLString_size(output) > 0 && *CSTLString_at(output, CSTLString_size(output) - 1) == ' '){
		CSTLString_pop_back(output);
	}
}

/**
�������m�ۊ֌W�̏��memalloc_info��z���|�C���^�̃I�t�Z�b�g���array_offset_list���猟�؎��𐶐����Avalidate_statement_list�ɒǉ�����B

@param variable_statement_list ������̌��؎����X�g
@param memalloc_info �������m�ۊ֌W�̏��
@param array_offset_list �z���|�C���^�̃I�t�Z�b�g���
@param validate_variable_list ���ؗp�ϐ����X�g

@return �Ȃ�
*/
void createValidateStatementForMallocAction(ValidateStatementList *validate_statement_list, MEMALLOC_INFO *memalloc_info,
										ARRAY_OFFSET_LIST *array_offset_list,ValidateVariableList *validate_variable_list){

	//array_offset_list�̃f�[�^
	ARRAY_OFFSET *array_offset = ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(array_offset_list));
	//array_offset�̃I�t�Z�b�g���X�g�ŎQ�Ƃ���̂Ɏg�p����C�e���[�^
	OFFSET_LISTIterator off_list_i;
	//validate_variable�ɑ΂���C�e���[�^
	ValidateVariableListIterator validate_variable_iterator;
	//array_offset_list����I�t�Z�b�g�̐[�����擾����B
	int array_offset_depth = OFFSET_LIST_size(array_offset->offset_list);

	//�|�C���^���x��
	int pointer_level;

	int i;

	for(validate_variable_iterator = ValidateVariableList_begin(validate_variable_list);
		validate_variable_iterator != ValidateVariableList_end(validate_variable_list);
		validate_variable_iterator = ValidateVariableList_next(validate_variable_iterator)){

			//���ؗp�̃I�t�Z�b�g���x�����I�t�Z�b�g�̐[�����傫���ꍇ
			if(ValidateVariableList_data(validate_variable_iterator)->offset_level > array_offset_depth){
				//array_offset�̕ϐ����ƈ�v���錟�ؗp�ϐ��������A�Ȃ�����array_offset�̈ʒu���Ă��鎮�̍s�ԍ������ؗp�ϐ��̗L���͈͂ɓ����Ă���ꍇ
				if(CSTLString_compare(array_offset->variable_name, ValidateVariableList_data(validate_variable_iterator)->target_variable_name) == 0 &&
					ValidateVariableList_data(validate_variable_iterator)->enable_start <= array_offset->target_statement->line &&
					array_offset->target_statement->line <= ValidateVariableList_data(validate_variable_iterator)->enable_end
					) {
						//�ǉ����錟�؎��̃f�[�^
						ValidateStatement *new_validate_statement;

						//validate_statement_list�̎��ʔԍ�
						int validate_statement_list_id;

						int offset_level_counter;

						CSTLString *statement = CSTLString_new();

						CSTLString *variable = CSTLString_new();
						//���ؗp�ϐ������擾
						CSTLString_printf(variable, 0, "%s", CSTLString_c_str(ValidateVariableList_data(validate_variable_iterator)->variable_name));
						//�z��I�t�Z�b�g����z�񎮂𐶐����A�ǉ�����
						createValidateVariableArrayExpression(variable, array_offset);

						//���؎��̃I�t�Z�b�g���x�����A���ۂ̔z��̃I�t�Z�b�g���x���{�P�Ɠ������ꍇ�i���Ȃ킿�A���ӂ̒l�Ɠ����悤�ȃI�t�Z�b�g���x���Ɠ����ꍇ�j
						if(ValidateVariableList_data(validate_variable_iterator)->offset_level == array_offset_depth + 1){
							//����max_size�n�i���I�z��̐����������́j�̏ꍇ
							if(CSTLString_find(variable, "max_size_", 0) == 0){
								//�����A�I�t�Z�b�g���x�����Q�ȏ�̏ꍇ�́A�K�����I�ɕϐ����擾���Ă���l������
								if(ValidateVariableList_data(validate_variable_iterator)->offset_level >= 2){
									CSTLString_printf(statement, 1, "%s = malloc(sizeof(int)); ",CSTLString_c_str(variable));
								}
								CSTLString_printf(statement, 1,"*%s = %s;", CSTLString_c_str(variable), CSTLString_c_str(memalloc_info->size));

							}
							//����basis_location�n�i�z��̈ʒu���������́j�̏ꍇ
							else if(CSTLString_find(variable, "basis_location_", 0) == 0){

								CSTLString_printf(statement, 1,"%s = 0;",CSTLString_c_str(variable));

							}
							//����defined�n�i�|�C���^�����炩�̕ϐ��̃A�h���X��ݒ肵�Ă��邩���������́j�̏ꍇ
							else if(CSTLString_find(variable, "defined_", 0) == 0){
								//�����A�I�t�Z�b�g���x�����Q�ȏ�̏ꍇ�́A�K�����I�ɕϐ����擾���Ă���l������
								if(ValidateVariableList_data(validate_variable_iterator)->offset_level >= 2){
									CSTLString_printf(statement, 1, "%s = malloc(sizeof(int)); ",CSTLString_c_str(variable));
								}
								CSTLString_printf(statement, 1,"*%s = 1;", CSTLString_c_str(variable));

							}
							//����malloc_flag_�n�i�|�C���^�����I�Ɋ��蓖�Ă��Ă��邩���������́j�̏ꍇ
							else if(CSTLString_find(variable, "malloc_flag_", 0) == 0){
								//�����A�I�t�Z�b�g���x�����Q�ȏ�̏ꍇ�́A�K�����I�ɕϐ����擾���Ă���l������
								if(ValidateVariableList_data(validate_variable_iterator)->offset_level >= 2){
									CSTLString_printf(statement, 1, "%s = malloc(sizeof(int)); ",CSTLString_c_str(variable));
								}
								CSTLString_printf(statement, 1,"*%s = 1;", CSTLString_c_str(variable));


							}else{
								fprintf(stderr,"�s���Ȍ��؎��ł��B\n");
								exit(1);
							}
						}
						//�����łȂ��ꍇ
						else{
							//malloc�֐��Ō��؎��ɑ΂��ĐV�����̈���m�ۂ���B
							if(CSTLString_find(variable, "basis_location_", 0) != CSTL_NPOS){
								CSTLString_printf(statement, 1,"%s = malloc((%s)*sizeof(int", CSTLString_c_str(variable), CSTLString_c_str(memalloc_info->size));
							}else{
								CSTLString_printf(statement, 1,"%s = malloc((%s)*sizeof(int*", CSTLString_c_str(variable), CSTLString_c_str(memalloc_info->size));
							}
							//�|�C���^�L����ǉ�����B
							for(i = array_offset_depth + 2; i < ValidateVariableList_data(validate_variable_iterator)->offset_level;
								i++){
								CSTLString_printf(statement, 1,"*");
							}
							//�֐������
							CSTLString_printf(statement, 1,"));");
						}

						//validate_statement_list����V�������ʔԍ����擾����
						validate_statement_list_id = getNewValidateStatementID(validate_statement_list, array_offset->target_statement);
						//�ǉ����錟�؎��̐���
						new_validate_statement = new_VALIDATE_STATEMENT(validate_statement_list_id, 1, VALIDATE_NOTUSED, statement, array_offset->target_statement);
						ValidateStatementList_push_back_ref(validate_statement_list, new_validate_statement);

						CSTLString_delete(variable);

				}
			}
	}


}

/**
�w�肵���z��I�t�Z�b�g���X�garrya_offset_list����A�C���N�������g����уf�N�������g�����܂�ł�����A
����ɉ�����basis_location�ɔ��f�����邽�߂̌��؎��𐶐����Avalidate_statement_list�ɒǉ�����B

@param validate_statement_list �ǉ���̌��؎�
@param array_offset_list �z��I�t�Z�b�g���X�g

@return �Ȃ�

*/
void createValidateStatemenFromIncDecExpr(ValidateStatementList *validate_statement_list, ARRAY_OFFSET_LIST *array_offset_list){

	int validate_statement_list_id;
	ValidateStatement *new_validate_statement;

	//�z��I�t�Z�b�g���X�g����A�l�����
	ARRAY_OFFSET *target_array_offset = ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(array_offset_list));

	//���Z��̃I�t�Z�b�g���x�������߂�
	int pointer_level = getOffsetLevelFromArrayOffset(target_array_offset);

	//���Z��̃I�t�Z�b�g���x����1�ȏ�̏ꍇ�ŁA�C���N�������g����уf�N�������g�̂����ꂩ���o�R���Ă���ꍇ
	if(pointer_level >= 1 && target_array_offset->inc_dec_flag != NOT_INC_DEC){


		//����ɉ�����basis_location�ɔ��f�����邽�߂̌��؎��𐶐�������

		//�f�N�������g���ł���ꍇ
		if(target_array_offset->inc_dec_flag == VIA_DEC){
			CSTLString *statement = CSTLString_new();

			CSTLString_printf(statement, 0, "basis_location_%d_%s = basis_location_%d_%s - 1; ", pointer_level,
			 CSTLString_c_str(target_array_offset->variable_name), pointer_level, CSTLString_c_str(target_array_offset->variable_name));

			//validate_statement_list����V�������ʔԍ����擾����
			validate_statement_list_id = getNewValidateStatementID(validate_statement_list, target_array_offset->target_statement);
			//�ǉ����錟�؎��̐���
			new_validate_statement = new_VALIDATE_STATEMENT(validate_statement_list_id, 1, VALIDATE_NOTUSED, statement, target_array_offset->target_statement);
			ValidateStatementList_push_back_ref(validate_statement_list, new_validate_statement);

		}

		//�C���N�������g���ł���ꍇ
		else if(target_array_offset->inc_dec_flag == VIA_INC){
			CSTLString *statement = CSTLString_new();

			CSTLString_printf(statement, 0, "basis_location_%d_%s = basis_location_%d_%s + 1; ", pointer_level,
			 CSTLString_c_str(target_array_offset->variable_name), pointer_level, CSTLString_c_str(target_array_offset->variable_name));

			//validate_statement_list����V�������ʔԍ����擾����
			validate_statement_list_id = getNewValidateStatementID(validate_statement_list, target_array_offset->target_statement);
			//�ǉ����錟�؎��̐���
			new_validate_statement = new_VALIDATE_STATEMENT(validate_statement_list_id, 1, VALIDATE_NOTUSED, statement, target_array_offset->target_statement);
			ValidateStatementList_push_back_ref(validate_statement_list, new_validate_statement);

		}

		//����ȊO�̓G���[�Ƃ��ďo�͂������I��������
		else{
			fprintf(stderr, "Unexpect Inclement Declement Flag\n");
			exit(1);
		}

	}



}
/**
����������֌W�̏��freememinfo���猟�؎��𐶐����Avalidate_statement_list�ɒǉ�����B

@param variable_statement_list ������̌��؎����X�g
@param freememinfo �������m�ۊ֌W�̏��
@param validate_variable_list ���ؗp�ϐ����X�g

@return �Ȃ�
*/
void createValidateStatementForFreeAction(ValidateStatementList *validate_statement_list, FREEMEMINFO *freememinfo,
				ValidateVariableList *validate_variable_list){
	//freememinfo��free_variable�Ɋւ���z��I�t�Z�b�g
	ARRAY_OFFSET *array_offset = ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(freememinfo->free_variable));
	//array_offset�̃I�t�Z�b�g���X�g�ŎQ�Ƃ���̂Ɏg�p����C�e���[�^
	OFFSET_LISTIterator off_list_i;
	//validate_variable�ɑ΂���C�e���[�^
	ValidateVariableListIterator validate_variable_iterator;
	//array_offset_list����I�t�Z�b�g�̐[�����擾����B
	int array_offset_depth = OFFSET_LIST_size(array_offset->offset_list);

	//�|�C���^���x��
	int pointer_level;

	int i;

	for(validate_variable_iterator = ValidateVariableList_begin(validate_variable_list);
		validate_variable_iterator != ValidateVariableList_end(validate_variable_list);
		validate_variable_iterator = ValidateVariableList_next(validate_variable_iterator)){

			//���ؗp�̃I�t�Z�b�g���x�����I�t�Z�b�g�̐[�����傫���ꍇ
			if(ValidateVariableList_data(validate_variable_iterator)->offset_level > array_offset_depth){
				//array_offset�̕ϐ����ƈ�v���錟�ؗp�ϐ��������A�Ȃ�����array_offset�̈ʒu���Ă��鎮�̍s�ԍ������ؗp�ϐ��̗L���͈͂ɓ����Ă���ꍇ
				if(CSTLString_compare(array_offset->variable_name, ValidateVariableList_data(validate_variable_iterator)->target_variable_name) == 0 &&
					ValidateVariableList_data(validate_variable_iterator)->enable_start <= array_offset->target_statement->line &&
					array_offset->target_statement->line <= ValidateVariableList_data(validate_variable_iterator)->enable_end){
						//�ǉ����錟�؎��̃f�[�^
						ValidateStatement *new_validate_statement;

						//validate_statement_list�̎��ʔԍ�
						int validate_statement_list_id;
						CSTLString *free_target_variable_name = CSTLString_new();
						CSTLString *statement = CSTLString_new();
						//���ؗp�ϐ������擾
						CSTLString_printf(free_target_variable_name, 0, "%s", CSTLString_c_str(ValidateVariableList_data(validate_variable_iterator)->variable_name));
						//�|�C���^�Ɣz��̋L�����폜����
						deletePointerAndArraySynbol(free_target_variable_name);
						//�I�t�Z�b�g����z��Ƃ��Ēǉ��}������
						for(off_list_i = OFFSET_LIST_begin(array_offset->offset_list);
							off_list_i != OFFSET_LIST_end(array_offset->offset_list);
							off_list_i = OFFSET_LIST_next(off_list_i)){
							CSTLString_printf(free_target_variable_name, 1, "[ %s ]", *OFFSET_LIST_data(off_list_i));
						}
						//���؎��̃I�t�Z�b�g���x�����A���ۂ̔z��̃I�t�Z�b�g���x���{�P�Ɠ������ꍇ�i���Ȃ킿�A���ӂ̒l�Ɠ����悤�ȃI�t�Z�b�g���x���Ɠ����ꍇ�j
						if(ValidateVariableList_data(validate_variable_iterator)->offset_level == array_offset_depth + 1){
							//����max_size�n�i���I�z��̐����������́j�̏ꍇ
							if(CSTLString_find(free_target_variable_name, "max_size_", 0)  == 0){
								CSTLString_printf(statement, 0,"*%s = 0; ", CSTLString_c_str(free_target_variable_name));


							}
							//����basis_location�n�i�z��̈ʒu���������́j�̏ꍇ
							else if(CSTLString_find(free_target_variable_name, "basis_location_", 0)  == 0){

								CSTLString_printf(statement, 0,"%s = 0; ", CSTLString_c_str(free_target_variable_name));

							}
							//����defined�n�i�|�C���^�����炩�̕ϐ��̃A�h���X��ݒ肵�Ă��邩���������́j�̏ꍇ
							else if(CSTLString_find(free_target_variable_name, "defined_", 0)  == 0){
								//�����A���ؗp�ϐ��̃I�t�Z�b�g���x�����P�̂Ƃ��́A���ڎQ�Ɖ��Z�q��t����
								CSTLString_printf(statement, 0,"*%s = 0; ", CSTLString_c_str(free_target_variable_name));


							}
							//����malloc_flag_�n�i�|�C���^�����I�Ɋ��蓖�Ă��Ă��邩���������́j�̏ꍇ
							else if(CSTLString_find(free_target_variable_name, "malloc_flag_", 0) == 0){
								//�����A���ؗp�ϐ��̃I�t�Z�b�g���x�����P�̂Ƃ��́A���ڎQ�Ɖ��Z�q��t����
								CSTLString_printf(statement, 0,"*%s = 0; ", CSTLString_c_str(free_target_variable_name));


							}else{
								fprintf(stderr,"�s���Ȍ��؎��ł��B\n");
								exit(1);
							}
						}

						//validate_statement_list����V�������ʔԍ����擾����
						validate_statement_list_id = getNewValidateStatementID(validate_statement_list, array_offset->target_statement);
						//�ǉ����錟�؎��̐���
						new_validate_statement = new_VALIDATE_STATEMENT(validate_statement_list_id, 1, VALIDATE_NOTUSED, statement, array_offset->target_statement);
						ValidateStatementList_push_back_ref(validate_statement_list, new_validate_statement);

				}
			}
	}
}

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
					,FUNCTION_INFORMATION_LIST *function_information_list){
	VARIABLE_TABLE_LISTIterator vtlist_i;

	int max_array_offset = 0, tmp_offset_size;

	int iterator;

	char variable_name[STRLEN];

	int validate_statement_id;

	CSTLString *global_v_name;

	CSTLString *main_function;

	CSTLString *call_initialize;

	FUNCTION_INFORMATION *main_function_information;

	AST * target_ast;

	for(vtlist_i = VARIABLE_TABLE_LIST_begin(variable_table_list);
		vtlist_i != VARIABLE_TABLE_LIST_end(variable_table_list);
		vtlist_i = VARIABLE_TABLE_LIST_next(vtlist_i)){
			OFFSET_LIST *offset_list = OFFSET_LIST_new();

			//�ϐ����X�g����z��̃I�t�Z�b�g���X�g���擾����
			getOFFSET_LISTFromVariableTable(offset_list, VARIABLE_TABLE_LIST_data(vtlist_i));

			//�ϐ����X�g���̍ő吔�̔z��̃I�t�Z�b�g�������߂�
			tmp_offset_size = OFFSET_LIST_size(offset_list);
			if(max_array_offset < tmp_offset_size){
				max_array_offset = tmp_offset_size;
			}

			if(tmp_offset_size > 0){
				//�z��̃I�t�Z�b�g���X�g�����ƂɌ��؎��𐶐�����
				CSTLString *output = CSTLString_new();

				//�O���[�o���ϐ��̏ꍇ�͂��̌��؎����֐�������B
				if(VARIABLE_TABLE_LIST_data(vtlist_i)->declaration_location_address->block_level == 0){
					global_v_name = CSTLString_new();
					CSTLString_assign(global_v_name, CSTLString_c_str(VARIABLE_TABLE_LIST_data(vtlist_i)->variable_name));
					deletePointerAndArraySynbol(global_v_name);

					CSTLString_printf(output, 1, "void initializer_%s(void) {", CSTLString_c_str(global_v_name));

				}
				ArrayOffsetToValidateStatement(output, validate_variable_list, VARIABLE_TABLE_LIST_data(vtlist_i), offset_list);
				//�O���[�o���ϐ��̏ꍇ�͂��̌��؎����֐�������B
				if(VARIABLE_TABLE_LIST_data(vtlist_i)->declaration_location_address->block_level == 0){
					CSTLString_printf(output, 1, "}");

					//�֐����X�g����Amain�֐����擾����B
					main_function = CSTLString_new();
					CSTLString_assign(main_function, "main");
					main_function_information = searchFUNCTION_INFORMATION(main_function,function_information_list);

					//main�֐��̃u���b�N���ɂ��̏������֐��Ăяo����ǉ�����B
					if(main_function_information != NULL){
						//main�֐��ɂ��̃O���[�o���ϐ��̏���������ǉ�����B
						call_initialize = CSTLString_new();
						CSTLString_printf(call_initialize, 0, "initializer_%s (); ", CSTLString_c_str(global_v_name));

						//�֐���`�̃m�[�h����A�u���b�N�̎n�܂�ւ�AST�m�[�h���擾����B
						if(CSTLString_compare_with_char(main_function_information->function_node->name, "function_definition_type_a") == 0){
							target_ast = ASTLIST_ITERATOR_1(ASTLIST_ITERATOR_4(main_function_information->function_node));
						}else if(CSTLString_compare_with_char(main_function_information->function_node->name, "function_definition_type_b") == 0){
							target_ast = ASTLIST_ITERATOR_1(ASTLIST_ITERATOR_3(main_function_information->function_node));
						}else{
							fprintf(stderr, "�s���ȃm�[�h:%s", CSTLString_c_str(main_function_information->function_node->name));
							exit(1);
						}


						ValidateStatementList_push_back_ref(validate_statement_list, new_VALIDATE_STATEMENT( getNewValidateStatementID(validate_statement_list, target_ast), MODIFY_VS, VALIDATE_NOTUSED, call_initialize , target_ast));
					}

					CSTLString_delete(global_v_name);

				}

				//ID��t������
				validate_statement_id = getNewValidateStatementID(validate_statement_list, VARIABLE_TABLE_LIST_data(vtlist_i)->declaration_location_address);

				//���؎����X�g�ɒǉ�
				ValidateStatementList_push_back_ref(validate_statement_list, new_VALIDATE_STATEMENT( validate_statement_id, 1, VALIDATE_NOTUSED, output, VARIABLE_TABLE_LIST_data(vtlist_i)->declaration_location_address));


			}

			//�I�t�Z�b�g���X�g�����O����
			deleteOFFSET_LIST(offset_list);
		}


	//���ؗp�ϐ����X�gvalidate_variable_list�ɁA�z��̃I�t�Z�b�g�𐶐�����̂Ɏg�p����ϐ�vviterator_2�`vviterator_n�in�͔z��̍ő原�����j�𐶐����A�ǉ�����B
	for( iterator = 2; iterator <= max_array_offset; iterator++){
				//�z��̃I�t�Z�b�g�𐶐�����̂Ɏg�p���錟�ؗp�̕ϐ��𐶐�����
				sprintf(variable_name, "vviterator_%d", iterator);

				ValidateVariableList_push_back_ref( validate_variable_list,

					new_VALIDATE_VARIABLE_with_char(VALIDATE_NOTUSED,
													1,
													INT_MAX,
													1,
													0,
													0,
													"int",
													variable_name,
													"null",
													1
					)
					);

	}
}

/**
�ϐ���`���X�g�Ń|�C���^�ϐ��ɑ΂��錟�ؗp�ϐ����X�V���邽�߂̌��؎����쐬���Avalidate_statement_list�ɒǉ�����B
@param validate_statement_list �ǉ���̌��؎�
@param variable_table_list �ϐ��e�[�u�����X�g
@param function_information_list �֐���`�Ɋւ����񃊃X�g

@return �Ȃ�
*/
void createVaridateStatementFromPointerDefine( ValidateStatementList *validate_statement_list, VARIABLE_TABLE_LIST *variable_table_list, FUNCTION_INFORMATION_LIST *function_information_list){
	int array_level, pointer_level;

	VARIABLE_TABLE_LISTIterator vtlist_i;

	CSTLString *variable_name = CSTLString_new();
	CSTLString *statement;

	int validate_statement_id;

	FUNCTION_INFORMATION *main_function_information;
	CSTLString *main_function;
	CSTLString *call_initialize;
	AST *target_ast;


	for(vtlist_i = VARIABLE_TABLE_LIST_begin(variable_table_list);
		vtlist_i != VARIABLE_TABLE_LIST_end(variable_table_list);
		vtlist_i = VARIABLE_TABLE_LIST_next(vtlist_i)){

		//�|�C���^���x������єz�񃌃x�����擾����
		getPointerLevelAndArrayLevelFromVARIABLE_TABLE(VARIABLE_TABLE_LIST_data(vtlist_i), &pointer_level, &array_level);

		//�����A�|�C���^���x�����P�ȏ�ŁA���z�񃌃x����0�ł���ꍇ
		if(pointer_level >= 1 && array_level == 0){
			//�|�C���^��z��L�����폜���邷�邱�ƂŁA�ϐ������擾����
			CSTLString_assign(variable_name, CSTLString_c_str(VARIABLE_TABLE_LIST_data(vtlist_i)->variable_name));
			deletePointerAndArraySynbol(variable_name);

			statement = CSTLString_new();

			//�|�C���^�̑��w�ڂ�max_size�Ebasis_location�Edefined�Emalloc_flag�ɑ΂��鎮�𐶐�����
			//�O���[�o���ϐ��̏ꍇ�́A�֐�������B
			if(VARIABLE_TABLE_LIST_data(vtlist_i)->declaration_location_address->block_level == 0){
				CSTLString_printf(statement, 1, "void initializer_%s(void) {", CSTLString_c_str(variable_name));
			}
			//���w�ڂ�max_size�̒l��0�ɂ���B
			CSTLString_printf(statement, 1, "max_size_1_%s = malloc(sizeof(int)); *max_size_1_%s = 0;", CSTLString_c_str(variable_name), CSTLString_c_str(variable_name));
			//���w�ڂ�basis_location��0�ɂ���B
			CSTLString_printf(statement, 1, "basis_location_1_%s = 0; ", CSTLString_c_str(variable_name));
			//���w�ڂ�defined�̒l��0�ɂ���B
			CSTLString_printf(statement, 1, "defined_1_%s = malloc(sizeof(int));  *defined_1_%s = 0;", CSTLString_c_str(variable_name), CSTLString_c_str(variable_name));
			//���w�ڂ�malloc_flag�̒l��0�ɂ���B
			CSTLString_printf(statement, 1, "malloc_flag_1_%s = malloc(sizeof(int)); *malloc_flag_1_%s = 0;", CSTLString_c_str(variable_name), CSTLString_c_str(variable_name));

			if(VARIABLE_TABLE_LIST_data(vtlist_i)->declaration_location_address->block_level == 0){
				CSTLString_printf(statement, 1, "}", CSTLString_c_str(variable_name));
				//�O���[�o���ϐ��̏ꍇ�͂��̌��؎����֐�������B
				if(VARIABLE_TABLE_LIST_data(vtlist_i)->declaration_location_address->block_level == 0){
					CSTLString_printf(statement, 1, "}");

					//�֐����X�g����Amain�֐����擾����B
					main_function = CSTLString_new();
					CSTLString_assign(main_function, "main");
					main_function_information = searchFUNCTION_INFORMATION(main_function,function_information_list);

					//main�֐��̃u���b�N���ɂ��̏������֐��Ăяo����ǉ�����B
					if(main_function_information != NULL){
						//main�֐��ɂ��̃O���[�o���ϐ��̏���������ǉ�����B
						call_initialize = CSTLString_new();
						CSTLString_printf(call_initialize, 0, "initializer_%s (); ", CSTLString_c_str(variable_name));

						//�֐���`�̃m�[�h����A�u���b�N�̎n�܂�ւ�AST�m�[�h���擾����B
						if(CSTLString_compare_with_char(main_function_information->function_node->name, "function_definition_type_a") == 0){
							target_ast = ASTLIST_ITERATOR_1(ASTLIST_ITERATOR_4(main_function_information->function_node));
						}else if(CSTLString_compare_with_char(main_function_information->function_node->name, "function_definition_type_b") == 0){
							target_ast = ASTLIST_ITERATOR_1(ASTLIST_ITERATOR_3(main_function_information->function_node));
						}else{
							fprintf(stderr, "�s���ȃm�[�h:%s", CSTLString_c_str(main_function_information->function_node->name));
							exit(1);
						}


						ValidateStatementList_push_back_ref(validate_statement_list, new_VALIDATE_STATEMENT( getNewValidateStatementID(validate_statement_list, target_ast), MODIFY_VS, VALIDATE_NOTUSED, call_initialize , target_ast));
					}

				}
			}

			//ID��t������
			validate_statement_id = getNewValidateStatementID(validate_statement_list, VARIABLE_TABLE_LIST_data(vtlist_i)->declaration_location_address);

			//���؎����X�g�ɒǉ�
			ValidateStatementList_push_back_ref(validate_statement_list, new_VALIDATE_STATEMENT( validate_statement_id, 1, VALIDATE_NOTUSED, statement, VARIABLE_TABLE_LIST_data(vtlist_i)->declaration_location_address));

		}

	}

	CSTLString_delete(variable_name);

}

/**
�z���|�C���^�Ȃǂ̃I�t�Z�b�g���̃��X�garray_offset_list����A�z��͈̔͊O�Q�Ƃ̃`�F�b�N�����邽�߂̌��؎�
��A����`��Ԃŏ������`�F�b�N���邽�߂̌��؎��𐶐����Avalidate_statement_list�֒ǉ�����B

@param validate_statement_list �ǉ���̌��؎����X�g
@param array_offset_list �z���|�C���^�Ȃǂ̃I�t�Z�b�g���̃��X�g
@param array_unbound_check �z�񂪔͈͊O���Q�Ƃ��Ă��Ȃ����ǂ��������؂��邽�߂̎��𐶐����邩�ǂ����@�P�F��������@�O�F�������Ȃ�
@param undefined_control_check ����`�ȏ������s���Ă��Ȃ����ǂ��������؂��邽�߂̎��𐶐����邩�ǂ��� �P�F�������� �O�F�������Ȃ�
@return �Ȃ�
*/
void createCheckUnboundAndUndefineOperationCheck(ValidateStatementList *validate_statement_list, ARRAY_OFFSET_LIST *array_offset_list, int array_unbound_check, int undefined_control_check){
	ARRAY_OFFSET_LISTIterator aoff_list_i;

	int array_offset_level;

	int offset_level_counter;

	OFFSET_LISTIterator off_list_i;

	if(array_unbound_check || undefined_control_check){

		//array_offset_list�̏��́A�Ō�̂ق��ɍŉ��ʃ��x���̃|�C���^����єz��Q�Ƃ�����̂ŁA��������T������
		for(aoff_list_i = ARRAY_OFFSET_LIST_rbegin(array_offset_list);
			aoff_list_i != ARRAY_OFFSET_LIST_rend(array_offset_list);
			aoff_list_i = ARRAY_OFFSET_LIST_prev(aoff_list_i)){

				//�I�t�Z�b�g���x���̎擾
				array_offset_level = OFFSET_LIST_size(ARRAY_OFFSET_LIST_data(aoff_list_i)->offset_list);

				//�I�t�Z�b�g���x����0�𒴂���ꍇ�i���Ȃ킿�A�I�t�Z�b�g��񂪑��݂���ꍇ�j
				if(array_offset_level > 0){

					//�z��̌`��ێ�������i�������Ŏg�p�����j
					CSTLString *array_string = CSTLString_new();
					CSTLString *basis_location_content = CSTLString_new();
					CSTLString_assign(array_string, "");
					CSTLString_assign(basis_location_content, "");

					//�I�t�Z�b�g�����Q�Ƃ���
					for(offset_level_counter = 1, off_list_i = OFFSET_LIST_begin(ARRAY_OFFSET_LIST_data(aoff_list_i)->offset_list);
						off_list_i != OFFSET_LIST_end(ARRAY_OFFSET_LIST_data(aoff_list_i)->offset_list);
						offset_level_counter++, off_list_i = OFFSET_LIST_next(off_list_i)){
							int is_expression_flag = isExpression(*OFFSET_LIST_data(off_list_i));
							//���؎������镶������
							CSTLString *statement = CSTLString_new();

							//����`�����`�F�b�N�t���O�����藧���Ă���ꍇ�A
							//���x�����Ƃ̖���`�����̌��؎��𐶐�����B����`�����̌��؎��̌`���͈ȉ��̒ʂ�ł���B
							//if(defined_�K�w_�ϐ��� == 0 && max_size_�K�w_�ϐ��� == 0){
							//	printf("#�t�@�C����#:�s��: detected undefine pointer access in variable �ϐ���);
							//	assert(0);
							//	���^�[����;
							//}
							if(undefined_control_check){

								CSTLString_printf(statement,0,"if(*defined_%d_%s%s == 0 && *malloc_flag_%d_%s%s == 0){",
											 offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string),
											 offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string)
										);

								CSTLString_printf(statement,1,"printf(\"#%s#:%d: detected undefine pointer access in variable %s\"); ",getFileName(), ARRAY_OFFSET_LIST_data(aoff_list_i)->target_statement->line, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name));

								CSTLString_printf(statement, 1, "assert(0);");

								//���^�[�����߂̕ԋp�^�ɉ�����ύX(�����Avoid�^�ł���΁A�ureturn;�v�ɂ���)
								if(CSTLString_compare_with_char(ARRAY_OFFSET_LIST_data(aoff_list_i)->target_statement->return_type, "void") == 0){
									CSTLString_printf(statement, 1, "return; ");
								}else{
									CSTLString_printf(statement, 1, "return 1; ");
								}

								CSTLString_printf(statement, 1, "} ");

							}

							//�z��͈͊O�`�F�b�N�t���O�����藧���Ă����ꍇ�A
							//���x�����Ƃ̔z��͈͊O�Q�Ƃ̌��؎��𐶐�����B�z��͈͊O�Q�Ƃ̎��̌`���͈ȉ��̒ʂ�ł���
							//if(0 > �� + ��{�ʒu || �� + ��{�ʒu < �Ώەϐ��̔z��){
							//	printf("#�t�@�C����#:�s��: detected unbound access in variable �ϐ��� basis_location = %d �� = %d\n", basis_location, ��);
							//	assert(0);
							//	���^�[����;
							//}
							if(array_unbound_check){
									CSTLString_printf(statement,1,"if(0 > %s + basis_location_%d_%s%s || %s + basis_location_%d_%s%s >= *max_size_%d_%s%s){",
												 *OFFSET_LIST_data(off_list_i), offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string),
												 *OFFSET_LIST_data(off_list_i), offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string),
												 offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string));

								CSTLString_printf(statement,1,"printf(\"#%s#:%d:detected unbound access in variable %s ",getFileName(), ARRAY_OFFSET_LIST_data(aoff_list_i)->target_statement->line, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name));

								//basis_location�̓��e���o�͂���
								CSTLString_printf(statement,1," basis_location = %%d ");

								//�����A�I�t�Z�b�g�̓��e�����ł���΁A�����l�Ƃ����`�ŏo�͂���
								if(is_expression_flag == 1){
									CSTLString_printf(statement,1,"(%s = %%d)\\n\"", *OFFSET_LIST_data(off_list_i));
									//basis_location�̓��e���܂߂������̓��e������
									CSTLString_printf(statement,1,", basis_location_%d_%s%s, %s",offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string) , *OFFSET_LIST_data(off_list_i));
								}

								//�����łȂ���΁A�l�Ƃ����`�ŏo�͂���
								else{
									CSTLString_printf(statement,1,"(%s)\\n\"", *OFFSET_LIST_data(off_list_i));
									//basis_location�̓��e�̈����̓��e������
									CSTLString_printf(statement,1,", basis_location_%d_%s%s", offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string));
								}
								CSTLString_printf(statement, 1, "); ");

								CSTLString_printf(statement, 1, "assert(0);");

								//���^�[�����߂̕ԋp�^�ɉ�����ύX(�����Avoid�^�ł���΁A�ureturn;�v�ɂ���)
								if(CSTLString_compare_with_char(ARRAY_OFFSET_LIST_data(aoff_list_i)->target_statement->return_type, "void") == 0){
									CSTLString_printf(statement, 1, "return; ");
								}else{
									CSTLString_printf(statement, 1, "return 1; ");
								}

								CSTLString_printf(statement, 1, "}");
							}
							//���؎��̒ǉ�
							ValidateStatementList_push_back_ref(validate_statement_list,
								new_VALIDATE_STATEMENT(
									getNewValidateStatementID(validate_statement_list, ARRAY_OFFSET_LIST_data(aoff_list_i)->target_statement),
									0,
									VALIDATE_NOTUSED,
									statement,
									ARRAY_OFFSET_LIST_data(aoff_list_i)->target_statement
								)
							);

							//���̃��x���̂��߂̔z��𐶐�����B
							CSTLString_printf(basis_location_content, 0, "basis_location_%d_%s%s", offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string));
							CSTLString_printf(array_string, 1," [ %s + %s ]", *OFFSET_LIST_data(off_list_i), (char*)CSTLString_c_str(basis_location_content));


					}

					CSTLString_delete(array_string);
					CSTLString_delete(basis_location_content);

				}


			}
		}


}

/**
ArrayOffsetToVaridateStatement�̓�������
@param output �o�͂��錟�؎�
@param validate_variable_list ���ؗp�ϐ����X�g
@param varia�Ȃ�ble_table �Ώۂ̕ϐ��f�[�^
@param offset_list �I�t�Z�b�g���X�g
@param offset_level ���Q�Ƃ��Ă���I�t�Z�b�g���x��

@return �Ȃ�
*/
void ArrayOffsetToVaridateStatement_Internal(CSTLString* output, ValidateVariableList *validate_variable_list, VARIABLE_TABLE *variable_table, OFFSET_LIST *offset_list, int *offset_level){
	ValidateVariableListIterator vvlist_i;
	OFFSET_LISTIterator off_list_i;
	int iterator;
	if(*offset_level <= OFFSET_LIST_size(offset_list)){

		//�I�t�Z�b�g���̎擾
		char *offset_info;
		for(iterator = 1, off_list_i = OFFSET_LIST_begin(offset_list);
			iterator < *offset_level && off_list_i != OFFSET_LIST_end(offset_list);
			iterator++, off_list_i = OFFSET_LIST_next(off_list_i));

		offset_info = *OFFSET_LIST_data(off_list_i);

		if(*offset_level > 1){
			CSTLString_printf( output, 1, "for(vviterator_%d = 0; vviterator_%d < %s; vviterator_%d++){ ", *offset_level, *offset_level, offset_info, *offset_level);
		}

		for(vvlist_i = ValidateVariableList_begin(validate_variable_list);
			vvlist_i != ValidateVariableList_end(validate_variable_list);
			vvlist_i = ValidateVariableList_next(vvlist_i)){
				//���ؗp�̃I�t�Z�b�g���x�����I�t�Z�b�g�̐[�����傫���ꍇ
				if(ValidateVariableList_data(vvlist_i)->offset_level >= *offset_level){

					CSTLString *variable_name = CSTLString_new();
					CSTLString_printf(variable_name, 0, "%s", CSTLString_c_str(variable_table->variable_name));
					deletePointerAndArraySynbol(variable_name);

					//array_offset�̕ϐ����ƈ�v���錟�ؗp�ϐ��������A�Ȃ����Ώەϐ��̗L���͈͂����ؗp�ϐ��̗L���͈͂���v�����ꍇ
					if(CSTLString_compare(variable_name, ValidateVariableList_data(vvlist_i)->target_variable_name) == 0 &&
						ValidateVariableList_data(vvlist_i)->enable_start == variable_table->enable_start  &&
						variable_table->enable_end == ValidateVariableList_data(vvlist_i)->enable_end){
							CSTLString *validate_variable = CSTLString_new();
							//���ؗp�ϐ������擾
							CSTLString_printf(validate_variable, 0, "%s", CSTLString_c_str(ValidateVariableList_data(vvlist_i)->variable_name));
							//�|�C���^�Ɣz��̋L�����폜����
							deletePointerAndArraySynbol(validate_variable);

							//���؎��̐ݒ�
							//�����Abasis_location����n�܂鎮�łȂ���΁A���̂悤�Ɏ���ǉ�����
							//���ؕϐ��� = malloc(sizeof(int)); *���ؕϐ���
							if(ValidateVariableList_data(vvlist_i)->offset_level == *offset_level &&
									CSTLString_find(validate_variable, "basis_location", 0) == CSTL_NPOS){
								CSTLString_printf(output, 1, "%s", CSTLString_c_str(validate_variable));
								//�񎟌��ڈȍ~�́A�z��Q�Ƃ̋L��������
								if(*offset_level > 1){
									for(iterator = 2; iterator <= *offset_level; iterator++){
										CSTLString_printf(output, 1, "[vviterator_%d]", iterator);
									}
								}
								CSTLString_printf(output, 1, " = malloc(sizeof(int)); *%s",  CSTLString_c_str(validate_variable));
							}else{
								CSTLString_printf(output, 1, "%s", CSTLString_c_str(validate_variable));
							}
							//�񎟌��ڈȍ~�́A�z��Q�Ƃ̋L��������
							if(*offset_level > 1){
								for(iterator = 2; iterator <= *offset_level; iterator++){
									CSTLString_printf(output, 1, "[vviterator_%d]", iterator);
								}
							}

							//���؎��̃I�t�Z�b�g���x�����A���ۂ̔z��̃I�t�Z�b�g���x���Ɠ������ꍇ�i���Ȃ킿�A���ӂ̒l�Ɠ����悤�ȃI�t�Z�b�g���x���Ɠ����ꍇ�j
							if(ValidateVariableList_data(vvlist_i)->offset_level == *offset_level){
								//����max_size�n�i���I�z��̐����������́j�̏ꍇ
								if(CSTLString_find(validate_variable, "max_size_", 0) == 0){

									CSTLString_printf(output, 1," = %s; ", offset_info);

								}
								//����basis_location�n�i�z��̈ʒu���������́j�̏ꍇ
								else if(CSTLString_find(validate_variable, "basis_location_", 0) == 0){

									CSTLString_printf(output, 1," = 0; ");

								}
								//����defined�n�i�|�C���^�����炩�̕ϐ��̃A�h���X��ݒ肵�Ă��邩���������́j�̏ꍇ
								else if(CSTLString_find(validate_variable, "defined_", 0) == 0){

									CSTLString_printf(output, 1," = 1; ");

								}
								//����malloc_flag_�n�i�|�C���^�����I�Ɋ��蓖�Ă��Ă��邩���������́j�̏ꍇ
								else if(CSTLString_find(validate_variable, "malloc_flag_", 0) == 0){

									CSTLString_printf(output, 1," = 0; ");

								}else{
									fprintf(stderr,"�s���Ȍ��؎��ł��B\n");
									exit(1);
								}
							}
							//�����łȂ��ꍇ
							else{
								//basis_location�n�̏ꍇ�͒ʏ�ɒǉ�����
								if(CSTLString_find(validate_variable, "basis_location_", 0) == 0){
									//malloc�֐��Ō��؎��ɑ΂��ĐV�����̈���m�ۂ���B
									CSTLString_printf(output, 1," = malloc((%s)*sizeof(int", offset_info);
								}
								//basis_location�n�ȊO�̏ꍇ�̓A�X�^���X�N��1��������
								else{
									//malloc�֐��Ō��؎��ɑ΂��ĐV�����̈���m�ۂ���B
									CSTLString_printf(output, 1," = malloc((%s)*sizeof(int*", offset_info);

								}
								//�|�C���^�L����ǉ�����B
								for(iterator = *offset_level + 2; iterator <= ValidateVariableList_data(vvlist_i)->offset_level;
									iterator++){
										CSTLString_printf(output, 1,"*");
								}
								//�֐������
								CSTLString_printf(output, 1,")); ");
							}

							CSTLString_delete(validate_variable);
					}

					CSTLString_delete(variable_name);
				}
		}
		*offset_level = *offset_level + 1;
		ArrayOffsetToVaridateStatement_Internal(output, validate_variable_list, variable_table, offset_list, offset_level);
		*offset_level = *offset_level - 1;
		if(*offset_level > 1){
			CSTLString_printf( output, 1, "} ");
		}

	}

}

/**
�z��̃I�t�Z�b�g���X�g����ɁA���؎����쐬����B
@param output �o�͂��錟�؎�
@param validate_variable_list ���ؗp�ϐ����X�g
@param variable_table �Ώۂ̕ϐ��f�[�^
@param offset_list �I�t�Z�b�g���X�g

@return �Ȃ�
*/
void ArrayOffsetToValidateStatement(CSTLString* output, ValidateVariableList *validate_variable_list, VARIABLE_TABLE *variable_table, OFFSET_LIST *offset_list){
	int offset_level = 1;
	ArrayOffsetToVaridateStatement_Internal(output, validate_variable_list, variable_table, offset_list, &offset_level);
}


/**
����������֌W�̏��freememinfo����Afree�֐��Ɋւ���ᔽ�s�ׂ��s���Ă��Ȃ����ǂ������`�F�b�N���邽�߂̌��؎��𐶐����Avalidate_statement_list�֒ǉ�����B

@param validate_statement_list �ǉ���̌��؎����X�g
@param freememinfo ����������֌W�̏��

@return �Ȃ�
*/
void createViolentFreeOperation(ValidateStatementList *validate_statement_list, FREEMEMINFO *freememinfo){
	//����������Ώۂ̕ϐ��̔z��I�t�Z�b�g�������o��
	ARRAY_OFFSET *target_free_variable = ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(freememinfo->free_variable));

	//�쐬���錟�؎�
	CSTLString *statement = CSTLString_new();

	//�ϐ��̔z��I�t�Z�b�g��񂩂�A�z������o���B
	int offset_level_counter;
	OFFSET_LISTIterator off_list_i;
	CSTLString *variable = CSTLString_new();

	//�z���ێ�������
	CSTLString *array_string = CSTLString_new();
	CSTLString *basis_location_content = CSTLString_new();
	//�ϐ����̎擾
	CSTLString_assign(variable, CSTLString_c_str(target_free_variable->variable_name));

	//�w�肵�������܂��́A���̔z��I�t�Z�b�g�������Ă��鎟���܂Ŕz�񎮂Ƃ��ďo�͂���
	for(offset_level_counter = 1, off_list_i = OFFSET_LIST_begin(target_free_variable->offset_list);
		off_list_i != OFFSET_LIST_end(target_free_variable->offset_list);
		offset_level_counter++, off_list_i = OFFSET_LIST_next(off_list_i)){


		//�z��𐶐����A�ǉ�����B
		CSTLString_printf(basis_location_content, 0, "basis_location_%d_%s%s", offset_level_counter, (char*)CSTLString_c_str(target_free_variable->variable_name), (char*)CSTLString_c_str(array_string));
		CSTLString_printf(array_string, 1," [ %s + %s ]", *OFFSET_LIST_data(off_list_i), (char*)CSTLString_c_str(basis_location_content));

		CSTLString_printf(variable, 1, "%s", CSTLString_c_str(array_string));
	}
	//��������A�`�F�b�N���邽�߂̕ϐ����쐬����
	//if(*malloc_flag_�K�w_�ϐ��� == 0) { printf("�\�[�X�t�@�C����Detected violent of free operation in variable �ϐ���"); assert(0); ���^�[������; }

	CSTLString_printf(statement, 0, "if(*malloc_flag_%d_%s == 0) { printf(\"#%s#:%d:Detected violent of free operation in variable %s\"); assert(0); ",
	 OFFSET_LIST_size(target_free_variable->offset_list) + 1, CSTLString_c_str(variable), getFileName(), target_free_variable->target_statement->line,  CSTLString_c_str(target_free_variable->variable_name));

	//���^�[�����߂̕ԋp�^�ɉ�����ύX(�����Avoid�^�ł���΁A�ureturn;�v�ɂ���)
	if(CSTLString_compare_with_char(target_free_variable->target_statement->return_type, "void") == 0){
		CSTLString_printf(statement, 1, "return; ");
	}else{
		CSTLString_printf(statement, 1, "return 1; ");
	}

	CSTLString_printf(statement, 1, "}");

	//���؎��̒ǉ�
	ValidateStatementList_push_back_ref(validate_statement_list,
		new_VALIDATE_STATEMENT(
			getNewValidateStatementID(validate_statement_list,target_free_variable->target_statement),
			CHECK_VS,
			VALIDATE_NOTUSED,
			statement,
			target_free_variable->target_statement
		)
	);
}

/**
���Z����я�]���̏�񂩂�A�[�����Z����я�]�ɂȂ��Ă��Ȃ����ǂ����̌��؎��𐶐�����B
@param validate_statement_list �i�[��̌��؎����X�g
@param divition_information_list �Ώۂ̏��Z����я�]���̏��

@return �Ȃ�
*/
void createZeroDivitionCheck(ValidateStatementList *validate_statement_list, DIVITION_INFORMATION_LIST *divition_information_list){
	//���Z����я�]���Ɋւ���C�e���[�^
	DIVITION_INFORMATION_LISTIterator di_i;
	//���Z����я�]�����̊e���ʎq�ɑ΂���C�e���[�^
	ARRAY_OFFSET_LISTIterator aoff_list_i;

	for(di_i = DIVITION_INFORMATION_LIST_rbegin(divition_information_list);
		di_i != DIVITION_INFORMATION_LIST_rend(divition_information_list);
		di_i = DIVITION_INFORMATION_LIST_prev(di_i)){
			//���Ɋւ���CSTL������𐶐�
			CSTLString *statement = CSTLString_new();
			CSTLString *identifires_list = CSTLString_new();
			CSTLString *parameter_list = CSTLString_new();
			CSTLString *output = CSTLString_new();
			//���̂悤�Ȏ��𐶐�����
			//if( (��) == 0 ){ printf("#�t�@�C����#:�s��:detected zero (divition/mod) operation in expression ��"); assert(0); ���^�[����; }
			CSTLString_printf(statement, 0, "if( (%s) == 0 ){ printf(\"#%s#:%d:detected zero ", CSTLString_c_str(DIVITION_INFORMATION_LIST_data(di_i)->statement),
				getFileName(), DIVITION_INFORMATION_LIST_data(di_i)->target_expression->line);

			//���̃^�C�v�����Z����]�Z�ɂ���ă��b�Z�[�W��ς���
			if(DIVITION_INFORMATION_LIST_data(di_i)->type == TYPE_DIV){
				CSTLString_printf(statement, 1, "division ");
			}else{
				CSTLString_printf(statement, 1, "mod ");
			}
			CSTLString_printf(statement, 1, "oparation in expression %s ", CSTLString_c_str(DIVITION_INFORMATION_LIST_data(di_i)->statement));

			//�z��I�t�Z�b�g���X�g����e���ʎq�̏����o�͂����A���ɒǉ����Ă���
			for(aoff_list_i = ARRAY_OFFSET_LIST_begin(DIVITION_INFORMATION_LIST_data(di_i)->identifiers);
				aoff_list_i != ARRAY_OFFSET_LIST_end(DIVITION_INFORMATION_LIST_data(di_i)->identifiers);
				aoff_list_i = ARRAY_OFFSET_LIST_next(aoff_list_i)){
					createArrayExpression(output, ARRAY_OFFSET_LIST_data(aoff_list_i), INT_MAX);
					CSTLString_printf(identifires_list, 1, "%s = %%d", CSTLString_c_str(output));
					//���ʎq���̍Ō�łȂ���΁A�J���}��؂肷��
					if(ARRAY_OFFSET_LIST_next(aoff_list_i) != ARRAY_OFFSET_LIST_end(DIVITION_INFORMATION_LIST_data(di_i)->identifiers)){
						CSTLString_printf(identifires_list, 1,", ");
					}

					CSTLString_printf(parameter_list, 1, ", %s", CSTLString_c_str(output));

				}
			CSTLString_printf(statement, 1, "( %s )\"%s); assert(0);", CSTLString_c_str(identifires_list), CSTLString_c_str(parameter_list));

			//���^�[�����߂̕ԋp�^�ɉ�����ύX(�����Avoid�^�ł���΁A�ureturn;�v�ɂ���)
			if(CSTLString_compare_with_char(DIVITION_INFORMATION_LIST_data(di_i)->target_expression->return_type, "void") == 0){
				CSTLString_printf(statement, 1, "return; ");
			}else{
				CSTLString_printf(statement, 1, "return 1; ");
			}

			CSTLString_printf(statement, 1, "}");

			//�������ꂽ���؎��̒ǉ�
			ValidateStatementList_push_back_ref(validate_statement_list,
				new_VALIDATE_STATEMENT(
					getNewValidateStatementID(validate_statement_list, DIVITION_INFORMATION_LIST_data(di_i)->target_expression),
					CHECK_VS,
					VALIDATE_NOTUSED,
					statement,
					DIVITION_INFORMATION_LIST_data(di_i)->target_expression
				)
			);

			CSTLString_delete(identifires_list);
			CSTLString_delete(parameter_list);
			CSTLString_delete(output);
		}
}
/**
���؎����X�gvalidate_statement_list����Atarget_statement�Ɠ���AST�̃A�h���X�����������̂�T���o���A�������ɏd�����Ȃ��悤�ɂ��邽�߂̐V�������؎��̎��ʔԍ����擾����B
�V�������؎������ɂ͂��̊֐�����V�������ʔԍ����擾���邱�ƁB

@param validate_statement_list �Ώۂ̌��؎����X�g
@param target_statement �Ώۂ̌��؎�����m�F���邽�߂�AST�̃A�h���X

@return �V�������ʔԍ����o�͂���B���łɓ���AST�̃A�h���X�������Ă��錟�؎����Ȃ���΂O��Ԃ��B
*/
int getNewValidateStatementID(ValidateStatementList *validate_statement_list, AST *target_statement){
	//�Ώۂ̌��؃��X�g���Q�Ƃ��邽�߂̃C�e���[�^
	ValidateStatementListIterator vslist_i;

	//�V�������ʔԍ��̂��߂̕ϐ�
	int new_id = 0;

	for(vslist_i = ValidateStatementList_begin(validate_statement_list);
		vslist_i != ValidateStatementList_end(validate_statement_list);
		vslist_i = ValidateStatementList_next(vslist_i)){
			//���łɓ���AST�̃A�h���X�����������̂�������΁Anew_id���J�E���g����B
			if(ValidateStatementList_data(vslist_i)->target_statement == target_statement){
				new_id++;
			}
	}

	return new_id;
}

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
		AST *target_expression, int *switch_mode){
	ASTListIterator p;
	int pointer_level, array_level;
	//direct_ref�����array_access����������A�P���ȍ~�̃��x�����m�F����
	if(CSTLString_compare_with_char(left_expression->name, "direct_ref") == 0 ||
		CSTLString_compare_with_char(left_expression->name, "array_access") == 0){
		ARRAY_OFFSET *array_offset = NULL;
		//�|�C���^����єz��ϐ��̊e�����̃I�t�Z�b�g�����߂�
		getPointerArrayOffset(left_expression, function_information_list, vtlist, 0, ignore_ast_list, &array_offset, target_expression, NOT_VIA_ANPASAND, NOT_INC_DEC);

		//DEBUG_MODE���L���Ȏ��|�C���^����єz��ϐ��̊e�����̃I�t�Z�b�g�̏����o�͂���
		#ifdef DEBUG_MODE
			if(array_offset != NULL){
				printARRAY_OFFSET(array_offset);
			}
		#endif
		//�|�C���^����єz��ϐ��̊e�����̃I�t�Z�b�g�̏�񂪎擾�ł����ꍇ�A����Ɋւ���������̏��̃��X�g�֓����
		if(array_offset != NULL){
			ARRAY_OFFSET_LIST_push_back_ref(array_offset_list, array_offset);
		}
		//�X�C�b�`�t���O���P�ɂ���
		*switch_mode = 1;
	}
	//�X�C�b�`�t���O���O�ł���AIDENTIFIER�����������ꍇ
	else if(*switch_mode == 0 && CSTLString_compare_with_char(left_expression->name, "IDENTIFIER") == 0 ){
		//�I�t�Z�b�g��񂪂Ȃ�array_offset���쐬����B
		ARRAY_OFFSET *array_offset;
		VARIABLE_TABLE *variable_table_data;
		OFFSET_LIST *offset_list = OFFSET_LIST_new();
		CSTLString *target_name = CSTLString_new();
		int ignore_flag;

		//�w�肵��IDLIST�Ɩ��O����ł��Y������ϐ��e�[�u���ւ̃A�h���X���擾����
		variable_table_data = searchVARIABLE_TABLE_LIST(left_expression->idlist, left_expression->content, vtlist);
		if(variable_table_data != NULL){
			//�w�肵���m�[�hleft_expression���Aignore_ast_list�ɑ��݂��Ȃ����ǂ������ׂ�
			ignore_flag = checkIgnoreASTList(left_expression, ignore_ast_list);

			//�����A���݂��Ȃ���΁A�z��I�t�Z�b�g���X�g
			if(ignore_flag == FAILED){
				getPointerLevelAndArrayLevelFromVARIABLE_TABLE(variable_table_data, &pointer_level, &array_level);

				CSTLString_assign(target_name, CSTLString_c_str(left_expression->content));

				array_offset = new_ARRAY_OFFSET(target_name, target_expression, left_expression, offset_list, pointer_level, array_level, NOT_VIA_ANPASAND, NOT_INC_DEC);

				//DEBUG_MODE���L���Ȏ��|�C���^����єz��ϐ��̊e�����̃I�t�Z�b�g�̏����o�͂���
				#ifdef DEBUG_MODE
					if(array_offset != NULL){
						printARRAY_OFFSET(array_offset);
					}
				#endif

				//�����array_offset_list�ɒǉ�����
				ARRAY_OFFSET_LIST_push_back_ref(array_offset_list, array_offset);
			}
		}else{
			fprintf(stderr,"#%s#:%d: variable %s is undeclarated!!\n",getFileName(), left_expression->line, CSTLString_c_str(left_expression->content));
			exit(1);
		}

	}//�C���N�������g���Z�q�������ꍇ�́A�]�܂����Ȃ������Ƃ��ċ����I��������
	else if(CSTLString_compare_with_char(left_expression->name, "inc_expr") == 0 ||
		CSTLString_compare_with_char(left_expression->name, "inc_after_expr") == 0){

			fprintf(stderr,"#%s#:%d: exist inclement operator in left expression!!\n",getFileName(), left_expression->line);
			exit(1);
	}
	//�f�N�������g���Z�q�������ꍇ�́A�]�܂����Ȃ������Ƃ��ċ����I��������
	else if(CSTLString_compare_with_char(left_expression->name, "dec_expr") == 0 ||
		CSTLString_compare_with_char(left_expression->name, "dec_after_expr") == 0){
			fprintf(stderr,"#%s#:%d: exist declement operator in left expression!!\n",getFileName(), left_expression->line);
			exit(1);

	}
	//�qAST�m�[�h���Q�Ƃ���
	for(p = ASTList_begin(left_expression->children);
		p != ASTList_end(left_expression->children);
		p = ASTList_next(p)){
			getLeftAssignmentInfo(ASTList_data(p), function_information_list, vtlist, ignore_ast_list, array_offset_list, target_expression, switch_mode);
	}

}

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
	 ARRAY_OFFSET_LIST *array_offset_list, ASTPOINTER_LIST *ignore_ast_list, AST *target_statement){
	//AST�̎q�m�[�h���Q�Ƃ����邽�߂̃C�e���[�^
	ASTListIterator ast_iterator;

	//�֐��Ăяo�����������ꍇ
	if(CSTLString_compare_with_char(root->name, "call_function") == 0){
		//���������蓖�Ċ֌W�̊֐��̉�͂��Asizeof�̌^�Ƃ��̎��̃T�C�Y���擾����
		*memalloc_info = memoryAllocationAnarysis(root, vtlist);
	}else if(CSTLString_compare_with_char(root->name, "direct_ref") == 0 ||
			CSTLString_compare_with_char(root->name, "array_access") == 0 ){
		//�|�C���^��z��̃I�t�Z�b�g���X�g���擾����
		int offset_level = 0;
		ARRAY_OFFSET *array_offset = NULL;
		getPointerArrayOffset(root, function_information_list, vtlist, offset_level, ignore_ast_list, &array_offset, target_statement, NOT_VIA_ANPASAND, NOT_INC_DEC);

		//DEBUG_MODE���L���Ȏ��|�C���^����єz��ϐ��̊e�����̃I�t�Z�b�g�̏����o�͂���
		#ifdef DEBUG_MODE
			if(array_offset != NULL){
				printARRAY_OFFSET(array_offset);
			}
		#endif

		//���炩�̔z��I�t�Z�b�g���X�g���擾�ł�����Aarray_offset_list�փv�b�V���o�b�N����
		if(array_offset != NULL){
			ARRAY_OFFSET_LIST_push_back_ref(array_offset_list, array_offset);
		}
	}
	//�A�h���X���Z�q�������ꍇ�́A�A�h���X���Z�q��ʂ����z��I�t�Z�b�g���X�g���擾����
	else if(CSTLString_compare_with_char(root->name, "address_ref") == 0){
		getArrayOffsetInAnpasandInfo(root, function_information_list, vtlist,
							array_offset_list, ignore_ast_list, target_statement);
	}
	//�C���N�������g���Z�q�������ꍇ�́A�]�܂����Ȃ������Ƃ��ċ����I��������
	//���R�F����p����������ɁA����p�������������Ă��邱�Ƃ͖]�܂����Ȃ�����
	else if(CSTLString_compare_with_char(root->name, "inc_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "inc_after_expr") == 0){

			fprintf(stderr,"#%s#:%d: exist increment operator in right assign expression!!\n",getFileName(), root->line);
			exit(1);
	}
	//�f�N�������g���Z�q�������ꍇ�́A�]�܂����Ȃ������Ƃ��ċ����I��������
	//���R�F����p����������ɁA����p�������������Ă��邱�Ƃ͖]�܂����Ȃ�����
	else if(CSTLString_compare_with_char(root->name, "dec_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "dec_after_expr") == 0){
			fprintf(stderr,"#%s#:%d: exist increment operator in right assign expression!!\n",getFileName(), root->line);
			exit(1);

	}
	//������������ꍇ�́A�]�܂����Ȃ������Ƃ��ċ����I��������
	else if(CSTLString_compare_with_char(root->name, "assignment_expression") == 0){
		fprintf(stderr,"#%s#:%d: exist assignment expression in right assign expression!!\n",getFileName(), root->line);
		exit(1);

	}
	//�����AIDENTIFIER�i���ʎq�j���������ꍇ
	else if(CSTLString_compare_with_char(root->name, "IDENTIFIER") == 0){
		//�I�t�Z�b�g��񂪂Ȃ�array_offset���쐬����B
		ARRAY_OFFSET *array_offset = NULL;
		VARIABLE_TABLE *variable_table_data;
		OFFSET_LIST *offset_list = OFFSET_LIST_new();
		CSTLString *target_name = CSTLString_new();
		//�w�肵���m�[�hroot���Aignore_ast_list�ɑ��݂��Ȃ����ǂ������ׂ邽�߂̃t���O
		int ignore_flag;
		//�Y������ϐ��̃|�C���^�������͔z��̎����𒲂ׂ�B
		int pointer_level, array_level;
		//�w�肵��IDLIST�Ɩ��O����ł��Y������ϐ��e�[�u���ւ̃A�h���X���擾����
		variable_table_data = searchVARIABLE_TABLE_LIST(root->idlist, root->content, vtlist);
		//�����A�Y������ϐ������������ꍇ
		if(variable_table_data != NULL){
			//�w�肵���m�[�hroot���Aignore_ast_list�ɑ��݂��Ȃ����ǂ������ׂ�
			ignore_flag = checkIgnoreASTList(root, ignore_ast_list);

			//�����A���݂��Ȃ���΁A�z��I�t�Z�b�g���X�g�ɒǉ�����
			if(ignore_flag == FAILED){
				getPointerLevelAndArrayLevelFromVARIABLE_TABLE(variable_table_data, &pointer_level, &array_level);

				CSTLString_assign(target_name, CSTLString_c_str(root->content));

				array_offset = new_ARRAY_OFFSET(target_name, target_statement, root, offset_list, pointer_level, array_level, NOT_VIA_ANPASAND, NOT_INC_DEC);

				//DEBUG_MODE���L���Ȏ��|�C���^����єz��ϐ��̊e�����̃I�t�Z�b�g�̏����o�͂���
				#ifdef DEBUG_MODE
					if(array_offset != NULL){
						printARRAY_OFFSET(array_offset);
					}
				#endif

				//�����array_offset_list�ɒǉ�����
				ARRAY_OFFSET_LIST_push_back_ref(array_offset_list, array_offset);
			}

		}
	}

	//AST�̎q�m�[�h���Q�Ƃ�����
	for(ast_iterator = ASTList_begin(root->children);
		ast_iterator != ASTList_end(root->children);
		ast_iterator = ASTList_next(ast_iterator)){

		getRightAssignmentInfo( ASTList_data(ast_iterator), function_information_list, vtlist, memalloc_info, array_offset_list, ignore_ast_list, target_statement);

	}
}


/**
�w�肵�����؎����X�gvalidate_statement_list����A���؎��̃��X�g�̓��e���o�͂���B
@param validate_statement_list �o�͂��錟�؎����X�g

@return �Ȃ�
*/
void printValidateStatementList(ValidateStatementList *validate_statement_list){

	ValidateStatementListIterator vslist_i;

	int vslist_counter = 0;
	printf("------ValidateStatementList_INFO------\n\n");

	for(vslist_i = ValidateStatementList_begin(validate_statement_list);
		vslist_i != ValidateStatementList_end(validate_statement_list);
		vslist_i = ValidateStatementList_next(vslist_i)){

		printf("------VARIDATE_STATEMENT_%d------\n\n", vslist_counter);
		printf("TARGET_AST_LIST_LINE = \"%d\"\n", ValidateStatementList_data(vslist_i)->target_statement->line);
		printf("TARGET_AST_NAME = \"%s\"\n", (char*)CSTLString_c_str(ValidateStatementList_data(vslist_i)->target_statement->name));

		if(ValidateStatementList_data(vslist_i)->check_or_modify == 0){
			printf("TYPE = \"CHECK\"\n");
		}else{
			printf("TYPE = \"MODIFY_VARIDATE_VARIABLE\"\n");
		}

		printf("VARIDATE_ID = \"%d\"\n", ValidateStatementList_data(vslist_i)->target_id);

		printf("USED = \"%d\"\n", ValidateStatementList_data(vslist_i)->used);

		printf("STATEMENT = \"%s\"\n", CSTLString_c_str(ValidateStatementList_data(vslist_i)->statement));

		printf("---------------------------------\n\n");

		vslist_counter++;

	}

	printf("----------------------------------------\n\n");

}

/**
fprintProgramDataWithVaridateStatement�̓��������B

@param output �o�͐�̃t�@�C���\����
@param root �v���O�����ւ�AST�m�[�h
@param validate_variable_list ���ؗp�ϐ����X�g
@param validate_statement_list ���؎����X�g
@param for_information_list for���Ɋւ�����̃��X�g
@param line �L���ێ�����v���O�����̍s��

@return �Ȃ�
*/
void fprintProgramDataWithVaridateStatement_Internal(FILE *output, AST *root, ValidateVariableList *validate_variable_list,
 ValidateStatementList *validate_statement_list, ForInformationList *for_information_list, int *line){
	ASTListIterator p;
	ValidateVariableListIterator vvlist_i;


	//�ϐ��̃u���b�NID
	int block_id;
	//�ϐ��̃u���b�N���x��
	int block_level;

	//�v���O�����ł���ꍇ�́A�v���O�������ʂ̌��ؗp�ϐ����o�͂���
	if(CSTLString_compare_with_char(root->name, "program") == 0){
		//���ؗp�ϐ����X�g���Q�Ƃ���
		for(vvlist_i = ValidateVariableList_begin(validate_variable_list);
			vvlist_i != ValidateVariableList_end(validate_variable_list);
			vvlist_i = ValidateVariableList_next(vvlist_i)){
				//���g�p��Ԃ̃u���b�NID�ƃu���b�N���x���������Ƃ��O�ł��錟�ؗp�ϐ���S�ďo�͂���
				if(ValidateVariableList_data(vvlist_i)->used == 0 && ValidateVariableList_data(vvlist_i)->block_level == 0 && ValidateVariableList_data(vvlist_i)->block_id == 0){
					fprintf(output, "%s %s ; ", (char*)CSTLString_c_str(ValidateVariableList_data(vvlist_i)->type), (char*)CSTLString_c_str(ValidateVariableList_data(vvlist_i)->variable_name));
					//���̌��ؗp�ϐ��͎g�p�ς݂ɂ���
					ValidateVariableList_data(vvlist_i)->used = 1;
				}
			}
		//AST�m�[�h���qAST�m�[�h�̏��������Ă�����A�qAST�m�[�h�ɂ��čċA�I�ɎQ�Ƃ�����
		for(p = ASTList_begin(root->children); p != ASTList_end(root->children); p = ASTList_next(p)){
			fprintProgramDataWithVaridateStatement_Internal(output, ASTList_data(p), validate_variable_list, validate_statement_list, for_information_list, line);
		}
	}
	//���[�t�m�[�h�i�qAST�m�[�h�̐���0��AST�m�[�h�j�̏ꍇ
	else if(ASTList_size(root->children) == 0){
		//AST�m�[�h�̍s���ƈ����̍s�������ݍ���Ȃ��Ƃ��A���s���o�͂����A�o�͂���s���𒲐�����
		while(*line < root->line){
			fprintf(output, "\n");
			*line = *line + 1;
		}

		//AST�m�[�h�̓��e���o�͂�����
		fprintf(output, "%s ",CSTLString_c_str(root->content));

		//�u���b�N�̊J�n�������L����������A���ؗp�ϐ����X�g����K�v�Ȍ��ؗp�ϐ����o�͂���
		if(CSTLString_compare_with_char(root->name, "{") == 0){

			//�u���b�N���x�����Ƃ�ID���擾����
			block_id = root->block_id;
			//�u���b�N���x�����擾����
			block_level = root->block_level;

			//���ؗp�ϐ����X�g���Q�Ƃ���
			for(vvlist_i = ValidateVariableList_begin(validate_variable_list);
				vvlist_i != ValidateVariableList_end(validate_variable_list);
				vvlist_i = ValidateVariableList_next(vvlist_i)){
				//���g�p��ԂŁA�錾�ʒu�E�u���b�NID�E�u���b�N���x������v���錟�ؗp�ϐ����o�͂���
				if(ValidateVariableList_data(vvlist_i)->used == 0 && root->line == ValidateVariableList_data(vvlist_i)->declaration_location
					&& ValidateVariableList_data(vvlist_i)->block_id == block_id && ValidateVariableList_data(vvlist_i)->block_level == block_level){
					fprintf(output, "%s %s ; ", (char*)CSTLString_c_str(ValidateVariableList_data(vvlist_i)->type), (char*)CSTLString_c_str(ValidateVariableList_data(vvlist_i)->variable_name));
					//���̌��ؗp�ϐ��͎g�p�ς݂ɂ���
					ValidateVariableList_data(vvlist_i)->used = 1;
				}
			}

			//�u���b�N�J�n���ɑ΂��錟�؎��̒ǉ�
			fprintValidateStatement(output, validate_statement_list, root, MODIFY_VS, FALSE);
		}
	}
	//���ʂ̎��̏ꍇ�̏���
	else if(CSTLString_compare_with_char(root->name, "expression_statement") == 0 ||
		CSTLString_compare_with_char(root->name, "declaration_with_init") == 0){


		//AST�m�[�h�̍s���ƈ����̍s�������ݍ���Ȃ��Ƃ��A���s���o�͂����A�o�͂���s���𒲐�����
		while(*line < root->line){
			fprintf(output, "\n");
			*line = *line + 1;
		}

		//�Y������expression_statement�ɑ΂���`�F�b�N�p���؎���S�ďo�͂�����
		fprintValidateStatement(output, validate_statement_list, root, CHECK_VS, FALSE);

		//AST�m�[�h���qAST�m�[�h�̏��������Ă�����A�qAST�m�[�h�ɂ��čċA�I�ɎQ�Ƃ�����
		for(p = ASTList_begin(root->children); p != ASTList_end(root->children); p = ASTList_next(p)){
			fprintProgramDataWithVaridateStatement_Internal(output, ASTList_data(p), validate_variable_list, validate_statement_list, for_information_list, line);
		}

		//�Y������expression_statement�ɑ΂��錟�؎��ύX�p�̌��؎���S�ďo�͂�����
		fprintValidateStatement(output, validate_statement_list, root, MODIFY_VS, FALSE);

		//�����̂��o�͂�����B
		CSTLString *c = CSTLString_new();
		getStringFromAST(c,root);
		CSTLString_replace_string(c,"\"","\\\"");
		CSTLString_replace_string(c,"%","%%");
		fprintf(output, "printf(\"%s\\n\");\n", CSTLString_c_str(c));

	}
	//for���n���������ꍇ�Awhile�̌`�ɒ����Ȃ���A���؎������Ă���
	else if(CSTLString_compare_with_char(root->name, "for_statement_type_a") == 0 ||
		CSTLString_compare_with_char(root->name, "for_statement_type_b") == 0 ||
		CSTLString_compare_with_char(root->name, "for_statement_type_c") == 0 ||
		CSTLString_compare_with_char(root->name, "for_statement_type_d") == 0){

		//���̏o�͂Ɏg�p���邽�߂�CSTLString
		CSTLString *statement = CSTLString_new();
		//���Ă͂܂�for���̏����擾����
		ForInformation *for_information = searchFOR_INFORMATION_FromAST(for_information_list, root);

		//AST�m�[�h�̍s���ƈ����̍s�������ݍ���Ȃ��Ƃ��A���s���o�͂����A�o�͂���s���𒲐�����
		while(*line < for_information->init_expression->line){
			fprintf(output, "\n");
			*line = *line + 1;
		}
		//�܂����������`�F�b�N������ь��ؗp�ϐ��̕ҏW�����܂܂��ďo�͂�����
		getStringFromAST(statement, for_information->init_expression);
		fprintValidateStatement(output, validate_statement_list, for_information->init_expression, CHECK_VS, FALSE);
		fprintf(output, "%s ", CSTLString_c_str(statement));
		fprintValidateStatement(output, validate_statement_list, for_information->init_expression, MODIFY_VS, FALSE);


		//���ɏ�������" while(������){for�����̎� " �̌`���ɂ���
		CSTLString_assign(statement, "");
		getStringFromAST(statement, for_information->continue_condition);
		//�Z�~�R�����͗]���Ȃ̂ō폜����
		CSTLString_replace_string(statement, ";", "");
		fprintf(output, "while( %s ) {", CSTLString_c_str(statement));

		//for�����̎��͍ċA�I�ɌĂяo��
		fprintProgramDataWithVaridateStatement_Internal(output, for_information->statement, validate_variable_list, validate_statement_list, for_information_list, line);

		//�Ō�ɑ�����������΁A������`�F�b�N������ь��ؗp�ϐ��̕ҏW�����܂܂��ďo�͂�����
		if(for_information->inc_dec_expression != NULL){
			CSTLString_assign(statement, "");
			getStringFromAST(statement, for_information->inc_dec_expression);
			fprintValidateStatement(output, validate_statement_list, for_information->inc_dec_expression, CHECK_VS, FALSE);
			fprintf(output, "\n%s ; ", CSTLString_c_str(statement));
			fprintValidateStatement(output, validate_statement_list, for_information->inc_dec_expression, MODIFY_VS, FALSE);
		}

		//�傩�����ŋ�؂��ďI��
		fprintf(output, "} ");
		CSTLString_delete(statement);
	}
	//if���Aswitch���Awhile���Ado-while���������ꍇ
	else if(CSTLString_compare_with_char(root->name, "if_statement") == 0 ||
		CSTLString_compare_with_char(root->name, "switch_statement") == 0 ||
		CSTLString_compare_with_char(root->name, "while_statement") == 0 ||
		CSTLString_compare_with_char(root->name, "dowhile_statement") == 0){
		//AST�m�[�h���qAST�m�[�h�̏��������Ă�����A�qAST�m�[�h�ɂ��čċA�I�ɎQ�Ƃ�����
		for(p = ASTList_begin(root->children);
			CSTLString_compare_with_char(ASTList_data(p)->name, "statement") != 0 &&
			p != ASTList_end(root->children);
			p = ASTList_next(p)){
			fprintProgramDataWithVaridateStatement_Internal(output, ASTList_data(p), validate_variable_list, validate_statement_list, for_information_list, line);
		}
		//statement�������ꍇ
		if(CSTLString_compare_with_char(ASTList_data(p)->name, "statement") == 0){
			//�u���b�N�t���̖��߂łȂ��ꍇ
			if(CSTLString_compare_with_char(ASTLIST_ITERATOR_1(ASTList_data(p))->name, "compound_statement_a") != 0 &&
			CSTLString_compare_with_char(ASTLIST_ITERATOR_1(ASTList_data(p))->name, "compound_statement_a") != 0){
				//��������ǉ����������A�ǉ�������
				fprintf(output, "{ ");
				fprintProgramDataWithVaridateStatement_Internal(output, ASTList_data(p), validate_variable_list, validate_statement_list, for_information_list, line);
				fprintf(output, "} ");
			}
			//�u���b�N�t���̏ꍇ
			else{
				fprintProgramDataWithVaridateStatement_Internal(output, ASTList_data(p), validate_variable_list, validate_statement_list, for_information_list, line);
			}
		}
		//statement�ȍ~�ɕ��͂�����΁A������ċA�I�ɏo�͂�����
		if(p != ASTList_end(root->children)){
			for(p = ASTList_next(p);
				p != ASTList_end(root->children);
				p = ASTList_next(p)){
				fprintProgramDataWithVaridateStatement_Internal(output, ASTList_data(p), validate_variable_list, validate_statement_list, for_information_list, line);
			}
		}

	}
	//if-else���������ꍇ
	else if(CSTLString_compare_with_char(root->name, "ifelse_statement") == 0){
		p = ASTList_begin(root->children);
		while(p != ASTList_end(root->children)){
			//AST�m�[�h���qAST�m�[�h�̏��������Ă�����A�qAST�m�[�h�ɂ��čċA�I�ɎQ�Ƃ�����
			for(;
				CSTLString_compare_with_char(ASTList_data(p)->name, "statement") != 0 &&
				p != ASTList_end(root->children);
				p = ASTList_next(p)){
				fprintProgramDataWithVaridateStatement_Internal(output, ASTList_data(p), validate_variable_list, validate_statement_list, for_information_list, line);
			}
			//statement�������ꍇ
			if(CSTLString_compare_with_char(ASTList_data(p)->name, "statement") == 0){
				//�u���b�N�t���̖��߂łȂ��ꍇ
				if(CSTLString_compare_with_char(ASTLIST_ITERATOR_1(ASTList_data(p))->name, "compound_statement_a") != 0 &&
				CSTLString_compare_with_char(ASTLIST_ITERATOR_1(ASTList_data(p))->name, "compound_statement_a") != 0){
					//��������ǉ����������A�ǉ�������
					//fprintf(output, "{ ");
					fprintProgramDataWithVaridateStatement_Internal(output, ASTList_data(p), validate_variable_list, validate_statement_list, for_information_list, line);
					//fprintf(output, "} ");
				}
				//�u���b�N�t���̏ꍇ
				else{
					fprintProgramDataWithVaridateStatement_Internal(output, ASTList_data(p), validate_variable_list, validate_statement_list, for_information_list, line);
				}
				//���̂Ƃ����P���炷
				p = ASTList_next(p);
			}else{
				break;
			}
		}
	}
	//�����֐��Ăяo���������ꍇ
	/*
	else if(CSTLString_compare_with_char(root->name, "call_function") == 0){
		//���؎���T�����߂̃C�e���[�^
		ValidateStatementListIterator vs_i;
		//�֐��ύX�^�̌��؎����i�[���邽�߂̌��؎�
		VALIDATE_STATEMENT* change_function = NULL;

		//�����ŁA�֐��ύX�^�̌��؎������݂��邩�ǂ������ׂ�
		for(vs_i = ValidateStatementList_begin(validate_statement_list);
			vs_i != ValidateStatementList_end(validate_statement_list);
			vs_i = ValidateStatementList_next(vs_i)){

				//�����Y�����関�g�p�̊֐��ύX�^�̌��؎������݂���Ȃ�΁A���̌��؎����擾���A�g�p�ς݂ɂ�����A�T�����I��������
				if(ValidateStatementList_data(vs_i)->used == VALIDATE_NOTUSED && ValidateStatementList_data(vs_i)->target_statement == root){
					change_function = ValidateStatementList_data(vs_i);
					change_function->used = VALIDATE_USED;
					break;
				}
			}

		//�����֐��ύX�^�̌��؎������������ꍇ�́A���̊֐��Ƃ��ďo�͂�����
		if(change_function != NULL){
			fprintf(output, "%s", CSTLString_c_str(change_function->statement));
		}else{
			//AST�m�[�h���qAST�m�[�h�̏��������Ă�����A�qAST�m�[�h�ɂ��čċA�I�ɎQ�Ƃ�����
			for(p = ASTList_begin(root->children); p != ASTList_end(root->children); p = ASTList_next(p)){
				fprintProgramDataWithVaridateStatement_Internal(output, ASTList_data(p), validate_variable_list, validate_statement_list, for_information_list, line);
			}
		}
	}*/
	else{
		//AST�m�[�h���qAST�m�[�h�̏��������Ă�����A�qAST�m�[�h�ɂ��čċA�I�ɎQ�Ƃ�����
		for(p = ASTList_begin(root->children); p != ASTList_end(root->children); p = ASTList_next(p)){
			fprintProgramDataWithVaridateStatement_Internal(output, ASTList_data(p), validate_variable_list, validate_statement_list, for_information_list, line);
		}
	}
}

/**
���؎����X�g�ƂƂ��Ƀv���O�����f�[�^���o�͂���B

@param root �v���O�����ւ�AST�m�[�h
@param validate_variable_list ���ؗp�ϐ����X�g
@param validate_statement_list ���؎����X�g
@param for_information_list for���Ɋւ�����̃��X�g

@return �Ȃ�
*/
void printProgramDataWithValidateStatement(AST *root, ValidateVariableList *validate_variable_list, ValidateStatementList *validate_statement_list, ForInformationList *for_information_list){

	int line = 1;

	fprintProgramDataWithVaridateStatement_Internal(stdout, root, validate_variable_list, validate_statement_list, for_information_list, &line);

}

/**
���؎����X�g�⌟�ؗp�ϐ������ƂɃv���O�����f�[�^�𐶐����A�w�肵���t�@�C��output�ɏo�͂���B

@param output �o�͐�̃t�@�C���\����
@param root �v���O�����ւ�AST�m�[�h
@param validate_variable_list ���ؗp�ϐ����X�g
@param validate_statement_list ���؎����X�g
@param for_information_list for���Ɋւ�����̃��X�g

@return �Ȃ�
*/
void fprintProgramDataWithValidateStatement(FILE *output, AST *root, ValidateVariableList *validate_variable_list, ValidateStatementList *validate_statement_list, ForInformationList *for_information_list){
	if(output != NULL){
		int line = 1;
		fprintProgramDataWithVaridateStatement_Internal(output, root, validate_variable_list, validate_statement_list, for_information_list, &line);
	}
	//�����A�t�@�C���\���̂�NULL�ł���ꍇ�̓G���[���o�͂��������A�����I��������
	else{
		fprintf(stderr,"Input File is unexists or invalid!!\n");
		exit(1);
	}
}

/**
���ɑΉ����錟�؎����o�͂�����B

@param output �o�͐�̃t�@�C���\����
@param validate_statement_list �o�͑Ώۂ̌��؎����X�g
@param target_ast �Ώۂ�AST�m�[�h
@param check_or_modify ���؎����`�F�b�N����^�C�v���A�v���O���������ɕҏW����^�C�v���𔻒f����t���O�B�O�F�`�F�b�N����^�C�v�A�P�F�ҏW����^�C�v
@param allow_output_used_statement �g�p�ς݂̌��؎����܂߂ďo�͂��邩�ǂ����̃t���O�@�O�F�o�͂��Ȃ��@�P�F�o�͂���

@return �Ȃ�
*/
void fprintValidateStatement(FILE *output, ValidateStatementList *validate_statement_list, AST *target_ast, int check_or_modify, int allow_output_used_statement){

	int output_id;
	ValidateStatement *output_validate_statement;
	ValidateStatementListIterator vslist_i;

	//�����A�g�p�ς݂̌��؎����o�͂���ꍇ�́A�g�p�ς݂̌��؎������ׂĖ��g�p�ɕύX����B
	if(allow_output_used_statement){
		for(vslist_i = ValidateStatementList_begin(validate_statement_list);
			vslist_i != ValidateStatementList_end(validate_statement_list);
			vslist_i = ValidateStatementList_next(vslist_i)){

				if( ValidateStatementList_data(vslist_i)->used == VALIDATE_USED &&
					ValidateStatementList_data(vslist_i)->target_statement == target_ast &&
					ValidateStatementList_data(vslist_i)->check_or_modify == check_or_modify &&
					output_id > ValidateStatementList_data(vslist_i)->target_id ){
						ValidateStatementList_data(vslist_i)->used = VALIDATE_NOTUSED;
					}
		}
	}
	//���g�p�̌��؎�������܂ŁA�����Əo�͂�����
	while(1){
		ValidateStatement *output_validate_statement;
		output_id = INT_MAX;
		//���g�p�ŁAtarget_id���ł����������؎���T���o���A�o�͂���
		for(vslist_i = ValidateStatementList_begin(validate_statement_list);
			vslist_i != ValidateStatementList_end(validate_statement_list);
			vslist_i = ValidateStatementList_next(vslist_i)){

				if( ValidateStatementList_data(vslist_i)->used == VALIDATE_NOTUSED &&
					ValidateStatementList_data(vslist_i)->target_statement == target_ast &&
					ValidateStatementList_data(vslist_i)->check_or_modify == check_or_modify &&
					output_id > ValidateStatementList_data(vslist_i)->target_id ){
						output_id = ValidateStatementList_data(vslist_i)->target_id;
						output_validate_statement = ValidateStatementList_data(vslist_i);
					}
		}
		//�����Aoutput_id��������ԂłȂ��ꍇ�i���Ȃ킿�Ȃ�炩�̌��؎��������o�����ꍇ)�͌��؎����o�͂�����
		if(output_id != INT_MAX){
			fprintf(output, "%s ", (char*)CSTLString_c_str(output_validate_statement->statement));
			//���̌��؎��͎g�p�ς݂ɂ���
			output_validate_statement->used = VALIDATE_USED;
		}else{
			break;
		}
	}
}
/**
���ɑΉ����錟�؎���assert(0); ���폜���������o�͂�����B

@param output �o�͐�̃t�@�C���\����
@param validate_statement_list �o�͑Ώۂ̌��؎����X�g
@param target_ast �Ώۂ�AST�m�[�h
@param check_or_modify ���؎����`�F�b�N����^�C�v���A�v���O���������ɕҏW����^�C�v���𔻒f����t���O�B�O�F�`�F�b�N����^�C�v�A�P�F�ҏW����^�C�v
@param allow_output_used_statement �g�p�ς݂̌��؎����܂߂ďo�͂��邩�ǂ����̃t���O�@�O�F�o�͂��Ȃ��@�P�F�o�͂���

@return �Ȃ�
*/
void fprintValidateStatement_not_assert(FILE *output, ValidateStatementList *validate_statement_list, AST *target_ast, int check_or_modify, int allow_output_used_statement){

	int output_id;
	ValidateStatement *output_validate_statement;
	ValidateStatementListIterator vslist_i;

	CSTLString *output_validate_statement_string = CSTLString_new();

	//�����A�g�p�ς݂̌��؎����o�͂���ꍇ�́A�g�p�ς݂̌��؎������ׂĖ��g�p�ɕύX����B
	if(allow_output_used_statement){
		for(vslist_i = ValidateStatementList_begin(validate_statement_list);
			vslist_i != ValidateStatementList_end(validate_statement_list);
			vslist_i = ValidateStatementList_next(vslist_i)){

				if( ValidateStatementList_data(vslist_i)->used == VALIDATE_USED &&
					ValidateStatementList_data(vslist_i)->target_statement == target_ast &&
					ValidateStatementList_data(vslist_i)->check_or_modify == check_or_modify &&
					output_id > ValidateStatementList_data(vslist_i)->target_id ){
						ValidateStatementList_data(vslist_i)->used = VALIDATE_NOTUSED;
					}
		}
	}
	//���g�p�̌��؎�������܂ŁA�����Əo�͂�����
	while(1){
		ValidateStatement *output_validate_statement;
		output_id = INT_MAX;
		//���g�p�ŁAtarget_id���ł����������؎���T���o���A�o�͂���
		for(vslist_i = ValidateStatementList_begin(validate_statement_list);
			vslist_i != ValidateStatementList_end(validate_statement_list);
			vslist_i = ValidateStatementList_next(vslist_i)){

				if( ValidateStatementList_data(vslist_i)->used == VALIDATE_NOTUSED &&
					ValidateStatementList_data(vslist_i)->target_statement == target_ast &&
					ValidateStatementList_data(vslist_i)->check_or_modify == check_or_modify &&
					output_id > ValidateStatementList_data(vslist_i)->target_id ){
						output_id = ValidateStatementList_data(vslist_i)->target_id;
						output_validate_statement = ValidateStatementList_data(vslist_i);
					}
		}
		//�����Aoutput_id��������ԂłȂ��ꍇ�i���Ȃ킿�Ȃ�炩�̌��؎��������o�����ꍇ)�͌��؎����o�͂�����
		if(output_id != INT_MAX){
			//�o�͂��������؎��𕶎���Ƃ��Ď擾����
			CSTLString_assign(output_validate_statement_string,
					CSTLString_c_str(output_validate_statement->statement));

			//assert(0);���폜���������A�o�͂�����
			CSTLString_replace_string(output_validate_statement_string, ASSERT_STRING, "");
			fprintf(output, "%s ", (char*)CSTLString_c_str(output_validate_statement_string));
			//���̌��؎��͎g�p�ς݂ɂ���
			output_validate_statement->used = VALIDATE_USED;
		}else{
			break;
		}
	}

	CSTLString_delete(output_validate_statement_string);
}

/**
�v���O�����X���C�V���O���̕ϐ���`�����ƂɁA���ؗp�ϐ����X�g�̏o�͂�ݒ肷��B
@param validate_variable_list ���ؗp�ϐ����X�g
@param expr_slicing_list �v���O�����X���C�V���O���̃��X�g

@return �Ȃ�
 */
void setValidateVariableFromExprSlicing(ValidateVariableList *validate_variable_list, EXPR_SLICING_LIST *expr_slicing_list){
	EXPR_SLICING_LISTIterator e_i;

	ValidateVariableListIterator vvlist_i;

	CSTLString *variable_name;
	AST *declaration_node;

	//���ؗp�ϐ����X�g�𒀎��擾���A�v���O�����X���C�V���O���̕ϐ��錾�ɑΉ����邩�ǂ����`�F�b�N����
	for(e_i = EXPR_SLICING_LIST_begin(expr_slicing_list);
		e_i != EXPR_SLICING_LIST_end(expr_slicing_list);
		e_i = EXPR_SLICING_LIST_next(e_i)){

		//�����A�ϐ��錾�ł���ꍇ
		if(CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "declaration_with_init") == 0 ||
				CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "declarator") == 0){
			//�ϐ������擾����
			variable_name = ARRAY_OFFSET_LIST_front(EXPR_SLICING_LIST_data(e_i)->target_variable)->variable_name;

			//�錾����擾����
			declaration_node = EXPR_SLICING_LIST_data(e_i)->expression;
			//�v���O�����X���C�V���O���̕ϐ��錾�ɑΉ����Ă��邱�Ƃ��킩��΁A���̕ϐ��̎g�p��Ԃ��O�Ƃ��A�g�p�ł���悤�ɂ���
			for(vvlist_i = ValidateVariableList_begin(validate_variable_list);
				vvlist_i != ValidateVariableList_end(validate_variable_list);
				vvlist_i = ValidateVariableList_next(vvlist_i)){
					if(CSTLString_compare(ValidateVariableList_data(vvlist_i)->target_variable_name, variable_name) == 0 &&
							ValidateVariableList_data(vvlist_i)->block_id == declaration_node->block_id &&
							ValidateVariableList_data(vvlist_i)->block_level == declaration_node->block_level){
						ValidateVariableList_data(vvlist_i)->used = 0;
					}
			}
		}

		//�q�m�[�h�ɂ������T�����s��
		setValidateVariableFromExprSlicing(validate_variable_list, EXPR_SLICING_LIST_data(e_i)->children1);
		setValidateVariableFromExprSlicing(validate_variable_list, EXPR_SLICING_LIST_data(e_i)->children2);
	}
}

/**
fprintProgramDataWithPSIVaridateStatement�̓��������ł���B

@param output �o�͂����̃t�@�C��
@param expr_slicing_list �v���O�����X���C�V���O���
@param validate_variable_list ���ؗp�ϐ����X�g
@param validate_statement_list ���؎����X�g
@param for_information_list for���Ɋւ�����
@param check_target_ast �`�F�b�N���؎��̑Ώۂւ�AST�m�[�h
@param line �o�͂ɗp����s��

@return �Ȃ�
 */
void fprintProgramDataWithPSIVaridateStatement_Internal(FILE *output, EXPR_SLICING_LIST *expr_slicing_list, ValidateStatementList *validate_statement_list,
			ValidateVariableList *validate_variable_list, ForInformationList *for_information_list, AST *check_target_ast, int *line){
	EXPR_SLICING_LISTIterator e_i;
	AST *block_start, *block_end;
	ValidateVariableListIterator vvlist_i;
	//�v���O�����X���C�V���O�Ɋ֌W��������o�͂�����B
	for(e_i = EXPR_SLICING_LIST_begin(expr_slicing_list);
		e_i != EXPR_SLICING_LIST_end(expr_slicing_list);
		e_i = EXPR_SLICING_LIST_next(e_i)){
		//�v���O�����X���C�V���O�̃t���O�������Ă���̂ݏo�͏������s��
		if(EXPR_SLICING_LIST_data(e_i)->flag == 1){
			//for���̏ꍇ
			if(CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "for_statement_type_a") == 0 ||
				CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "for_statement_type_b") == 0 ||
				CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "for_statement_type_c") == 0 ||
				CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "for_statement_type_d") == 0){
				//���̏o�͂Ɏg�p���邽�߂�CSTLString
				CSTLString *statement = CSTLString_new();
				//���Ă͂܂�for���̏����擾����
				ForInformation *for_information = searchFOR_INFORMATION_FromAST(for_information_list, EXPR_SLICING_LIST_data(e_i)->expression);

				//AST�m�[�h�̍s���ƈ����̍s�������ݍ���Ȃ��Ƃ��A���s���o�͂����A�o�͂���s���𒲐�����
				while(*line < for_information->init_expression->line){
					fprintf(output, "\n");
					*line = *line + 1;
				}
				//�܂��������ɂ��Ẵ`�F�b�N�p����ь��ؗp�ϐ��̕ҏW�p�̌��؎��o�͂�����
				//�`�F�b�N���ɂ��Ă�check_target_ast�ƈ�v����AST�m�[�h�̏ꍇ�̂ݏo�͂�����
				getStringFromAST(statement, for_information->init_expression);
				if(EXPR_SLICING_LIST_data(e_i)->expression == check_target_ast){
					fprintValidateStatement(output, validate_statement_list, for_information->init_expression, CHECK_VS, FALSE);
				}else{
					fprintValidateStatement_not_assert(output, validate_statement_list, for_information->init_expression, CHECK_VS, FALSE);
				}
				fprintf(output, "%s ", CSTLString_c_str(statement));
				fprintValidateStatement(output, validate_statement_list, for_information->init_expression, MODIFY_VS, FALSE);


				//���ɏ�������" while(������){for�����̎� " �̌`���ɂ���
				CSTLString_assign(statement, "");
				getStringFromAST(statement, for_information->continue_condition);
				//�Z�~�R�����͗]���Ȃ̂ō폜����
				CSTLString_replace_string(statement, ";", "");
				fprintf(output, "while( %s ) {", CSTLString_c_str(statement));

				//for�����̎��͍ċA�I�ɌĂяo��
				fprintProgramDataWithPSIVaridateStatement_Internal(output, EXPR_SLICING_LIST_data(e_i)->children1, validate_statement_list,
						validate_variable_list, for_information_list, check_target_ast, line);

				//�Ō�ɑ�����������΁A������`�F�b�N������ь��ؗp�ϐ��̕ҏW�����܂܂��ďo�͂�����
				//�`�F�b�N���ɂ��Ă�check_target_ast�ƈ�v����AST�m�[�h�̏ꍇ�̂ݏo�͂�����
				if(for_information->inc_dec_expression != NULL){
					CSTLString_assign(statement, "");
					getStringFromAST(statement, for_information->inc_dec_expression);
					if(EXPR_SLICING_LIST_data(e_i)->expression == check_target_ast){
						fprintValidateStatement(output, validate_statement_list, for_information->inc_dec_expression, CHECK_VS, FALSE);
					}else{
						fprintValidateStatement_not_assert(output, validate_statement_list, for_information->inc_dec_expression, CHECK_VS, FALSE);
					}
					fprintf(output, "\n%s ; ", CSTLString_c_str(statement));
					fprintValidateStatement(output, validate_statement_list, for_information->inc_dec_expression, MODIFY_VS, FALSE);
				}

				//�傩�����ŋ�؂��ďI��
				fprintf(output, "} ");
				CSTLString_delete(statement);
			}
			//if_else���̏ꍇ
			else if(CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "ifelse_statement") == 0){
				//1�Ԗڂ̃m�[�h(if����)����statement�����܂ŏo�͂�����
				fprintfStatement(output, EXPR_SLICING_LIST_data(e_i)->expression, line, 1, &block_start, &block_end);
				//���[�J���ϐ��ɑ΂��錟�ؗp�ϐ����o�͂�����
				if(block_start != NULL){
					for(vvlist_i = ValidateVariableList_begin(validate_variable_list);
						vvlist_i != ValidateVariableList_end(validate_variable_list);
						vvlist_i = ValidateVariableList_next(vvlist_i)){
						//���g�p��ԂŁA�錾�ʒu�E�u���b�NID�E�u���b�N���x������v���錟�ؗp�ϐ����o�͂���
						if(ValidateVariableList_data(vvlist_i)->used == 0 && block_start->line == ValidateVariableList_data(vvlist_i)->declaration_location
							&& ValidateVariableList_data(vvlist_i)->block_id == block_start->block_id && ValidateVariableList_data(vvlist_i)->block_level == block_start->block_level){
							fprintf(output, "%s %s ; ", (char*)CSTLString_c_str(ValidateVariableList_data(vvlist_i)->type), (char*)CSTLString_c_str(ValidateVariableList_data(vvlist_i)->variable_name));
							//���̌��ؗp�ϐ��͎g�p�ς݂ɂ���
							ValidateVariableList_data(vvlist_i)->used = 1;
						}
					}
				}
				//�v���O�����X���C�V���O�̎q�m�[�h���Q�Ƃ���
				fprintProgramDataWithPSIVaridateStatement_Internal(output, EXPR_SLICING_LIST_data(e_i)->children1, validate_statement_list,
						validate_variable_list, for_information_list, check_target_ast, line);
				//�u���b�N�ō\������Ă���ꍇ�͏I����"}"��ǉ��ŏo�͂�����
				if(block_end != NULL){
					fprintDataFromAST(output, block_end, line);
				}
				//�R�Ԗڂ̃m�[�h(else����)����statement�����܂ŏo�͂�����
				fprintfStatement(output, EXPR_SLICING_LIST_data(e_i)->expression, line, 3, &block_start, &block_end);
				//���[�J���ϐ��ɑ΂��錟�ؗp�ϐ����o�͂�����
				if(block_start != NULL){
					for(vvlist_i = ValidateVariableList_begin(validate_variable_list);
						vvlist_i != ValidateVariableList_end(validate_variable_list);
						vvlist_i = ValidateVariableList_next(vvlist_i)){
						//���g�p��ԂŁA�錾�ʒu�E�u���b�NID�E�u���b�N���x������v���錟�ؗp�ϐ����o�͂���
						if(ValidateVariableList_data(vvlist_i)->used == 0 && block_start->line == ValidateVariableList_data(vvlist_i)->declaration_location
							&& ValidateVariableList_data(vvlist_i)->block_id == block_start->block_id && ValidateVariableList_data(vvlist_i)->block_level == block_start->block_level){
							fprintf(output, "%s %s ; ", (char*)CSTLString_c_str(ValidateVariableList_data(vvlist_i)->type), (char*)CSTLString_c_str(ValidateVariableList_data(vvlist_i)->variable_name));
							//���̌��ؗp�ϐ��͎g�p�ς݂ɂ���
							ValidateVariableList_data(vvlist_i)->used = 1;
						}
					}
				}
				//�v���O�����X���C�V���O�̎q�m�[�h���Q�Ƃ���
				fprintProgramDataWithPSIVaridateStatement_Internal(output, EXPR_SLICING_LIST_data(e_i)->children2, validate_statement_list,
						validate_variable_list, for_information_list, check_target_ast, line);
				//�u���b�N�ō\������Ă���ꍇ�͏I����"}"��ǉ��ŏo�͂�����
				if(block_end != NULL){
					fprintDataFromAST(output, block_end, line);
				}
			}
			//�ȉ��̂悤�Ȏq�m�[�h�����̂��̂ł���ꍇ
			//�֐���`,if���Awhile��,do_while��,switch��,���x����
			else if(EXPR_SLICING_LIST_size(EXPR_SLICING_LIST_data(e_i)->children1) > 0){
				//1�Ԗڂ̎q�m�[�h����statement�����܂ŏo�͂�����
				fprintfStatement(output, EXPR_SLICING_LIST_data(e_i)->expression, line, 1, &block_start, &block_end);
				//���[�J���ϐ��ɑ΂��錟�ؗp�ϐ����o�͂�����
				if(block_start != NULL){
					for(vvlist_i = ValidateVariableList_begin(validate_variable_list);
						vvlist_i != ValidateVariableList_end(validate_variable_list);
						vvlist_i = ValidateVariableList_next(vvlist_i)){
						//���g�p��ԂŁA�錾�ʒu�E�u���b�NID�E�u���b�N���x������v���錟�ؗp�ϐ����o�͂���
						if(ValidateVariableList_data(vvlist_i)->used == 0 && block_start->line == ValidateVariableList_data(vvlist_i)->declaration_location
							&& ValidateVariableList_data(vvlist_i)->block_id == block_start->block_id && ValidateVariableList_data(vvlist_i)->block_level == block_start->block_level){
							fprintf(output, "%s %s ; ", (char*)CSTLString_c_str(ValidateVariableList_data(vvlist_i)->type), (char*)CSTLString_c_str(ValidateVariableList_data(vvlist_i)->variable_name));
							//���̌��ؗp�ϐ��͎g�p�ς݂ɂ���
							ValidateVariableList_data(vvlist_i)->used = 1;
						}
					}
				}

				//�u���b�N�J�n���ɑ΂��錟�؎��̒ǉ�
				fprintValidateStatement(output, validate_statement_list, block_start, MODIFY_VS, FALSE);

				//�v���O�����X���C�V���O�̎q�m�[�h���Q�Ƃ���
				fprintProgramDataWithPSIVaridateStatement_Internal(output, EXPR_SLICING_LIST_data(e_i)->children1, validate_statement_list,
						validate_variable_list, for_information_list, check_target_ast, line);
				//�u���b�N�ō\������Ă���ꍇ�͏I����"}"��ǉ��ŏo�͂�����
				if(block_end != NULL){
					fprintDataFromAST(output, block_end, line);
				}
			}
			//��L�ȊO�̎��̏ꍇ
			else{
				//���ɑ΂��āA�`�F�b�N������ь��ؗp�ϐ��̕ҏW�����܂܂��ďo�͂�����
				//�`�F�b�N���ɂ��Ă�check_target_ast�ƈ�v����AST�m�[�h�̏ꍇ�̂ݏo�͂�����
				if(EXPR_SLICING_LIST_data(e_i)->expression == check_target_ast){
					fprintValidateStatement(output, validate_statement_list, EXPR_SLICING_LIST_data(e_i)->expression, CHECK_VS, FALSE);
				}else{
					fprintValidateStatement_not_assert(output, validate_statement_list, EXPR_SLICING_LIST_data(e_i)->expression, CHECK_VS, FALSE);
				}
				fprintDataFromAST(output, EXPR_SLICING_LIST_data(e_i)->expression, line);
				fprintValidateStatement(output, validate_statement_list, EXPR_SLICING_LIST_data(e_i)->expression, MODIFY_VS, FALSE);
			}
		}
	}
}


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
			ValidateVariableList *validate_variable_list, ForInformationList *for_information_list, AST *check_target_ast){

	ValidateVariableListIterator vvlist_i;

	//���ׂĂ̌��ؗp�ϐ����X�g�����ׂĎg�p��Ԃɂ���
	for(vvlist_i = ValidateVariableList_begin(validate_variable_list);
		vvlist_i != ValidateVariableList_end(validate_variable_list);
		vvlist_i = ValidateVariableList_next(vvlist_i)){
		ValidateVariableList_data(vvlist_i)->used = 1;
	}
	//�v���O�����X���C�V���O���̕ϐ���`�����ƂɁA���ؗp�ϐ����X�g�̏o�͂�ݒ肷��
	setValidateVariableFromExprSlicing(validate_variable_list, expr_slicing_list);

	//�O���[�o���ϐ��ɑ΂��錟�ؗp�ϐ����X�g���o�͂�����
	for(vvlist_i = ValidateVariableList_begin(validate_variable_list);
		vvlist_i != ValidateVariableList_end(validate_variable_list);
		vvlist_i = ValidateVariableList_next(vvlist_i)){
			//���g�p��Ԃ̃u���b�NID�ƃu���b�N���x���������Ƃ��O�ł��錟�ؗp�ϐ���S�ďo�͂���
			if(ValidateVariableList_data(vvlist_i)->used == 0 && ValidateVariableList_data(vvlist_i)->block_level == 0 && ValidateVariableList_data(vvlist_i)->block_id == 0){
				fprintf(output, "%s %s ; ", (char*)CSTLString_c_str(ValidateVariableList_data(vvlist_i)->type), (char*)CSTLString_c_str(ValidateVariableList_data(vvlist_i)->variable_name));
				//���̌��ؗp�ϐ��͎g�p�ς݂ɂ���
				ValidateVariableList_data(vvlist_i)->used = 1;
			}
		}

	//�v���O�����X���C�V���O�������ƂɁA���؎���ǉ����Ȃ���o�͂�����
	int line = 1;
	fprintProgramDataWithPSIVaridateStatement_Internal(output, expr_slicing_list, validate_statement_list,
			validate_variable_list,for_information_list, check_target_ast, &line);

}


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
		ValidateVariableList *validate_variable_list, ForInformationList *for_information_list, INCLUDE_LIST *include_list){

	ASTPOINTER_LIST *astpointer_list = ASTPOINTER_LIST_new();
	ASTPOINTER_LISTIterator a_i;

	int file_counter;

	CSTLString *file_name = CSTLString_new();

	FILE *output;

	//���؎��̃`�F�b�N����AST�m�[�h���X�g���擾����
	getASTList_FromValidateStatementList(validate_statement_list, astpointer_list);

	for(file_counter = 0, a_i = ASTPOINTER_LIST_begin(astpointer_list);
		a_i != ASTPOINTER_LIST_end(astpointer_list);
		file_counter++, a_i = ASTPOINTER_LIST_next(a_i)){
		//�v���O�����X���C�V���O�̏�Ԃ�����������
		initExprSlicingListFlag(expr_slicing_list);

		//����AST�m�[�h�����ƂɃv���O�����X���C�V���O���s��
		startStaticSlicing(*ASTPOINTER_LIST_data(a_i), expr_slicing_list);

		//�o�͂������t�@�C�������w�肷��
		CSTLString_printf(file_name, 0, "%s_%d.c", getFileName(), file_counter);

		//�t�@�C�����J����
		output = fopen(CSTLString_c_str(file_name), "w");

		//���ׂĂ̌��؎����X�g�̎g�p��Ԃ𖢎g�p��Ԃɏ���������
		initVaridateStatement_flag(validate_statement_list);

		//�v���O�����X���C�V���O���Ɋ�Â��āA���؎����o�͂�����
		fprintProgramDataWithPSIVaridateStatement(output, expr_slicing_list, validate_statement_list,
				validate_variable_list, for_information_list, *ASTPOINTER_LIST_data(a_i));

		//�t�@�C�������
		fclose(output);

		//�C���N���[�h���X�g����C���N���[�h��ǉ�����
		addIncludeDataFromFile((char*)CSTLString_c_str(file_name), include_list);
	}

	CSTLString_delete(file_name);
}

int compare_validate_statement_list_ast(const void *a, const void *b){

	int flag = ((ValidateStatement*)a)->target_statement - ((ValidateStatement*)b)->target_statement;

	if(flag != 0){
		return ((ValidateStatement*)a)->target_statement->line - ((ValidateStatement*)b)->target_statement->line;
	}else{
		return flag;
	}
}

/**
���؎����X�g��AST�m�[�h���ƂɃ\�[�g����B
@param validate_statement_list �\�[�g�Ώۂ̌��؎����X�g
*/
void validateStatementListSort(ValidateStatementList *validate_statement_list){
	ValidateStatementList_sort(validate_statement_list, compare_validate_statement_list_ast);
}

/**
���؎����X�g�̃`�F�b�N������AAST�m�[�h�����o���AAST���X�g�Ƃ��Ă܂Ƃ߂�B
@param validate_statement_list ���o����̌��؎����X�g
@param ast_node_list �܂Ƃ߂���AST�m�[�h���X�g

@return �Ȃ�
 */
void getASTList_FromValidateStatementList(ValidateStatementList *validate_statement_list, ASTPOINTER_LIST *ast_node_list){
	AST *tmp;
	ValidateStatementListIterator vs_list;
	//���؎����X�g��T������
	for(vs_list = ValidateStatementList_begin(validate_statement_list);
		vs_list != ValidateStatementList_end(validate_statement_list);
		vs_list = ValidateStatementList_next(vs_list)){

		//�����Atmp������`���قȂ�l���o���ꍇ
		if(tmp == NULL || ValidateStatementList_data(vs_list)->check_or_modify == CHECK_VS &&
				tmp != ValidateStatementList_data(vs_list)->target_statement){
			tmp = ValidateStatementList_data(vs_list)->target_statement;
			ASTPOINTER_LIST_push_back(ast_node_list, tmp);
		}
	}
}
