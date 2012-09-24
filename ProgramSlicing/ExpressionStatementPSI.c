#include"ExpressionStatementPSI.h"
#include"../ANSICInformation/SubEffectCheck.h"
#include"../ANSICInformation/ANSIC_CODE.h"

#include<stdio.h>
#include<stdlib.h>

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

#define STRLEN 100

/**
���S�ʂ�AST�m�[�hexpression_statement����A�֐��ɑ΂���v���O�����X���C�V���O�𒊏o���A
�v���O�����X���C�V���O���X�gexpr_slicing_list�ɒǉ�����B

@param expr_slicing_list �ǉ���̃v���O�����X���C�V���O���X�gexpr_slicing_list
@param expression_statement ���S�ʂɊւ���AST�m�[�h
@param parent �m�[�h��ǉ�����Ƃ��̐e�m�[�h
@param vtlist �ϐ��e�[�u�����X�g
@param function_information_list �֐��Ɋւ����񃊃X�g
@param ignore_ast_list �d���h�~�̂��߂ɖ�������m�[�h���X�g
@param target_statement expression_statement���w�������m�[�h

@return �Ȃ�
 */
void getExpressionStatementPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *expression_statement, EXPR_SLICING *parent,
		VARIABLE_TABLE_LIST *vtlist, FUNCTION_INFORMATION_LIST *function_information_list, ASTPOINTER_LIST *ignore_ast_list,
		AST *target_statement){

	//children1,children2�̏����^
	EXPR_SLICING_LIST *children1 = EXPR_SLICING_LIST_new();
	EXPR_SLICING_LIST *children2 = EXPR_SLICING_LIST_new();
	//���Ӓl�ɂ�����e�����̃|�C���^��z��̃I�t�Z�b�g�Ɋւ�����̃��X�g
	ARRAY_OFFSET_LIST * target_variable = ARRAY_OFFSET_LIST_new();

	//�E�ӎ��ɂ�����e�����̃|�C���^��z��̃I�t�Z�b�g�Ɋւ�����̃��X�g
	ARRAY_OFFSET_LIST * dependences = ARRAY_OFFSET_LIST_new();

	//���������z��I�t�Z�b�g���X�g�̓o�^���s��
	getASI_ARRAY_OFFSET_LIST(expression_statement, target_variable, dependences, function_information_list, vtlist, ignore_ast_list, target_statement, 1);

	//�C���N�������g��f�N�������g�̎���dependence�Ō���������Atarget_variable�ɃR�s�[����B
	registerIncDecVariable(dependences, target_variable);

	//�V�����v���O�����X���C�V���O�f�[�^
	EXPR_SLICING *new_expr_slicing = new_EXPR_SLICING(EXPR_SLICING_LIST_size(expr_slicing_list) + 1, target_statement,target_variable,dependences, children1, children2, parent);
	EXPR_SLICING_LIST_push_back_ref(expr_slicing_list,new_expr_slicing);
}

