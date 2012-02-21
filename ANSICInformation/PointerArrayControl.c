#include"PointerArrayControl.h"

#include"../Library/CSTLString.h"
#include "../Library/CharStringExtend.h"
#include "../Library/IdList.h"
#include "../Library/StoreInformation.h"
#include "SubEffectCheck.h"
#include "ANSIC_CODE.h"
//������̒���
#define STRLEN 1024

//primary_expresion�ŏo�͂ɐ��������ꍇ
#define PRIMARY_SUCCESS 2
//���������ꍇ
#define SUCCESS 1
//���s�����ꍇ
#define FAILED 0

//�A���p�T���h�ł͂���ł��Ȃ��ꍇ�̃t���O
#define NOT_VIA_ANPASAND 0

//�A���p�T���h�ł͂���ł���ꍇ�̃t���O
#define VIA_ANPASAND 1

//�C���N�������g���f�N�������g���܂܂�Ă��邩�ǂ����������t���O
#define NOT_INC_DEC 0
#define VIA_INC 1
#define VIA_DEC 2

//����p���������ۂ��������t���O
#define ALLOW_SUBEFF 1
#define DENIDE_SUBEFF 0

#define DEBUG_MODE


CSTL_LIST_IMPLEMENT(OFFSET_LIST, char *);

CSTL_LIST_IMPLEMENT(ARRAY_OFFSET_LIST, ARRAY_OFFSET);

CSTL_LIST_IMPLEMENT(ASTPOINTER_LIST, AST*);

/**
�z���|�C���^�̊e�����̃I�t�Z�b�g�֌W���i�[���邽�߂̍\���̂̃f�[�^�𐶐�������B
@param variable_name �ϐ���
@param target_statement �^�[�Q�b�g��statement
@param variable_address ���̕ϐ������w���Ă���AST�A�h���X
@param offset_list �e�����̃I�t�Z�b�g
@param pointer_level ���̕ϐ��̃|�C���^���x��
@param array_level ���̕ϐ��̔z�񃌃x��
@param anpasand_flag �A���p�T���h������ł��邩�ǂ����̃t���O�@�P�F����ł���@�O�F����ł��Ȃ�
@param inc_dec_flag �C���N�������g����уf�N�������g���܂܂�Ă��邩�ǂ����̃t���O�@�O�F�܂�ł��Ȃ��@�P�F�C���N�������g���܂܂�Ă���@�Q�F�f�N�������g���܂܂�Ă���

@return �z���|�C���^�̊e�����̃I�t�Z�b�g�Ɋւ���\���̂ւ̃A�h���X��Ԃ��B
*/
ARRAY_OFFSET *new_ARRAY_OFFSET_char(char *variable_name, AST *target_statement, AST *variable_address,
									OFFSET_LIST *offset_list, int pointer_level, int array_level, int anpasand_flag, int inc_dec_flag){
	CSTLString *variable_name_cstl = CSTLString_new();
	CSTLString_assign(variable_name_cstl, variable_name);

	return new_ARRAY_OFFSET(variable_name_cstl, target_statement, variable_address, offset_list, pointer_level, array_level, anpasand_flag, inc_dec_flag);
}

/**�B
�z���|�C���^�̊e�����̃I�t�Z�b�g�֌W���i�[���邽�߂̍\���̂̃f�[�^�𐶐�������B
@param variable_name �ϐ���
@param target_statement �^�[�Q�b�g��statement
@param variable_address ���̕ϐ������w���Ă���AST�A�h���X
@param offset_list �e�����̃I�t�Z�b�g
@param pointer_level ���̕ϐ��̃|�C���^���x��
@param array_level ���̕ϐ��̔z�񃌃x��
@param anpasand_flag ���̕ϐ��̓A���p�T���h������ł��邩�ǂ����̃t���O�@�P�F����ł���@�O�F����ł��Ȃ�
@param inc_dec_flag �C���N�������g����уf�N�������g���܂܂�Ă��邩�ǂ����̃t���O�@�O�F�܂�ł��Ȃ��@�P�F�C���N�������g���܂܂�Ă���@�Q�F�f�N�������g���܂܂�Ă���

@return �z���|�C���^�̊e�����̃I�t�Z�b�g�Ɋւ���\���̂ւ̃A�h���X��Ԃ��B
*/
ARRAY_OFFSET *new_ARRAY_OFFSET(	CSTLString *variable_name, AST *target_statement, AST *variable_address,
							   OFFSET_LIST *offset_list, int pointer_level, int array_level, int anpasand_flag, int inc_dec_flag){
	//�z���|�C���^�̊e�����̃I�t�Z�b�g�֌W���i�[���邽�߂̍\���̂𐶐�����
	ARRAY_OFFSET *new_array_offset = (ARRAY_OFFSET*)malloc(sizeof(ARRAY_OFFSET));

	//�K�v�ȏ��������Ă���
	new_array_offset->variable_name = variable_name;
	new_array_offset->target_statement = target_statement;
	new_array_offset->variable_address = variable_address;
	new_array_offset->offset_list = offset_list;
	new_array_offset->pointer_level = pointer_level;
	new_array_offset->array_level = array_level;
	new_array_offset->anpasand_flag = anpasand_flag;
	new_array_offset->inc_dec_flag = inc_dec_flag;
	//�z���|�C���^�̊e�����̃I�t�Z�b�g�֌W���i�[���邽�߂̍\���̂ւ̃A�h���X��Ԃ�
	return new_array_offset;
}

/**
�C�ӂ̕�������A���I�ϐ��Ƃ��ăI�t�Z�b�g���X�g�ɒǉ�����B
@param offset_list �Ώۂ̃I�t�Z�b�g���X�g
@param string �C�ӂ̕�����

@return �Ȃ�
 */
void OFFSET_LIST_push_back_alloc(OFFSET_LIST *offset_list, char *string){
	 char *target;

	 //�C�ӂ̕����񕪂𐶐����A�C�ӂ̕�����ɑ������
	 target = calloc(strlen(string), sizeof(char));
	 strcpy(target, string);

	 //�������ꂽtarget���I�t�Z�b�g���X�g�ɒǉ�����
	 OFFSET_LIST_push_back(offset_list, target);
 }

