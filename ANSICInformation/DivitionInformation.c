 #include"DivitionInformation.h"
 #include<stdio.h>
 #include<stdlib.h>

 #define ASTLIST_ITERATOR_1(target) ASTList_data(ASTList_begin(target->children))
 #define ASTLIST_ITERATOR_2(target) ASTList_data(ASTList_next(ASTList_begin(target->children)))
 #define ASTLIST_ITERATOR_3(target) ASTList_data(ASTList_next(ASTList_next(ASTList_begin(target->children))))

//���Z����]�Z���ǂ����̃t���O
#define TYPE_DIV 0
#define TYPE_MOD 1

 /**
 DIVITION_INFORMATION�̃��X�g
 */
 CSTL_LIST_IMPLEMENT(DIVITION_INFORMATION_LIST, DIVITION_INFORMATION)

 /**
 ���Z����я�]�Z�Ɋւ�����𐶐�����B

 @param target_expression �Ώۂ̎��ւ�AST�m�[�h�̃A�h���X
 @param type ���Z����]���ǂ����̃^�C�v�@�O�F���Z���@�P�F��]��
 @param statement ���Z����я�]�ȉ��̎�
 @param identifiers �����̎��ʎq�ꗗ

 @return �������ꂽ���ւ̃A�h���X���Ԃ����
 */
 DIVITION_INFORMATION *new_DIVITION_INFORMATION(AST *target_expression, int type, CSTLString *statement, ARRAY_OFFSET_LIST *identifiers){
	//���Z����я�]�Z�Ɋւ������V���ɐ�������
	DIVITION_INFORMATION *new_divition_information = (DIVITION_INFORMATION*)malloc(sizeof(DIVITION_INFORMATION));

	//���������Ɏ��s�����ꍇ�̓������s���Ƃ��ăG���[��Ԃ������I��������
	if(new_divition_information == NULL){
		fprintf(stderr, "�������s���ł�\n");
		exit(1);
	}
	//�����ɐ���������A�K�v�ȏ������Ă���
	else{
		new_divition_information->target_expression = target_expression;
		new_divition_information->type = type;
		new_divition_information->statement = statement;
		new_divition_information->identifiers = identifiers;
	}
	return new_divition_information;
 }

 /**
 ���Z����я�]�Z�Ɋւ�����𐶐�����B

 @param target_expression �Ώۂ̎��ւ�AST�m�[�h�̃A�h���X
 @param type ���Z����]���ǂ����̃^�C�v�@�O�F���Z���@�P�F��]��
 @param statement ���Z����я�]�ȉ��̎�
 @param identifiers �����̎��ʎq�ꗗ

 @return �������ꂽ���ւ̃A�h���X���Ԃ����
 */
 DIVITION_INFORMATION *new_DIVITION_INFORMATION_char(AST *target_expression, int type, char *statement, ARRAY_OFFSET_LIST *identifiers){
	//statement�Ɋւ���CSTL������𐶐����Astatement�̓��e��������
	CSTLString *statement_cstl = CSTLString_new();
	CSTLString_assign(statement_cstl, statement);

	//�V���ȏ��Z����я�]�Z�Ɋւ�����𐶐�����
	return new_DIVITION_INFORMATION(target_expression, type, statement_cstl, identifiers);
 }

 /**
 �w�肳�ꂽ������Adiv_expr�����mod_expr�������A����ȉ��̎������Z����я�]�c�Ɋւ�����Ɋi�[����

 @param expression_ast �w�肳�ꂽ���ւ�AST�m�[�h�̃A�h���X
 @param function_information_list �֐��Ɋւ�����̃��X�g
 @param vtlist �ϐ��e�[�u�����X�g
 @param divition_information_list ���Z����я�]�Z�Ɋւ�������i�[���邽�߂̃��X�g
 @param target_expression �Ώۂ̎��ւ�AST�m�[�h�̃A�h���X
 @param ignore_ast_list �d���h�~�̂��߂Ɏg�p����AST�m�[�h�ւ̃��X�g

 @return �Ȃ�
 */
 void getDIVITION_INFORMATION_LIST(AST *expression_ast, FUNCTION_INFORMATION_LIST *function_information_list,
		 VARIABLE_TABLE_LIST *vtlist, DIVITION_INFORMATION_LIST *divition_information_list, AST *target_expression,
		 ASTPOINTER_LIST *ignore_ast_list){
	ASTListIterator ast_i;



	//�����A���Z�������m�[�h����������
	if(CSTLString_compare_with_char(expression_ast->name, "div_expr") == 0){
		//�w�肳�ꂽexpression_ast��ignore_ast_list�ɑ��݂��Ȃ����ǂ����𒲂ׁA������Ȃ���Βǉ�����
		if(checkIgnoreASTList(expression_ast, ignore_ast_list) == 0){
			//�����̎��ʎq���X�g
			ARRAY_OFFSET_LIST *identifiers = ARRAY_OFFSET_LIST_new();

			//�������X�g
			ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();
			//�E�ӎ��̎����擾����
			CSTLString *statement = CSTLString_new();
			getStringFromAST(statement, ASTLIST_ITERATOR_3(expression_ast));

			//IDENTIFIER�ƃ|�C���^���Z���Ƃ��ɒT���悤�ɂ���
			int switch_mode = 0;
			getArgumentOffsetInfo(ASTLIST_ITERATOR_3(expression_ast), function_information_list, vtlist, ignore_ast_list, identifiers, target_expression, &switch_mode);

			//���Z����я�]�Z�Ɋւ�����Ƃ��ă��X�g�ɒǉ�����
			DIVITION_INFORMATION_LIST_push_back_ref( divition_information_list,
				new_DIVITION_INFORMATION(target_expression, TYPE_DIV, statement, identifiers)
				);

			//�������X�g���폜������
			ASTPOINTER_LIST_clear(ignore_ast_list);
			ASTPOINTER_LIST_delete(ignore_ast_list);
		}
	}

	//�����A��]�Z�������m�[�h����������
	else if(CSTLString_compare_with_char(expression_ast->name, "mod_expr") == 0){
		//�w�肳�ꂽexpression_ast��ignore_ast_list�ɑ��݂��Ȃ����ǂ����𒲂ׁA������Ȃ���Βǉ�����
		if(checkIgnoreASTList(expression_ast, ignore_ast_list) == 0){
			//�����̎��ʎq���X�g
			ARRAY_OFFSET_LIST *identifiers = ARRAY_OFFSET_LIST_new();

			//�������X�g
			ASTPOINTER_LIST *ignore_ast_list = ASTPOINTER_LIST_new();
			//�E�ӎ��̎����擾����
			CSTLString *statement = CSTLString_new();
			getStringFromAST(statement, ASTLIST_ITERATOR_3(expression_ast));

			//IDENTIFIER�ƃ|�C���^���Z���Ƃ��ɒT���悤�ɂ���
			int switch_mode = 0;
			getArgumentOffsetInfo(ASTLIST_ITERATOR_3(expression_ast), function_information_list, vtlist, ignore_ast_list, identifiers, target_expression, &switch_mode);

			//���Z����я�]�Z�Ɋւ�����Ƃ��ă��X�g�ɒǉ�����
			DIVITION_INFORMATION_LIST_push_back_ref( divition_information_list,
				new_DIVITION_INFORMATION(target_expression, TYPE_MOD, statement, identifiers)
				);

			//�������X�g���폜������
			ASTPOINTER_LIST_clear(ignore_ast_list);
			ASTPOINTER_LIST_delete(ignore_ast_list);
		}
	}

	//�qAST�m�[�h���Q�Ƃ���
	for(ast_i = ASTList_begin(expression_ast->children);
		ast_i != ASTList_end(expression_ast->children);
		ast_i = ASTList_next(ast_i)){
			getDIVITION_INFORMATION_LIST(ASTList_data(ast_i), function_information_list, vtlist, divition_information_list, target_expression, ignore_ast_list);
		}
 }

 /**
 ���Z����я�]�Z�Ɋւ�����̃��X�g�̓��e���o�͂�����

 @param divition_information_list ���Z����я�]�Z�Ɋւ�����̃��X�g

 @return �Ȃ�
 */
 void printDIVITION_INFORMATION_LIST(DIVITION_INFORMATION_LIST *divition_information_list){
 	//���Z����я�]���Ɋւ���C�e���[�^
	DIVITION_INFORMATION_LISTIterator di_i;

	int counter;

	for(counter = 1, di_i = DIVITION_INFORMATION_LIST_rbegin(divition_information_list);
		di_i != DIVITION_INFORMATION_LIST_rend(divition_information_list);
		counter++, di_i = DIVITION_INFORMATION_LIST_prev(di_i)){

			printf("---DIVITION_INFOMATION_%d---\n\n", counter);
			printf("TARGET_LINE = \"%d\"\n", DIVITION_INFORMATION_LIST_data(di_i)->target_expression->line);
			printf("TYPE = ");
			//���Z����]�Z���ɂ���ēK�؂ȃ^�C�v���o�͂�����
			if(DIVITION_INFORMATION_LIST_data(di_i)->type == TYPE_DIV){
				printf("\"DIVITION\"\n");
			}else{
				printf("\"MOD\"\n");
			}
			printf("STATEMENT = \"%s\"\n\n",CSTLString_c_str(DIVITION_INFORMATION_LIST_data(di_i)->statement));
			printf("----------------------------\n\n");

		}
 }
