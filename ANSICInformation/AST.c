#ifndef AST_HEADDER
#include "AST.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "../Library/Stack_int.h"
#include "ANSIC_CODE.h"

CSTL_LIST_IMPLEMENT(ASTList, struct abstract_syntax_tree)

/**
�V����AST�m�[�h�𐶐�����B
@param new_name �V�����m�[�h��
@param new_content �V�������e
@param new_line �V�����s��
@return �V�����������ꂽAST�m�[�h�ւ̃A�h���X���Ԃ����B
*/
AST* new_AST(char *new_name, char *new_content,int new_line){
	//�V����AST�m�[�h�𓮓I�m�ۂŎ擾����
	AST* new_ASTNode = (AST*)malloc(sizeof(AST));
	//�V����AST�m�[�h�ɖ��O�E���e�E�s�����w�肵�A�q�m�[�h�̏���������������
	new_ASTNode->name = CSTLString_new();
	CSTLString_assign(new_ASTNode->name, new_name);
	new_ASTNode->content = CSTLString_new();
	CSTLString_assign(new_ASTNode->content, new_content);
	new_ASTNode->line = new_line;
	new_ASTNode->children = ASTList_new();

	//�ԋp�l�̃^�C�v�͏���������i�����setASTReturnType�ɂ���Ă��ƂŒǉ������j
	new_ASTNode->return_type = CSTLString_new();

	//�u���b�N���x����ID�̏������������Ȃ��i�����setASTBlocklevelAndId�ɂ���Ă��ƂŒǉ������j
	new_ASTNode->block_level = 0;
	new_ASTNode->block_id = 0;
	new_ASTNode->idlist = IDLIST_new();

	//AST�̃f�o�b�O���[�hAST_DEBUG_MODE���`�����ꍇ�A�V����AST�m�[�h�̖��O�E���e�E�s����\��������
#ifdef AST_DEBUG_MODE
	printf("new node = \"%s\" content = \"%s\" line = \"%d\"\n",CSTLString_c_str(new_ASTNode->name),CSTLString_c_str(new_ASTNode->content),new_ASTNode->line);
	fflush(stdout);
#endif

	//�V����AST�m�[�h��Ԃ�
	return new_ASTNode;

}

/**
���O�Ɠ��e�������ł���AST�m�[�h�𐶐�����B
@param new_name �V�����m�[�h��
@param new_line �V�����s��
@return �V�����������ꂽAST�m�[�h�ւ̃A�h���X���Ԃ����B
*/
AST* same_new_AST(char *new_name, int new_line){
	//���O�Ɠ��e������AST�m�[�h�𐶐�������
	return new_AST(new_name, new_name, new_line);
}

/**
AST�̃m�[�h�����ǂ�Aroot�m�[�h�ȉ��̃m�[�h�̖��O�E���e�E�s����\��������B
�܂��A���ʃ��x���̃m�[�h�̓^�u��}�����\������B�Ⴆ�΁A1���x�����ʂ̃m�[�h�̓^�u��1�}��������ŕ\�������B
@param root �V�����m�[�h��
@param tab_level �^�u���x��(���̐����^�u���}�������j
@return �Ȃ�
*/
void traverseAST(AST *root, int tab_level){
	int i;
	ASTListIterator p;

	//tab_level���^�u���o�͂�����
	for(i = 0; i < tab_level; i++){
		printf("\t");
	}
	//���[�t�m�[�h�i�qAST�m�[�h�̐���0��AST�m�[�h�j�̏ꍇ�A*��ǉ��ŏo�͂�����B�������邱�ƂŃ��[�t�m�[�h������������
	if(ASTList_size(root->children) == 0){
		printf("*");
	}
	//AST�m�[�h�̖��O�E���e�E�s�����o�͂�����
	printf("node name = \"%s\" content = \"%s\" line = \"%d\" return_type = \"%s\" block_level = \"%d\" block_level = \"%d\"",
		CSTLString_c_str(root->name), CSTLString_c_str(root->content) ,root->line, CSTLString_c_str(root->return_type), root->block_level, root->block_id);
	//block_id�̓��e���o�͂���B
	printf("idlist = \"");
	printIDLIST(root->idlist, 0);
	printf("\"\n");

	//AST�m�[�h���qAST�m�[�h�̏��������Ă�����A�qAST�m�[�h�ɂ��čċA�I�ɎQ�Ƃ�����
	for(p = ASTList_begin(root->children); p != ASTList_end(root->children); p = ASTList_next(p)){
		traverseAST(ASTList_data(p), tab_level + 1);
	}
}