/**
getPointerArrayOffset�̓�������
@param root ���Ӓl�Ɋւ���AST�m�[�h
@param function_information_list �֐��Ɋւ����񃊃X�g
@param vtlist ���ؑΏۂ̎����}�[�N���邽�߂̕ϐ����X�g
@param offset_level �I�t�Z�b�g���x�����v�Z���邽�߂̂Ƃ���B��{�I�ɂO����͂���B�P�ȏ���͂���΁A���ꂪ�ŉ��ʃ��x���ƂȂ�B
@param ignore_ast_list �|�C���^�ł̈ʒu�����؍ς݂ł���AIDENTIFIER�𖳎����邽�߂�AST�̃A�h���X���X�g
@param array_offset �|�C���^����єz��̃I�t�Z�b�g���
@param target_statement ���؎��̑ΏۂƂȂ�X�e�[�g�����g
@param anpasand_flag �A���p�T���h������ł��邩�ǂ����̃t���O�@�P�F����ł���@0�F����ł��Ȃ�
@param inc_dec_flag �C���N�������g����уf�N�������g���܂܂�Ă��邩�ǂ����̃t���O�@�O�F�܂�ł��Ȃ��@�P�F�C���N�������g���܂܂�Ă���@�Q�F�f�N�������g���܂܂�Ă���
@return �Ȃ�
*/
int getPointerArrayOffset_Internal(AST *root, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist, int offset_level,
		ASTPOINTER_LIST *ignore_ast_list, ARRAY_OFFSET **array_offset, AST *target_statement, int anpasand_flag, int inc_dec_flag){
	//direct_ref��艺�ʂ�AST�m�[�h
		AST *low_output = NULL;
		AST *low_output2 = NULL;

		//primary�ȉ���AST�m�[�h���X�g�Ƃ��̐�
		AST **primary_level_node_list;

		int primary_level_node_num = 0;
		int i;

		int success_flag = FAILED;

		int pointer_level, array_level;

		int valid_flag;

		CSTLString *primary_level_node_string;

		CSTLString *target;

		CSTLString *array_content;

		VARIABLE_TABLE_LISTIterator vi;

		char *zero;

		//�������x����0�ł���ꍇ�Avalid_flag�͋����I��SUCCESS�ɂ��Alow_output��root���̂��̂ł���
		if(offset_level == 0){
			valid_flag = SUCCESS;
			low_output = root;
		}else{

			//direct_ref��艺�ʂ��ǂ��Ȃ��Ă��邩���ׂ�
			valid_flag = searchPointerAccessOrIdentifierOrPrimary(root, &low_output);
		}

		if(valid_flag == SUCCESS){
			//�����Adirect_ref�Ȃ�A���x�����グ�ē����Q�Ƃ��s���A���̎��̎����̃I�t�Z�b�g��0�ł���B
			if(CSTLString_compare_with_char(low_output->name, "direct_ref") == 0){
				success_flag = getPointerArrayOffset_Internal(low_output, function_information_list, vtlist, offset_level + 1,
					ignore_ast_list, array_offset, target_statement, anpasand_flag, inc_dec_flag);
				//�ϐ�����������΁A�I�t�Z�b�g��ݒ肷��
				if(success_flag == SUCCESS){

					//�I�t�Z�b�g���e�����̔z�񂨂�у|�C���^�̃I�t�Z�b�g���X�g�ɐݒ肷��
					zero = calloc(2, sizeof(char));
					sprintf(zero, "0");
					OFFSET_LIST_push_back_alloc((*array_offset)->offset_list, zero);

				}
				//�����Aprimary_expression�Ƃ��ďo�͂��ꂽ�ꍇ
				else if(success_flag == PRIMARY_SUCCESS){
					success_flag = SUCCESS;
				}
			}

			//�����Aarray_access�Ȃ�A���x�����グ�ē����Q�Ƃ��s���A���̎��̎����̃I�t�Z�b�g�͔z��̒��g�ł���B
			else if(CSTLString_compare_with_char(low_output->name, "array_access") == 0){
				success_flag = getPointerArrayOffset_Internal(low_output, function_information_list, vtlist, offset_level + 1,
					ignore_ast_list, array_offset, target_statement, anpasand_flag, inc_dec_flag);
				//�ϐ�����������΁A�I�t�Z�b�g��ݒ肷��
				if(success_flag == SUCCESS){

					//�I�t�Z�b�g���e�����̔z�񂨂�у|�C���^�̃I�t�Z�b�g���X�g�ɐݒ肷��
					array_content = CSTLString_new();
					getStringFromAST(array_content, getASTwithString(low_output, "array_content", 1));
					OFFSET_LIST_push_back_alloc((*array_offset)->offset_list, (char*)CSTLString_c_str(array_content));

					CSTLString_delete(array_content);
				}
			}

			//�����Aprimary_expression�Ȃ�A���̎��ɗ���̂�minus_expr��plus_expr���Aarray_access��direct_ref���A�͂��܂�IDENTIFIER��CONSTANT�����ׂ�
			else if(CSTLString_compare_with_char(low_output->name, "primary_expression") == 0){
				//primary_expression��艺�ʂ͂ǂ��Ȃ��Ă��邩���ׂ�
				valid_flag = searchExpressionOrPointeArrayOrIden(low_output, &low_output2);
				if(valid_flag == SUCCESS){

					//minus_expr��plus_expr�Ȃ��array_acces�Edirect_ref�EIDENTIFIER���m�[�h���ł���AST���X�g���쐬����B
					if(CSTLString_compare_with_char(low_output2->name, "minus_expr") == 0 ||
						CSTLString_compare_with_char(low_output2->name, "plus_expr") == 0){

						getPointerAccessOrIdentifierList(low_output2, &primary_level_node_list, &primary_level_node_num);

						//�����Aarray_access��direct_ref�Ȃ烌�x�����グ�ē����Q�Ƃ��s���A
						for(i = 0; i < primary_level_node_num; i++){

							//�����Adirect_ref�Ȃ�A���x�����グ�ē����Q�Ƃ��s���A���̎��̎����̃I�t�Z�b�g��0�ł���B
							if(CSTLString_compare_with_char(primary_level_node_list[i]->name, "direct_ref") == 0){
								success_flag = getPointerArrayOffset_Internal(primary_level_node_list[i], function_information_list, vtlist, offset_level + 1, ignore_ast_list,
									array_offset, target_statement, anpasand_flag, inc_dec_flag);
								//�ϐ�����������΁A�I�t�Z�b�g��ݒ肷��
								if(success_flag == SUCCESS){
									//�I�t�Z�b�g���e�����̔z�񂨂�у|�C���^�̃I�t�Z�b�g���X�g�ɐݒ肷��
									OFFSET_LIST_push_back_alloc((*array_offset)->offset_list, "0");

								}
								//�����Aprimary_expression�Ƃ��ďo�͂��ꂽ�ꍇ
								else if(success_flag == PRIMARY_SUCCESS){
									success_flag = SUCCESS;
								}
							}


							//�����Aarray_access�Ȃ�A���x�����グ�ē����Q�Ƃ��s���A���̎��̎����̃I�t�Z�b�g�͔z��̒��g�ł���B
							else if(CSTLString_compare_with_char(primary_level_node_list[i]->name, "array_access") == 0){
								success_flag = getPointerArrayOffset_Internal(primary_level_node_list[i], function_information_list, vtlist, offset_level + 1, ignore_ast_list,
									array_offset, target_statement, anpasand_flag, inc_dec_flag);
								//�ϐ�����������΁A�I�t�Z�b�g��ݒ肷��
								if(success_flag == SUCCESS){
									//�I�t�Z�b�g���e�����̔z�񂨂�у|�C���^�̃I�t�Z�b�g���X�g�ɐݒ肷��
									array_content = CSTLString_new();
									getStringFromAST(array_content, getASTwithString(primary_level_node_list[i], "array_content", 1));
									OFFSET_LIST_push_back_alloc((*array_offset)->offset_list, (char*)CSTLString_c_str(array_content));

									CSTLString_delete(array_content);
									break;
								}
							}

							//IDENTIFIER��������A�ϐ��e�[�u�����璲�ׁA�ǂ̂悤�ȕϐ��ł��邩����ׂ�
							else if(CSTLString_compare_with_char(primary_level_node_list[i]->name, "IDENTIFIER") == 0){
								pointer_level = 0;
								array_level = 0;
								success_flag = checkIdentifierPointerArrayLevel(primary_level_node_list[i], offset_level, vtlist,
									ignore_ast_list, &pointer_level, &array_level);
								if(success_flag == SUCCESS){
									//�z���|�C���^�̊e�����ɑ΂���I�t�Z�b�g���𐶐����Aarray_offset�ɑ������
									OFFSET_LIST *offset_list = OFFSET_LIST_new();

									*array_offset = new_ARRAY_OFFSET_char((char *)CSTLString_c_str(primary_level_node_list[i]->content), target_statement,
										primary_level_node_list[i], offset_list, pointer_level, array_level, anpasand_flag, inc_dec_flag);
								}
							}

							//�����A�֐��Ăяo���Ȃ�A���̊֐��������݂��邩�ǂ������ׂ�
							else if(CSTLString_compare_with_char(primary_level_node_list[i]->name, "call_function")){
								checkCallFunction(primary_level_node_list[i],offset_level,function_information_list);
							}

							//�����A�C���N�������g��f�N�������g���������ꍇ�́A����͖]�܂����Ȃ������Ƃ݂Ȃ��A�G���[���o�͂��A�����I��������
							//���R�F����p���������|�C���^���Z��z����ɏ������Ǝ��̂��ێ�I�ɕ�����ɂ�������
							else if(CSTLString_compare_with_char(primary_level_node_list[i]->name, "inc_after_expr") == 0 ||
							CSTLString_compare_with_char(primary_level_node_list[i]->name, "inc_expr") == 0 ||
							CSTLString_compare_with_char(primary_level_node_list[i]->name, "dec_after_expr") == 0 ||
							CSTLString_compare_with_char(primary_level_node_list[i]->name, "inc_expr") == 0){
								fprintf(stderr, "#%s#:%d:Invalid Pointer Access!! Shouldn't contain Inclement or Declement Expression!!\n", getFileName(), primary_level_node_list[i]->line);
								exit(1);
							}
							//�����A������������ꍇ�́A����͖]�܂����Ȃ������Ƃ݂Ȃ��A�G���[���o�͂��A�����I��������
							//���R�F����p���������|�C���^���Z��z����ɂɏ������Ǝ��̖]�܂����Ȃ�����
							else if(CSTLString_compare_with_char(primary_level_node_list[i]->name, "assignment_expression") == 0){
								fprintf(stderr, "#%s#:%d:Invalid Pointer Access!! Shouldn't contain Assignment Expression!!\n", getFileName(), primary_level_node_list[i]->line);
								exit(1);
							}
							if(success_flag == SUCCESS){
								break;
							}

						}
						//primary_expression�ȉ��̎��ŁA�|�C���^�ϐ����������ꍇ
						if(success_flag == SUCCESS){
							//�܂��A���̃|�C���^�ϐ��͊ԐړI�ɂǂ̉��Z�Ɉʒu���Ă��邩�ǂ������ׁAupper_relation�ɑ������B
							//����upper_relation��minus_expr�ł���ꍇ�́A������1���̃m�[�h��one_level_down�ɑ������B
							//����́A-���Z���ł��̂ЂƂ������l���E�l�Ɉʒu���Ă��邩�ǂ����m�F���邽�߂ł���B
							AST *upper_relation, *one_level_down;
							valid_flag = getUpperExpressionRelationNode(primary_level_node_list[i], low_output, &upper_relation, &one_level_down);

							//minus_expr�ł���A�ЂƂ����E�l�Ɉʒu���Ă���ꍇ
							if(CSTLString_compare_with_char(upper_relation->name, "minus_expr") == 0 &&
								ASTList_data(ASTList_next(ASTList_next(ASTList_begin(upper_relation->children)))) == one_level_down){
									fprintf(stderr, "#%s#:%d:Invalid Pointer Operator is %s and located right value!", getFileName(), low_output2->line, CSTLString_c_str(upper_relation->name));
									exit(1);
							}

							//��ʊ֌W�𒲂ׂ�̂Ɏ��s�������Aprimary_expression�Earray_access�Edirect_ref�Eplus_expr�Eminus_expr�̂�����ł��Ȃ��ꍇ
							else if(valid_flag == FAILED ||
								(CSTLString_compare_with_char(upper_relation->name, "primary_expression") != 0 &&
								CSTLString_compare_with_char(upper_relation->name, "array_access") != 0 &&
								CSTLString_compare_with_char(upper_relation->name, "direct_ref") != 0 &&
								CSTLString_compare_with_char(upper_relation->name, "plus_expr") != 0 &&
								CSTLString_compare_with_char(upper_relation->name, "minus_expr") != 0)){
									//�G���[���o�͂��A�����I��������B
									fprintf(stderr, "#%s#:%d:Invalid Pointer Operator is %s !", getFileName(), low_output2->line, CSTLString_c_str(upper_relation->name));
									exit(1);
							}

							//��L�ȊO�̏ꍇ�͐����ł���
							else{

								//�I�t�Z�b�g���e�����̔z�񂨂�у|�C���^�̃I�t�Z�b�g���X�g�ɐݒ肷��
								primary_level_node_string = CSTLString_new();
								getStringReplaceASTtoString(primary_level_node_string, getASTwithString(low_output, "t_expression", 1), primary_level_node_list[i], "0");
								OFFSET_LIST_push_back_alloc((*array_offset)->offset_list, (char*)CSTLString_c_str(primary_level_node_string));

								CSTLString_delete(primary_level_node_string);
								//primary_expression�ŏo�͂��ꂽ���Ƃ������Ŏ���
								success_flag = PRIMARY_SUCCESS;
							}

						}

						//primary�ȉ���AST�m�[�h���X�g�͂����ŏ���������A���̌��͂O�ƂȂ�B
						free(primary_level_node_list);
						primary_level_node_num = 0;

					}

					//�����Adirect_ref�Ȃ�A���x�����グ�ē����Q�Ƃ��s���A���̎��̎����̃I�t�Z�b�g��0�ł���B
					else if(CSTLString_compare_with_char(low_output2->name, "direct_ref") == 0){
						success_flag = getPointerArrayOffset_Internal(low_output2, function_information_list, vtlist, offset_level + 1, ignore_ast_list, array_offset, target_statement, anpasand_flag, inc_dec_flag);
						//�ϐ�����������΁A�I�t�Z�b�g��ݒ肷��
						if(success_flag == SUCCESS){
							//�I�t�Z�b�g���e�����̔z�񂨂�у|�C���^�̃I�t�Z�b�g���X�g�ɐݒ肷��
							OFFSET_LIST_push_back_alloc((*array_offset)->offset_list, "0");

						}
						//�����Aprimary_expression�Ƃ��ďo�͂��ꂽ�ꍇ
						else if(success_flag == PRIMARY_SUCCESS){
							success_flag = SUCCESS;
						}
					}

					//�����Aarray_access�Ȃ�A���x�����グ�ē����Q�Ƃ��s���A���̎��̎����̃I�t�Z�b�g�͔z��̒��g�ł���B
					else if(CSTLString_compare_with_char(low_output2->name, "array_access") == 0){
						success_flag = getPointerArrayOffset_Internal(low_output2, function_information_list, vtlist, offset_level + 1, ignore_ast_list, array_offset, target_statement, anpasand_flag, inc_dec_flag);
						//�ϐ�����������΁A�I�t�Z�b�g��ݒ肷��
						if(success_flag == SUCCESS){

							//�I�t�Z�b�g���e�����̔z�񂨂�у|�C���^�̃I�t�Z�b�g���X�g�ɐݒ肷��
							array_content = CSTLString_new();
							getStringFromAST(array_content, getASTwithString(low_output2, "array_content", 1));
							OFFSET_LIST_push_back_alloc((*array_offset)->offset_list, (char*)CSTLString_c_str(array_content));

							CSTLString_delete(array_content);
						}
					}

					//IDENTIFIER��������A�ϐ��e�[�u�����璲�ׁA�ǂ̂悤�ȕϐ��ł��邩����ׂ�
					else if(CSTLString_compare_with_char(low_output2->name, "IDENTIFIER") == 0){
						pointer_level = 0;
						array_level = 0;
						success_flag = checkIdentifierPointerArrayLevel(low_output2, offset_level, vtlist, ignore_ast_list, &pointer_level, &array_level);
						if(success_flag == SUCCESS){
							//�z���|�C���^�̊e�����ɑ΂���I�t�Z�b�g���𐶐����Aarray_offset�ɑ������
							OFFSET_LIST *offset_list = OFFSET_LIST_new();
							*array_offset = new_ARRAY_OFFSET_char((char *)CSTLString_c_str(low_output2->content), target_statement, low_output2,
								offset_list, pointer_level, array_level, anpasand_flag, inc_dec_flag);
						}
					}

					//�����A�֐��Ăяo���Ȃ�A���̊֐��������݂��邩�ǂ������ׂ�
					else if(CSTLString_compare_with_char(low_output2->name, "call_function")){
						checkCallFunction(low_output2,offset_level,function_information_list);
					}

					//�����A�C���N�������g��f�N�������g���������ꍇ�́A����͖]�܂����Ȃ������Ƃ݂Ȃ��A�G���[���o�͂��A�����I��������
					//���R�F����p���������|�C���^���Z��z����ɏ������Ǝ��̂��ێ�I�ɕ�����ɂ�������
					else if(CSTLString_compare_with_char(low_output2->name, "inc_after_expr") == 0 ||
					CSTLString_compare_with_char(low_output2->name, "inc_expr") == 0 ||
					CSTLString_compare_with_char(low_output2->name, "dec_after_expr") == 0 ||
					CSTLString_compare_with_char(low_output2->name, "inc_expr") == 0){
						fprintf(stderr, "#%s#:%d:Invalid Pointer Access!! Shouldn't contain Inclement or Declement Expression!!\n", getFileName(), low_output2->line);
						exit(1);
					}
					//�����A������������ꍇ�́A����͖]�܂����Ȃ������Ƃ݂Ȃ��A�G���[���o�͂��A�����I��������
					//���R�F����p���������|�C���^���Z��z����ɂɏ������Ǝ��̖]�܂����Ȃ�����
					else if(CSTLString_compare_with_char(low_output2->name, "assignment_expression") == 0){
						fprintf(stderr, "#%s#:%d:Invalid Pointer Access!! Shouldn't contain Assignment Expression!!\n", getFileName(), low_output2->line);
						exit(1);
					}
				}

				//��L�ȊO�̎���������A�G���[���o�͂�����
				else if(valid_flag == -1){
					fprintf(stderr, "#%s#:%d:Invalid Access!\n", getFileName(), root->line);
					fflush(stderr);
					exit(1);
				}
			}

			//�����AIDENTIFIER�Ȃ�A�ϐ��e�[�u�����璲�ׁA�ǂ̂悤�ȕϐ��ł��邩����ׂ�
			else if(CSTLString_compare_with_char(low_output->name, "IDENTIFIER") == 0){
				pointer_level = 0;
				array_level = 0;
				success_flag = checkIdentifierPointerArrayLevel(low_output, offset_level, vtlist, ignore_ast_list, &pointer_level, &array_level);
				if(success_flag == SUCCESS){
					//�z���|�C���^�̊e�����ɑ΂���I�t�Z�b�g���𐶐����Aarray_offset�ɑ������
					OFFSET_LIST *offset_list = OFFSET_LIST_new();
					*array_offset = new_ARRAY_OFFSET_char((char *)CSTLString_c_str(low_output->content), target_statement, low_output,
						offset_list, pointer_level, array_level, anpasand_flag, inc_dec_flag);
				}
			}

			//�����A�֐��Ăяo���Ȃ�A���̊֐��������݂��邩�ǂ������ׂ�
			else if(CSTLString_compare_with_char(low_output->name, "call_function")){
				checkCallFunction(low_output,offset_level,function_information_list);
			}

			//�����A�C���N�������g��f�N�������g���������ꍇ�́A����͖]�܂����Ȃ������Ƃ݂Ȃ��A�G���[���o�͂��A�����I��������
			//���R�F����p���������|�C���^���Z��z����ɏ������Ǝ��̖]�܂����Ȃ�����
			else if(CSTLString_compare_with_char(low_output->name, "inc_after_expr") == 0 ||
			CSTLString_compare_with_char(low_output->name, "inc_expr") == 0 ||
			CSTLString_compare_with_char(low_output->name, "dec_after_expr") == 0 ||
			CSTLString_compare_with_char(low_output->name, "inc_expr") == 0){
				fprintf(stderr, "#%s#:%d:Invalid Pointer Access!! Shouldn't contain Increment or Decrement Expression!!\n", getFileName(), low_output->line);
				exit(1);
			}
			//�����A������������ꍇ�́A����͖]�܂����Ȃ������Ƃ݂Ȃ��A�G���[���o�͂��A�����I��������
			//���R�F����p���������|�C���^���Z��z����ɂɏ������Ǝ��̖]�܂����Ȃ�����
			else if(CSTLString_compare_with_char(low_output->name, "assignment_expression") == 0){
				fprintf(stderr, "#%s#:%d:Invalid Pointer Access!! Shouldn't contain Assignment Expression!!\n", getFileName(), low_output->line);
				exit(1);
			}

		}

		return success_flag;
}



/**
�|�C���^����єz��ϐ��̊e�����̃I�t�Z�b�g�ƂȂ鎮�����߂�B
@param root ���Ӓl�Ɋւ���AST�m�[�h
@param function_information_list �֐��Ɋւ����񃊃X�g
@param vtlist ���ؑΏۂ̎����}�[�N���邽�߂̕ϐ����X�g
@param offset_level �I�t�Z�b�g���x�����v�Z���邽�߂̂Ƃ���B��{�I�ɂO����͂���B�P�ȏ���͂���΁A���ꂪ�ŉ��ʃ��x���ƂȂ�B
@param ignore_ast_list �|�C���^�ł̈ʒu�����؍ς݂ł���AIDENTIFIER�𖳎����邽�߂�AST�̃A�h���X���X�g
@param array_offset �|�C���^����єz��̃I�t�Z�b�g���
@param target_statement ���؎��̑ΏۂƂȂ�X�e�[�g�����g
@param anpasand_flag �A���p�T���h������ł��邩�ǂ����̃t���O�@�P�F����ł���@0�F����ł��Ȃ�
@param inc_dec_flag �C���N�������g����уf�N�������g���܂܂�Ă��邩�ǂ����̃t���O�@�O�F�܂�ł��Ȃ��@�P�F�C���N�������g���܂܂�Ă���@�Q�F�f�N�������g���܂܂�Ă���
@return �Ȃ�
*/
int getPointerArrayOffset(AST *root, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist, int offset_level,
	ASTPOINTER_LIST *ignore_ast_list, ARRAY_OFFSET **array_offset, AST *target_statement, int anpasand_flag, int inc_dec_flag){
	int success_flag;
	//����p�����܂܂�Ă��邩�ǂ����`�F�b�N����
	int contain_subeffect_flag = checkContainSubEffectStatement(root);
	switch(contain_subeffect_flag){
	//�C���N�������g�����܂܂�Ă����ꍇ
	case 1:
		fprintf(stderr, "#%s#:%d:Invalid Pointer Access!! Shouldn't contain Increment Expression!!\n", getFileName(), root->line);
		exit(1);
		break;
	//�f�N�������g�����܂܂�Ă����ꍇ
	case 2:
		fprintf(stderr, "#%s#:%d:Invalid Pointer Access!! Shouldn't contain Decrement Expression!!\n", getFileName(), root->line);
		exit(1);
		break;
	//��������܂܂�Ă����ꍇ
	case 3:
		fprintf(stderr, "#%s#:%d:Invalid Pointer Access!! Shouldn't contain Assignment Expression!!\n", getFileName(), root->line);
		exit(1);
		break;
	//����p�����܂܂�Ă��Ȃ������ꍇ�A�z��I�t�Z�b�g���擾����
	default:
		success_flag = getPointerArrayOffset_Internal(root, function_information_list, vtlist, offset_level, ignore_ast_list, array_offset, target_statement, anpasand_flag, inc_dec_flag);
	}
	return success_flag;
}

