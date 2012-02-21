/*!
  @brief ���̃t�@�C���́A����������֌W�̊֐�����A����������֌W�̏����擾���閽�߂��܂܂�Ă���B
  ��̓I�ɂ́AC����v���O������ɂ���free�֐�����A�ǂ̕ϐ����������Ă��邩�ǂ����ɂ��Ď擾����B

  @file FreeMemInfo.h
  @author faithnh

 */

 #ifndef FREEMEMINFO_HEADDER
 #define FREEMEMINFO_HEADDER

 #include "PointerArrayControl.h"
 #include "FunctionInformation.h"

/**
�������m�ۊ֌W�Ɋ֌W����ϐ����܂܂��B����́A����������֐��̋����ɍ��킹�Č��؎���ǉ����邽�߂ɗp����B
 */
 typedef struct freemem_info{
	ARRAY_OFFSET_LIST * free_variable; ///�����̕ϐ��Ɋւ���I�t�Z�b�g���X�g
 } FREEMEMINFO;

 /**
 �V��������������֌W�̏��𐶐�����B

 @param free_variable �V���������̕ϐ��Ɋւ���I�t�Z�b�g���X�g

 @return �V�����������ꂽ����������֌W�̏��ւ̃A�h���X��Ԃ��B
 */
 FREEMEMINFO * new_FREEMEMINFO(ARRAY_OFFSET_LIST *free_variable);


 /**
 �Ώۂ̊֐��ւ�AST�m�[�h����free�֐��������A����Ɋւ�������擾����B

 @param freememinfo �擾��̃���������֌W�̏��
 @param call_function �Ώۂ̊֐��ւ�AST�m�[�h
 @param function_information_list �֐��Ɋւ�����̃��X�g
 @param vtlist �ϐ��e�[�u���̏��
 @param target_statement �Ώۂ̊֐����ʒu���Ă��鎮�ւ�AST�m�[�h

 @return �Ȃ�
 */

 void getFreememInfo(FREEMEMINFO **freememinfo, AST *call_function, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist, AST *target_statement);

 /**
 �w�肵������������֌W�̏����o�͂���B

 @param freememinfo �o�͂��郁��������֌W�̏��

 @return �Ȃ�
 */
 void printFREEMEMINFO(FREEMEMINFO *freememinfo);

 #endif
