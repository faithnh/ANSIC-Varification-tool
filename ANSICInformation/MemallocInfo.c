#include "MemallocInfo.h"

//������̒���
#define STRLEN 256

//sizeof�Œ��g�������Ƃ邽�߂ɏ��O���郊�X�g�̐�
#define EXCEPT_SIZEOF_SIZE 3

//���������ꍇ
#define SUCCESS 1
//���s�����ꍇ
#define FAILED 0

/**
���������蓖�ĂɊւ�������i�[���邽�߂̍\���̂̃f�[�^�𐶐�������B
@param sizeof_type		sizeof�̌^��
@param realloc_target	realloc���̃^�[�Q�b�g�^�C�v
@param size				malloc���̃T�C�Y

@return ���������蓖�ĂɊւ�������i�[���邽�߂̍\���̂ւ̃A�h���X��Ԃ��B
*/
MEMALLOC_INFO *new_MEMALLOC_INFO_char(char *sizeof_type, ARRAY_OFFSET_LIST *realloc_target, char *size){
	CSTLString *sizeof_type_cstl = CSTLString_new();
	CSTLString_assign(sizeof_type_cstl, sizeof_type);

	CSTLString *size_cstl = CSTLString_new();
	CSTLString_assign(size_cstl, size);

	return new_MEMALLOC_INFO(sizeof_type_cstl, realloc_target, size_cstl);
}

/**
���������蓖�ĂɊւ�������i�[���邽�߂̍\���̂̃f�[�^�𐶐�������B
@param sizeof_type		sizeof�̌^��
@param realloc_target	realloc���̃^�[�Q�b�g�^�C�v
@param size				malloc���̃T�C�Y

@return ���������蓖�ĂɊւ�������i�[���邽�߂̍\���̂ւ̃A�h���X��Ԃ��B
*/
MEMALLOC_INFO *new_MEMALLOC_INFO(CSTLString *sizeof_type, ARRAY_OFFSET_LIST *realloc_target, CSTLString *size){
	//�V�������������蓖�ĂɊւ�����𐶐�����
	MEMALLOC_INFO *new_memalloc_info = (MEMALLOC_INFO*)malloc(sizeof(MEMALLOC_INFO));

	//�K�v�ȏ��������Ă���
	new_memalloc_info->sizeof_type = sizeof_type;
	new_memalloc_info->realloc_target = realloc_target;
	new_memalloc_info->size = size;

	//�V�������������蓖�ĂɊւ�����ւ̃A�h���X��Ԃ�
	return new_memalloc_info;
}

/**
�w�肳�ꂽAST�m�[�h���烁�����m�ۊ֌W�̊֐��Ɋւ�������擾����B
@param root �w�肳�ꂽAST�m�[�h
@param vtlist realloc��realloc�̃^�[�Q�b�g���̃I�t�Z�b�g�����擾����̂ɕK�v�ȃv���O�����̕ϐ����X�g
@return �������m�ۊ֌W�̍\���̂ւ̃A�h���X��Ԃ��B
*/
MEMALLOC_INFO *memoryAllocationAnarysis(AST *root, VARIABLE_TABLE_LIST *vtlist){

		MEMALLOC_INFO *memalloc_info = NULL;

		CSTLString *sizeof_type = CSTLString_new();
		CSTLString *constant = CSTLString_new();
		ARRAY_OFFSET_LIST *realloc_target = ARRAY_OFFSET_LIST_new();

		//�Ăяo�����֐������擾����
		CSTLString *function_name = CSTLString_new();
		getStringFromAST(function_name, ASTList_data(ASTList_begin(root->children)));

		//�Ăяo�����֐�����malloc�ł���ꍇ
		if(CSTLString_compare_with_char(function_name, "malloc") == 0){

			//malloc�̏����擾����
			getMallocInformation(root, sizeof_type, constant);

			memalloc_info = new_MEMALLOC_INFO_char((char *)CSTLString_c_str(sizeof_type), realloc_target, (char *)CSTLString_c_str(constant));
		}
		//�Ăяo�����֐�����calloc�ł���ꍇ
		else if(CSTLString_compare_with_char(function_name, "calloc") == 0){
			//malloc�̏����擾����
			getCallocInformation(root, sizeof_type, constant);

			memalloc_info = new_MEMALLOC_INFO_char((char *)CSTLString_c_str(sizeof_type), realloc_target, (char *)CSTLString_c_str(constant));
		}
		//�Ăяo�����֐�����realloc�ł���ꍇ
		else if(CSTLString_compare_with_char(function_name, "realloc") == 0){
			//realloc�̏����擾����
			getReallocInformation(root, vtlist, sizeof_type, constant, realloc_target);

			memalloc_info = new_MEMALLOC_INFO_char((char *)CSTLString_c_str(sizeof_type), realloc_target , (char *)CSTLString_c_str(constant));
		}
		CSTLString_delete(function_name);

		return memalloc_info;
}


