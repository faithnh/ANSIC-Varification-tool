/*!
  @brief ���̃t�@�C���́AC����v���O������̕��G�Ȕz��Q�Ƃ���ђ��ڎQ�Ƃɂ�鉉�Z���e�����̔z��I�t�Z�b�g���Ƃ��Ċi�[���邽�߂̖��߂��܂܂�Ă���B
  �e�����̔z��I�t�Z�b�g���Ƃ͊e�����ɂ����āA�ǂ̕������w���Ă��邩�Ƃ������Ɋւ�����̂��Ƃł���B
  @file PointerArrayControl.h
  @author faithnh
 */

#ifndef POINTER_ARRAY_CONTROL_HEADDER
#define POINTER_ARRAY_CONTROL_HEADDER

#include <cstl/list.h>
#include"../Library/CSTLString.h"
#include"AST.h"
#include"Synbol.h"

#include"FunctionInformation.h"

CSTL_LIST_INTERFACE(OFFSET_LIST, char *);

/**
�z���|�C���^�̊e�����̃I�t�Z�b�g�֌W���i�[���邽�߂̍\���̂ł���B�z��I�t�Z�b�g�ƌĂ΂��B
*/
typedef struct array_offset {
	CSTLString *variable_name;				///�ϐ���
	AST *target_statement;					///�^�[�Q�b�g��statement(�����ł�expression_statement�Ȃǂ�����)
	AST *variable_address;				///���̕ϐ������w���Ă���AST�A�h���X
	int pointer_level;			///���̕ϐ��̃|�C���^���x��
	int array_level;			///���̕ϐ��̔z�񃌃x��
	int anpasand_flag;			///���̕ϐ��̓A���p�T���h������ł��邩�ǂ����̃t���O�@�P�F����ł���@�O�F����ł��Ȃ�
	int inc_dec_flag;			///���̕ϐ��̓C���N�������g����уf�N�������g���܂܂�Ă��邩�ǂ����̃t���O�@�O�F�܂�ł��Ȃ��@�P�F�C���N�������g���܂܂�Ă���@�Q�F�f�N�������g���܂܂�Ă���
	OFFSET_LIST *offset_list;	///�e�����̃I�t�Z�b�g
} ARRAY_OFFSET;

CSTL_LIST_INTERFACE(ARRAY_OFFSET_LIST, ARRAY_OFFSET);

CSTL_LIST_INTERFACE(ASTPOINTER_LIST, AST *);

/**
�z���|�C���^�̊e�����̃I�t�Z�b�g�֌W���i�[���邽�߂̍\���̂̃f�[�^�𐶐�������B
@param variable_name �ϐ���
@param target_statement �^�[�Q�b�g��statement
@param variable_address ���̕ϐ������w���Ă���AST�A�h���X
@param offset_list �e�����̃I�t�Z�b�g
@param pointer_level ���̕ϐ��̃|�C���^���x��
@param array_level ���̕ϐ��̔z�񃌃x��
@param anpasand_flag �A���p�T���h������ł��邩�ǂ����̃t���O�@�P�F����ł���@�O�F����ł��Ȃ�
@param inc_dec_flag �C���N�������g����уf�N�������g���܂܂�Ă��邩�ǂ����̃t���O�@�O�F�܂�ł��Ȃ��@�P�F�C���N�������g���܂܂�Ă���@�Q�F�f�N�������g���܂܂�Ă���

@return �z���|�C���^�̊e�����̃I�t�Z�b�g�Ɋւ���\���̂ւ̃A�h���X��Ԃ�
*/
ARRAY_OFFSET *new_ARRAY_OFFSET_char(char *variable_name, AST *target_statement, AST *variable_address,
									OFFSET_LIST *offset_list, int pointer_level, int array_level, int anpasand_flag, int inc_dec_flag);

