#include "FlagDatabase.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//XML���[�h�̃t���O�̐��l�ƕ�����Ǝ擾��
#define XML_OUTPUT_MODE 1
#define XML_OUTPUT_MODE_STRING "--xml"
#define GET_XML_OUTPUT_MODE flag_database % 2
//�w���v���[�h�̃t���O�̐��l�ƕ�����Ǝ擾��
#define HELP_MODE 2
#define HELP_MODE_STRING "--h"
#define GET_HELP_MODE (flag_database >> 1) % 2
//�z��͈͊O�Q�ƃ`�F�b�N���[�h�̃t���O�̐��l�ƕ�����Ǝ擾��
#define ARRAY_UNBOUND_CHECK_MODE 4
#define ARRAY_UNBOUND_CHECK_MODE_STRING "--array-unbound-check"
#define GET_ARRAY_UNBOUND_CHECK_MODE (flag_database >> 2) % 2
//����`����`�F�b�N���[�h(����`�|�C���^�̎Q�ƂȂ�)�̃t���O�̐��l�ƕ�����Ǝ擾��
#define UNDEFINE_CONTROL_CHECK_MODE 8
#define UNDEFINE_CONTROL_CHECK_MODE_STRING "--undefined-control-check"
#define GET_UNDEFINE_CONTROL_CHECK_MODE (flag_database >> 3) % 2
//�[�����Z�`�F�b�N���[�h�̃t���O�̐��l�ƕ�����Ǝ擾��
#define ZERO_DIVITION_CHECK_MODE 16
#define ZERO_DIVITION_CHECK_MODE_STRING "--zero-division-check"
#define GET_ZERO_DIVITION_CHECK_MODE (flag_database >> 4) % 2
//�[�����Z�`�F�b�N���[�h�̃t���O�̐��l�ƕ�����Ǝ擾��
#define ZERO_DIVITION_CHECK_MODE 16
#define ZERO_DIVITION_CHECK_MODE_STRING "--zero-division-check"
#define GET_ZERO_DIVITION_CHECK_MODE (flag_database >> 4) % 2
//����������֌W�̕s���`�F�b�N���[�h�̃t���O�̐��l�ƕ�����Ǝ擾��
#define FREE_VIOLATION_CHECK_MODE 32
#define FREE_VIOLATION_CHECK_MODE_STRING "--free-violation-check"
#define GET_FREE_VIOLATION_CHECK_MODE (flag_database >> 5) % 2
//�v���O�����X���C�V���O���[�h�̃t���O�̐��l�ƕ�����Ǝ擾��
#define PROGRAM_SLICING_MODE 64
#define PROGRAM_SLICING_MODE_STRING "--program-slicing-mode"
#define GET_PROGRAM_SLICING_MODE (flag_database >> 6) % 2
//�ȈՔŃ��[�h�̃t���O�̐��l�ƕ�����Ǝ擾��
#define SIMPLE_MODE 64
#define SIMPLE_MODE_STRING "--simple-mode"
#define GET_SIMPLE_MODE (flag_database >> 7) % 2

