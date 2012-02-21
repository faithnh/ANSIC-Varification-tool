#include"ProgramSlicingInformation.h"
#include"../ANSICInformation/ANSIC_CODE.h"
#include<stdlib.h>

CSTL_LIST_IMPLEMENT(DD_INFORMATION_LIST, DD_INFORMATION)

CSTL_LIST_IMPLEMENT(EXPR_SLICING_LIST, struct expr_slicing)

/**
�X���C�V���O���s�����߂̍\���̂𐶐�����B
@param expr_slicing_number �Ώۂ̎��ɑ΂���AST�ԍ�
@param expression �Ώۂ̎��ւ̂`�r�s�m�[�h
@param target_variable �ϐ��̃I�t�Z�b�g���X�g
@param dependences �ˑ��֌W�̔z��I�t�Z�b�g���X�g
@param children1 if��while�Afor�ɑ΂���X���C�V���O���X�g
@param children2 else���ɑ΂���X���C�V���O���X�g
@param parent �e�����ǂ邽�߂̃m�[�h

@return �������ꂽ�X���C�V���O���s�����߂̍\���̂ւ̃A�h���X��Ԃ�

*/
EXPR_SLICING *new_EXPR_SLICING(int expr_slicing_number, AST *expression, ARRAY_OFFSET_LIST *target_variable,
		ARRAY_OFFSET_LIST *dependences,EXPR_SLICING_LIST *children1, EXPR_SLICING_LIST *children2,
		EXPR_SLICING *parent ){
	EXPR_SLICING *new_expr_slicing = (EXPR_SLICING*)malloc(sizeof(EXPR_SLICING));

	//������������̂ɐ��������ꍇ
	if(new_expr_slicing != NULL){
		//�����ɂ����������
		new_expr_slicing->expr_slicing_number = expr_slicing_number;
		new_expr_slicing->expression = expression;
		new_expr_slicing->target_variable = target_variable;
		new_expr_slicing->dependences = dependences;
		new_expr_slicing->children1 = children1;
		new_expr_slicing->children2 = children2;
		new_expr_slicing->parent = parent;

		//DD���X�g�i�f�[�^�ˑ��֌W�̃��X�g�j�͏������������Ă���
		new_expr_slicing->dd_list = DD_INFORMATION_LIST_new();
		//�g�p���Ă��邩�ǂ����������t���O�͕K��0(���g�p���)�ɂ��Ă���
		new_expr_slicing->flag = 0;
	}
	//�V�����X���C�V���O���s�����߂̍\���̂𐶐����邽�߂Ɋm�ۂ���̂Ɏ��s�����ꍇ�̓������s���Ƃ��ăG���[���o�������I��������
	else{
		fprintf(stderr,"�������s���ł�!\n");
		exit(1);
	}

	return new_expr_slicing;
}

/**
�f�[�^�ˑ��֌W�Ɋւ�����𐶐�����B
@param dd_variable_name �f�[�^�ˑ��֌W�Ɋւ���ϐ���
@param *dd_target �f�[�^�ˑ��֌W�̃^�[�Q�b�g�ƂȂ閽��

@return �������ꂽ�f�[�^�ˑ��֌W�Ɋւ�����̍\���̂ւ̃A�h���X��Ԃ�

*/
DD_INFORMATION *new_DD_INFORMATION(CSTLString *dd_variable_name, EXPR_SLICING *dd_target){
	DD_INFORMATION *new_dd_information = (DD_INFORMATION*)malloc(sizeof(DD_INFORMATION));

	//������������̂ɐ��������ꍇ
	if(new_dd_information != NULL){
		new_dd_information->dd_variable_name = dd_variable_name;
		new_dd_information->dd_target = dd_target;
	}
	//�����Ɏ��s�����ꍇ�̓������s���Ƃ��ăG���[���o�͂��A�����I��������
	else{
		fprintf(stderr,"�������s���ł�!\n");
		exit(1);
	}

	return new_dd_information;

}

