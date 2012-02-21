#include"FunctionInformation.h"
#include<stdlib.h>
#include<stdio.h>

#include"ANSIC_CODE.h"

CSTL_LIST_IMPLEMENT(PARAM_INFORMATION_LIST, PARAM_INFORMATION)

CSTL_LIST_IMPLEMENT(FUNCTION_INFORMATION_LIST, FUNCTION_INFORMATION)

#define LINE 65536
#define LENGTH 4096

#define FUNCTION_DEFINE_INPUTED 2
#define PARAMETER_DEFINE_INPUTED 3
/**
�֐��Ɋւ�����𐶐�����B

@param function_node �Ώۂ̊֐��ւ̃m�[�h
@param return_type �ԋp�l�̃^�C�v
@param function_name �֐���
@param param_information_list �p�����[�^�Ɋւ�����

@return �������ꂽ�֐��Ɋւ�����ւ̃A�h���X��Ԃ��B
 */
FUNCTION_INFORMATION *new_FUNCTION_INFORMATION(AST *function_node, CSTLString *return_type,
			CSTLString *function_name, PARAM_INFORMATION_LIST *param_information_list){
	FUNCTION_INFORMATION *new_function_information = (FUNCTION_INFORMATION*)malloc(sizeof(FUNCTION_INFORMATION));

	if(new_function_information == NULL){
		fprintf(stderr, "�������s���ł�\n");
		exit(1);
	}else{
		new_function_information->function_node = function_node;
		new_function_information->return_type = return_type;
		new_function_information->function_name = function_name;
		new_function_information->param_information_list = param_information_list;
	}

	return new_function_information;
}

/**
�p�����[�^�Ɋւ�����𐶐�����B

@param param_type �p�����[�^�̌^
@param param_name �p�����[�^�̖��O
@param array_level �z��̃��x��
@param pointer_level �|�C���^�̃��x��
@param in_out_flag ���͌^���o�͌^���̔���@�P�F���́@�O�F�o�́@�Q�F���o��

@return �������ꂽ�p�����[�^�Ɋւ�����ւ̃A�h���X��Ԃ��B
 */

PARAM_INFORMATION *new_PARAM_INFORMATION(CSTLString *param_type, CSTLString *param_name,
			int array_level, int pointer_level, int in_out_flag){
	PARAM_INFORMATION *new_param_information = (PARAM_INFORMATION*)malloc(sizeof(PARAM_INFORMATION));

	if(new_param_information == NULL){
		fprintf(stderr, "�������s���ł�\n");
		exit(1);
	}else{
		new_param_information->param_type = param_type;
		new_param_information->param_name = param_name;
		new_param_information->array_level = array_level;
		new_param_information->pointer_level = pointer_level;
		new_param_information->in_out_flag = in_out_flag;
	}

	return new_param_information;
}

/**
�w�肵���v���O������AST�m�[�h����֐���`��T���A����Ɋ�Â��Ċ֐��Ɋւ�����𐶐����A�����̃��X�gfunction_information_list
�ɓo�^����B

@param function_information_list �o�^��̊֐��Ɋւ�����̃��X�g
@param root �w�肵���v���O������AST�m�[�h

@return �Ȃ�
 */
