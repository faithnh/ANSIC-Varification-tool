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

	//フラグデータベースの設定
	int flag_database = getFlagDatabase(argc, argv);

	//ヘルプモードが含まれていたらヘルプだけ表示させる
	if(isHelpMode(flag_database)){
		viewHelp();
	}
	//そうでなければ、検証式付加処理に進める
	else{
		int i;

		//フラグを飛ばす
		for(i = 1;i < argc && strlen(argv[i]) >= 2 && ( argv[i][0] == '-' && argv[i][1] == '-' ); i++);
		if(i == argc){
			fprintf(stderr, "開くファイル名が存在しません！\n");
			exit(1);
		}

		if(argc >= ENABLE_ARGUMENT){
				//ファイル名を設定する（これは他のエラー処理などでファイル名を表示させるようにするために必要）
					setFileName(argv[i]);

					//前処理に成功した場合
					if(preProcesser(argv[i])){

						//プリプロセス後のファイル名の設定
						snprintf(preprocess_file_name, FILE_PATH, "%s_out.c_pre.c", argv[i]);

						//インクルードファイルリストを取得
						include_list = INCLUDE_LIST_new();
						readIncludeDataFromFile(preprocess_file_name, include_list);

						target_source_file = fopen(preprocess_file_name, "r");

						if(target_source_file != NULL){

							//ここから変数宣言の分割処理

							pre_programAST = parserANSIC(target_source_file, &typedef_table_list_zen);

							//ASTノードに、返却の型名・ブロックレベル・ブロックIDを付加する。
							setASTReturnType(pre_programAST);
							setASTBlocklevelAndId(pre_programAST);

							//AST木から変数テーブルを生成
							variable_table_list_zen = VARIABLE_TABLE_LIST_new();
							getVARIABLE_TABLE_LIST(variable_table_list_zen, pre_programAST);
							printVARIABLE_TABLE_LIST(variable_table_list_zen);
							fclose(target_source_file);

							//分割後を出力させるために同じファイルに上書きさせる
							output = fopen(preprocess_file_name, "w");
							OutputSourceAfterDivitionDeclarator(output, pre_programAST, variable_table_list_zen);

							fclose(output);

							//ここまで変数宣言の分割処理

							//ソースファイルを開ける（ここは確実に開けるので、チェック機構はなしにする）
							target_source_file = fopen(preprocess_file_name, "r");

							programAST = parserANSIC(target_source_file, &typedef_table_list);

							//ASTノードに、返却の型名・ブロックレベル・ブロックIDを付加する。
							setASTReturnType(programAST);
							setASTBlocklevelAndId(programAST);

							//ＸＭＬモードである場合
							if(isXmlMode(flag_database)){
								//AST木全体をXMLとして出力する
								traverseASTwithXML(programAST, 0);
								printTargetASTNode(programAST, "array_access", 1, 1);
								printTargetASTNode(programAST, "direct_ref", 1, 1);
								printTargetASTNode(programAST, "expression_statement", 1, 1);
								printTargetASTNode(programAST, "function_definition", 1, 1);
								printTargetASTNode(programAST, "if_statement",1, 1);
							}else{
								//AST木全体を出力する
								//traverseAST(programAST, 0);

								//AST木からプログラムを出力する
								int tmp = 1;
								//printDataFromAST(programAST, &tmp);

								//AST木から生成したTYPEDEFテーブルを表示
								//printTYPEDEF_TABLE_LIST(typedef_table_list);

								//AST木から構造体テーブルを生成して出力
								struct_table_list = STRUCT_TABLE_LIST_new();
								getSTRUCT_TABLE_DATA(struct_table_list, programAST);
								//printSTRUCT_TABLE_LIST(struct_table_list);

								//AST木から変数テーブルを生成して出力
								variable_table_list = VARIABLE_TABLE_LIST_new();
								getVARIABLE_TABLE_LIST(variable_table_list, programAST);
								getParameterVARIABLE_TABLE_LIST(variable_table_list, programAST);


								//変数テーブルから検証用変数テーブルを生成して出力
								varidate_variable_list = ValidateVariableList_new();
								getValidate_Variable(variable_table_list, varidate_variable_list);

								//printVALIDATE_VARIABLE_LIST(varidate_variable_list);

								//関数に関するリストを生成して出力
								function_information_list = FUNCTION_INFORMATION_LIST_new();
								getFunctionInformation(function_information_list, programAST);
								getFunctionInformationFromFile(function_information_list, "./Standard_library.ini");

								printFUNCTION_INFORMATION_LIST(function_information_list);

								//（実験）指定されたASTの情報を出力
								//printTargetASTNode(programAST, "call_function", 0, 0);
								//printTargetASTNode(programAST, "direct_ref", 0, 0);
								//printTargetASTNode(programAST, "assignment_expression", 0, 0);
								//printTargetASTNode(programAST, "expression_statement", 0, 0);

								//検証式の生成
								validate_statement_list = ValidateStatementList_new();
								for_information_list = ForInformationList_new();
								createValidateStatementFromArrayDefine(varidate_variable_list, validate_statement_list, variable_table_list, function_information_list);
								createVaridateStatementFromPointerDefine(validate_statement_list, variable_table_list, function_information_list);
								createValidateStatement(programAST,  function_information_list, variable_table_list, varidate_variable_list, validate_statement_list,
								 for_information_list, isUndefineControlCheckMode(flag_database), isZeroDivitionCheckMode(flag_database), isArrayUnboundCheckMode(flag_database),
								 isFreeViolationCheckMode(flag_database));

								if(isProgramSlicingMode(flag_database)){
									//検証式リストをASTノードごとにソートする
									validateStatementListSort(validate_statement_list);

									//プログラムスライシングリストに関する情報を生成
									expr_slicing_list = EXPR_SLICING_LIST_new();
									createStatementNodeList(programAST, expr_slicing_list, NULL, variable_table_list, function_information_list);

									//関数内で使用されているグローバル変数を抽出し、プログラムスライシングの関数呼び出しの対象の変数に設定する
									setGlobalVariable(expr_slicing_list, expr_slicing_list);
									//プログラムスライシングの対象の変数および依存関係に対して、データ依存関係を追加する
									createDD_listAll(expr_slicing_list, function_information_list, expr_slicing_list);

									//プログラムスライシングに関する情報を出力させる
									print_EXPR_SLICING_LIST(expr_slicing_list);
									print_tree_EXPR_SLICING_LIST(expr_slicing_list, 0);

									//プログラムスライシング情報をもとに、検証式を出力させる
									createValidateStatementAdderFileEachCheck(expr_slicing_list, validate_statement_list,
											varidate_variable_list, for_information_list, include_list);
								}else{
									//出力ファイルに検証式付きのプログラムを出力させる
									snprintf(output_file_name, FILE_PATH, "%s_output.c", preprocess_file_name);
									output = fopen(output_file_name, "w");
									printProgramDataWithValidateStatement(programAST, varidate_variable_list, validate_statement_list, for_information_list);
									//fprintProgramDataWithValidateStatement(output, programAST, varidate_variable_list, validate_statement_list, for_information_list);

									//入力ファイルおよび出力ファイルを閉じる
									fclose(target_source_file);
									fclose(output);
									//インクルードリストからインクルードを付加する
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