/**
�w�肵���f�[�^�ˑ��֌W�̃��X�g����A�w�肳�ꂽ�ϐ��������݂��邩���ׂ�B

@param variable_name �w�肳�ꂽ�ϐ���
@param dd_information_list �w�肵���f�[�^�ˑ��֌W�̃��X�g
@param find_dd_informaiton �������ꍇ�ɕԂ��f�[�^�ˑ��֌W�̏��
@return ���݂���ꍇ�͂P�A�����łȂ��ꍇ�͂O��Ԃ�
 */
int searchDD(CSTLString *variable_name, DD_INFORMATION_LIST *dd_information_list, DD_INFORMATION **find_dd_informaiton){
	int find_flag = 0;

	DD_INFORMATION_LISTIterator dd_i;
	//�f�[�^�ˑ��֌W��T������
	for(dd_i = DD_INFORMATION_LIST_begin(dd_information_list);
		dd_i != DD_INFORMATION_LIST_end(dd_information_list);
		dd_i = DD_INFORMATION_LIST_next(dd_i)){

		//�����A�ϐ��錾�̑Ώۂ̕ϐ�����w�肳�ꂽ�ϐ�����������ꂽ��A�P��ݒ肵�A�T�����I��������
		if(searchARRAY_OFFSET_LIST(DD_INFORMATION_LIST_data(dd_i)->dd_target->target_variable, variable_name) != NULL){
			find_flag = 1;
			*find_dd_informaiton = DD_INFORMATION_LIST_data(dd_i);
			break;
		}

	}

	return find_flag;
}
/**
�w�肵���v���O�����X���C�V���O���̃f�[�^�ˑ��֌W����A�w�肳�ꂽ�ϐ����ł���ϐ��錾�����݂��邩���ׂ�B

@param variable_name �w�肳�ꂽ�ϐ���
@param expr_slicing �w�肵���v���O�����X���C�V���O���̃f�[�^

@return ���݂���ꍇ�͂P�A�����łȂ��ꍇ�͂O��Ԃ��B
 */
int searchDeclarationDD(CSTLString *variable_name, EXPR_SLICING *expr_slicing){
	int find_flag = 0;

	DD_INFORMATION_LISTIterator dd_i;
	//�f�[�^�ˑ��֌W��T������
	for(dd_i = DD_INFORMATION_LIST_begin(expr_slicing->dd_list);
		dd_i != DD_INFORMATION_LIST_end(expr_slicing->dd_list);
		dd_i = DD_INFORMATION_LIST_next(dd_i)){

		//�ϐ��錾�܂��͈����錾���������ꍇ
		if(CSTLString_compare_with_char(DD_INFORMATION_LIST_data(dd_i)->dd_target->expression->name, "declaration_with_init") == 0 ||
				CSTLString_compare_with_char(DD_INFORMATION_LIST_data(dd_i)->dd_target->expression->name, "declarator") == 0){
			//�����A�ϐ��錾�̑Ώۂ̕ϐ�����w�肳�ꂽ�ϐ�����������ꂽ��A�P��ݒ肵�A�T�����I��������
			if(searchARRAY_OFFSET_LIST(DD_INFORMATION_LIST_data(dd_i)->dd_target->target_variable, variable_name) != NULL){
				find_flag = 1;
				break;
			}

		}

	}

	return find_flag;
}

/**
�v���O�����X���C�V���O��flag������������B
@param expr_slicing_list �Ώۂ̃v���O�����X���C�V���O���̃��X�g

@return �Ȃ�
 */
void initExprSlicingListFlag(EXPR_SLICING_LIST *expr_slicing_list){
	EXPR_SLICING_LISTIterator e_i;
	//�v���O�����X���C�V���O���X�g��񂩂�P���Q�Ƃ���
	for(e_i = EXPR_SLICING_LIST_begin(expr_slicing_list);
		e_i != EXPR_SLICING_LIST_end(expr_slicing_list);
		e_i = EXPR_SLICING_LIST_next(e_i)){

		//flag��0�ɂ���
		EXPR_SLICING_LIST_data(e_i)->flag = 0;

		//children1,children2�ɂ��Ă������������s��
		initExprSlicingListFlag(EXPR_SLICING_LIST_data(e_i)->children1);
		initExprSlicingListFlag(EXPR_SLICING_LIST_data(e_i)->children2);

	}

}

