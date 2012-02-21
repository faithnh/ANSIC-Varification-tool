#include <stdio.h>
#include <string.h>

#include "CharStringExtend.h"

/**
������source����J�n������start����w�肳�ꂽ������strlen���̕�����𒊏o���A���̌��ʂ𕶎���dest�֓����B
�܂��I�[�q���t���̂ŁA�����o���������{�P���̕����񂪕K�v

@param dest ���o���ʂ����镶����
@param source ���o�Ώۂ̕�����
@param start ���o�̊J�n�ʒu
@param str_length ���o���镶����

@return �����������ǂ����̃t���O ���������ꍇ�͂P�@�r���Œ��o�Ɏ��s�����ꍇ�͂O��Ԃ��B
*/
int str_extract(char *dest, char *source, int start, int str_length){
	//�����t���O
	int success_flag = 1;

	//source�̕�����
	int source_length;

	int source_iterator;
	int dest_iterator;

	source_length = strlen(source);

	//������source����J�n������start����w�肳�ꂽ������strlen���̕�����𒊏o���A���̌��ʂ𕶎���dest�֓����
	for(source_iterator = start, dest_iterator = 0;
		source_iterator < source_length && source_iterator < start + str_length;
		source_iterator++ , dest_iterator++){

			*(dest + dest_iterator) = *(source + source_iterator);

		}

	//�����Asource_iterator��source_length�ȏ�܂���dest_iteratror��dest_length�ȏ�ŁA�Ȃ�����source_iterator��start+strlen�����̏ꍇ
	if(source_iterator >= source_length && source_iterator < start + str_length){
		success_flag = 0;
	}
	*(dest + dest_iterator) = '\0';

	return success_flag;
}

/**
������source�͎��܂��͎��ʎq�ł��邩�ǂ����𒲂ׂ�B

@param source �Ώۂ̕�����

@return ���܂��͎��ʎq�ł���ꍇ�͂P�A�����łȂ��ꍇ�͂O��Ԃ��B
*/
int isExpression(char *source){
	int source_length = strlen(source);

	int source_iterator;

	int is_expression_flag = 0;
	//������source�𒲂ׂ�
	for(source_iterator = 0; source_iterator < source_length; source_iterator++){
		//�����A������󔒁A�I�[�A���s�ȊO�̕����������ꍇ�́A���܂��͎��ʎq�Ƃ݂Ȃ�
		if(('0' > source[source_iterator] || '9' < source[source_iterator]) &&
		 source[source_iterator] != ' ' && source[source_iterator] != '\0' &&
		  source[source_iterator] != '\n'){
			is_expression_flag = 1;
			break;
		}
	}

	return is_expression_flag;
}
