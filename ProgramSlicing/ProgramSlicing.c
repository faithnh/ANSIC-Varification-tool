#include"ProgramSlicing.h"

#include"FunctionPSI.h"
#include"ExpressionStatementPSI.h"
#include"DeclarationPSI.h"
#include"IfStatementPSI.h"
#include"ForStatementPSI.h"
#include"WhileStatementPSI.h"
#include"JumpStatementPSI.h"
#include"SwitchStatementPSI.h"
#include"LabeledStatementPSI.h"
#include"ReturnStatementPSI.h"

#include"../ANSICInformation/ANSIC_CODE.h"

#include<stdlib.h>

//�f�[�^�ˑ��֌W�̐����ŁA���߂����������ǂ����𔻒肷�邽�߂̃t���O
#define NOT_FIND 0					//0:���߂������Ă��Ȃ�
#define FIND_EXPR 1					//1:���߂�������

//�f�[�^�ˑ��֌W�̕ϐ������������ǂ����̃t���O
#define NOT_FIND_DD 0
#define FIND_DD 1

//�^���U���̔���
#define TRUE 1
#define FALSE 0

/**
�w�肵���v���O�����`�r�s�m�[�h���玟�̂悤�ȃm�[�h���擾���A
��������X���C�V���O���s�����߂̍\���̃��X�gexpr_slicing_list�𐶐�����B
function_definition_type_a�Afunction_definition_type_b�A
expression_statement�Adeclaration_with_init�Aif_statement�Aifelse_statement�Aswitch_statement�Awhile_statement�A
dowhile_statement�Afor_statement_type_a�Afor_statement_type_b�Afor_statement_type_c�Afor_statement_type_d�A
goto_statement�Acontinue_statement�Abreak_statement�Areturn_statement�Areturn_expr_statement
goto_labeled_statement�Acase_labeled_statement�Adefault_labeled_statement

@param root �w�肵���v���O�����`�r�s�m�[�h
@param expr_slicing_list �X���C�V���O���s�����߂̍\����
@param parent �e�̃X���C�V���O�f�[�^
@param vtlist �ϐ��e�[�u�����X�g
@param function_information_list �֐��Ɋւ�����̃��X�g
@return �Ȃ�
*/
void *createStatementNodeList(AST *root, EXPR_SLICING_LIST *expr_slicing_list, EXPR_SLICING *parent,
		VARIABLE_TABLE_LIST *vtlist, FUNCTION_INFORMATION_LIST *function_information_list){
	ASTListIterator ast_p;
	EXPR_SLICING *new_expr_slicing;

	//function_definition_type_a�Afunction_definition_type_b���o�Ă����ꍇ
	if(CSTLString_compare_with_char(root->name,"function_definition_type_a") == 0 ||
		CSTLString_compare_with_char(root->name,"function_definition_type_b") == 0){
		//�֐��Ɋւ���v���O�����X���C�V���O�����擾����
		new_expr_slicing = getFunctionPSI(expr_slicing_list, root, parent);

		//�q�m�[�h�����ǂ�
		createStatementNodeList(ASTLIST_ITERATOR_3(root), new_expr_slicing->children1,
				new_expr_slicing,
				vtlist, function_information_list);


	}

	//expression_statement���o�Ă����ꍇ
	else if(CSTLString_compare_with_char(root->name,"expression_statement") == 0 ){
		//�d���h�~�̖�������AST���X�g��V�K�쐬����
		ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();
		//���S�ʂɊւ���v���O�����X���C�V���O�����擾����
		getExpressionStatementPSI(expr_slicing_list, root, parent, vtlist, function_information_list, ignore_ast_list, root);

		//�d���h�~�̖�������AST���X�g���폜����
		ASTPOINTER_LIST_clear(ignore_ast_list);
		ASTPOINTER_LIST_delete(ignore_ast_list);
	}

	//declaration_with_init���o�Ă����ꍇ
	else if(CSTLString_compare_with_char(root->name,"declaration_with_init") == 0 ){
		//�d���h�~�̖�������AST���X�g��V�K�쐬����
		ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();
		//�錾�S�ʂɊւ���v���O�����X���C�V���O�����擾����
		getDeclarationtPSI(expr_slicing_list, root, parent, vtlist, function_information_list, ignore_ast_list, root);


	}

	//if_statement���o�Ă����ꍇ
	else if(CSTLString_compare_with_char(root->name,"if_statement") == 0){
		//�d���h�~�̖�������AST���X�g��V�K�쐬����
		ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();

		//if���Ɋւ���v���O�����X���C�V���O�����擾����
		new_expr_slicing = getIfStatementPSI(expr_slicing_list, root, parent, vtlist, function_information_list, ignore_ast_list);

		//�d���h�~�̖�������AST���X�g���폜����
		ASTPOINTER_LIST_clear(ignore_ast_list);
		ASTPOINTER_LIST_delete(ignore_ast_list);

		//if�u���b�N���̎q�m�[�h�����ǂ�
		createStatementNodeList(ASTLIST_ITERATOR_5(root), new_expr_slicing->children1,
				new_expr_slicing,
				vtlist, function_information_list);
	}

	//ifelse_statement���o�Ă����ꍇ
	else if(CSTLString_compare_with_char(root->name,"ifelse_statement") == 0){
		//�d���h�~�̖�������AST���X�g��V�K�쐬����
		ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();

		//ifelse���Ɋւ���v���O�����X���C�V���O�����擾����
		new_expr_slicing = getIfStatementPSI(expr_slicing_list, root, parent, vtlist, function_information_list, ignore_ast_list);

		//�d���h�~�̖�������AST���X�g���폜����
		ASTPOINTER_LIST_clear(ignore_ast_list);
		ASTPOINTER_LIST_delete(ignore_ast_list);

		//if�u���b�N���̎q�m�[�h�����ǂ�
		createStatementNodeList(ASTLIST_ITERATOR_5(root), new_expr_slicing->children1,
				new_expr_slicing,
				vtlist, function_information_list);
		//else�u���b�N���̎q�m�[�h�����ǂ�
		createStatementNodeList(ASTLIST_ITERATOR_7(root), new_expr_slicing->children2,
				new_expr_slicing,
				vtlist, function_information_list);
	}

	//switch_statement���o�Ă����ꍇ
	else if(CSTLString_compare_with_char(root->name,"switch_statement") == 0 ){
		//�d���h�~�̖�������AST���X�g��V�K�쐬����
		ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();

		//switch���Ɋւ���v���O�����X���C�V���O�����擾����
		new_expr_slicing = getSwicthStatementPSI(expr_slicing_list, root, parent, vtlist, function_information_list, ignore_ast_list);

		//�d���h�~�̖�������AST���X�g���폜����
		ASTPOINTER_LIST_clear(ignore_ast_list);
		ASTPOINTER_LIST_delete(ignore_ast_list);

		//switch�u���b�N���̎q�m�[�h�����ǂ�
		createStatementNodeList(ASTLIST_ITERATOR_5(root), new_expr_slicing->children1,
				new_expr_slicing,
				vtlist, function_information_list);
	}

	//while_statement���o�Ă����ꍇ
	else if(CSTLString_compare_with_char(root->name,"while_statement") == 0 ){
		//�d���h�~�̖�������AST���X�g��V�K�쐬����
		ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();

		//while���Ɋւ���v���O�����X���C�V���O�����擾����
		new_expr_slicing = getWhileStatementPSI(expr_slicing_list, root, parent, vtlist, function_information_list, ignore_ast_list);

		//�d���h�~�̖�������AST���X�g���폜����
		ASTPOINTER_LIST_clear(ignore_ast_list);
		ASTPOINTER_LIST_delete(ignore_ast_list);

		//while�u���b�N���̎q�m�[�h�����ǂ�
		createStatementNodeList(ASTLIST_ITERATOR_5(root), new_expr_slicing->children1,
				new_expr_slicing,
				vtlist, function_information_list);
	}

	//dowhile_statement���o�Ă����ꍇ
	else if(CSTLString_compare_with_char(root->name,"dowhile_statement") == 0 ){
		//�d���h�~�̖�������AST���X�g��V�K�쐬����
		ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();

		//dowhile���Ɋւ���v���O�����X���C�V���O�����擾����
		new_expr_slicing = getWhileStatementPSI(expr_slicing_list, root, parent, vtlist, function_information_list, ignore_ast_list);

		//�d���h�~�̖�������AST���X�g���폜����
		ASTPOINTER_LIST_clear(ignore_ast_list);
		ASTPOINTER_LIST_delete(ignore_ast_list);

		//do�u���b�N���̎q�m�[�h�����ǂ�
		createStatementNodeList(ASTLIST_ITERATOR_2(root), new_expr_slicing->children1,
				new_expr_slicing,
				vtlist, function_information_list);
	}

	//for_statement_type_a�Afor_statement_type_b���o�Ă����ꍇ
	else if(CSTLString_compare_with_char(root->name,"for_statement_type_a") == 0 ){
		//�d���h�~�̖�������AST���X�g��V�K�쐬����
		ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();

		//for���Ɋւ���v���O�����X���C�V���O�����擾����
		new_expr_slicing = getForStatementPSI(expr_slicing_list, root, parent, vtlist, function_information_list, ignore_ast_list);

		//�d���h�~�̖�������AST���X�g���폜����
		ASTPOINTER_LIST_clear(ignore_ast_list);
		ASTPOINTER_LIST_delete(ignore_ast_list);

		//for�u���b�N���̎q�m�[�h�����ǂ�
		createStatementNodeList(ASTLIST_ITERATOR_6(root), new_expr_slicing->children1,
				new_expr_slicing,
				vtlist, function_information_list);

	}else if(CSTLString_compare_with_char(root->name,"for_statement_type_b") == 0 ){
		//�d���h�~�̖�������AST���X�g��V�K�쐬����
		ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();

		//for���Ɋւ���v���O�����X���C�V���O�����擾����
		new_expr_slicing = getForStatementPSI(expr_slicing_list, root, parent, vtlist, function_information_list, ignore_ast_list);

		//�d���h�~�̖�������AST���X�g���폜����
		ASTPOINTER_LIST_clear(ignore_ast_list);
		ASTPOINTER_LIST_delete(ignore_ast_list);

		//for�u���b�N���̎q�m�[�h�����ǂ�
		createStatementNodeList(ASTLIST_ITERATOR_7(root), new_expr_slicing->children1,
				new_expr_slicing,
				vtlist, function_information_list);
	}

	//for_statement_type_c�Afor_statement_type_d���o�Ă����ꍇ�A�]�܂����Ȃ������Ƃ��ăG���[���o�͂��A�����I��������
	else if(CSTLString_compare_with_char(root->name,"for_statement_type_c") == 0 ||
			CSTLString_compare_with_char(root->name,"for_statement_type_d") == 0 ){
		fprintf(stderr,"#%s#:%d:Don't Declaration In For Statement!!", getFileName(), ASTLIST_ITERATOR_1(root)->line);
		exit(1);
	}

	//goto_statement���o�Ă����ꍇ
	else if(CSTLString_compare_with_char(root->name,"goto_statement") == 0 ){
		//goto���Ɋւ���v���O�����X���C�V���O�����擾����
		getJumpStatementPSI(expr_slicing_list, root, parent);
	}

	//continue_statement���o�Ă����ꍇ
	else if(CSTLString_compare_with_char(root->name,"continue_statement") == 0 ){
		//continue���Ɋւ���v���O�����X���C�V���O�����擾����
		getJumpStatementPSI(expr_slicing_list, root, parent);
	}

	//break_statement���o�Ă����ꍇ
	else if(CSTLString_compare_with_char(root->name,"break_statement") == 0 ){
		//break���Ɋւ���v���O�����X���C�V���O�����擾����
		getJumpStatementPSI(expr_slicing_list, root, parent);
	}
	//return_statement�Areturn_expr_statement���o�Ă����ꍇ
	else if(CSTLString_compare_with_char(root->name,"return_statement") == 0 ||
		CSTLString_compare_with_char(root->name,"return_expr_statement") == 0){
		//�d���h�~�̖�������AST���X�g��V�K�쐬����
		ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();

		//return���Ɋւ���v���O�����X���C�V���O�����擾����
		getReturnStatementPSI(expr_slicing_list, root, parent, vtlist, function_information_list, ignore_ast_list);

		//�d���h�~�̖�������AST���X�g���폜����
		ASTPOINTER_LIST_clear(ignore_ast_list);
		ASTPOINTER_LIST_delete(ignore_ast_list);
	}
	//goto_labeled_statement�Adefault_labeled_statement���o�Ă����ꍇ
	else if(CSTLString_compare_with_char(root->name,"goto_labeled_statement") == 0 ||
			CSTLString_compare_with_char(root->name,"default_labeled_statement") == 0 ){
		//�d���h�~�̖�������AST���X�g��V�K�쐬����
		ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();

		//goto���x������default���x�����Ɋւ���v���O�����X���C�V���O�����擾����
		new_expr_slicing = getLabeledStatementPSI(expr_slicing_list, root, parent,
				vtlist, function_information_list, ignore_ast_list);

		//�d���h�~�̖�������AST���X�g���폜����
		ASTPOINTER_LIST_clear(ignore_ast_list);
		ASTPOINTER_LIST_delete(ignore_ast_list);

		//goto���x������default���x�������statement�̎q�m�[�h�����ǂ�
		createStatementNodeList(ASTLIST_ITERATOR_3(root), new_expr_slicing->children1,
				new_expr_slicing,
				vtlist, function_information_list);
	}
	//case_labeled_statement���o�Ă����ꍇ
	else if(CSTLString_compare_with_char(root->name,"case_labeled_statement") == 0 ){
		//�d���h�~�̖�������AST���X�g��V�K�쐬����
		ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();

		//case���x�����Ɋւ���v���O�����X���C�V���O�����擾����
		new_expr_slicing = getLabeledStatementPSI(expr_slicing_list, root, parent,
				vtlist, function_information_list, ignore_ast_list);

		//�d���h�~�̖�������AST���X�g���폜����
		ASTPOINTER_LIST_clear(ignore_ast_list);
		ASTPOINTER_LIST_delete(ignore_ast_list);

		//case���x�������statement�̎q�m�[�h�����ǂ�
		createStatementNodeList(ASTLIST_ITERATOR_4(root), new_expr_slicing->children1,
				new_expr_slicing,
				vtlist, function_information_list);
	}
	else{
		//�q�m�[�h�����ǂ�
		for(ast_p = ASTList_begin(root->children);
			ast_p != ASTList_end(root->children);
			ast_p = ASTList_next(ast_p)){
				createStatementNodeList(ASTList_data(ast_p), expr_slicing_list, parent, vtlist, function_information_list);
		}
	}
}