/**
�v���O�����S�̂̃v���O�����X���C�V���O���X�gexpr_slicing_list����A
�֐��Ăяo���ɑΉ�����֐���`�̃v���O�����X���C�V���O�����擾����B

@param function_name �֐���
@param expr_slicing_list �v���O�����S�̂̃v���O�����X���C�V���O���X�g

@return �擾�ɐ��������ꍇ�A�֐��Ăяo���ɑΉ�����֐���`�ւ̃v���O�����X���C�V���O����Ԃ��A���s�����ꍇ��NULL��Ԃ��B
 */
EXPR_SLICING *searchFunctionPSI(CSTLString *function_name, EXPR_SLICING_LIST *expr_slicing_list){
	EXPR_SLICING *result = NULL;

	EXPR_SLICING_LISTIterator e_i;
	CSTLString *epsi_function_name = CSTLString_new();

	//�v���O�����S�̂̃v���O�����X���C�V���O���X�g��T������
	for(e_i = EXPR_SLICING_LIST_begin(expr_slicing_list);
		e_i != EXPR_SLICING_LIST_end(expr_slicing_list);
		e_i = EXPR_SLICING_LIST_next(e_i)){

		//�����A�֐���`�̃v���O�����X���C�V���O�����������ꍇ
		if(CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "function_definition_type_b") == 0){


			//�֐������擾����
			getStringFromAST(epsi_function_name, ASTLIST_ITERATOR_2(EXPR_SLICING_LIST_data(e_i)->expression));
			//�֐�������p�����[�^�Ȃǂ̗]���ȏ����폜����
			deleteParameterDefine(epsi_function_name);
			//�擾�����֐������A�T�������֐����ł���ꍇ�͂��̃v���O�����X���C�V���O�����擾���A�T�����I��������
			if(CSTLString_compare(epsi_function_name, function_name) == 0){
				result = EXPR_SLICING_LIST_data(e_i);
				break;
			}
		}
	}

	return result;
}

/**
�֐����ň����O���[�o���ϐ��𒊏o���A�z��I�t�Z�b�g���X�g�Ƃ��Ē��o����B

@param output_global_variable_list ���o��̔z��I�t�Z�b�g���X�g
@param function_expr_slicing_list �֐��Ăяo���ɑ΂���v���O�����X���C�V���O���X�g
@param global_variable_list �O���[�o���ϐ��ꗗ�������z��I�t�Z�b�g���X�g

@return �Ȃ�
 */
void getFunctionGrobalVariable(ARRAY_OFFSET_LIST *output_global_variable_list, EXPR_SLICING_LIST *function_expr_slicing_list,
	ARRAY_OFFSET_LIST *global_variable_list){

	ARRAY_OFFSET_LIST *tmp_global_variable_list;
	ARRAY_OFFSET_LIST *local_variable_list;

	EXPR_SLICING_LISTIterator e_i;
	ARRAY_OFFSET_LISTIterator a_i;

	//�����A�v���O�����X���C�V���O���X�g�̖��߂����݂���ꍇ
	if(EXPR_SLICING_LIST_size(function_expr_slicing_list) != 0){
		//�֐����̃O���[�o���ϐ����R�s�[����
		tmp_global_variable_list = ARRAY_OFFSET_LIST_new();
		copyArrayOffsetList(global_variable_list, tmp_global_variable_list, 0);

		//�Ώۖ��ߓ��̃v���O�����X���C�V���O���X�g���烍�[�J���ϐ����𒊏o����
		local_variable_list = ARRAY_OFFSET_LIST_new();
		getVariableDeclarationFromEXPR_SLICING_LIST(local_variable_list, function_expr_slicing_list);

		//���[�J���ϐ��Əd������悤�ȕϐ����폜����
		minusArrayOffsetList(tmp_global_variable_list, local_variable_list);

		//���[�J���ϐ����������A�O���[�o���ϐ��̏�񂪑��݂���΁A�X���C�V���O���X�g���̖��߂�T������
		if(ARRAY_OFFSET_LIST_size(tmp_global_variable_list) > 0){
			for(e_i = EXPR_SLICING_LIST_begin(function_expr_slicing_list);
				e_i != EXPR_SLICING_LIST_end(function_expr_slicing_list);
				e_i = EXPR_SLICING_LIST_next(e_i)){

				//�Ώۂ̕ϐ�����O���[�o���ϐ����܂܂�Ă��邩�ǂ����T������
				for(a_i = ARRAY_OFFSET_LIST_begin(EXPR_SLICING_LIST_data(e_i)->target_variable);
						a_i != ARRAY_OFFSET_LIST_end(EXPR_SLICING_LIST_data(e_i)->target_variable);
						a_i = ARRAY_OFFSET_LIST_next(a_i)){
					//�Ώۂ̕ϐ�����O���[�o���ϐ���������ꂽ�ꍇ
					if(searchARRAY_OFFSET_LIST(tmp_global_variable_list, ARRAY_OFFSET_LIST_data(a_i)->variable_name)){
						//�d�����Ȃ��悤��out_global_variable_list�ɒǉ�����
						ARRAY_OFFSET_LIST_push_back_ref_not_dup(output_global_variable_list, ARRAY_OFFSET_LIST_data(a_i));
					}
				}

				//�X���C�V���O���̎q�m�[�h���T������
				getFunctionGrobalVariable(output_global_variable_list, EXPR_SLICING_LIST_data(e_i)->children1,
						tmp_global_variable_list);
				getFunctionGrobalVariable(output_global_variable_list, EXPR_SLICING_LIST_data(e_i)->children2,
						tmp_global_variable_list);

			}
		}

		ARRAY_OFFSET_LIST_clear(tmp_global_variable_list);
		ARRAY_OFFSET_LIST_delete(tmp_global_variable_list);
		ARRAY_OFFSET_LIST_clear(local_variable_list);
		ARRAY_OFFSET_LIST_delete(local_variable_list);
	}


}