/**
AST�̃m�[�h�����ǂ�Aroot�m�[�h�ȉ��̃m�[�h�̖��O�E���e�E�s����XML�`���ŏo�͂���B�i�f�o�b�O�p�j
�܂��A���ʃ��x���̃m�[�h�̓^�u��}�����o�͂���B�Ⴆ�΁A1���x�����ʂ̃m�[�h�̓^�u��1�}��������Ń^�O���o�͂����B
XML�ɂ��Ă͎��̌`���ŏo�͂���(a�̓��[�g�m�[�h�Aa_sub�̓��[�t�m�[�h�ł���Ƃ���j
<a content = "" line = "1">
	<leaf name="a_sub" content = "+" line = "1"/>
</a>

@param root �V�����m�[�h��
@param tab_level �^�u���x��(���̐����^�u���}�������j
@return �Ȃ�
*/
void traverseASTwithXML(AST* root,int tab_level){
	int i;
	ASTListIterator p;
	//���[�t�m�[�h�����肷��t���O
	int reaf_flag = 0;

	//���[�t�m�[�h�i�qAST�m�[�h�̐���0��AST�m�[�h�j�̏ꍇ�A*��ǉ��ŏo�͂�����B�������邱�ƂŃ��[�t�m�[�h������������
	if(ASTList_size(root->children) == 0){
		reaf_flag = 1;
	}


	//tab_level���^�u���o�͂�����
	for(i = 0; i < tab_level; i++){
		printf("\t");
	}
	//���[�t�m�[�h�ł���ꍇ
	if(reaf_flag == 1){

		//�^�O�������O�ł����v�f�^�O�ŁA���e�E�s�����o�͂�����
		printf("<leaf name = \"%s\" content = \"%s\" line = \"%d\"/>\n", CSTLString_c_str(root->name), CSTLString_c_str(root->content) ,root->line);

	}else{

		//�^�O�������O�ł���J�n�^�O�ŁA���e�E�s�����o�͂�����
		printf("<%s content = \"%s\" line = \"%d\">\n", CSTLString_c_str(root->name), CSTLString_c_str(root->content) ,root->line);
		//�qAST�m�[�h�ɂ��Ă������`���ŏo�͂�������
		for(p = ASTList_begin(root->children); p != ASTList_end(root->children); p = ASTList_next(p)){
			traverseASTwithXML(ASTList_data(p), tab_level + 1);
		}

		//tab_level���^�u���o�͂�����
		for(i = 0; i < tab_level; i++){
			printf("\t");
		}
		//�^�O�������O�ł���I���^�O���o�͂�����
		printf("</%s>\n", CSTLString_c_str(root->name));
	}

}

/**
�w�肳�ꂽAST�m�[�h�ȉ��̓��e���A�w�肳�ꂽ�t�@�C���ɑ΂��ďo�͂�����
@param output �o�͐�̃t�@�C���\����
@param root �w�肳�ꂽ�m�[�h��
@param line �o�͂ɗ��p����s��

@return �Ȃ�
 */
void fprintDataFromAST(FILE *output, AST *root, int *line){
	ASTListIterator p;

	//���[�t�m�[�h�i�qAST�m�[�h�̐���0��AST�m�[�h�j�̏ꍇ
	if(ASTList_size(root->children) == 0){
		//AST�m�[�h�̍s���ƈ����̍s�������ݍ���Ȃ��Ƃ��A���s���o�͂����A�o�͂���s���𒲐�����
		while(*line < root->line){
			fprintf(output, "\n");
			*line = *line + 1;
		}
		//AST�m�[�h�̓��e���o�͂�����
		fprintf(output, "%s ",CSTLString_c_str(root->content));
	}

	//AST�m�[�h���qAST�m�[�h�̏��������Ă�����A�qAST�m�[�h�ɂ��čċA�I�ɎQ�Ƃ�����
	for(p = ASTList_begin(root->children); p != ASTList_end(root->children); p = ASTList_next(p)){
		fprintDataFromAST(output, ASTList_data(p), line);
	}
}

/**
�w�肵��AST�m�[�h�ȉ��̓��e���o�͂�����BAST�m�[�h�̍s���ɂ��������ďo�͂����B
@param root �V�����m�[�h��
@param line �w�肷��s��(��{�I�ɂP����͂���j
@return �Ȃ�
*/
void printDataFromAST(AST* root, int *line){

	fprintDataFromAST(stdout, root, line);
}

/**
getStringFromAST�̓�������
@param output �o�͑Ώۂ̕�����f�[�^
@param root �V�����m�[�h��
@return �Ȃ�
*/
void getStringFromAST_Internal(CSTLString* output, AST* root){
	ASTListIterator p;
	//���[�t�m�[�h�i�qAST�m�[�h�̐���0��AST�m�[�h�j�̏ꍇ�A���̓��e��output�ɒǉ�������
	if(ASTList_size(root->children) == 0){
		CSTLString_append(output, CSTLString_c_str(root->content));
		CSTLString_append(output, " ");
	}

	//AST�m�[�h���qAST�m�[�h�̏��������Ă�����A�qAST�m�[�h�ɂ��čċA�I�ɎQ�Ƃ�����
	for(p = ASTList_begin(root->children); p != ASTList_end(root->children); p = ASTList_next(p)){
		getStringFromAST_Internal(output, ASTList_data(p));
	}
}

/**
�w�肵��AST�m�[�h�ȉ��̓��e���o�͑Ώۂ̕�����f�[�^�ɏo�͂�����B
@param output �o�͑Ώۂ̕�����f�[�^
@param root �V�����m�[�h��
@return �Ȃ�
*/
void getStringFromAST(CSTLString* output, AST* root){
	getStringFromAST_Internal(output, root);

	//������̖��������p�X�y�[�X�̂Ƃ��A������폜����
	if(CSTLString_size(output) > 0 && *CSTLString_at(output, CSTLString_size(output) - 1) == ' '){
		CSTLString_pop_back(output);
	}
	//�O�ɂ��Ă���󔒕����Ȃǂ��폜����
	CSTLString_ltrim(output);
}