/**
createDD_list�̓��������ł���B�Ώۂ̖���parent_expr_slicing�͈̔͂ŁA
�ˑ��֌W�̕ϐ��Ɋ֌W���閽�߂���������A���̖��߂��f�[�^�ˑ��֌W���X�g�ɒǉ�����B

@param parent_expr_slicing �Ώۂ̖��ߔ͈�parent_expr_slicing
@param expr_slicing ���ׂ�Ώۂ̖���
@param exception_variable_list ���O����ϐ����X�g
@param invest_flag ���ׂ邩�ǂ����̃t���O�@�P:�L���@�O�F����

@return �Ȃ�
 */
void createDD_list_Internal(EXPR_SLICING *parent_expr_slicing, EXPR_SLICING *expr_slicing, ARRAY_OFFSET_LIST *exception_variable_list, int *find_expr_flag){
	EXPR_SLICING_LISTIterator e_i;
	ARRAY_OFFSET_LISTIterator a_i;
	int find_flag = NOT_FIND;
	//�f�[�^�ˑ��֌W�̖��߂̌��
	DD_INFORMATION *candidate_dd_info = NULL;
	DD_INFORMATION_LIST *candidate_dd_list = DD_INFORMATION_LIST_new();
	//�J��Ԃ��n���߂̏ꍇ�͈ȉ��̏������s��
	if(CSTLString_compare_with_char(parent_expr_slicing->expression->name, "for_statement_type_a") == 0 ||
		CSTLString_compare_with_char(parent_expr_slicing->expression->name, "for_statement_type_b") == 0 ||
		CSTLString_compare_with_char(parent_expr_slicing->expression->name, "while_statement") == 0 ||
		CSTLString_compare_with_char(parent_expr_slicing->expression->name, "dowhile_statement") == 0 )
	{
		int find_expr_in_iteration_flag = FALSE;
		//children1��T�����A�Y���̖��߂������邩�ǂ����𒲂ׂ�
		for(e_i = EXPR_SLICING_LIST_rbegin(parent_expr_slicing->children1);
			e_i != EXPR_SLICING_LIST_rend(parent_expr_slicing->children1);
			e_i = EXPR_SLICING_LIST_prev(e_i)){

			if(EXPR_SLICING_LIST_data(e_i) == expr_slicing){
				find_expr_in_iteration_flag = TRUE;

				break;
			}

		}
		//�����Afor�����ŊY���̖��߂����������ꍇ
		if(find_expr_in_iteration_flag){

			*find_expr_flag = FIND_EXPR;

			//children1���t���ɒT������
			for(;
				e_i != EXPR_SLICING_LIST_rend(parent_expr_slicing->children1);
				e_i = EXPR_SLICING_LIST_prev(e_i)){

				createDD_list_Internal(EXPR_SLICING_LIST_data(e_i), expr_slicing, exception_variable_list, find_expr_flag);

				find_flag = NOT_FIND_DD;
				if(EXPR_SLICING_LIST_data(e_i) != expr_slicing){
					for(a_i = ARRAY_OFFSET_LIST_begin(expr_slicing->dependences);
						a_i != ARRAY_OFFSET_LIST_end(expr_slicing->dependences);
						a_i = ARRAY_OFFSET_LIST_next(a_i)){

						if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable,
								ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL &&
								searchARRAY_OFFSET_LIST(exception_variable_list,
								ARRAY_OFFSET_LIST_data(a_i)->variable_name) == NULL){
							find_flag = FIND_DD;
							break;
						}
					}

					if(find_flag == FIND_DD){
						//�����A�f�[�^�ˑ��֌W�Ɋ֌W����ϐ��Ƃ��Ԃ��Ă�����̂�������Ȃ���΁A�ǉ�����
						if(searchDD(ARRAY_OFFSET_LIST_data(a_i)->variable_name, candidate_dd_list, &candidate_dd_info) == 0){
							DD_INFORMATION_LIST_push_back_ref(candidate_dd_list, new_DD_INFORMATION(ARRAY_OFFSET_LIST_data(a_i)->variable_name,EXPR_SLICING_LIST_data(e_i)));
						}
					}
				}

			}
			//children1���t���ɒT������
			for(e_i = EXPR_SLICING_LIST_rbegin(parent_expr_slicing->children1);
				EXPR_SLICING_LIST_data(e_i) != expr_slicing;
				e_i = EXPR_SLICING_LIST_prev(e_i)){

				createDD_list_Internal(EXPR_SLICING_LIST_data(e_i), expr_slicing, exception_variable_list, find_expr_flag);

				find_flag = NOT_FIND_DD;
				if(EXPR_SLICING_LIST_data(e_i) != expr_slicing){
					for(a_i = ARRAY_OFFSET_LIST_begin(expr_slicing->dependences);
						a_i != ARRAY_OFFSET_LIST_end(expr_slicing->dependences);
						a_i = ARRAY_OFFSET_LIST_next(a_i)){

						if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable,
								ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL &&
								searchARRAY_OFFSET_LIST(exception_variable_list,
								ARRAY_OFFSET_LIST_data(a_i)->variable_name) == NULL){
							find_flag = FIND_DD;
							break;
						}
					}

					if(find_flag == FIND_DD){
						//�����A�f�[�^�ˑ��֌W�Ɋ֌W����ϐ��Ƃ��Ԃ��Ă�����̂�������Ȃ���΁A�ǉ�����
						if(searchDD(ARRAY_OFFSET_LIST_data(a_i)->variable_name, candidate_dd_list, &candidate_dd_info) == 0){
							DD_INFORMATION_LIST_push_back_ref(candidate_dd_list, new_DD_INFORMATION(ARRAY_OFFSET_LIST_data(a_i)->variable_name,EXPR_SLICING_LIST_data(e_i)));
						}
					}
				}

			}
			//�f�[�^�ˑ��֌W�̃��X�g��ǉ�����
			if(DD_INFORMATION_LIST_size(candidate_dd_list) != 0){
				DD_INFORMATION_LIST_splice(expr_slicing->dd_list, DD_INFORMATION_LIST_end(expr_slicing->dd_list),
						candidate_dd_list, DD_INFORMATION_LIST_begin(candidate_dd_list), DD_INFORMATION_LIST_end(candidate_dd_list));
			}


		}
		//�����łȂ��ꍇ�͕��ʂɋt���ɒT������
		else{
			for(e_i = EXPR_SLICING_LIST_rbegin(parent_expr_slicing->children1);
				e_i != EXPR_SLICING_LIST_rend(parent_expr_slicing->children1);
				e_i = EXPR_SLICING_LIST_prev(e_i)){

				createDD_list_Internal(EXPR_SLICING_LIST_data(e_i), expr_slicing, exception_variable_list, find_expr_flag);

				if(*find_expr_flag == NOT_FIND){
					if(EXPR_SLICING_LIST_data(e_i) == expr_slicing){
						*find_expr_flag = FIND_EXPR;
					}
				}
				//���ׂĂ��閽�߂��錾�������錾�ł���΁A
				//�Ώۂ̖��߂̈ˑ��֌W��Ώۂ̕ϐ��Ƀf�[�^�ˑ��֌W�����邩�ǂ������ׂ�
				else if((*find_expr_flag != NOT_FIND && CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "declaration_with_init") == 0) ||
						CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "declarator") == 0){
					for(a_i = ARRAY_OFFSET_LIST_begin(expr_slicing->target_variable);
						a_i != ARRAY_OFFSET_LIST_end(expr_slicing->target_variable);
						a_i = ARRAY_OFFSET_LIST_next(a_i)){

						if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable,
								ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL){
							DD_INFORMATION_LIST_push_back_ref(expr_slicing->dd_list, new_DD_INFORMATION(ARRAY_OFFSET_LIST_data(a_i)->variable_name, EXPR_SLICING_LIST_data(e_i)));
							find_flag = FIND_DD;

							break;
						}
					}
					for(a_i = ARRAY_OFFSET_LIST_begin(expr_slicing->dependences);
						a_i != ARRAY_OFFSET_LIST_end(expr_slicing->dependences);
						a_i = ARRAY_OFFSET_LIST_next(a_i)){

						if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable,
								ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL){
							DD_INFORMATION_LIST_push_back_ref(expr_slicing->dd_list, new_DD_INFORMATION(ARRAY_OFFSET_LIST_data(a_i)->variable_name, EXPR_SLICING_LIST_data(e_i)));
							find_flag = FIND_DD;

							break;
						}
					}
				}
				//�錾������錾�łȂ���΁A�Ώۂ̒��O�̖��߂P�ɑ΂��ăf�[�^�ˑ��֌W������
				else{
					for(a_i = ARRAY_OFFSET_LIST_begin(expr_slicing->dependences);
						a_i != ARRAY_OFFSET_LIST_end(expr_slicing->dependences);
						a_i = ARRAY_OFFSET_LIST_next(a_i)){
						//�ˑ��֌W�̕ϐ����A�Ώۂ̕ϐ��ɑ��݂��A���O���X�g�ɍڂ��Ă��Ȃ��ꍇ
						if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable,
								ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL &&
								searchARRAY_OFFSET_LIST(exception_variable_list,
								ARRAY_OFFSET_LIST_data(a_i)->variable_name) == NULL){

							//�_�u�肪���݂��Ȃ��ꍇ�͌��Ƃ��Ēǉ�����
							if(searchDD(ARRAY_OFFSET_LIST_data(a_i)->variable_name, candidate_dd_list, &candidate_dd_info) == 0){
								DD_INFORMATION_LIST_push_back_ref(candidate_dd_list, new_DD_INFORMATION(ARRAY_OFFSET_LIST_data(a_i)->variable_name, EXPR_SLICING_LIST_data(e_i)));
								find_flag = FIND_DD;
								break;
							}
						}
					}
				}

			}
			//�f�[�^�ˑ��֌W�̃��X�g��ǉ�����
			if(DD_INFORMATION_LIST_size(candidate_dd_list) != 0){
				DD_INFORMATION_LIST_splice(expr_slicing->dd_list, DD_INFORMATION_LIST_end(expr_slicing->dd_list),
						candidate_dd_list, DD_INFORMATION_LIST_begin(candidate_dd_list), DD_INFORMATION_LIST_end(candidate_dd_list));
			}
		}

	//�J��Ԃ����߂łȂ��ꍇ�́A�ȉ��̏��������s����
	}else{
		//children2����t���ɒT������
		for(e_i = EXPR_SLICING_LIST_rbegin(parent_expr_slicing->children2);
			e_i != EXPR_SLICING_LIST_rend(parent_expr_slicing->children2);
			e_i = EXPR_SLICING_LIST_prev(e_i)){

			createDD_list_Internal(EXPR_SLICING_LIST_data(e_i), expr_slicing, exception_variable_list, find_expr_flag);

			if(*find_expr_flag == NOT_FIND){
				if(EXPR_SLICING_LIST_data(e_i) == expr_slicing){
					*find_expr_flag = FIND_EXPR;
				}
			}
			//���ׂĂ��閽�߂��錾�������錾�ł���΁A
			//�Ώۂ̖��߂̈ˑ��֌W��Ώۂ̕ϐ��Ƀf�[�^�ˑ��֌W�����邩�ǂ������ׂ�
			else if((*find_expr_flag != NOT_FIND && CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "declaration_with_init") == 0) ||
					CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "declarator") == 0){
				for(a_i = ARRAY_OFFSET_LIST_begin(expr_slicing->target_variable);
					a_i != ARRAY_OFFSET_LIST_end(expr_slicing->target_variable);
					a_i = ARRAY_OFFSET_LIST_next(a_i)){

					if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable,
							ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL){
						DD_INFORMATION_LIST_push_back_ref(expr_slicing->dd_list, new_DD_INFORMATION(ARRAY_OFFSET_LIST_data(a_i)->variable_name, EXPR_SLICING_LIST_data(e_i)));
						find_flag = FIND_DD;
						break;
					}
				}
				for(a_i = ARRAY_OFFSET_LIST_begin(expr_slicing->dependences);
					a_i != ARRAY_OFFSET_LIST_end(expr_slicing->dependences);
					a_i = ARRAY_OFFSET_LIST_next(a_i)){

					if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable,
							ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL){
						DD_INFORMATION_LIST_push_back_ref(expr_slicing->dd_list, new_DD_INFORMATION(ARRAY_OFFSET_LIST_data(a_i)->variable_name, EXPR_SLICING_LIST_data(e_i)));
						find_flag = FIND_DD;
						break;
					}
				}
			}
			//�錾������錾�łȂ���΁A�Ώۂ̒��O�̖��߂P�ɑ΂��ăf�[�^�ˑ��֌W������
			/*else if(find_flag == NOT_FIND_DD){

				for(a_i = ARRAY_OFFSET_LIST_begin(expr_slicing->dependences);
					a_i != ARRAY_OFFSET_LIST_end(expr_slicing->dependences);
					a_i = ARRAY_OFFSET_LIST_next(a_i)){

					if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable,
							ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL &&
							searchARRAY_OFFSET_LIST(exception_variable_list,
							ARRAY_OFFSET_LIST_data(a_i)->variable_name) == NULL){
						DD_INFORMATION_LIST_push_back_ref(expr_slicing->dd_list, new_DD_INFORMATION(ARRAY_OFFSET_LIST_data(a_i)->variable_name, EXPR_SLICING_LIST_data(e_i)));
						find_flag = FIND_DD;
						break;
					}
				}
			}*/
			//�錾������錾�łȂ���΁A�Ώۂ̒��O�̖��߂P�ɑ΂��ăf�[�^�ˑ��֌W������
			else{
				for(a_i = ARRAY_OFFSET_LIST_begin(expr_slicing->dependences);
					a_i != ARRAY_OFFSET_LIST_end(expr_slicing->dependences);
					a_i = ARRAY_OFFSET_LIST_next(a_i)){
					//�ˑ��֌W�̕ϐ����A�Ώۂ̕ϐ��ɑ��݂��A���O���X�g�ɍڂ��Ă��Ȃ��ꍇ
					if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable,
							ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL &&
							searchARRAY_OFFSET_LIST(exception_variable_list,
							ARRAY_OFFSET_LIST_data(a_i)->variable_name) == NULL){

						//�_�u�肪���݂��Ȃ��ꍇ�͌��Ƃ��Ēǉ�����
						if(searchDD(ARRAY_OFFSET_LIST_data(a_i)->variable_name, candidate_dd_list, &candidate_dd_info) == 0){
							DD_INFORMATION_LIST_push_back_ref(candidate_dd_list, new_DD_INFORMATION(ARRAY_OFFSET_LIST_data(a_i)->variable_name, EXPR_SLICING_LIST_data(e_i)));
							find_flag = FIND_DD;
							break;
						}
					}
				}
			}

		}

		find_flag = NOT_FIND_DD;

		//����children1���t���ɒT������
		for(e_i = EXPR_SLICING_LIST_rbegin(parent_expr_slicing->children1);
			e_i != EXPR_SLICING_LIST_rend(parent_expr_slicing->children1);
			e_i = EXPR_SLICING_LIST_prev(e_i)){

			createDD_list_Internal(EXPR_SLICING_LIST_data(e_i), expr_slicing, exception_variable_list, find_expr_flag);
			//�����A�Ώۂ̖��߂��������Ă��Ȃ���Ԃ̏ꍇ�́A�Ώۂ̖��߂�������܂ŒT��
			if(*find_expr_flag == NOT_FIND){
				if(EXPR_SLICING_LIST_data(e_i) == expr_slicing){
					*find_expr_flag = FIND_EXPR;
				}
			}
			//���ׂĂ��閽�߂��錾�������錾�ł���΁A
			//�Ώۂ̖��߂̈ˑ��֌W��Ώۂ̕ϐ��Ƀf�[�^�ˑ��֌W�����邩�ǂ������ׂ�
			else if((*find_expr_flag != NOT_FIND && CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "declaration_with_init") == 0) ||
					CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "declarator") == 0){
				for(a_i = ARRAY_OFFSET_LIST_begin(expr_slicing->target_variable);
					a_i != ARRAY_OFFSET_LIST_end(expr_slicing->target_variable);
					a_i = ARRAY_OFFSET_LIST_next(a_i)){

					if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable,
							ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL){
						DD_INFORMATION_LIST_push_back_ref(expr_slicing->dd_list, new_DD_INFORMATION(ARRAY_OFFSET_LIST_data(a_i)->variable_name, EXPR_SLICING_LIST_data(e_i)));
						find_flag = FIND_DD;
						break;
					}
				}
				for(a_i = ARRAY_OFFSET_LIST_begin(expr_slicing->dependences);
					a_i != ARRAY_OFFSET_LIST_end(expr_slicing->dependences);
					a_i = ARRAY_OFFSET_LIST_next(a_i)){

					if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable,
							ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL){
						DD_INFORMATION_LIST_push_back_ref(expr_slicing->dd_list, new_DD_INFORMATION(ARRAY_OFFSET_LIST_data(a_i)->variable_name, EXPR_SLICING_LIST_data(e_i)));
						find_flag = FIND_DD;
						break;
					}
				}
			}
			//�錾������錾�łȂ���΁A�Ώۂ̒��O�̖��߂P�ɑ΂��ăf�[�^�ˑ��֌W������
			else{
				for(a_i = ARRAY_OFFSET_LIST_begin(expr_slicing->dependences);
					a_i != ARRAY_OFFSET_LIST_end(expr_slicing->dependences);
					a_i = ARRAY_OFFSET_LIST_next(a_i)){
					//�ˑ��֌W�̕ϐ����A�Ώۂ̕ϐ��ɑ��݂��A���O���X�g�ɍڂ��Ă��Ȃ��ꍇ
					if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable,
							ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL &&
							searchARRAY_OFFSET_LIST(exception_variable_list,
							ARRAY_OFFSET_LIST_data(a_i)->variable_name) == NULL){

						//�_�u�肪���݂��Ȃ��ꍇ�͌��Ƃ��Ēǉ�����
						if(searchDD(ARRAY_OFFSET_LIST_data(a_i)->variable_name, candidate_dd_list, &candidate_dd_info) == 0){
							DD_INFORMATION_LIST_push_back_ref(candidate_dd_list, new_DD_INFORMATION(ARRAY_OFFSET_LIST_data(a_i)->variable_name, EXPR_SLICING_LIST_data(e_i)));
							find_flag = FIND_DD;
							break;
						}
					}
				}
			}

		}

		//�f�[�^�ˑ��֌W�̃��X�g��ǉ�����
		if(DD_INFORMATION_LIST_size(candidate_dd_list) != 0){
			DD_INFORMATION_LIST_splice(expr_slicing->dd_list, DD_INFORMATION_LIST_end(expr_slicing->dd_list),
					candidate_dd_list, DD_INFORMATION_LIST_begin(candidate_dd_list), DD_INFORMATION_LIST_end(candidate_dd_list));
		}
	}

}
/**
�w�肵���Ώۂ̖��߂ƃO���[�o���ϐ��錾�Ɋւ��ăf�[�^�ˑ��֌W�����邩�ǂ������ׂ�B
���݂���΁A�O���[�o���ϐ��錾�ɑ΂��āA�f�[�^�ˑ��֌W�Ƃ��Č��т���

@param expr_slicing �w�肵���Ώۂ̖���
@param program_expr_slicing_list �v���O�����S�̂̃X���C�V���O���X�g

@return �Ȃ�
 */

