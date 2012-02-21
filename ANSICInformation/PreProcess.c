#include "PreProcess.h"
#include "../Library/CSTLString.h"

#include<stdio.h>
#include<stdlib.h>

#define STRLEN 1024
#define MAX_FILE_PATH 1024
#define COMMAND_PATH 4096

//�u/*PROGRAM_START*/�v�̒���
#define PROGRAM_START_LENGTH 17

CSTL_LIST_IMPLEMENT(INCLUDE_LIST, INCLUDE_DATA)

/**
�V�����C���N���[�h�t�@�C���𐶐�����B
@param include_data include�t�@�C���̖��O
@param line ���̍s��
*/
INCLUDE_DATA *new_INCLUDE_DATA(CSTLString *include_data, int line){
	//�V���ɃC���N���[�h�t�@�C���𐶐�����
	INCLUDE_DATA *new_include_data = (INCLUDE_DATA*)malloc(sizeof(INCLUDE_DATA));

	//�����A�����ɐ��������ꍇ
	if(new_include_data != NULL){
		new_include_data->include_data = include_data;
		new_include_data->line = line;
	}
	//�����Ɏ��s�����ꍇ�́A�G���[���o�͂��������I��������B
	else{
		fprintf(stderr, "Memory is lack!!\n");
		exit(1);
	}

	return new_include_data;
}

/**
���s���������\�[�X�Ƀv���v���Z�b�T��������B�v���v���Z�b�T�̂������t�@�C���̓t�@�C����_out_pre.c�Ƃ��ďo�͂����B
@param source_file_name ���s���������\�[�X�t�@�C����

@return �����������ǂ����������@���������ꍇ�͂P���������A�����łȂ��ꍇ�͂O��Ԃ��B
*/
int preProcesser(char *source_file_name){
	//�����t���O
	int success_flag = 1;

	char out_file_name[MAX_FILE_PATH];
	char excec_command[COMMAND_PATH];
	FILE *test_open;
	//include���R�����g�A�E�g����
	includeComment(source_file_name);

	//�o�̓t�@�C���̐ݒ�
	snprintf(out_file_name, MAX_FILE_PATH, "%s_out.c", source_file_name);

	//�R�}���h�̐ݒ�
	snprintf(excec_command, COMMAND_PATH, "gcc -E -P -C %s > %s_pre.c", out_file_name, out_file_name);

	//gcc�̃v���v���Z�b�T�̎��s
	system(excec_command);

	//�o�̓t�@�C���̍Đݒ�(_pre.c��ǉ�)
	snprintf(out_file_name, MAX_FILE_PATH, "%s_pre.c", out_file_name);
	//�e�X�g�Ńt�@�C�����J����
	test_open = fopen(out_file_name, "r");

	//�v���O�����X�^�[�g�𒲐������s�ɏI������ꍇ�A���̏����͎��s�ɏI��������ƂɂȂ�
	if(adjustProgramStart(out_file_name) == 0){
		success_flag = 0;
	}
	return success_flag;
}

/**
"#include"�ɃR�����g�������Ă����B�R�����g�A�E�g�����������ʂ̓t�@�C����_out.c�Ƃ��ďo�͂����B
@param source_file_name �Ώۂ̃\�[�X�t�@�C����

@return �����������ǂ����������@���������ꍇ�͂P���������A�����łȂ��ꍇ�͂O��Ԃ��B
*/
int includeComment(char *source_file_name){
	//�����ɐ����������ǂ����������t���O
	int success_flag = 1;

	FILE *in, *out;
	char buff[STRLEN];
	char out_file_name[MAX_FILE_PATH];

	CSTLString *file_buff = CSTLString_new();
	//�\�[�X�t�@�C�����I�[�v��
	in = fopen(source_file_name, "rt");

	//�J���̂Ɏ��s�����ꍇ
	if(in == NULL){
		//�����͎��s�ɏI��������ƂƂ݂Ȃ�
		success_flag = 0;
	}else{
		//�v���O�����̊J�n�������R�����g�����Ă���
		CSTLString_assign(file_buff,"/*PROGRAM_START*/");

		//�t�@�C�������s�����o���Afile_buff�֊i�[����
		buff[1] = '\0';
		while(fgets(buff,STRLEN,in) != NULL){
			CSTLString_append(file_buff, (char *)buff);
		}
		fclose(in);

		//#include���R�����g�A�E�g����
		CSTLString_replace_string(file_buff, "#include", "//#xinclude");

		sprintf(out_file_name,"%s_out.c", source_file_name);

		out = fopen(out_file_name, "w");

		fprintf(out, "%s", CSTLString_c_str(file_buff));

		fclose(out);
	}
	CSTLString_delete(file_buff);
	return success_flag;
}

