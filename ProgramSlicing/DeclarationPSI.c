#include "DeclarationPSI.h"

#include "../ANSICInformation/ANSIC_CODE.h"

/**
�錾����AST�m�[�hdeclaration����v���O�����X���C�V���O�𒊏o���A
�v���O�����X���C�V���O���X�gexpr_slicing_list�ɒǉ�����B

@param expr_slicing_list �ǉ���̃v���O�����X���C�V���O���X�gexpr_slicing_list
@param declaration ���S�ʂɊւ���AST�m�[�h
@param parent �m�[�h��ǉ�����Ƃ��̐e�m�[�h
@param vtlist �ϐ��e�[�u�����X�g
@param function_information_list �֐��Ɋւ����񃊃X�g
@param ignore_ast_list �d���h�~�̂��߂ɖ�������m�[�h���X�g
@param target_statement expression_statement���w�������m�[�h

@return �Ȃ�
 */
void getVariableDeclarationtPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *declaration, EXPR_SLICING *parent,
		VARIABLE_TABLE_LIST *vtlist, FUNCTION_INFORMATION_LIST *function_information_list, ASTPOINTER_LIST *ignore_ast_list,
		AST *target_statement){

	//AST�̎q�m�[�h���Q�Ƃ����邽�߂̃C�e���[�^
	ASTListIterator ast_iterator;

	//��������������ꍇ
	if(CSTLString_compare_with_char(declaration->name, "init_declarator") == 0){
		EXPR_SLICING_LIST *children1 = EXPR_SLICING_LIST_new();
		EXPR_SLICING_LIST *children2 = EXPR_SLICING_LIST_new();

		//�ϐ��̒�`�ɑ΂���m�[�h�ɂ�����e�����̃|�C���^��z��̃I�t�Z�b�g�Ɋւ�����̃��X�g
		ARRAY_OFFSET_LIST * declarator_array_offset_list = ARRAY_OFFSET_LIST_new();

		//�����̎��ɂ�����e�����̃|�C���^��z��̃I�t�Z�b�g�Ɋւ�����̃��X�g
		ARRAY_OFFSET_LIST * initializer_array_offset_list = ARRAY_OFFSET_LIST_new();

		AST *declarator_expression = getASTwithString(ASTLIST_ITERATOR_1(declaration), "IDENTIFIER", -1);

		AST *initializer_expression = ASTLIST_ITERATOR_3(declaration);

		//�ϐ��e�[�u������A�ϐ��̒�`�ɑ΂���m�[�h�ɊY���������T���A����ɑ΂���z��I�t�Z�b�g�����擾����B�i�q�m�[�h�̂P�Ԗڂ̎Q�Ɓj
		getDeclaratorArrayOffset(declarator_array_offset_list, declarator_expression, target_statement, vtlist);
		//�����̎��ɂ��āA�z��I�t�Z�b�g���X�g���擾����i�q�m�[�h�̂R�Ԗڂ̎Q�Ɓj
		getARRAY_OFFSET_LIST(initializer_expression, initializer_array_offset_list,
				function_information_list, vtlist, ignore_ast_list, target_statement);

		//�X���C�V���O���X�g�ɒǉ�����
		EXPR_SLICING_LIST_push_back_ref(expr_slicing_list, new_EXPR_SLICING(EXPR_SLICING_LIST_size(expr_slicing_list) + 1, target_statement,
				declarator_array_offset_list,initializer_array_offset_list, children1, children2, parent));

	}else if(CSTLString_compare_with_char(declaration->name, "t_init_declarator") == 0){
		EXPR_SLICING_LIST *children1 = EXPR_SLICING_LIST_new();
		EXPR_SLICING_LIST *children2 = EXPR_SLICING_LIST_new();

		//�ϐ��̒�`�ɑ΂���m�[�h�ɂ�����e�����̃|�C���^��z��̃I�t�Z�b�g�Ɋւ�����̃��X�g
		ARRAY_OFFSET_LIST * declarator_array_offset_list = ARRAY_OFFSET_LIST_new();

		//�����̎��ɂ�����e�����̃|�C���^��z��̃I�t�Z�b�g�Ɋւ�����̃��X�g
		ARRAY_OFFSET_LIST * dependences = ARRAY_OFFSET_LIST_new();

		AST *declarator_expression = getASTwithString(ASTLIST_ITERATOR_1(declaration), "IDENTIFIER", -1);

		//�ϐ��e�[�u������A�ϐ��̒�`�ɑ΂���m�[�h�ɊY���������T���A����ɑ΂���z��I�t�Z�b�g�����擾����B�i�q�m�[�h�̂P�Ԗڂ̎Q�Ɓj
		getDeclaratorArrayOffset(declarator_array_offset_list, declarator_expression, target_statement, vtlist);

		//�X���C�V���O���X�g�ɒǉ�����
		EXPR_SLICING_LIST_push_back_ref(expr_slicing_list, new_EXPR_SLICING(EXPR_SLICING_LIST_size(expr_slicing_list) + 1, target_statement,
				declarator_array_offset_list,dependences, children1, children2, parent));
	}
	else{
		//AST�̎q�m�[�h���Q�Ƃ�����
		for(ast_iterator = ASTList_begin(declaration->children);
			ast_iterator != ASTList_end(declaration->children);
			ast_iterator = ASTList_next(ast_iterator)){

			getVariableDeclarationtPSI(expr_slicing_list , ASTList_data(ast_iterator), parent,
					vtlist, function_information_list, ignore_ast_list, target_statement);

		}
	}
}