void createDD_list_in_global(EXPR_SLICING *expr_slicing, EXPR_SLICING_LIST *program_expr_slicing_list){

	EXPR_SLICING_LISTIterator e_i;

	ARRAY_OFFSET_LISTIterator a_i;

	int find_flag;

	//�v���O�����S�̂̃X���C�V���O���X�g����O���[�o���ϐ��錾�����݂��邩�ǂ����T������
	for(e_i = EXPR_SLICING_LIST_begin(program_expr_slicing_list);
		e_i != EXPR_SLICING_LIST_end(program_expr_slicing_list);
		e_i = EXPR_SLICING_LIST_next(e_i)){

		find_flag = 0;

		//�X���C�V���O���̊ւ���Ă���AST�m�[�h����declaration_with_init�ł���A���Ȃ킿�O���[�o���ϐ��錾�ł���ꍇ
		if(CSTLString_compare_with_char(EXPR_SLICING_LIST_data(e_i)->expression->name, "declaration_with_init") == 0){
			//�O���[�o���ϐ��錾�̑Ώۂ̕ϐ��ɂ��Ē��ׂ�
			for(a_i = ARRAY_OFFSET_LIST_begin(EXPR_SLICING_LIST_data(e_i)->target_variable);
				a_i != ARRAY_OFFSET_LIST_end(EXPR_SLICING_LIST_data(e_i)->target_variable);
				a_i = ARRAY_OFFSET_LIST_next(a_i)){

				//�w�肳�ꂽ���߂̑Ώۂ̕ϐ����ˑ��֌W���A�O���[�o���ϐ��錾�ɑ΂��ăf�[�^�ˑ��֌W������ꍇ
				if(searchARRAY_OFFSET_LIST(expr_slicing->target_variable, ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL ||
						searchARRAY_OFFSET_LIST(expr_slicing->dependences, ARRAY_OFFSET_LIST_data(a_i)->variable_name) != NULL){

					//�����A�f�[�^�ˑ��֌W����O���[�o���ϐ����Ɠ����ł���A���[�J���ϐ��錾�����݂��Ȃ��ꍇ�A
					//�O���[�o���ϐ��錾���f�[�^�ˑ��֌W�Ƃ��Ēǉ�����
					if(searchDeclarationDD(ARRAY_OFFSET_LIST_data(a_i)->variable_name, expr_slicing) == 0){
						DD_INFORMATION_LIST_push_back_ref(expr_slicing->dd_list, new_DD_INFORMATION(ARRAY_OFFSET_LIST_data(a_i)->variable_name, EXPR_SLICING_LIST_data(e_i)));
						break;
					}
				}
			}
		}
	}

}
/**
�w�肵���Ώۂ̖��߂ɑ΂��āA�f�[�^�ˑ��֌W�̖��߂�T���A���̖��߂����т���B

@param expr_slicing �w�肵���Ώۂ̖���

@return �Ȃ�
 */
void createDD_list(EXPR_SLICING *expr_slicing){
	//�Ώۂ̖��߂Ɋւ���Ώ۔͈͂�ݒ肷��
	EXPR_SLICING *parent_expr_slicing = expr_slicing->parent;

	ARRAY_OFFSET_LIST *exception_variable_list = ARRAY_OFFSET_LIST_new();
	//���[�g�m�[�h�܂��́A�֐��Ăяo���ɂȂ�܂Őe���ċA�I�ɌĂяo��
	while(parent_expr_slicing != NULL && CSTLString_compare_with_char(parent_expr_slicing->expression->name, "function_definition_type_a") != 0
			&& CSTLString_compare_with_char(parent_expr_slicing->expression->name, "function_definition_type_b") != 0){
		//�����Afor�����������ꍇ�́Afor�����̑Ώۂ̕ϐ����f�[�^�ˑ��֌W�̏��O���X�g�ɓ����
		if(CSTLString_compare_with_char(parent_expr_slicing->expression->name, "for_statement_type_a") == 0 ||
				CSTLString_compare_with_char(parent_expr_slicing->expression->name, "for_statement_type_a") == 0){
			copyArrayOffsetList(parent_expr_slicing->target_variable, exception_variable_list, 0);
		}
		parent_expr_slicing = parent_expr_slicing->parent;

	}

	if(parent_expr_slicing != NULL && ( CSTLString_compare_with_char(parent_expr_slicing->expression->name, "function_definition_type_a") != 0
			|| CSTLString_compare_with_char(parent_expr_slicing->expression->name, "function_definition_type_b") != 0) ){
		int invest_flag = NOT_FIND;
		//���̊֐��͈̔͂ŋt���ōċA�I�ɒT�����A�ˑ��֌W�̕ϐ��Ɋ֌W���閽�߂���������A���̖��߂��f�[�^�ˑ��֌W���X�g�ɒǉ�����B
		createDD_list_Internal(parent_expr_slicing, expr_slicing, exception_variable_list, &invest_flag);
	}

	ARRAY_OFFSET_LIST_delete(exception_variable_list);
}

/**
�v���O�����X���C�V���O���X�g���̂��ׂĂ̖��߂ɑ΂��A�f�[�^�ˑ��֌W�̖��߂�T���A���̖��߂����т���B


@param expr_slicing_list �w�肵���Ώۂ̃v���O�����X���C�V���O���X�g
@param function_information_list �֐��Ɋւ����񃊃X�g
@param program_expr_slicing_list �v���O�����S�̂ւ̃X���C�V���O���X�g
@return �Ȃ�
 */
void createDD_listAll(EXPR_SLICING_LIST *expr_slicing_list, FUNCTION_INFORMATION_LIST *function_information_list,
		EXPR_SLICING_LIST *program_expr_slicing_list){
	EXPR_SLICING_LISTIterator e_i;
	//�Ώۂ̖��߂Ɋւ���Ώ۔͈͂�ݒ肷��
	//children1��T�����A�Y���̖��߂������邩�ǂ����𒲂ׂ�
	for(e_i = EXPR_SLICING_LIST_begin(expr_slicing_list);
		e_i != EXPR_SLICING_LIST_end(expr_slicing_list);
		e_i = EXPR_SLICING_LIST_next(e_i)){

		//�����A�Ώۂ̕ϐ���ˑ��֌W�̕ϐ������݂��閽�߂Ȃ�΁A�f�[�^�ˑ��֌W��T���A���̖��߂Ɍ��т���
		if(ARRAY_OFFSET_LIST_size(EXPR_SLICING_LIST_data(e_i)->target_variable) > 0 ||
				ARRAY_OFFSET_LIST_size(EXPR_SLICING_LIST_data(e_i)->dependences) > 0){

			//�֐��ďo����Ăяo���Ă���֐��ւ̃f�[�^�ˑ��֌W��T���o���A���̖��߂����т���
			createDD_list_in_Function(EXPR_SLICING_LIST_data(e_i), program_expr_slicing_list,
					function_information_list);

			//�Ώۂ̖��߂ɑ΂���f�[�^�ˑ��֌W��T���o���A���̖��߂����т���
			createDD_list(EXPR_SLICING_LIST_data(e_i));

			//�O���[�o���ϐ��ɑ΂��āA�f�[�^�ˑ��֌W��T���o���A���̖��߂����т���
			createDD_list_in_global(EXPR_SLICING_LIST_data(e_i), program_expr_slicing_list);
		}

		createDD_listAll(EXPR_SLICING_LIST_data(e_i)->children1,function_information_list, program_expr_slicing_list);
		createDD_listAll(EXPR_SLICING_LIST_data(e_i)->children2,function_information_list, program_expr_slicing_list);
	}
}

/**
�֐��Ăяo������A�Ăяo���Ă���֐��ւ̃f�[�^�ˑ��֌W�𐶐�����B

@param expr_slicing �֐��Ăяo�����܂܂�Ă��鏈����
@param expr_slicing_list �v���O�����S�̂̃v���O�����X���C�V���O���X�g
@param function_information_list �֐��Ɋւ����񃊃X�g

@return �Ȃ�
 */
void createDD_list_in_Function(EXPR_SLICING *expr_slicing, EXPR_SLICING_LIST *expr_slicing_list,
		FUNCTION_INFORMATION_LIST *function_information_list){

	ARRAY_OFFSET_LISTIterator a_i;
	EXPR_SLICING *search_expr_slicing;
	CSTLString *target_function_name = CSTLString_new();
	CSTLString *argument_number_str = CSTLString_new();
	int argument_number;
	CSTLString *argument_name = CSTLString_new();

	FUNCTION_INFORMATION *function_information;
	PARAM_INFORMATION_LISTIterator p_i;
	int p_counter;
	//expr_slicing�̑Ώۂ̕ϐ�����шˑ��֌W�����ׂĒT��
	for(a_i = ARRAY_OFFSET_LIST_begin(expr_slicing->target_variable);
		a_i != ARRAY_OFFSET_LIST_end(expr_slicing->target_variable);
		a_i = ARRAY_OFFSET_LIST_next(a_i)){

		//�����A�Ώۂ̕ϐ����֐��Ăяo���̈����̏ꍇ
		if(CSTLString_compare_with_char(ARRAY_OFFSET_LIST_data(a_i)->target_statement->name, "call_function") == 0){
			//�֐��������o��
			getStringFromAST(target_function_name, ASTLIST_ITERATOR_1(ARRAY_OFFSET_LIST_data(a_i)->target_statement));

			//expr_slicing_list����A�֐��Ăяo���ɑΉ�����֐��ւ̃v���O�����X���C�V���O�������o��
			search_expr_slicing = searchFunctionPSI(target_function_name, expr_slicing_list);

			//�֐��Ăяo���ɑΉ�����֐��ւ̃v���O�����X���C�V���O���̎��o���ɐ��������ꍇ
			if(search_expr_slicing != NULL){

				//�����ԍ������o��
				CSTLString_assign(argument_number_str, CSTLString_c_str(ARRAY_OFFSET_LIST_data(a_i)->variable_name));
				CSTLString_erase(argument_number_str, 0, CSTLString_find(argument_number_str, "#", 0) + 1);
				argument_number = atoi(CSTLString_c_str(argument_number_str));

				//�֐��Ăяo����AST�m�[�h����A�������������o��
				function_information = searchFUNCTION_INFORMATION(target_function_name, function_information_list);

				for(p_counter = 0, p_i = PARAM_INFORMATION_LIST_begin(function_information->param_information_list);
					p_i != PARAM_INFORMATION_LIST_end(function_information->param_information_list);
					p_counter++, p_i = PARAM_INFORMATION_LIST_next(p_i)){
					if(p_counter == argument_number){
						CSTLString_assign(argument_name, CSTLString_c_str(PARAM_INFORMATION_LIST_data(p_i)->param_name));
						break;
					}
				}

				//���̊֐��ւ̃X���C�V���O�ɑ΂��āA���������ɑ΂���f�[�^�ˑ��֌W��expr_slicing�ɐݒ肷��
				createDD_list_in_argument(expr_slicing, argument_name, search_expr_slicing);
			}
		}
	}

	CSTLString_delete(target_function_name);
	CSTLString_delete(argument_number_str);
	CSTLString_delete(argument_name);
}

/**
�֐��ւ̃X���C�V���O���ɑ΂��āA�����������ˑ��֌W�Ƃ��ėp���Ă��閽�߂�T���A������w�肵���v���O�����X���C�V���O
�̃f�[�^�ˑ��֌W�Ƃ��Ēǉ�����B

@param expr_slicing �֐��Ăяo���̃v���O�����X���C�V���O
@param argument_name ��������
@param function_definition_expr_slicing �֐��錾�ւ̃v���O�����X���C�V���O

@return �Ȃ�
 */
void createDD_list_in_argument(EXPR_SLICING *expr_slicing, CSTLString *argument_name,
		EXPR_SLICING *function_definition_expr_slicing){

	EXPR_SLICING_LISTIterator e_i;

	CSTLString *target_variable;
	DD_INFORMATION *dd_information;

	//expr_slicing��children2�𖖔�����T������
	for(e_i = EXPR_SLICING_LIST_rbegin(function_definition_expr_slicing->children2);
		e_i != EXPR_SLICING_LIST_rend(function_definition_expr_slicing->children2);
		e_i = EXPR_SLICING_LIST_prev(e_i)){

		createDD_list_in_argument(expr_slicing, argument_name, EXPR_SLICING_LIST_data(e_i));

		//�����A�����������p�����Ă��閽�߂���������Aexpr_slicing�̃f�[�^�ˑ��֌W�Ƃ��Ēǉ�����
		if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable, argument_name) != NULL){

			target_variable = CSTLString_new();
			CSTLString_assign(target_variable, CSTLString_c_str(argument_name));

			dd_information = new_DD_INFORMATION(target_variable, EXPR_SLICING_LIST_data(e_i));
			DD_INFORMATION_LIST_push_back_ref(expr_slicing->dd_list, dd_information);
			break;
		}
	}
	//expr_slicing��children1�𖖔�����T������
	for(e_i = EXPR_SLICING_LIST_rbegin(function_definition_expr_slicing->children1);
		e_i != EXPR_SLICING_LIST_rend(function_definition_expr_slicing->children1);
		e_i = EXPR_SLICING_LIST_prev(e_i)){

		createDD_list_in_argument(expr_slicing, argument_name, EXPR_SLICING_LIST_data(e_i));

		//�����A�����������p�����Ă��閽�߂���������Aexpr_slicing�̃f�[�^�ˑ��֌W�Ƃ��Ēǉ�����
		if(searchARRAY_OFFSET_LIST(EXPR_SLICING_LIST_data(e_i)->target_variable, argument_name) != NULL){
			target_variable = CSTLString_new();
			CSTLString_assign(target_variable, CSTLString_c_str(argument_name));

			dd_information = new_DD_INFORMATION(target_variable, EXPR_SLICING_LIST_data(e_i));
			DD_INFORMATION_LIST_push_back_ref(expr_slicing->dd_list, dd_information);
			break;
		}

	}

}

