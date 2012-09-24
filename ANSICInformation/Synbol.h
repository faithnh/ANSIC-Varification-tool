/*!
  @brief ���̃t�@�C���́A�\����͂ɂ���Đ������ꂽ���ۍ\���؁iAST�j����A�ϐ��Etypedef�e�[�u���E�\���̃e�[�u����
  ���������邽�߂̖��߂��܂܂�Ă���B
  �Ƃ��ɁAtypedef�e�[�u���̐����́AC����̍\����͂ł͕K�{�ȏ����ł���B

  @file Synbol.h
  @author faithnh

 */
#ifndef C_SYNBOL_HEADDER
#define C_SYNBOL_HEADDER

#include <stdio.h>
#include <cstl/list.h>

#include"../Library/CSTLString.h"
#include "../Library/IdList.h"
#include "AST.h"

/**
�^��`�Ɋւ�����ŁABISON�ɂ��\����͎��̌^��`�̔F���ɗp������B
 */
typedef struct typedef_table {
	CSTLString *target_type;	///�Ώۂ̌^��`
	CSTLString *change_type;	///�^��`�Ŏg�p����^��
} TYPEDEF_TABLE;

/**
�v���O�������̕ϐ��Ɋւ�����ł���A���؎��������ɕϐ������ʂ���̂ɗp������B
 */
typedef struct variable_table {
	int enable_start;					///���̕ϐ����L���ł���J�n�̍s��
	int enable_end;						///���̕ϐ����L���ł���I���̍s��
	AST *declaration_location_address;	///���̕ϐ��̐錾�����Ă���AST�m�[�h�ւ̃A�h���X
	int block_level;					///���̕ϐ����錾���Ă���u���b�N���x��(�O���[�o���ϐ��Ȃ�O�A�֐����̃��[�J���ϐ��Ȃ�P�ƂȂ�j
	int block_id;						///���̕ϐ����錾���Ă���e�X�̃u���b�N�̎��ʎq
	IDLIST *idlist;						///���̕ϐ����錾���Ă���u���b�N���x������ю��ʎq�̗����Ɋւ�����ŁA�ϐ��X�R�[�v�����ʂ���̂Ɏg�p�����B
	CSTLString *type;					///���̕ϐ��̌^
	CSTLString *variable_name;			///���̕ϐ��̖��O
	AST *initiarizer;					///������`���ɑ΂���AST�m�[�h�ւ̃A�h���X
} VARIABLE_TABLE;

CSTL_LIST_INTERFACE(VARIABLE_TABLE_LIST, VARIABLE_TABLE);

/**
�\���̂Ɋւ�����ł���A�v���O�������̍\���̂̎��ʂ���̂ɗp������B
 */
typedef struct struct_table{
	int line;				///�s��
	CSTLString *type;		///�\���̂̃^�C�v union:������ struct:�\����
	CSTLString *struct_name;///�\���̖̂��O
	VARIABLE_TABLE_LIST *member_list;	///�\���̂̃����o�Ɋւ���ϐ����
} STRUCT_TABLE;

CSTL_LIST_INTERFACE(TYPEDEF_TABLE_LIST, TYPEDEF_TABLE);
CSTL_LIST_INTERFACE(STRUCT_TABLE_LIST, STRUCT_TABLE);
/**
�V����typedef�e�[�u���̃f�[�^�𐶐�������B
@param target_type typedef�̑Ώۂ̌^
@param change_type typedef�Ŋ��蓖�Ă���̐V�����^��
@return �V�����������ꂽtypedef�e�[�u���̃f�[�^�ւ̃A�h���X���Ԃ����B
*/
TYPEDEF_TABLE *new_TYPEDEF_TABLE(CSTLString *target_type, CSTLString *change_type);
/**
�V�����ϐ��e�[�u���̃f�[�^�𐶐�������B
@param enable_start ���̕ϐ��̗L���͈͂̎n�܂�̍s��
@param enable_end ���̕ϐ��̗L���͈͂̏I���̍s��
@param declaration_location_address ���̕ϐ���錾�����ꏊ������AST�̃A�h���X
@param block_level ���̕ϐ��̃u���b�N���x���i�O���[�o���ϐ��Ȃ�O�Ƃ��A�֐��̒��ł̒�`�Ȃ�P�A���̊֐�����for���Ȃǂ̃u���b�N���Ȃ��ł̐錾�Ȃ�Q�Ƃ���j
@param block_id �u���b�N���Ƃ�ID�i��{�I�ɂ�0����n��A�u���b�N���x���Q���Q��ڂɂ���ƁA�P�ƂȂ�j
@param idlist �u���b�N���Ƃ�ID�i����͕ϐ��X�R�[�v�����ʂ��邽�߂Ɏg�p����j
@param type �^��
@param variable_name �ϐ���
@param initializer ������`���ւ�AST�m�[�h

@return �V�����������ꂽ�ϐ��e�[�u���̃f�[�^�ւ̃A�h���X���Ԃ����B
*/
VARIABLE_TABLE *new_VARIABLE_TABLE(int enable_start, int enable_end, AST* declaration_location_address,
								   int block_level ,int block_id, IDLIST *idlist, CSTLString *type, CSTLString *variable_name, AST *initializer);

