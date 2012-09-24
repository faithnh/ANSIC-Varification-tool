#include "Synbol.h"
#include "../Library/Stack_int.h"

CSTL_LIST_IMPLEMENT(TYPEDEF_TABLE_LIST, TYPEDEF_TABLE);
CSTL_LIST_IMPLEMENT(STRUCT_TABLE_LIST, STRUCT_TABLE);
CSTL_LIST_IMPLEMENT(VARIABLE_TABLE_LIST, VARIABLE_TABLE);

#define NOT_DEFINE_LINE -1
#define INIT_MAX_LINE -1
#define PROGRAM_START_LINE 1
#define NOT_DEFINE_BLOCK_LEVEL -1
#define NOT_DEFINE_BLOCK_ID -1
/**
�V����typedef�e�[�u���̃f�[�^�𐶐�������B
@param target_type typedef�̑Ώۂ̌^
@param change_type typedef�Ŋ��蓖�Ă���̐V�����^��
@return �V�����������ꂽtypedef�e�[�u���̃f�[�^�ւ̃A�h���X���Ԃ����B
*/
TYPEDEF_TABLE *new_TYPEDEF_TABLE(CSTLString *target_type, CSTLString *change_type){
	//typedef�e�[�u���̐���
	TYPEDEF_TABLE* new_typedef_table = (TYPEDEF_TABLE*)malloc(sizeof(TYPEDEF_TABLE));

	//typedef�e�[�u���ɁAtypedef�̑Ώۂ̌^��A���蓖�Ă���̐V�����^��������
	new_typedef_table->target_type = target_type;

	new_typedef_table->change_type = change_type;

	//typedef�e�[�u���̃f�[�^�̃A�h���X��Ԃ�
	return new_typedef_table;
}
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
								   int block_level ,int block_id, IDLIST *idlist, CSTLString *type, CSTLString *variable_name, AST *initializer){
	//�ϐ��e�[�u���̐���
	VARIABLE_TABLE *new_variable_table = (VARIABLE_TABLE*)malloc(sizeof(VARIABLE_TABLE));

	//�ϐ��e�[�u���ɁA�ϐ��̗L���͈͂̎n�܂�A�I���A�^���A�ϐ���������
	new_variable_table->enable_start = enable_start;

	new_variable_table->enable_end = enable_end;

	new_variable_table->declaration_location_address = declaration_location_address;

	new_variable_table->block_level = block_level;

	new_variable_table->block_id = block_id;

	new_variable_table->idlist = idlist;

	new_variable_table->type = type;

	new_variable_table->variable_name = variable_name;

	new_variable_table->initiarizer = initializer;

	//�ϐ��e�[�u���̃f�[�^�̃A�h���X��Ԃ�
	return new_variable_table;
}

/**
�V�����\���̃e�[�u���̃f�[�^�𐶐�������B
@param line �s��
@param type �^��
@param struct_name �\���̖�(struct��union�̂����ꂩ�j
@param member_list �����o���X�g(�ϐ��e�[�u�����j
@return �V�����������ꂽ�\���̃e�[�u���̃f�[�^�ւ̃A�h���X���Ԃ����B
*/
STRUCT_TABLE *new_STRUCT_TABLE(int line, CSTLString *type, CSTLString *struct_name, VARIABLE_TABLE_LIST *member_list){
	//�\���̃e�[�u���̐���
	STRUCT_TABLE *new_struct_table = (STRUCT_TABLE*)malloc(sizeof(STRUCT_TABLE));

	//�\���̃e�[�u���ɁA�s���A�^���A�\���̖��A�����o���X�g������
	new_struct_table->line = line;

	new_struct_table->type = type;

	new_struct_table->struct_name = struct_name;

	new_struct_table->member_list = member_list;

	//�\���̃e�[�u���̃f�[�^�̃A�h���X��Ԃ�
	return new_struct_table;
}
/**
�V�����\���̃e�[�u���̃f�[�^�𐶐�������(char������Ή�)�B
@param line �s��
@param type �^��(struct��union�̂����ꂩ�j
@param struct_name �\���̖̂��O
@param member_list �����o���X�g(�ϐ��e�[�u�����j
@return �V�����������ꂽ�\���̃e�[�u���̃f�[�^�ւ̃A�h���X���Ԃ����B
*/
STRUCT_TABLE *new_STRUCT_TABLE_with_char(int line, char *type, char *struct_name, VARIABLE_TABLE_LIST *member_list){
	//CSTLString�����̌^���ƍ\���̖̂��O��ݒ肷��
	CSTLString *CSTLtype = CSTLString_new();
	CSTLString *CSTLstruct_name = CSTLString_new();

	CSTLString_assign(CSTLtype, type);
	CSTLString_assign(CSTLstruct_name, struct_name);

	//�\���̃e�[�u���̐���
	STRUCT_TABLE *new_struct_table = new_STRUCT_TABLE(line, CSTLtype, CSTLstruct_name, member_list);

	//�\���̃e�[�u���̃f�[�^�̃A�h���X��Ԃ�
	return new_struct_table;
}