/**
�|�C���^����єz��ϐ��̊e�����̃I�t�Z�b�g���X�g���擾����B
@param root �I�t�Z�b�g���X�g�ɊY������AST�m�[�h
@param array_offset_list �|�C���^����єz��̃I�t�Z�b�g���̃��X�g
@param function_information_list �֐��Ɋւ����񃊃X�g
@param vtlist ���ؑΏۂ̎����}�[�N���邽�߂̕ϐ����X�g
@param ignore_ast_list �|�C���^�ł̈ʒu�����؍ς݂ł���AIDENTIFIER�𖳎����邽�߂�AST�̃A�h���X���X�g
@param target_statement ���؎��̑ΏۂƂȂ�X�e�[�g�����g
@return �Ȃ�
*/
void getARRAY_OFFSET_LIST(AST *root, ARRAY_OFFSET_LIST *array_offset_list, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
						  ASTPOINTER_LIST *ignore_ast_list, AST *target_statement){
	ASTListIterator ast_i;
	//���ڎQ�ƋL����z��Q�Ƃ������ꍇ�A�I�t�Z�b�g���X�g���쐬����B
	if(CSTLString_compare_with_char(root->name, "direct_ref") == 0 ||
		CSTLString_compare_with_char(root->name, "array_access") == 0){

			ARRAY_OFFSET *array_offset = NULL;
			getPointerArrayOffset(root, function_information_list, vtlist, 0, ignore_ast_list, &array_offset, target_statement, NOT_VIA_ANPASAND, NOT_INC_DEC);
			if(array_offset != NULL){
				ARRAY_OFFSET_LIST_push_back_ref(array_offset_list, array_offset);
			}

	}
	//�A�h���X���Z�q�������ꍇ�́A���̂悤�ɒT��
	else if(CSTLString_compare_with_char(root->name, "address_ref") == 0){
			getArrayOffsetInAnpasandInfo(root, function_information_list, vtlist,
							array_offset_list, ignore_ast_list, target_statement);
	}
	//�C���N�������g���Z�q�������ꍇ�́A�C���N�������g��ʂ����z��I�t�Z�b�g���X�g���擾����
	else if(CSTLString_compare_with_char(root->name, "inc_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "inc_after_expr") == 0){
		getArrayOffsetInIncDecInfo(root, function_information_list, vtlist,
								array_offset_list, ignore_ast_list, target_statement, VIA_INC);
	}
	//�f�N�������g���Z�q�������ꍇ�́A�C���N�������g��ʂ����z��I�t�Z�b�g���X�g���擾����
	else if(CSTLString_compare_with_char(root->name, "dec_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "dec_after_expr") == 0){
		getArrayOffsetInIncDecInfo(root, function_information_list, vtlist,
								array_offset_list, ignore_ast_list, target_statement, VIA_DEC);
	}
	//���ʎq��������΁A�ϐ��e�[�u�����瑶�݂���ϐ����ǂ����𒲂ׂĂ���A�I�t�Z�b�g���X�g���쐬����B
	else if(CSTLString_compare_with_char(root->name, "IDENTIFIER") == 0){
		//�I�t�Z�b�g��񂪂Ȃ�array_offset���쐬����B
		ARRAY_OFFSET *array_offset;
		VARIABLE_TABLE *variable_table_data;
		OFFSET_LIST *offset_list = OFFSET_LIST_new();
		CSTLString *target_name = CSTLString_new();
		//�w�肵���m�[�hroot���Aignore_ast_list�ɑ��݂��Ȃ����ǂ������ׂ邽�߂̃t���O
		int ignore_flag;
		//�Y������ϐ��̃|�C���^�������͔z��̎����𒲂ׂ�B
		int pointer_level, array_level;
		//�w�肵��IDLIST�Ɩ��O����ł��Y������ϐ��e�[�u���ւ̃A�h���X���擾����
		variable_table_data = searchVARIABLE_TABLE_LIST(root->idlist, root->content, vtlist);
		//�����A�Y������ϐ������������ꍇ
		if(variable_table_data != NULL){
			//�w�肵���m�[�hroot���Aignore_ast_list�ɑ��݂��Ȃ����ǂ������ׂ�
			ignore_flag = checkIgnoreASTList(root, ignore_ast_list);

			//�����A���݂��Ȃ���΁A�z��I�t�Z�b�g���X�g�ɒǉ�����
			if(ignore_flag == FAILED){
				getPointerLevelAndArrayLevelFromVARIABLE_TABLE(variable_table_data, &pointer_level, &array_level);

				CSTLString_assign(target_name, CSTLString_c_str(root->content));

				array_offset = new_ARRAY_OFFSET(target_name, target_statement, root, offset_list, pointer_level, array_level, NOT_VIA_ANPASAND, NOT_INC_DEC);

				//DEBUG_MODE���L���Ȏ��|�C���^����єz��ϐ��̊e�����̃I�t�Z�b�g�̏����o�͂���
				#ifdef DEBUG_MODE
					if(array_offset != NULL){
						printARRAY_OFFSET(array_offset);
					}
				#endif

				//�����array_offset_list�ɒǉ�����
				ARRAY_OFFSET_LIST_push_back_ref(array_offset_list, array_offset);
			}

		}
	}
	for(ast_i = ASTList_begin(root->children);
		ast_i != ASTList_end(root->children);
		ast_i = ASTList_next(ast_i)){

			getARRAY_OFFSET_LIST(ASTList_data(ast_i) ,array_offset_list, function_information_list, vtlist, ignore_ast_list, target_statement);
	}

}
/**
�|�C���^����єz��ϐ��̊e�����̃I�t�Z�b�g���X�g���擾����B�܂��A����������Ώۂ̃m�[�h��ݒ�\�ł���B
@param root �I�t�Z�b�g���X�g�ɊY������AST�m�[�h
@param array_offset_list �|�C���^����єz��̃I�t�Z�b�g���̃��X�g
@param function_information_list �֐��Ɋւ����񃊃X�g
@param vtlist ���ؑΏۂ̎����}�[�N���邽�߂̕ϐ����X�g
@param ignore_ast_list �|�C���^�ł̈ʒu�����؍ς݂ł���AIDENTIFIER�𖳎����邽�߂�AST�̃A�h���X���X�g
@param target_statement ���؎��̑ΏۂƂȂ�X�e�[�g�����g
@param ignore_ast_name ����������`�r�s��
@return �Ȃ�
*/
void get_ARRAY_OFFSET_LISTIgnoreASTNAME(AST *root, ARRAY_OFFSET_LIST *array_offset_list, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
		  ASTPOINTER_LIST *ignore_ast_list, AST *target_statement, CSTLString *ignore_ast_name){
	ASTListIterator ast_i;
	//���ڎQ�ƋL����z��Q�Ƃ������ꍇ�A�I�t�Z�b�g���X�g���쐬����B
	if(CSTLString_compare_with_char(root->name, "direct_ref") == 0 ||
		CSTLString_compare_with_char(root->name, "array_access") == 0){

			ARRAY_OFFSET *array_offset = NULL;
			getPointerArrayOffset(root, function_information_list, vtlist, 0, ignore_ast_list, &array_offset, target_statement, NOT_VIA_ANPASAND, NOT_INC_DEC);
			if(array_offset != NULL){
				ARRAY_OFFSET_LIST_push_back_ref(array_offset_list, array_offset);
			}

	}
	//�A�h���X���Z�q�������ꍇ�́A���̂悤�ɒT��
	else if(CSTLString_compare_with_char(root->name, "address_ref") == 0){
			getArrayOffsetInAnpasandInfo(root, function_information_list, vtlist,
							array_offset_list, ignore_ast_list, target_statement);
	}
	//�C���N�������g���Z�q�������ꍇ�́A�C���N�������g��ʂ����z��I�t�Z�b�g���X�g���擾����
	else if(CSTLString_compare_with_char(root->name, "inc_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "inc_after_expr") == 0){
		getArrayOffsetInIncDecInfo(root, function_information_list, vtlist,
								array_offset_list, ignore_ast_list, target_statement, VIA_INC);
	}
	//�f�N�������g���Z�q�������ꍇ�́A�C���N�������g��ʂ����z��I�t�Z�b�g���X�g���擾����
	else if(CSTLString_compare_with_char(root->name, "dec_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "dec_after_expr") == 0){
		getArrayOffsetInIncDecInfo(root, function_information_list, vtlist,
								array_offset_list, ignore_ast_list, target_statement, VIA_DEC);
	}
	//���ʎq��������΁A�ϐ��e�[�u�����瑶�݂���ϐ����ǂ����𒲂ׂĂ���A�I�t�Z�b�g���X�g���쐬����B
	else if(CSTLString_compare_with_char(root->name, "IDENTIFIER") == 0){
		//�I�t�Z�b�g��񂪂Ȃ�array_offset���쐬����B
		ARRAY_OFFSET *array_offset;
		VARIABLE_TABLE *variable_table_data;
		OFFSET_LIST *offset_list = OFFSET_LIST_new();
		CSTLString *target_name = CSTLString_new();
		//�w�肵���m�[�hroot���Aignore_ast_list�ɑ��݂��Ȃ����ǂ������ׂ邽�߂̃t���O
		int ignore_flag;
		//�Y������ϐ��̃|�C���^�������͔z��̎����𒲂ׂ�B
		int pointer_level, array_level;
		//�w�肵��IDLIST�Ɩ��O����ł��Y������ϐ��e�[�u���ւ̃A�h���X���擾����
		variable_table_data = searchVARIABLE_TABLE_LIST(root->idlist, root->content, vtlist);
		//�����A�Y������ϐ������������ꍇ
		if(variable_table_data != NULL){
			//�w�肵���m�[�hroot���Aignore_ast_list�ɑ��݂��Ȃ����ǂ������ׂ�
			ignore_flag = checkIgnoreASTList(root, ignore_ast_list);

			//�����A���݂��Ȃ���΁A�z��I�t�Z�b�g���X�g�ɒǉ�����
			if(ignore_flag == FAILED){
				getPointerLevelAndArrayLevelFromVARIABLE_TABLE(variable_table_data, &pointer_level, &array_level);

				CSTLString_assign(target_name, CSTLString_c_str(root->content));

				array_offset = new_ARRAY_OFFSET(target_name, target_statement, root, offset_list, pointer_level, array_level, NOT_VIA_ANPASAND, NOT_INC_DEC);

				//DEBUG_MODE���L���Ȏ��|�C���^����єz��ϐ��̊e�����̃I�t�Z�b�g�̏����o�͂���
				#ifdef DEBUG_MODE
					if(array_offset != NULL){
						printARRAY_OFFSET(array_offset);
					}
				#endif

				//�����array_offset_list�ɒǉ�����
				ARRAY_OFFSET_LIST_push_back_ref(array_offset_list, array_offset);
			}

		}
	}
	for(ast_i = ASTList_begin(root->children);
		ast_i != ASTList_end(root->children);
		ast_i = ASTList_next(ast_i)){
			//��������m�[�h���ł���΁A�ȗ�����
			if(CSTLString_compare(ASTList_data(ast_i)->name, ignore_ast_name) != 0){
				getARRAY_OFFSET_LIST(ASTList_data(ast_i) ,array_offset_list, function_information_list, vtlist, ignore_ast_list, target_statement);
			}
	}
}
/**
address_ref�ł���m�[�h����T�����A����ɑ΂���A�h���X�Q�Ƃ�A���ʎq��T���o���A��������z��I�t�Z�b�g���X�garray_offset_list�֓����B
@param root �E�ӎ��Ɋւ���AST�m�[�h
@param function_information_list �֐��Ɋւ�����̃��X�g
@param vtlist �������m�ۏ����擾����̂ɕK�v�ȃv���O�����ϐ����X�g
@param array_offset_list ���ӎ���ɂ���|�C���^�Q�Ƃɑ΂���I�t�Z�b�g���X�g
@param ignore_ast_list �����ʒu�̃|�C���^�����Ă��������邽�߂̃��X�g
@param target_statement ���̌v�Z���𑮂��Ă���AST�m�[�h�ւ̃A�h���X�i��{�I��expression_statement�ł���m�[�h������j

@return �Ȃ�
*/
void getArrayOffsetInAnpasandInfo(AST *root,FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
							ARRAY_OFFSET_LIST *array_offset_list, ASTPOINTER_LIST *ignore_ast_list, AST *target_statement){
	ASTListIterator ast_i;
	//���ڎQ�ƋL����z��Q�Ƃ������ꍇ�A�I�t�Z�b�g���X�g���쐬����B
	if(CSTLString_compare_with_char(root->name, "direct_ref") == 0 ||
		CSTLString_compare_with_char(root->name, "array_access") == 0){

			ARRAY_OFFSET *array_offset = NULL;
			getPointerArrayOffset(root, function_information_list, vtlist, 0, ignore_ast_list, &array_offset, target_statement, VIA_ANPASAND, NOT_INC_DEC);
			if(array_offset != NULL){
				ARRAY_OFFSET_LIST_push_back_ref(array_offset_list, array_offset);
			}

			#ifdef DEBUG_MODE
				if(array_offset != NULL){
					printARRAY_OFFSET(array_offset);
				}
			#endif

	}
	//���ʎq��������΁A�ϐ��e�[�u�����瑶�݂���ϐ����ǂ����𒲂ׂĂ���A�I�t�Z�b�g���X�g���쐬����B
	else if(CSTLString_compare_with_char(root->name, "IDENTIFIER") == 0){
		//�I�t�Z�b�g��񂪂Ȃ�array_offset���쐬����B
		ARRAY_OFFSET *array_offset;
		VARIABLE_TABLE *variable_table_data;
		OFFSET_LIST *offset_list = OFFSET_LIST_new();
		CSTLString *target_name = CSTLString_new();
		//�w�肵���m�[�hroot���Aignore_ast_list�ɑ��݂��Ȃ����ǂ������ׂ邽�߂̃t���O
		int ignore_flag;
		//�Y������ϐ��̃|�C���^�������͔z��̎����𒲂ׂ�B
		int pointer_level, array_level;
		//�w�肵��IDLIST�Ɩ��O����ł��Y������ϐ��e�[�u���ւ̃A�h���X���擾����
		variable_table_data = searchVARIABLE_TABLE_LIST(root->idlist, root->content, vtlist);
		//�����A�Y������ϐ������������ꍇ
		if(variable_table_data != NULL){
			//�w�肵���m�[�hroot���Aignore_ast_list�ɑ��݂��Ȃ����ǂ������ׂ�
			ignore_flag = checkIgnoreASTList(root, ignore_ast_list);

			//�����A���݂��Ȃ���΁A�z��I�t�Z�b�g���X�g�ɒǉ�����
			if(ignore_flag == FAILED){
				getPointerLevelAndArrayLevelFromVARIABLE_TABLE(variable_table_data, &pointer_level, &array_level);

				CSTLString_assign(target_name, CSTLString_c_str(root->content));

				array_offset = new_ARRAY_OFFSET(target_name, target_statement, root, offset_list, pointer_level, array_level, VIA_ANPASAND, NOT_INC_DEC);

				//DEBUG_MODE���L���Ȏ��|�C���^����єz��ϐ��̊e�����̃I�t�Z�b�g�̏����o�͂���
				#ifdef DEBUG_MODE
					if(array_offset != NULL){
						printARRAY_OFFSET(array_offset);
					}
				#endif

				//�����array_offset_list�ɒǉ�����
				ARRAY_OFFSET_LIST_push_back_ref(array_offset_list, array_offset);
			}

		}
	}
	//��ɁA�C���N�������g����уf�N�������g�A���̑��̉��Z����������΁A�G���[���o�͂��ċ����I��������
	else if(CSTLString_compare_with_char(root->name, "inc_after_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "inc_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "dec_after_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "dec_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "minus_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "plus_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "log_or_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "log_and_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "or_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "xor_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "and_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "eq_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "ne_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "lethan_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "gethan_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "leeq_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "geeq_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "left_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "right_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "mul_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "div_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "mod_expr") == 0){
			fprintf(stderr,"#%s#:%d:lvalue required as unary \'&\' operand",getFileName(), root->line);
			exit(1);
	}
	else{
		for(ast_i = ASTList_begin(root->children);
			ast_i != ASTList_end(root->children);
			ast_i = ASTList_next(ast_i)){

				getArrayOffsetInAnpasandInfo(ASTList_data(ast_i), function_information_list, vtlist, array_offset_list, ignore_ast_list, target_statement);
		}
	}
}

/**
inc_expr��dec_expr�Ȃǂ̃C���N�������g��f�N�������g���ł���m�[�h����T�����A����ɑ΂���A�h���X�Q�Ƃ�A���ʎq��T���o���A��������z��I�t�Z�b�g���X�garray_offset_list�֓����B
@param root inc_expr��dec_expr�Ȃǂ̃C���N�������g��f�N�������g���Ɋւ���AST�m�[�h
@param function_information_list �֐��Ɋւ�����̃��X�g
@param vtlist �������m�ۏ����擾����̂ɕK�v�ȃv���O�����ϐ����X�g
@param array_offset_list ���ӎ���ɂ���|�C���^�Q�Ƃɑ΂���I�t�Z�b�g���X�g
@param ignore_ast_list �����ʒu�̃|�C���^�����Ă��������邽�߂̃��X�g
@param target_statement ���̌v�Z���𑮂��Ă���AST�m�[�h�ւ̃A�h���X�i��{�I��expression_statement�ł���m�[�h������j
@param inc_dec_flag �C���N�������g����уf�N�������g���܂܂�Ă��邩�ǂ����̃t���O�@�P�F�C���N�������g���܂܂�Ă���@�Q�F�f�N�������g���܂܂�Ă���

@return �Ȃ�
*/
void getArrayOffsetInIncDecInfo(AST *root, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
								ARRAY_OFFSET_LIST *array_offset_list, ASTPOINTER_LIST *ignore_ast_list, AST *target_statement, int inc_dec_flag){
	ASTListIterator ast_i;
	//���ڎQ�ƋL����z��Q�Ƃ������ꍇ�A�I�t�Z�b�g���X�g���쐬����B
	if(CSTLString_compare_with_char(root->name, "direct_ref") == 0 ||
		CSTLString_compare_with_char(root->name, "array_access") == 0){

			ARRAY_OFFSET *array_offset = NULL;
			getPointerArrayOffset(root, function_information_list, vtlist, 0, ignore_ast_list, &array_offset, target_statement, NOT_VIA_ANPASAND, inc_dec_flag);
			if(array_offset != NULL){
				ARRAY_OFFSET_LIST_push_back_ref(array_offset_list, array_offset);
			}

			#ifdef DEBUG_MODE
				if(array_offset != NULL){
					printARRAY_OFFSET(array_offset);
				}
			#endif

	}
	//���ʎq��������΁A�ϐ��e�[�u�����瑶�݂���ϐ����ǂ����𒲂ׂĂ���A�I�t�Z�b�g���X�g���쐬����B
	else if(CSTLString_compare_with_char(root->name, "IDENTIFIER") == 0){
		//�I�t�Z�b�g��񂪂Ȃ�array_offset���쐬����B
		ARRAY_OFFSET *array_offset;
		VARIABLE_TABLE *variable_table_data;
		OFFSET_LIST *offset_list = OFFSET_LIST_new();
		CSTLString *target_name = CSTLString_new();
		//�w�肵���m�[�hroot���Aignore_ast_list�ɑ��݂��Ȃ����ǂ������ׂ邽�߂̃t���O
		int ignore_flag;
		//�Y������ϐ��̃|�C���^�������͔z��̎����𒲂ׂ�B
		int pointer_level, array_level;
		//�w�肵��IDLIST�Ɩ��O����ł��Y������ϐ��e�[�u���ւ̃A�h���X���擾����
		variable_table_data = searchVARIABLE_TABLE_LIST(root->idlist, root->content, vtlist);
		//�����A�Y������ϐ������������ꍇ
		if(variable_table_data != NULL){
			//�w�肵���m�[�hroot���Aignore_ast_list�ɑ��݂��Ȃ����ǂ������ׂ�
			ignore_flag = checkIgnoreASTList(root, ignore_ast_list);

			//�����A���݂��Ȃ���΁A�z��I�t�Z�b�g���X�g�ɒǉ�����
			if(ignore_flag == FAILED){
				getPointerLevelAndArrayLevelFromVARIABLE_TABLE(variable_table_data, &pointer_level, &array_level);

				CSTLString_assign(target_name, CSTLString_c_str(root->content));

				array_offset = new_ARRAY_OFFSET(target_name, target_statement, root, offset_list, pointer_level, array_level, NOT_VIA_ANPASAND, inc_dec_flag);

				//DEBUG_MODE���L���Ȏ��|�C���^����єz��ϐ��̊e�����̃I�t�Z�b�g�̏����o�͂���
				#ifdef DEBUG_MODE
					if(array_offset != NULL){
						printARRAY_OFFSET(array_offset);
					}
				#endif

				//�����array_offset_list�ɒǉ�����
				ARRAY_OFFSET_LIST_push_back_ref(array_offset_list, array_offset);
			}

		}
	}
	//��ɁA�A�h���X�Q�Ɖ��Z�q�A���̑��̉��Z�q������������G���[���o�͂��ċ����I��������B
	else if(CSTLString_compare_with_char(root->name, "address_ref") == 0 ||
		CSTLString_compare_with_char(root->name, "minus_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "plus_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "log_or_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "log_and_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "or_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "xor_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "and_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "eq_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "ne_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "lethan_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "gethan_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "leeq_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "geeq_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "left_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "right_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "mul_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "div_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "mod_expr") == 0){
		if(inc_dec_flag == VIA_INC){
			fprintf(stderr,"#%s#:%d:lvalue required as unary inclement operand",getFileName(), root->line);
		}else{
			fprintf(stderr,"#%s#:%d:lvalue required as unary declement operand",getFileName(), root->line);
		}
			exit(1);
	}
	else{
		for(ast_i = ASTList_begin(root->children);
			ast_i != ASTList_end(root->children);
			ast_i = ASTList_next(ast_i)){

				getArrayOffsetInIncDecInfo(ASTList_data(ast_i), function_information_list, vtlist, array_offset_list, ignore_ast_list, target_statement, inc_dec_flag);
		}
	}
}
/**
getUpperExpressionRelationNode�̓��������ł���B

@param target ���ؑΏۂƂȂ��Ă���ϐ�
@param root ���ؑΏۂ̃m�[�h
@param output �o�͂����ԐړI�Ɋ֌W���Ă���m�[�h�ւ̃A�h���X
@param mode ���ʂ𒲂ׂĂ��邩�A��ʂ𒲂ׂĂ��邩�̔��f�������t���O�B���ʂȂ�O�A��ʂȂ�P�Ƃ���B

@return �����������������ǂ����̃t���O�B���������ꍇ�͂P�A�����łȂ��ꍇ�͂O��Ԃ��B
*/
int getUpperExpressionRelationNode_Internal(AST *target, AST *root, AST **output, AST **output2, int *mode){
	ASTListIterator p;
	int success_flag = FAILED;

	//�������g�̃m�[�h�����ׂ�ꂽ��A��ʂ𒲂׎n�߂�
	if(root == target){
		*mode = 1;
	}
	//�����łȂ��ꍇ�͉��ʂ𒲂ב�����B
	else{
		for(p = ASTList_begin(root->children);
			p != ASTList_end(root->children);
			p = ASTList_next(p)){

			success_flag = getUpperExpressionRelationNode_Internal(target, ASTList_data(p), output, output2, mode);
			//�T�����I�������ꍇ�͂����őł��؂�B
			if(success_flag == SUCCESS){
				break;
			}
			//��ʂ𒲂ׂĂ���Ƃ����t���O�������Ă��鎞
			if(*mode == 1){
				//��ʃm�[�h��minus_expr�ł���ꍇ
				if(CSTLString_compare_with_char(root->name, "minus_expr") == 0){
					//���̃t���O���P�ɂ��邱�ƂŏI��������B
					success_flag = SUCCESS;

					//root�m�[�h�ւ̃A�h���X��output�֓��͂�����
					*output = root;

					//minus_expr������̃m�[�h������
					*output2 = ASTList_data(p);
				}
				//��ʃm�[�h�����̂悤�Ȃ��̂ł���ꍇ
				else if((CSTLString_compare_with_char(root->name, "primary_expression") == 0 ||
				CSTLString_compare_with_char(root->name, "array_access") == 0 ||
				CSTLString_compare_with_char(root->name, "direct_ref") == 0 ||
				CSTLString_compare_with_char(root->name, "plus_expr") == 0 ||
				CSTLString_compare_with_char(root->name, "log_or_expr") == 0 ||
				CSTLString_compare_with_char(root->name, "log_and_expr") == 0 ||
				CSTLString_compare_with_char(root->name, "or_expr") == 0 ||
				CSTLString_compare_with_char(root->name, "xor_expr") == 0 ||
				CSTLString_compare_with_char(root->name, "and_expr") == 0 ||
				CSTLString_compare_with_char(root->name, "eq_expr") == 0 ||
				CSTLString_compare_with_char(root->name, "ne_expr") == 0 ||
				CSTLString_compare_with_char(root->name, "lethan_expr") == 0 ||
				CSTLString_compare_with_char(root->name, "gethan_expr") == 0 ||
				CSTLString_compare_with_char(root->name, "leeq_expr") == 0 ||
				CSTLString_compare_with_char(root->name, "geeq_expr") == 0 ||
				CSTLString_compare_with_char(root->name, "left_expr") == 0 ||
				CSTLString_compare_with_char(root->name, "right_expr") == 0 ||
				CSTLString_compare_with_char(root->name, "mul_expr") == 0 ||
				CSTLString_compare_with_char(root->name, "div_expr") == 0 ||
				CSTLString_compare_with_char(root->name, "mod_expr") == 0)){

					//���̃t���O���P�ɂ��邱�ƂŏI��������B
					success_flag = SUCCESS;

					//root�m�[�h�ւ̃A�h���X��output�֓��͂�����
					*output = root;
					break;
				}
			}
		}
	}

	return success_flag;

}
/**
�|�C���^�̃I�t�Z�b�g�̌��ؑΏۂƂȂ��Ă���ϐ�������AST�m�[�htarget����A�ԐړI�ɂǂ̊֌W�̒��Ɉʒu���Ă��邩�ǂ����𒲂ׁA���̃m�[�h�̃A�h���Xoutput�Ƃ��ĕԂ��B
���̂Ƃ��Atarget��薾�炩�ɏ�ʂł���AST�m�[�hroot��ݒ肵�Ȃ���΂Ȃ�Ȃ��B
�܂��Aoutput��minus_expr�̏ꍇ�͂��̃|�C���^���ЂƂ������ӂ��E�ӂ��ǂ����𒲂ׂ邽�߂ɁA
���̃|�C���^�̈���̃m�[�h��output2�֑������B

@param target ���ؑΏۂƂȂ��Ă���ϐ�
@param root ���ؑΏۂ̃m�[�h
@param output �o�͂����ԐړI�Ɋ֌W���Ă���m�[�h�ւ̃A�h���X
@param output2 output��minus_expr�̏ꍇ�Aminus_expr���1���̃m�[�h�������ɑ�������
@return �����������������ǂ����̃t���O�B���������ꍇ�͂P�A�����łȂ��ꍇ�͂O��Ԃ��B
*/
int getUpperExpressionRelationNode(AST *target, AST *root, AST **output, AST **output2){
	int mode = 0;
	return getUpperExpressionRelationNode_Internal(target, root, output, output2, &mode);
}


/**
primary_expression�Ƃ��Ďw�肵��AST�m�[�hroot����A���̎��̉��ʂł��鎟�̃m�[�h����T���o���A���̃A�h���X��output�֏o�͂����A1��Ԃ��B

minus_expr, plus_expr, array_access, direct_ref, IDENTIFIER, primary_expression

�Ȃ��Aoutput�̓��e��NULL�ɂ��邱�ƂŁAroot��艺�ʂ̃m�[�h���炪�����̑ΏۂƂȂ�B
�܂��A�|�C���^�v�Z�̊֌W��A+-���Z���Z�q�������悤�Ȃ��̂�CONSTANT(�萔�j�������ꍇ�̂݁A-1��Ԃ��B
������Ȃ��ꍇ��0�ł���B

@param root �w�肵��AST�m�[�h
@param output ��L�̌������m�[�h�ւ̃A�h���X

@return ��L�̏����Œl��ԋp����B

*/
int searchExpressionOrPointeArrayOrIden(AST *root, AST **output){
	int success_flag = FAILED;
	ASTListIterator p;

	//�����̃m�[�h�����Ă����B�������邱�ƂŎ����̃m�[�h�������Ă�����ŏI��点�Ȃ��悤�ɂ���
	if(*output == NULL){
		*output = root;
	}
	//�����AIDENTIFIER��direct_ref��array_access�Aprimary_expression����сA
	//�C���N�������g�f�N�������g����������������΁Aoutput�ɐݒ肵�ĒT�����I��点��
	if(CSTLString_compare_with_char(root->name, "minus_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "plus_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "array_access") == 0 ||
		CSTLString_compare_with_char(root->name, "direct_ref") == 0 ||
		CSTLString_compare_with_char(root->name, "IDENTIFIER") == 0 ||
		CSTLString_compare_with_char(root->name, "primary_expression") == 0 ||
		CSTLString_compare_with_char(root->name, "inc_after_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "inc_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "dec_after_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "inc_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "assignment_expression") == 0 ||
		CSTLString_compare_with_char(root->name, "function_call") == 0){
			//root�Ɠ����m�[�h�ł͂Ȃ������ׂ�
			if(root != *output){
				*output = root;
				success_flag = SUCCESS;
			}
			//�����łȂ��ꍇ�́A�����̃m�[�h��T������
			else{
				for(p = ASTList_begin(root->children);
					success_flag == 0 && p != ASTList_end(root->children);
					p = ASTList_next(p)){
						success_flag = searchExpressionOrPointeArrayOrIden(ASTList_data(p), output);
				}
			}
		}
	//�����A�|�C���^�ȉ���primary�ȉ������Ă͂����Ȃ����������ꍇ�Asuccess_flag��-1�������ďI��点��
	else if(CSTLString_compare_with_char(root->name, "log_or_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "log_and_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "or_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "xor_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "and_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "eq_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "ne_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "lethan_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "gethan_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "leeq_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "geeq_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "left_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "right_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "mul_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "div_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "mod_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "CONSTANT") == 0 ){
			success_flag = -1;
		}
	//�����łȂ��ꍇ�́A�qAST�m�[�h�ɂ��Ă������Q�Ƃ��s��
	else{
		for(p = ASTList_begin(root->children);
			success_flag == FAILED && success_flag != -1 && p != ASTList_end(root->children);
			p = ASTList_next(p)){
				success_flag = searchExpressionOrPointeArrayOrIden(ASTList_data(p), output);
			}
	}

	return success_flag;
}

/**
direct_ref�Ƃ��Ďw�肵��AST�m�[�hroot����A���̎��̉��ʂł��鎟�̃m�[�h����T���o���A���̃A�h���X��output�֏o�͂����A1��Ԃ��B

IDENTIFIER array_access, direct_ref, IDENTIFIER, primary_expression
inc_after_expression, inc_expr, dec_after_expr, inc_expr
assignment_expression

�Ȃ��Aoutput�̓��e��NULL�ɂ��邱�ƂŁAroot��艺�ʂ̃m�[�h���炪�����̑ΏۂƂȂ�B
������Ȃ��ꍇ��0�ł���B

@param root �w�肵��AST�m�[�h
@param output ��L�̌������m�[�h�ւ̃A�h���X

@return ��L�̏����Œl��ԋp����B

*/
int searchPointerAccessOrIdentifierOrPrimary(AST *root, AST **output){
	int success_flag = FAILED;
	ASTListIterator p;
	//�����̃m�[�h�����Ă����B�������邱�ƂŎ����̃m�[�h�������Ă�����ŏI��点�Ȃ��悤�ɂ���
	if(*output == NULL){
		*output = root;
	}
	//�����AIDENTIFIER��direct_ref��array_access�Aprimary_expression��������΁Aoutput�ɐݒ肵�ĒT�����I��点��
	if(CSTLString_compare_with_char(root->name, "IDENTIFIER") == 0 ||
		CSTLString_compare_with_char(root->name, "direct_ref") == 0 ||
		CSTLString_compare_with_char(root->name, "array_access") == 0 ||
		CSTLString_compare_with_char(root->name, "primary_expression") == 0 ||
		CSTLString_compare_with_char(root->name, "inc_after_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "inc_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "dec_after_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "dec_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "assignment_expression") == 0 ||
		CSTLString_compare_with_char(root->name, "function_call") == 0){
			//root�Ɠ����m�[�h�ł͂Ȃ������ׂ�
			if(root != *output){
				*output = root;
				success_flag = SUCCESS;
			}
			//�����łȂ��ꍇ�́A�����̃m�[�h��T������
			else{
				for(p = ASTList_begin(root->children);
					success_flag == FAILED && p != ASTList_end(root->children);
					p = ASTList_next(p)){
						success_flag = searchPointerAccessOrIdentifierOrPrimary(ASTList_data(p), output);
				}
			}

		}
	//�����łȂ��ꍇ�́A�qAST�m�[�h�ɂ��Ă������Q�Ƃ��s��
	else{
		for(p = ASTList_begin(root->children);
			success_flag == FAILED && p != ASTList_end(root->children);
			p = ASTList_next(p)){
				success_flag = searchPointerAccessOrIdentifierOrPrimary(ASTList_data(p), output);
			}
	}

	return success_flag;
}

/**
direct_ref�Ƃ��Ďw�肵��AST�m�[�hroot����A�ȉ��̃m�[�h��T�������A�����AST���X�goutput�Ƃ��Ď擾����B

IDENTIFIER array_access, direct_ref, IDENTIFIER, primary_expression

�Ȃ��Aoutput�̓��e��NULL�ɂ��邱�ƂŁAroot��艺�ʂ̃m�[�h���炪�����̑ΏۂƂȂ�B
������Ȃ��ꍇ��0�ł���B

@param root �w�肵��AST�m�[�h
@param output ��L�̌������m�[�h�ւ̃A�h���X
@param getSize �擾�����l�̃T�C�Y��Ԃ����߂̕ϐ��B������Ȃ��ꍇ��0�ɂ����B

@return �Ȃ�
*/
void getPointerAccessOrIdentifierList(AST *root, AST ***output, int *getSize){

	ASTListIterator p;
	AST **temp;
	//�����AIDENTIFIER��direct_ref��array_access��������΁Aoutput�Ƃ������X�g�ɒǉ�����
	if(CSTLString_compare_with_char(root->name, "IDENTIFIER") == 0 ||
		CSTLString_compare_with_char(root->name, "direct_ref") == 0 ||
		CSTLString_compare_with_char(root->name, "array_access") == 0 ||
		CSTLString_compare_with_char(root->name, "primary_expression") == 0 ||
		CSTLString_compare_with_char(root->name, "inc_after_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "inc_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "dec_after_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "inc_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "assignment_expression") == 0 ||
		CSTLString_compare_with_char(root->name, "function_call") == 0){
			if(*getSize == 0){
				*output = malloc(sizeof(AST*));
				*output[0] = root;
				*getSize = 1;
			}else{
				temp = realloc(*output, sizeof(AST*) * (*getSize + 1));
				if(temp == NULL){
					fprintf(stderr,"�������s���ł��I\n");
					exit(1);
				}else{
					temp[*getSize] = root;
					*output = temp;

				}
				*getSize = *getSize + 1;
			}
	}else if(ASTList_size(root->children) == 0){
		return;
	}
	//�����łȂ��ꍇ�́A�qAST�m�[�h�ɂ��Ă������Q�Ƃ��s��
	else{
		for(p = ASTList_begin(root->children);
			p != ASTList_end(root->children);
			p = ASTList_next(p)){
				getPointerAccessOrIdentifierList(ASTList_data(p), output, getSize);
			}
	}
}

/**
���ʎq�̖��O����v����ϐ���ϐ����X�g����T���B���̂Ƃ��A��v����ϐ��𒲂ׂ���A�|�C���^�Ɣz��̎��������ׁA�I�t�Z�b�g���x���ȏ�ł���΁A
���������ƂɂȂ�A�P��Ԃ��B�����łȂ���΁A�O��Ԃ��B�܂��Aignore_ast_list�͖�������IDENTIFIER��AST�̃A�h���X���X�g�������邽�тɓo�^
�����B�����Aignore_ast_list�ɓo�^����Ă���m�[�h�Ȃ�A����͖��������B�܂��A������̂ɐ��������ꍇ�A���̊Y������ϐ��̔z�񃌃x����|
�C���^�̃��x�����Ԃ��B

@param identifier ���ʎq�̖��O
@param offset_level �I�t�Z�b�g���x��
@param variable_table_list �ϐ��e�[�u�����X�g
@param ignore_ast_list �|�C���^�ł̈ʒu�����؍ς݂ł���AIDENTIFIER�𖳎����邽�߂�AST�̃A�h���X���X�g
@param pointer_level �ϐ����X�g���猩�����ϐ��̃|�C���^���x��
@param array_level �ϐ����X�g���猩�����ϐ��̔z�񃌃x��

@return ���ʎq�̖��O����уI�t�Z�b�g���x���������𖞂����Ă���΂P��Ԃ��A�����łȂ���΂O��Ԃ��B
*/
int checkIdentifierPointerArrayLevel(AST *identifier,int offset_level, VARIABLE_TABLE_LIST *variable_table_list,
 ASTPOINTER_LIST *ignore_ast_list, int *pointer_level, int *array_level){
	int success_flag;

	VARIABLE_TABLE_LISTIterator vi;
	CSTLString *target;

	target = CSTLString_new();
	//ignore_ast_list����AST�m�[�h�̃A�h���Xidentifier���݂��邩�ǂ����̃t���O
	int ignore_flag;

	//�ϐ��e�[�u���f�[�^
	VARIABLE_TABLE *varidate_table_data = NULL;

	for(vi = VARIABLE_TABLE_LIST_begin(variable_table_list);
		vi != VARIABLE_TABLE_LIST_end(variable_table_list);
		vi = VARIABLE_TABLE_LIST_next(vi)){

		//���̕ϐ����Ɣ�r
		CSTLString_assign(target, CSTLString_c_str(VARIABLE_TABLE_LIST_data(vi)->variable_name));
		//�w�肵���ϐ����Ɣ�r���邽�߂Ƀ|�C���^��z��������L����S�č폜����
		deletePointerAndArraySynbol(target);

		//�w�肵���ϐ����ƕϐ����X�g�̕ϐ��̖��O����v���A�ϐ��X�R�[�v���Ɏ��܂��Ă���Ƃ�
		if(CSTLString_compare(identifier->content, target) == 0 &&
			IDLIST_compare_with(identifier->idlist, VARIABLE_TABLE_LIST_data(vi)->idlist) == 1){

			//���łɌ������Ă��Ȃ��ꍇ�͕ϐ��e�[�u���f�[�^�ɐݒ肷��
			if(varidate_table_data == NULL){
				varidate_table_data = VARIABLE_TABLE_LIST_data(vi);
			}
			//���łɐݒ肵�Ă��āA�u���b�N���x����������΁A�ϐ��e�[�u���f�[�^�ɐݒ肷��
			else if(varidate_table_data->block_level < VARIABLE_TABLE_LIST_data(vi)->block_level){
				varidate_table_data = VARIABLE_TABLE_LIST_data(vi);
			}
		}

	}

	if(varidate_table_data != NULL){
			//���ؑΏۂ̕ϐ�������|�C���^�̎�������сA�z��̎������v�Z����
		getPointerLevelAndArrayLevelFromVARIABLE_TABLE(varidate_table_data, pointer_level, array_level);

			//���ؑΏۂ̕ϐ�������̃|�C���^���x������єz��̎������I�t�Z�b�g���x���ȏ�ł���ꍇ
			if(offset_level <= *pointer_level + *array_level){
				//�w�肵��AST�A�h���Xidenfier���Aignore_ast_list�ɑ��݂��邩�ǂ������ׂ�B
				ignore_flag = checkIgnoreASTList(identifier, ignore_ast_list);

				//���؍ς݂�AST�m�[�h���X�g�ƈ�v���Ȃ��Ǝ������ꍇ
				if(ignore_flag == FAILED){
					//�����t���O�𗧂Ă�
					success_flag = SUCCESS;
				}
			}
	}
	CSTLString_delete(target);
	return success_flag;
}

/**
�֐��Ăяo��������AST�m�[�h���A�o�^����Ă���֐��Ɋւ�����Ɋ܂܂�Ă��邩�ǂ����𒲂ׁA�����A���̊֐��̃|�C���^���x�����I�t�Z�b�g���x���ƈ�v
�����ꍇ�́A�G���[���o�͂��A�����I��������B
@param call_function �֐��Ăяo��������AST�m�[�h
@param offset_level �I�t�Z�b�g���x��
@param function_information_list �֐��Ɋւ�����̃��X�g

@return �Ȃ�
 */
void checkCallFunction(AST *call_function, int offset_level, FUNCTION_INFORMATION_LIST *function_information_list){
	CSTLString *function_name = CSTLString_new();

	int pointer_level;

	//�֐������擾����
	getStringFromAST(function_name, ASTList_data(ASTList_begin(call_function->children)));
	//�֐��Ɋւ����񃊃X�g����A�֐��̃|�C���^���x�����擾����
	pointer_level = getPointerLevelFromFUNCTION_INFORMATION_LIST(function_name, function_information_list);
	//�����A���x�������킵����A�|�C���^�A�N�Z�X��z��ōs�����Ƃ��]�܂����Ȃ��̂ŃG���[���o�͂�����B
	if(pointer_level == offset_level){
		fprintf(stderr, "#%s#:%d:Shouldn't access from Function Call!!\n", getFileName(), call_function->line);
		fflush(stderr);
		exit(1);
	}
	//�ꎞ�I�ɓ��I�Ɋm�ۂ��Ă����֐������J��������
	CSTLString_delete(function_name);
}

/**
�w�肵��AST�m�[�hast_data��AST�A�h���X���X�gignore_ast_list�ɑ��݂��邩�ǂ����𒲂ׂ�B���݂���ꍇ�͂P���������B
���݂��Ȃ��ꍇ�́Aast_data�̃A�h���X��ignore_ast_list�ɒǉ�������A0��Ԃ��B
@param ast_data �w�肵��AST�m�[�h
@param ignore_ast_list ���ׂ�Ώۂ�AST�A�h���X���X�g

@return ���݂���ꍇ�͂P��Ԃ��A�����łȂ��ꍇ�͂O��Ԃ�
*/
int checkIgnoreASTList(AST *ast_data, ASTPOINTER_LIST *ignore_ast_list){
		//���؍ς݂�AST�m�[�h���X�g�ƈ�v���邩�ǂ������ׂ邽�߂̃C�e���[�^
		ASTPOINTER_LISTIterator ignore_iterator;

		//���؍ς݂�AST�m�[�h���X�g�ƈ�v���邩�ǂ������ׂ邽�߂̃t���O
		int ignore_flag = FAILED;

		//���؍ς݂�AST�m�[�h���X�g�ƈ�v���邩�ǂ������ׂ�
		for(ignore_iterator = ASTPOINTER_LIST_begin(ignore_ast_list);
			ignore_iterator != ASTPOINTER_LIST_end(ignore_ast_list);
			ignore_iterator = ASTPOINTER_LIST_next(ignore_iterator)){
				//�w�肵���ϐ��ƌ��؍ς݂�AST�m�[�h���X�g�ƃA�h���X�ň�v�����ꍇ�B�t���O�𗧂Ă�break����B
				if(*ASTPOINTER_LIST_data(ignore_iterator) == ast_data){
					ignore_flag = SUCCESS;
					break;
				}
			}

		//���؍ς݂�AST�m�[�h���X�g�ƈ�v���Ȃ��Ǝ������ꍇ
		if(ignore_flag == FAILED){
			//���̌��؂���AST�m�[�h�̃A�h���X�����؍ς݂�AST�m�[�h���X�g�ɓo�^����
			ASTPOINTER_LIST_push_back(ignore_ast_list, ast_data);
		}

		return ignore_flag;
}
/*
�w�肵���e�����̔z���|�C���^�̃I�t�Z�b�g���X�garray_offset�̓��e���o�͂���B

@param array_offset �o�͑Ώۂ̊e�����̔z���|�C���^�̃I�t�Z�b�g���X�g

@return �Ȃ�
*/
void printARRAY_OFFSET(ARRAY_OFFSET *array_offset){
	//�I�t�Z�b�g���X�g�ւ̃C�e���[�^
	OFFSET_LISTIterator off_list_i;
	int counter = 0;
	//�Ώۂ̃|�C���^��z�񖼂��o�͂���

	printf("------ARRAY_OFFSET_INFO------\n\n");
	printf("VARIABLE_NAME = \"%s\"\n", CSTLString_c_str(array_offset->variable_name));
	printf("TARGET_STATEMENT_LOCATION = \"%d\"\n", array_offset->target_statement->line);
	printf("ARRAY_LEVEL = \"%d\"\n", array_offset->array_level);
	printf("POINTER_LEVEL = \"%d\"\n", array_offset->pointer_level);
	printf("ANPASAND_FLAG = \"%d\"\n\n", array_offset->anpasand_flag);
	printf("INC_DEC_FLAG = ");
	if(array_offset->inc_dec_flag == VIA_INC){
		printf("\"VIA_INC\"\n\n");
	}else if(array_offset->inc_dec_flag == VIA_DEC){
		printf("\"VIA_DEC\"\n\n");
	}else{
		printf("\"NONE\"\n\n");
	}
	for(counter = 0,off_list_i = OFFSET_LIST_begin(array_offset->offset_list);
		off_list_i != OFFSET_LIST_end(array_offset->offset_list);
		counter++, off_list_i = OFFSET_LIST_next(off_list_i)){

			printf("OFFSET_LEVEL_%d = \"%s\"\n", counter, *OFFSET_LIST_data(off_list_i));

		}

	printf("-----------------------------\n\n");
}


/*
�w�肵���e�����̔z���|�C���^�̃I�t�Z�b�g���X�garray_offset�̓��e���o�͂���B

@param array_offset_list �o�͑Ώۂ̊e�����̔z���|�C���^�̃I�t�Z�b�g���̃��X�g

@return �Ȃ�
*/
void printARRAY_OFFSET_LIST(ARRAY_OFFSET_LIST *array_offset_list){
	//	//�I�t�Z�b�g���X�g�ւ̃C�e���[�^
	OFFSET_LISTIterator off_list_i;
	int offset_counter = 1;

	//�I�t�Z�b�g���̃��X�g�ւ̃C�e���[�^
	ARRAY_OFFSET_LISTIterator aoff_list_i;
	int aoffset_counter = 1;

	printf("------ARRAY_OFFSET_LIST_INFO------\n\n");

	for(aoff_list_i = ARRAY_OFFSET_LIST_begin(array_offset_list);
		aoff_list_i != ARRAY_OFFSET_LIST_end(array_offset_list);
		aoffset_counter++, aoff_list_i = ARRAY_OFFSET_LIST_next(aoff_list_i)){

			//�Ώۂ̃|�C���^��z�񖼂��o�͂���
			printf("------ARRAY_OFFSET_INFO_%d------\n\n", aoffset_counter);
			printf("VARIABLE_NAME = \"%s\"\n", CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name));
			printf("TARGET_STATEMENT_LOCATION = \"%d\"\n", ARRAY_OFFSET_LIST_data(aoff_list_i)->target_statement->line);
			printf("ARRAY_LEVEL = \"%d\"\n", ARRAY_OFFSET_LIST_data(aoff_list_i)->array_level);
			printf("POINTER_LEVEL = \"%d\"\n", ARRAY_OFFSET_LIST_data(aoff_list_i)->pointer_level);
			printf("ANPASAND_FLAG = \"%d\"\n", ARRAY_OFFSET_LIST_data(aoff_list_i)->anpasand_flag);
			printf("INC_DEC_FLAG = ");
			if(ARRAY_OFFSET_LIST_data(aoff_list_i)->inc_dec_flag == VIA_INC){
				printf("\"VIA_INC\"\n\n");
			}else if(ARRAY_OFFSET_LIST_data(aoff_list_i)->inc_dec_flag == VIA_DEC){
				printf("\"VIA_DEC\"\n\n");
			}else{
				printf("\"NONE\"\n\n");
			}
			//�|�C���^��z��̊e�����̃I�t�Z�b�g���o��
			for(off_list_i = OFFSET_LIST_begin(ARRAY_OFFSET_LIST_data(aoff_list_i)->offset_list);
				off_list_i != OFFSET_LIST_end(ARRAY_OFFSET_LIST_data(aoff_list_i)->offset_list);
				offset_counter++, off_list_i = OFFSET_LIST_next(off_list_i)){

					printf("OFFSET_LEVEL_%d = \"%s\"\n", offset_counter, *OFFSET_LIST_data(off_list_i));

				}

			printf("-----------------------------\n\n");

	}
	printf("-----------------------------------\n\n");

}

/**
�ϐ��e�[�u���f�[�^variable_table����I�t�Z�b�g���X�goffset_list�𐶐�����B

@param offset_list ������̃I�t�Z�b�g���X�g
@param variable_table �ϐ��e�[�u���f�[�^

@return �Ȃ�
*/
void getOFFSET_LISTFromVariableTable(OFFSET_LIST *offset_list, VARIABLE_TABLE *variable_table){
	//�ϐ��e�[�u���̃T�C�Y
	int variable_name_size = CSTLString_size(variable_table->variable_name);
	int location;

	//�e�v�f�̓��e
	char *offset;
	//�z����ɓ����Ă��邩�ǂ����̃t���O�@�O�F�����Ă��Ȃ��@�P�F�����Ă���
	int array_into = 0;
	int array_start, array_end;

	int str_extract_flag;
	//������𒲂ׂ�
	for(location = 0; location < variable_name_size; location++){
		//�����z��̊J�n������������A�z��ɓ����Ă����Ԃɂ��A�z��̓��e�̍ŏ��̈ʒu��ݒ肷��
		if(array_into == 0 && *CSTLString_at(variable_table->variable_name, location) == '['){
			array_start = location + 1;
			array_into = 1;
		}
		//�z��ɓ����Ă����Ԃł���A�z��̏I���������L�����������ꍇ
		else if( array_into == 1 && *CSTLString_at(variable_table->variable_name, location) == ']'){
			//�z��̏I���̈ʒu��ݒ肷��
			array_end = location - 1;

			//�z��̒��g���󂾂Ɣ��f�����ꍇ
			if(array_start > array_end || (array_start == array_end && *CSTLString_at(variable_table->variable_name, array_start) == ' ')){
				fprintf(stderr, "��̔z��ɂ͑Ή����Ă��܂���I\n");
				exit(1);
			}else{
				//��łȂ��Ɣ��f�����ꍇ�A�z��̓��e�𒊏o����B���̂Ƃ����o�Ɏ��s�����ꍇ�A�����G���[�Ƃ��ďo�͂��A�����I������
				offset = calloc(array_end - array_start + 1, sizeof(char));
				str_extract_flag = str_extract(offset, (char*)CSTLString_c_str(variable_table->variable_name), array_start, array_end - array_start);
				if(str_extract_flag == 0){
					fprintf(stderr, "�����G���[\n");
					exit(1);
				}

				//�z��̓��e���I�t�Z�b�g���X�g�ɂ����
				OFFSET_LIST_push_back_alloc(offset_list, offset);

				free(offset);
			}

			//�z��̊O�ɂ����ԂɕύX
			array_into = 0;
		}
	}
}

/**
�I�t�Z�b�g���X�goffset_list�̒��g�����S�ɉ��������B

@param offset_list ���������offset_list

@return �Ȃ�
*/
void deleteOFFSET_LIST(OFFSET_LIST *offset_list){
	OFFSET_LISTIterator off_list_i;
	//�I�t�Z�b�g���X�g���ɂ���e�v�f�̓��e���������
	for(off_list_i = OFFSET_LIST_begin(offset_list);
		off_list_i != OFFSET_LIST_end(offset_list);
		off_list_i = OFFSET_LIST_next(off_list_i)){

		free(*OFFSET_LIST_data(off_list_i));
	}

	//�I�t�Z�b�g���X�g���ɂ���S�v�f�ւ̃��X�g���������
	OFFSET_LIST_clear(offset_list);
	//�I�t�Z�b�g���X�g���̂��������
	OFFSET_LIST_delete(offset_list);
}
/**
�w�肵���z��I�t�Z�b�g����A���Z��̃|�C���^���x�������߂�B���Z��̃|�C���^���x���͂��̂Ƃ���ł���B
���Z��̃|�C���^���x�������̕ϐ��̔z��ƃ|�C���^���x���̍��v�l�{�A���p�T���h�t���O�i����ł���Ȃ�P�A�����łȂ��ꍇ�͂O�j�|���̔z��I�t�Z�b�g���̃I�t�Z�b�g���X�g
@param array_offset �w�肵���z��I�t�Z�b�g

@return ���߂����Z��̃|�C���^���x����Ԃ�
*/
int getOffsetLevelFromArrayOffset(ARRAY_OFFSET *array_offset){
	return array_offset->pointer_level + array_offset->array_level + array_offset->anpasand_flag - OFFSET_LIST_size(array_offset->offset_list);
}
/**
�w�肵���z��I�t�Z�b�g���X�g�ł̉��Z��̃|�C���^���x���̍ő僌�x���ł���z��I�t�Z�b�g�̃A�h���X�����߂�B�z��I�t�Z�b�g����̏ꍇ��NULL��������B
@param array_offset_list �w�肵���z��I�t�Z�b�g���X�g

@return ���߂����Z��̃|�C���^���x�����ő�ł���z��I�t�Z�b�g�̃A�h���X��Ԃ�
*/
ARRAY_OFFSET *maxOffsetLevelAddressFromArrayOffsetList(ARRAY_OFFSET_LIST *array_offset_list){
	ARRAY_OFFSET_LIST *aoff_list_i;
	ARRAY_OFFSET *max_array_offset;
	int max_pointer_level;
	int tmp_pointer_level;
	//�z��I�t�Z�b�g���X�g����łȂ��ꍇ
	if(ARRAY_OFFSET_LIST_size(array_offset_list) != 0){
		//�ŏ��̃��X�g���̉��Z��̃|�C���^���x�������߂�
		max_pointer_level = getOffsetLevelFromArrayOffset(ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(array_offset_list)));
		max_array_offset = ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(array_offset_list));
		//���X�g�����牉�Z��̃|�C���^���x���̍ő僌�x�������߂�
		for(aoff_list_i = ARRAY_OFFSET_LIST_next(ARRAY_OFFSET_LIST_begin(array_offset_list));
			aoff_list_i != ARRAY_OFFSET_LIST_end(array_offset_list);
			aoff_list_i = ARRAY_OFFSET_LIST_next(aoff_list_i)){

				tmp_pointer_level = getOffsetLevelFromArrayOffset(ARRAY_OFFSET_LIST_data(aoff_list_i));

				if(max_pointer_level < tmp_pointer_level){
					max_pointer_level = tmp_pointer_level;
					max_array_offset = ARRAY_OFFSET_LIST_data(aoff_list_i);
				}
		}
	}
	//�z��I�t�Z�b�g���X�g����̏ꍇ�́A�O��������
	else{
		max_pointer_level = 0;
		max_array_offset = NULL;
	}

	return max_array_offset;

}
/**
�w�肵���z��I�t�Z�b�g���X�g�ł̉��Z��̃|�C���^���x���̍ő僌�x�������߂�B�z��I�t�Z�b�g����̏ꍇ�͂O��������B
@param array_offset_list �w�肵���z��I�t�Z�b�g���X�g

@return ���߂����Z��̃|�C���^���x����Ԃ�
*/
int maxOffsetLevelFromArrayOffsetList(ARRAY_OFFSET_LIST *array_offset_list){
	ARRAY_OFFSET_LIST *aoff_list_i;
	int max_pointer_level;
	int tmp_pointer_level;
	//�z��I�t�Z�b�g���X�g����łȂ��ꍇ
	if(ARRAY_OFFSET_LIST_size(array_offset_list) != 0){
		//�ŏ��̃��X�g���̉��Z��̃|�C���^���x�������߂�
		max_pointer_level = getOffsetLevelFromArrayOffset(ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(array_offset_list)));

		//���X�g�����牉�Z��̃|�C���^���x���̍ő僌�x�������߂�
		for(aoff_list_i = ARRAY_OFFSET_LIST_next(ARRAY_OFFSET_LIST_begin(array_offset_list));
			aoff_list_i != ARRAY_OFFSET_LIST_end(array_offset_list);
			aoff_list_i = ARRAY_OFFSET_LIST_next(aoff_list_i)){

				tmp_pointer_level = getOffsetLevelFromArrayOffset(ARRAY_OFFSET_LIST_data(aoff_list_i));

				if(max_pointer_level < tmp_pointer_level){
					max_pointer_level = tmp_pointer_level;
				}
		}
	}
	//�z��I�t�Z�b�g���X�g����̏ꍇ�́A�O��������
	else{
		max_pointer_level = 0;
	}

	return max_pointer_level;

}

/**
�Ώۂ�AST�m�[�h����A���Z��̃|�C���^���x�����w�肳�ꂽ�|�C���^���x���Ɣz�񃌃x���̍��v�ƈ�v����悤��
�ϐ��̔z��I�t�Z�b�g���w�肳�ꂽ�z��I�t�Z�b�g���X�g����T���o���A����������A�h���X���擾����B

@param root �Ώۂ�AST�m�[�h
@param array_offset_list �Ώۂ̔z��I�t�Z�b�g���X�g
@param pointer_level �w�肷��|�C���^���x��
@param array_level �w�肷��z�񃌃x��

@return ���Z��̃|�C���^���x���Ǝw�肳�ꂽ�|�C���^���x���Ɣz�񃌃x���̍��v����v����悤�ȕϐ���Ԃ��B���s�����ꍇ��NULL��Ԃ��B
 */

ARRAY_OFFSET *searchOffsetLevelAddressFromArrayOffsetList(AST *root, ARRAY_OFFSET_LIST *array_offset_list,
		int pointer_level, int array_level){

	ARRAY_OFFSET *result = NULL;

	ASTListIterator ast_i;

	ARRAY_OFFSET_LISTIterator aoff_list_i;

	//AST�m�[�h���环�ʎq��T�����A���������ꍇ
	if(CSTLString_compare_with_char(root->name, "IDENTIFIER") == 0){
		//�z��I�t�Z�b�g���X�g����Y������ϐ���T��
		for(aoff_list_i = ARRAY_OFFSET_LIST_begin(array_offset_list);
			aoff_list_i != ARRAY_OFFSET_LIST_end(array_offset_list);
			aoff_list_i = ARRAY_OFFSET_LIST_next(aoff_list_i)){

			//�z��I�t�Z�b�g���X�g����Y������ϐ����������z��I�t�Z�b�g���������A
			//���̔z��I�t�Z�b�g��񂩂�̉��Z��̃|�C���^���x�����|�C���^���x���Ɣz�񃌃x���̍��v�ƈ�v�����ꍇ
			if(root == ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_address &&
					getOffsetLevelFromArrayOffset(ARRAY_OFFSET_LIST_data(aoff_list_i)) == pointer_level + array_level){
				//���̃A�h���X���擾���A�T�����I��������
				result = ARRAY_OFFSET_LIST_data(aoff_list_i);
				break;
			}

		}
	}
	//������Ȃ��ꍇ�́A�q�m�[�h�̒T�����s��
	//�z��I�t�Z�b�g�̃A�h���X���擾�ł���܂ŒT�����s��
	else{
		for(ast_i = ASTList_begin(root->children);
			result == NULL && ast_i != ASTList_end(root->children);
			ast_i = ASTList_next(ast_i)){
			result = searchOffsetLevelAddressFromArrayOffsetList(ASTList_data(ast_i), array_offset_list, pointer_level, array_level);
		}
	}

	return result;
}

/**
�w�肵��������A�K�v�ȃI�t�Z�b�g�����擾����B
@param expression �w�肵�����Ɋւ���AST�m�[�h
@param function_information_list �֐��Ɋւ�����̃��X�g
@param vtlist ���ؑΏۂ̎����}�[�N���邽�߂̕ϐ����X�g
@param ignore_ast_list �|�C���^�ł̈ʒu�����؍ς݂ł���AIDENTIFIER�𖳎����邽�߂�AST�̃A�h���X���X�g
@param array_offset_list �e�|�C���^����єz�񂲂Ƃ̃I�t�Z�b�g�̃��X�g
@param target_expression ���̍��ӎ��̏�ʂɈʒu����AST�m�[�h
@param switch_mode ���ڃA�N�Z�X����єz��A�N�Z�X��T�����AIDENTIFIER��T�����ǂ����̃X�C�b�`�t���O �O�F�����������@�P�Fdirect_ref��array_access�̂ݒT��
@param allow_subeffect ����p�̎����������ǂ����̃t���O �P�F���� �O�F�����Ȃ�
@return �Ȃ�
*/
void getExpressionOffsetInfo(AST *expression, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist, ASTPOINTER_LIST *ignore_ast_list,
 ARRAY_OFFSET_LIST * array_offset_list, AST *target_expression, int *switch_mode, int allow_subeffect){
	ASTListIterator p;
	int pointer_level, array_level;
	//direct_ref�����array_access����������A�P���ȍ~�̃��x�����m�F����
	if(CSTLString_compare_with_char(expression->name, "direct_ref") == 0 ||
		CSTLString_compare_with_char(expression->name, "array_access") == 0){
		ARRAY_OFFSET *array_offset = NULL;
		//�|�C���^����єz��ϐ��̊e�����̃I�t�Z�b�g�����߂�
		getPointerArrayOffset(expression, function_information_list, vtlist, 0, ignore_ast_list, &array_offset, target_expression, NOT_VIA_ANPASAND, NOT_INC_DEC);

		//DEBUG_MODE���L���Ȏ��|�C���^����єz��ϐ��̊e�����̃I�t�Z�b�g�̏����o�͂���
		#ifdef DEBUG_MODE
			if(array_offset != NULL){
				printARRAY_OFFSET(array_offset);
			}
		#endif
		//�|�C���^����єz��ϐ��̊e�����̃I�t�Z�b�g�̏�񂪎擾�ł����ꍇ�A����Ɋւ���������̏��̃��X�g�֓����
		if(array_offset != NULL){
			ARRAY_OFFSET_LIST_push_back_ref(array_offset_list, array_offset);
		}
		//�X�C�b�`�t���O���P�ɂ���
		*switch_mode = 1;
	}
	//�X�C�b�`�t���O���O�ł���AIDENTIFIER�����������ꍇ
	else if(*switch_mode == 0 && CSTLString_compare_with_char(expression->name, "IDENTIFIER") == 0 ){
		//�I�t�Z�b�g��񂪂Ȃ�array_offset���쐬����B
		ARRAY_OFFSET *array_offset;
		VARIABLE_TABLE *variable_table_data;
		OFFSET_LIST *offset_list = OFFSET_LIST_new();
		CSTLString *target_name = CSTLString_new();
		int ignore_flag;

		//�w�肵��IDLIST�Ɩ��O����ł��Y������ϐ��e�[�u���ւ̃A�h���X���擾����
		variable_table_data = searchVARIABLE_TABLE_LIST(expression->idlist, expression->content, vtlist);
		if(variable_table_data != NULL){
			//�w�肵���m�[�hexpression���Aignore_ast_list�ɑ��݂��Ȃ����ǂ������ׂ�
			ignore_flag = checkIgnoreASTList(expression, ignore_ast_list);

			//�����A���݂��Ȃ���΁A�z��I�t�Z�b�g���X�g
			if(ignore_flag == FAILED){
				getPointerLevelAndArrayLevelFromVARIABLE_TABLE(variable_table_data, &pointer_level, &array_level);

				CSTLString_assign(target_name, CSTLString_c_str(expression->content));

				array_offset = new_ARRAY_OFFSET(target_name, target_expression, expression, offset_list, pointer_level, array_level, NOT_VIA_ANPASAND, NOT_INC_DEC);

				//DEBUG_MODE���L���Ȏ��|�C���^����єz��ϐ��̊e�����̃I�t�Z�b�g�̏����o�͂���
				#ifdef DEBUG_MODE
					if(array_offset != NULL){
						printARRAY_OFFSET(array_offset);
					}
				#endif

				//�����array_offset_list�ɒǉ�����
				ARRAY_OFFSET_LIST_push_back_ref(array_offset_list, array_offset);
			}
		}else{
			fprintf(stderr,"#%s#:%d: variable %s is undeclarated!!\n",getFileName(), expression->line, CSTLString_c_str(expression->content));
			exit(1);
		}

	}
	//�C���N�������g���Z�q�������ꍇ�́A�C���N�������g��ʂ����z��I�t�Z�b�g���X�g���擾����
	else if(CSTLString_compare_with_char(expression->name, "inc_expr") == 0 ||
		CSTLString_compare_with_char(expression->name, "inc_after_expr") == 0){
		//����p���������ꍇ�́A�C���N�������g��ʂ����z��I�t�Z�b�g���X�g���擾����
		if(allow_subeffect == ALLOW_SUBEFF){
			getArrayOffsetInIncDecInfo(expression, function_information_list, vtlist,
								array_offset_list, ignore_ast_list, target_expression, VIA_INC);
		}
		//�����łȂ��ꍇ�́A�]�܂����Ȃ������Ƃ݂Ȃ��A�����I��������
		else{
			fprintf(stderr,"#%s#:%d: This Expression is NOT arrow to contain Inclement expression!!\n",getFileName(), expression->line);
			exit(1);
		}
	}
	//�f�N�������g���Z�q�������ꍇ�́A�C���N�������g��ʂ����z��I�t�Z�b�g���X�g���擾����
	else if(CSTLString_compare_with_char(expression->name, "dec_expr") == 0 ||
		CSTLString_compare_with_char(expression->name, "dec_after_expr") == 0){
		//����p���������ꍇ�́A�C���N�������g��ʂ����z��I�t�Z�b�g���X�g���擾����

		if(allow_subeffect == ALLOW_SUBEFF){
			getArrayOffsetInIncDecInfo(expression, function_information_list, vtlist,
								array_offset_list, ignore_ast_list, target_expression, VIA_DEC);
		}
		//�����łȂ��ꍇ�́A�]�܂����Ȃ������Ƃ݂Ȃ��A�����I��������
		else{
			fprintf(stderr,"#%s#:%d: This Expression is NOT arrow to contain Inclement expression!!\n",getFileName(), expression->line);
			exit(1);
		}
	}
	//�qAST�m�[�h���Q�Ƃ���
	for(p = ASTList_begin(expression->children);
		p != ASTList_end(expression->children);
		p = ASTList_next(p)){
			getExpressionOffsetInfo(ASTList_data(p), function_information_list, vtlist, ignore_ast_list, array_offset_list, target_expression, switch_mode, allow_subeffect);
	}

}

/**
�w�肵����������A�K�v�ȃI�t�Z�b�g�����擾����B
@param argument �w�肵�������Ɋւ���AST�m�[�h
@param function_information_list �֐��Ɋւ�����̃��X�g
@param vtlist ���ؑΏۂ̎����}�[�N���邽�߂̕ϐ����X�g
@param ignore_ast_list �|�C���^�ł̈ʒu�����؍ς݂ł���AIDENTIFIER�𖳎����邽�߂�AST�̃A�h���X���X�g
@param array_offset_list �e�|�C���^����єz�񂲂Ƃ̃I�t�Z�b�g�̃��X�g
@param target_expression ���̍��ӎ��̏�ʂɈʒu����AST�m�[�h
@param switch_mode ���ڃA�N�Z�X����єz��A�N�Z�X��T�����AIDENTIFIER��T�����ǂ����̃X�C�b�`�t���O �O�F�����������@�P�Fdirect_ref��array_access�̂ݒT��
@return �Ȃ�
*/
void getArgumentOffsetInfo(AST *argument, FUNCTION_INFORMATION_LIST *function_information_list,
		VARIABLE_TABLE_LIST *vtlist, ASTPOINTER_LIST *ignore_ast_list, ARRAY_OFFSET_LIST * array_offset_list,
		AST *target_expression, int *switch_mode){

	getExpressionOffsetInfo(argument, function_information_list, vtlist, ignore_ast_list, array_offset_list, target_expression, switch_mode, DENIDE_SUBEFF);

}

/**
�w�肵��������A�K�v�ȃI�t�Z�b�g�����擾����B����͕���p�̎��������B
@param expression �w�肵�����Ɋւ���AST�m�[�h
@param function_information_list �֐��Ɋւ�����̃��X�g
@param vtlist ���ؑΏۂ̎����}�[�N���邽�߂̕ϐ����X�g
@param ignore_ast_list �|�C���^�ł̈ʒu�����؍ς݂ł���AIDENTIFIER�𖳎����邽�߂�AST�̃A�h���X���X�g
@param array_offset_list �e�|�C���^����єz�񂲂Ƃ̃I�t�Z�b�g�̃��X�g
@param target_expression ���̍��ӎ��̏�ʂɈʒu����AST�m�[�h
@param switch_mode ���ڃA�N�Z�X����єz��A�N�Z�X��T�����AIDENTIFIER��T�����ǂ����̃X�C�b�`�t���O �O�F�����������@�P�Fdirect_ref��array_access�̂ݒT��
@return �Ȃ�
*/
void getSingleExpressionOffsetInfo(AST *expression, FUNCTION_INFORMATION_LIST *function_information_list,
		VARIABLE_TABLE_LIST *vtlist, ASTPOINTER_LIST *ignore_ast_list,
 ARRAY_OFFSET_LIST * array_offset_list, AST *target_expression, int *switch_mode){
 	getExpressionOffsetInfo(expression, function_information_list, vtlist, ignore_ast_list, array_offset_list, target_expression, switch_mode, ALLOW_SUBEFF);
 }

/**
�z��I�t�Z�b�g��񂩂�A�C�ӂ̎����܂ł̔z�񎮂𐶐�����B

@param output �z�񎮂𐶐�����镶����
@param array_offset �Ώۂ̔z��I�t�Z�b�g
@param output_level �o�͂���������(���̂Ƃ��A�z��I�t�Z�b�g�𒴂���l����ꂽ�ꍇ�́A�z��I�t�Z�b�g�������܂ł̔z�񎮂��o�͂���)

@return �Ȃ�
*/

void createArrayExpression(CSTLString *output, ARRAY_OFFSET *array_offset, int output_level){
	//�I�t�Z�b�g���X�g�̃C�e���[�^
	OFFSET_LISTIterator off_list_i;
	//�������J�E���g����J�E���^
	int counter;

	//�ϐ������ɑ������
	CSTLString_assign(output, CSTLString_c_str(array_offset->variable_name));

	//�J�b�R���̎���ǉ����Ă���
	for(counter = 0, off_list_i = OFFSET_LIST_begin(array_offset->offset_list);
		counter < output_level && off_list_i != OFFSET_LIST_end(array_offset->offset_list);
		counter++, off_list_i = OFFSET_LIST_next(off_list_i)){
			CSTLString_printf(output, 1, "[ %s ]", *OFFSET_LIST_data(off_list_i));
		}

}

/**
�z��I�t�Z�b�g��񂩂�A���ؗp�ϐ��Ɏg����z�񎮂𐶐����A�I�t�Z�b�g���x����Ԃ��B
@param output ������̕�����
@param array_offset �Ώۂ̔z��I�t�Z�b�g

@return �z��I�t�Z�b�g��񂩂琶�����ꂽ�I�t�Z�b�g���x����Ԃ��B
 */
int createValidateVariableArrayExpression(CSTLString *output, ARRAY_OFFSET *array_offset){
	int offset_level_counter;

	OFFSET_LISTIterator off_list_i;

	CSTLString *basis_location_content = CSTLString_new();
	CSTLString *array_string = CSTLString_new();


	//�|�C���^�Ɣz��̋L�����폜����
	deletePointerAndArraySynbol(output);

	//�z��I�t�Z�b�g��񂩂�A�z�񎮕������o�͂���
	for(offset_level_counter = 1, off_list_i = OFFSET_LIST_begin(array_offset->offset_list);
		off_list_i != OFFSET_LIST_end(array_offset->offset_list);
		offset_level_counter++, off_list_i = OFFSET_LIST_next(off_list_i)){

		//���̃��x���̂��߂̔z��𐶐�����B
		CSTLString_printf(basis_location_content, 0, "basis_location_%d_%s%s", offset_level_counter, (char*)CSTLString_c_str(array_offset->variable_name), (char*)CSTLString_c_str(array_string));
		CSTLString_printf(array_string, 1," [ %s + %s ]", *OFFSET_LIST_data(off_list_i), (char*)CSTLString_c_str(basis_location_content));

	}

	//�ϐ����ɔz�񎮂�ǉ�����
	CSTLString_printf(output, 1, "%s", CSTLString_c_str(array_string));

	//���̂Ƃ��̃I�t�Z�b�g���x����Ԃ�
	return offset_level_counter;
}

/**
�z��I�t�Z�b�g���X�gfromlist����move_start�ȍ~�̃f�[�^�����ׂāA��������̔z��I�t�Z�b�g���X�gtolist�Ɉړ�������B
@param fromlist �ړ����Ƃ̔z��I�t�Z�b�g���X�g
@param tolist �ړ���̔z��I�t�Z�b�g���X�g
@param move_start �ړ����������f�[�^�̈ʒu(�擪����O�ԖڂƂ���)

@return �Ȃ�
 */
void moveArrayOffsetList(ARRAY_OFFSET_LIST *fromlist, ARRAY_OFFSET_LIST *tolist, int move_start){
	ARRAY_OFFSET_LISTIterator aoff_i;
	int i;
	int count = 0;
	//�ړ��ʒu�����̒l�̏ꍇ�̓G���[���o�͂��A�����I��������
	if(move_start < 0){
		fprintf(stderr,"%d:�z��I�t�Z�b�g�̓������l���s���ł�!\n");
		exit(1);
	}else{
		//�ړ������Ă�������𐔂��Ȃ���fromlist�̃f�[�^��tolist�ɒǉ�����
		for(aoff_i = ARRAY_OFFSET_LIST_begin(fromlist);
			aoff_i != ARRAY_OFFSET_LIST_end(fromlist);
			aoff_i = ARRAY_OFFSET_LIST_next(aoff_i)){
				//�ړ����������f�[�^�̈ʒu��0�ɂȂ�΁A��������f�[�^���ړ�������
				if(move_start == 0){
					ARRAY_OFFSET_LIST_push_back_ref(tolist, ARRAY_OFFSET_LIST_data(aoff_i));
					count++;
				}else{
					move_start--;
				}
		}
		//��������ړ������������폜����
		for(i = 0; i < count; i++){
			ARRAY_OFFSET_LIST_pop_back(fromlist);
		}
	}
}
/**
�z��I�t�Z�b�g���X�gfromlist����move_start�ȍ~�̃f�[�^�����ׂāA��������̔z��I�t�Z�b�g���X�gtolist�ɃR�s�[������B
@param fromlist �R�s�[���̔z��I�t�Z�b�g���X�g
@param tolist �R�s�[��̔z��I�t�Z�b�g���X�g
@param move_start �ړ����������f�[�^�̈ʒu(�擪����O�ԖڂƂ���)

@return �Ȃ�
 */
void copyArrayOffsetList(ARRAY_OFFSET_LIST *fromlist, ARRAY_OFFSET_LIST *tolist, int move_start){
	ARRAY_OFFSET_LISTIterator aoff_i;
	int i;
	//�ړ��ʒu�����̒l�̏ꍇ�̓G���[���o�͂��A�����I��������
	if(move_start < 0){
		fprintf(stderr,"%d:�z��I�t�Z�b�g�̓������l���s���ł�!\n");
		exit(1);
	}else{
		//�R�s�[�����Ă�������𐔂��Ȃ���fromlist�̃f�[�^��tolist�ɒǉ�����
		for(aoff_i = ARRAY_OFFSET_LIST_begin(fromlist);
			aoff_i != ARRAY_OFFSET_LIST_end(fromlist);
			aoff_i = ARRAY_OFFSET_LIST_next(aoff_i)){
				//�R�s�[���������f�[�^�̈ʒu��0�ɂȂ�΁A��������f�[�^���ړ�������
				if(move_start == 0){
					ARRAY_OFFSET_LIST_push_back_ref(tolist,
							new_ARRAY_OFFSET_char((char *)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_i)->variable_name),
									ARRAY_OFFSET_LIST_data(aoff_i)->target_statement,
									ARRAY_OFFSET_LIST_data(aoff_i)->variable_address,
									ARRAY_OFFSET_LIST_data(aoff_i)->offset_list,
									ARRAY_OFFSET_LIST_data(aoff_i)->pointer_level,
									ARRAY_OFFSET_LIST_data(aoff_i)->array_level,
									ARRAY_OFFSET_LIST_data(aoff_i)->anpasand_flag,
									ARRAY_OFFSET_LIST_data(aoff_i)->inc_dec_flag)
									);
				}else{
					move_start--;
				}
		}
	}
}