/**
�^��`����AST�m�[�htypedef_declaration����v���O�����X���C�V���O�𒊏o���A
�v���O�����X���C�V���O���X�gexpr_slicing_list�ɒǉ�����B

@param expr_slicing_list �ǉ���̃v���O�����X���C�V���O���X�gexpr_slicing_list
@param declaration ���S�ʂɊւ���AST�m�[�h
@param parent �m�[�h��ǉ�����Ƃ��̐e�m�[�h

@return �Ȃ�
 */
void getTypedefDeclarationtPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *typedef_declaration, EXPR_SLICING *parent){
	//children1,children2�𐶐�����i�Ȃɂ�����Ȃ��j
	EXPR_SLICING_LIST *children1 = EXPR_SLICING_LIST_new();
	EXPR_SLICING_LIST *children2 = EXPR_SLICING_LIST_new();

	//�ϐ��̒�`�ɑ΂���m�[�h�ɂ�����e�����̃|�C���^��z��̃I�t�Z�b�g�Ɋւ�����̃��X�g�i�Ȃɂ�����Ȃ��j
	ARRAY_OFFSET_LIST * target_variable = ARRAY_OFFSET_LIST_new();

	//�����̎��ɂ�����e�����̃|�C���^��z��̃I�t�Z�b�g�Ɋւ�����̃��X�g�i�Ȃɂ�����Ȃ��j
	ARRAY_OFFSET_LIST * dependences = ARRAY_OFFSET_LIST_new();

	//�X���C�V���O���𐶐�����
	EXPR_SLICING *new_expr_slicing = new_EXPR_SLICING(EXPR_SLICING_LIST_size(expr_slicing_list) + 1, typedef_declaration,
			target_variable, dependences, children1, children2, parent);

	//���̃X���C�V���O���͏�Ɏg�p�\�ɂ���
	new_expr_slicing->flag = 1;

	//���������X���C�V���O�����X���C�V���O���X�g�ɒǉ�����
	EXPR_SLICING_LIST_push_back_ref(expr_slicing_list, new_expr_slicing);
}

/**
�錾����AST�m�[�hdeclaration����A�֐��ɑ΂���v���O�����X���C�V���O�𒊏o���A
�v���O�����X���C�V���O���X�gexpr_slicing_list�ɒǉ�����B

@param expr_slicing_list �ǉ���̃v���O�����X���C�V���O���X�gexpr_slicing_list
@param declaration ���S�ʂɊւ���AST�m�[�h
@param parent �m�[�h��ǉ�����Ƃ��̐e�m�[�h
@param vtlist �ϐ��e�[�u�����X�g
@param function_information_list �֐��Ɋւ����񃊃X�g
@param ignore_ast_list �d���h�~�̂��߂ɖ�������m�[�h���X�g
@param target_statement expression_statement���w�������m�[�h
@return �Ȃ�
 */
void getDeclarationtPSI(EXPR_SLICING_LIST *expr_slicing_list, AST *declaration, EXPR_SLICING *parent,
		VARIABLE_TABLE_LIST *vtlist, FUNCTION_INFORMATION_LIST *function_information_list, ASTPOINTER_LIST *ignore_ast_list,
		AST *target_statement){
	CSTLString *type = CSTLString_new();

	//�^�����擾����
	getStringFromAST(type, ASTLIST_ITERATOR_1(declaration));

	//�����A�^����typedef���܂܂�Ă����ꍇ�A�^��`�Ƃ݂Ȃ��A�X���C�V���O�����擾����
	if(CSTLString_find(type, "typedef", 0) != CSTL_NPOS){
		getTypedefDeclarationtPSI(expr_slicing_list, declaration, parent);
	}

	//typedef���܂܂�Ă��Ȃ���΁A�ϐ��錾�Ƃ݂Ȃ��A�X���C�V���O�����擾����
	else{
		getVariableDeclarationtPSI(expr_slicing_list, declaration, parent, vtlist,
				function_information_list, ignore_ast_list, target_statement);

	}

	CSTLString_delete(type);

}