/**
getASI_ARRAY_OFFSET_LIST�̓��������ł���

@param root �I�t�Z�b�g���X�g�ɊY������AST�m�[�h
@param target_variable ���ӎ��̃|�C���^����єz��̃I�t�Z�b�g���̃��X�g
@param dependences �E�ӎ��̃|�C���^����єz��̃I�t�Z�b�g���̃��X�g
@param function_information_list �֐��Ɋւ����񃊃X�g
@param vtlist ���ؑΏۂ̎����}�[�N���邽�߂̕ϐ����X�g
@param ignore_ast_list �z��I�t�Z�b�g���X�g�̏d���o�^��h�~���邽�߂́AIDENTIFIER�𖳎����邽�߂�AST�̃A�h���X���X�g
@param target_statement ���؎��̑ΏۂƂȂ�X�e�[�g�����g
@return �Ȃ�
*/
void getASI_ARRAY_OFFSET_LIST_Internal(AST *root, ARRAY_OFFSET_LIST *target_variable, ARRAY_OFFSET_LIST *dependences, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
		ASTPOINTER_LIST *ignore_ast_list, AST *target_statement){

	ASTListIterator ast_i;
	//assignment_expression���������ꍇ
	if(CSTLString_compare_with_char(root->name, "assignment_expression") == 0){
		//���ӂ���щE�ӂ̑Ώۂ̕ϐ�����шˑ��֌W�̕ϐ������߂�
		getARRAY_OFFSET_LIST(ASTLIST_ITERATOR_1(root), target_variable, function_information_list, vtlist, ignore_ast_list, root);

		//�֐��ɂ��Ă̑Ώۂ̕ϐ�����шˑ��֌W�̕ϐ����擾����
		getInputFunctionPSI(ASTLIST_ITERATOR_3(root), target_variable, dependences, function_information_list, vtlist, ignore_ast_list, target_statement);
		getARRAY_OFFSET_LIST(ASTLIST_ITERATOR_3(root), dependences, function_information_list, vtlist, ignore_ast_list, root);
		//���ӎ���2�Ԗڈȍ~�̔z��I�t�Z�b�g�����E�ӎ��̃I�t�Z�b�g���X�g���擾����
		moveArrayOffsetList(target_variable, dependences, 1);
		//������̃^�C�v�����߂�
		int a_op_flag = getAssignment_TYPE(root);
		//a_op_flag��=�ȊO�̏ꍇ�́A�E�ӎ��̃I�t�Z�b�g���X�g�ɂ͗��ӂ̎��̃I�t�Z�b�g���X�g���擾����
		if(a_op_flag != EQUAL){
			//�E�ӂɗ��Ă��鍶�ӂ̃m�[�h���R�s�[����
			copyArrayOffsetList(target_variable, dependences, 0);
		}
	}else if(CSTLString_compare_with_char(root->name, "t_assignment_expression") == 0){
		//�֐��ɂ��Ă̑Ώۂ̕ϐ�����шˑ��֌W�̕ϐ����擾����
		getInputFunctionPSI(root, target_variable, dependences, function_information_list, vtlist, ignore_ast_list, target_statement);
		getARRAY_OFFSET_LIST(root, dependences, function_information_list, vtlist, ignore_ast_list, target_statement);
	}else{
		//�q�m�[�h���Q�Ƃ�����
		for(ast_i = ASTList_begin(root->children);
			ast_i != ASTList_end(root->children);
			ast_i = ASTList_next(ast_i)){

			getASI_ARRAY_OFFSET_LIST_Internal(ASTList_data(ast_i), target_variable, dependences,
					function_information_list, vtlist, ignore_ast_list, target_statement);
		}
	}
}

/**
call_function��AST�m�[�h������o�͊֌W�̊֐���T���o���A�����̈����̕ϐ������ׂāA�Ώەϐ��Ƃ��ēo�^����B
@param root �Ώۂ�AST�m�[�h
@param target_variable �Ώۂ̕ϐ��̔z��I�t�Z�b�g��񃊃X�g
@param dependences �ˑ��֌W�̔z��I�t�Z�b�g��񃊃X�g
@param function_information_list �֐��Ɋւ����񃊃X�g
@param vtlist ���؎��̎����}�[�N���邽�߂̕ϐ����X�g
@param ignore_ast_list �z��I�t�Z�b�g���X�g�̏d���o�^��h�~���邽�߂́AIDENTIFIER�𖳎����邽�߂�AST�̃A�h���X���X�g
@param target_statement ���؎��̑ΏۂƂȂ�X�e�[�g�����g

@return �Ȃ�
 */