/**
malloc�֐��Ɋւ�������擾����B
@param root
@param sizeof_type sizeof�ł̌^
@param constant sizeof�ȊO�ł̎��i���Ȃ킿�m�ۂ��Ă���^�ɑ΂���T�C�Y�ɑ�������j

@return �Ȃ�
*/
void getMallocInformation(AST *root, CSTLString *sizeof_type, CSTLString *constant)
{
	//sizeof�������������Ă��邩�ǂ����̃t���O
	int valid_sizeof_flag;
	//��������AST�m�[�h�����擾����
	AST *argument;
	getArgumentAST(&argument, root, 1);
	//sizeof��T���A�^���擾����B���̂Ƃ��Asizeof���Q��ނ���ꍇ�isizeof�ɕs�s��������ꍇ�j��0��Ԃ��A�����łȂ��ꍇ��1��Ԃ�
	valid_sizeof_flag = searchSizeof(sizeof_type, argument);

	//sizeof�̒�`�ɕs�s�����Ȃ����
	if(valid_sizeof_flag){
		//������A�T�C�Y�����������擾����
		getMallocMaxsize(constant, argument);
		//�����Asizeof�̌^�������擾�ł��Ȃ������ꍇ��null�Ƃ���B
		if(CSTLString_size(sizeof_type) == 0){
			CSTLString_assign(sizeof_type, "null");
		}
	}
	//sizeof�ɕs�s���Ȏg���������Ă���ꍇ
	else{
		//�s����malloc�̎g�����ł���ƃG���[���o�͂��A�����I��������
		fprintf(stderr,"line:%d:Invalid malloc", root->line);
		exit(1);
	}

}
/**
calloc�֐��Ɋւ�������擾����B
@param root
@param sizeof_type sizeof�ł̌^
@param constant sizeof�ȊO�ł̎��i���Ȃ킿�m�ۂ��Ă���^�ɑ΂���T�C�Y�ɑ�������j

@return �Ȃ�
*/
void getCallocInformation(AST *root, CSTLString *sizeof_type, CSTLString *constant)
{
	char exception_sizeof[][STRLEN] = {"sizeof","(",")"};

	//����������sizeof_type���擾����
	getArgumentStringEnableExcept(sizeof_type, root, 2, EXCEPT_SIZEOF_SIZE, exception_sizeof);

	//����������constant���擾����
	getArgumentString(constant, root, 1);

}