/**
getStringFromASTEnableExcept�̓�������
@param output �o�͑Ώۂ̕�����f�[�^
@param root �V�����m�[�h��
@param num ���O������AST�m�[�h���X�g�̐�
@param except_list ���O������AST�m�[�h
@return �Ȃ�
*/
void getStringFromASTEnableExcept_Internal(CSTLString* output, AST* root, int num, char except_list[][256]){
	ASTListIterator p;
	int i;
	va_list EXCEPT_LIST;
	int except_flag;

	//���[�t�m�[�h�i�qAST�m�[�h�̐���0��AST�m�[�h�j�̏ꍇ�A���̓��e��output�ɒǉ�������
	if(ASTList_size(root->children) == 0){
		CSTLString_append(output, CSTLString_c_str(root->content));
		CSTLString_append(output, " ");
	}

	//AST�m�[�h���qAST�m�[�h�̏��������Ă�����A�qAST�m�[�h�ɂ��čċA�I�ɎQ�Ƃ�����
	for(p = ASTList_begin(root->children); p != ASTList_end(root->children); p = ASTList_next(p)){


		except_flag = 0;
		//���O���X�g��S�ĎQ�Ƃ���
		for(i = 0; i < num; i++){
			//���O���X�g�ƃ}�b�`�����ꍇ�A���O�t���O������
			if(CSTLString_compare_with_char(ASTList_data(p)->name,except_list[i]) == 0){
			 except_flag = 1;
			 break;
			}
		}

		//���O�t���O�������Ă��Ȃ���΁A���̎qAST�m�[�h�͒T���Ώۂɓ���
		if(except_flag == 0){
			getStringFromASTEnableExcept_Internal(output, ASTList_data(p), num, except_list);
		}
	}
}

/**
getStringFromAST�̊g���ŁB�o�͑Ώۂ��珜�O����AST�m�[�h�����w��ł���B
@param output �o�͑Ώۂ̕�����f�[�^
@param root �V�����m�[�h��
@param num ���O������AST�m�[�h���X�g�̐�
@param except_list ���O������AST�m�[�h
@return �Ȃ�
*/
void getStringFromASTEnableExcept(CSTLString* output, AST* root,int num, char except_list[][256]){
	getStringFromASTEnableExcept_Internal(output, root, num, except_list);

	//������̖��������p�X�y�[�X�̂Ƃ��A������폜����
	if(CSTLString_size(output) > 0 && *CSTLString_at(output, CSTLString_size(output) - 1) == ' '){
		CSTLString_pop_back(output);
	}
	//�O�ɂ��Ă���󔒕����Ȃǂ��폜����
	CSTLString_ltrim(output);
}

/**
�w�肵��AST�m�[�h�ȉ���S�ĊJ��������
@param output �o�͑Ώۂ̕�����f�[�^
@return �Ȃ�
*/
void deleteAST_sub(AST* sub_root){
	int i;
	ASTListIterator p;
	//AST�m�[�h���qAST�m�[�h�̏��������Ă�����A�qAST�m�[�h�ɂ��čċA�I�ɎQ�Ƃ�����
	for(p = ASTList_begin(sub_root->children); p != ASTList_end(sub_root->children); p = ASTList_next(p)){
		deleteAST_sub(ASTList_data(p));
	}

	//�qAST�m�[�h�̎Q�Ƃ��I���΁A���̃��X�g���̂��폜������
	ASTList_delete(sub_root->children);

}

/**
�w�肵��AST�m�[�h�ȉ���S�ĊJ��������B
@param root �w�肵��AST�m�[�h
@return �Ȃ�
*/
void deleteAST(AST* root){
	int i;
	//AST�m�[�h���qAST�m�[�h�̏��������Ă�����A�qAST�m�[�h�ɂ��čċA�I�ɎQ�Ƃ�����
	ASTListIterator p;
	for(p = ASTList_begin(root->children); p != ASTList_end(root->children); p = ASTList_next(p)){
		deleteAST_sub(ASTList_data(p));
	}
	//�qAST�m�[�h�̎Q�Ƃ��I���΁A���̃��X�g���̂��폜������
	ASTList_delete(root->children);
	//root�m�[�h���̂��J������
	free(root);

}

/**
�w�肳�ꂽ�eAST�m�[�h�Ɏw�肳�ꂽ�qAST�m�[�h��ǉ�����B
@param parent �w�肳�ꂽ�eAST�m�[�h
@param child �w�肳�ꂽ�qAST�m�[�h
@return �Ȃ�
*/
void push_back_childrenAST(AST *parent, AST *child){

	//�eAST�m�[�h�ɎqAST�m�[�h��ǉ�����
	ASTList_push_back_ref(parent->children, child);
}