/**
�z���|�C���^�̊e�����̃I�t�Z�b�g�֌W���i�[���邽�߂̍\���̂̃f�[�^�𐶐�������B
@param variable_name �ϐ���
@param target_statement �^�[�Q�b�g��statement
@param variable_address ���̕ϐ������w���Ă���AST�A�h���X
@param offset_list �e�����̃I�t�Z�b�g
@param pointer_level ���̕ϐ��̃|�C���^���x��
@param array_level ���̕ϐ��̔z�񃌃x��
@param anpasand_flag ���̕ϐ��̓A���p�T���h������ł��邩�ǂ����̃t���O�@�P�F����ł���@�O�F����ł��Ȃ�
@param inc_dec_flag �C���N�������g����уf�N�������g���܂܂�Ă��邩�ǂ����̃t���O�@�O�F�܂�ł��Ȃ��@�P�F�C���N�������g���܂܂�Ă���@�Q�F�f�N�������g���܂܂�Ă���

@return �z���|�C���^�̊e�����̃I�t�Z�b�g�Ɋւ���\���̂ւ̃A�h���X��Ԃ��B
*/
ARRAY_OFFSET *new_ARRAY_OFFSET(	CSTLString *variable_name, AST *target_statement, AST *variable_address,
							   OFFSET_LIST *offset_list, int pointer_level, int array_level, int anpasand_flag, int inc_dec_flag);

/**
�C�ӂ̕�������A���I�ϐ��Ƃ��ăI�t�Z�b�g���X�g�ɒǉ�����B
@param offset_list �Ώۂ̃I�t�Z�b�g���X�g
@param string �C�ӂ̕�����

@return �Ȃ�
 */
void OFFSET_LIST_push_back_alloc(OFFSET_LIST *offset_list, char *string);

/**
�|�C���^����єz��ϐ��̊e�����̃I�t�Z�b�g�ƂȂ鎮�����߂�B
@param root ���Ӓl�Ɋւ���AST�m�[�h
@param function_information_list �֐��Ɋւ����񃊃X�g
@param vtlist ���ؑΏۂ̎����}�[�N���邽�߂̕ϐ����X�g
@param offset_level �I�t�Z�b�g���x�����v�Z���邽�߂̂Ƃ���B��{�I�ɂO����͂���B�P�ȏ���͂���΁A���ꂪ�ŉ��ʃ��x���ƂȂ�B
@param ignore_ast_list �|�C���^�ł̈ʒu�����؍ς݂ł���AIDENTIFIER�𖳎����邽�߂�AST�̃A�h���X���X�g
@param array_offset �|�C���^����єz��̃I�t�Z�b�g���
@param target_statement ���؎��̑ΏۂƂȂ�X�e�[�g�����g
@param anpasand_flag �A���p�T���h������ł��邩�ǂ����̃t���O�@�P�F����ł���@0�F����ł��Ȃ�
@param inc_dec_flag �C���N�������g����уf�N�������g���܂܂�Ă��邩�ǂ����̃t���O�@�O�F�܂�ł��Ȃ��@�P�F�C���N�������g���܂܂�Ă���@�Q�F�f�N�������g���܂܂�Ă���
@return �Ȃ�
*/
int getPointerArrayOffset(AST *root, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist, int offset_level,
	ASTPOINTER_LIST *ignore_ast_list, ARRAY_OFFSET **array_offset, AST *target_statement, int anpasand_flag, int inc_dec_flag);

/**
�|�C���^����єz��ϐ��̊e�����̃I�t�Z�b�g���X�g���擾����B
@param root �I�t�Z�b�g���X�g�ɊY������AST�m�[�h
@param array_offset_list �|�C���^����єz��̃I�t�Z�b�g���̃��X�g
@param function_information_list �֐��Ɋւ����񃊃X�g
@param vtlist ���ؑΏۂ̎����}�[�N���邽�߂̕ϐ����X�g
@param ignore_ast_list �|�C���^�ł̈ʒu�����؍ς݂ł���AIDENTIFIER�𖳎����邽�߂�AST�̃A�h���X���X�g
@param target_statement ���؎��̑ΏۂƂȂ�X�e�[�g�����g
@return �Ȃ�
*/
void getARRAY_OFFSET_LIST(AST *root, ARRAY_OFFSET_LIST *array_offset_list, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
						  ASTPOINTER_LIST *ignore_ast_list, AST *target_statement);