/**
realloc�֐��Ɋւ�������擾����B
@param root �Ώۂ�AST�m�[�h
@param vtlist �Ώۂ̃v���O�����̕ϐ����X�g
@param sizeof_type sizeof�ł̌^
@param constant sizeof�ȊO�ł̎��i���Ȃ킿�m�ۂ��Ă���^�ɑ΂���T�C�Y�ɑ�������j
@param realloc_target realloc���ΏۂƂ���I�t�Z�b�g���

@return �Ȃ�
*/
void getReallocInformation(AST *root,VARIABLE_TABLE_LIST *vtlist, CSTLString *sizeof_type, CSTLString *constant, ARRAY_OFFSET_LIST *realloc_target){
	//���A��������AST
	AST *argument1, *argument2;
	//sizeof�������������Ă��邩�ǂ����̃t���O
	int valid_sizeof_flag;

	//realloc_target�ŃI�t�Z�b�g���X�g���擾����Ƃ��ɁA�d�������I�t�Z�b�g���̎擾��h�~���邽�߂�AST�A�h���X���X�g�𐶐�����
	ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();
	//switch_mode���g�p���邽�߂̕ϐ��i������d�������I�t�Z�b�g���̎擾��h�~���邽�߂ɂ���j
	int switch_mode = 0;

	//�֐���AST�m�[�hroot�������������AST���擾���Arealloc_target�ɂ�����I�t�Z�b�g�����擾����
	getArgumentAST(&argument1, root, 1);
	getArgumentOffsetInfo:(argument1, vtlist, ignore_ast_list, realloc_target, root, &switch_mode);
	//�֐���AST�m�[�hroot�����������AST���擾
	getArgumentAST(&argument2, root, 2);

	//�������̎�����sizeof��T���A�^���擾����B���̂Ƃ��Asizeof���Q��ނ���ꍇ�isizeof�ɕs�s��������ꍇ�j��0��Ԃ��A�����łȂ��ꍇ��1��Ԃ�
	valid_sizeof_flag = searchSizeof(sizeof_type, argument2);

	//sizeof�̒�`�ɕs�s�����Ȃ����
	if(valid_sizeof_flag){
		//�������̎�����A�T�C�Y�����������擾����
		getMallocMaxsize(constant, argument2);
		//�����Asizeof�̌^�������擾�ł��Ȃ������ꍇ��null�Ƃ���B
		if(CSTLString_size(sizeof_type) == 0){
			CSTLString_assign(sizeof_type, "null");
		}
	}
	//sizeof�ɕs�s���Ȏg���������Ă���ꍇ
	else{
		//�s����malloc�̎g�����ł���ƃG���[���o�͂��A�����I��������
		fprintf(stderr,"line:%d:Invalid realloc", root->line);
		exit(1);
	}

	//ignore_ast_list�̉��
	ASTPOINTER_LIST_delete(ignore_ast_list);

}