/**
�V����typedef�e�[�u���̃f�[�^�𐶐�������(char������Ή�)�B
@param target_type typedef�̑Ώۂ̌^
@param change_type typedef�Ŋ��蓖�Ă���̐V�����^��
@return �V�����������ꂽtypedef�e�[�u���̃f�[�^�ւ̃A�h���X���Ԃ����B
*/
TYPEDEF_TABLE *new_TYPEDEF_TABLE_with_char(char *target_type, char *change_type){

	//CSTLString������typedef�̑Ώۂ̌^��typedef�Ŋ��蓖�Ă���̐V�����^����ݒ肷��
	CSTLString *CSTLtarget_type = CSTLString_new();
	CSTLString *CSTLchange_type = CSTLString_new();

	CSTLString_assign(CSTLtarget_type, target_type);
	CSTLString_assign(CSTLchange_type, change_type);

	//typedef�e�[�u���̐���
	TYPEDEF_TABLE *new_typedef_table = new_TYPEDEF_TABLE(CSTLtarget_type, CSTLchange_type);

	//typedef�e�[�u���̃f�[�^�̃A�h���X��Ԃ�
	return new_typedef_table;
}

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
								   int block_level ,int block_id,IDLIST *idlist, char *type, char *variable_name, AST *initializer){

	//CSTLString�����̌^���ƕϐ�����ݒ肷��
	CSTLString *CSTLtype = CSTLString_new();
	CSTLString *CSTLvariable_name = CSTLString_new();

	CSTLString_assign(CSTLtype, type);
	CSTLString_assign(CSTLvariable_name, variable_name);

	//�ϐ��e�[�u���̐���
	VARIABLE_TABLE *new_variable_table = new_VARIABLE_TABLE(enable_start, enable_end, declaration_location_address, block_level, block_id, idlist, CSTLtype, CSTLvariable_name, initializer);


	//�ϐ��e�[�u���̃f�[�^�̃A�h���X��Ԃ�
	return new_variable_table;
}

/**
�w�肵��AST�m�[�h����Q�Ƃ��A����typedef�錾�̏ꍇ�́Atypedef�e�[�u���ɓ����B
@param typedef_table_list typedef�e�[�u��
@param typelist �^���X�g�ւ�AST�m�[�h
@param identifier ���ʂւ�AST�m�[�h
@return �Ȃ�
*/
void getTYPEDEF_TABLE_DATA(TYPEDEF_TABLE_LIST *typedef_table_list, AST *typelist, AST *identifier){
	CSTLString *identifier_str;
	//���O���X�g
	char except_list[4][256] = { "{", "}", "struct_declaration_list", "enumerator_list"};
	//typelist��AST����^���Ɋւ��镶����̏����擾����
	CSTLString *typelist_str = CSTLString_new();
	getStringFromASTEnableExcept(typelist_str, typelist, 4, except_list);

	//�����A�^���Ɋւ������typedef���܂܂ꂽ�ꍇ
	if(CSTLString_find(typelist_str, "typedef", 0) != CSTL_NPOS){
		//identifier��AST���犄�蓖�Č�̕ϐ������擾����
		identifier_str = CSTLString_new();
		getStringFromAST(identifier_str, identifier);

		//�^���Ɋւ��镶����̏�񂩂�Atypedef����菜��
		CSTLString_replace_string(typelist_str,"typedef ","");
		//�擾�����A�^���Ɋւ��镶����̏��ƁA���蓖�Č�̕ϐ�����o�^����typedef�e�[�u���̃f�[�^���쐬����
		TYPEDEF_TABLE *new_typedef_table = new_TYPEDEF_TABLE(typelist_str, identifier_str);
		//�쐬����typedef�e�[�u���̃f�[�^��typedef�e�[�u���ɓ����
		TYPEDEF_TABLE_LIST_push_back_ref(typedef_table_list, new_typedef_table);
	}
}

/**
�w�肵��typedef�e�[�u���̃��X�g����Q�Ƃ��A�w�肳�ꂽ�g�[�N���Ɉ�v����悤��typedef�e�[�u���f�[�^�����݂��邩�ǂ������ׂ�B
�����A������΁A���e���w�肳�ꂽ�g�[�N���ŁA���O��TYPE_NAME�ł���AST�m�[�h�𐶐����A����ւ̃A�h���X��Ԃ��B
�������Ȃ���΁A���O��IDENTIFIER�ł���AST�m�[�h�𐶐����A����ւ̃A�h���X��Ԃ��B
@param typedef_table_list �w�肵��typedef�e�[�u���̃��X�g
@param token �w�肳�ꂽ�g�[�N��
@param line �w�肳�ꂽ�s��
@return �������ꂽAST�m�[�h�ւ̃A�h���X��Ԃ��B
*/

AST *getTYPEDEFfromAST(TYPEDEF_TABLE_LIST *typedef_table_list, char *token, int line){
	//�w�肳�ꂽ�g�[�N���ƈ�v����悤��typedef�e�[�u���f�[�^�����݂��邩�ǂ����̃t���O
	int find_typedef_type = 0;

	//�V����AST�m�[�h
	AST* new_ast_node;
	//�w�肵��typedef�e�[�u���̃��X�g����A�w�肳�ꂽ�g�[�N���Ɉ�v����悤��typedef�e�[�u���f�[�^�����݂��邩�ǂ������ׂ�B
	TYPEDEF_TABLE_LISTIterator p;
	for(p = TYPEDEF_TABLE_LIST_begin(typedef_table_list); p != TYPEDEF_TABLE_LIST_end(typedef_table_list); p = TYPEDEF_TABLE_LIST_next(p)){
		//���݂���΁A���݂���Ƃ����t���O��Ԃ��A���ׂ��Ƃ��I��点��B
		if(CSTLString_compare_with_char((TYPEDEF_TABLE_LIST_data(p))->change_type, token) == 0){
			find_typedef_type = 1;
			break;
		}
	}

	//���݂��邩�ǂ����̃t���O�𒲂ׁA�������݂���΁A���O��TYPE_NAME�ł���A���e���w�肳�ꂽ�g�[�N���̂悤��AST�m�[�h�𐶐�����B
	if(find_typedef_type == 1){
		new_ast_node = new_AST("TYPE_NAME", token, line);
	}
	//���݂��Ȃ���΁A���O��IDENTIFIER�ł���A���e���w�肳�ꂽ�g�[�N���̂悤��AST�m�[�h�𐶐�����B
	else{
		new_ast_node = new_AST("IDENTIFIER", token, line);
	}
	//�������ꂽAST�m�[�h�ւ̃A�h���X��ԋp����B
	return new_ast_node;

}