/**
�v���O�����̈�������t���O�f�[�^�x�[�X���擾����B
�����ŕs���Ƀt���O���ݒ肳��Ă����ꍇ�i���݂��Ȃ��t���O������E�t���O����d�ɒ�`����Ă���ꍇ�j�A
�G���[��Ԃ��A�����I�������B

@param argc �����t���O�̐�
@param argv �����t���O�̕�����

@return ��������擾�����t���O���擾����B
*/
int getFlagDatabase(int argc, char * argv[]){

	int i;
	int flag_database = 0;

	for(i = 1; i < argc; i++){
		//�t���O�ł���ꍇ
		if(strlen(argv[i]) >= 2 && argv[i][0] == '-' && argv[i][1] == '-'){
			//�w�l�k���[�h�������t���O�ł���ꍇ
			if(strcmp(argv[i], XML_OUTPUT_MODE_STRING) == 0){
				//�w�l�k���[�h����d�ɒ�`����Ă��Ȃ����ǂ������ׂ�B��d�ɒ�`����Ă�����G���[��Ԃ��A�����I�������B
				if(!isXmlMode(flag_database)){
					flag_database += XML_OUTPUT_MODE;
				}else{
					fprintf(stderr,"�t���O����d�ł��I\n");
					exit(1);
				}
			}
			//�w���v���[�h
			else if(strcmp(argv[i], HELP_MODE_STRING) == 0){
				//�w���v���[�h����d�ɒ�`����Ă��Ȃ����ǂ������ׂ�B��d�ɒ�`����Ă�����G���[��Ԃ��A�����I�������B
				if(!isHelpMode(flag_database)){
					flag_database += HELP_MODE;
				}else{
					fprintf(stderr,"�t���O����d�ł��I\n");
					exit(1);
				}
			}
			//�z��͈͊O�Q�ƃ`�F�b�N���[�h
			else if(strcmp(argv[i], ARRAY_UNBOUND_CHECK_MODE_STRING) == 0){
				//�z��͈͊O�Q�ƃ`�F�b�N���[�h����d�ɒ�`����Ă��Ȃ����ǂ������ׂ�B��d�ɒ�`����Ă�����G���[��Ԃ��A�����I�������B
				if(!isArrayUnboundCheckMode(flag_database)){
					flag_database += ARRAY_UNBOUND_CHECK_MODE;
				}else{
					fprintf(stderr,"�t���O����d�ł��I\n");
					exit(1);
				}
			}
			//����`����`�F�b�N���[�h
			else if(strcmp(argv[i], UNDEFINE_CONTROL_CHECK_MODE_STRING) == 0){
				//����`����`�F�b�N���[�h����d�ɒ�`����Ă��Ȃ����ǂ������ׂ�B��d�ɒ�`����Ă�����G���[��Ԃ��A�����I�������B
				if(!isUndefineControlCheckMode(flag_database)){
					flag_database += UNDEFINE_CONTROL_CHECK_MODE;
				}else{
					fprintf(stderr,"�t���O����d�ł��I\n");
					exit(1);
				}
			}
			//�[�����Z�`�F�b�N���[�h
			else if(strcmp(argv[i], ZERO_DIVITION_CHECK_MODE_STRING) == 0){
				//�[�����Z�`�F�b�N���[�h����d�ɒ�`����Ă��Ȃ����ǂ������ׂ�B��d�ɒ�`����Ă�����G���[��Ԃ��A�����I�������B
				if(!isZeroDivitionCheckMode(flag_database)){
					flag_database += ZERO_DIVITION_CHECK_MODE;
				}else{
					fprintf(stderr,"�t���O����d�ł��I\n");
					exit(1);
				}
			}
			//����������̕s���`�F�b�N���[�h
			else if(strcmp(argv[i], FREE_VIOLATION_CHECK_MODE_STRING) == 0){
				//�[�����Z�`�F�b�N���[�h����d�ɒ�`����Ă��Ȃ����ǂ������ׂ�B��d�ɒ�`����Ă�����G���[��Ԃ��A�����I�������B
				if(!isFreeViolationCheckMode(flag_database)){
					flag_database += FREE_VIOLATION_CHECK_MODE;
				}else{
					fprintf(stderr,"�t���O����d�ł��I\n");
					exit(1);
				}
			}
			//�v���O�����X���C�V���O���[�h
			else if(strcmp(argv[i], PROGRAM_SLICING_MODE_STRING) == 0){
				//�[�����Z�`�F�b�N���[�h����d�ɒ�`����Ă��Ȃ����ǂ������ׂ�B��d�ɒ�`����Ă�����G���[��Ԃ��A�����I�������B
				if(!isProgramSlicingMode(flag_database)){
					flag_database += PROGRAM_SLICING_MODE;
				}else{
					fprintf(stderr,"�t���O����d�ł��I\n");
					exit(1);
				}
			}
			//�V���v�����[�h
			else if(strcmp(argv[i], SIMPLE_MODE_STRING) == 0){
				//�V���v�����[�h����d�ɒ�`����Ă��Ȃ����ǂ������ׂ�B��d�ɒ�`����Ă�����G���[��Ԃ��A�����I�������B
				if(!isSimpleMode(flag_database)){
					flag_database += SIMPLE_MODE;
				}else{
					fprintf(stderr,"�t���O����d�ł��I\n");
					exit(1);
				}
			}
			//��������Y�����Ȃ������ꍇ�́A����`�̃t���O�Ƃ��ăG���[��Ԃ��A�����I�������B
			else{
				fprintf(stderr, "����`�̃t���O %s\n", argv[i]);
				exit(1);
			}
		}
	}

	return flag_database;
}