/**
�V�����\���̃e�[�u���̃f�[�^�𐶐�������(char������Ή�)�B
@param line �s��
@param type �^��(struct��union�̂����ꂩ�j
@param struct_name �\���̖̂��O
@param member_list �����o���X�g(�ϐ��e�[�u�����j
@return �V�����������ꂽ�\���̃e�[�u���̃f�[�^�ւ̃A�h���X���Ԃ����B
*/
STRUCT_TABLE *new_STRUCT_TABLE_with_char(int line, char *type, char *struct_name, VARIABLE_TABLE_LIST *member_list);

/**
�V����typedef�e�[�u���̃f�[�^�𐶐�������(char������Ή�)�B
@param target_type typedef�̑Ώۂ̌^
@param change_type typedef�Ŋ��蓖�Ă���̐V�����^��
@return �V�����������ꂽtypedef�e�[�u���̃f�[�^�ւ̃A�h���X���Ԃ����B
*/
TYPEDEF_TABLE *new_TYPEDEF_TABLE_with_char(char *target_type, char *change_type);
/**
�V�����ϐ��e�[�u���̃f�[�^�𐶐�������(char������Ή�)�B
@param enable_start ���̕ϐ��̗L���͈͂̎n�܂�̍s��
@param enable_end ���̕ϐ��̗L���͈͂̏I���̍s��
@param declaration_location_address ���̕ϐ���錾�����ꏊ������AST�̃A�h���X
@param block_level ���̕ϐ��̃u���b�N���x���i�O���[�o���ϐ��Ȃ�O�Ƃ��A�֐��̒��ł̒�`�Ȃ�P�A���̊֐�����for���Ȃǂ̃u���b�N���Ȃ��ł̐錾�Ȃ�Q�Ƃ���j
@param block_id �u���b�N���Ƃ�ID�i��{�I�ɂ�0����n��A�u���b�N���x���Q���Q��ڂɂ���ƁA�P�ƂȂ�j
@param idlist �u���b�N���Ƃ�ID�i����͕ϐ��X�R�[�v�����ʂ��邽�߂Ɏg�p����j
@param type �^��
@param variable_name �ϐ���
@param initializer ������`���ւ�AST�m�[�h

@return �V�����������ꂽ�ϐ��e�[�u���̃f�[�^�ւ̃A�h���X���Ԃ����B
*/
VARIABLE_TABLE *new_VARIABLE_TABLE_with_char(int enable_start, int enable_end, AST* declaration_location_address,
								   int block_level ,int block_id,IDLIST *idlist, char *type, char *variable_name, AST *initializer);

/**
�V�����\���̃e�[�u���̃f�[�^�𐶐�������B
@param line �s��
@param type �^��(struct��union�̂����ꂩ�j
@param struct_name �\���̖̂��O
@param member_list �����o���X�g(�ϐ��e�[�u�����j
@return �V�����������ꂽ�\���̃e�[�u���̃f�[�^�ւ̃A�h���X���Ԃ����B
*/
STRUCT_TABLE *new_STRUCT_TABLE(int line, CSTLString *type, CSTLString *struct_name, VARIABLE_TABLE_LIST *member_list);