void getInputFunctionPSI(AST *root, ARRAY_OFFSET_LIST *target_variable, ARRAY_OFFSET_LIST *dependences, FUNCTION_INFORMATION_LIST *function_information_list,
		VARIABLE_TABLE_LIST *vtlist, ASTPOINTER_LIST *ignore_ast_list, AST *target_statement){

	ASTListIterator ast_i;
	FUNCTION_INFORMATION *function_information;

	if(CSTLString_compare_with_char(root->name, "call_function") == 0){
		//�֐������擾����
		CSTLString *function_name = CSTLString_new();
		getStringFromAST(function_name, ASTLIST_ITERATOR_1(root));

		//�֐������ȉ��̖��O�ł��邩�ǂ������ׁA�����ł���΁A�����̊֐����̈��������ׂāA�Ώەϐ��Ƃ��Ď擾����B
		function_information = searchFUNCTION_INFORMATION(function_name, function_information_list);
		if(function_information != NULL){
			//�֐��Ăяo���̂`�r�s�m�[�h���炷�ׂĂ̈������Ăяo���A�֐����ɑΉ����Ă�����o�͌^�ɏ]���āA
			//�Ώۂ̕ϐ���ˑ��֌W�̕ϐ��ɒǉ�����
			int argument_counter = 1;
			AST *argument;
			ARRAY_OFFSET_LIST *tmp;
			PARAM_INFORMATION_LISTIterator p_info_i = PARAM_INFORMATION_LIST_begin(function_information->param_information_list);
			while(getArgumentAST(&argument, root, argument_counter) != 0){
				//�����ŁA������񂪔͈͊O�Q�Ƃ��N�������ꍇ�̓G���[���o�͂��A�����I��������B
				if(p_info_i == PARAM_INFORMATION_LIST_end(function_information->param_information_list)){
					fprintf(stderr, "#%s#:%d:Too argument in function %s!", getFileName(), root->line, CSTLString_c_str(function_name));
					exit(1);
				}else{
					switch(PARAM_INFORMATION_LIST_data(p_info_i)->in_out_flag){
					case PARAM_IN_TYPE:
						get_ARRAY_OFFSET_LISTIgnoreASTNAME(argument, dependences,
								function_information_list, vtlist, ignore_ast_list, root, root->name);
						//�������Ƃ��Ċ܂܂�Ă���z��I�t�Z�b�g���ɑ΂��āA�����ԍ���t��������
						setARGUMENT_NUMBER( dependences, argument_counter, root);
						break;
					case PARAM_OUT_TYPE:
						get_ARRAY_OFFSET_LISTIgnoreASTNAME(argument, target_variable,
								function_information_list, vtlist, ignore_ast_list, root, root->name);
						//�������Ƃ��Ċ܂܂�Ă���z��I�t�Z�b�g���ɑ΂��āA�����ԍ���t��������
						setARGUMENT_NUMBER( target_variable, argument_counter, root);
						break;
					case PARAM_INOUT_TYPE:
						//���̔z��I�t�Z�b�g���X�g�𐶐����A�����ɕϐ������擾����
						tmp = ARRAY_OFFSET_LIST_new();
						get_ARRAY_OFFSET_LISTIgnoreASTNAME(argument, tmp,
								function_information_list, vtlist, ignore_ast_list, root, root->name);

						//�擾�����z��I�t�Z�b�g�����A�Ώۂ̈�����񂨂�шˑ��֌W�̈����Ɉړ�������
						copyArrayOffsetList(tmp, target_variable, 0);
						moveArrayOffsetList(tmp, dependences, 0);

						//���̔z��I�t�Z�b�g���X�g���폜����
						ARRAY_OFFSET_LIST_clear(tmp);
						ARRAY_OFFSET_LIST_delete(tmp);

						//�������Ƃ��Ċ܂܂�Ă���z��I�t�Z�b�g���ɑ΂��āA�����ԍ���t��������
						setARGUMENT_NUMBER( target_variable, argument_counter, root);
						setARGUMENT_NUMBER( dependences, argument_counter, root);
						break;
					default:
						fprintf(stderr, "�s���Ȉ����^�C�v�ł��I\n");
						exit(1);
					}
				}


				//�ϒ��ϐ����������̂����Ȃ���΁A���̈��������Ăяo���B
				if(CSTLString_compare_with_char(PARAM_INFORMATION_LIST_data(p_info_i)->param_type, "valist") != 0 ||
						CSTLString_compare_with_char(PARAM_INFORMATION_LIST_data(p_info_i)->param_name, "...") != 0){
					p_info_i = PARAM_INFORMATION_LIST_next(p_info_i);
				}
				argument_counter++;
			}
		}
		CSTLString_delete(function_name);
	}

	//�q�m�[�h���Q�Ƃ�����
	for(ast_i = ASTList_begin(root->children);
		ast_i != ASTList_end(root->children);
		ast_i = ASTList_next(ast_i)){

		getInputFunctionPSI(ASTList_data(ast_i), target_variable, dependences,
				function_information_list, vtlist, ignore_ast_list, target_statement);
	}

}