/**
typedef�e�[�u���̃��X�g�ɓo�^����Ă�����̂��o�͂�����B

@param typedef_table_list �o�͑Ώۂ�typedef�e�[�u���̃��X�g
@return �Ȃ�
*/
void printTYPEDEF_TABLE_LIST(TYPEDEF_TABLE_LIST *typedef_table_list){
	TYPEDEF_TABLE_LISTIterator p;
	int counter = 1;
	printf("---------------TYPEDEF_TABLE---------------\n\n");
	//typedef�e�[�u���̃��X�g��S�ĎQ�Ƃ���B
	for(p = TYPEDEF_TABLE_LIST_begin(typedef_table_list); p != TYPEDEF_TABLE_LIST_end(typedef_table_list); p = TYPEDEF_TABLE_LIST_next(p)){
		//target_type change_type�̏��ɏo�͂�����B
		printf("---------------TYPEDEF_%d_INFO---------------\n\n", counter);
		printf("TYPEDEF_%d_TARGET_TYPE = \"%s\"\n", counter, CSTLString_c_str(TYPEDEF_TABLE_LIST_data(p)->target_type));
		printf("TYPEDEF_%d_CHANGE_TYPE = \"%s\"\n\n", counter, CSTLString_c_str(TYPEDEF_TABLE_LIST_data(p)->change_type));
		counter++;
	}
	printf("--------------------------------------------\n\n");
}

/** �w�肳�ꂽAST�m�[�h����A�\���̃e�[�u�����X�g�ɍ\���̃f�[�^��o�^������B
@param struct_table_list �o�^��̍\���̃e�[�u�����X�g
@param ast_data �w�肳�ꂽAST�m�[�h
@return �Ȃ�

*/
void getSTRUCT_TABLE_DATA(STRUCT_TABLE_LIST *struct_table_list, AST *ast_data){
	ASTListIterator ast_p;

	//�T���̓r���ŁAstruct_or_union_specifier��������ꂽ��A�\���̃f�[�^�̓o�^��Ƃ��s��
	if(CSTLString_compare_with_char(ast_data->name, "struct_or_union_specifier") == 0){
			//�\���̃f�[�^�𐶐�����
			fflush(stdout);
			getSTRUCT_DATA(ast_data, struct_table_list);

	}
	//AST�ɎqAST�m�[�h�������Ă���ꍇ�́A�qAST�m�[�h�ɂ��Ă������T�����s���B
	for(ast_p = ASTList_begin(ast_data->children); ast_p != ASTList_end(ast_data->children); ast_p = ASTList_next(ast_p)){
		getSTRUCT_TABLE_DATA(struct_table_list,ASTList_data(ast_p));
	}

}

/** �\���̃e�[�u�����X�g�ɓ�����`���Ȃ����ǂ����𒲂ׂ�B
@param struct_table_list �����Ώۂ̍\���̃e�[�u�����X�g
@param target �������镶����
@return ������ꂽ��A�P��Ԃ��A�����łȂ���΂O��Ԃ��B
*/
int find_STRUCT_TABLE_DATA(STRUCT_TABLE_LIST *struct_table_list, CSTLString *target){
	STRUCT_TABLE_LISTIterator stlist_p;
	int find_flag = 0;
	for(stlist_p = STRUCT_TABLE_LIST_begin(struct_table_list) ;
		stlist_p != STRUCT_TABLE_LIST_end(struct_table_list) ;
		stlist_p = STRUCT_TABLE_LIST_next(stlist_p)){

			if(CSTLString_find(STRUCT_TABLE_LIST_data(stlist_p)->struct_name, CSTLString_c_str(target), 0) != CSTL_NPOS){
				find_flag = 1;
				break;
			}
	}

	return find_flag;
}

/** �w�肳�ꂽAST�m�[�h����A�\���̃f�[�^���쐬�����A�\���̃e�[�u���̃��X�g�֓o�^������B
@param ast_data �w�肳�ꂽAST�m�[�h
@param struct_table_data �o�^��̍\���̃e�[�u�����X�g
@return �Ȃ�

*/
void getSTRUCT_DATA(AST *ast_data, STRUCT_TABLE_LIST *struct_table_data){
	//�\���̖̂��O�ƌ^�ւ�AST���擾����B
	AST *struct_name = ASTList_data(ASTList_next(ASTList_begin(ast_data->children)));
	AST *type = ASTList_data(ASTList_begin(ast_data->children));

	STRUCT_TABLE *struct_data;
	//�\���̃e�[�u���̃��X�g����A���łɓ�����`���Ȃ����ǂ������ׂ�B������`���Ȃ���΁A�\���̃f�[�^�𐶐����鏈�����s���B
	if(find_STRUCT_TABLE_DATA(struct_table_data, struct_name->content) == 0){
		//struct�e�[�u���̃��X�g�ɓo�^���邽�߂̃f�[�^�i�ȉ��\���̃f�[�^�j���P����������B
		struct_data = (STRUCT_TABLE*)malloc(sizeof(STRUCT_TABLE));

		//struct_or_union_specifier�̏��߂�struct��union���K������̂ŁA�\���̃f�[�^��type�Ƃ��ēo�^����B
		CSTLString *type_str = CSTLString_new();
		getStringFromAST(type_str,type);
		struct_data->type = type_str;
		//2�ڂ�IDENTIFIER������͂��Ȃ̂ŁA�\���̃f�[�^��struct_name�Ƃ��ēo�^����
		CSTLString *struct_name_str = CSTLString_new();
		getStringFromAST(struct_name_str,struct_name);
		struct_data->struct_name = struct_name_str;
		struct_data->member_list = VARIABLE_TABLE_LIST_new();
		//�����o�o�^��Ƃ��s��
		getMemberList(struct_data->member_list, ast_data);

		//�ŏI�I�ɍ쐬���ꂽ�\���̃f�[�^�͍\���̃e�[�u���̃��X�g�֓o�^����
		STRUCT_TABLE_LIST_push_back_ref(struct_table_data, struct_data);
	}
}