void getFunctionInformation(FUNCTION_INFORMATION_LIST *function_information_list, AST *root){
	ASTListIterator ast_p;
	AST *enable_start, *enable_end;
	//�����Afunction_definition_type_b��������ꂽ��ȉ��̑�����s��
	if(CSTLString_compare_with_char(root->name, "function_definition_type_b") == 0){
		//�ԋp�l����ъ֐������`����
		CSTLString *return_type = CSTLString_new();
		CSTLString *function_name = CSTLString_new();

		//�֐��̃p�����[�^�����擾����
		PARAM_INFORMATION_LIST *param_information_list = PARAM_INFORMATION_LIST_new();
		getParamInformationFromFunctionDifinition(ASTLIST_ITERATOR_2(root), param_information_list);

		//�ԋp�l����ъ֐������擾����
		getStringFromAST(return_type, ASTLIST_ITERATOR_1(root));
		getStringFromAST(function_name, ASTLIST_ITERATOR_2(root));
		//�֐�������A�p�����[�^��`�̕������폜����
		deleteParameterDefine(function_name);


		FUNCTION_INFORMATION_LIST_push_back_ref(function_information_list, new_FUNCTION_INFORMATION(root, return_type, function_name, param_information_list));
	}
	//AST�ɎqAST�m�[�h�������Ă���ꍇ�́A�qAST�m�[�h�ɂ��Ă������T�����s���B
	for(ast_p = ASTList_begin(root->children); ast_p != ASTList_end(root->children); ast_p = ASTList_next(ast_p)){
		//�ċA�I��struct_or_union_specifier��`�������ꍇ�́A�����͒T�������Ȃ��悤�ɂ���B
		if(CSTLString_compare_with_char(ASTList_data(ast_p)->name, "struct_or_union_specifier") != 0){
			getFunctionInformation(function_information_list, ASTList_data(ast_p));
		}
	}
}

/**
�w�肵���t�@�C����file_name�Œ�`���ꂽ�֐��Ɋւ�������֐��Ɋւ�����̃��X�gfunction_information_list�ɐݒ肷��B
@param function_information_list �o�^��̊֐��Ɋւ�����̃��X�g
@param file_name �w�肵���t�@�C����

@return �Ȃ�
 */