/**
�ϐ��e�[�u������A�ϐ��̒�`�ɑ΂���m�[�h�ɊY���������T���A����ɑ΂���z��I�t�Z�b�g�����擾����B
@param declarator_array_offset_list �擾��̔z��I�t�Z�b�g���
@param declarator_expression �ϐ���`�܂ł�AST�A�h���X
@param target_expression �Ώۂ�declarator_with_init�ւ�AST�A�h���X
@param vtlist ���ׂ��̕ϐ��e�[�u��

@return �Ȃ�
*/
void getDeclaratorArrayOffset(ARRAY_OFFSET_LIST *declarator_array_offset_list, AST *declarator_expression, AST *target_expression, VARIABLE_TABLE_LIST *vtlist){

	//�ϐ��̃|�C���^���x����z�񃌃x��
	int pointer_level, array_level;

	//�ϐ������쐬����
	CSTLString *variable_name = CSTLString_new();
	getStringFromAST(variable_name, declarator_expression);

	//�ϐ��e�[�u���𒲂ׂ�
	VARIABLE_TABLE *variable_table_data = NULL;
	variable_table_data = searchVARIABLE_TABLE_LIST(target_expression->idlist, variable_name, vtlist);

	//�ϐ�������|�C���^��z��������L�����폜����
	deletePointerAndArraySynbol(variable_name);

	//�����A�ϐ��e�[�u������Y������ϐ������擾�ł�����
	if(variable_table_data != NULL){

		getPointerLevelAndArrayLevelFromVARIABLE_TABLE(variable_table_data, &pointer_level, &array_level);

		//OFFSET_LIST(��)�𐶐�
		OFFSET_LIST *offset_list = OFFSET_LIST_new();
		//ARRAY_OFFSET�𐶐�
		ARRAY_OFFSET *new_array_offset = new_ARRAY_OFFSET(variable_name, target_expression, target_expression,
								offset_list, pointer_level, array_level, NOT_VIA_ANPASAND, NOT_INC_DEC);

		//�z��I�t�Z�b�g���X�g�ɒǉ�
		ARRAY_OFFSET_LIST_push_back_ref(declarator_array_offset_list, new_array_offset);
	}
	//�ł��Ȃ�������A�G���[���o�͂��ďI������B
	else{
		fprintf(stderr,"#%s#:%d:Undefine IDENTIFIRE is %s!\n", getFileName(), target_expression->line, CSTLString_c_str(variable_name));
		exit(1);
	}
}

