 #include "FreeMemInfo.h"

 /**
 �V��������������֌W�̏��𐶐�����B

 @param free_variable �V���������̕ϐ��Ɋւ���I�t�Z�b�g���X�g

 @return �V�����������ꂽ����������֌W�̏��ւ̃A�h���X��Ԃ��B
 */
 FREEMEMINFO * new_FREEMEMINFO(ARRAY_OFFSET_LIST *free_variable){
	FREEMEMINFO *new_freememinfo = (FREEMEMINFO*)malloc(sizeof(FREEMEMINFO));

	new_freememinfo->free_variable = free_variable;

	return new_freememinfo;
 }

 /**
 �Ώۂ̊֐��ւ�AST�m�[�h����free�֐��������A����Ɋւ�������擾����B

 @param freememinfo �擾��̃���������֌W�̏��
 @param call_function �Ώۂ̊֐��ւ�AST�m�[�h
 @param function_information_list �֐��Ɋւ�����̃��X�g
 @param vtlist �ϐ��e�[�u���̏��
 @param target_statement �Ώۂ̊֐����ʒu���Ă��鎮�ւ�AST�m�[�h

 @return �Ȃ�
 */

 void getFreememInfo(FREEMEMINFO **freememinfo, AST *call_function, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist, AST *target_statement){

	//�֐������擾����
	//�Ăяo�����֐������擾����
	CSTLString *function_name = CSTLString_new();
	getStringFromAST(function_name, ASTList_data(ASTList_begin(call_function->children)));
	//�����֐�����free�ł���ꍇ
	if(CSTLString_compare_with_char(function_name, "free") == 0){
		//�������邽�߂�AST�m�[�h���X�g
		ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();

		ARRAY_OFFSET_LIST *freemem_argument_info = ARRAY_OFFSET_LIST_new();

		int switch_mode = 0;
		//free�̑��������擾����B
		AST *argument1;
		getArgumentAST(&argument1, call_function, 1);
		//�������̓��e����A����������֌W�̏����擾����
		getArgumentOffsetInfo(argument1, function_information_list, vtlist, ignore_ast_list, freemem_argument_info, target_statement, &switch_mode);

		//�����A���炩�C���ł����ꍇ
		if(ARRAY_OFFSET_LIST_size(freemem_argument_info) > 0){
			*freememinfo = new_FREEMEMINFO(freemem_argument_info);
		}
	}
 }

 /**
 �w�肵������������֌W�̏����o�͂���B

 @param freememinfo �o�͂��郁��������֌W�̏��

 @return �Ȃ�
 */
 void printFREEMEMINFO(FREEMEMINFO *freememinfo){
	printf("------FREE_INFO------\n\n");
	printARRAY_OFFSET_LIST(freememinfo->free_variable);
	printf("---------------------\n\n");
 }