/**
�|�C���^����єz��ϐ��̊e�����̃I�t�Z�b�g���X�g���擾����B�܂��A����������Ώۂ̃m�[�h��ݒ�\�ł���B
@param root �I�t�Z�b�g���X�g�ɊY������AST�m�[�h
@param array_offset_list �|�C���^����єz��̃I�t�Z�b�g���̃��X�g
@param function_information_list �֐��Ɋւ����񃊃X�g
@param vtlist ���ؑΏۂ̎����}�[�N���邽�߂̕ϐ����X�g
@param ignore_ast_list �|�C���^�ł̈ʒu�����؍ς݂ł���AIDENTIFIER�𖳎����邽�߂�AST�̃A�h���X���X�g
@param target_statement ���؎��̑ΏۂƂȂ�X�e�[�g�����g
@param ignore_ast_name ����������`�r�s��
@return �Ȃ�
*/
void get_ARRAY_OFFSET_LISTIgnoreASTNAME(AST *root, ARRAY_OFFSET_LIST *array_offset_list, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
		  ASTPOINTER_LIST *ignore_ast_list, AST *target_statement, CSTLString *ignore_ast_name);
/**
address_ref�ł���m�[�h����T�����A����ɑ΂���A�h���X�Q�Ƃ�A���ʎq��T���o���A��������z��I�t�Z�b�g���X�garray_offset_list�֓����B
@param root �E�ӎ��Ɋւ���AST�m�[�h
@param function_information_list �֐��Ɋւ�����̃��X�g
@param vtlist �������m�ۏ����擾����̂ɕK�v�ȃv���O�����ϐ����X�g
@param array_offset_list ���ӎ���ɂ���|�C���^�Q�Ƃɑ΂���I�t�Z�b�g���X�g
@param ignore_ast_list �����ʒu�̃|�C���^�����Ă��������邽�߂̃��X�g
@param target_statement ���̌v�Z���𑮂��Ă���AST�m�[�h�ւ̃A�h���X�i��{�I��expression_statement�ł���m�[�h������j

@return �Ȃ�
*/
void getArrayOffsetInAnpasandInfo(AST *root,FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
							ARRAY_OFFSET_LIST *array_offset_list, ASTPOINTER_LIST *ignore_ast_list, AST *target_statement);

/**
inc_expr��dec_expr�Ȃǂ̃C���N�������g��f�N�������g���ł���m�[�h����T�����A����ɑ΂���A�h���X�Q�Ƃ�A���ʎq��T���o���A��������z��I�t�Z�b�g���X�garray_offset_list�֓����B
@param root inc_expr��dec_expr�Ȃǂ̃C���N�������g��f�N�������g���Ɋւ���AST�m�[�h
@param function_information_list �֐��Ɋւ�����̃��X�g
@param vtlist �������m�ۏ����擾����̂ɕK�v�ȃv���O�����ϐ����X�g
@param array_offset_list ���ӎ���ɂ���|�C���^�Q�Ƃɑ΂���I�t�Z�b�g���X�g
@param ignore_ast_list �����ʒu�̃|�C���^�����Ă��������邽�߂̃��X�g
@param target_statement ���̌v�Z���𑮂��Ă���AST�m�[�h�ւ̃A�h���X�i��{�I��expression_statement�ł���m�[�h������j
@param inc_dec_flag �C���N�������g����уf�N�������g���܂܂�Ă��邩�ǂ����̃t���O�@�P�F�C���N�������g���܂܂�Ă���@�Q�F�f�N�������g���܂܂�Ă���

@return �Ȃ�
*/
void getArrayOffsetInIncDecInfo(AST *root, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
								ARRAY_OFFSET_LIST *array_offset_list, ASTPOINTER_LIST *ignore_ast_list, AST *target_statement, int inc_dec_flag);

/**
�|�C���^�̃I�t�Z�b�g�̌��ؑΏۂƂȂ��Ă���ϐ�������AST�m�[�htarget����A�ԐړI�ɂǂ̊֌W�̒��Ɉʒu���Ă��邩�ǂ����𒲂ׁA���̃m�[�h�̃A�h���Xoutput�Ƃ��ĕԂ��B
���̂Ƃ��Atarget��薾�炩�ɏ�ʂł���AST�m�[�hroot��ݒ肵�Ȃ���΂Ȃ�Ȃ��B
�܂��Aoutput��minus_expr�̏ꍇ�͂��̃|�C���^���ЂƂ������ӂ��E�ӂ��ǂ����𒲂ׂ邽�߂ɁA
���̃|�C���^�̈���̃m�[�h��output2�֑������B

@param target ���ؑΏۂƂȂ��Ă���ϐ�
@param root ���ؑΏۂ̃m�[�h
@param output �o�͂����ԐړI�Ɋ֌W���Ă���m�[�h�ւ̃A�h���X
@param output2 output��minus_expr�̏ꍇ�Aminus_expr���1���̃m�[�h�������ɑ�������
@return �����������������ǂ����̃t���O�B���������ꍇ�͂P�A�����łȂ��ꍇ�͂O��Ԃ��B

@return �Ȃ�
*/
int getUpperExpressionRelationNode(AST *target, AST *root, AST **output, AST **output2);