void getFunctionInformationFromFile(FUNCTION_INFORMATION_LIST *function_information_list, char* file_name){
	FILE *open;

	char type[LENGTH],name[LENGTH];
	char param_type[LENGTH],param_name[LENGTH];
	char in_out_flag_str[LENGTH];
	CSTLString *CSTL_function_type;
	CSTLString *CSTL_function_name;
	CSTLString *CSTL_param_type;
	CSTLString *CSTL_param_name;
	CSTLString *CSTL_in_out_flag_str = CSTLString_new();
	PARAM_INFORMATION_LIST *param_information_list;
	int file_pos;
	int pointer_level, array_level;
	int in_out_flag;
	fpos_t fpos;
	char input_char;
	open = fopen(file_name, "r");

	int scanf_count;


	if(open == NULL){
		fprintf(stderr,"�w�肵���t�@�C��:%s���J�����܂���B", file_name);
		exit(1);
	}else{
		//�t�@�C���̏I���܂ŁA�ԋp�l�̌^�Ɗ֐������擾����
		while(1){
			scanf_count = fscanf(open, "%[^,],%[^,\n]",type, name);
			if(scanf_count == EOF){
				break;
			}else if(scanf_count != FUNCTION_DEFINE_INPUTED){
				fprintf(stderr,"���̓t�H�[�}�b�g�ԋp�^,�֐���,���s���ł��I\n");
				exit(1);
			}
			//�֐��̕ԋp�^�Ɩ��O���擾����
			CSTL_function_type = CSTLString_new();
			CSTLString_assign(CSTL_function_type, type);
			CSTL_function_name = CSTLString_new();
			CSTLString_assign(CSTL_function_name, name);


			//�p�����[�^���X�g������������
			param_information_list = PARAM_INFORMATION_LIST_new();

			//�C�ӂɃp�����[�^���擾����
			if(fgetc(open) == ','){
				while(1){
					if(fscanf(open, "%[^:\n]:%[^:\n]:%[^,\n\0]", param_type, param_name,in_out_flag_str) != PARAMETER_DEFINE_INPUTED){
						fprintf(stderr,"���̓t�H�[�}�b�g�^��:�ϐ���:���o�͑������s���ł��I\n");
						exit(1);
					}


					//�p�����[�^�̌^�����擾����
					CSTL_param_type = CSTLString_new();
					CSTLString_assign(CSTL_param_type, param_type);
					CSTLString_ltrim(CSTL_param_type);

					//�p�����[�^�̕ϐ������擾����
					CSTL_param_name = CSTLString_new();
					CSTLString_assign(CSTL_param_name, param_name);
					CSTLString_ltrim(CSTL_param_name);

					//���͂��o�͂��̕�������擾����
					CSTLString_assign(CSTL_in_out_flag_str, in_out_flag_str);

					//\r�L�����܂܂�Ă����炻���\0�ɒu��������B
					CSTLString_replace_string(CSTL_in_out_flag_str, "\r", "\0");
					//�󔒕������폜����
					CSTLString_replace_string(CSTL_in_out_flag_str, " ", "");

					//�|�C���^���x������єz�񃌃x�����擾����
					getPointerLevelAndArrayLevel(CSTL_param_name, &pointer_level, &array_level);

					//�p�����[�^�̕ϐ�������A�|�C���^����єz��������L�����폜����
					deletePointerAndArraySynbol(CSTL_param_name);

					//�p�����[�^�̌^������у|�C���^���x���E�z�񃌃x�����炱�̃p�����[�^�͓��͌^���o�͌^�����f����
					if(CSTLString_compare_with_char(CSTL_in_out_flag_str, "IN") == 0){
						in_out_flag = PARAM_IN_TYPE;
					}else if(CSTLString_compare_with_char(CSTL_in_out_flag_str, "OUT") == 0){
						in_out_flag = PARAM_OUT_TYPE;
					}else if(CSTLString_compare_with_char(CSTL_in_out_flag_str, "IN_OUT") == 0){
						in_out_flag = PARAM_INOUT_TYPE;
					}else{
						fprintf(stderr, "���́E�o�̓^�C�v%s���s���ł��I\n", CSTLString_c_str(CSTL_in_out_flag_str));
						exit(1);
					}

					//�p�����[�^���X�g�ɂ����
					PARAM_INFORMATION_LIST_push_back_ref(param_information_list,
							new_PARAM_INFORMATION(CSTL_param_type, CSTL_param_name, array_level, pointer_level, in_out_flag));
					//�t�@�C������ǂݍ���1�����O�̕��������s��EOF�ł���΁A�I������
					input_char = fgetc(open);
					if(input_char == '\n' ||input_char == EOF){
						break;
					}

				}
			}

			//�֐����X�g�ɒǉ�����
			FUNCTION_INFORMATION_LIST_push_back_ref(function_information_list,
					new_FUNCTION_INFORMATION(NULL, CSTL_function_type, CSTL_function_name, param_information_list));
		}
		fclose(open);


	}
	CSTLString_delete(CSTL_in_out_flag_str);
}

/**
�w�肵���֐��̒�`���̂���A�p�����[�^��`�Ȃǂ��폜����B

@param target_string �Ώۂ̊֐��̒�`���̂̕�����

@return �Ȃ�
 */
void deleteParameterDefine(CSTLString *target_string){
	int i;
	//�p�����[�^�������t���O
	int parameter_flag = 0;

	for(i = 0; i < CSTLString_size(target_string);){
		//�p�����[�^�������t���O�������Ă��Ȃ��Ƃ�
		if(parameter_flag == 0){
			//�p�����[�^�̊J�n�������}�[�N�������ꍇ�́A���̕������폜���āA�t���O�𗧂Ă�
			if(*CSTLString_at(target_string,i) == '('){
				CSTLString_erase(target_string, i, 1);
				parameter_flag = 1;
			}else if(*CSTLString_at(target_string,i) == ' '){
				CSTLString_erase(target_string, i, 1);

			}
			//����ȊO�̏ꍇ�́A�ꕶ���i�߂�
			else{
				i++;
			}
		}
		//�p�����[�^�������t���O�������Ă���Ƃ�
		else{
			//�p�����[�^�̏I���������}�[�N�������ꍇ�́A���̕������폜���������A�t���O��������
			if(*CSTLString_at(target_string,i) == ')'){
				CSTLString_erase(target_string, i, 1);
				parameter_flag = 0;
			}
			//����ȊO�̏ꍇ�͍폜���Ă���
			else{
				CSTLString_erase(target_string, i, 1);
			}
		}

	}
}
/**
�֐��Ɋւ����񃊃X�g�̓��e���o�͂�����B
@param function_information_list �o�͑Ώۂ̊֐��Ɋւ����񃊃X�g

@return �Ȃ�
*/

