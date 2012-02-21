#include"MallocNumber.h"

#include<stdio.h>
#include<stdlib.h>


/**
malloc�p���ʔԍ��֐����J�����g�f�B���N�g����ɐ���������B
@param target_directory �쐬����f�B���N�g����

@return �Ȃ�
*/
void generateMallocNumber(CSTLString *target_directory){
	FILE *header, *source;

	CSTLString *header_string = CSTLString_new();
	CSTLString *source_string = CSTLString_new();
	if(CSTLString_size(target_directory) != 0){
		CSTLString_printf(header_string, 1, "%s/malloc_number.h", CSTLString_c_str(target_directory));
		CSTLString_printf(source_string, 1, "%s/malloc_number.c", CSTLString_c_str(target_directory));
	}else{
		CSTLString_printf(header_string, 1, "./malloc_number.h");
		CSTLString_printf(source_string, 1, "./malloc_number.c");
	}
	//�\�[�X�t�@�C���𐶐�����
	source = fopen(CSTLString_c_str(source_string), "w");

	fprintf(source, "#include \"malloc_number.h\"\n");
	fprintf(source, "#include <stdio.h>\n");
	fprintf(source, "#include <stdlib.h>\n");
	fprintf(source, "int static_malloc_number = 1;\n");
	fprintf(source, "void malloc_number(int *set_malloc_number){\n");
	fprintf(source, "	*set_malloc_number = static_malloc_number;\n");
	fprintf(source, "	static_malloc_number++;\n");
	fprintf(source, "}\n");

	fclose(source);

	//�w�b�_�[�t�@�C���𐶐�����
	header = fopen(CSTLString_c_str(header_string), "w");

	fprintf(header, "#ifndef MALLOC_NUMBER_HEADDER_FILE\n");
	fprintf(header, "#define MALLOC_NUMBER_HEADDER_FILE\n");
	fprintf(header, "void malloc_number(int *set_malloc_number);\n");
	fprintf(header, "#endif\n");

	fclose(header);
}

/**
�C���N���[�h����malloc�p���ʔԍ��t���֐����܂܂�Ă���w�b�_�[�t�@�C����ǉ�������B
@param include_list �C���N���[�h���ւ̃��X�g

@return �Ȃ�
*/
void insertMallocNumberHeadder(INCLUDE_LIST *include_list){
	CSTLString *include_data = CSTLString_new();

	//malloc_number.h�ւ̃C���N���[�h����ǉ�������
	CSTLString_assign(include_data, "#include\"malloc_number.h\"\n");
	INCLUDE_LIST_push_back_ref(include_list, new_INCLUDE_DATA(include_data, 0));
}