/**
�Ώۂ̃v���O�����X���C�V���O���X�g����A�ϐ��錾�����𒊏o���A�z��I�t�Z�b�g���Ƃ��Ē��o����B

@param global_variable_list �O���[�o���ϐ��ꗗ�������z��I�t�Z�b�g���X�g
@param program_expr_slicing_list �v���O�����S�̂̃v���O�����X���C�V���O���X�g

@return �Ȃ�
 */
void getVariableDeclarationFromEXPR_SLICING_LIST(ARRAY_OFFSET_LIST *global_variable_list, EXPR_SLICING_LIST *program_expr_slicing_list){
	EXPR_SLICING_LISTIterator e_i;

	//�S�̂�T������
	for(e_i = EXPR_SLICING_LIST_begin(program_expr_slicing_list);
		e_i != EXPR_SLICING_LIST_end(program_expr_slicing_list);
		e_i = EXPR_SLICING_LIST_next(e_i)){

		//�����Adecralation_with_init�Ƃ����ϐ��錾���������ꍇ�A���̑Ώۂ̕ϐ������ƂɁA�z��I�t�Z�b�g���ɃR�s�[����
		if(CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "declaration_with_init") == 0 ||
				CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "declarator") == 0){
			copyArrayOffsetList(EXPR_SLICING_LIST_data(e_i)->target_variable, global_variable_list, 0);
		}
	}
}

/**
setGrobalVariable�̓��������B�֐����̃O���[�o���ϐ��𒊏o���A�Ώۂ̕ϐ��ɒǉ�������B

@param expr_slicing_list �ǉ��Ώۂ̃v���O�����X���C�V���O���X�g
@param program_expr_slicing_list �v���O�����S�̂̃v���O�����X���C�V���O���X�g
@param global_variable_list �O���[�o���ϐ����X�g

@return �Ȃ�
 */