/**
�ϐ�������z�񂨂�у|�C���^�������L����S�č폜����B
@param target �ύX�Ώۂ̕ϐ���
@return �Ȃ�
*/
void deletePointerAndArraySynbol(CSTLString *target);

/**
�ϐ�������|�C���^�������L���̂ݑS�č폜����B
@param target �ύX�Ώۂ̕ϐ���
@return �Ȃ�
*/
void deletePointer(CSTLString *target);

/**
primary_expression�Ƃ��Ďw�肵��AST�m�[�hroot����A���̎��̉��ʂł��鎟�̃m�[�h����T���o���A���̃A�h���X��output�֏o�͂����A1��Ԃ��B

minus_expr, plus_expr, array_access, direct_ref, IDENTIFIER, primary_expression

�Ȃ��Aoutput�̓��e��NULL�ɂ��邱�ƂŁAroot��艺�ʂ̃m�[�h���炪�����̑ΏۂƂȂ�B
�܂��A�|�C���^�v�Z�̊֌W��A+-���Z���Z�q�������悤�Ȃ��̂�CONSTANT(�萔�j�������ꍇ�̂݁A-1��Ԃ��B
������Ȃ��ꍇ��0�ł���B

@param root �w�肵��AST�m�[�h
@param output ��L�̌������m�[�h�ւ̃A�h���X

@return ��L�̏����Œl��ԋp����B

*/
int searchExpressionOrPointeArrayOrIden(AST *root, AST **output);

/**
direct_ref�Ƃ��Ďw�肵��AST�m�[�hroot����A���̎��̉��ʂł��鎟�̃m�[�h����T���o���A���̃A�h���X��output�֏o�͂����A1��Ԃ��B

IDENTIFIER array_access, direct_ref, IDENTIFIER, primary_expression
inc_after_expression, inc_expr, dec_after_expr, inc_expr
assignment_expression

�Ȃ��Aoutput�̓��e��NULL�ɂ��邱�ƂŁAroot��艺�ʂ̃m�[�h���炪�����̑ΏۂƂȂ�B
������Ȃ��ꍇ��0�ł���B

@param root �w�肵��AST�m�[�h
@param output ��L�̌������m�[�h�ւ̃A�h���X

@return ��L�̏����Œl��ԋp����B

*/
int searchPointerAccessOrIdentifierOrPrimary(AST *root, AST **output);

/**
direct_ref�Ƃ��Ďw�肵��AST�m�[�hroot����A�ȉ��̃m�[�h��T�������A�����AST���X�goutput�Ƃ��Ď擾����B

IDENTIFIER array_access, direct_ref, IDENTIFIER, primary_expression

�Ȃ��Aoutput�̓��e��NULL�ɂ��邱�ƂŁAroot��艺�ʂ̃m�[�h���炪�����̑ΏۂƂȂ�B
������Ȃ��ꍇ��0�ł���B

@param root �w�肵��AST�m�[�h
@param output ��L�̌������m�[�h�ւ̃A�h���X
@param getSize �擾�����l�̃T�C�Y��Ԃ����߂̕ϐ��B������Ȃ��ꍇ��0�ɂ����B

@return �Ȃ�
*/
void getPointerAccessOrIdentifierList(AST *root, AST ***output, int *getSize);