/**
�w�肵�����ʎq�̖��߂ɑ΂��ăX�^�e�B�b�N�X���C�V���O�������s���B

@param expr_slicing �w�肵�����߂ɑ΂���v���O�����X���C�V���O���

@return �Ȃ�

*/
void staticSlicing(EXPR_SLICING *expr_slicing){
	//�����A���߂�NULL�ł͂Ȃ��A�g�p���邩�ǂ����̃t���O�������Ă��Ȃ������ꍇ�A���̃t���O�𗧂Ă�
	if(expr_slicing != NULL && expr_slicing->flag == 0){
		DD_INFORMATION_LISTIterator dd_e_i;
		//���̖��߂��g�p����
		expr_slicing->flag = 1;
		//�e�����ǂ�
		staticSlicing(expr_slicing->parent);

		//�f�[�^�ˑ��֌W���X�g�ɏ]���Ė��߂����ǂ�
		for(dd_e_i = DD_INFORMATION_LIST_rbegin(expr_slicing->dd_list);
				dd_e_i != DD_INFORMATION_LIST_rend(expr_slicing->dd_list);
				dd_e_i = DD_INFORMATION_LIST_prev(dd_e_i)){
			staticSlicing(DD_INFORMATION_LIST_data(dd_e_i)->dd_target);
		}

	}

}