void printFUNCTION_INFORMATION_LIST(FUNCTION_INFORMATION_LIST *function_information_list){
	FUNCTION_INFORMATION_LISTIterator f_info_list;
	PARAM_INFORMATION_LISTIterator p_info_list;
	int f_counter;
	for(f_counter = 1, f_info_list = FUNCTION_INFORMATION_LIST_begin(function_information_list);
		f_info_list != FUNCTION_INFORMATION_LIST_end(function_information_list);
		f_counter++, f_info_list = FUNCTION_INFORMATION_LIST_next(f_info_list)){

		//�֐��Ɋւ�����̓��e���o�͂���
		printf("-------FUNCTION_INFORMATION_%d-------\n\n",f_counter);
		if(FUNCTION_INFORMATION_LIST_data(f_info_list)->function_node != NULL){
			printf("FUNCTION_LINE = %d\n", FUNCTION_INFORMATION_LIST_data(f_info_list)->function_node->line);
		}
		printf("RETURN_TYPE = \"%s\"\n", CSTLString_c_str(FUNCTION_INFORMATION_LIST_data(f_info_list)->return_type));
		printf("FUNCTION_NAME = \"%s\"\n", CSTLString_c_str(FUNCTION_INFORMATION_LIST_data(f_info_list)->function_name));
		//�ϐ������o�͂�����
		for(p_info_list = PARAM_INFORMATION_LIST_begin(FUNCTION_INFORMATION_LIST_data(f_info_list)->param_information_list);
			p_info_list != PARAM_INFORMATION_LIST_end(FUNCTION_INFORMATION_LIST_data(f_info_list)->param_information_list);
			p_info_list = PARAM_INFORMATION_LIST_next(p_info_list)){

			//�p�����[�^�̌^���E���O�E�|�C���^���x���E�z�񃌃x���E���o�͑����̏��ɏo�͂�����
			printf("%s %s POINTER_LEVEL = %d a_level = %d io_type = ", CSTLString_c_str(PARAM_INFORMATION_LIST_data(p_info_list)->param_type),
					CSTLString_c_str(PARAM_INFORMATION_LIST_data(p_info_list)->param_name), PARAM_INFORMATION_LIST_data(p_info_list)->pointer_level,
					PARAM_INFORMATION_LIST_data(p_info_list)->array_level);

			//�p�����[�^�̓��o�͑������o�͂�����
			if(PARAM_INFORMATION_LIST_data(p_info_list)->in_out_flag == PARAM_IN_TYPE){
				printf("IN\n");
			}else if(PARAM_INFORMATION_LIST_data(p_info_list)->in_out_flag == PARAM_OUT_TYPE){
				printf("OUT\n");
			}else if(PARAM_INFORMATION_LIST_data(p_info_list)->in_out_flag == PARAM_INOUT_TYPE){
				printf("IN_OUT\n");
			}else{
				printf("NOT_DEFINE!");
			}
		}
		printf("-------------------------------------\n\n");
	}
}

/**
�֐��Ɋւ����񃊃X�g����A�w�肵���֐�����T���A����Ɋւ���\���̂ւ̃A�h���X��Ԃ��B

@param target_function_name �w�肵���֐���
@param function_information_list �����Ώۂ̊֐��Ɋւ����񃊃X�g

@return ���������ꍇ�͂��̊֐��Ɋւ���\���̂ւ̃A�h���X��Ԃ��B�݂���Ȃ���΁ANULL��Ԃ��B
 */

