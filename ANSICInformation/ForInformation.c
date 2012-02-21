#include<stdio.h>
#include<stdlib.h>
#include "ForInformation.h"

CSTL_LIST_IMPLEMENT(ForInformationList, ForInformation)

#include"ANSIC_CODE.h"

/**
for���Ɋւ�����FOR_INFORMATION�𐶐�����B
@param target_expression ����for�����̂̏��
@param init_expression ������
@param continue_condition �p����
@param inc_dec_expression ������
@param statement for�����̑S�̂̎����w��
@return �������ꂽFOR_INFORMATION�ւ̃A�h���X��Ԃ��B

*/
ForInformation *new_FOR_INFORMATION(AST *target_expression, AST *init_expression, AST *continue_condition, AST *inc_dec_expression, AST *statement){
	//for���Ɋւ������V������������
	ForInformation *new_for_information = (ForInformation*)malloc(sizeof(ForInformation));

	if(new_for_information == NULL){
		fprintf(stderr, "�������s���ł�\n");
		exit(1);

	}else{
		//�K�v�ȏ������Ă���
		new_for_information->target_expression = target_expression;
		new_for_information->init_expression = init_expression;
		new_for_information->continue_condition = continue_condition;
		new_for_information->inc_dec_expression = inc_dec_expression;
		new_for_information->statement = statement;

	}

	return new_for_information;
}

/**
for���Ɋւ�����̃��X�gfor_information_list���o�͂���
@param for_information_list for���Ɋւ�����̃��X�g

@return �Ȃ�
*/
void print_FOR_INFORMATION_LIST(ForInformationList *for_information_list){
	ForInformationListIterator f_ite;
	int counter;
	//for���Ɋւ�����̃��X�g���擾����
	for(counter = 1, f_ite = ForInformationList_begin(for_information_list);
		f_ite != ForInformationList_end(for_information_list);
		counter++, f_ite = ForInformationList_next(f_ite)){
			CSTLString *output = CSTLString_new();
			printf("------------------FOR_INFORMATION_%d------------------\n\n", counter);
			printf("FOR LINE = \"%d\"\n", ForInformationList_data(f_ite)->target_expression->line);

			CSTLString_assign(output, "");
			getStringFromAST(output, ForInformationList_data(f_ite)->init_expression);
			printf("INIT_EXPRESSION CONTENT = \"%s\"\n", CSTLString_c_str(output));

			CSTLString_assign(output, "");
			getStringFromAST(output, ForInformationList_data(f_ite)->continue_condition);
			printf("CONTINUE_CONDITION CONTENT = \"%s\"\n", CSTLString_c_str(output));

			if(ForInformationList_data(f_ite)->inc_dec_expression != NULL){
				CSTLString_assign(output, "");
				getStringFromAST(output, ForInformationList_data(f_ite)->inc_dec_expression);
				printf("INC_DEC_EXPRESSION CONTENT = \"%s\"\n", CSTLString_c_str(output));
			}else{
				printf("INC_DEC_EXPRESSION CONTENT = \"null\"\n");
			}

			CSTLString_assign(output, "");
			getStringFromAST(output, ForInformationList_data(f_ite)->statement);
			printf("STATEMENT CONTENT = \"%s\"\n\n", CSTLString_c_str(output));
			printf("------------------------------------------------------\n\n");

		}
}

/**
for���Ɋւ�����̃��X�gfor_information_list����A�w�肵��AST�m�[�h�ɑΉ��������̂��o�͂�����B
@param for_information_list �����Ώۂ�for���Ɋւ�����̃��X�g
@param target_ast ��������AST

@return �}�b�`�������̂�������΁A����ɑΉ��������̂ւ̃A�h���X���o�͂�����B������Ȃ��ꍇ��NULL��Ԃ��B
*/
ForInformation *searchFOR_INFORMATION_FromAST(ForInformationList *for_information_list, AST *target_ast){
	ForInformationListIterator f_ite;

	ForInformation *ret = NULL;

	//for���Ɋւ�����̃��X�g���擾����
	for(f_ite = ForInformationList_begin(for_information_list);
		f_ite != ForInformationList_end(for_information_list);
		f_ite = ForInformationList_next(f_ite)){
			if(ForInformationList_data(f_ite)->target_expression == target_ast){
				ret = ForInformationList_data(f_ite);
				break;
			}
	}

	return ret;
}

/**
for_iteration��AST�m�[�h����Afor���Ɋւ�����̃��X�g���擾����B

@param for_information_list for���Ɋւ�����̃��X�g
@param for_iteration_ast for���Ɋւ�����̃��X�g

@return �Ȃ�
*/
void getFOR_INFORMATION_LIST(ForInformationList *for_information_list, AST *for_iteration_ast){

	AST *target_expression;
	AST *init_expression;
	AST *continue_condition;
	AST *inc_dec_expression;
	AST *statement;

	//for���̃^�C�v�ɏ]���āA�擾����
	target_expression = for_iteration_ast;

	if(CSTLString_compare_with_char(for_iteration_ast->name, "for_statement_type_a") == 0){

		init_expression = ASTLIST_ITERATOR_3(for_iteration_ast);
		continue_condition = ASTLIST_ITERATOR_4(for_iteration_ast);
		inc_dec_expression = NULL;
		statement = ASTLIST_ITERATOR_6(for_iteration_ast);

	}else if(CSTLString_compare_with_char(for_iteration_ast->name, "for_statement_type_b") == 0){

		init_expression = ASTLIST_ITERATOR_3(for_iteration_ast);
		continue_condition = ASTLIST_ITERATOR_4(for_iteration_ast);
		inc_dec_expression = ASTLIST_ITERATOR_5(for_iteration_ast);
		statement = ASTLIST_ITERATOR_7(for_iteration_ast);

	}else if(CSTLString_compare_with_char(for_iteration_ast->name, "for_statement_type_c") == 0 ||
			CSTLString_compare_with_char(for_iteration_ast->name, "for_statement_type_d") == 0){

		fprintf(stderr, "#%s#:%d:Can't define declaration in for expression!\n",getFileName(),ASTLIST_ITERATOR_1(for_iteration_ast));
		exit(1);

	}else{
		fprintf(stderr, "Unexpected for type!!\n");
		exit(1);
	}

	statement = ASTLIST_ITERATOR_1(statement);
	if(CSTLString_compare_with_char(statement->name, "compound_statement_a") == 0){
		statement = NULL;
	}else if(CSTLString_compare_with_char(statement->name, "compound_statement_b") == 0){
		statement = ASTLIST_ITERATOR_2(statement);
	}

	ForInformationList_push_back_ref(for_information_list,
		new_FOR_INFORMATION(
		target_expression, init_expression, continue_condition, inc_dec_expression, statement
		)
	);

}
