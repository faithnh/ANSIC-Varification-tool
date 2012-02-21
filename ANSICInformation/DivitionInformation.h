/*!
  @brief ���̃t�@�C���́A���Z�E��]�Z�����o���邽�߂Ɏg�p����̂ɕK�v�ȏ����擾���邽�߂̖��߂��܂܂�Ă���B

  @file DivitionInformation.h
  @author faithnh
 */

 #ifndef DIVITION_INFORMATION_HEADDER
 #define DIVITION_INFORMATION_HEADDER

 #include<cstl/list.h>
 #include"AST.h"
 #include"Synbol.h"
 #include"../Library/CSTLString.h"
 #include"PointerArrayControl.h"
#include"FunctionInformation.h"
 /**
 ���Z����я�]�Z�Ɋւ�������i�[����B
 */
 typedef struct divition_information{
	AST *target_expression; ///�Ώۂ̎�
	int type; ///���Z����]���ǂ����̃^�C�v�@�O�F���Z���@�P�F��]��
	CSTLString *statement; ///���Z����я�]�ȉ��̎�
	ARRAY_OFFSET_LIST *identifiers; ///�����̎��ʎq�ꗗ
 } DIVITION_INFORMATION;

 /**
 DIVITION_INFORMATION�̃��X�g
 */
 CSTL_LIST_INTERFACE(DIVITION_INFORMATION_LIST, DIVITION_INFORMATION)

 /**
 ���Z����я�]�Z�Ɋւ�����𐶐�����B

 @param target_expression �Ώۂ̎��ւ�AST�m�[�h�̃A�h���X
 @param type ���Z����]���ǂ����̃^�C�v�@�O�F���Z���@�P�F��]��
 @param statement ���Z����я�]�ȉ��̎�
 @param identifiers �����̎��ʎq�ꗗ

 @return �������ꂽ���ւ̃A�h���X���Ԃ����
 */
 DIVITION_INFORMATION *new_DIVITION_INFORMATION(AST *target_expression, int type, CSTLString *statement, ARRAY_OFFSET_LIST *identifiers);

 /**
 ���Z����я�]�Z�Ɋւ�����𐶐�����B

 @param target_expression �Ώۂ̎��ւ�AST�m�[�h�̃A�h���X
 @param type ���Z����]���ǂ����̃^�C�v�@�O�F���Z���@�P�F��]��
 @param statement ���Z����я�]�ȉ��̎�
 @param identifiers �����̎��ʎq�ꗗ

 @return �������ꂽ���ւ̃A�h���X���Ԃ����
 */
 DIVITION_INFORMATION *new_DIVITION_INFORMATION_char(AST *target_expression, int type, char *statement, ARRAY_OFFSET_LIST *identifiers);

 /**
 �w�肳�ꂽ������Adiv_expr�����mod_expr�������A����ȉ��̎������Z����я�]�c�Ɋւ�����Ɋi�[����

 @param expression_ast �w�肳�ꂽ���ւ�AST�m�[�h�̃A�h���X
 @param function_information_list �֐��Ɋւ�����̃��X�g
 @param vtlist �ϐ��e�[�u�����X�g
 @param divition_information_list ���Z����я�]�Z�Ɋւ�������i�[���邽�߂̃��X�g
 @param target_expression �Ώۂ̎��ւ�AST�m�[�h�̃A�h���X
 @param ignore_ast_list �d���h�~�̂��߂Ɏg�p����AST�m�[�h�ւ̃��X�g

 @return �Ȃ�
 */
 void getDIVITION_INFORMATION_LIST(AST *expression_ast, FUNCTION_INFORMATION_LIST *function_information_list,
		 VARIABLE_TABLE_LIST *vtlist, DIVITION_INFORMATION_LIST *divition_information_list, AST *target_expression,
		 ASTPOINTER_LIST *ignore_ast_list);

 /**
 ���Z����я�]�Z�Ɋւ�����̃��X�g�̓��e���o�͂�����

 @param divition_information_list ���Z����я�]�Z�Ɋւ�����̃��X�g

 @return �Ȃ�
 */
 void printDIVITION_INFORMATION_LIST(DIVITION_INFORMATION_LIST *divition_information_list);
 #endif
