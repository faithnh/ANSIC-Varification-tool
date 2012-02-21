#include "CSTLString.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdarg.h>

#define STRLEN 1024

CSTL_STRING_IMPLEMENT(CSTLString, char)

/**
�w�肵��CSTL������target�ɑ΂��āA�u���Ώۂ̕�����search����u��������������replace�ɒu�����s���B
@param target �w�肵��CSTL������
@param search �u���Ώۂ̕�����
@param replace �u��������������

@return �Ȃ�
*/
void CSTLString_replace_string(CSTLString *target, char *search, char *replace){
	int location = CSTLString_find(target,search,0);
	while(location != CSTL_NPOS){
		CSTLString_replace(target, location, strlen(search), replace);
		location = CSTLString_find(target,search,location + strlen(replace));
	}
}
/**
�w�肵��CSTL������target1�Ɣ�r�Ώۂ̕��ʂ̕�����target2�Ɣ�r����B

@param target1 �w�肵��CSTL������
@param target2 ��r�Ώۂ̕��ʂ̕�����

@return ��r�������ʂ�Ԃ��A��v�����ꍇ�͂O�A�����łȂ��ꍇ�͂O�ȊO�̒l��Ԃ��B
*/
int CSTLString_compare_with_char(CSTLString *target1, char *target2){
	int compare;

	CSTLString *target_CSTLString2 = CSTLString_new();
	CSTLString_assign(target_CSTLString2,target2);

	compare = CSTLString_compare(target1, target_CSTLString2);
	CSTLString_delete(target_CSTLString2);

	return compare;
}

/**
�w�肵��CSTL������target1����A�w�肵��������del_str�̍ŏ��ɏo������ӏ��ȍ~��S�č폜����B

@param target1 �w�肵��CSTL������
@param del_str �폜����ꏊ���w�肷�邽�߂̕�����

@return �����������ǂ����ۂ���Ԃ��B���������ꍇ�͂P�A�����łȂ��ꍇ��0��Ԃ��B
 */
int CSTLString_delete_tail_str(CSTLString *target1, char *del_str){
	//�擪���當�����T������
	int location = CSTLString_find(target1, del_str, 0);


	//�w�肵���폜���镶������������ꍇ�A����ȍ~�̕���������ׂč폜����
	if(location != CSTL_NPOS){
		CSTLString_erase(target1, location, CSTLString_size(target1) - location);
		//�P��Ԃ�
		return 1;
	}else{
		//�����łȂ��ꍇ�͒T���Ɏ��s�����Ƃ��āA�O��Ԃ�
		return 0;
	}
}

/**
�w�肵��������source���ȈՔł̏����t�H�[�}�b�g�`���Ŏw�肵��CSTL������target�ɓ��͂���B
�ȈՔłȂ̂ŁA%d�A%f�A%s�A%d�A%%�ɂ����Ή����Ă��Ȃ��B\n�͉\�B
�܂��Aadd_flag���w�肷�邱�ƂŁA�ǉ��E����̑I�����ł���B
@param target ���͐�̎w�肵��CSTL������i���炩���ߏ���������K�v����j
@param add_flag �ǉ��}�����邩�ǂ����̃t���O�@�P�F�ǉ��@�O�F���
@param source �w�肵��������i�����t�H�[�}�b�g�`���j
@param ... �����ɑΉ������C�ӂ̈���
@return �Ȃ�
*/
void CSTLString_printf(CSTLString *target, int add_flag, char *source, ...){
	//�ϒ��������X�g
	va_list args;
	//�ϒ��������n�߂�
    va_start(args, source);

	//�����^�𕶎���ɕς��邽�߂̕�����ϐ�
	char toChar[STRLEN];

	//������𑖍�����ʒu
	int location;

	//������̒���
	int length = strlen(source);

	//�����̕�����̏�����
	if(add_flag == 0){
		CSTLString_assign(target, "");
	}
	for(location = 0; location < length ; location++){

		if( source[location] == '%'){
			if(location + 1 < length){
				//%d�������炻���������ł��鐮���ɐ؂�ւ���
				if(source[location + 1] == 'd'){
					int va_list = va_arg(args, int);
					snprintf(toChar, STRLEN, "%d", va_list);
					CSTLString_append(target, toChar);
				}
				//%f�������炻���������ł�������ɐ؂�ւ���
				else if(source[location + 1] == 'f'){
					double va_list = va_arg(args, double);
					snprintf(toChar, STRLEN, "%f", va_list);
					CSTLString_append(target, toChar);
				}
				//%s�������炻���������ł��镶����ɐ؂�ւ���
				else if(source[location + 1] == 's'){
					char *va_list = va_arg(args, char*);
					CSTLString_append(target, va_list);
				}
				//%c�������炻���������ł��镶���ɐ؂�ւ���
				else if(source[location + 1] == 'c'){
					int va_list = va_arg(args, int);
					CSTLString_push_back(target, (char)va_list);
				}
				//%%��������%�ɂ���B
				else if(source[location + 1] == '%'){
					CSTLString_push_back(target, '%');
				}
				//����ȊO��������A�G���[�Ƃ��ďo�͂���B
				else{
					fprintf(stderr, "������G���[�B'%%'�̂��Ƃ̓��͂��s���ł��I\n");
					exit(1);
				}
				location++;
			}else{
				fprintf(stderr, "������G���[�B'%%'�̂��Ƃ̓��͂��s���ł��I\n");
				exit(1);
			}
		}else{
			CSTLString_push_back(target, source[location]);
		}
	}
}

/**
�w�肵��������̑O�̔��p�X�y�[�X�E���s�����E�^�u���폜����B

@param target �w�肵��������
@return �Ȃ�
 */
void CSTLString_ltrim(CSTLString *target){
	while(*CSTLString_at(target, 0) == ' ' || *CSTLString_at(target, 0) == '\t' ||
			*CSTLString_at(target, 0) == '\n'){
		target = CSTLString_replace(target, 0, 1, "");
	}

}
