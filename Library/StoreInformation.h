/*!
  @brief ����̓t�@�C�����ȂǂƂ������v���O�������ŋ��ʂ��镔�����m�ۂ��邽�߂̖��߂��܂܂�Ă���B
  ��Ƀt�@�C�����Ȃǂ��m�ۂ���B

  @file StoreInformation.h
  @author faithnh
 */

#ifndef STORE_INFORMATION_HEADDER
#define STORE_INFORMATION_HEADDER

/**
�t�@�C������ݒ肷��B4096�o�C�g���܂ł̕������m�ۂł��A����ȏ�͐؂�̂Ă���B

@param str �t�@�C����

@return �Ȃ�
*/
void setFileName(char *str);
/**
�ݒ肵���t�@�C�������Ăяo���B

@return �Ăяo���ꂽ�t�@�C������Ԃ�
*/
char *getFileName();
#endif