/**
�w�肳�ꂽ�eAST�m�[�h�ɔC�ӂ̎qAST�m�[�h��ǉ�����B
@param parent �w�肳�ꂽ�eAST�m�[�h
@param num �ǉ�����qAST�m�[�h�̐�
@param ... �ǉ�����C�ӂ̎qAST�m�[�h
@return �Ȃ�
*/
void multi_push_back_childrenAST(AST *parent,int num, ...){
	va_list AST_list;
	int i;
	//�qAST�m�[�h���X�g���擾
	va_start(AST_list, num);

	//�qAST�m�[�h�̐����Q�Ƃ�����
	for(i = 0; i < num; i++){
		//�eAST�m�[�h�ɎqAST�m�[�h��ǉ�����
		push_back_childrenAST(parent,va_arg(AST_list, AST*));
	}

	//�qAST�m�[�h���X�g���폜������
	va_end(AST_list);
}
/**
�w�肳�ꂽ�eAST�m�[�h����A�w�肵���m�[�h����艺�ʂɂ��Ă̏������ׂĕ\��������B
�܂��Atraverse_flag���P�ɂ��邱�ƂŁA�w�肵���m�[�h���ɂ��Ă̂��ׂĂ̏����c���[�\���ŕ\�������邱�Ƃ��ł���B
����ɁAxml_flag���P�ɂ��邱�ƂŁA�c���[�\���ŕ\����������e��XML�Ƃ��ďo�͂ł���悤�ɂȂ�(traverse_flag���P�ɂȂ��Ă��邱�Ƃ��O��ł���)�B
@param root �w�肳�ꂽ�eAST�m�[�h
@param target �w�肵��������
@param traverse_flag �w�肵���m�[�h���ȉ����c���[�\���ŕ\�������邩�ǂ����̃t���O�B�P�Ȃ�\�������A�O�Ȃ�\�������Ȃ�
@param xml_flag XML�Ƃ��ďo�͂��邩�ǂ����̃t���O�B�P�Ȃ�XML�Ƃ��ďo�͂�����
@return �Ȃ�
*/
void printTargetASTNode(AST *root, char *target, int traverse_flag , int xml_flag){
	int i;
	ASTListIterator p;
	CSTLString *node_content;
	//�w�肵���m�[�h�������������ꍇ
	if(CSTLString_compare_with_char(root->name, target) == 0){
		//�m�[�h���ݒ肷�邽�߂̕�����Ƀm�[�h�̓��e��ݒ肷��
		node_content = CSTLString_new();
		getStringFromAST(node_content, root);
		//�w�肵��AST�m�[�h�̍s���Ƃ��̉��ʂ��܂߂����ׂĂ̏����o�͂�����
		printf("line = \"%d\" , content = \"%s\"\n", root->line, CSTLString_c_str(node_content) );

		//�c���[�\�����\��������t���O���P�ɂȂ��Ă���ꍇ�A�c���[�\�����\��������
		if(traverse_flag == 1){
			printf("\n#AST TREE INFOMATION\n");
			//XML�Ƃ��ďo�͂����邽�߂̃t���O����������AXML�Ƃ��ďo�͂���B
			if(xml_flag == 1){
				traverseASTwithXML(root, 1);
			}else{
				traverseAST(root, 1);
			}
			printf("\n#HERE IS END AST TREE INFOMATION\n");
		}
		//�m�[�h����ݒ肷�邽�߂̕������j������
		CSTLString_delete(node_content);
	}

	//AST�m�[�h���qAST�m�[�h�̏��������Ă�����A�qAST�m�[�h�ɂ��čċA�I�ɎQ�Ƃ�����
	for(p = ASTList_begin(root->children); p != ASTList_end(root->children); p = ASTList_next(p)){
		printTargetASTNode(ASTList_data(p), target, traverse_flag, xml_flag);
	}
}
/**
getArgumentString�̓�������
@param output �o�͂��������̓��e
@param call_function ���O��call_function�ł���AST�m�[�h
@param arg_num ���Ԗڂ̈���

@return �����������ǂ����������B���������Ȃ�΂P�A���s�����ꍇ�͂O��Ԃ��B
*/
int getArgumentString_Internal(CSTLString *output, AST* argument, int *arg_num){
	ASTListIterator p;
	//�����������ǂ����̃t���O
	int success_flag = 0;
	//�����A�����̓��e������t_argument_expression�������ꍇ
	if(CSTLString_compare_with_char(argument->name, "t_argument_expression") == 0){
		//�����������ϐ������炵�A0�ɂȂ�΂��̈����̓��e��output�ɐݒ肷��
		*arg_num = *arg_num - 1;
		if(*arg_num == 0){
			//success_flag���P�ɂ���
			success_flag = 1;
			getStringFromAST(output, argument);
		}
	}
	//AST�m�[�h���qAST�m�[�h�̏��������Ă�����A�qAST�m�[�h�ɂ��čċA�I�ɎQ�Ƃ�����Bsuccess_flag���P�ɂȂ�����I��������B
	for(p = ASTList_begin(argument->children); success_flag == 0 && p != ASTList_end(argument->children); p = ASTList_next(p)){
		success_flag = getArgumentString_Internal(output, ASTList_data(p), arg_num);
	}

	return success_flag;
}

/**
�w�肳�ꂽcall_function�ɑ�������֐�����A�C�ӂ̈����ڂ̏����擾����B
���̂Ƃ��A�w�肳�ꂽ�m�[�h����call_function�łȂ���΂Ȃ�Ȃ��B
@param output �o�͂��������̓��e
@param call_function ���O��call_function�ł���AST�m�[�h
@param arg_num ���Ԗڂ̈���
@return �����������ǂ����������B���������Ȃ�΂P�A���s�����ꍇ�͂O��Ԃ��B
*/
int getArgumentString(CSTLString *output, AST* call_function, int arg_num){

	int success_flag;
	if(CSTLString_compare_with_char(call_function->name, "call_function") == 0){
		int *p_arg_num = &arg_num;
		success_flag = getArgumentString_Internal(output, call_function, p_arg_num);
	}else{
		success_flag = 0;
	}
	return success_flag;
}