/**
�z��I�t�Z�b�g���X�garray_offset_list����A�w�肵���ϐ�����T�����A
������΂��̕ϐ����ւ̃A�h���X��Ԃ��B

@param array_offset_list �T���Ώۂ̔z��I�t�Z�b�g���X�g
@param name �T���������ϐ���

@return ������Εϐ����ւ̃A�h���X��Ԃ��B�����łȂ����NULL��Ԃ��B
 */
ARRAY_OFFSET *searchARRAY_OFFSET_LIST(ARRAY_OFFSET_LIST *array_offset_list, CSTLString *name){

	ARRAY_OFFSET_LISTIterator a_i;
	ARRAY_OFFSET *result = NULL;
	//�z��I�t�Z�b�g���̕ϐ������r����̂Ɏg�p����ϐ�
	CSTLString *aol_vname = CSTLString_new();
	//�T���������ϐ������r����̂Ɏg�p����ϐ�
	CSTLString *s_vname = CSTLString_new();

	for(a_i = ARRAY_OFFSET_LIST_begin(array_offset_list);
		a_i != ARRAY_OFFSET_LIST_end(array_offset_list);
		a_i = ARRAY_OFFSET_LIST_next(a_i)){

		CSTLString_assign(aol_vname, CSTLString_c_str(ARRAY_OFFSET_LIST_data(a_i)->variable_name));
		CSTLString_assign(s_vname, CSTLString_c_str(name));

		//�ϐ����ȊO�̕����i�����ԍ������������Ȃǁj����������
		CSTLString_delete_tail_str(aol_vname, "#");
		CSTLString_delete_tail_str(s_vname, "#");
		//�z��I�t�Z�b�g���X�g���̕ϐ����ƒT���Ă���ϐ����̖��O����v�����ꍇ�Aresult�ɂ��̃f�[�^�������A�I������
		if(CSTLString_compare(aol_vname, s_vname) == 0){
			result = ARRAY_OFFSET_LIST_data(a_i);
			break;
		}
	}

	//��r�p�Ɏg�p���Ă����ϐ����J��������
	CSTLString_delete(aol_vname);
	CSTLString_delete(s_vname);
	return result;
}