/** �w�肳�ꂽAST�m�[�h����A�����o���X�g�𐶐�����B
@param member_list �o�^�Ώۂ̃����o���X�g
@param ast_data �w�肳�ꂽAST�m�[�h
@return �쐬���ꂽ�\���̃f�[�^�ւ̃A�h���X��ԋp����B

*/
void getMemberList(VARIABLE_TABLE_LIST *member_list, AST *ast_data){
	//�����o�̒�`��T���B���Ȃ킿�Astract_declaration��T���B
	ASTListIterator ast_p;
	//���O���X�g
	char except_list[4][256] = { "{", "}", "struct_declaration_list", "enumerator_list"};
	//�����Astract_declaration��������ꂽ��ȉ��̑�����s��
	if(CSTLString_compare_with_char(ast_data->name, "struct_declaration") == 0){

		//1�ڂ̓^�C�v������͂��Ȃ̂ŁA���ꂩ��錾����new_type�Ƃ��ēo�^����B
		CSTLString *new_type = CSTLString_new();
		getStringFromASTEnableExcept(new_type, ASTList_data(ASTList_begin(ast_data->children)), 4, except_list);
		//declarator��T���A�������������w�肵���^�̕ϐ��Ƃ��ă����o���X�g�ɓo�^����
		//�ϐ��̗L���͈͂������̓u���b�N���x���֌W�͂��ׂĖ����ł���i�\���̃e�[�u���ł͕s�v�Ȃ��߁j
		//�܂��A�����o�ɑ΂���AST�A�h���X�͕s�v�Ȃ̂Őݒ肵�Ȃ��iNULL�ɂ���j
		getDeclaratorFromAST(CSTLString_c_str(new_type), ast_data, member_list,
			NOT_DEFINE_LINE, NOT_DEFINE_LINE, NOT_DEFINE_BLOCK_LEVEL, NOT_DEFINE_BLOCK_ID, NULL);

		//new_type���J������B
		CSTLString_delete(new_type);
	}

	//AST�ɎqAST�m�[�h�������Ă���ꍇ�́A�qAST�m�[�h�ɂ��Ă������T�����s���B
	for(ast_p = ASTList_begin(ast_data->children); ast_p != ASTList_end(ast_data->children); ast_p = ASTList_next(ast_p)){
		//�ċA�I��struct_or_union_specifier��`�������ꍇ�́A�����͒T�������Ȃ��悤�ɂ���B
		if(CSTLString_compare_with_char(ASTList_data(ast_p)->name, "struct_or_union_specifier") != 0){
			getMemberList(member_list,ASTList_data(ast_p));
		}
	}

}

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
						  int enable_start, int enable_end ,int block_level, int block_id, AST* declaration_location_address){
	ASTListIterator ast_p;
	VARIABLE_TABLE *variable_data;


	//�����Adeclarator��������ꂽ��ȉ��̑�����s��
	if(CSTLString_compare_with_char(ast_data->name, "t_init_declarator") == 0){
		//�����o�錾�Ƃ��ēo�^���邽�߂̃f�[�^�i�ȉ������o�錾�f�[�^�j���P��������B
		CSTLString *CSTLtype = CSTLString_new();
		CSTLString_assign(CSTLtype, type);
		//�ϐ������擾����
		CSTLString *CSTLvariable_name = CSTLString_new();
		getStringFromAST(CSTLvariable_name, ast_data);

		//���̐錾���̂̃A�h���X��NULL�łȂ���΁A����ɂ��Ă̓o�^���s��
		if(declaration_location_address != NULL){
			variable_data = new_VARIABLE_TABLE(enable_start, enable_end, declaration_location_address , block_level, block_id, declaration_location_address->idlist, CSTLtype, CSTLvariable_name, NULL);
		}else{
			variable_data = new_VARIABLE_TABLE(enable_start, enable_end, declaration_location_address , block_level, block_id, NULL, CSTLtype, CSTLvariable_name, NULL);
		}
		//�����o���X�g�ɓo�^����
		VARIABLE_TABLE_LIST_push_back_ref(member_list, variable_data);
	}else if(CSTLString_compare_with_char(ast_data->name, "init_declarator") == 0){
			//�����o�錾�Ƃ��ēo�^���邽�߂̃f�[�^�i�ȉ������o�錾�f�[�^�j���P��������B
			CSTLString *CSTLtype = CSTLString_new();
			CSTLString_assign(CSTLtype, type);
			//�ϐ������擾����
			CSTLString *CSTLvariable_name = CSTLString_new();
			getStringFromAST(CSTLvariable_name, ASTList_data(ASTList_begin(ast_data->children)));

		//���̐錾���̂̃A�h���X��NULL�łȂ���΁A����ɂ��Ă̓o�^���s��
		if(declaration_location_address != NULL){
			variable_data = new_VARIABLE_TABLE(enable_start, enable_end, declaration_location_address ,
					block_level, block_id, declaration_location_address->idlist, CSTLtype, CSTLvariable_name,
					ASTList_data(ASTList_next(ASTList_next(ASTList_begin(ast_data->children)))));
		}else{
			variable_data = new_VARIABLE_TABLE(enable_start, enable_end, declaration_location_address ,
					block_level, block_id, NULL, CSTLtype, CSTLvariable_name,
					ASTList_data(ASTList_next(ASTList_next(ASTList_begin(ast_data->children)))));
		}
		//�����o���X�g�ɓo�^����
		VARIABLE_TABLE_LIST_push_back_ref(member_list, variable_data);
	}
	//AST�ɎqAST�m�[�h�������Ă���ꍇ�́A�qAST�m�[�h�ɂ��Ă������T�����s���B
	for(ast_p = ASTList_begin(ast_data->children); ast_p != ASTList_end(ast_data->children); ast_p = ASTList_next(ast_p)){
		//�ċA�I��struct_or_union_specifier��`�������ꍇ�́A�����͒T�������Ȃ��悤�ɂ���B
		if(CSTLString_compare_with_char(ASTList_data(ast_p)->name, "struct_or_union_specifier") != 0){
			getDeclaratorFromAST(type, ASTList_data(ast_p), member_list,
						  enable_start, enable_end ,block_level, block_id, declaration_location_address);
		}
	}
}

