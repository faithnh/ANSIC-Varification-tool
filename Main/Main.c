/*
 * Main.c
 *
 *  Created on: 2010/11/29
 *      Author: faithnh
 */
#include<stdio.h>
#include<stdlib.h>

#include "Help.h"

#include "../ANSICInformation/AST.h"
#include "../Library/CSTLString.h"
#include "../ANSICInformation/Synbol.h"
#include "../ANSICInformation/Varidate_Statement.h"
#include "../ANSICInformation/PreProcess.h"
#include "../Library/StoreInformation.h"
#include "../ANSICInformation/ForInformation.h"
#include "../ANSICInformation/FunctionInformation.h"
#include "../Library/FlagDatabase.h"
#include"../ANSICInformation/y.tab.h"
#include"../ANSICInformation/DivitionDeclarator.h"

#include"../ProgramSlicing/ProgramSlicing.h"

#define ENABLE_ARGUMENT 2
#define FILE_PATH 512
int main(int argc, char *argv[]){

	char preprocess_file_name[FILE_PATH];
	char output_file_name[FILE_PATH];

	FILE *target_source_file, *output;

	TYPEDEF_TABLE_LIST *typedef_table_list_zen, *typedef_table_list;
	STRUCT_TABLE_LIST *struct_table_list;
	VARIABLE_TABLE_LIST *variable_table_list_zen, *variable_table_list;
	ValidateVariableList *varidate_variable_list;
	ValidateStatementList *validate_statement_list;
	INCLUDE_LIST *include_list;
	ForInformationList *for_information_list;
	FUNCTION_INFORMATION_LIST *function_information_list;
	EXPR_SLICING_LIST *expr_slicing_list;
	AST *pre_programAST, *programAST;

	//�t���O�f�[�^�x�[�X�̐ݒ�
	int flag_database = getFlagDatabase(argc, argv);

	//�w���v���[�h���܂܂�Ă�����w���v�����\��������
	if(isHelpMode(flag_database)){
		viewHelp();
	}
	//�����łȂ���΁A���؎��t�������ɐi�߂�
	else{
		int i;

		//�t���O���΂�
		for(i = 1;i < argc && strlen(argv[i]) >= 2 && ( argv[i][0] == '-' && argv[i][1] == '-' ); i++);
		if(i == argc){
			fprintf(stderr, "�J���t�@�C���������݂��܂���I\n");
			exit(1);
		}

		if(argc >= ENABLE_ARGUMENT){
				//�t�@�C������ݒ肷��i����͑��̃G���[�����ȂǂŃt�@�C������\��������悤�ɂ��邽�߂ɕK�v�j
					setFileName(argv[i]);

					//�O�����ɐ��������ꍇ
					if(preProcesser(argv[i])){

						//�v���v���Z�X��̃t�@�C�����̐ݒ�
						snprintf(preprocess_file_name, FILE_PATH, "%s_out.c_pre.c", argv[i]);

						//�C���N���[�h�t�@�C�����X�g���擾
						include_list = INCLUDE_LIST_new();
						readIncludeDataFromFile(preprocess_file_name, include_list);

						target_source_file = fopen(preprocess_file_name, "r");

						if(target_source_file != NULL){

							//��������ϐ��錾�̕�������

							pre_programAST = parserANSIC(target_source_file, &typedef_table_list_zen);

							//AST�m�[�h�ɁA�ԋp�̌^���E�u���b�N���x���E�u���b�NID��t������B
							setASTReturnType(pre_programAST);
							setASTBlocklevelAndId(pre_programAST);

							//AST�؂���ϐ��e�[�u���𐶐�
							variable_table_list_zen = VARIABLE_TABLE_LIST_new();
							getVARIABLE_TABLE_LIST(variable_table_list_zen, pre_programAST);
							printVARIABLE_TABLE_LIST(variable_table_list_zen);
							fclose(target_source_file);

							//��������o�͂����邽�߂ɓ����t�@�C���ɏ㏑��������
							output = fopen(preprocess_file_name, "w");
							OutputSourceAfterDivitionDeclarator(output, pre_programAST, variable_table_list_zen);

							fclose(output);

							//�����܂ŕϐ��錾�̕�������

							//�\�[�X�t�@�C�����J����i�����͊m���ɊJ����̂ŁA�`�F�b�N�@�\�͂Ȃ��ɂ���j
							target_source_file = fopen(preprocess_file_name, "r");

							programAST = parserANSIC(target_source_file, &typedef_table_list);

							//AST�m�[�h�ɁA�ԋp�̌^���E�u���b�N���x���E�u���b�NID��t������B
							setASTReturnType(programAST);
							setASTBlocklevelAndId(programAST);

							//�w�l�k���[�h�ł���ꍇ
							if(isXmlMode(flag_database)){
								//AST�ؑS�̂�XML�Ƃ��ďo�͂���
								traverseASTwithXML(programAST, 0);
								printTargetASTNode(programAST, "array_access", 1, 1);
								printTargetASTNode(programAST, "direct_ref", 1, 1);
								printTargetASTNode(programAST, "expression_statement", 1, 1);
								printTargetASTNode(programAST, "function_definition", 1, 1);
								printTargetASTNode(programAST, "if_statement",1, 1);
							}else{
								//AST�ؑS�̂��o�͂���
								//traverseAST(programAST, 0);

								//AST�؂���v���O�������o�͂���
								int tmp = 1;
								//printDataFromAST(programAST, &tmp);

								//AST�؂��琶������TYPEDEF�e�[�u����\��
								//printTYPEDEF_TABLE_LIST(typedef_table_list);

								//AST�؂���\���̃e�[�u���𐶐����ďo��
								struct_table_list = STRUCT_TABLE_LIST_new();
								getSTRUCT_TABLE_DATA(struct_table_list, programAST);
								//printSTRUCT_TABLE_LIST(struct_table_list);

								//AST�؂���ϐ��e�[�u���𐶐����ďo��
								variable_table_list = VARIABLE_TABLE_LIST_new();
								getVARIABLE_TABLE_LIST(variable_table_list, programAST);
								getParameterVARIABLE_TABLE_LIST(variable_table_list, programAST);


								//�ϐ��e�[�u�����猟�ؗp�ϐ��e�[�u���𐶐����ďo��
								varidate_variable_list = ValidateVariableList_new();
								getValidate_Variable(variable_table_list, varidate_variable_list);

								//printVALIDATE_VARIABLE_LIST(varidate_variable_list);

								//�֐��Ɋւ��郊�X�g�𐶐����ďo��
								function_information_list = FUNCTION_INFORMATION_LIST_new();
								getFunctionInformation(function_information_list, programAST);
								getFunctionInformationFromFile(function_information_list, "./Standard_library.ini");

								printFUNCTION_INFORMATION_LIST(function_information_list);

								//�i�����j�w�肳�ꂽAST�̏����o��
								//printTargetASTNode(programAST, "call_function", 0, 0);
								//printTargetASTNode(programAST, "direct_ref", 0, 0);
								//printTargetASTNode(programAST, "assignment_expression", 0, 0);
								//printTargetASTNode(programAST, "expression_statement", 0, 0);

								//���؎��̐���
								validate_statement_list = ValidateStatementList_new();
								for_information_list = ForInformationList_new();
								createValidateStatementFromArrayDefine(varidate_variable_list, validate_statement_list, variable_table_list, function_information_list);
								createVaridateStatementFromPointerDefine(validate_statement_list, variable_table_list, function_information_list);
								createValidateStatement(programAST,  function_information_list, variable_table_list, varidate_variable_list, validate_statement_list,
								 for_information_list, isUndefineControlCheckMode(flag_database), isZeroDivitionCheckMode(flag_database), isArrayUnboundCheckMode(flag_database),
								 isFreeViolationCheckMode(flag_database));

								if(isProgramSlicingMode(flag_database)){
									//���؎����X�g��AST�m�[�h���ƂɃ\�[�g����
									validateStatementListSort(validate_statement_list);

									//�v���O�����X���C�V���O���X�g�Ɋւ�����𐶐�
									expr_slicing_list = EXPR_SLICING_LIST_new();
									createStatementNodeList(programAST, expr_slicing_list, NULL, variable_table_list, function_information_list);

									//�֐����Ŏg�p����Ă���O���[�o���ϐ��𒊏o���A�v���O�����X���C�V���O�̊֐��Ăяo���̑Ώۂ̕ϐ��ɐݒ肷��
									setGlobalVariable(expr_slicing_list, expr_slicing_list);
									//�v���O�����X���C�V���O�̑Ώۂ̕ϐ�����шˑ��֌W�ɑ΂��āA�f�[�^�ˑ��֌W��ǉ�����
									createDD_listAll(expr_slicing_list, function_information_list, expr_slicing_list);

									//�v���O�����X���C�V���O�Ɋւ�������o�͂�����
									print_EXPR_SLICING_LIST(expr_slicing_list);
									print_tree_EXPR_SLICING_LIST(expr_slicing_list, 0);

									//�v���O�����X���C�V���O�������ƂɁA���؎����o�͂�����
									createValidateStatementAdderFileEachCheck(expr_slicing_list, validate_statement_list,
											varidate_variable_list, for_information_list, include_list);
								}else{
									//�o�̓t�@�C���Ɍ��؎��t���̃v���O�������o�͂�����
									snprintf(output_file_name, FILE_PATH, "%s_output.c", preprocess_file_name);
									output = fopen(output_file_name, "w");
									printProgramDataWithValidateStatement(programAST, varidate_variable_list, validate_statement_list, for_information_list);
									//fprintProgramDataWithValidateStatement(output, programAST, varidate_variable_list, validate_statement_list, for_information_list);

									//���̓t�@�C������яo�̓t�@�C�������
									fclose(target_source_file);
									fclose(output);
									//�C���N���[�h���X�g����C���N���[�h��t������
									addIncludeDataFromFile(output_file_name, include_list);
								}



							}

						}else{
							printf("PreProcesser is failed!! Please Check your source file!!\n");
						}
					}
		}
	}
}
