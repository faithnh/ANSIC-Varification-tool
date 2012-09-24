#include "WriteVelificationStatement.h"
#include "xmlWriter/XmlWriter.h"
#include <stdio.h>
#include<limits.h>

//���Z����]�Z���ǂ����̃t���O
#define TYPE_DIV 0
#define TYPE_MOD 1
/*
 * WriteVelificationStatement.c
 *
 *  Created on: 2012/06/11
 *      Author: fken-2
 */

/*�z��͈͊O�Q�ƂƖ���`�����̌��؎��̐���*/
void writeArrayCheck(CSTLString *output, ARRAY_OFFSET_LISTIterator aoff_list_i, int undefined_control_check, int array_unbound_check){
	int array_offset_level;

	int offset_level_counter;

	OFFSET_LISTIterator off_list_i;
	//�I�t�Z�b�g���x���̎擾
	array_offset_level = OFFSET_LIST_size(ARRAY_OFFSET_LIST_data(aoff_list_i)->offset_list);

	//�I�t�Z�b�g���x����0�𒴂���ꍇ�i���Ȃ킿�A�I�t�Z�b�g��񂪑��݂���ꍇ�j
	if(array_offset_level > 0){

	//�z��̌`��ێ�������i�������Ŏg�p�����j
		CSTLString *array_string = CSTLString_new();
		CSTLString *basis_location_content = CSTLString_new();
		CSTLString_assign(array_string, "");
		CSTLString_assign(basis_location_content, "");

		//�I�t�Z�b�g�����Q�Ƃ���
		for(offset_level_counter = 1, off_list_i = OFFSET_LIST_begin(ARRAY_OFFSET_LIST_data(aoff_list_i)->offset_list);
			off_list_i != OFFSET_LIST_end(ARRAY_OFFSET_LIST_data(aoff_list_i)->offset_list);
			offset_level_counter++, off_list_i = OFFSET_LIST_next(off_list_i)){
				int is_expression_flag = isExpression(*OFFSET_LIST_data(off_list_i));
				CSTLString *statement = CSTLString_new();

				//����`�����`�F�b�N�t���O�����藧���Ă���ꍇ�A
				//���x�����Ƃ̖���`�����̌��؎��𐶐�����B����`�����̌��؎��̌`���͈ȉ��̒ʂ�ł���B
				//if(defined_�K�w_�ϐ��� == 0 && max_size_�K�w_�ϐ��� == 0){
				//	printf("#�t�@�C����#:�s��: detected undefine pointer access in variable �ϐ���);
				//	assert(0);
				//	���^�[����;
				//}
				if(undefined_control_check){

					CSTLString_printf(statement,0,"if(*defined_%d_%s%s == 0 && *malloc_flag_%d_%s%s == 0){\n",
								 offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string),
								 offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string)
							);

					CSTLString_printf(statement,1,"printf(\"#%s#:%d: detected undefine pointer access in variable %s\");\n ",getFileName(), ARRAY_OFFSET_LIST_data(aoff_list_i)->target_statement->line, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name));

					CSTLString_printf(statement, 1, "assert(0);\n");

					//���^�[�����߂̕ԋp�^�ɉ�����ύX(�����Avoid�^�ł���΁A�ureturn;�v�ɂ���)
					if(CSTLString_compare_with_char(ARRAY_OFFSET_LIST_data(aoff_list_i)->target_statement->return_type, "void") == 0){
						CSTLString_printf(statement, 1, "return;\n");
					}else{
						CSTLString_printf(statement, 1, "return 1;\n");
					}

					CSTLString_printf(statement, 1, "}\n");

				}

				//�z��͈͊O�`�F�b�N�t���O�����藧���Ă����ꍇ�A
				//���x�����Ƃ̔z��͈͊O�Q�Ƃ̌��؎��𐶐�����B�z��͈͊O�Q�Ƃ̎��̌`���͈ȉ��̒ʂ�ł���
				//if(0 > �� + ��{�ʒu || �� + ��{�ʒu < �Ώەϐ��̔z��){
				//	printf("#�t�@�C����#:�s��: detected unbound access in variable �ϐ��� basis_location = %d �� = %d\n", basis_location, ��);
				//	assert(0);
				//	���^�[����;
				//}
				if(array_unbound_check){
					CSTLString_printf(statement,1,"if(0 > %s + basis_location_%d_%s%s){\n",
								 *OFFSET_LIST_data(off_list_i), offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string));
					/*
					CSTLString_printf(statement,1,"printf(\"#%s#:%d:detected unbound access in variable %s ",getFileName(), ARRAY_OFFSET_LIST_data(aoff_list_i)->target_statement->line, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name));

					//basis_location�̓��e���o�͂���
					CSTLString_printf(statement,1," basis_location = %%d ");

					//�����A�I�t�Z�b�g�̓��e�����ł���΁A�����l�Ƃ����`�ŏo�͂���
					if(is_expression_flag == 1){
						CSTLString_printf(statement,1,"(%s = %%d)\\n\"", *OFFSET_LIST_data(off_list_i));
						//basis_location�̓��e���܂߂������̓��e������
						CSTLString_printf(statement,1,", basis_location_%d_%s%s, %s",offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string) , *OFFSET_LIST_data(off_list_i));
					}

					//�����łȂ���΁A�l�Ƃ����`�ŏo�͂���
					else{
						CSTLString_printf(statement,1,"(%s)\\n\"", *OFFSET_LIST_data(off_list_i));
						//basis_location�̓��e�̈����̓��e������
						CSTLString_printf(statement,1,", basis_location_%d_%s%s", offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string));
					}
					CSTLString_printf(statement, 1, ");\n");
					*/
					//�G���[�̂w�l�k���o��
					CSTLString_printf(statement,1,"printf(\"<error type = #dquot#Lower Unbound#dquot# variable=#dquot#%s#dquot#>\");\n",(char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name));
					if(is_expression_flag == 1){
						CSTLString_printf(statement,1,"printf(\"<expression text=#dquot#%s#dquot# value=#dquot#%%d#dquot#></expression>\",%s);\n", *OFFSET_LIST_data(off_list_i), *OFFSET_LIST_data(off_list_i));
					}else{
						CSTLString_printf(statement,1,"printf(\"<expression value=#dquot#%%d#dquot#></expression>\",%s);\n",*OFFSET_LIST_data(off_list_i));
					}
					CSTLString_printf(statement,1,"printf(\"<basic_location value=#dquot#%%d#dquot#></basic_location>\", basis_location_%d_%s%s);\n", offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string));
					CSTLString_printf(statement,1,"printf(\"</error>\");\n");
					CSTLString_printf(statement,1,"printf(\"</source>\");\n");

					CSTLString_printf(statement, 1, "assert(0);\n");

					//���^�[�����߂̕ԋp�^�ɉ�����ύX(�����Avoid�^�ł���΁A�ureturn;�v�ɂ���)
					if(CSTLString_compare_with_char(ARRAY_OFFSET_LIST_data(aoff_list_i)->target_statement->return_type, "void") == 0){
						CSTLString_printf(statement, 1, "return;\n");
					}else{
						CSTLString_printf(statement, 1, "return 1;\n");
					}

					CSTLString_printf(statement, 1, "}\n");
					CSTLString_printf(statement, 1, "if(%s + basis_location_%d_%s%s >= *max_size_%d_%s%s){",
							*OFFSET_LIST_data(off_list_i), offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string),
							offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string));
					//�G���[�̂w�l�k���o��
					outputErrorXml(statement, aoff_list_i, off_list_i, offset_level_counter, array_string);