/**
�\���̃e�[�u���̃��X�g�̓��e���o�͂�����B
@param struct_table_list �o�͑Ώۂ̍\���̃e�[�u���̃��X�g
@return �Ȃ�

*/
void printSTRUCT_TABLE_LIST(STRUCT_TABLE_LIST *struct_table_list){
	STRUCT_TABLE_LISTIterator stlist_p;
	VARIABLE_TABLE_LISTIterator member_p;
	//�����o�𐔂��邽�߂̃J�E���^
	int member_counter;
	//�\���̂𐔂��邽�߂̃J�E���^
	int struct_counter = 1;
	printf("---------------STRUCT_TABLE---------------\n\n");
	//�\���̃e�[�u���̃��X�g�����ׂĎQ�Ƃ���
	for(stlist_p = STRUCT_TABLE_LIST_begin(struct_table_list) ;
		stlist_p != STRUCT_TABLE_LIST_end(struct_table_list) ;
		stlist_p = STRUCT_TABLE_LIST_next(stlist_p)){
			printf("---------------STRUCT_%d_INFO---------------\n\n", struct_counter);
			//�\���̂̃^�C�v(struct��union�j�Ɩ��O��\��������
			printf("STRUCT%d_TYPE = \"%s\"\n", struct_counter, CSTLString_c_str(STRUCT_TABLE_LIST_data(stlist_p)->type));
			//�\���̖̂��O��\��������
			printf("STRUCT%d_NAME = \"%s\"\n", struct_counter, CSTLString_c_str(STRUCT_TABLE_LIST_data(stlist_p)->struct_name));
			printf("\n");
			member_counter = 1;
			//�\���̂ɂ��郁���o���X�g���Q�Ƃ���
			for(member_p = VARIABLE_TABLE_LIST_begin(STRUCT_TABLE_LIST_data(stlist_p)->member_list) ;
				member_p != VARIABLE_TABLE_LIST_end(STRUCT_TABLE_LIST_data(stlist_p)->member_list) ;
				member_p = VARIABLE_TABLE_LIST_next(member_p)){
					//�����o�̃^�C�v�i�^���j�Ɩ��O��\��������
					printf("\tMEMBER%d_TYPE = \"%s\"\n", member_counter, CSTLString_c_str(VARIABLE_TABLE_LIST_data(member_p)->type));
					printf("\tMEMBER%d_NAME = \"%s\"\n", member_counter, CSTLString_c_str(VARIABLE_TABLE_LIST_data(member_p)->variable_name));
					printf("\n");
					member_counter++;
			}

		struct_counter++;

	}

	printf("------------------------------------------\n\n");
}

/**
getVARIABLE_TABLE_LIST�̓��������ł���B
@param variable_table_list �ϐ��e�[�u���̃��X�g
@param ast_data �Ώۂ�AST�m�[�h
@param line_stack �s���̃X�^�b�N�i�ϐ��̃X�R�[�v�𔽉f�����邽�߂Ɏg�p����j
@param max_line �v���O�����̍ő�s���i�ϐ��̃X�R�[�v�ɔ��f�����邽�߂Ɏg�p����j

@return �Ȃ�
*/

