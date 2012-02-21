#include"SubEffectCheck.h"
#include<stdlib.h>
#include<stdio.h>
#include"../Library/CSTLString.h"
#include"../ANSICInformation/ANSIC_CODE.h"

//����p�����܂܂�Ă��Ȃ��ꍇ
#define NOT_CONTAIN 0
//�ォ��A�C���N�������g���A�f�N�������g���A��������܂܂�Ă����ꍇ
#define CONTAIN_INC 1
#define CONTAIN_DEC 2
#define CONTAIN_ASI 3

//������Z�q�������Ƃ����t���O0:=,1:+=,2:-=,3:*=,4:/=,5:%=,6:<<=,7:>>=,8:&=,9:|=,10:^=
#define EQUAL 0
#define PLUS_EQUAL 1
#define MINUS_EQUAL 2
#define MUL_EQUAL 3
#define DIV_EQUAL 4
#define MOD_EQUAL 5
#define LEFT_EQUAL 6
#define RIGHT_EQUAL 7
#define AND_EQUAL 8
#define OR_EQUAL 9
#define XOR_EQUAL 10

/**
�w�肳�ꂽAST�m�[�hnode����A����p��(�C���N�������g���E�f�N�������g���E�����)���܂܂�Ă��邩�ǂ����`�F�b�N����B

@param node �Ώۂ�AST�m�[�h

@return �܂܂�Ă��������C���N�������g���̏ꍇ�P�A�f�N�������g���̏ꍇ�Q�A������̏ꍇ�R�Ƃ���B�܂܂�Ă��Ȃ��ꍇ�͂O��Ԃ��B
 */

int checkContainSubEffectStatement(AST *node){
	int contain_flag = NOT_CONTAIN;
	ASTListIterator ast_p;
	//�C���N�������g�������������ꍇ�A�C���N�������g�����܂܂�Ă���Ƃ����t���O�̒l�ŕԂ�
	if(CSTLString_compare_with_char(node->name, "inc_expr") == 0 ||
			CSTLString_compare_with_char(node->name, "inc_after_expr") == 0){
		return CONTAIN_INC;
	}
	//�f�N�������g�������������ꍇ�A�f�N�������g�����܂܂�Ă���Ƃ����t���O�̒l�ŕԂ�
	else if(CSTLString_compare_with_char(node->name, "dec_expr") == 0 ||
			CSTLString_compare_with_char(node->name, "dec_after_expr") == 0){
		return CONTAIN_DEC;
	}
	//����������������ꍇ�A��������܂܂�Ă���Ƃ����t���O�̒l�ŕԂ�
	else if(CSTLString_compare_with_char(node->name, "assignment_expression") == 0){
		return CONTAIN_ASI;
	}
	//�����łȂ���΁A�q�m�[�h���T������
	else{
		for(ast_p = ASTList_begin(node->children);
				contain_flag == NOT_CONTAIN && ast_p != ASTList_end(node->children);
				ast_p = ASTList_next(ast_p)){

			contain_flag = checkContainSubEffectStatement(ASTList_data(ast_p));
		}
	}

	return contain_flag;
}

/**
������̃^�C�v���o�͂�����B

@param assignment_expression_list ������Ɋւ���AST�m�[�h�̃��X�g

@return ������̃^�C�v�ɉ������l��ԋp����B 0:=,1:+=,2:-=,3:*=,4:/=,5:%=,6:<<=,7:>>=,8:&=,9:|=,10:^=
 */
int getAssignment_TYPE(AST *assignment_expression_list){
	int a_op_flag;
	if(CSTLString_compare_with_char(assignment_expression_list->name, "assignment_expression") == 0){
		//������̃^�C�v�����߂�

		CSTLString *a_op_string = CSTLString_new();
		//������Z�q���擾����
		getStringFromAST(a_op_string, ASTLIST_ITERATOR_2(assignment_expression_list));

		//����=�̏ꍇ
		if(CSTLString_compare_with_char(a_op_string, "=") == 0){
			a_op_flag = EQUAL;
		}
		//����+=�̏ꍇ
		else if(CSTLString_compare_with_char(a_op_string, "+=") == 0){
			a_op_flag = PLUS_EQUAL;
		}
		//����-=�̏ꍇ
		else if(CSTLString_compare_with_char(a_op_string, "-=") == 0){
			a_op_flag = MINUS_EQUAL;
		}
		//����*=�̏ꍇ
		else if(CSTLString_compare_with_char(a_op_string, "*=") == 0){
			a_op_flag = MUL_EQUAL;
		}
		//����/=�̏ꍇ
		else if(CSTLString_compare_with_char(a_op_string, "/=") == 0){
			a_op_flag = DIV_EQUAL;
		}
		//����%=�̏ꍇ
		else if(CSTLString_compare_with_char(a_op_string, "%=") == 0){
			a_op_flag = MOD_EQUAL;
		}
		//����<<=�̏ꍇ
		else if(CSTLString_compare_with_char(a_op_string, "<<=") == 0){
			a_op_flag = LEFT_EQUAL;
		}
		//����>>=�̏ꍇ
		else if(CSTLString_compare_with_char(a_op_string, ">>=") == 0){
			a_op_flag = RIGHT_EQUAL;
		}
		//����&=�̏ꍇ
		else if(CSTLString_compare_with_char(a_op_string, "&=") == 0){
			a_op_flag = AND_EQUAL;
		}
		//����|=�̏ꍇ
		else if(CSTLString_compare_with_char(a_op_string, "|=") == 0){
			a_op_flag = OR_EQUAL;
		}
		//����^=�̏ꍇ
		else if(CSTLString_compare_with_char(a_op_string, "^=") == 0){
			a_op_flag = XOR_EQUAL;
		}else {
			fprintf(stderr,"#%s#:%d:Invalid Assignment Operator!!",
					getFileName(), ASTList_data(ASTList_next(ASTList_begin(assignment_expression_list->children)))->line);
			exit(1);
		}
		CSTLString_delete(a_op_string);
	}else{
		fprintf(stderr,"�s���ȃm�[�h%s�������܂���",CSTLString_c_str(assignment_expression_list->name));
		exit(1);
	}

	return a_op_flag;
}
