/*!
  @brief ���̃t�@�C���́ACSTL���C�u������p����������^CSTLString�𐶐�������A����Ɋւ��鑀����s�����߂̖��߂��܂܂�Ă���B

  @file CSTLString.h
  @author faithnh

 */
#ifndef CSTLSTRING_HEADDER
#define CSTLSTRING_HEADDER

#include <cstl/string.h>

/* string�̃C���^�[�t�F�C�X�Ǝ�����W�J */
CSTL_STRING_INTERFACE(CSTLString, char)

/**
�w�肵��CSTL������target�ɑ΂��āA�u���Ώۂ̕�����search����u��������������replace�ɒu�����s���B
@param target �w�肵��CSTL������
@param search �u���Ώۂ̕�����
@param replace �u��������������

@return �Ȃ�
*/
void CSTLString_replace_string(CSTLString *target, char *search, char *replace);

/**
�w�肵��CSTL������target1�Ɣ�r�Ώۂ̕��ʂ̕�����target2�Ɣ�r����B

@param target1 �w�肵��CSTL������
@param target2 ��r�Ώۂ̕��ʂ̕�����

@return ��r�������ʂ�Ԃ��A��v�����ꍇ�͂O�A�����łȂ��ꍇ�͂O�ȊO�̒l��Ԃ��B
*/
int CSTLString_compare_with_char(CSTLString *target1, char *target2);

/**
�w�肵��CSTL������target1����A�w�肵��������del_str�̍ŏ��ɏo������ӏ��ȍ~��S�č폜����B

@param target1 �w�肵��CSTL������
@param del_str �폜����ꏊ���w�肷�邽�߂̕�����

@return �����������ǂ����ۂ���Ԃ��B���������ꍇ�͂P�A�����łȂ��ꍇ��0��Ԃ��B
 */
int CSTLString_delete_tail_str(CSTLString *target1, char *del_str);

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
void CSTLString_printf(CSTLString *target, int add_flag, char *source, ...);

/**
�w�肵��������̑O�̔��p�X�y�[�X�E���s�����E�^�u���폜����B

@param target �w�肵��������
@return �Ȃ�
 */
void CSTLString_ltrim(CSTLString *target);

#endif