void getVARIABLE_TABLE_LIST_Internal(VARIABLE_TABLE_LIST *variable_table_list, AST *ast_data, STACK_INT *line_stack, int *max_line)
{
	ASTListIterator ast_p;
	VARIABLE_TABLE_LISTIterator vtlist;
	VARIABLE_TABLE *variable_data;
	int start_line;
	int end_line;
	int block_level;
	int block_id;
	CSTLString *type;

	//���O���X�g
	char except_list[4][256] = { "{", "}", "struct_declaration_list", "enumerator_list"};
	//�m�[�h���Ƃɍs�����r�E�X�V���邱�ƂŁA�v���O�����̍ő�̍s�����擾����B
	if(*max_line < ast_data->line){
		*max_line = ast_data->line;
	}

	//�����Adeclaration_with_init��������ꂽ��ȉ��̑�����s��
	if(CSTLString_compare_with_char(ast_data->name, "declaration_with_init") == 0){
		//��Ɍ^�����擾���Atypedef�łȂ����ǂ����m���߂�
		type = CSTLString_new();
		getStringFromASTEnableExcept(type, ASTList_data(ASTList_begin(ast_data->children)), 4, except_list);
		//typedef��������Ȃ��ꍇ�̏���
		if(CSTLString_find(type, "typedef", 0) == CSTL_NPOS){

			//�u���b�Nid�̎w��i�O���[�o���̏ꍇ�͏��0�Ƃ��A�����łȂ��ꍇ�́A�u���b�N���x���̌��ꂽ�񐔂���͂���B
			if(!STACK_INT_empty(line_stack)){
				start_line = *STACK_INT_at(line_stack, STACK_INT_size(line_stack) - 1);
			}else{
				start_line = PROGRAM_START_LINE;
			}

			block_id = ast_data->block_id;
			//�u���b�N���x���̎w��i�O���[�o���Ȃ�O�A���炩�̊֐��̂Ȃ��ł͂P�A���̒���for���Ƃ��̃u���b�N�����ł͂Q�Ǝw�肷��j
			block_level = ast_data->block_level;

			//Declarator��T���o���A�ϐ��e�[�u���̃��X�g�ɓo�^���Ă���
			getDeclaratorFromAST(CSTLString_c_str(type), ASTList_data(ASTList_next(ASTList_begin(ast_data->children))),
				variable_table_list, start_line, NOT_DEFINE_LINE , block_level, block_id, ast_data);
		}else{
			//�擾�����^���̕������j������B
			CSTLString_delete(type);
		}

	}
	//�v���O�����r���ŁA"{"�����ꂽ�ꍇ�A�u���b�N���x�����グ��
	else if(CSTLString_compare_with_char(ast_data->name, "{") == 0){
		//�u���b�N�̍s�����v�b�V���o�b�N����
		STACK_INT_push_back(line_stack, ast_data->line);

	}

	else if(CSTLString_compare_with_char(ast_data->name, "}") == 0){

		if(!STACK_INT_empty(line_stack)){
			start_line = *STACK_INT_back(line_stack);
		}else{
			start_line = PROGRAM_START_LINE;
		}
		end_line = ast_data->line;
		STACK_INT_pop_back(line_stack);

		for(vtlist = VARIABLE_TABLE_LIST_begin(variable_table_list);
			vtlist != VARIABLE_TABLE_LIST_end(variable_table_list);
			vtlist = VARIABLE_TABLE_LIST_next(vtlist)){
				if(VARIABLE_TABLE_LIST_data(vtlist)->enable_start == start_line){
						VARIABLE_TABLE_LIST_data(vtlist)->enable_end = end_line;
				}
		}
	}


	//AST�ɎqAST�m�[�h�������Ă���ꍇ�́A�qAST�m�[�h�ɂ��Ă������T�����s���B
	for(ast_p = ASTList_begin(ast_data->children); ast_p != ASTList_end(ast_data->children); ast_p = ASTList_next(ast_p)){
		//�ċA�I��struct_or_union_specifier��`�������ꍇ�́A�����͒T�������Ȃ��悤�ɂ���B
		if(CSTLString_compare_with_char(ASTList_data(ast_p)->name, "struct_or_union_specifier") != 0){
			getVARIABLE_TABLE_LIST_Internal(variable_table_list, ASTList_data(ast_p), line_stack, max_line);
		}
	}
}
/**
�Ώۂ�AST�m�[�h����ϐ��e�[�u���̃��X�g��o�^����B
@param variable_table_list �ϐ��e�[�u���̃��X�g
@param ast_data �Ώۂ�AST�m�[�h

@return �Ȃ�
*/

void getVARIABLE_TABLE_LIST(VARIABLE_TABLE_LIST *variable_table_list, AST *ast_data)
{
	VARIABLE_TABLE_LISTIterator vtlist;
	//�u���b�N�P�ʂ̍s�X�^�b�N�̔z�u
	STACK_INT *line_stack = STACK_INT_new();

	//�v���O�����̍ő�s��
	int max_line = -1;
	getVARIABLE_TABLE_LIST_Internal(variable_table_list, ast_data, line_stack, &max_line);
	//�u���b�N�P�ʂ̍s�X�^�b�N�̔j��
	STACK_INT_delete(line_stack);
	//�ϐ����X�g�̃X�R�[�v�̏I��肪NOT_DEFINE_LINE�ł�����̂����ׂăv���O�����̍ő�s�ɂ���B
	for(vtlist = VARIABLE_TABLE_LIST_begin(variable_table_list);
	vtlist != VARIABLE_TABLE_LIST_end(variable_table_list);
	vtlist = VARIABLE_TABLE_LIST_next(vtlist)){
		if(VARIABLE_TABLE_LIST_data(vtlist)->enable_end == NOT_DEFINE_LINE){
			VARIABLE_TABLE_LIST_data(vtlist)->enable_end = max_line;
		}
	}
}

/**
�֐��̃p�����[�^���X�g������AST�m�[�h����Aparameter_declaration�������A��������ϐ��e�[�u���̃��X�g�ɓo�^������B
@param variable_table_list �ϐ��e�[�u���̃��X�g
@param ast_data �Ώۂ�AST�m�[�h
@param enable_start �L���͈͂̊J�n
@param enable_end �L���͈͂̏I��
@return �Ȃ�
*/
void getParameterData(VARIABLE_TABLE_LIST *variable_table_list, AST *ast_data, AST *enable_start, AST *enable_end){
	ASTListIterator ast_p;
	VARIABLE_TABLE_LISTIterator vtlist;
	VARIABLE_TABLE *variable_data;
	CSTLString *type;
	CSTLString *name;
	//���O���X�g
	char except_list[4][256] = { "{", "}", "struct_declaration_list", "enumerator_list"};

	//�����Aparameter_declaration_with_declarator��������ꂽ��ȉ��̑�����s��
	if(CSTLString_compare_with_char(ast_data->name, "parameter_declaration_with_declarator") == 0){
		//��Ɍ^�����擾���Atypedef�łȂ����ǂ����m���߂�
		type = CSTLString_new();
		getStringFromASTEnableExcept(type, ASTList_data(ASTList_begin(ast_data->children)), 4, except_list);
		//typedef��������Ȃ��ꍇ�̏���
		if(CSTLString_find(type, "typedef", 0) == CSTL_NPOS){

			name = CSTLString_new();
			getStringFromAST(name, ASTList_data(ASTList_next(ASTList_begin(ast_data->children))));

			variable_data = new_VARIABLE_TABLE(enable_start->line, enable_end->line, enable_start,
			 enable_start->block_level, enable_start->block_id, enable_start->idlist, type, name, NULL);

			VARIABLE_TABLE_LIST_push_back_ref(variable_table_list, variable_data);
		}else{
			//�擾�����^���̕������j������B
			CSTLString_delete(type);
		}
	}

	//AST�ɎqAST�m�[�h�������Ă���ꍇ�́A�qAST�m�[�h�ɂ��Ă������T�����s���B
	for(ast_p = ASTList_begin(ast_data->children); ast_p != ASTList_end(ast_data->children); ast_p = ASTList_next(ast_p)){
		//�ċA�I��struct_or_union_specifier��`�������ꍇ�́A�����͒T�������Ȃ��悤�ɂ���B
		if(CSTLString_compare_with_char(ASTList_data(ast_p)->name, "struct_or_union_specifier") != 0){
			getParameterData(variable_table_list, ASTList_data(ast_p), enable_start, enable_end);
		}
	}

}