/**
�Ώۂ̔z��I�t�Z�b�g���X�gtarget_array_offset_list�ɑ΂��āA�Ώۂ����菜������
�z��I�t�Z�b�g���X�gdelete_array_offset_list�̖��O�ɊY������z��I�t�Z�b�g����
�폜����B

@param target_array_offset_list �Ώۂ̔z��I�t�Z�b�g���X�g
@param delete_array_offset_list �Ώۂ����菜�������z��I�t�Z�b�g���X�g

@return �Ȃ�
 */
void minusArrayOffsetList(ARRAY_OFFSET_LIST *target_array_offset_list, ARRAY_OFFSET_LIST *delete_array_offset_list){

	ARRAY_OFFSET_LISTIterator d_aoff_i, t_aoff_i;

	//delete_array_offset_list����ϐ�����1�����o��
	for(d_aoff_i = ARRAY_OFFSET_LIST_begin(delete_array_offset_list);
		d_aoff_i != ARRAY_OFFSET_LIST_end(delete_array_offset_list);
		d_aoff_i = ARRAY_OFFSET_LIST_next(d_aoff_i)){

		//delete_array_offset_list�ɍ폜�������z�񂪑��݂��Ȃ����ǂ����T��
			for(t_aoff_i = ARRAY_OFFSET_LIST_begin(target_array_offset_list);
				t_aoff_i != ARRAY_OFFSET_LIST_end(target_array_offset_list);
				){

				//��������A�Y������z��I�t�Z�b�g�����폜����
				if(CSTLString_compare(ARRAY_OFFSET_LIST_data(t_aoff_i)->variable_name, ARRAY_OFFSET_LIST_data(d_aoff_i)->variable_name) == 0){
					deleteOFFSET_LIST(ARRAY_OFFSET_LIST_data(t_aoff_i)->offset_list);
					CSTLString_delete(ARRAY_OFFSET_LIST_data(t_aoff_i)->variable_name);

					t_aoff_i = ARRAY_OFFSET_LIST_erase(target_array_offset_list, t_aoff_i);
					continue;
				}
				t_aoff_i = ARRAY_OFFSET_LIST_next(t_aoff_i);
			}
	}

}