void setGrobalVariable_Internal(EXPR_SLICING_LIST *expr_slicing_list, EXPR_SLICING_LIST *program_expr_slicing_list,
	ARRAY_OFFSET_LIST *global_variable_list){

	EXPR_SLICING_LISTIterator e_i;

	ARRAY_OFFSET_LISTIterator a_i;

	EXPR_SLICING *search_expr_slicing;

	CSTLString *function_name = CSTLString_new();

	//�v���O�����X���C�V���O�𒲂ׂĂ���
	for(e_i = EXPR_SLICING_LIST_begin(expr_slicing_list);
		e_i != EXPR_SLICING_LIST_end(expr_slicing_list);
		e_i = EXPR_SLICING_LIST_next(e_i)){

		//�Ώۂ̕ϐ��𒲂ׂĂ���
		for(a_i = ARRAY_OFFSET_LIST_begin(EXPR_SLICING_LIST_data(e_i)->target_variable);
				a_i != ARRAY_OFFSET_LIST_end(EXPR_SLICING_LIST_data(e_i)->target_variable);
				a_i = ARRAY_OFFSET_LIST_next(a_i)){

			//�֐��Ăяo���֌W�̖��߂��������ꍇ
			if(CSTLString_compare_with_char(ARRAY_OFFSET_LIST_data(a_i)->target_statement->name, "call_function") == 0){
				//�֐��������o��
				getStringFromAST(function_name, ASTLIST_ITERATOR_1(ARRAY_OFFSET_LIST_data(a_i)->target_statement));

				//expr_slicing_list����A�֐��Ăяo���ɑΉ�����֐��ւ̃v���O�����X���C�V���O�������o��
				search_expr_slicing = searchFunctionPSI(function_name, program_expr_slicing_list);

				//�����A������Ί֐���`���ň����O���[�o���ϐ��𒊏o���A�Ώۂ̕ϐ��ɒǉ�������
				if(search_expr_slicing != NULL){
					getFunctionGrobalVariable(EXPR_SLICING_LIST_data(e_i)->target_variable, search_expr_slicing->children1, global_variable_list);
				}
			}
		}

		//�ˑ��֌W�̕ϐ��𒲂ׂĂ���
		for(a_i = ARRAY_OFFSET_LIST_begin(EXPR_SLICING_LIST_data(e_i)->dependences);
				a_i != ARRAY_OFFSET_LIST_end(EXPR_SLICING_LIST_data(e_i)->dependences);
				a_i = ARRAY_OFFSET_LIST_next(a_i)){

			//�֐��Ăяo���֌W�̖��߂��������ꍇ
			if(CSTLString_compare_with_char(ARRAY_OFFSET_LIST_data(a_i)->target_statement->name, "call_function") == 0){
				//�֐��������o��
				getStringFromAST(function_name, ASTLIST_ITERATOR_1(ARRAY_OFFSET_LIST_data(a_i)->target_statement));

				//expr_slicing_list����A�֐��Ăяo���ɑΉ�����֐��ւ̃v���O�����X���C�V���O�������o��
				search_expr_slicing = searchFunctionPSI(function_name, program_expr_slicing_list);

				//�����A������Ί֐���`���ň����O���[�o���ϐ��𒊏o���A�Ώۂ̕ϐ��ɒǉ�������
				if(search_expr_slicing != NULL){
					getFunctionGrobalVariable(EXPR_SLICING_LIST_data(e_i)->target_variable, search_expr_slicing->children1, global_variable_list);
				}
			}
		}

		//�q�m�[�h���T������
		setGrobalVariable_Internal(EXPR_SLICING_LIST_data(e_i)->children1, program_expr_slicing_list, global_variable_list);
		setGrobalVariable_Internal(EXPR_SLICING_LIST_data(e_i)->children2, program_expr_slicing_list, global_variable_list);
	}

	CSTLString_delete(function_name);
}

/**
�֐��Ăяo������A��舵���O���[�o���ϐ��𒊏o���A�Ώۂ̕ϐ��ꗗ�ɒǉ����Ă����B
@param expr_slicing_list �ǉ��Ώۂ̃v���O�����X���C�V���O���X�g
@param program_expr_slicing_list �v���O�����S�̂̃v���O�����X���C�V���O���X�g

@return �Ȃ�
 */
void setGlobalVariable(EXPR_SLICING_LIST *expr_slicing_list, EXPR_SLICING_LIST *program_expr_slicing_list){
	ARRAY_OFFSET_LIST *global_variable_list = ARRAY_OFFSET_LIST_new();

	//�O���[�o���ϐ����X�g�𒊏o������
	getVariableDeclarationFromEXPR_SLICING_LIST(global_variable_list, program_expr_slicing_list);

	//�֐��Ăяo������A��舵���O���[�o���ϐ��𒊏o���A�Ώۂ̕ϐ��ɒǉ����Ă���
	setGrobalVariable_Internal(expr_slicing_list, program_expr_slicing_list, global_variable_list);

	ARRAY_OFFSET_LIST_delete(global_variable_list);
}