/**
���ʎq�̖��O����v����ϐ���ϐ����X�g����T���B���̂Ƃ��A��v����ϐ��𒲂ׂ���A�|�C���^�Ɣz��̎��������ׁA�I�t�Z�b�g���x���ȏ�ł���΁A
���������ƂɂȂ�A�P��Ԃ��B�����łȂ���΁A�O��Ԃ��B�܂��Aignore_ast_list�͖�������IDENTIFIER��AST�̃A�h���X���X�g�������邽�тɓo�^
�����B�����Aignore_ast_list�ɓo�^����Ă���m�[�h�Ȃ�A����͖��������B�܂��A������̂ɐ��������ꍇ�A���̊Y������ϐ��̔z�񃌃x����|
�C���^�̃��x�����Ԃ��B

@param identifier ���ʎq�̖��O
@param offset_level �I�t�Z�b�g���x��
@param variable_table_list �ϐ��e�[�u�����X�g
@param ignore_ast_list �|�C���^�ł̈ʒu�����؍ς݂ł���AIDENTIFIER�𖳎����邽�߂�AST�̃A�h���X���X�g
@param pointer_level �ϐ����X�g���猩�����ϐ��̃|�C���^���x��
@param array_level �ϐ����X�g���猩�����ϐ��̔z�񃌃x��

@return ���ʎq�̖��O����уI�t�Z�b�g���x���������𖞂����Ă���΂P��Ԃ��A�����łȂ���΂O��Ԃ��B
*/
int checkIdentifierPointerArrayLevel(AST *identifier,int offset_level, VARIABLE_TABLE_LIST *variable_table_list,
 ASTPOINTER_LIST *ignore_ast_list, int *pointer_level, int *array_level);

/**
�֐��Ăяo��������AST�m�[�h���A�o�^����Ă���֐��Ɋւ�����Ɋ܂܂�Ă��邩�ǂ����𒲂ׁA�����A���̊֐��̃|�C���^���x�����I�t�Z�b�g���x���ƈ�v
�����ꍇ�́A�G���[���o�͂��A�����I��������B
@param call_function �֐��Ăяo��������AST�m�[�h
@param offset_level �I�t�Z�b�g���x��
@param function_information_list �֐��Ɋւ�����̃��X�g

@return �Ȃ�
 */
void checkCallFunction(AST *call_function, int offset_level, FUNCTION_INFORMATION_LIST *function_information_list);

/**
�w�肵��AST�m�[�hast_data��AST�A�h���X���X�gignore_ast_list�ɑ��݂��邩�ǂ����𒲂ׂ�B���݂���ꍇ�͂P���������B
���݂��Ȃ��ꍇ�́Aast_data�̃A�h���X��ignore_ast_list�ɒǉ�������A0��Ԃ��B
@param ast_data �w�肵��AST�m�[�h
@param ignore_ast_list ���ׂ�Ώۂ�AST�A�h���X���X�g

@return ���݂���ꍇ�͂P��Ԃ��A�����łȂ��ꍇ�͂O��Ԃ�
*/
int checkIgnoreASTList(AST *ast_data, ASTPOINTER_LIST *ignore_ast_list);

/**
�|�C���^�̃I�t�Z�b�g�̌��ؑΏۂƂȂ��Ă���ϐ�������AST�m�[�htarget����A�ԐړI�ɂǂ̊֌W�̒��Ɉʒu���Ă��邩�ǂ����𒲂ׁA���̃m�[�h�̃A�h���Xoutput�Ƃ��ĕԂ��B
���̂Ƃ��Atarget��薾�炩�ɏ�ʂł���AST�m�[�hroot��ݒ肵�Ȃ���΂Ȃ�Ȃ��B
�܂��Aoutput��minus_expr�̏ꍇ�͂��̃|�C���^���ЂƂ������ӂ��E�ӂ��ǂ����𒲂ׂ邽�߂ɁA
���̃|�C���^�̈���̃m�[�h��output2�֑������B

@param target ���ؑΏۂƂȂ��Ă���ϐ�
@param root ���ؑΏۂ̃m�[�h
@param output �o�͂����ԐړI�Ɋ֌W���Ă���m�[�h�ւ̃A�h���X
@param output2 output��minus_expr�̏ꍇ�Aminus_expr���1���̃m�[�h�������ɑ�������
@return �����������������ǂ����̃t���O�B���������ꍇ�͂P�A�����łȂ��ꍇ�͂O��Ԃ��B
*/
int getUpperExpressionRelationNode(AST *target, AST *root, AST **output, AST **output2);


/*
�w�肵���e�����̔z���|�C���^�̃I�t�Z�b�g���X�garray_offset�̓��e���o�͂���B

@param array_offset �o�͑Ώۂ̊e�����̔z���|�C���^�̃I�t�Z�b�g���X�g

@return �Ȃ�
*/
void printARRAY_OFFSET(ARRAY_OFFSET *array_offset);

/*
�w�肵���e�����̔z���|�C���^�̃I�t�Z�b�g���X�garray_offset�̓��e���o�͂���B

@param array_offset_list �o�͑Ώۂ̊e�����̔z���|�C���^�̃I�t�Z�b�g���̃��X�g

@return �Ȃ�
*/
void printARRAY_OFFSET_LIST(ARRAY_OFFSET_LIST *array_offset_list);