/**
�Ώۂ�AST�m�[�h����֐���T���A�֐����̈�����ϐ��e�[�u���̃��X�g�ɓo�^����B
@param variable_table_list �ϐ��e�[�u���̃��X�g
@param ast_data �Ώۂ�AST�m�[�h
@return �Ȃ�
*/
void getParameterVARIABLE_TABLE_LIST(VARIABLE_TABLE_LIST *variable_table_list, AST *ast_data){
	ASTListIterator ast_p;
	AST *enable_start, *enable_end;
	//�����Afunction_definition_type_b��������ꂽ��ȉ��̑�����s��
	if(CSTLString_compare_with_char(ast_data->name, "function_definition_type_b") == 0){
		enable_start = ASTList_data(ASTList_next(ASTList_next(ASTList_begin(ast_data->children))));
		enable_end = ASTList_data(ASTList_next(ASTList_next(ASTList_begin(ast_data->children))));
		enable_start = ASTList_data(ASTList_begin(enable_start->children));
		enable_end = ASTList_data(ASTList_next(ASTList_next(ASTList_begin(enable_end->children))));

		getParameterData(variable_table_list,ASTList_data(ASTList_next(ASTList_begin(ast_data->children))), enable_start, enable_end);
	}
	//AST�ɎqAST�m�[�h�������Ă���ꍇ�́A�qAST�m�[�h�ɂ��Ă������T�����s���B
	for(ast_p = ASTList_begin(ast_data->children); ast_p != ASTList_end(ast_data->children); ast_p = ASTList_next(ast_p)){
		//�ċA�I��struct_or_union_specifier��`�������ꍇ�́A�����͒T�������Ȃ��悤�ɂ���B
		if(CSTLString_compare_with_char(ASTList_data(ast_p)->name, "struct_or_union_specifier") != 0){
			getParameterVARIABLE_TABLE_LIST(variable_table_list, ASTList_data(ast_p));
		}
	}
}

/**
�ϐ��e�[�u���̃��X�g�̓��e���o�͂�����B
@param variable_table_list �o�͑Ώۂ̕ϐ��e�[�u���̃��X�g
@return �Ȃ�

*/
void printVARIABLE_TABLE_LIST(VARIABLE_TABLE_LIST *variable_table_list)
{
	VARIABLE_TABLE_LISTIterator vtlist;
	int counter = 1;

	printf("---------------VARIABLE_TABLE---------------\n\n");

	for(vtlist = VARIABLE_TABLE_LIST_begin(variable_table_list);
	vtlist != VARIABLE_TABLE_LIST_end(variable_table_list);
	vtlist = VARIABLE_TABLE_LIST_next(vtlist)){
		printf("---------------VARIABLE_%d_INFO---------------\n\n", counter);
		printf("VARIABLE_%d_TYPE = \"%s\"\n", counter, CSTLString_c_str(VARIABLE_TABLE_LIST_data(vtlist)->type));
		printf("VARIABLE_%d_NAME = \"%s\"\n", counter, CSTLString_c_str(VARIABLE_TABLE_LIST_data(vtlist)->variable_name));
		printf("VARIABLE_%d_ENABLE_START = \"%d\"\n", counter, VARIABLE_TABLE_LIST_data(vtlist)->enable_start);
		printf("VARIABLE_%d_ENABLE_END = \"%d\"\n", counter, VARIABLE_TABLE_LIST_data(vtlist)->enable_end);
		printf("VARIABLE_%d_DECLARATION_LOCATION = \"%d\"\n", counter, VARIABLE_TABLE_LIST_data(vtlist)->declaration_location_address->line);
		printf("VARIABLE_%d_BLOCK_LEVEL = \"%d\"\n", counter, VARIABLE_TABLE_LIST_data(vtlist)->block_level);
		printf("VARIABLE_%d_BLOCK_ID = \"%d\"",counter, VARIABLE_TABLE_LIST_data(vtlist)->block_id);
		printf("VARIABLE_%d_IDLIST = \"",counter);
		printIDLIST(VARIABLE_TABLE_LIST_data(vtlist)->idlist, 0);
		printf("\"\n");
		counter++;
	}
	printf("--------------------------------------------\n\n");
}

/**
�ϐ��e�[�u������A�|�C���^�̎�������єz��̎������擾����B
@param variable_table_data �ϐ��e�[�u���̃��X�g
@param output_pointer_level �o�͂����|�C���^���x��
@param output_array_level �o�͂����z�񃌃x��
@return �Ȃ�
*/
void getPointerLevelAndArrayLevelFromVARIABLE_TABLE(VARIABLE_TABLE *variable_table_data, int *output_pointer_level, int *output_array_level){
	getPointerLevelAndArrayLevel(variable_table_data->variable_name, output_pointer_level, output_array_level);
}