FUNCTION_INFORMATION *searchFUNCTION_INFORMATION(CSTLString *target_function_name, FUNCTION_INFORMATION_LIST *function_information_list){
	FUNCTION_INFORMATION_LISTIterator f_info_list;
	//�֐��Ɋւ����񃊃X�g����擾�����֐���
	CSTLString *function_name = CSTLString_new();
	int output_pointer_level, output_array_level;

	for(f_info_list = FUNCTION_INFORMATION_LIST_begin(function_information_list);
		f_info_list != FUNCTION_INFORMATION_LIST_end(function_information_list);
		f_info_list = FUNCTION_INFORMATION_LIST_next(f_info_list)){

		//�֐��Ɋւ����񃊃X�g����֐������擾����
		CSTLString_assign(function_name, CSTLString_c_str(FUNCTION_INFORMATION_LIST_data(f_info_list)->function_name));

		//�֐�������]���ȃ|�C���^��z��L�����폜����
		deletePointerAndArraySynbol(function_name);

		//�����A�֐�������v�����ꍇ�̓|�C���^���x����Ԃ�
		if(CSTLString_compare(target_function_name, function_name) == 0){
			return FUNCTION_INFORMATION_LIST_data(f_info_list);
		}
	}

	return NULL;
}

/**
�w�肵���֐������֐��Ɋւ����񃊃X�g����T���A�|�C���^���x����Ԃ��B
@param target_function_name �w�肵���֐���
@param function_information_list �����Ώۂ̊֐��Ɋւ����񃊃X�g

@return ���������ꍇ�͂��̊֐��̃|�C���^���x����Ԃ��B�����łȂ��ꍇ��-1��Ԃ��B
 */

int getPointerLevelFromFUNCTION_INFORMATION_LIST(CSTLString *target_function_name, FUNCTION_INFORMATION_LIST *function_information_list){
	FUNCTION_INFORMATION_LISTIterator f_info_list;
	//�֐��Ɋւ����񃊃X�g����擾�����֐���
	CSTLString *function_name = CSTLString_new();
	int output_pointer_level, output_array_level;
	int f_counter;
	for(f_counter = 1, f_info_list = FUNCTION_INFORMATION_LIST_begin(function_information_list);
		f_info_list != FUNCTION_INFORMATION_LIST_end(function_information_list);
		f_counter++, f_info_list = FUNCTION_INFORMATION_LIST_next(f_info_list)){

		//�֐��Ɋւ����񃊃X�g����֐������擾����
		CSTLString_assign(function_name, CSTLString_c_str(FUNCTION_INFORMATION_LIST_data(f_info_list)->function_name));
		//�֐�������|�C���^���x�����擾����
		getPointerLevelAndArrayLevel(function_name,&output_pointer_level,&output_array_level);

		//�֐�������]���ȃ|�C���^��z��L�����폜����
		deletePointerAndArraySynbol(function_name);

		//�����A�֐�������v�����ꍇ�̓|�C���^���x����Ԃ�
		if(CSTLString_compare(target_function_name, function_name) == 0){
			return output_pointer_level;
		}
	}

	return -1;
}
/**
�p�����[�^���X�g�������m�[�hparam_info_node����A�p�����[�^�̏����擾���Aparam_information_list�ɓo�^����B

@param param_info_node �p�����[�^���X�g�������m�[�h
@param param_information_list �o�^��̃p�����[�^��񃊃X�g

@return �Ȃ�
 */