/**
�w�肵������AST�ɑ΂��āAsizeof��T�����A���̌^����sizeof_type�Ŏ擾����B�����A���ɈقȂ�Q��ނ�sizeof��`������΁A�T���t���O�͎��s����B
�܂��A������Ȃ���΁Asizeof_type�͉����w�肵�Ă��Ȃ��܂܂̏�Ԃł���B
@param sizeof_type �o�͂���sizeof�̌^��
@param root �T���Ώۂ̎��ւ�AST�m�[�h
@return �Ȃ�
*/
int searchSizeof(CSTLString *sizeof_type, AST *root){
	//AST�̎q�m�[�h���Q�Ƃ����邽�߂̃C�e���[�^
	ASTListIterator ast_iterator;
	char exception_sizeof[EXCEPT_SIZEOF_SIZE][STRLEN] = {"sizeof","(",")"};
	int flag = SUCCESS;

	if(CSTLString_compare_with_char(root->name, "sizeof_expression") == 0){
		//sizeof�̃^�C�v���擾����
		CSTLString *tmp_sizeof_type = CSTLString_new();
		getStringFromASTEnableExcept(tmp_sizeof_type ,root, EXCEPT_SIZEOF_SIZE, exception_sizeof);

		//��x�ڂ̒�`�ł͂Ȃ��ꍇ�i����͉�����`���Ă��Ȃ��̂ŁA������̒������O�ł���j�Asizeof�̌^���`����
		if(CSTLString_size(sizeof_type)==0 ){
			CSTLString_assign(sizeof_type, CSTLString_c_str(tmp_sizeof_type));
		}
		//��x�ڂ̒�`�ł���ꍇ
		else{
			//�����^���̒�`�ł���ꍇ�́A�G���[�Ƃ��ďI��������
			if(CSTLString_compare(tmp_sizeof_type, sizeof_type) != 0){
				CSTLString_delete(tmp_sizeof_type);
				return FAILED;
			}
		}
		CSTLString_delete(tmp_sizeof_type);

	}

	//AST�̎q�m�[�h���Q�Ƃ�����
	for(ast_iterator = ASTList_begin(root->children);
		ast_iterator != ASTList_end(root->children);
		ast_iterator = ASTList_next(ast_iterator)){

		flag = searchSizeof(sizeof_type, ASTList_data(ast_iterator));
		if(flag == FAILED){
			break;
		}
	}
	return flag;
}
/**
getMallocMaxsize�̓�������

@param constant �擾����sizeof�ȊO�ł̎��i���Ȃ킿�m�ۂ��Ă���^�ɑ΂���T�C�Y�ɑ�������j
@param root malloc�Ȃǂ̊֐����̎��ւ�AST�m�[�h
@return �Ȃ�
*/
void getMallocMaxsize_Internal(CSTLString *constant,AST *root){
	//AST�̎q�m�[�h���Q�Ƃ����邽�߂̃C�e���[�^
	ASTListIterator ast_iterator;

	//sizeof_expression�ł���ꍇ�́A���̕����͂P�ɒ����A�����艺�ʂ͎Q�Ƃ��Ȃ�
	if(CSTLString_compare_with_char(root->name, "sizeof_expression") == 0){
		CSTLString_append(constant, "1 ");
		return;
	}
	//�����łȂ��ꍇ
	else{
		//�����A���[�t�m�[�h�ł���ꍇ�i�qAST�m�[�h�������Ă��Ȃ��ꍇ�j
		if(ASTList_size(root->children) == 0){
			//���[�t�m�[�h�̒��g��ǉ�����
			CSTLString_append(constant, CSTLString_c_str(root->content));
			CSTLString_append(constant, " ");
		}
	}

	//AST�̎q�m�[�h���Q�Ƃ�����
	for(ast_iterator = ASTList_begin(root->children);
		ast_iterator != ASTList_end(root->children);
		ast_iterator = ASTList_next(ast_iterator)){

		getMallocMaxsize_Internal(constant, ASTList_data(ast_iterator));

	}
}
/**
malloc�Ȃǂ̊֐����̎�����A�m�ۂ����T�C�Y�����������擾����B����́Asizeof(�^)���P�ɏ��������Ȃ���A�����o�͂����邱�Ƃōs���Ă���B

@param constant �擾����sizeof�ȊO�ł̎��i���Ȃ킿�m�ۂ��Ă���^�ɑ΂���T�C�Y�ɑ�������j
@param root malloc�Ȃǂ̊֐����̎��ւ�AST�m�[�h
@return �Ȃ�
*/
void getMallocMaxsize(CSTLString *constant,AST *root){
	//constant�̒��g����ɂ���
	CSTLString_assign(constant, "");
	//sizeof��1�ɕϊ����Ȃ���Aroot��艺�ʂ̃m�[�h�̏����擾����
	getMallocMaxsize_Internal(constant, root);

	//�����A�Ō�ɔ��p�X�y�[�X�������Ă�����폜����
	if(CSTLString_size(constant) > 0 && *CSTLString_at(constant, CSTLString_size(constant) - 1) == ' '){
		CSTLString_pop_back(constant);
	}
}

/*
�w�肵���������m�ۏ��memalloc_info�̓��e���o�͂���B

@param memalloc_info �o�͑Ώۂ̃������m�ۏ��

@return �Ȃ�
*/
void printMEMALLOC_INFO(MEMALLOC_INFO *memalloc_info){
	printf("------MALLOC_OFFSET_INFO------\n\n");
	printf("SIZEOF_TYPE = \"%s\"\n",CSTLString_c_str(memalloc_info->sizeof_type));
	printf("------REALLOC_TARGET_TYPE_INFO-----\n\n");
	printARRAY_OFFSET_LIST(memalloc_info->realloc_target);
	printf("-----------------------------------\n\n");
	printf("SIZE = \"%s\"\n",CSTLString_c_str(memalloc_info->size));
	printf("------------------------------\n\n");

}