/**
�w�肵�����߂ւ�AST�m�[�h�Ɋ�Â���expr_slicing_list�ɑ΂��ăX�^�e�B�b�N�X���C�V���O�������s���B

@param inst_ast �w�肵�����߂ւ�AST�m�[�h
@param expr_slicing_list �X�^�e�B�b�N�X���C�V���O�������s�����߂̍\���̃��X�g

@return �����������ǂ�����ԋp����B�@�P�F�����@�O�F���s

*/
int startStaticSlicing(AST *inst_ast, EXPR_SLICING_LIST *expr_slicing_list){
	EXPR_SLICING_LISTIterator e_i;
	//AST�m�[�h����A�X���C�V���O�����Ɋ֌W����ꏊ����������
	int success_flag = 0;

	for(e_i = EXPR_SLICING_LIST_begin(expr_slicing_list);
		success_flag == 0 && e_i != EXPR_SLICING_LIST_end(expr_slicing_list);
		e_i = EXPR_SLICING_LIST_next(e_i)){

		//�v���O�����X���C�V���O���ɓo�^����Ă���AST�m�[�h�ƈ�v����΁A����ɑ΂��ăv���O�����X���C�V���O�������s��
		if(EXPR_SLICING_LIST_data(e_i)->expression == inst_ast){
			staticSlicing(EXPR_SLICING_LIST_data(e_i));
			success_flag = 1;
			break;
		}
		//�����łȂ���΁A�v���O�����X���C�V���O�̎q�m�[�h���Q�Ƃ���
		else{

			success_flag = startStaticSlicing(inst_ast, EXPR_SLICING_LIST_data(e_i)->children1);
			if(success_flag){
				break;
			}

			success_flag = startStaticSlicing(inst_ast, EXPR_SLICING_LIST_data(e_i)->children2);
			if(success_flag){
				break;
			}

		}
	}

	return success_flag;
}
