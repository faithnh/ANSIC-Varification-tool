/*!
  @brief ����͊Ȍ����̂��߂ɕϐ���`�𕪊������邽�߂̂��̂ł���B
�@��Fint a,b = 1; �� int a; int b = 1;
  @file DivitionDeclarator.h
  @author faithnh
 */

#ifndef DIVITIONDECLARATOR_H_
#define DIVITIONDECLARATOR_H_

#include"AST.h"
#include"Synbol.h"
/**
�ϐ���`�𕪊���������Ԃŏo�͂�����B
�@��Fint a,b = 1; �� int a; int b = 1;
@param output �o�͐�̃t�@�C���\����
@param programAST �v���O�����ɑ΂���AST
@param variable_table_list �ϐ��e�[�u��

@return �Ȃ�
 */
void OutputSourceAfterDivitionDeclarator(FILE *output, AST *programAST, VARIABLE_TABLE_LIST *variable_table_list);

#endif /* DIVITIONDECLARATOR_H_ */