/**
�z��I�t�Z�b�g���X�g�ɔz��I�t�Z�b�g����ǉ�����B�������A�ϐ������d������̂ł���΁A�ǉ����Ȃ��B

@param target_array_offset_list �ǉ���̔z��I�t�Z�b�g���X�g
@param array_offset �ǉ�����z��I�t�Z�b�g���

@return �Ȃ�
 */
void ARRAY_OFFSET_LIST_push_back_ref_not_dup(ARRAY_OFFSET_LIST *target_array_offset_list, ARRAY_OFFSET *array_offset){
	int dup_flag = 0;

	ARRAY_OFFSET_LISTIterator a_i;

	//�z��I�t�Z�b�g���X�g�ɒǉ�����z��I�t�Z�b�g���ɁA�������O���Ȃ����ǂ������ׂ�
	for(a_i = ARRAY_OFFSET_LIST_begin(target_array_offset_list);
		a_i != ARRAY_OFFSET_LIST_end(target_array_offset_list);
		a_i = ARRAY_OFFSET_LIST_next(a_i)){

		//�����A�d�����閼�O�����݂���΁A�T�����I��������
		if(CSTLString_compare(ARRAY_OFFSET_LIST_data(a_i)->variable_name, array_offset->variable_name) == 0){
			dup_flag = 1;
			break;
		}
	}

	//�����A�z��I�t�Z�b�g���X�g����d������z��I�t�Z�b�g��񂪑��݂��Ȃ���΁A�ǉ�����
	if(dup_flag == 0){
		ARRAY_OFFSET_LIST_push_back_ref(target_array_offset_list, array_offset);
	}
}

/**
AST�̃|�C���^���X�g�̓��e���o�͂�����B

@param astpointer_list AST�̃|�C���^���X�g

@return �Ȃ�
 */
void printASTPOINTER_LIST(ASTPOINTER_LIST *astpointer_list){
	ASTPOINTER_LISTIterator a_i;

	for(a_i = ASTPOINTER_LIST_begin(astpointer_list);
		a_i != ASTPOINTER_LIST_end(astpointer_list);
		a_i = ASTPOINTER_LIST_next(a_i)){

		//�|�C���^�̃A�h���X�E�s���E�m�[�h�����o�͂�����
		printf("�E%p line = %d %s\n", *ASTPOINTER_LIST_data(a_i), (*ASTPOINTER_LIST_data(a_i))->line,
				CSTLString_c_str((*ASTPOINTER_LIST_data(a_i))->name));
	}
}