/**
�X���C�V���O�Ɋւ����񃊃X�gexpr_slicing_list���o�͂�����B

@param expr_slicing_list �X���C�V���O�Ɋւ����񃊃X�g

@return �Ȃ�
 */
void print_EXPR_SLICING_LIST(EXPR_SLICING_LIST *expr_slicing_list){

	EXPR_SLICING_LISTIterator el_i;
	DD_INFORMATION_LISTIterator dd_el_i;
	ARRAY_OFFSET_LISTIterator aoff_i;
	//�X���C�V���O���X�g���P�P�T������
	for(el_i = EXPR_SLICING_LIST_begin(expr_slicing_list);
		el_i != EXPR_SLICING_LIST_end(expr_slicing_list);
		el_i = EXPR_SLICING_LIST_next(el_i)){

		//�X���C�V���O�̃^�C�v�E�ʒu�i�s���j�E�Ώۂ̕ϐ��E�ˑ��֌W�̕ϐ����o�͂�����
		printf("--------------------------------------------\n");

		printf("SLICING_TYPE = %s\n",CSTLString_c_str(EXPR_SLICING_LIST_data(el_i)->expression->name));
		printf("LOCATION = %d\n", EXPR_SLICING_LIST_data(el_i)->expression->line);

		//�Ώۂ̕ϐ����uTARGET_VARIABLE = �ϐ�1, �ϐ�2, ...�v�Əo�͂�����
		printf("TARGET_VARIABLE = ");
		for(aoff_i = ARRAY_OFFSET_LIST_begin(EXPR_SLICING_LIST_data(el_i)->target_variable);
			aoff_i != ARRAY_OFFSET_LIST_end(EXPR_SLICING_LIST_data(el_i)->target_variable);
			aoff_i = ARRAY_OFFSET_LIST_next(aoff_i)){

				printf("%s", CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_i)->variable_name));
				if(ARRAY_OFFSET_LIST_next(aoff_i) != ARRAY_OFFSET_LIST_end(EXPR_SLICING_LIST_data(el_i)->target_variable)){
					printf(", ");
				}
			}
		printf("\n");

		//�Ώۂ̕ϐ����uDEPENDENCES = �ϐ�1, �ϐ�2, ...�v�Əo�͂�����
		printf("DEPENDENCES = ");
		for(aoff_i = ARRAY_OFFSET_LIST_begin(EXPR_SLICING_LIST_data(el_i)->dependences);
			aoff_i != ARRAY_OFFSET_LIST_end(EXPR_SLICING_LIST_data(el_i)->dependences);
			aoff_i = ARRAY_OFFSET_LIST_next(aoff_i)){

				printf("%s", CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_i)->variable_name));
				if(ARRAY_OFFSET_LIST_next(aoff_i) != ARRAY_OFFSET_LIST_end(EXPR_SLICING_LIST_data(el_i)->dependences)){
					printf(", ");
				}
			}
		printf("\n");

		//�f�[�^�ˑ��֌W���o�͂�����
		for(dd_el_i = DD_INFORMATION_LIST_rbegin(EXPR_SLICING_LIST_data(el_i)->dd_list);
				dd_el_i != DD_INFORMATION_LIST_rend(EXPR_SLICING_LIST_data(el_i)->dd_list);
				dd_el_i = DD_INFORMATION_LIST_prev(dd_el_i)){
			printf("j�E%s %s line = %d\t",CSTLString_c_str(DD_INFORMATION_LIST_data(dd_el_i)->dd_variable_name),CSTLString_c_str(DD_INFORMATION_LIST_data(dd_el_i)->dd_target->expression->name), DD_INFORMATION_LIST_data(dd_el_i)->dd_target->expression->line);
			//�Ώۂ̕ϐ����u�ϐ�1, �ϐ�2, ...�v�Əo�͂�����
			if(ARRAY_OFFSET_LIST_size(DD_INFORMATION_LIST_data(dd_el_i)->dd_target->target_variable) > 0){
				for(aoff_i = ARRAY_OFFSET_LIST_begin(DD_INFORMATION_LIST_data(dd_el_i)->dd_target->target_variable);
					aoff_i != ARRAY_OFFSET_LIST_end(DD_INFORMATION_LIST_data(dd_el_i)->dd_target->target_variable);
					aoff_i = ARRAY_OFFSET_LIST_next(aoff_i)){

						printf("%s", CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_i)->variable_name));
						if(ARRAY_OFFSET_LIST_next(aoff_i) != ARRAY_OFFSET_LIST_end(DD_INFORMATION_LIST_data(dd_el_i)->dd_target->target_variable)){
							printf(", ");
						}
				}
			}else{
				printf("NOTHING");
			}
			//�ˑ��֌W�̕ϐ����u�ϐ�1, �ϐ�2, ...�v�Əo�͂�����
			printf("\t");
			if(ARRAY_OFFSET_LIST_size(DD_INFORMATION_LIST_data(dd_el_i)->dd_target->dependences) > 0){
				for(aoff_i = ARRAY_OFFSET_LIST_begin(DD_INFORMATION_LIST_data(dd_el_i)->dd_target->dependences);
					aoff_i != ARRAY_OFFSET_LIST_end(DD_INFORMATION_LIST_data(dd_el_i)->dd_target->dependences);
					aoff_i = ARRAY_OFFSET_LIST_next(aoff_i)){

						printf("%s", CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_i)->variable_name));
						if(ARRAY_OFFSET_LIST_next(aoff_i) != ARRAY_OFFSET_LIST_end(DD_INFORMATION_LIST_data(dd_el_i)->dd_target->dependences)){
							printf(", ");
						}
				}
			}else{
				printf("NOTHING");
			}
			printf("\n");
		}
		printf("--------------------------------------------\n\n");

		//�q�m�[�h���T��������
		print_EXPR_SLICING_LIST(EXPR_SLICING_LIST_data(el_i)->children1);
		print_EXPR_SLICING_LIST(EXPR_SLICING_LIST_data(el_i)->children2);
	}

}
/**
print_tree_EXPR_SLICING_LIST�̓��������ł���B

@param expr_slicing_list �X���C�V���O�Ɋւ����񃊃X�g
@param tree_level �c���[�̃��x��
@param program_slicing_mode �v���O�����X���C�V���O��̃��[�h�ɂ��邩�ǂ����̃t���O�@�P�F�L���@�O�F����

@return �Ȃ�
 */