/**
�ϐ��e�[�u���f�[�^variable_table����I�t�Z�b�g���X�goffset_list�𐶐�����B

@param offset_list ������̃I�t�Z�b�g���X�g
@param variable_table �ϐ��e�[�u���f�[�^

@return �Ȃ�
*/
void getOFFSET_LISTFromVariableTable(OFFSET_LIST *offset_list, VARIABLE_TABLE *variable_table);

/**
�I�t�Z�b�g���X�goffset_list�̒��g�����S�ɉ��������B

@param offset_list

@return �Ȃ�
*/
void deleteOFFSET_LIST(OFFSET_LIST *offset_list);

/**
�w�肵���z��I�t�Z�b�g����A���Z��̃|�C���^���x�������߂�B���Z��̃|�C���^���x���͂��̂Ƃ���ł���B
���Z��̃|�C���^���x�������̕ϐ��̔z��ƃ|�C���^���x���̍��v�l�{�A���p�T���h�t���O�i����ł���Ȃ�P�A�����łȂ��ꍇ�͂O�j�|���̔z��I�t�Z�b�g���̃I�t�Z�b�g���X�g
@param array_offset �w�肵���z��I�t�Z�b�g

@return ���߂����Z��̃|�C���^���x����Ԃ�
*/
int getOffsetLevelFromArrayOffset(ARRAY_OFFSET *array_offset);

/**
�w�肵���z��I�t�Z�b�g���X�g�ł̉��Z��̃|�C���^���x���̍ő僌�x���ł���z��I�t�Z�b�g�̃A�h���X�����߂�B�z��I�t�Z�b�g����̏ꍇ��NULL��������B
@param array_offset_list �w�肵���z��I�t�Z�b�g���X�g

@return ���߂����Z��̃|�C���^���x�����ő�ł���z��I�t�Z�b�g�̃A�h���X��Ԃ�
*/
ARRAY_OFFSET *maxOffsetLevelAddressFromArrayOffsetList(ARRAY_OFFSET_LIST *array_offset_list);

/**
�Ώۂ�AST�m�[�h����A���Z��̃|�C���^���x�����w�肳�ꂽ�|�C���^���x���Ɣz�񃌃x���̍��v�ƈ�v����悤��
�ϐ��̔z��I�t�Z�b�g���w�肳�ꂽ�z��I�t�Z�b�g���X�g����T���o���A����������A�h���X���擾����B

@param root �Ώۂ�AST�m�[�h
@param array_offset_list �Ώۂ̔z��I�t�Z�b�g���X�g
@param pointer_level �w�肷��|�C���^���x��
@param array_level �w�肷��z�񃌃x��

@return ���Z��̃|�C���^���x���Ǝw�肳�ꂽ�|�C���^���x���Ɣz�񃌃x���̍��v����v����悤�ȕϐ���Ԃ��B���s�����ꍇ��NULL��Ԃ��B
 */

ARRAY_OFFSET *searchOffsetLevelAddressFromArrayOffsetList(AST *root, ARRAY_OFFSET_LIST *array_offset_list,
		int pointer_level, int array_level);
/**
�w�肵���z��I�t�Z�b�g���X�g�ł̉��Z��̃|�C���^���x���̍ő僌�x�������߂�B�z��I�t�Z�b�g����̏ꍇ�͂O��������B
@param array_offset_list �w�肵���z��I�t�Z�b�g���X�g

@return ���߂����Z��̃|�C���^���x����Ԃ��B
*/
int maxOffsetLevelFromArrayOffsetList(ARRAY_OFFSET_LIST *array_offset_list);

