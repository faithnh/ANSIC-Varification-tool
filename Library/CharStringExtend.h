/*!
  @brief ���̃t�@�C���́Astring.h�ɂȂ��悤�ȏ��������������邽�߂̖��߂��܂܂�Ă���B
  ��̓I�ɂ͕����񂩂炠��ꏊ���炠��ꏊ�܂ł𒊏o������Ƃ��������Ƃ��ł���B

  @file CharStringExtend.h
  @author faithnh

 */

#ifndef CHAR_STRING_EXTEND_HEADDER
#define CHAR_STRING_EXTEND_HEADDER

/**
������source����J�n������start����w�肳�ꂽ������strlen���̕�����𒊏o���A���̌��ʂ𕶎���dest�֓����B
�܂��I�[�q���t���̂ŁA�����o���������{�P���̕����񂪕K�v

@param dest ���o���ʂ����镶����
@param source ���o�Ώۂ̕�����
@param start ���o�̊J�n�ʒu
@param str_length ���o���镶����

@return �����������ǂ����̃t���O ���������ꍇ�͂P�@�r���Œ��o�Ɏ��s�����ꍇ�͂O��Ԃ��B
*/
int str_extract(char *dest, char *source, int start, int str_length);

/**
������source�͎��ł��邩�ǂ����𒲂ׂ�B

@param source �Ώۂ̕�����

@return ���ł���ꍇ�͂P�A�����łȂ��ꍇ�͂O��Ԃ��B

*/
int isExpression(char *source);

#endif