/*					CSTLString_printf(statement,1,"printf(\"<error type = #dquot#Upper Unbound#dquot# variable=#dquot#%s#dquot#>\");\n",(char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name));
					if(is_expression_flag == 1){
						CSTLString_printf(statement,1,"printf(\"<expression text=#dquot#%s#dquot# value=#dquot#%%d#dquot#></expression>\",%s);\n", *OFFSET_LIST_data(off_list_i), *OFFSET_LIST_data(off_list_i));
					}else{
						CSTLString_printf(statement,1,"printf(\"<expression value=#dquot#%%d#dquot#></expression>\",%s);\n",*OFFSET_LIST_data(off_list_i));
					}
					CSTLString_printf(statement,1,"printf(\"<basic_location value=#dquot#%%d#dquot#></basic_location>\", basis_location_%d_%s%s);\n", offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string));
					CSTLString_printf(statement,1,"printf(\"</error>\");\n");
					CSTLString_printf(statement,1,"printf(\"</source>\");\n");*/

					CSTLString_printf(statement, 1, "assert(0);\n");

					//���^�[�����߂̕ԋp�^�ɉ�����ύX(�����Avoid�^�ł���΁A�ureturn;�v�ɂ���)
					if(CSTLString_compare_with_char(ARRAY_OFFSET_LIST_data(aoff_list_i)->target_statement->return_type, "void") == 0){
						CSTLString_printf(statement, 1, "return;\n");
					}else{
						CSTLString_printf(statement, 1, "return 1;\n");
					}

					CSTLString_printf(statement, 1, "}\n");
				}
				CSTLString_printf(output, 1, "%s", (char*)CSTLString_c_str(statement));

				//���̃��x���̂��߂̔z��𐶐�����B
				CSTLString_printf(basis_location_content, 0, "basis_location_%d_%s%s", offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string));
				CSTLString_printf(array_string, 1," [ %s + %s ]", *OFFSET_LIST_data(off_list_i), (char*)CSTLString_c_str(basis_location_content));
				CSTLString_delete(statement);
		}

		CSTLString_delete(array_string);
		CSTLString_delete(basis_location_content);

	}

}