/**
�Ώۂ̎��ʎq�̃|�C���^�̎�������єz��̎������擾����B
@param target_identifier �Ώۂ̎��ʎq
@param output_pointer_level �o�͂����|�C���^���x��
@param output_array_level �o�͂����z�񃌃x��
@return �Ȃ�
*/
void getPointerLevelAndArrayLevel(CSTLString *target_identifier, int *output_pointer_level, int *output_array_level){
	int i;

	*output_pointer_level = 0;
	*output_array_level = 0;
	//�ϐ����̕�����𒲂ׂ�
	for(i = 0; i < CSTLString_size(target_identifier); i++){
		//�z�������'['�������ꍇ�́A�z��̎����𑝂₷
		if(*CSTLString_at(target_identifier, i) == '['){
			*output_array_level = *output_array_level + 1;
		}
		//�|�C���^������'*'�������ꍇ�́A�|�C���^�̎����𑝂₷
		else if(*CSTLString_at(target_identifier, i) == '*'){
			*output_pointer_level = *output_pointer_level + 1;
		}
	}
}
/**
�ϐ��e�[�u�����X�gvariable_table_list����A�w�肵���ϐ��X�R�[�v��IDLIST target_idlist��target_string�ɊY���悤�ȕϐ��e�[�u���ւ̃A�h���X��Ԃ��B

@param target_idlist �w�肵���ϐ��X�R�[�v��IDLIST
@param target_string �Ώۂ̕ϐ���
@param variable_table_list �ϐ��e�[�u�����X�g

@return ��L�̏������猩�����ϐ��e�[�u���ւ̃A�h���X��Ԃ��B������Ȃ����NULL��Ԃ��B
*/
VARIABLE_TABLE *searchVARIABLE_TABLE_LIST(IDLIST *target_idlist, CSTLString *target_string, VARIABLE_TABLE_LIST* variable_table_list){
	VARIABLE_TABLE_LISTIterator vi;

	//�ϐ��e�[�u���f�[�^
	VARIABLE_TABLE *variable_table_data = NULL;

	CSTLString *target = CSTLString_new();

	for(vi = VARIABLE_TABLE_LIST_begin(variable_table_list);
		vi != VARIABLE_TABLE_LIST_end(variable_table_list);
		vi = VARIABLE_TABLE_LIST_next(vi)){

		//���̕ϐ����Ɣ�r
		CSTLString_assign(target, CSTLString_c_str(VARIABLE_TABLE_LIST_data(vi)->variable_name));
		//�w�肵���ϐ����Ɣ�r���邽�߂Ƀ|�C���^��z��������L����S�č폜����
		deletePointerAndArraySynbol(target);

		//�w�肵���ϐ����ƕϐ����X�g�̕ϐ��̖��O����v���A�ϐ��X�R�[�v���Ɏ��܂��Ă���Ƃ�
		if(CSTLString_compare(target_string, target) == 0 &&
			IDLIST_compare_with(target_idlist, VARIABLE_TABLE_LIST_data(vi)->idlist) == 1){

			//���łɌ������Ă��Ȃ��ꍇ�͕ϐ��e�[�u���f�[�^�ɐݒ肷��
			if(variable_table_data == NULL){
				variable_table_data = VARIABLE_TABLE_LIST_data(vi);
			}
			//���łɐݒ肵�Ă��āA�u���b�N���x����������΁A�ϐ��e�[�u���f�[�^�ɐݒ肷��
			else if(variable_table_data->block_level < VARIABLE_TABLE_LIST_data(vi)->block_level){
				variable_table_data = VARIABLE_TABLE_LIST_data(vi);
			}
		}

	}

	return variable_table_data;
}


/**
�ϐ�������z�񂨂�у|�C���^�������L����S�č폜����B
@param target �ύX�Ώۂ̕ϐ���
@return �Ȃ�
*/
void deletePointerAndArraySynbol(CSTLString *target){
	int i;
	//�z��̒��ł���t���O
	int array_flag = 0;
	i = 0;
	//������S�̂�T��
	while(i < CSTLString_size(target)){
		//�z��̒��ł���t���O�������Ă��Ȃ��i�z��̒��ł͂Ȃ��j�ꍇ
		if(array_flag == 0){
			//�����A���p�X�y�[�X���|�C���^�������A�X�^���X�N���������炻�̕������폜����
			//�܂��A�ۃJ�b�R�����Ă��폜������
			if(*CSTLString_at(target, i) == ' ' || *CSTLString_at(target, i) == '*' ||
			 *CSTLString_at(target, i) == '(' || *CSTLString_at(target, i) == ')'){
				CSTLString_erase(target, i, 1);
				continue;
			}
			//�z��̎n�܂�������L������������A�z��̒��ł���t���O�����āA���̕������폜����
			else if(*CSTLString_at(target, i) == '[' ){
				CSTLString_erase(target, i, 1);
				array_flag = 1;
				continue;
			}
			//�폜����Ă��Ȃ��ꍇ�̂݁A���̕����ֈړ�����
			i++;
		}
		//�z��̒��ł���t���O�������Ă���i�z��̒��ł���j�ꍇ
		else{
			//�z��̏I���������L����������΁A�z��̒��ł���t���O��������
			if(*CSTLString_at(target, i) == ']' ){
				array_flag = 0;
			}
			//�z��̏I���������L����������܂ł����ƕ������폜����
			CSTLString_erase(target, i, 1);
			continue;
		}
	}
}

/**
�ϐ�������|�C���^�������L���̂ݑS�č폜����B
@param target �ύX�Ώۂ̕ϐ���
@return �Ȃ�
*/
void deletePointer(CSTLString *target){
	CSTLString_replace_string(target, "* ", "");
}

CSTLString *getTypeOfVariable(CSTLString *variable_name , VARIABLE_TABLE *variable_table){
	CSTLString *output = CSTLString_new();
	CSTLString_assign(output, CSTLString_c_str(variable_table->variable_name));
	size_t idx = CSTLString_find(output, CSTLString_c_str(variable_name), 0);
	CSTLString_replace_len(output, idx, CSTLString_size(variable_name),
			CSTLString_c_str(variable_table->type), CSTLString_size(variable_table->type));

	return output;
}