/**
expression_statement����сAexpression�ɑ�������m�[�h����A�Ώۂ̕ϐ�����шˑ��֌W�̔z��I�t�Z�b�g���X�g���擾����B

@param root �I�t�Z�b�g���X�g�ɊY������AST�m�[�h
@param target_variable ���ӎ��̃|�C���^����єz��̃I�t�Z�b�g���̃��X�g
@param dependences �E�ӎ��̃|�C���^����єz��̃I�t�Z�b�g���̃��X�g
@param function_information_list �֐��Ɋւ����񃊃X�g
@param vtlist ���ؑΏۂ̎����}�[�N���邽�߂̕ϐ����X�g
@param ignore_ast_list �|�C���^�ł̈ʒu�����؍ς݂ł���AIDENTIFIER�𖳎����邽�߂�AST�̃A�h���X���X�g
@param target_statement ���؎��̑ΏۂƂȂ�X�e�[�g�����g
@param allow_side_effect ����p�����������ǂ����̃t���O�@�P�F���� �O�F�����Ȃ�
@return �Ȃ�
*/
void getASI_ARRAY_OFFSET_LIST(AST *root, ARRAY_OFFSET_LIST *target_variable, ARRAY_OFFSET_LIST *dependences, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
						  ASTPOINTER_LIST *ignore_ast_list, AST *target_statement, int allow_side_effect){
	//����p���������Ȃ���ԂŁA����p�����������ꍇ
	if(allow_side_effect == 0 && checkContainSubEffectStatement(root) != 0){
		fprintf(stderr,"#%s#:%d:NOT ALLOW SUB EFFECT EXPRESSION!!", getFileName(), root->line);
		exit(1);
	}
	//expression_statement����сAexpression�ɑ�������m�[�h����A�Ώۂ̕ϐ�����шˑ��֌W�̔z��I�t�Z�b�g���X�g���擾����
	getASI_ARRAY_OFFSET_LIST_Internal(root, target_variable, dependences,
		function_information_list, vtlist, ignore_ast_list, target_statement);
}

/**
�Q�Ɛ��AST�m�[�h���w�肵���֐��Ăяo��call_function�ł���z��I�t�Z�b�g���X�gargument_list�ɑ΂��āA
�w�肵�������̔ԍ�argument_number���ȉ��̌`�ŕt������B

���O�@���@���O#�����ԍ�

@param argument_list �t���Ώۂ̔z��I�t�Z�b�g���X�g
@param arg_num ����
@param call_function �֐��Ăяo���ɑ΂���AST�m�[�h

@return �Ȃ�
 */
void setARGUMENT_NUMBER( ARRAY_OFFSET_LIST *argument_list, int arg_num, AST *call_function){

	ARRAY_OFFSET_LISTIterator a_i;

	//�����Ƃ��đ���������
	char number[STRLEN];
	snprintf(number, STRLEN, "#%d", arg_num);

	//�z��I�t�Z�b�g���X�g�����ׂĒT������
	for(a_i = ARRAY_OFFSET_LIST_begin(argument_list);
		a_i != ARRAY_OFFSET_LIST_end(argument_list);
		a_i = ARRAY_OFFSET_LIST_next(a_i)){
		//�Q�Ɛ��AST�m�[�h���֐��Ăяo���ɑ΂���AST�m�[�h�Ɠ������ꍇ
		if(ARRAY_OFFSET_LIST_data(a_i)->target_statement == call_function){
			//#�̕������܂܂�Ă��Ȃ���΁A#�����ԍ���������
			if(CSTLString_find(ARRAY_OFFSET_LIST_data(a_i)->variable_name, "#", 0) == CSTL_NPOS){
				CSTLString_append(ARRAY_OFFSET_LIST_data(a_i)->variable_name, number);

			}
		}

	}
}

