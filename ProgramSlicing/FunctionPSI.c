#include"FunctionPSI.h"

#include<stdio.h>
#include<stdlib.h>

#include"../Library/CSTLString.h"

#include"../ANSICInformation/ANSIC_CODE.h"

/**
�֐���`��AST�m�[�hfunction_definition����A�֐��ɑ΂���v���O�����X���C�V���O�𒊏o���A
�v���O�����X���C�V���O���X�gexpr_slicing_list�ɒǉ�����B

@param expr_slicing_list �ǉ���̃v���O�����X���C�V���O���X�gexpr_slicing_list
@param function_definition �֐���`�Ɋւ���AST�m�[�h
@param parent �m�[�h��ǉ�����Ƃ��̐e�m�[�h

@return �ǉ������֐��̃X���C�V���O�ւ̃A�h���X��Ԃ�
 */
EXPR_SLICING *getFunctionPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *function_definition, EXPR_SLICING *parent){
	//�V�����v���O�����X���C�V���O�f�[�^
	EXPR_SLICING *new_expr_slicing = NULL;
	//�֐������擾�����ꍇ
	if(CSTLString_compare_with_char(function_definition->name,"function_definition_type_b") == 0){
		//��`���X�g�A�ˑ����X�g�A�q�f�[�^���X�g�P�A�q�f�[�^���X�g�Q��������Ԃɂ��Ă���
		ARRAY_OFFSET_LIST *target_variable = ARRAY_OFFSET_LIST_new();
		ARRAY_OFFSET_LIST *dependences =  ARRAY_OFFSET_LIST_new();
		EXPR_SLICING_LIST *children1 = EXPR_SLICING_LIST_new();
		EXPR_SLICING_LIST *children2 = EXPR_SLICING_LIST_new();

		//�e�m�[�h�������̃X���C�V���O���X�g���w���Ă���X���C�V���O�m�[�h�𐶐����A�X���C�V���O���X�g�ɓo�^����
		EXPR_SLICING_LIST_push_back_ref(expr_slicing_list,
				new_EXPR_SLICING(EXPR_SLICING_LIST_size(expr_slicing_list) + 1, function_definition, target_variable,
						dependences, children1, children2, parent));

		//�o�^�����������擾����
		new_expr_slicing = EXPR_SLICING_LIST_data(EXPR_SLICING_LIST_rbegin(expr_slicing_list));

		//�֐��Ăяo������p�����[�^��T���o���A�V�����v���O�����X���C�V���O�̎q�m�[�h�Ƃ��ēo�^����
		getParameterPSI(new_expr_slicing, ASTLIST_ITERATOR_2(function_definition), ASTLIST_ITERATOR_2(function_definition));




	}else{
		fprintf(stderr,"�s���ȃm�[�h%s�������܂���",CSTLString_c_str(function_definition->name));
		exit(1);
	}

	return new_expr_slicing;
}

/**
�p�����[�^���X�g�Ɋւ���AST�m�[�hparameter_node����֐���`�̃v���O�����X���C�V���O���X�gexpr_slicing_list�Ɋi�[���Ă���

@param expr_slicing �֐���`�̃v���O�����X���C�V���O
@param parameter_node �e�p�����[�^�̒�`���X�g
@param basis_parameter_node �p�����[�^���w��AST�m�[�h

@return �Ȃ�
 */
void getParameterPSI(EXPR_SLICING *expr_slicing, AST *parameter_node, AST *basis_parameter_node){
	ASTListIterator ast_p;
	//�����Aparameter_declaration_with_declarator��������ꂽ��ȉ��̑�����s��
	if(CSTLString_compare_with_char(parameter_node->name, "parameter_declaration_with_declarator") == 0){
		//�ϐ����E�|�C���^���x���E�z�񃌃x��
		CSTLString *variable_name = CSTLString_new();
		int pointer_level, array_level;

		//�ϐ������擾����
		getStringFromAST(variable_name, ASTLIST_ITERATOR_2(parameter_node));
		//�ϐ�������|�C���^���x���E�z�񃌃x�����擾����
		getPointerLevelAndArrayLevel(variable_name, &pointer_level, &array_level);
		//�ϐ�������A�|�C���^��z��������L�������ׂč폜����
		deletePointerAndArraySynbol(variable_name);
		//��`���X�g�A�ˑ����X�g�A�q�f�[�^���X�g�P�A�q�f�[�^���X�g�Q��������Ԃɂ��Ă���
		ARRAY_OFFSET_LIST *target_variable = ARRAY_OFFSET_LIST_new();
		ARRAY_OFFSET_LIST *dependences =  ARRAY_OFFSET_LIST_new();
		EXPR_SLICING_LIST *children1 = EXPR_SLICING_LIST_new();
		EXPR_SLICING_LIST *children2 = EXPR_SLICING_LIST_new();

		//��`���X�g�Ƀp�����[�^�̓��e��o�^����
		ARRAY_OFFSET_LIST_push_back_ref(target_variable, new_ARRAY_OFFSET(variable_name, basis_parameter_node, parameter_node, OFFSET_LIST_new(), pointer_level, array_level, 0, 0));

		EXPR_SLICING_LIST_push_back_ref(expr_slicing->children1, new_EXPR_SLICING(EXPR_SLICING_LIST_size(expr_slicing->children1) + 1, basis_parameter_node,target_variable, dependences, children1, children2, expr_slicing));

		//�p�����[�^�͏�Ɏg�p����悤�Ƀt���O�𗧂ĂĂ���
		EXPR_SLICING_LIST_data(EXPR_SLICING_LIST_rbegin(expr_slicing->children1))->flag = 1;
	}else{
		//�q�m�[�h�����ǂ�
		for(ast_p = ASTList_begin(parameter_node->children);
			ast_p != ASTList_end(parameter_node->children);
			ast_p = ASTList_next(ast_p)){
			getParameterPSI(expr_slicing, ASTList_data(ast_p), basis_parameter_node);
		}
	}
}