void getParamInformationFromFunctionDifinition(AST *param_info_node, PARAM_INFORMATION_LIST *param_information_list){

	ASTListIterator ast_p;
	PARAM_INFORMATION *param_information;
	CSTLString *type;
	CSTLString *name;
	int array_level, pointer_level;
	int in_out_flag;
	//���O���X�g
	char except_list[4][256] = { "{", "}", "struct_declaration_list", "enumerator_list"};

	//�����Aparameter_declaration_with_declarator��������ꂽ��ȉ��̑�����s��
	if(CSTLString_compare_with_char(param_info_node->name, "parameter_declaration_with_declarator") == 0){
		//��Ɍ^�����擾���Atypedef�łȂ����ǂ����m���߂�
		type = CSTLString_new();
		getStringFromASTEnableExcept(type, ASTLIST_ITERATOR_1(param_info_node), 4, except_list);

		//typedef��������Ȃ��ꍇ�̏���
		if(CSTLString_find(type, "typedef", 0) == CSTL_NPOS){
			//�p�����[�^�̕ϐ������擾����
			name = CSTLString_new();
			getStringFromAST(name, ASTLIST_ITERATOR_2(param_info_node));

			//�|�C���^���x������єz�񃌃x�����擾����
			getPointerLevelAndArrayLevel(name, &pointer_level, &array_level);

			//�p�����[�^�̕ϐ�������A�|�C���^����єz��������L�����폜����
			deletePointerAndArraySynbol(name);

			//�p�����[�^�̌^������у|�C���^���x���E�z�񃌃x�����炱�̃p�����[�^�͓��͌^���o�͌^�����f����
			in_out_flag = getIN_OUT_FLAG(type, pointer_level, array_level);

			//�V���Ƀp�����[�^�𐶐����A�p�����[�^���X�gparam_information_list�ɒǉ�����
			param_information = new_PARAM_INFORMATION(type, name, array_level, pointer_level, in_out_flag);
			PARAM_INFORMATION_LIST_push_back_ref(param_information_list, param_information);
		}else{
			//�擾�����^���̕������j������B
			CSTLString_delete(type);
		}
	}

	//AST�ɎqAST�m�[�h�������Ă���ꍇ�́A�qAST�m�[�h�ɂ��Ă������T�����s���B
	for(ast_p = ASTList_begin(param_info_node->children); ast_p != ASTList_end(param_info_node->children); ast_p = ASTList_next(ast_p)){
		//�ċA�I��struct_or_union_specifier��`�������ꍇ�́A�����͒T�������Ȃ��悤�ɂ���B
		if(CSTLString_compare_with_char(ASTList_data(ast_p)->name, "struct_or_union_specifier") != 0){
			getParamInformationFromFunctionDifinition(ASTList_data(ast_p), param_information_list);
		}
	}
}

/**
�p�����[�^�̃|�C���^���x���E�z�񃌃x������ь^������A���̃p�����[�^�͓��͌^���o�͌^�����肷��B

@param param_type �p�����[�^�̌^��
@param pointer_level �|�C���^�̃��x��
@param array_level �z��̃��x��

@return ���͌^�Ȃ�΂P�A�o�͌^�Ȃ�΂O��Ԃ��B
 */
int getIN_OUT_FLAG(CSTLString *param_type, int pointer_level, int array_level){
	//���͌^���o�͌^���̃t���O
	int in_out_flag;

	//�p�����[�^�̌^����const�L�[���[�h���܂܂�Ă����ꍇ�́A���͌^�Ƃ���
	if(CSTLString_find(param_type, "const", 0) != CSTL_NPOS){
		in_out_flag = PARAM_IN_TYPE;
	}
	//�����ł͂Ȃ��A�|�C���^���x������єz�񃌃x�����P�ȏ�Ȃ�΁A�o�͌^�Ƃ���B�����łȂ���Γ��͌^�Ƃ���B
	else if(pointer_level > 0 || array_level > 0){
		in_out_flag = PARAM_OUT_TYPE;
	}else{
		in_out_flag = PARAM_IN_TYPE;
	}

	return in_out_flag;
}
