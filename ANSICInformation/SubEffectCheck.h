/*!
  @brief ���̃t�@�C���ɂ͕���p���̃`�F�b�N����֐��������̃^�C�v�����߂閽�߂��܂܂�Ă���B

  @file SubEffectCheck.h
  @author faithnh
 */
#ifndef SUBEFFECTCHECK_HEADDER
#define SUBEFFECTCHECK_HEADDER

#include"AST.h"
/**
�w�肳�ꂽAST�m�[�hnode����A����p��(�C���N�������g���E�f�N�������g���E�����)���܂܂�Ă��邩�ǂ����`�F�b�N����B

@param node �Ώۂ�AST�m�[�h

@return �܂܂�Ă��������C���N�������g���̏ꍇ�P�A�f�N�������g���̏ꍇ�Q�A������̏ꍇ�R�Ƃ���B�܂܂�Ă��Ȃ��ꍇ�͂O��Ԃ��B
 */

int checkContainSubEffectStatement(AST *node);

/**
������̃^�C�v���o�͂�����B

@param assignment_expression_list ������Ɋւ���AST�m�[�h�̃��X�g

@return ������̃^�C�v�ɉ������l��ԋp����B 0:=,1:+=,2:-=,3:*=,4:/=,5:%=,6:<<=,7:>>=,8:&=,9:|=,10:^=
 */
int getAssignment_TYPE(AST *assignment_expression_list);
#endif
