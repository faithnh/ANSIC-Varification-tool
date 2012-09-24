#include"StoreInformation.h"
#include"../Library/CSTLString.h"
#include<stdio.h>
#include<string.h>

#define STORE_INFOMATION_SIZE 4096

///�t�@�C�������m�ۂ��邽�߂̗̈�
char fileName[STORE_INFOMATION_SIZE]="";

/**
�t�@�C������ݒ肷��B4096�o�C�g���܂ł̕������m�ۂł��A����ȏ�͐؂�̂Ă���B

@param str �t�@�C����

@return �Ȃ�
*/
void setFileName(char *str){
	//�G���[�΍�̂��߁A�G�X�P�[�v�}�[�N\�����݂���ꍇ�́A\\�ɒu��������B
	CSTLString *tmp = CSTLString_new_assign(str);
	CSTLString_replace_string(tmp, "\\", "\\\\");

	//4096�o�C�g���܂ł̕������m�ۂ���
	strncpy(fileName, CSTLString_c_str(tmp), STORE_INFOMATION_SIZE);

	CSTLString_delete(tmp);
}

/**
�ݒ肵���t�@�C�������Ăяo���B

@return �Ăяo���ꂽ�t�@�C������Ԃ�
*/
char *getFileName(){
	return fileName;
}