void print_tree_EXPR_SLICING_LIST_internal(EXPR_SLICING_LIST *expr_slicing_list,int tree_level, int program_slicing_mode){
	EXPR_SLICING_LISTIterator el_i;
	ARRAY_OFFSET_LISTIterator aoff_i;

	//�X���C�V���O���X�g���P�P�T������

	for(el_i = EXPR_SLICING_LIST_begin(expr_slicing_list);
		el_i != EXPR_SLICING_LIST_end(expr_slicing_list);
		el_i = EXPR_SLICING_LIST_next(el_i)){

		//�v���O�����X���C�V���O��̃��[�h�ɂȂ��Ă���Ƃ��́A�X���C�V���O��̃f�[�^�Ƃ��Ďg�p������̈ȊO��
		//�X���C�V���O�̃^�C�v�E�ʒu�i�s���j�E�Ώۂ̕ϐ��E�ˑ��֌W�̕ϐ����o�͂����Ȃ�
		if(program_slicing_mode == 0 || EXPR_SLICING_LIST_data(el_i)->flag == 1){
			int i;
			for(i = 0; i < tree_level; i++){
				printf("�@");
			}
			printf("�E%p %d %s line = %d\t", EXPR_SLICING_LIST_data(el_i), EXPR_SLICING_LIST_data(el_i)->expr_slicing_number,
					CSTLString_c_str(EXPR_SLICING_LIST_data(el_i)->expression->name),
					EXPR_SLICING_LIST_data(el_i)->expression->line);
			//�Ώۂ̕ϐ����u�ϐ�1, �ϐ�2, ...�v�Əo�͂�����
			if(ARRAY_OFFSET_LIST_size(EXPR_SLICING_LIST_data(el_i)->target_variable) > 0){
				for(aoff_i = ARRAY_OFFSET_LIST_begin(EXPR_SLICING_LIST_data(el_i)->target_variable);
					aoff_i != ARRAY_OFFSET_LIST_end(EXPR_SLICING_LIST_data(el_i)->target_variable);
					aoff_i = ARRAY_OFFSET_LIST_next(aoff_i)){

						printf("%s", CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_i)->variable_name));
						if(ARRAY_OFFSET_LIST_next(aoff_i) != ARRAY_OFFSET_LIST_end(EXPR_SLICING_LIST_data(el_i)->target_variable)){
							printf(", ");
						}
				}
			}else{
				printf("NOTHING");
			}
			//�ˑ��֌W�̕ϐ����u�ϐ�1, �ϐ�2, ...�v�Əo�͂�����
			printf("\t");
			if(ARRAY_OFFSET_LIST_size(EXPR_SLICING_LIST_data(el_i)->dependences) > 0){
				for(aoff_i = ARRAY_OFFSET_LIST_begin(EXPR_SLICING_LIST_data(el_i)->dependences);
					aoff_i != ARRAY_OFFSET_LIST_end(EXPR_SLICING_LIST_data(el_i)->dependences);
					aoff_i = ARRAY_OFFSET_LIST_next(aoff_i)){

						printf("%s", CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_i)->variable_name));
						if(ARRAY_OFFSET_LIST_next(aoff_i) != ARRAY_OFFSET_LIST_end(EXPR_SLICING_LIST_data(el_i)->dependences)){
							printf(", ");
						}
				}
			}else{
				printf("NOTHING");
			}
			//�f�[�^�ˑ��֌W�̐����o�͂�����
			printf("\tDD_LIST = %d", DD_INFORMATION_LIST_size(EXPR_SLICING_LIST_data(el_i)->dd_list));
			printf("\n");

			//�q�m�[�h���T��������
			print_tree_EXPR_SLICING_LIST_internal(EXPR_SLICING_LIST_data(el_i)->children1, tree_level + 1, program_slicing_mode);
			print_tree_EXPR_SLICING_LIST_internal(EXPR_SLICING_LIST_data(el_i)->children2, tree_level + 1, program_slicing_mode);
		}


	}

}