/**
getArgumentStringEnableExcept�̓�������
@param output �o�͂��������̓��e
@param call_function ���O��call_function�ł���AST�m�[�h
@param arg_num ���Ԗڂ̈���
@param num ���O������AST�m�[�h���X�g�̐�
@param except_list ���O������AST�m�[�h

@return �����������ǂ����������B���������Ȃ�΂P�A���s�����ꍇ�͂O��Ԃ��B
*/
int getArgumentStringEnableExcept_Internal(CSTLString *output, AST* argument, int *arg_num, int num, char except_list[][256]){
	ASTListIterator p;
	//�����������ǂ����̃t���O
	int success_flag = 0;
	//�����A�����̓��e������t_argument_expression�������ꍇ
	if(CSTLString_compare_with_char(argument->name, "t_argument_expression") == 0){
		//�����������ϐ������炵�A0�ɂȂ�΂��̈����̓��e��output�ɐݒ肷��
		*arg_num = *arg_num - 1;
		if(*arg_num == 0){
			//success_flag���P�ɂ���
			success_flag = 1;
			getStringFromASTEnableExcept(output, argument, num, except_list);
		}
	}
	//AST�m�[�h���qAST�m�[�h�̏��������Ă�����A�qAST�m�[�h�ɂ��čċA�I�ɎQ�Ƃ�����Bsuccess_flag���P�ɂȂ�����I��������B
	for(p = ASTList_begin(argument->children); success_flag == 0 && p != ASTList_end(argument->children); p = ASTList_next(p)){
		success_flag = getArgumentStringEnableExcept_Internal(output, ASTList_data(p), arg_num, num, except_list);
	}

	return success_flag;
}
/**
getArgumentEnableExcept�̊g���ŁB�o�͑Ώۂɂ��Ȃ�������������������̏������ׂďo�͂�����B
@param output �o�͂��������̓��e
@param call_function ���O��call_function�ł���AST�m�[�h
@param arg_num ���Ԗڂ̈���
@param num ���O������AST�m�[�h���X�g�̐�
@param except_list ���O������AST�m�[�h

@return �����������ǂ����������B���������Ȃ�΂P�A���s�����ꍇ�͂O��Ԃ��B
*/
int getArgumentStringEnableExcept(CSTLString *output, AST* call_function, int arg_num, int num, char except_list[][256]){
	int success_flag;
	if(CSTLString_compare_with_char(call_function->name, "call_function") == 0){
		int *p_arg_num = &arg_num;
		success_flag = getArgumentStringEnableExcept_Internal(output, call_function, p_arg_num, num, except_list);
	}else{
		success_flag = 0;
	}
	return success_flag;
}

/**
getArgumentAST�̓�������
@param output �擾����Ώۂ̃m�[�h
@param call_function ���O��call_function�ł���AST�m�[�h
@param arg_num ���Ԗڂ̈���

@return �����������ǂ����������B���������Ȃ�΂P�A���s�����ꍇ�͂O��Ԃ��B
*/
int getArgumentAST_Internal(AST **output, AST* argument, int *arg_num){
	ASTListIterator p;
	//�����������ǂ����̃t���O
	int success_flag = 0;
	//�����A�����̓��e������t_argument_expression�������ꍇ
	if(CSTLString_compare_with_char(argument->name, "t_argument_expression") == 0){
		//�����������ϐ������炵�A0�ɂȂ�΂��̈����̓��e��output�ɐݒ肷��
		*arg_num = *arg_num - 1;
		if(*arg_num == 0){
			//success_flag���P�ɂ���
			success_flag = 1;
			*output = argument;
		}
	}
	//AST�m�[�h���qAST�m�[�h�̏��������Ă�����A�qAST�m�[�h�ɂ��čċA�I�ɎQ�Ƃ�����Bsuccess_flag���P�ɂȂ�����I��������B
	for(p = ASTList_begin(argument->children); success_flag == 0 && p != ASTList_end(argument->children); p = ASTList_next(p)){
		success_flag = getArgumentAST_Internal(output, ASTList_data(p), arg_num);
	}

	return success_flag;
}

/**
�w�肳�ꂽcall_function�ɑ�������֐�����A�C�ӂ̈����ڂւ̃m�[�h���擾����B
���̂Ƃ��A�w�肳�ꂽ�m�[�h����call_function�łȂ���΂Ȃ�Ȃ��B
@param output �擾����Ώۂ̃m�[�h
@param call_function ���O��call_function�ł���AST�m�[�h
@param arg_num ���Ԗڂ̈���

@return �����������ǂ����������B���������Ȃ�΂P�A���s�����ꍇ�͂O��Ԃ��B
*/
int getArgumentAST(AST **output, AST* call_function, int arg_num){
	int success_flag;
	if(CSTLString_compare_with_char(call_function->name, "call_function") == 0){
		int *p_arg_num = &arg_num;
		success_flag = getArgumentAST_Internal(output, call_function, p_arg_num);
	}else{
		success_flag = 0;
	}
	return success_flag;

}