/**
�w�肵��AST�m�[�h����Q�Ƃ��A����typedef�錾�̏ꍇ�́Atypedef�e�[�u���ɓ����B
@param typedef_table_list typedef�e�[�u��
@param typelist �^���X�g�ւ�AST�m�[�h
@param identifier ���ʂւ�AST�m�[�h
@return �Ȃ�
*/
void getTYPEDEF_TABLE_DATA(TYPEDEF_TABLE_LIST *typedef_table_list, AST *typelist, AST *identifier);

/**
�w�肵��typedef�e�[�u���̃��X�g����Q�Ƃ��A�w�肳�ꂽ�g�[�N���Ɉ�v����悤��typedef�e�[�u���f�[�^�����݂��邩�ǂ������ׂ�B
�����A������΁A���e���w�肳�ꂽ�g�[�N���ŁA���O��TYPE_NAME�ł���AST�m�[�h�𐶐����A����ւ̃A�h���X��Ԃ��B
@param typedef_table_list �w�肵��typedef�e�[�u���̃��X�g
@param token �w�肳�ꂽ�g�[�N��
@return �������ꂽAST�m�[�h�ւ̃A�h���X��Ԃ��B
*/
AST *getTYPEDEFfromAST(TYPEDEF_TABLE_LIST *typedef_table_list, char *token, int line);
/**
typedef�e�[�u���̃��X�g�ɓo�^����Ă�����̂��A���̂悤�Ȍ`���ŏo�͂�����B

target_type change_type

@param typedef_table_list �o�͑Ώۂ�typedef�e�[�u���̃��X�g
@return �Ȃ�
*/
void printTYPEDEF_TABLE_LIST(TYPEDEF_TABLE_LIST *typedef_table_list);

/** �w�肳�ꂽAST�m�[�h����A�\���̃e�[�u�����X�g�ɍ\���̃f�[�^��o�^������B
@param struct_table_list �o�^��̍\���̃e�[�u�����X�g
@param ast_data �w�肳�ꂽAST�m�[�h
@return �Ȃ�

*/
void getSTRUCT_TABLE_DATA(STRUCT_TABLE_LIST *struct_table_list, AST *ast_data);

/** �\���̃e�[�u�����X�g�ɓ�����`���Ȃ����ǂ����𒲂ׂ�B
@param struct_table_list �����Ώۂ̍\���̃e�[�u�����X�g
@param target �������镶����
@return ������ꂽ��A�P��Ԃ��A�����łȂ���΂O��Ԃ��B
*/
int find_STRUCT_TABLE_DATA(STRUCT_TABLE_LIST *struct_table_list, CSTLString *target);

/** �w�肳�ꂽAST�m�[�h����A�\���̃f�[�^���쐬�����A�\���̃e�[�u���̃��X�g�֓o�^������B
@param ast_data �w�肳�ꂽAST�m�[�h
@param struct_table_data �o�^��̍\���̃e�[�u�����X�g
@return �Ȃ�

*/
void getSTRUCT_DATA(AST *ast_data, STRUCT_TABLE_LIST *struct_table_data);

/** �w�肳�ꂽAST�m�[�h����A�����o���X�g�𐶐�����B
@param member_list �o�^�Ώۂ̃����o���X�g
@param ast_data �w�肳�ꂽAST�m�[�h
@return �쐬���ꂽ�\���̃f�[�^�ւ̃A�h���X��ԋp����

*/
void getMemberList(VARIABLE_TABLE_LIST *member_list, AST *ast_data);

/** �w�肳�ꂽAST�m�[�h����Adeclarator��T���A�������������w�肵���^�̕ϐ��Ƃ��ĕϐ����X�g�ɓo�^����B
@param type �w�肵���^
@param ast_data �w�肳�ꂽAST�m�[�h
@param member_list �o�^��̕ϐ����X�g
@param enable_start �ϐ��X�R�[�v�̗L���͈͂̊J�n
@param enable_end �ϐ��X�R�[�v�̗L���͈͂̏I���
@param block_level ���̕ϐ��̃u���b�N���x��
@param block_id �u���b�N�����ʂ��邽�߂̎��ʔԍ�
@param declaration_location_address ���̐錾���̂�AST�ւ̃A�h���X(���؎��̐����ɕK�v)

@return �Ȃ�
*/
void getDeclaratorFromAST(char const *type, AST *ast_data, VARIABLE_TABLE_LIST *member_list,
						  int enable_start, int enable_end ,int block_level, int block_id, AST* declaration_location_address);