/**
�X���C�V���O�Ɋւ����񃊃X�gexpr_slicing_list���c���[�`���ŏo�͂�����B

@param expr_slicing_list �X���C�V���O�Ɋւ����񃊃X�g
@param program_slicing_mode �v���O�����X���C�V���O��̃��[�h�ɂ��邩�ǂ����̃t���O�@�P�F�L���@�O�F����
@return �Ȃ�
 */
void print_tree_EXPR_SLICING_LIST(EXPR_SLICING_LIST *expr_slicing_list, int program_slicing_mode){

	int tree_level = 1;
	printf("�EPROGRAM_START\n");
	print_tree_EXPR_SLICING_LIST_internal(expr_slicing_list, tree_level, program_slicing_mode);

}

/**
dependences�ŃC���N�������g��f�N�������g�̃t���O�������Ă���ϐ�����������A�����target_variable�ɓo�^����B

@param dependences �C���N�������g��f�N�������g��T���Ώۂ̈ˑ��ϐ�
@param target_variable �o�^��̒�`�Ώەϐ�

@return �Ȃ�
 */
void registerIncDecVariable(ARRAY_OFFSET_LIST *dependences, ARRAY_OFFSET_LIST *target_variable){
	ARRAY_OFFSET_LISTIterator a_i;

	//�ˑ��ϐ��̃��X�g����A�C���N�������g��f�N�������g�̃t���O�������Ă���ϐ���T��
	for(a_i = ARRAY_OFFSET_LIST_begin(dependences);
		a_i != ARRAY_OFFSET_LIST_end(dependences);
		a_i = ARRAY_OFFSET_LIST_next(a_i)){
		//�C���N�������g��f�N�������g�̃t���O�������Ă���ϐ�����������A�����target_variable�ɓo�^����B
		if(ARRAY_OFFSET_LIST_data(a_i)->inc_dec_flag != 0){
			ARRAY_OFFSET_LIST_push_back(target_variable, *ARRAY_OFFSET_LIST_data(a_i));
		}
	}
}