/**
�w�肵��AST�m�[�hroot����A�w�肵�����Oname��AST�m�[�h��T���B
������AST�m�[�h�ւ̃A�h���X��Ԃ��B
@param root �w�肵��AST�m�[�h
@param name �w�肵�����O
@param depth �T������q�m�[�h�̐[���i�����ɂ���ꍇ��-1���w��A�q�m�[�h�͌������Ȃ��ꍇ��0�ɂ���)
@return ������AST�m�[�h�ւ̃A�h���X��Ԃ��B
*/
AST *getASTwithString(AST *root, char *name, int depth){
	//�qAST�m�[�h�����ǂ�C�e���[�^
	ASTListIterator p;
	//�o�͂�����AST�m�[�h
	AST *output = NULL;
	if(depth < -1){
		fprintf(stderr, "�[��������`�ł��B\n");
		exit(1);
	}
	//�w�肵�����O��AST�m�[�h���������炻�̎��_�ŕԂ��B
	if(CSTLString_compare_with_char(root->name, name) == 0){
		output = root;
	}
	else{
		//depth��0�ɂȂ�܂ŌJ��Ԃ�
		if(depth > 0){
			//AST�m�[�h���qAST�m�[�h�̏��������Ă�����A�qAST�m�[�h�ɂ��čċA�I�ɎQ�Ƃ�����Bsuccess_flag���P�ɂȂ�����I��������B
			for(p = ASTList_begin(root->children); output == NULL && p != ASTList_end(root->children); p = ASTList_next(p)){
				output = getASTwithString(ASTList_data(p), name, depth - 1);
			}
		}
		//depth��-1�ł���΁A�K���q�m�[�h���Q�Ƃ���
		else if(depth == -1){
			//AST�m�[�h���qAST�m�[�h�̏��������Ă�����A�qAST�m�[�h�ɂ��čċA�I�ɎQ�Ƃ�����Bsuccess_flag���P�ɂȂ�����I��������B
			for(p = ASTList_begin(root->children); output == NULL && p != ASTList_end(root->children); p = ASTList_next(p)){
				output = getASTwithString(ASTList_data(p), name, depth);
			}
		}
	}

	return output;

}

/**
getStringReplaceASTtoString�̓��������B

@param root �w�肵��AST�m�[�h
@param output �o�͂�����
@param target �ϊ��Ώۂ�AST�m�[�h�̃A�h���X
@param replace_string �ϊ���̕�����

@return �Ȃ�
*/
void getStringReplaceASTtoString_Internal(CSTLString *output, AST *root, AST *target, char *replace_string){
	ASTListIterator p;
	//���[�t�m�[�h�i�qAST�m�[�h�̐���0��AST�m�[�h�j�̏ꍇ�A���̓��e��output�ɒǉ�������
	if(root == target){
		CSTLString_append(output, replace_string);
		CSTLString_append(output, " ");
	}else if(ASTList_size(root->children) == 0){
		CSTLString_append(output, CSTLString_c_str(root->content));
		CSTLString_append(output, " ");
	}else{
		//AST�m�[�h���qAST�m�[�h�̏��������Ă�����A�qAST�m�[�h�ɂ��čċA�I�ɎQ�Ƃ�����
		for(p = ASTList_begin(root->children); p != ASTList_end(root->children); p = ASTList_next(p)){
			getStringReplaceASTtoString_Internal(output, ASTList_data(p), target, replace_string);
		}
	}
}

/**
�w�肵��AST�m�[�hroot�ɑ΂��Ă̏��𕶎���output���o�͂�����B
���̂Ƃ��AAST�m�[�h��target�̃A�h���X�l�ƈ�v����m�[�h���������i�A�h���X�Ƃ��đS������AST�m�[�h���������j
�ꍇ�A���̃m�[�h����replace_string�ɕϊ����ďo�͂�����B

@param root �w�肵��AST�m�[�h
@param output �o�͂�����
@param target �ϊ��Ώۂ�AST�m�[�h�̃A�h���X
@param replace_string �ϊ���̕�����

@return �Ȃ�
*/
void getStringReplaceASTtoString(CSTLString *output, AST *root, AST *target, char *replace_string){
	getStringReplaceASTtoString_Internal(output, root, target, replace_string);

	//������̖��������p�X�y�[�X�̂Ƃ��A������폜����
	if(CSTLString_size(output) > 0 && *CSTLString_at(output, CSTLString_size(output) - 1) == ' '){
		CSTLString_pop_back(output);
	}
}

/**
setASTReturnType�̓��������B�����ł́A�^�C�v��t�����Ă����B

@param root �Ώۂ�AST�m�[�h
@param type �t������ԋp�l�̃^�C�v

@return �Ȃ�
*/
void setASTReturnType_Internal(AST *root, CSTLString *type){
	ASTListIterator ast_i;

	//�ԋp�l�̃^�C�v��t������B
	CSTLString_printf(root->return_type, 0, "%s", CSTLString_c_str(type));

	//�q�m�[�h�ɂ������悤�ȏ�����K������
	for(ast_i = ASTList_begin(root->children);
		ast_i != ASTList_end(root->children);
		ast_i = ASTList_next(ast_i)){
			setASTReturnType_Internal(ASTList_data(ast_i), type);
	}
}