/**
�\���̃e�[�u���̃��X�g�̓��e���o�͂�����B
@param struct_table_list �o�͑Ώۂ̍\���̃e�[�u���̃��X�g
@return �Ȃ�

*/
void printSTRUCT_TABLE_LIST(STRUCT_TABLE_LIST *struct_table_list);

/**
�Ώۂ�AST�m�[�h����ϐ��e�[�u���̃��X�g��o�^����B
@param variable_table_list �ϐ��e�[�u���̃��X�g
@param ast_data �Ώۂ�AST�m�[�h

@return �Ȃ�
*/
void getVARIABLE_TABLE_LIST(VARIABLE_TABLE_LIST *variable_table_list, AST *ast_data);

/**
�֐��̃p�����[�^���X�g������AST�m�[�h����Aparameter_declaration�������A��������ϐ��e�[�u���̃��X�g�ɓo�^������B
@param variable_table_list �ϐ��e�[�u���̃��X�g
@param ast_data �Ώۂ�AST�m�[�h
@param enable_start �L���͈͂̊J�n������AST�m�[�h�̃A�h���X
@param enable_end �L���͈͂̏I��������AST�m�[�h�̃A�h���X
@return �Ȃ�
*/
void getParameterData(VARIABLE_TABLE_LIST *variable_table_list, AST *ast_data, AST *enable_start, AST *enable_end);

/**
�Ώۂ�AST�m�[�h����֐���T���A�֐����̈�����ϐ��e�[�u���̃��X�g�ɓo�^����B
@param variable_table_list �ϐ��e�[�u���̃��X�g
@param ast_data �Ώۂ�AST�m�[�h
@return �Ȃ�
*/
void getParameterVARIABLE_TABLE_LIST(VARIABLE_TABLE_LIST *variable_table_list, AST *ast_data);
/**
�ϐ��e�[�u���̃��X�g�̓��e���o�͂�����B
@param variable_table_list �o�͑Ώۂ̕ϐ��e�[�u���̃��X�g
@return �Ȃ�

*/
void printVARIABLE_TABLE_LIST(VARIABLE_TABLE_LIST *variable_table_list);

/**
�ϐ��e�[�u������A�|�C���^�̎�������єz��̎������擾����B
@param variable_table_data �ϐ��e�[�u���̃��X�g
@param output_pointer_level �o�͂����|�C���^���x��
@param output_array_level �o�͂����z�񃌃x��
@return �Ȃ�
*/
void getPointerLevelAndArrayLevelFromVARIABLE_TABLE(VARIABLE_TABLE *variable_table_data, int *output_pointer_level, int *output_array_level);

/**
�Ώۂ̎��ʎq�̃|�C���^�̎�������єz��̎������擾����B
@param target_identifier �Ώۂ̎��ʎq
@param output_pointer_level �o�͂����|�C���^���x��
@param output_array_level �o�͂����z�񃌃x��
@return �Ȃ�
*/
void getPointerLevelAndArrayLevel(CSTLString *target_identifier, int *output_pointer_level, int *output_array_level);


/**
�ϐ��e�[�u�����X�gvariable_table_list����A�w�肵���ϐ��X�R�[�v��IDLIST target_idlist��target_string�ɊY���悤�ȕϐ��e�[�u���ւ̃A�h���X��Ԃ��B

@param target_idlist �w�肵���ϐ��X�R�[�v��IDLIST
@param target_string �Ώۂ̕ϐ���
@param variable_table_list �ϐ��e�[�u�����X�g

@return ��L�̏������猩�����ϐ��e�[�u���ւ̃A�h���X��Ԃ��B������Ȃ����NULL��Ԃ��B
*/
VARIABLE_TABLE *searchVARIABLE_TABLE_LIST(IDLIST *target_idlist, CSTLString *target_string, VARIABLE_TABLE_LIST* variable_table_list);

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
�ϐ���񂩂�^�����܂񂾂��̂𕶎���ŏo�͂�����
@param variable_name �ϐ���
@param variable_table �Ώۂ̕ϐ����
@return �擾�����������Ԃ�
 */
CSTLString *getTypeOfVariable(CSTLString *variable_name , VARIABLE_TABLE *variable_table);
#endif

