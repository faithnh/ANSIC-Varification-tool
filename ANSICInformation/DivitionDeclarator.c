
#include"DivitionDeclarator.h"
#include"../Library/CSTLString.h"

#include<stdio.h>
#include<stdlib.h>
/**
OutputSourceAfterDivitionDeclarator�̓��������ł���
@param output �o�͐�̃t�@�C���\����
@param programAST �v���O�����ɑ΂���AST
@param variable_table_list �ϐ��e�[�u��
@param line �������̍s��

@return �Ȃ�
 */
void OutputSourceAfterDivitionDeclarator_Internal(FILE *output, AST *programAST, VARIABLE_TABLE_LIST *variable_table_list, int *line){

	ASTListIterator p;

	VARIABLE_TABLE_LISTIterator vi_list_i;

	//�ϐ��e�[�u���ɂ����`�������������ǂ����̃t���O
	int find_flag;

	//decralation_with_init���������ꍇ
	if(CSTLString_compare_with_char(programAST->name, "declaration_with_init") == 0){
		//�ϐ��e�[�u���ɂ����`���������Ă��Ȃ���Ԃɂ��Ă���
		find_flag = 0;

		for(vi_list_i = VARIABLE_TABLE_LIST_begin(variable_table_list);
			vi_list_i != VARIABLE_TABLE_LIST_end(variable_table_list);
			vi_list_i = VARIABLE_TABLE_LIST_next(vi_list_i)){

				//�����A�ϐ��e�[�u�����X�g�ɂ��鏉����`���ƈ�v�����ꍇ
				if(VARIABLE_TABLE_LIST_data(vi_list_i)->declaration_location_address == programAST){

					//�ϐ��e�[�u���ɂ����`������������Ԃɂ��Ă���
					find_flag = 1;

					//AST�m�[�h�̍s���ƈ����̍s�������ݍ���Ȃ��Ƃ��A���s���o�͂����A�o�͂���s���𒲐�����
					while(*line < programAST->line){
						fprintf(output, "\n");
						*line = *line + 1;
					}

					//������`�������݂���ꍇ
					if(VARIABLE_TABLE_LIST_data(vi_list_i)->initiarizer != NULL){
						//������`�����擾����
						CSTLString *init_expr = CSTLString_new();
						getStringFromAST(init_expr, VARIABLE_TABLE_LIST_data(vi_list_i)->initiarizer);

						//�u�^�� �ϐ��� = ������`��;�v�Ƃ����`�ŏo�͂���
						fprintf(output, "%s %s = %s ; ",CSTLString_c_str(VARIABLE_TABLE_LIST_data(vi_list_i)->type),
								CSTLString_c_str(VARIABLE_TABLE_LIST_data(vi_list_i)->variable_name),
								CSTLString_c_str(init_expr));
						CSTLString_delete(init_expr);
					}else{
						//�u�^�� �ϐ���;�v�Ƃ����`�ŏo�͂���
						fprintf(output, "%s %s ; ",CSTLString_c_str(VARIABLE_TABLE_LIST_data(vi_list_i)->type),
								CSTLString_c_str(VARIABLE_TABLE_LIST_data(vi_list_i)->variable_name));
					}

				}
		}

		//�ϐ��e�[�u���ɂ����`���������Ă��Ȃ���Ԃł���ꍇ�́A�q�m�[�h��T�����Ă���
		if(find_flag == 0){
			for(p = ASTList_begin(programAST->children); p != ASTList_end(programAST->children); p = ASTList_next(p)){
				OutputSourceAfterDivitionDeclarator_Internal(output, ASTList_data(p), variable_table_list, line);
			}
		}
	}
	//���[�t�m�[�h�i�qAST�m�[�h�̐���0��AST�m�[�h�j�̏ꍇ
	else if(ASTList_size(programAST->children) == 0){
		//AST�m�[�h�̍s���ƈ����̍s�������ݍ���Ȃ��Ƃ��A���s���o�͂����A�o�͂���s���𒲐�����
		while(*line < programAST->line){
			fprintf(output, "\n");
			*line = *line + 1;
		}
		//AST�m�[�h�̓��e���o�͂�����
		fprintf(output, "%s ",CSTLString_c_str(programAST->content));
	}
	else{
		//AST�m�[�h���qAST�m�[�h�̏��������Ă�����A�qAST�m�[�h�ɂ��čċA�I�ɎQ�Ƃ�����
		for(p = ASTList_begin(programAST->children); p != ASTList_end(programAST->children); p = ASTList_next(p)){
			OutputSourceAfterDivitionDeclarator_Internal(output, ASTList_data(p), variable_table_list, line);
		}
	}
}

/**
�ϐ���`�𕪊���������Ԃŏo�͂�����B
�@��Fint a,b = 1; �� int a; int b = 1;
@param output �o�͐�̃t�@�C���\����
@param programAST �v���O�����ɑ΂���AST
@param variable_table_list �ϐ��e�[�u��

@return �Ȃ�
 */
void OutputSourceAfterDivitionDeclarator(FILE *output, AST *programAST, VARIABLE_TABLE_LIST *variable_table_list){

	int line = 1;

	OutputSourceAfterDivitionDeclarator_Internal(output,programAST,variable_table_list,&line);
}