/**
�Ώۂ�AST�m�[�h��root�ȉ��ɂ���ɁA�֐��̕ԋp�l�̃^�C�v���w�肷��B

@param root �Ώۂ�AST�m�[�h

@return �Ȃ�
*/
void setASTReturnType(AST *root){
	ASTListIterator ast_i;
	//�֐���`���������ꍇ
	if(CSTLString_compare_with_char(root->name, "function_definition") == 0){
		//�ݒ肷��ԋp�̌^
		CSTLString *return_type = CSTLString_new();

		//�q�m�[�h����ԋp�l���擾
		for(ast_i = ASTList_begin(root->children);
			ast_i != ASTList_end(root->children);
			ast_i = ASTList_next(ast_i)){
				//�^���Ƃ��đ����閼�O���݂�����ԋp�̌^���擾����B
				if(CSTLString_compare_with_char(ASTList_data(ast_i)->name, "declaration_specifiers") == 0 ||
				CSTLString_compare_with_char(ASTList_data(ast_i)->name, "storage_class_specifier") == 0 ||
				CSTLString_compare_with_char(ASTList_data(ast_i)->name, "type_specifier") == 0 ||
				CSTLString_compare_with_char(ASTList_data(ast_i)->name, "type_qualifier") == 0 ||
				CSTLString_compare_with_char(ASTList_data(ast_i)->name, "function_specifier") == 0){
					getStringFromAST(return_type, ASTList_data(ast_i));
					break;
				}
		}

		//�֐���`�ȉ��̎q�m�[�h�ɂ��Ă͑S�ĕԋp�̌^��t��������B
		for(ast_i = ASTList_begin(root->children);
			ast_i != ASTList_end(root->children);
			ast_i = ASTList_next(ast_i)){
				//declaration_specifiers����A�ԋp�̌^���擾����B
				setASTReturnType_Internal(ASTList_data(ast_i), return_type);
		}

		CSTLString_delete(return_type);

	}
	//�����łȂ�������A�q�m�[�h���T������
	else{


		for(ast_i = ASTList_begin(root->children);
			ast_i != ASTList_end(root->children);
			ast_i = ASTList_next(ast_i)){
				setASTReturnType(ASTList_data(ast_i));
		}
	}
}
/**
setASTBlocklevelAndId�̓��������ł���B

@param root �Ώۂ�AST�m�[�h

@return �Ȃ�
*/
void setASTBlocklevelAndId_Internal(AST *root, STACK_INT *block_ids, int *block_level){
	ASTListIterator ast_i;

	int block_id;

	//"{"��������A�u���b�N���x�����グ��
	if(CSTLString_compare_with_char(root->name, "{") == 0){
		*block_level = *block_level + 1;
		STACK_INT_at_and_alloc(block_ids, *block_level - 1);
	}
	//"}"��������A���̓����x���u���b�N�̂��߂ɁA��قǂ̃u���b�N���x���ɑ΂���ID���C���N�������g���������ŁA�u���b�N���x����������
	else if(CSTLString_compare_with_char(root->name,"}") == 0){
		STACK_INT_inclement_at(block_ids, *block_level - 1);
		*block_level = *block_level - 1;
	}

	//�u���b�N���x����0�𒴂���ꍇ��block_ids����u���b�NID���擾����
	if(*block_level > 0){
		block_id = STACK_INT_at_and_alloc(block_ids, *block_level - 1);
	}
	//0�ł���ꍇ�̓u���b�NID��0�ɂ���
	else{
		block_id = 0;
	}

	//�w�肵��AST�m�[�h�Ƀu���b�N���x���ƃu���b�NID��IDLIST��t������
	root->block_level = *block_level;
	root->block_id = block_id;
	SET_STACK_INTToIDLIST(root->idlist, block_ids, *block_level);

	for(ast_i = ASTList_begin(root->children);
		ast_i != ASTList_end(root->children);
		ast_i = ASTList_next(ast_i)){

			setASTBlocklevelAndId_Internal(ASTList_data(ast_i), block_ids, block_level);
	}
}

/**
�Ώۂ�AST�m�[�h�ɁA�u���b�NID����уu���b�N���x����t������B

@param root �Ώۂ�AST�m�[�h


@return �Ȃ�
*/
void setASTBlocklevelAndId(AST *root){
	STACK_INT *block_ids = STACK_INT_new();
	int block_level = 0;
	setASTBlocklevelAndId_Internal(root, block_ids, &block_level);
}

/**
�T���Ώۂ�AST�m�[�hroot����A�w�肵��AST�m�[�h�̃A�h���Xtarget�����݂��邩�ǂ������ׂ�B�݂���΁A�P��Ԃ��A�����łȂ���΂O��Ԃ��B

@param root �T���Ώۂ�AST�m�[�h
@param target �w�肵��AST�m�[�h�̃A�h���X

@return �w�肵��AST�m�[�htarget����������P��Ԃ��A�����łȂ���΂O��Ԃ��B
*/
int findASTAddress(AST *root, AST *target){
	int find_flag = 0;

	ASTListIterator ast_i;

	//�����Atarget��������ꂽ��A�P��Ԃ��B
	if(root == target){
		find_flag = 1;
	}
	//�����łȂ���΁A�q�m�[�h���T���A�q�m�[�h���猩���邱�Ƃ��o������I������
	else{
		for(ast_i = ASTList_begin(root->children);
			find_flag == 0 && ast_i != ASTList_end(root->children);
			ast_i = ASTList_next(ast_i)){

				find_flag = findASTAddress(ASTList_data(ast_i), target);
		}
	}

	return find_flag;
}