/**
�v���O�����̎n�܂�������ʒu�܂ł��ׂč폜����B
@param source_file_name �Ώۂ̃\�[�X�t�@�C����

@return �����������ǂ����������@���������ꍇ�͂P���������A�����łȂ��ꍇ�͂O��Ԃ��B
*/
int adjustProgramStart(char *source_file_name){
	//�����ɐ����������ǂ����������t���O
	int success_flag = 1;

	FILE *in, *out;
	char buff[STRLEN];
	int program_start_location;

	CSTLString *file_buff = CSTLString_new();
	//�\�[�X�t�@�C�����I�[�v��
	in = fopen(source_file_name, "rt");

	//�J���̂Ɏ��s�����ꍇ
	if(in == NULL){
		//�����͎��s�ɏI��������ƂƂ݂Ȃ�
		success_flag = 0;
	}else{

		//�t�@�C�������s�����o���Afile_buff�֊i�[����
		buff[1] = '\0';
		while(fgets(buff,STRLEN,in) != NULL){
			CSTLString_append(file_buff, (char *)buff);
		}
		fclose(in);
		//�u/*PROGRAM_START*/�v��T���o���A������΁A���̃R�����g���Ƃ��ׂč폜����
		program_start_location = CSTLString_find(file_buff,"/*PROGRAM_START*/",0);
		if(program_start_location != CSTL_NPOS){
			CSTLString_replace(file_buff,0,program_start_location + PROGRAM_START_LENGTH,"");
		}

		out = fopen(source_file_name, "w");

		fprintf(out, "%s", CSTLString_c_str(file_buff));

		fclose(out);
	}
	CSTLString_delete(file_buff);
	return success_flag;
}

/**
"#include"�ɃR�����g�����������݂̂̂����o���A��肾�������̂��C���N���[�h�t�@�C���̃��X�ginclude_list�ɂ����B
@param file_name �J���t�@�C����
@param include_list �C���N���[�h���X�g

@return �Ȃ�
*/
void readIncludeDataFromFile(char *file_name, INCLUDE_LIST *include_list){
	FILE *in;

	char fbuff[STRLEN];

	int line = 1;
		//�t�@�C�����J��
	in = fopen(file_name, "r");

	//�t�@�C�����J���̂ɐ���������
	if(in != NULL){
			//��s���Q�Ƃ���
			while(fgets(fbuff, STRLEN, in) != NULL){
				CSTLString *line_buff = CSTLString_new();
				CSTLString_assign(line_buff, fbuff);
				if(CSTLString_find(line_buff,"//#xinclude",0) != CSTL_NPOS){
					CSTLString_replace_string(line_buff, "//#xinclude", "#include");
					INCLUDE_LIST_push_back_ref(include_list, new_INCLUDE_DATA(line_buff, line));
				}else{
					CSTLString_delete(line_buff);
				}

				line++;
			}
	}
	//�t�@�C�����J�����Ȃ���΃G���[���o�͂��I������
	else{
		fprintf(stderr, "File %s is not exist or invalid!\n", file_name);
		exit(1);
	}
}

/**
�C���N���[�h���X�g����ɁA�Ώۂ̃t�@�C���ɃC���N���[�h��ǉ�����B
@param file_name �J���t�@�C����
@param include_list �C���N���[�h���X�g

@return �Ȃ�
*/
void addIncludeDataFromFile(char *file_name, INCLUDE_LIST *include_list){
	FILE *in, *tmp;

	char fbuff[STRLEN];

	char tmp_file_name[MAX_FILE_PATH];

	char move_command[STRLEN];

	snprintf(tmp_file_name, MAX_FILE_PATH,"%s,tmp", file_name);

	snprintf(move_command, STRLEN, "mv %s %s", tmp_file_name, file_name);

	INCLUDE_LISTIterator inlist_iterator;

	//tmp�t�@�C�����J��
	tmp = fopen(tmp_file_name, "w");
	in = fopen(file_name, "r");

	//�t�@�C�����J���̂ɐ���������
	if(in != NULL){
			for(inlist_iterator = INCLUDE_LIST_begin(include_list);
				inlist_iterator != INCLUDE_LIST_end(include_list);
				inlist_iterator = INCLUDE_LIST_next(inlist_iterator)){

				fprintf(tmp, "%s", CSTLString_c_str(INCLUDE_LIST_data(inlist_iterator)->include_data));
			}
			//��s���Q�Ƃ���
			while(fgets(fbuff, STRLEN, in) != NULL){
				fprintf(tmp, "%s", fbuff);
			}

			fclose(tmp);
			fclose(in);

			//tmp�t�@�C�������̃t�@�C���Ƃ��ď㏑������
			system(move_command);
	}
	//�t�@�C�����J�����Ȃ���΃G���[���o�͂��I������
	else{
		fprintf(stderr, "File %s is not exist or invalid!\n", file_name);
		exit(1);
	}
}