/**
�t���O�f�[�^�x�[�X����AXML_MODE���܂܂�Ă��邩�ǂ����m�F����B
@param flag_database �t���O�f�[�^�x�[�X

@return XML_MODE���܂܂�Ă�����P��Ԃ��A�����łȂ���΂O��Ԃ��B
*/
int isXmlMode(int flag_database){
	return GET_XML_OUTPUT_MODE;
}

/**
�t���O�f�[�^�x�[�X����AHELP_MODE���܂܂�Ă��邩�ǂ����m�F����B
@param flag_database �t���O�f�[�^�x�[�X

@return HELP_MODE���܂܂�Ă�����P��Ԃ��A�����łȂ���΂O��Ԃ��B
*/
int isHelpMode(int flag_database){
	return GET_HELP_MODE;
}

/**
�t���O�f�[�^�x�[�X����AARRAY_UNBOUND_CHECK_MODE���܂܂�Ă��邩�ǂ����m�F����B
@param flag_database �t���O�f�[�^�x�[�X

@return ARRAY_UNBOUND_CHECK_MODE���܂܂�Ă�����P��Ԃ��A�����łȂ���΂O��Ԃ��B
*/
int isArrayUnboundCheckMode(int flag_database){
	return GET_ARRAY_UNBOUND_CHECK_MODE;
}

/**
�t���O�f�[�^�x�[�X����AUNDEFINE_CONTROL_CHECK_MODE���܂܂�Ă��邩�ǂ����m�F����B
@param flag_database �t���O�f�[�^�x�[�X

@return UNDEFINE_CONTROL_CHECK_MODE���܂܂�Ă�����P��Ԃ��A�����łȂ���΂O��Ԃ��B
*/
int isUndefineControlCheckMode(int flag_database){
	return GET_UNDEFINE_CONTROL_CHECK_MODE;
}

/**
�t���O�f�[�^�x�[�X����AZERO_DIVITION_CHECK_MODE���܂܂�Ă��邩�ǂ����m�F����B
@param flag_database �t���O�f�[�^�x�[�X

@return ZERO_DIVITION_CHECK_MODE���܂܂�Ă�����P��Ԃ��A�����łȂ���΂O��Ԃ��B
*/
int isZeroDivitionCheckMode(int flag_database){
	return GET_ZERO_DIVITION_CHECK_MODE;
}

/**
�t���O�f�[�^�x�[�X����AFREE_VIOLATION_CHECK_MODE���܂܂�Ă��邩�ǂ����m�F����B
@param flag_database �t���O�f�[�^�x�[�X

@return FREE_VIOLATION_CHECK_MODE���܂܂�Ă�����P��Ԃ��A�����łȂ���΂O��Ԃ��B
*/
int isFreeViolationCheckMode(int flag_database){
	return GET_FREE_VIOLATION_CHECK_MODE;
}

/**
�t���O�f�[�^�x�[�X����APROGRAM_SLICING_MODE���܂܂�Ă��邩�ǂ����m�F����B
@param flag_database �t���O�f�[�^�x�[�X

@return PROGRAM_SLICING_MODE���܂܂�Ă�����P��Ԃ��A�����łȂ���΂O��Ԃ��B
*/
int isProgramSlicingMode(int flag_database){
	return GET_PROGRAM_SLICING_MODE;
}

/**
�t���O�f�[�^�x�[�X����ASIMPLE_MODE���܂܂�Ă��邩�ǂ����m�F����B
@param flag_database �t���O�f�[�^�x�[�X

@return SIMPLE_MODE���܂܂�Ă�����P��Ԃ��A�����łȂ���΂O��Ԃ��B
*/
int isSimpleMode(int flag_database){
	return GET_SIMPLE_MODE;
}