/**
�w�肳�ꂽ�m�[�h�ɑ΂��āAstatement�̒��O�܂ŏo�͂�����B�܂��A�o�͑ΏۂƂȂ��Ă���m�[�h�ԍ�������܂ł͏o�͂̑ΏۂƂ��Ȃ��B
�u���b�N�Ƃ��ĕ\�L����Ă���ꍇ�͎n�܂�̃u���b�N��I���̃u���b�N�ւ�AST�m�[�h�̃A�h���X��out_block_start��out_block_end��
�ݒ肷��B�����łȂ���΁ANULL�Őݒ肳���B

@param output �o�͐�̃t�@�C���\����
@param root �w�肳�ꂽAST�m�[�h
@param line �o�͂ɗ��p����s��
@param output_subnode_num �o�͑ΏۂƂȂ�m�[�h�ԍ� �P�`���i�P�Ɏw�肷��ƁA���ׂĂ̎q�m�[�h���o�͂̑ΏۂƂȂ�j
@param out_block_start �u���b�N�Ƃ��ĕ\�L����Ă���ꍇ�́A�n�܂�̃u���b�N�ւ�AST�m�[�h�̃A�h���X��ԋp����
@param out_block_end �u���b�N�Ƃ��ĕ\�L����Ă���ꍇ�́A�I���u�̃��b�N�ւ�AST�m�[�h�̃A�h���X��ԋp����B
@return �Ȃ�
 */

void fprintfStatement(FILE *output, AST *root, int *line, int output_subnode_num, AST **out_block_start, AST **out_block_end){

	ASTListIterator ast_i;

	*out_block_start = NULL;
	*out_block_end = NULL;

	int counter;

	//�Ώۂ�AST�m�[�h�̎q�m�[�h��T������
	for(counter = 1, ast_i = ASTList_begin(root->children);
		ast_i != ASTList_end(root->children);
		counter++, ast_i = ASTList_next(ast_i)){
		//�w�肳�ꂽ�o�͑ΏۂƂȂ�m�[�h�ԍ��𒴂����ꍇ�A�o�͑ΏۂƂ���
		if(counter >= output_subnode_num){
			//statement���������ꍇ
			if(CSTLString_compare_with_char(ASTList_data(ast_i)->name, "statement") == 0){

				//�u���b�N�Ƃ��ĕ\�L����Ă���ꍇ�A�n�܂�ƏI���u���b�N�ւ�AST�m�[�h�̃A�h���X���擾����
				if(CSTLString_compare_with_char(ASTLIST_ITERATOR_1(ASTList_data(ast_i))->name, "compound_statement_a") == 0){
					*out_block_start = ASTLIST_ITERATOR_1(ASTLIST_ITERATOR_1(ASTList_data(ast_i)));
					*out_block_end = ASTLIST_ITERATOR_2(ASTLIST_ITERATOR_1(ASTList_data(ast_i)));
					fprintDataFromAST(output, ASTLIST_ITERATOR_1(ASTLIST_ITERATOR_1(ASTList_data(ast_i))), line);
				}
				else if(CSTLString_compare_with_char(ASTLIST_ITERATOR_1(ASTList_data(ast_i))->name, "compound_statement_b") == 0){
					*out_block_start = ASTLIST_ITERATOR_1(ASTLIST_ITERATOR_1(ASTList_data(ast_i)));
					*out_block_end = ASTLIST_ITERATOR_3(ASTLIST_ITERATOR_1(ASTList_data(ast_i)));
					fprintDataFromAST(output, ASTLIST_ITERATOR_1(ASTLIST_ITERATOR_1(ASTList_data(ast_i))), line);
				}

				break;

			}
			//compound_statement_a���������ꍇ
			else if(CSTLString_compare_with_char(ASTList_data(ast_i)->name, "compound_statement_a") == 0){
				*out_block_start = ASTLIST_ITERATOR_1(ASTList_data(ast_i));
				*out_block_end = ASTLIST_ITERATOR_2(ASTList_data(ast_i));
				fprintDataFromAST(output, ASTLIST_ITERATOR_1(ASTList_data(ast_i)), line);
			}
			//compound_statement_b���������ꍇ
			else if(CSTLString_compare_with_char(ASTList_data(ast_i)->name, "compound_statement_b") == 0){
				*out_block_start = ASTLIST_ITERATOR_1(ASTList_data(ast_i));
				*out_block_end = ASTLIST_ITERATOR_3(ASTList_data(ast_i));
				fprintDataFromAST(output, ASTLIST_ITERATOR_1(ASTList_data(ast_i)), line);
			}else{

				//�q�m�[�h�ȉ��̓��e���A�s���ɉ����ďo�͂�����
				fprintDataFromAST(output, ASTList_data(ast_i), line);

			}
		}

	}

}