void writeZeroCheck(CSTLString *statement, DIVITION_INFORMATION_LISTIterator di_i){
	ARRAY_OFFSET_LISTIterator aoff_list_i;
	//���Ɋւ���CSTL������𐶐�
	CSTLString *identifires_list = CSTLString_new();
	CSTLString *parameter_list = CSTLString_new();
	CSTLString *output = CSTLString_new();
	//���̂悤�Ȏ��𐶐�����
	//if( (��) == 0 ){ printf("#�t�@�C����#:�s��:detected zero (divition/mod) operation in expression ��"); assert(0); ���^�[����; }
	CSTLString_printf(statement, 0, "if( (%s) == 0 ){ printf(\"#%s#:%d:detected zero ", CSTLString_c_str(DIVITION_INFORMATION_LIST_data(di_i)->statement),
		getFileName(), DIVITION_INFORMATION_LIST_data(di_i)->target_expression->line);

	//���̃^�C�v�����Z����]�Z�ɂ���ă��b�Z�[�W��ς���
	if(DIVITION_INFORMATION_LIST_data(di_i)->type == TYPE_DIV){
		CSTLString_printf(statement, 1, "division ");
	}else{
		CSTLString_printf(statement, 1, "mod ");
	}
	CSTLString_printf(statement, 1, "oparation in expression %s ", CSTLString_c_str(DIVITION_INFORMATION_LIST_data(di_i)->statement));

	//�z��I�t�Z�b�g���X�g����e���ʎq�̏����o�͂����A���ɒǉ����Ă���
	for(aoff_list_i = ARRAY_OFFSET_LIST_begin(DIVITION_INFORMATION_LIST_data(di_i)->identifiers);
		aoff_list_i != ARRAY_OFFSET_LIST_end(DIVITION_INFORMATION_LIST_data(di_i)->identifiers);
		aoff_list_i = ARRAY_OFFSET_LIST_next(aoff_list_i)){
			createArrayExpression(output, ARRAY_OFFSET_LIST_data(aoff_list_i), INT_MAX);
			CSTLString_printf(identifires_list, 1, "%s = %%d", CSTLString_c_str(output));
			//���ʎq���̍Ō�łȂ���΁A�J���}��؂肷��
			if(ARRAY_OFFSET_LIST_next(aoff_list_i) != ARRAY_OFFSET_LIST_end(DIVITION_INFORMATION_LIST_data(di_i)->identifiers)){
				CSTLString_printf(identifires_list, 1,", ");
			}

			CSTLString_printf(parameter_list, 1, ", %s", CSTLString_c_str(output));

		}
	CSTLString_printf(statement, 1, "( %s )\"%s); assert(0);", CSTLString_c_str(identifires_list), CSTLString_c_str(parameter_list));

	//���^�[�����߂̕ԋp�^�ɉ�����ύX(�����Avoid�^�ł���΁A�ureturn;�v�ɂ���)
	if(CSTLString_compare_with_char(DIVITION_INFORMATION_LIST_data(di_i)->target_expression->return_type, "void") == 0){
		CSTLString_printf(statement, 1, "return; ");
	}else{
		CSTLString_printf(statement, 1, "return 1; ");
	}

	CSTLString_printf(statement, 1, "}");

	CSTLString_delete(identifires_list);
	CSTLString_delete(parameter_list);
	CSTLString_delete(output);
}
