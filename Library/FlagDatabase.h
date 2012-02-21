/*!
  @brief ���̃t�@�C���́A�{�̂Ɋւ���t���O�ݒ���i�[���邽�߂̖��߂��܂܂�Ă���B
  ���Ƃ��΁Axml�Ƃ��ďo�͂���Ƃ��ȂǂƂ������ݒ肪�܂܂�Ă���B

  @file FlagDatabase.h
  @author faithnh

 */

#ifndef FLAGDATABASE_HEADDER
#define FLAGDATABASE_HEADDER



/**
�v���O�����̈�������t���O�f�[�^�x�[�X���擾����B
�����ŕs���Ƀt���O���ݒ肳��Ă����ꍇ�i���݂��Ȃ��t���O������E�t���O����d�ɒ�`����Ă���ꍇ�j�A
�G���[��Ԃ��A�����I�������B

@param argc �����t���O�̐�
@param argv �����t���O�̕�����

@return ��������擾�����t���O���擾����
*/
int getFlagDatabase(int argc, char * argv[]);

/**
�t���O�f�[�^�x�[�X����AXML_MODE���܂܂�Ă��邩�ǂ����m�F����B
@param flag_database �t���O�f�[�^�x�[�X

@return XML_MODE���܂܂�Ă�����P��Ԃ��A�����łȂ���΂O��Ԃ��B
*/
int isXmlMode(int flag_database);

/**
�t���O�f�[�^�x�[�X����AHELP_MODE���܂܂�Ă��邩�ǂ����m�F����B
@param flag_database �t���O�f�[�^�x�[�X

@return HELP_MODE���܂܂�Ă�����P��Ԃ��A�����łȂ���΂O��Ԃ��B
*/
int isHelpMode(int flag_database);

/**
�t���O�f�[�^�x�[�X����AARRAY_UNBOUND_CHECK_MODE���܂܂�Ă��邩�ǂ����m�F����B
@param flag_database �t���O�f�[�^�x�[�X

@return ARRAY_UNBOUND_CHECK_MODE���܂܂�Ă�����P��Ԃ��A�����łȂ���΂O��Ԃ��B
*/
int isArrayUnboundCheckMode(int flag_database);

/**
�t���O�f�[�^�x�[�X����AUNDEFINE_CONTROL_CHECK_MODE���܂܂�Ă��邩�ǂ����m�F����B
@param flag_database �t���O�f�[�^�x�[�X

@return UNDEFINE_CONTROL_CHECK_MODE���܂܂�Ă�����P��Ԃ��A�����łȂ���΂O��Ԃ��B
*/
int isUndefineControlCheckMode(int flag_database);

/**
�t���O�f�[�^�x�[�X����AZERO_DIVITION_CHECK_MODE���܂܂�Ă��邩�ǂ����m�F����B
@param flag_database �t���O�f�[�^�x�[�X

@return ZERO_DIVITION_CHECK_MODE���܂܂�Ă�����P��Ԃ��A�����łȂ���΂O��Ԃ��B
*/
int isZeroDivitionCheckMode(int flag_database);

/**
�t���O�f�[�^�x�[�X����AFREE_VIOLATION_CHECK_MODE���܂܂�Ă��邩�ǂ����m�F����B
@param flag_database �t���O�f�[�^�x�[�X

@return FREE_VIOLATION_CHECK_MODE���܂܂�Ă�����P��Ԃ��A�����łȂ���΂O��Ԃ��B
*/
int isFreeViolationCheckMode(int flag_database);

/**
�t���O�f�[�^�x�[�X����APROGRAM_SLICING_MODE���܂܂�Ă��邩�ǂ����m�F����B
@param flag_database �t���O�f�[�^�x�[�X

@return PROGRAM_SLICING_MODE���܂܂�Ă�����P��Ԃ��A�����łȂ���΂O��Ԃ��B
*/
int isProgramSlicingMode(int flag_database);

#endif