/**
�w�肵��������A�K�v�ȃI�t�Z�b�g�����擾����B
@param expression �w�肵�����Ɋւ���AST�m�[�h
@param function_information_list �֐��Ɋւ�����̃��X�g
@param vtlist ���ؑΏۂ̎����}�[�N���邽�߂̕ϐ����X�g
@param ignore_ast_list �|�C���^�ł̈ʒu�����؍ς݂ł���AIDENTIFIER�𖳎����邽�߂�AST�̃A�h���X���X�g
@param array_offset_list �e�|�C���^����єz�񂲂Ƃ̃I�t�Z�b�g�̃��X�g
@param target_expression ���̍��ӎ��̏�ʂɈʒu����AST�m�[�h
@param switch_mode ���ڃA�N�Z�X����єz��A�N�Z�X��T�����AIDENTIFIER��T�����ǂ����̃X�C�b�`�t���O �O�F�����������@�P�Fdirect_ref��array_access�̂ݒT��
@param allow_subeffect ����p�̎����������ǂ����̃t���O �P�F���� �O�F�����Ȃ�
@return �Ȃ�
*/
void getExpressionOffsetInfo(AST *expression, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist, ASTPOINTER_LIST *ignore_ast_list,
 ARRAY_OFFSET_LIST * array_offset_list, AST *target_expression, int *switch_mode, int allow_subeffect);

/**
�w�肵����������A�K�v�ȃI�t�Z�b�g�����擾����B
@param argument �w�肵�������Ɋւ���AST�m�[�h
@param function_information_list �֐��Ɋւ�����̃��X�g
@param vtlist ���ؑΏۂ̎����}�[�N���邽�߂̕ϐ����X�g
@param ignore_ast_list �|�C���^�ł̈ʒu�����؍ς݂ł���AIDENTIFIER�𖳎����邽�߂�AST�̃A�h���X���X�g
@param array_offset_list �e�|�C���^����єz�񂲂Ƃ̃I�t�Z�b�g�̃��X�g
@param target_expression ���̍��ӎ��̏�ʂɈʒu����AST�m�[�h
@param switch_mode ���ڃA�N�Z�X����єz��A�N�Z�X��T�����AIDENTIFIER��T�����ǂ����̃X�C�b�`�t���O �O�F�����������@�P�Fdirect_ref��array_access�̂ݒT��
@return �Ȃ�
*/
void getArgumentOffsetInfo(AST *argument, FUNCTION_INFORMATION_LIST *function_information_list,
		VARIABLE_TABLE_LIST *vtlist, ASTPOINTER_LIST *ignore_ast_list, ARRAY_OFFSET_LIST * array_offset_list,
		AST *target_expression, int *switch_mode);

/**
�w�肵��������A�K�v�ȃI�t�Z�b�g�����擾����B����͕���p�̎��������B
@param expression �w�肵�����Ɋւ���AST�m�[�h
@param function_information_list �֐��Ɋւ�����̃��X�g
@param vtlist ���ؑΏۂ̎����}�[�N���邽�߂̕ϐ����X�g
@param ignore_ast_list �|�C���^�ł̈ʒu�����؍ς݂ł���AIDENTIFIER�𖳎����邽�߂�AST�̃A�h���X���X�g
@param array_offset_list �e�|�C���^����єz�񂲂Ƃ̃I�t�Z�b�g�̃��X�g
@param target_expression ���̍��ӎ��̏�ʂɈʒu����AST�m�[�h
@param switch_mode ���ڃA�N�Z�X����єz��A�N�Z�X��T�����AIDENTIFIER��T�����ǂ����̃X�C�b�`�t���O �O�F�����������@�P�Fdirect_ref��array_access�̂ݒT��
@return �Ȃ�
*/
void getSingleExpressionOffsetInfo(AST *expression, FUNCTION_INFORMATION_LIST *function_information_list,
		VARIABLE_TABLE_LIST *vtlist, ASTPOINTER_LIST *ignore_ast_list,
 ARRAY_OFFSET_LIST * array_offset_list, AST *target_expression, int *switch_mode);
/**
�z��I�t�Z�b�g��񂩂�A�C�ӂ̎����܂ł̔z�񎮂𐶐�����B

@param output �z�񎮂𐶐�����镶����
@param array_offset �Ώۂ̔z��I�t�Z�b�g
@param output_level �o�͂���������(���̂Ƃ��A�z��I�t�Z�b�g�𒴂���l����ꂽ�ꍇ�́A�z��I�t�Z�b�g�������܂ł̔z�񎮂��o�͂���)

@return �Ȃ�
*/

void createArrayExpression(CSTLString *output, ARRAY_OFFSET *array_offset, int output_level);

/**
�z��I�t�Z�b�g��񂩂�A���ؗp�ϐ��Ɏg����z�񎮂𐶐����A�I�t�Z�b�g���x����Ԃ��B
@param output ������̕�����
@param array_offset �Ώۂ̔z��I�t�Z�b�g

@return �z��I�t�Z�b�g��񂩂琶�����ꂽ�I�t�Z�b�g���x����Ԃ�
 */
