#include"StoreInformation.h"
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
	//4096�o�C�g���܂ł̕�����str����m�ۂ���
	strncpy(fileName, str, STORE_INFOMATION_SIZE);
}

/**
�ݒ肵���t�@�C�������Ăяo���B

@return �Ăяo���ꂽ�t�@�C������Ԃ�
*/
char *getFileName(){
	return fileName;
}