int createValidateVariableArrayExpression(CSTLString *output, ARRAY_OFFSET *array_offset);

/**
�z��I�t�Z�b�g���X�gfromlist����move_start�ȍ~�̃f�[�^�����ׂāA��������̔z��I�t�Z�b�g���X�gtolist�Ɉړ�������B
@param fromlist �ړ����Ƃ̔z��I�t�Z�b�g���X�g
@param tolist �ړ���̔z��I�t�Z�b�g���X�g
@param move_start �ړ����������f�[�^�̈ʒu(�擪����O�ԖڂƂ���)

@return �Ȃ�
 */
void moveArrayOffsetList(ARRAY_OFFSET_LIST *fromlist, ARRAY_OFFSET_LIST *tolist, int move_start);

/**
�z��I�t�Z�b�g���X�gfromlist����move_start�ȍ~�̃f�[�^�����ׂāA��������̔z��I�t�Z�b�g���X�gtolist�ɃR�s�[������B
@param fromlist �R�s�[���̔z��I�t�Z�b�g���X�g
@param tolist �R�s�[��̔z��I�t�Z�b�g���X�g
@param move_start �ړ����������f�[�^�̈ʒu(�擪����O�ԖڂƂ���)

@return �Ȃ�
 */
void copyArrayOffsetList(ARRAY_OFFSET_LIST *fromlist, ARRAY_OFFSET_LIST *tolist, int move_start);

/**
�ϐ��e�[�u������A�ϐ��̒�`�ɑ΂���m�[�h�ɊY���������T���A����ɑ΂���z��I�t�Z�b�g�����擾����B
@param declarator_array_offset_list �擾��̔z��I�t�Z�b�g���
@param declarator_expression �ϐ���`�܂ł�AST�A�h���X
@param target_expression �Ώۂ�declarator_with_init�ւ�AST�A�h���X
@param vtlist ���ׂ��̕ϐ��e�[�u��

@return �Ȃ�
*/
void getDeclaratorArrayOffset(ARRAY_OFFSET_LIST *declarator_array_offset_list, AST *declarator_expression, AST *target_expression, VARIABLE_TABLE_LIST *vtlist);

/**
�z��I�t�Z�b�g���X�garray_offset_list����A�w�肵���ϐ�����T�����A
������΂��̕ϐ����ւ̃A�h���X��Ԃ��B

@param array_offset_list �T���Ώۂ̔z��I�t�Z�b�g���X�g
@param name �T���������ϐ���

@return ������Εϐ����ւ̃A�h���X��Ԃ��B�����łȂ����NULL��Ԃ��B
 */
ARRAY_OFFSET *searchARRAY_OFFSET_LIST(ARRAY_OFFSET_LIST *array_offset_list, CSTLString *name);

/**
�Ώۂ̔z��I�t�Z�b�g���X�gtarget_array_offset_list�ɑ΂��āA�Ώۂ����菜������
�z��I�t�Z�b�g���X�gdelete_array_offset_list�̖��O�ɊY������z��I�t�Z�b�g����
�폜����B

@param target_array_offset_list �Ώۂ̔z��I�t�Z�b�g���X�g
@param delete_array_offset_list �Ώۂ����菜�������z��I�t�Z�b�g���X�g

@return �Ȃ�
 */
void minusArrayOffsetList(ARRAY_OFFSET_LIST *target_array_offset_list, ARRAY_OFFSET_LIST *delete_array_offset_list);

/**
�z��I�t�Z�b�g���X�g�ɔz��I�t�Z�b�g����ǉ�����B�������A�ϐ������d������̂ł���΁A�ǉ����Ȃ��B

@param target_array_offset_list �ǉ���̔z��I�t�Z�b�g���X�g
@param array_offset �ǉ�����z��I�t�Z�b�g���

@return �Ȃ�
 */
void ARRAY_OFFSET_LIST_push_back_ref_not_dup(ARRAY_OFFSET_LIST *target_array_offset_list, ARRAY_OFFSET *array_offset);

/**
AST�̃|�C���^���X�g�̓��e���o�͂�����B

@param astpointer_list AST�̃|�C���^���X�g

@return �Ȃ�
 */
void printASTPOINTER_LIST(ASTPOINTER_LIST *astpointer_list);
#endif
