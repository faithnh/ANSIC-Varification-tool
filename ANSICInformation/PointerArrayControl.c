#include"PointerArrayControl.h"

#include"../Library/CSTLString.h"
#include "../Library/CharStringExtend.h"
#include "../Library/IdList.h"
#include "../Library/StoreInformation.h"
#include "SubEffectCheck.h"
#include "ANSIC_CODE.h"
//文字列の長さ
#define STRLEN 1024

//primary_expresionで出力に成功した場合
#define PRIMARY_SUCCESS 2
//成功した場合
#define SUCCESS 1
//失敗した場合
#define FAILED 0

//アンパサンドではさんでいない場合のフラグ
#define NOT_VIA_ANPASAND 0

//アンパサンドではさんでいる場合のフラグ
#define VIA_ANPASAND 1

//インクリメントかデクリメントが含まれているかどうかを示すフラグ
#define NOT_INC_DEC 0
#define VIA_INC 1
#define VIA_DEC 2

//副作用を許すか否かを示すフラグ
#define ALLOW_SUBEFF 1
#define DENIDE_SUBEFF 0

#define DEBUG_MODE


CSTL_LIST_IMPLEMENT(OFFSET_LIST, char *);

CSTL_LIST_IMPLEMENT(ARRAY_OFFSET_LIST, ARRAY_OFFSET);

CSTL_LIST_IMPLEMENT(ASTPOINTER_LIST, AST*);

/**
配列やポインタの各次元のオフセット関係を格納するための構造体のデータを生成させる。
@param variable_name 変数名
@param target_statement ターゲットのstatement
@param variable_address この変数名が指しているASTアドレス
@param offset_list 各次元のオフセット
@param pointer_level この変数のポインタレベル
@param array_level この変数の配列レベル
@param anpasand_flag アンパサンドを挟んでいるかどうかのフラグ　１：挟んでいる　０：挟んでいない
@param inc_dec_flag インクリメントおよびデクリメントが含まれているかどうかのフラグ　０：含んでいない　１：インクリメントが含まれている　２：デクリメントが含まれている

@return 配列やポインタの各次元のオフセットに関する構造体へのアドレスを返す。
*/
ARRAY_OFFSET *new_ARRAY_OFFSET_char(char *variable_name, AST *target_statement, AST *variable_address,
									OFFSET_LIST *offset_list, int pointer_level, int array_level, int anpasand_flag, int inc_dec_flag){
	CSTLString *variable_name_cstl = CSTLString_new();
	CSTLString_assign(variable_name_cstl, variable_name);

	return new_ARRAY_OFFSET(variable_name_cstl, target_statement, variable_address, offset_list, pointer_level, array_level, anpasand_flag, inc_dec_flag);
}

/**。
配列やポインタの各次元のオフセット関係を格納するための構造体のデータを生成させる。
@param variable_name 変数名
@param target_statement ターゲットのstatement
@param variable_address この変数名が指しているASTアドレス
@param offset_list 各次元のオフセット
@param pointer_level この変数のポインタレベル
@param array_level この変数の配列レベル
@param anpasand_flag この変数はアンパサンドを挟んでいるかどうかのフラグ　１：挟んでいる　０：挟んでいない
@param inc_dec_flag インクリメントおよびデクリメントが含まれているかどうかのフラグ　０：含んでいない　１：インクリメントが含まれている　２：デクリメントが含まれている

@return 配列やポインタの各次元のオフセットに関する構造体へのアドレスを返す。
*/
ARRAY_OFFSET *new_ARRAY_OFFSET(	CSTLString *variable_name, AST *target_statement, AST *variable_address,
							   OFFSET_LIST *offset_list, int pointer_level, int array_level, int anpasand_flag, int inc_dec_flag){
	//配列やポインタの各次元のオフセット関係を格納するための構造体を生成する
	ARRAY_OFFSET *new_array_offset = (ARRAY_OFFSET*)malloc(sizeof(ARRAY_OFFSET));

	//必要な情報を代入していく
	new_array_offset->variable_name = variable_name;
	new_array_offset->target_statement = target_statement;
	new_array_offset->variable_address = variable_address;
	new_array_offset->offset_list = offset_list;
	new_array_offset->pointer_level = pointer_level;
	new_array_offset->array_level = array_level;
	new_array_offset->anpasand_flag = anpasand_flag;
	new_array_offset->inc_dec_flag = inc_dec_flag;
	//配列やポインタの各次元のオフセット関係を格納するための構造体へのアドレスを返す
	return new_array_offset;
}

/**
任意の文字列を、動的変数としてオフセットリストに追加する。
@param offset_list 対象のオフセットリスト
@param string 任意の文字列

@return なし
 */
void OFFSET_LIST_push_back_alloc(OFFSET_LIST *offset_list, char *string){
	 char *target;

	 //任意の文字列分を生成し、任意の文字列に代入する
	 target = calloc(strlen(string), sizeof(char));
	 strcpy(target, string);

	 //生成されたtargetをオフセットリストに追加する
	 OFFSET_LIST_push_back(offset_list, target);
 }

/**
getPointerArrayOffsetの内部処理
@param root 左辺値に関するASTノード
@param function_information_list 関数に関する情報リスト
@param vtlist 検証対象の式をマークするための変数リスト
@param offset_level オフセットレベルを計算するためのところ。基本的に０を入力する。１以上入力すれば、それが最下位レベルとなる。
@param ignore_ast_list ポインタでの位置が検証済みである、IDENTIFIERを無視するためのASTのアドレスリスト
@param array_offset ポインタおよび配列のオフセット情報
@param target_statement 検証式の対象となるステートメント
@param anpasand_flag アンパサンドを挟んでいるかどうかのフラグ　１：挟んでいる　0：挟んでいない
@param inc_dec_flag インクリメントおよびデクリメントが含まれているかどうかのフラグ　０：含んでいない　１：インクリメントが含まれている　２：デクリメントが含まれている
@return なし
*/
int getPointerArrayOffset_Internal(AST *root, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist, int offset_level,
		ASTPOINTER_LIST *ignore_ast_list, ARRAY_OFFSET **array_offset, AST *target_statement, int anpasand_flag, int inc_dec_flag){
	//direct_refより下位のASTノード
		AST *low_output = NULL;
		AST *low_output2 = NULL;

		//primary以下のASTノードリストとその数
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

		//もしレベルが0である場合、valid_flagは強制的にSUCCESSにし、low_outputはrootそのものである
		if(offset_level == 0){
			valid_flag = SUCCESS;
			low_output = root;
		}else{

			//direct_refより下位がどうなっているか調べる
			valid_flag = searchPointerAccessOrIdentifierOrPrimary(root, &low_output);
		}

		if(valid_flag == SUCCESS){
			//もし、direct_refなら、レベルを上げて同じ参照を行う、この時の次元のオフセットは0である。
			if(CSTLString_compare_with_char(low_output->name, "direct_ref") == 0){
				success_flag = getPointerArrayOffset_Internal(low_output, function_information_list, vtlist, offset_level + 1,
					ignore_ast_list, array_offset, target_statement, anpasand_flag, inc_dec_flag);
				//変数名が見つかれば、オフセットを設定する
				if(success_flag == SUCCESS){

					//オフセットを各次元の配列およびポインタのオフセットリストに設定する
					zero = calloc(2, sizeof(char));
					sprintf(zero, "0");
					OFFSET_LIST_push_back_alloc((*array_offset)->offset_list, zero);

				}
				//もし、primary_expressionとして出力された場合
				else if(success_flag == PRIMARY_SUCCESS){
					success_flag = SUCCESS;
				}
			}

			//もし、array_accessなら、レベルを上げて同じ参照を行う、この時の次元のオフセットは配列の中身である。
			else if(CSTLString_compare_with_char(low_output->name, "array_access") == 0){
				success_flag = getPointerArrayOffset_Internal(low_output, function_information_list, vtlist, offset_level + 1,
					ignore_ast_list, array_offset, target_statement, anpasand_flag, inc_dec_flag);
				//変数名が見つかれば、オフセットを設定する
				if(success_flag == SUCCESS){

					//オフセットを各次元の配列およびポインタのオフセットリストに設定する
					array_content = CSTLString_new();
					getStringFromAST(array_content, getASTwithString(low_output, "array_content", 1));
					OFFSET_LIST_push_back_alloc((*array_offset)->offset_list, (char*)CSTLString_c_str(array_content));

					CSTLString_delete(array_content);
				}
			}

			//もし、primary_expressionなら、その次に来るのがminus_exprかplus_exprか、array_accessかdirect_refか、はたまたIDENTIFIERかCONSTANTか調べる
			else if(CSTLString_compare_with_char(low_output->name, "primary_expression") == 0){
				//primary_expressionより下位はどうなっているか調べる
				valid_flag = searchExpressionOrPointeArrayOrIden(low_output, &low_output2);
				if(valid_flag == SUCCESS){

					//minus_exprかplus_exprならばarray_acces・direct_ref・IDENTIFIERがノード名であるASTリストを作成する。
					if(CSTLString_compare_with_char(low_output2->name, "minus_expr") == 0 ||
						CSTLString_compare_with_char(low_output2->name, "plus_expr") == 0){

						getPointerAccessOrIdentifierList(low_output2, &primary_level_node_list, &primary_level_node_num);

						//もし、array_accessやdirect_refならレベルを上げて同じ参照を行う、
						for(i = 0; i < primary_level_node_num; i++){

							//もし、direct_refなら、レベルを上げて同じ参照を行う、この時の次元のオフセットは0である。
							if(CSTLString_compare_with_char(primary_level_node_list[i]->name, "direct_ref") == 0){
								success_flag = getPointerArrayOffset_Internal(primary_level_node_list[i], function_information_list, vtlist, offset_level + 1, ignore_ast_list,
									array_offset, target_statement, anpasand_flag, inc_dec_flag);
								//変数名が見つかれば、オフセットを設定する
								if(success_flag == SUCCESS){
									//オフセットを各次元の配列およびポインタのオフセットリストに設定する
									OFFSET_LIST_push_back_alloc((*array_offset)->offset_list, "0");

								}
								//もし、primary_expressionとして出力された場合
								else if(success_flag == PRIMARY_SUCCESS){
									success_flag = SUCCESS;
								}
							}


							//もし、array_accessなら、レベルを上げて同じ参照を行う、この時の次元のオフセットは配列の中身である。
							else if(CSTLString_compare_with_char(primary_level_node_list[i]->name, "array_access") == 0){
								success_flag = getPointerArrayOffset_Internal(primary_level_node_list[i], function_information_list, vtlist, offset_level + 1, ignore_ast_list,
									array_offset, target_statement, anpasand_flag, inc_dec_flag);
								//変数名が見つかれば、オフセットを設定する
								if(success_flag == SUCCESS){
									//オフセットを各次元の配列およびポインタのオフセットリストに設定する
									array_content = CSTLString_new();
									getStringFromAST(array_content, getASTwithString(primary_level_node_list[i], "array_content", 1));
									OFFSET_LIST_push_back_alloc((*array_offset)->offset_list, (char*)CSTLString_c_str(array_content));

									CSTLString_delete(array_content);
									break;
								}
							}

							//IDENTIFIERが来たら、変数テーブルから調べ、どのような変数であるかしらべる
							else if(CSTLString_compare_with_char(primary_level_node_list[i]->name, "IDENTIFIER") == 0){
								pointer_level = 0;
								array_level = 0;
								success_flag = checkIdentifierPointerArrayLevel(primary_level_node_list[i], offset_level, vtlist,
									ignore_ast_list, &pointer_level, &array_level);
								if(success_flag == SUCCESS){
									//配列やポインタの各次元に対するオフセット情報を生成し、array_offsetに代入する
									OFFSET_LIST *offset_list = OFFSET_LIST_new();

									*array_offset = new_ARRAY_OFFSET_char((char *)CSTLString_c_str(primary_level_node_list[i]->content), target_statement,
										primary_level_node_list[i], offset_list, pointer_level, array_level, anpasand_flag, inc_dec_flag);
								}
							}

							//もし、関数呼び出しなら、この関数名が存在するかどうか調べる
							else if(CSTLString_compare_with_char(primary_level_node_list[i]->name, "call_function")){
								checkCallFunction(primary_level_node_list[i],offset_level,function_information_list);
							}

							//もし、インクリメントやデクリメント式が来た場合は、それは望ましくない処理とみなし、エラーを出力し、強制終了させる
							//理由：副作用を持つ式をポインタ演算や配列内に書くこと自体が保守的に分かりにくいため
							else if(CSTLString_compare_with_char(primary_level_node_list[i]->name, "inc_after_expr") == 0 ||
							CSTLString_compare_with_char(primary_level_node_list[i]->name, "inc_expr") == 0 ||
							CSTLString_compare_with_char(primary_level_node_list[i]->name, "dec_after_expr") == 0 ||
							CSTLString_compare_with_char(primary_level_node_list[i]->name, "inc_expr") == 0){
								fprintf(stderr, "#%s#:%d:Invalid Pointer Access!! Shouldn't contain Inclement or Declement Expression!!\n", getFileName(), primary_level_node_list[i]->line);
								exit(1);
							}
							//もし、代入式が来た場合は、それは望ましくない処理とみなし、エラーを出力し、強制終了させる
							//理由：副作用を持つ式をポインタ演算や配列内にに書くこと自体望ましくないから
							else if(CSTLString_compare_with_char(primary_level_node_list[i]->name, "assignment_expression") == 0){
								fprintf(stderr, "#%s#:%d:Invalid Pointer Access!! Shouldn't contain Assignment Expression!!\n", getFileName(), primary_level_node_list[i]->line);
								exit(1);
							}
							if(success_flag == SUCCESS){
								break;
							}

						}
						//primary_expression以下の式で、ポインタ変数を見つけた場合
						if(success_flag == SUCCESS){
							//まず、このポインタ変数は間接的にどの演算に位置しているかどうか調べ、upper_relationに代入する。
							//もしupper_relationがminus_exprである場合は、それより1つ下のノードがone_level_downに代入する。
							//これは、-演算式でそのひとつ下が左値か右値に位置しているかどうか確認するためである。
							AST *upper_relation, *one_level_down;
							valid_flag = getUpperExpressionRelationNode(primary_level_node_list[i], low_output, &upper_relation, &one_level_down);

							//minus_exprであり、ひとつ下が右値に位置している場合
							if(CSTLString_compare_with_char(upper_relation->name, "minus_expr") == 0 &&
								ASTList_data(ASTList_next(ASTList_next(ASTList_begin(upper_relation->children)))) == one_level_down){
									fprintf(stderr, "#%s#:%d:Invalid Pointer Operator is %s and located right value!", getFileName(), low_output2->line, CSTLString_c_str(upper_relation->name));
									exit(1);
							}

							//上位関係を調べるのに失敗したか、primary_expression・array_access・direct_ref・plus_expr・minus_exprのいずれでもない場合
							else if(valid_flag == FAILED ||
								(CSTLString_compare_with_char(upper_relation->name, "primary_expression") != 0 &&
								CSTLString_compare_with_char(upper_relation->name, "array_access") != 0 &&
								CSTLString_compare_with_char(upper_relation->name, "direct_ref") != 0 &&
								CSTLString_compare_with_char(upper_relation->name, "plus_expr") != 0 &&
								CSTLString_compare_with_char(upper_relation->name, "minus_expr") != 0)){
									//エラーを出力し、強制終了させる。
									fprintf(stderr, "#%s#:%d:Invalid Pointer Operator is %s !", getFileName(), low_output2->line, CSTLString_c_str(upper_relation->name));
									exit(1);
							}

							//上記以外の場合は成功である
							else{

								//オフセットを各次元の配列およびポインタのオフセットリストに設定する
								primary_level_node_string = CSTLString_new();
								getStringReplaceASTtoString(primary_level_node_string, getASTwithString(low_output, "t_expression", 1), primary_level_node_list[i], "0");
								OFFSET_LIST_push_back_alloc((*array_offset)->offset_list, (char*)CSTLString_c_str(primary_level_node_string));

								CSTLString_delete(primary_level_node_string);
								//primary_expressionで出力されたことをここで示す
								success_flag = PRIMARY_SUCCESS;
							}

						}

						//primary以下のASTノードリストはここで初期化され、その個数は０となる。
						free(primary_level_node_list);
						primary_level_node_num = 0;

					}

					//もし、direct_refなら、レベルを上げて同じ参照を行う、この時の次元のオフセットは0である。
					else if(CSTLString_compare_with_char(low_output2->name, "direct_ref") == 0){
						success_flag = getPointerArrayOffset_Internal(low_output2, function_information_list, vtlist, offset_level + 1, ignore_ast_list, array_offset, target_statement, anpasand_flag, inc_dec_flag);
						//変数名が見つかれば、オフセットを設定する
						if(success_flag == SUCCESS){
							//オフセットを各次元の配列およびポインタのオフセットリストに設定する
							OFFSET_LIST_push_back_alloc((*array_offset)->offset_list, "0");

						}
						//もし、primary_expressionとして出力された場合
						else if(success_flag == PRIMARY_SUCCESS){
							success_flag = SUCCESS;
						}
					}

					//もし、array_accessなら、レベルを上げて同じ参照を行う、この時の次元のオフセットは配列の中身である。
					else if(CSTLString_compare_with_char(low_output2->name, "array_access") == 0){
						success_flag = getPointerArrayOffset_Internal(low_output2, function_information_list, vtlist, offset_level + 1, ignore_ast_list, array_offset, target_statement, anpasand_flag, inc_dec_flag);
						//変数名が見つかれば、オフセットを設定する
						if(success_flag == SUCCESS){

							//オフセットを各次元の配列およびポインタのオフセットリストに設定する
							array_content = CSTLString_new();
							getStringFromAST(array_content, getASTwithString(low_output2, "array_content", 1));
							OFFSET_LIST_push_back_alloc((*array_offset)->offset_list, (char*)CSTLString_c_str(array_content));

							CSTLString_delete(array_content);
						}
					}

					//IDENTIFIERが来たら、変数テーブルから調べ、どのような変数であるかしらべる
					else if(CSTLString_compare_with_char(low_output2->name, "IDENTIFIER") == 0){
						pointer_level = 0;
						array_level = 0;
						success_flag = checkIdentifierPointerArrayLevel(low_output2, offset_level, vtlist, ignore_ast_list, &pointer_level, &array_level);
						if(success_flag == SUCCESS){
							//配列やポインタの各次元に対するオフセット情報を生成し、array_offsetに代入する
							OFFSET_LIST *offset_list = OFFSET_LIST_new();
							*array_offset = new_ARRAY_OFFSET_char((char *)CSTLString_c_str(low_output2->content), target_statement, low_output2,
								offset_list, pointer_level, array_level, anpasand_flag, inc_dec_flag);
						}
					}

					//もし、関数呼び出しなら、この関数名が存在するかどうか調べる
					else if(CSTLString_compare_with_char(low_output2->name, "call_function")){
						checkCallFunction(low_output2,offset_level,function_information_list);
					}

					//もし、インクリメントやデクリメント式が来た場合は、それは望ましくない処理とみなし、エラーを出力し、強制終了させる
					//理由：副作用を持つ式をポインタ演算や配列内に書くこと自体が保守的に分かりにくいため
					else if(CSTLString_compare_with_char(low_output2->name, "inc_after_expr") == 0 ||
					CSTLString_compare_with_char(low_output2->name, "inc_expr") == 0 ||
					CSTLString_compare_with_char(low_output2->name, "dec_after_expr") == 0 ||
					CSTLString_compare_with_char(low_output2->name, "inc_expr") == 0){
						fprintf(stderr, "#%s#:%d:Invalid Pointer Access!! Shouldn't contain Inclement or Declement Expression!!\n", getFileName(), low_output2->line);
						exit(1);
					}
					//もし、代入式が来た場合は、それは望ましくない処理とみなし、エラーを出力し、強制終了させる
					//理由：副作用を持つ式をポインタ演算や配列内にに書くこと自体望ましくないから
					else if(CSTLString_compare_with_char(low_output2->name, "assignment_expression") == 0){
						fprintf(stderr, "#%s#:%d:Invalid Pointer Access!! Shouldn't contain Assignment Expression!!\n", getFileName(), low_output2->line);
						exit(1);
					}
				}

				//上記以外の式がきたら、エラーを出力させる
				else if(valid_flag == -1){
					fprintf(stderr, "#%s#:%d:Invalid Access!\n", getFileName(), root->line);
					fflush(stderr);
					exit(1);
				}
			}

			//もし、IDENTIFIERなら、変数テーブルから調べ、どのような変数であるかしらべる
			else if(CSTLString_compare_with_char(low_output->name, "IDENTIFIER") == 0){
				pointer_level = 0;
				array_level = 0;
				success_flag = checkIdentifierPointerArrayLevel(low_output, offset_level, vtlist, ignore_ast_list, &pointer_level, &array_level);
				if(success_flag == SUCCESS){
					//配列やポインタの各次元に対するオフセット情報を生成し、array_offsetに代入する
					OFFSET_LIST *offset_list = OFFSET_LIST_new();
					*array_offset = new_ARRAY_OFFSET_char((char *)CSTLString_c_str(low_output->content), target_statement, low_output,
						offset_list, pointer_level, array_level, anpasand_flag, inc_dec_flag);
				}
			}

			//もし、関数呼び出しなら、この関数名が存在するかどうか調べる
			else if(CSTLString_compare_with_char(low_output->name, "call_function")){
				checkCallFunction(low_output,offset_level,function_information_list);
			}

			//もし、インクリメントやデクリメント式が来た場合は、それは望ましくない処理とみなし、エラーを出力し、強制終了させる
			//理由：副作用を持つ式をポインタ演算や配列内に書くこと自体望ましくないから
			else if(CSTLString_compare_with_char(low_output->name, "inc_after_expr") == 0 ||
			CSTLString_compare_with_char(low_output->name, "inc_expr") == 0 ||
			CSTLString_compare_with_char(low_output->name, "dec_after_expr") == 0 ||
			CSTLString_compare_with_char(low_output->name, "inc_expr") == 0){
				fprintf(stderr, "#%s#:%d:Invalid Pointer Access!! Shouldn't contain Increment or Decrement Expression!!\n", getFileName(), low_output->line);
				exit(1);
			}
			//もし、代入式が来た場合は、それは望ましくない処理とみなし、エラーを出力し、強制終了させる
			//理由：副作用を持つ式をポインタ演算や配列内にに書くこと自体望ましくないから
			else if(CSTLString_compare_with_char(low_output->name, "assignment_expression") == 0){
				fprintf(stderr, "#%s#:%d:Invalid Pointer Access!! Shouldn't contain Assignment Expression!!\n", getFileName(), low_output->line);
				exit(1);
			}

		}

		return success_flag;
}



/**
ポインタおよび配列変数の各次元のオフセットとなる式を求める。
@param root 左辺値に関するASTノード
@param function_information_list 関数に関する情報リスト
@param vtlist 検証対象の式をマークするための変数リスト
@param offset_level オフセットレベルを計算するためのところ。基本的に０を入力する。１以上入力すれば、それが最下位レベルとなる。
@param ignore_ast_list ポインタでの位置が検証済みである、IDENTIFIERを無視するためのASTのアドレスリスト
@param array_offset ポインタおよび配列のオフセット情報
@param target_statement 検証式の対象となるステートメント
@param anpasand_flag アンパサンドを挟んでいるかどうかのフラグ　１：挟んでいる　0：挟んでいない
@param inc_dec_flag インクリメントおよびデクリメントが含まれているかどうかのフラグ　０：含んでいない　１：インクリメントが含まれている　２：デクリメントが含まれている
@return なし
*/
int getPointerArrayOffset(AST *root, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist, int offset_level,
	ASTPOINTER_LIST *ignore_ast_list, ARRAY_OFFSET **array_offset, AST *target_statement, int anpasand_flag, int inc_dec_flag){
	int success_flag;
	//副作用式が含まれているかどうかチェックする
	int contain_subeffect_flag = checkContainSubEffectStatement(root);
	switch(contain_subeffect_flag){
	//インクリメント式が含まれていた場合
	case 1:
		fprintf(stderr, "#%s#:%d:Invalid Pointer Access!! Shouldn't contain Increment Expression!!\n", getFileName(), root->line);
		exit(1);
		break;
	//デクリメント式が含まれていた場合
	case 2:
		fprintf(stderr, "#%s#:%d:Invalid Pointer Access!! Shouldn't contain Decrement Expression!!\n", getFileName(), root->line);
		exit(1);
		break;
	//代入式が含まれていた場合
	case 3:
		fprintf(stderr, "#%s#:%d:Invalid Pointer Access!! Shouldn't contain Assignment Expression!!\n", getFileName(), root->line);
		exit(1);
		break;
	//副作用式が含まれていなかった場合、配列オフセットを取得する
	default:
		success_flag = getPointerArrayOffset_Internal(root, function_information_list, vtlist, offset_level, ignore_ast_list, array_offset, target_statement, anpasand_flag, inc_dec_flag);
	}
	return success_flag;
}

/**
ポインタおよび配列変数の各次元のオフセットリストを取得する。
@param root オフセットリストに該当するASTノード
@param array_offset_list ポインタおよび配列のオフセット情報のリスト
@param function_information_list 関数に関する情報リスト
@param vtlist 検証対象の式をマークするための変数リスト
@param ignore_ast_list ポインタでの位置が検証済みである、IDENTIFIERを無視するためのASTのアドレスリスト
@param target_statement 検証式の対象となるステートメント
@return なし
*/
void getARRAY_OFFSET_LIST(AST *root, ARRAY_OFFSET_LIST *array_offset_list, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
						  ASTPOINTER_LIST *ignore_ast_list, AST *target_statement){
	ASTListIterator ast_i;
	//直接参照記号や配列参照が来た場合、オフセットリストを作成する。
	if(CSTLString_compare_with_char(root->name, "direct_ref") == 0 ||
		CSTLString_compare_with_char(root->name, "array_access") == 0){

			ARRAY_OFFSET *array_offset = NULL;
			getPointerArrayOffset(root, function_information_list, vtlist, 0, ignore_ast_list, &array_offset, target_statement, NOT_VIA_ANPASAND, NOT_INC_DEC);
			if(array_offset != NULL){
				ARRAY_OFFSET_LIST_push_back_ref(array_offset_list, array_offset);
			}

	}
	//アドレス演算子が来た場合は、次のように探す
	else if(CSTLString_compare_with_char(root->name, "address_ref") == 0){
			getArrayOffsetInAnpasandInfo(root, function_information_list, vtlist,
							array_offset_list, ignore_ast_list, target_statement);
	}
	//インクリメント演算子が来た場合は、インクリメントを通した配列オフセットリストを取得する
	else if(CSTLString_compare_with_char(root->name, "inc_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "inc_after_expr") == 0){
		getArrayOffsetInIncDecInfo(root, function_information_list, vtlist,
								array_offset_list, ignore_ast_list, target_statement, VIA_INC);
	}
	//デクリメント演算子が来た場合は、インクリメントを通した配列オフセットリストを取得する
	else if(CSTLString_compare_with_char(root->name, "dec_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "dec_after_expr") == 0){
		getArrayOffsetInIncDecInfo(root, function_information_list, vtlist,
								array_offset_list, ignore_ast_list, target_statement, VIA_DEC);
	}
	//識別子が見つかれば、変数テーブルから存在する変数かどうかを調べてから、オフセットリストを作成する。
	else if(CSTLString_compare_with_char(root->name, "IDENTIFIER") == 0){
		//オフセット情報がないarray_offsetを作成する。
		ARRAY_OFFSET *array_offset;
		VARIABLE_TABLE *variable_table_data;
		OFFSET_LIST *offset_list = OFFSET_LIST_new();
		CSTLString *target_name = CSTLString_new();
		//指定したノードrootが、ignore_ast_listに存在しないかどうか調べるためのフラグ
		int ignore_flag;
		//該当する変数のポインタもしくは配列の次元を調べる。
		int pointer_level, array_level;
		//指定したIDLISTと名前から最も該当する変数テーブルへのアドレスを取得する
		variable_table_data = searchVARIABLE_TABLE_LIST(root->idlist, root->content, vtlist);
		//もし、該当する変数を見つかった場合
		if(variable_table_data != NULL){
			//指定したノードrootが、ignore_ast_listに存在しないかどうか調べる
			ignore_flag = checkIgnoreASTList(root, ignore_ast_list);

			//もし、存在しなければ、配列オフセットリストに追加する
			if(ignore_flag == FAILED){
				getPointerLevelAndArrayLevelFromVARIABLE_TABLE(variable_table_data, &pointer_level, &array_level);

				CSTLString_assign(target_name, CSTLString_c_str(root->content));

				array_offset = new_ARRAY_OFFSET(target_name, target_statement, root, offset_list, pointer_level, array_level, NOT_VIA_ANPASAND, NOT_INC_DEC);

				//DEBUG_MODEが有効な時ポインタおよび配列変数の各次元のオフセットの情報を出力する
				#ifdef DEBUG_MODE
					if(array_offset != NULL){
						printARRAY_OFFSET(array_offset);
					}
				#endif

				//それをarray_offset_listに追加する
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
ポインタおよび配列変数の各次元のオフセットリストを取得する。また、無視をする対象のノードを設定可能である。
@param root オフセットリストに該当するASTノード
@param array_offset_list ポインタおよび配列のオフセット情報のリスト
@param function_information_list 関数に関する情報リスト
@param vtlist 検証対象の式をマークするための変数リスト
@param ignore_ast_list ポインタでの位置が検証済みである、IDENTIFIERを無視するためのASTのアドレスリスト
@param target_statement 検証式の対象となるステートメント
@param ignore_ast_name 無視をするＡＳＴ名
@return なし
*/
void get_ARRAY_OFFSET_LISTIgnoreASTNAME(AST *root, ARRAY_OFFSET_LIST *array_offset_list, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
		  ASTPOINTER_LIST *ignore_ast_list, AST *target_statement, CSTLString *ignore_ast_name){
	ASTListIterator ast_i;
	//直接参照記号や配列参照が来た場合、オフセットリストを作成する。
	if(CSTLString_compare_with_char(root->name, "direct_ref") == 0 ||
		CSTLString_compare_with_char(root->name, "array_access") == 0){

			ARRAY_OFFSET *array_offset = NULL;
			getPointerArrayOffset(root, function_information_list, vtlist, 0, ignore_ast_list, &array_offset, target_statement, NOT_VIA_ANPASAND, NOT_INC_DEC);
			if(array_offset != NULL){
				ARRAY_OFFSET_LIST_push_back_ref(array_offset_list, array_offset);
			}

	}
	//アドレス演算子が来た場合は、次のように探す
	else if(CSTLString_compare_with_char(root->name, "address_ref") == 0){
			getArrayOffsetInAnpasandInfo(root, function_information_list, vtlist,
							array_offset_list, ignore_ast_list, target_statement);
	}
	//インクリメント演算子が来た場合は、インクリメントを通した配列オフセットリストを取得する
	else if(CSTLString_compare_with_char(root->name, "inc_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "inc_after_expr") == 0){
		getArrayOffsetInIncDecInfo(root, function_information_list, vtlist,
								array_offset_list, ignore_ast_list, target_statement, VIA_INC);
	}
	//デクリメント演算子が来た場合は、インクリメントを通した配列オフセットリストを取得する
	else if(CSTLString_compare_with_char(root->name, "dec_expr") == 0 ||
		CSTLString_compare_with_char(root->name, "dec_after_expr") == 0){
		getArrayOffsetInIncDecInfo(root, function_information_list, vtlist,
								array_offset_list, ignore_ast_list, target_statement, VIA_DEC);
	}
	//識別子が見つかれば、変数テーブルから存在する変数かどうかを調べてから、オフセットリストを作成する。
	else if(CSTLString_compare_with_char(root->name, "IDENTIFIER") == 0){
		//オフセット情報がないarray_offsetを作成する。
		ARRAY_OFFSET *array_offset;
		VARIABLE_TABLE *variable_table_data;
		OFFSET_LIST *offset_list = OFFSET_LIST_new();
		CSTLString *target_name = CSTLString_new();
		//指定したノードrootが、ignore_ast_listに存在しないかどうか調べるためのフラグ
		int ignore_flag;
		//該当する変数のポインタもしくは配列の次元を調べる。
		int pointer_level, array_level;
		//指定したIDLISTと名前から最も該当する変数テーブルへのアドレスを取得する
		variable_table_data = searchVARIABLE_TABLE_LIST(root->idlist, root->content, vtlist);
		//もし、該当する変数を見つかった場合
		if(variable_table_data != NULL){
			//指定したノードrootが、ignore_ast_listに存在しないかどうか調べる
			ignore_flag = checkIgnoreASTList(root, ignore_ast_list);

			//もし、存在しなければ、配列オフセットリストに追加する
			if(ignore_flag == FAILED){
				getPointerLevelAndArrayLevelFromVARIABLE_TABLE(variable_table_data, &pointer_level, &array_level);

				CSTLString_assign(target_name, CSTLString_c_str(root->content));

				array_offset = new_ARRAY_OFFSET(target_name, target_statement, root, offset_list, pointer_level, array_level, NOT_VIA_ANPASAND, NOT_INC_DEC);

				//DEBUG_MODEが有効な時ポインタおよび配列変数の各次元のオフセットの情報を出力する
				#ifdef DEBUG_MODE
					if(array_offset != NULL){
						printARRAY_OFFSET(array_offset);
					}
				#endif

				//それをarray_offset_listに追加する
				ARRAY_OFFSET_LIST_push_back_ref(array_offset_list, array_offset);
			}

		}
	}
	for(ast_i = ASTList_begin(root->children);
		ast_i != ASTList_end(root->children);
		ast_i = ASTList_next(ast_i)){
			//無視するノード名であれば、省略する
			if(CSTLString_compare(ASTList_data(ast_i)->name, ignore_ast_name) != 0){
				getARRAY_OFFSET_LIST(ASTList_data(ast_i) ,array_offset_list, function_information_list, vtlist, ignore_ast_list, target_statement);
			}
	}
}
/**
address_refであるノード内を探索し、それに対するアドレス参照や、識別子を探し出し、見つけたら配列オフセットリストarray_offset_listへ入れる。
@param root 右辺式に関するASTノード
@param function_information_list 関数に関する情報のリスト
@param vtlist メモリ確保情報を取得するのに必要なプログラム変数リスト
@param array_offset_list 左辺式上にあるポインタ参照に対するオフセットリスト
@param ignore_ast_list 同じ位置のポインタが来ても無視するためのリスト
@param target_statement この計算式を属しているASTノードへのアドレス（基本的にexpression_statementであるノードが入る）

@return なし
*/
void getArrayOffsetInAnpasandInfo(AST *root,FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
							ARRAY_OFFSET_LIST *array_offset_list, ASTPOINTER_LIST *ignore_ast_list, AST *target_statement){
	ASTListIterator ast_i;
	//直接参照記号や配列参照が来た場合、オフセットリストを作成する。
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
	//識別子が見つかれば、変数テーブルから存在する変数かどうかを調べてから、オフセットリストを作成する。
	else if(CSTLString_compare_with_char(root->name, "IDENTIFIER") == 0){
		//オフセット情報がないarray_offsetを作成する。
		ARRAY_OFFSET *array_offset;
		VARIABLE_TABLE *variable_table_data;
		OFFSET_LIST *offset_list = OFFSET_LIST_new();
		CSTLString *target_name = CSTLString_new();
		//指定したノードrootが、ignore_ast_listに存在しないかどうか調べるためのフラグ
		int ignore_flag;
		//該当する変数のポインタもしくは配列の次元を調べる。
		int pointer_level, array_level;
		//指定したIDLISTと名前から最も該当する変数テーブルへのアドレスを取得する
		variable_table_data = searchVARIABLE_TABLE_LIST(root->idlist, root->content, vtlist);
		//もし、該当する変数を見つかった場合
		if(variable_table_data != NULL){
			//指定したノードrootが、ignore_ast_listに存在しないかどうか調べる
			ignore_flag = checkIgnoreASTList(root, ignore_ast_list);

			//もし、存在しなければ、配列オフセットリストに追加する
			if(ignore_flag == FAILED){
				getPointerLevelAndArrayLevelFromVARIABLE_TABLE(variable_table_data, &pointer_level, &array_level);

				CSTLString_assign(target_name, CSTLString_c_str(root->content));

				array_offset = new_ARRAY_OFFSET(target_name, target_statement, root, offset_list, pointer_level, array_level, VIA_ANPASAND, NOT_INC_DEC);

				//DEBUG_MODEが有効な時ポインタおよび配列変数の各次元のオフセットの情報を出力する
				#ifdef DEBUG_MODE
					if(array_offset != NULL){
						printARRAY_OFFSET(array_offset);
					}
				#endif

				//それをarray_offset_listに追加する
				ARRAY_OFFSET_LIST_push_back_ref(array_offset_list, array_offset);
			}

		}
	}
	//先に、インクリメントおよびデクリメント、その他の演算式を見つかれば、エラーを出力して強制終了させる
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
inc_exprやdec_exprなどのインクリメントやデクリメント式であるノード内を探索し、それに対するアドレス参照や、識別子を探し出し、見つけたら配列オフセットリストarray_offset_listへ入れる。
@param root inc_exprやdec_exprなどのインクリメントやデクリメント式に関するASTノード
@param function_information_list 関数に関する情報のリスト
@param vtlist メモリ確保情報を取得するのに必要なプログラム変数リスト
@param array_offset_list 左辺式上にあるポインタ参照に対するオフセットリスト
@param ignore_ast_list 同じ位置のポインタが来ても無視するためのリスト
@param target_statement この計算式を属しているASTノードへのアドレス（基本的にexpression_statementであるノードが入る）
@param inc_dec_flag インクリメントおよびデクリメントが含まれているかどうかのフラグ　１：インクリメントが含まれている　２：デクリメントが含まれている

@return なし
*/
void getArrayOffsetInIncDecInfo(AST *root, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist,
								ARRAY_OFFSET_LIST *array_offset_list, ASTPOINTER_LIST *ignore_ast_list, AST *target_statement, int inc_dec_flag){
	ASTListIterator ast_i;
	//直接参照記号や配列参照が来た場合、オフセットリストを作成する。
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
	//識別子が見つかれば、変数テーブルから存在する変数かどうかを調べてから、オフセットリストを作成する。
	else if(CSTLString_compare_with_char(root->name, "IDENTIFIER") == 0){
		//オフセット情報がないarray_offsetを作成する。
		ARRAY_OFFSET *array_offset;
		VARIABLE_TABLE *variable_table_data;
		OFFSET_LIST *offset_list = OFFSET_LIST_new();
		CSTLString *target_name = CSTLString_new();
		//指定したノードrootが、ignore_ast_listに存在しないかどうか調べるためのフラグ
		int ignore_flag;
		//該当する変数のポインタもしくは配列の次元を調べる。
		int pointer_level, array_level;
		//指定したIDLISTと名前から最も該当する変数テーブルへのアドレスを取得する
		variable_table_data = searchVARIABLE_TABLE_LIST(root->idlist, root->content, vtlist);
		//もし、該当する変数を見つかった場合
		if(variable_table_data != NULL){
			//指定したノードrootが、ignore_ast_listに存在しないかどうか調べる
			ignore_flag = checkIgnoreASTList(root, ignore_ast_list);

			//もし、存在しなければ、配列オフセットリストに追加する
			if(ignore_flag == FAILED){
				getPointerLevelAndArrayLevelFromVARIABLE_TABLE(variable_table_data, &pointer_level, &array_level);

				CSTLString_assign(target_name, CSTLString_c_str(root->content));

				array_offset = new_ARRAY_OFFSET(target_name, target_statement, root, offset_list, pointer_level, array_level, NOT_VIA_ANPASAND, inc_dec_flag);

				//DEBUG_MODEが有効な時ポインタおよび配列変数の各次元のオフセットの情報を出力する
				#ifdef DEBUG_MODE
					if(array_offset != NULL){
						printARRAY_OFFSET(array_offset);
					}
				#endif

				//それをarray_offset_listに追加する
				ARRAY_OFFSET_LIST_push_back_ref(array_offset_list, array_offset);
			}

		}
	}
	//先に、アドレス参照演算子、その他の演算子が見つかったらエラーを出力して強制終了させる。
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
getUpperExpressionRelationNodeの内部処理である。

@param target 検証対象となっている変数
@param root 検証対象のノード
@param output 出力される間接的に関係しているノードへのアドレス
@param mode 下位を調べているか、上位を調べているかの判断を示すフラグ。下位なら０、上位なら１とする。

@return 検索が成功したかどうかのフラグ。成功した場合は１、そうでない場合は０を返す。
*/
int getUpperExpressionRelationNode_Internal(AST *target, AST *root, AST **output, AST **output2, int *mode){
	ASTListIterator p;
	int success_flag = FAILED;

	//自分自身のノードが調べられたら、上位を調べ始める
	if(root == target){
		*mode = 1;
	}
	//そうでない場合は下位を調べ続ける。
	else{
		for(p = ASTList_begin(root->children);
			p != ASTList_end(root->children);
			p = ASTList_next(p)){

			success_flag = getUpperExpressionRelationNode_Internal(target, ASTList_data(p), output, output2, mode);
			//探索が終了した場合はここで打ち切る。
			if(success_flag == SUCCESS){
				break;
			}
			//上位を調べているというフラグが立っている時
			if(*mode == 1){
				//上位ノードがminus_exprである場合
				if(CSTLString_compare_with_char(root->name, "minus_expr") == 0){
					//このフラグを１にすることで終了させる。
					success_flag = SUCCESS;

					//rootノードへのアドレスをoutputへ入力させる
					*output = root;

					//minus_exprより一つ下のノードを入れる
					*output2 = ASTList_data(p);
				}
				//上位ノードが次のようなものである場合
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

					//このフラグを１にすることで終了させる。
					success_flag = SUCCESS;

					//rootノードへのアドレスをoutputへ入力させる
					*output = root;
					break;
				}
			}
		}
	}

	return success_flag;

}
/**
ポインタのオフセットの検証対象となっている変数を示すASTノードtargetから、間接的にどの関係の中に位置しているかどうかを調べ、そのノードのアドレスoutputとして返す。
このとき、targetより明らかに上位であるASTノードrootを設定しなければならない。
また、outputがminus_exprの場合はそのポインタよりひとつ下が左辺か右辺かどうかを調べるために、
そのポインタの一つ下のノードをoutput2へ代入する。

@param target 検証対象となっている変数
@param root 検証対象のノード
@param output 出力される間接的に関係しているノードへのアドレス
@param output2 outputがminus_exprの場合、minus_exprより1つ下のノードがここに代入される
@return 検索が成功したかどうかのフラグ。成功した場合は１、そうでない場合は０を返す。
*/
int getUpperExpressionRelationNode(AST *target, AST *root, AST **output, AST **output2){
	int mode = 0;
	return getUpperExpressionRelationNode_Internal(target, root, output, output2, &mode);
}


/**
primary_expressionとして指定したASTノードrootから、その次の下位である次のノード名を探し出し、そのアドレスをoutputへ出力させ、1を返す。

minus_expr, plus_expr, array_access, direct_ref, IDENTIFIER, primary_expression

なお、outputの内容をNULLにすることで、rootより下位のノードからが検索の対象となる。
また、ポインタ計算の関係上、+-演算演算子を示すようなものやCONSTANT(定数）が来た場合のみ、-1を返す。
見つからない場合は0である。

@param root 指定したASTノード
@param output 上記の見つけたノードへのアドレス

@return 上記の条件で値を返却する。

*/
int searchExpressionOrPointeArrayOrIden(AST *root, AST **output){
	int success_flag = FAILED;
	ASTListIterator p;

	//自分のノードを入れておく。こうすることで自分のノードを見つけてもそれで終わらせないようにする
	if(*output == NULL){
		*output = root;
	}
	//もし、IDENTIFIERかdirect_refかarray_access、primary_expressionおよび、
	//インクリメントデクリメント式や代入式が見つかれば、outputに設定して探索を終わらせる
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
			//rootと同じノードではないか調べる
			if(root != *output){
				*output = root;
				success_flag = SUCCESS;
			}
			//そうでない場合は、自分のノードを探索する
			else{
				for(p = ASTList_begin(root->children);
					success_flag == 0 && p != ASTList_end(root->children);
					p = ASTList_next(p)){
						success_flag = searchExpressionOrPointeArrayOrIden(ASTList_data(p), output);
				}
			}
		}
	//もし、ポインタ以下のprimary以下が来てはいけない式が来た場合、success_flagに-1を代入して終わらせる
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
	//そうでない場合は、子ASTノードについても同じ参照を行う
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
direct_refとして指定したASTノードrootから、その次の下位である次のノード名を探し出し、そのアドレスをoutputへ出力させ、1を返す。

IDENTIFIER array_access, direct_ref, IDENTIFIER, primary_expression
inc_after_expression, inc_expr, dec_after_expr, inc_expr
assignment_expression

なお、outputの内容をNULLにすることで、rootより下位のノードからが検索の対象となる。
見つからない場合は0である。

@param root 指定したASTノード
@param output 上記の見つけたノードへのアドレス

@return 上記の条件で値を返却する。

*/
int searchPointerAccessOrIdentifierOrPrimary(AST *root, AST **output){
	int success_flag = FAILED;
	ASTListIterator p;
	//自分のノードを入れておく。こうすることで自分のノードを見つけてもそれで終わらせないようにする
	if(*output == NULL){
		*output = root;
	}
	//もし、IDENTIFIERかdirect_refかarray_access、primary_expressionが見つかれば、outputに設定して探索を終わらせる
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
			//rootと同じノードではないか調べる
			if(root != *output){
				*output = root;
				success_flag = SUCCESS;
			}
			//そうでない場合は、自分のノードを探索する
			else{
				for(p = ASTList_begin(root->children);
					success_flag == FAILED && p != ASTList_end(root->children);
					p = ASTList_next(p)){
						success_flag = searchPointerAccessOrIdentifierOrPrimary(ASTList_data(p), output);
				}
			}

		}
	//そうでない場合は、子ASTノードについても同じ参照を行う
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
direct_refとして指定したASTノードrootから、以下のノードを探しだし、それをASTリストoutputとして取得する。

IDENTIFIER array_access, direct_ref, IDENTIFIER, primary_expression

なお、outputの内容をNULLにすることで、rootより下位のノードからが検索の対象となる。
見つからない場合は0である。

@param root 指定したASTノード
@param output 上記の見つけたノードへのアドレス
@param getSize 取得した値のサイズを返すための変数。見つからない場合は0にされる。

@return なし
*/
void getPointerAccessOrIdentifierList(AST *root, AST ***output, int *getSize){

	ASTListIterator p;
	AST **temp;
	//もし、IDENTIFIERかdirect_refかarray_accessが見つかれば、outputというリストに追加する
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
					fprintf(stderr,"メモリ不足です！\n");
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
	//そうでない場合は、子ASTノードについても同じ参照を行う
	else{
		for(p = ASTList_begin(root->children);
			p != ASTList_end(root->children);
			p = ASTList_next(p)){
				getPointerAccessOrIdentifierList(ASTList_data(p), output, getSize);
			}
	}
}

/**
識別子の名前を一致する変数を変数リストから探す。このとき、一致する変数を調べたら、ポインタと配列の次元も調べ、オフセットレベル以上であれば、
見つけたことになり、１を返す。そうでなければ、０を返す。また、ignore_ast_listは無視するIDENTIFIERのASTのアドレスリストを見つけるたびに登録
される。もし、ignore_ast_listに登録されているノードなら、それは無視される。また、見つけるのに成功した場合、その該当する変数の配列レベルやポ
インタのレベルも返す。

@param identifier 識別子の名前
@param offset_level オフセットレベル
@param variable_table_list 変数テーブルリスト
@param ignore_ast_list ポインタでの位置が検証済みである、IDENTIFIERを無視するためのASTのアドレスリスト
@param pointer_level 変数リストから見つけた変数のポインタレベル
@param array_level 変数リストから見つけた変数の配列レベル

@return 識別子の名前およびオフセットレベルが条件を満たしていれば１を返し、そうでなければ０を返す。
*/
int checkIdentifierPointerArrayLevel(AST *identifier,int offset_level, VARIABLE_TABLE_LIST *variable_table_list,
 ASTPOINTER_LIST *ignore_ast_list, int *pointer_level, int *array_level){
	int success_flag;

	VARIABLE_TABLE_LISTIterator vi;
	CSTLString *target;

	target = CSTLString_new();
	//ignore_ast_list内にASTノードのアドレスidentifier存在するかどうかのフラグ
	int ignore_flag;

	//変数テーブルデータ
	VARIABLE_TABLE *varidate_table_data = NULL;

	for(vi = VARIABLE_TABLE_LIST_begin(variable_table_list);
		vi != VARIABLE_TABLE_LIST_end(variable_table_list);
		vi = VARIABLE_TABLE_LIST_next(vi)){

		//元の変数名と比較
		CSTLString_assign(target, CSTLString_c_str(VARIABLE_TABLE_LIST_data(vi)->variable_name));
		//指定した変数名と比較するためにポインタや配列を示す記号を全て削除する
		deletePointerAndArraySynbol(target);

		//指定した変数名と変数リストの変数の名前が一致し、変数スコープ内に収まっているとき
		if(CSTLString_compare(identifier->content, target) == 0 &&
			IDLIST_compare_with(identifier->idlist, VARIABLE_TABLE_LIST_data(vi)->idlist) == 1){

			//すでに見つかっていない場合は変数テーブルデータに設定する
			if(varidate_table_data == NULL){
				varidate_table_data = VARIABLE_TABLE_LIST_data(vi);
			}
			//すでに設定していて、ブロックレベルが高ければ、変数テーブルデータに設定する
			else if(varidate_table_data->block_level < VARIABLE_TABLE_LIST_data(vi)->block_level){
				varidate_table_data = VARIABLE_TABLE_LIST_data(vi);
			}
		}

	}

	if(varidate_table_data != NULL){
			//検証対象の変数名からポインタの次元および、配列の次元を計算する
		getPointerLevelAndArrayLevelFromVARIABLE_TABLE(varidate_table_data, pointer_level, array_level);

			//検証対象の変数名からのポインタレベルおよび配列の次元がオフセットレベル以上である場合
			if(offset_level <= *pointer_level + *array_level){
				//指定したASTアドレスidenfierが、ignore_ast_listに存在するかどうか調べる。
				ignore_flag = checkIgnoreASTList(identifier, ignore_ast_list);

				//検証済みのASTノードリストと一致しないと示した場合
				if(ignore_flag == FAILED){
					//成功フラグを立てる
					success_flag = SUCCESS;
				}
			}
	}
	CSTLString_delete(target);
	return success_flag;
}

/**
関数呼び出しを示すASTノードが、登録されている関数に関する情報に含まれているかどうかを調べ、もし、その関数のポインタレベルがオフセットレベルと一致
した場合は、エラーを出力し、強制終了させる。
@param call_function 関数呼び出しを示すASTノード
@param offset_level オフセットレベル
@param function_information_list 関数に関する情報のリスト

@return なし
 */
void checkCallFunction(AST *call_function, int offset_level, FUNCTION_INFORMATION_LIST *function_information_list){
	CSTLString *function_name = CSTLString_new();

	int pointer_level;

	//関数名を取得する
	getStringFromAST(function_name, ASTList_data(ASTList_begin(call_function->children)));
	//関数に関する情報リストから、関数のポインタレベルを取得する
	pointer_level = getPointerLevelFromFUNCTION_INFORMATION_LIST(function_name, function_information_list);
	//もし、レベルを合わしたら、ポインタアクセスを配列で行うことが望ましくないのでエラーを出力させる。
	if(pointer_level == offset_level){
		fprintf(stderr, "#%s#:%d:Shouldn't access from Function Call!!\n", getFileName(), call_function->line);
		fflush(stderr);
		exit(1);
	}
	//一時的に動的に確保していた関数名を開放させる
	CSTLString_delete(function_name);
}

/**
指定したASTノードast_dataがASTアドレスリストignore_ast_listに存在するかどうかを調べる。存在する場合は１をかえす。
存在しない場合は、ast_dataのアドレスをignore_ast_listに追加した上、0を返す。
@param ast_data 指定したASTノード
@param ignore_ast_list 調べる対象のASTアドレスリスト

@return 存在する場合は１を返し、そうでない場合は０を返す
*/
int checkIgnoreASTList(AST *ast_data, ASTPOINTER_LIST *ignore_ast_list){
		//検証済みのASTノードリストと一致するかどうか調べるためのイテレータ
		ASTPOINTER_LISTIterator ignore_iterator;

		//検証済みのASTノードリストと一致するかどうか調べるためのフラグ
		int ignore_flag = FAILED;

		//検証済みのASTノードリストと一致するかどうか調べる
		for(ignore_iterator = ASTPOINTER_LIST_begin(ignore_ast_list);
			ignore_iterator != ASTPOINTER_LIST_end(ignore_ast_list);
			ignore_iterator = ASTPOINTER_LIST_next(ignore_iterator)){
				//指定した変数と検証済みのASTノードリストとアドレスで一致した場合。フラグを立ててbreakする。
				if(*ASTPOINTER_LIST_data(ignore_iterator) == ast_data){
					ignore_flag = SUCCESS;
					break;
				}
			}

		//検証済みのASTノードリストと一致しないと示した場合
		if(ignore_flag == FAILED){
			//この検証したASTノードのアドレスを検証済みのASTノードリストに登録する
			ASTPOINTER_LIST_push_back(ignore_ast_list, ast_data);
		}

		return ignore_flag;
}
/*
指定した各次元の配列やポインタのオフセットリストarray_offsetの内容を出力する。

@param array_offset 出力対象の各次元の配列やポインタのオフセットリスト

@return なし
*/
void printARRAY_OFFSET(ARRAY_OFFSET *array_offset){
	//オフセットリストへのイテレータ
	OFFSET_LISTIterator off_list_i;
	int counter = 0;
	//対象のポインタや配列名を出力する

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
指定した各次元の配列やポインタのオフセットリストarray_offsetの内容を出力する。

@param array_offset_list 出力対象の各次元の配列やポインタのオフセット情報のリスト

@return なし
*/
void printARRAY_OFFSET_LIST(ARRAY_OFFSET_LIST *array_offset_list){
	//	//オフセットリストへのイテレータ
	OFFSET_LISTIterator off_list_i;
	int offset_counter = 1;

	//オフセット情報のリストへのイテレータ
	ARRAY_OFFSET_LISTIterator aoff_list_i;
	int aoffset_counter = 1;

	printf("------ARRAY_OFFSET_LIST_INFO------\n\n");

	for(aoff_list_i = ARRAY_OFFSET_LIST_begin(array_offset_list);
		aoff_list_i != ARRAY_OFFSET_LIST_end(array_offset_list);
		aoffset_counter++, aoff_list_i = ARRAY_OFFSET_LIST_next(aoff_list_i)){

			//対象のポインタや配列名を出力する
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
			//ポインタや配列の各次元のオフセットを出力
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
変数テーブルデータvariable_tableからオフセットリストoffset_listを生成する。

@param offset_list 生成先のオフセットリスト
@param variable_table 変数テーブルデータ

@return なし
*/
void getOFFSET_LISTFromVariableTable(OFFSET_LIST *offset_list, VARIABLE_TABLE *variable_table){
	//変数テーブルのサイズ
	int variable_name_size = CSTLString_size(variable_table->variable_name);
	int location;

	//各要素の内容
	char *offset;
	//配列内に入っているかどうかのフラグ　０：入っていない　１：入っている
	int array_into = 0;
	int array_start, array_end;

	int str_extract_flag;
	//文字列を調べる
	for(location = 0; location < variable_name_size; location++){
		//もし配列の開始が見つかったら、配列に入っている状態にし、配列の内容の最初の位置を設定する
		if(array_into == 0 && *CSTLString_at(variable_table->variable_name, location) == '['){
			array_start = location + 1;
			array_into = 1;
		}
		//配列に入っている状態であり、配列の終わりを示す記号を見つけた場合
		else if( array_into == 1 && *CSTLString_at(variable_table->variable_name, location) == ']'){
			//配列の終わりの位置を設定する
			array_end = location - 1;

			//配列の中身が空だと判断した場合
			if(array_start > array_end || (array_start == array_end && *CSTLString_at(variable_table->variable_name, array_start) == ' ')){
				fprintf(stderr, "空の配列には対応していません！\n");
				exit(1);
			}else{
				//空でないと判断した場合、配列の内容を抽出する。このとき抽出に失敗した場合、内部エラーとして出力し、強制終了する
				offset = calloc(array_end - array_start + 1, sizeof(char));
				str_extract_flag = str_extract(offset, (char*)CSTLString_c_str(variable_table->variable_name), array_start, array_end - array_start);
				if(str_extract_flag == 0){
					fprintf(stderr, "内部エラー\n");
					exit(1);
				}

				//配列の内容をオフセットリストにいれる
				OFFSET_LIST_push_back_alloc(offset_list, offset);

				free(offset);
			}

			//配列の外にいる状態に変更
			array_into = 0;
		}
	}
}

/**
オフセットリストoffset_listの中身を完全に解放させる。

@param offset_list 解放させるoffset_list

@return なし
*/
void deleteOFFSET_LIST(OFFSET_LIST *offset_list){
	OFFSET_LISTIterator off_list_i;
	//オフセットリスト内にある各要素の内容を解放する
	for(off_list_i = OFFSET_LIST_begin(offset_list);
		off_list_i != OFFSET_LIST_end(offset_list);
		off_list_i = OFFSET_LIST_next(off_list_i)){

		free(*OFFSET_LIST_data(off_list_i));
	}

	//オフセットリスト内にある全要素へのリストを解放する
	OFFSET_LIST_clear(offset_list);
	//オフセットリスト自体を解放する
	OFFSET_LIST_delete(offset_list);
}
/**
指定した配列オフセットから、演算後のポインタレベルを求める。演算後のポインタレベルはつぎのとおりである。
演算後のポインタレベル＝この変数の配列とポインタレベルの合計値＋アンパサンドフラグ（挟んでいるなら１、そうでない場合は０）－この配列オフセット内のオフセットリスト
@param array_offset 指定した配列オフセット

@return 求めた演算後のポインタレベルを返す
*/
int getOffsetLevelFromArrayOffset(ARRAY_OFFSET *array_offset){
	return array_offset->pointer_level + array_offset->array_level + array_offset->anpasand_flag - OFFSET_LIST_size(array_offset->offset_list);
}
/**
指定した配列オフセットリストでの演算後のポインタレベルの最大レベルである配列オフセットのアドレスを求める。配列オフセットが空の場合はNULLを代入する。
@param array_offset_list 指定した配列オフセットリスト

@return 求めた演算後のポインタレベルが最大である配列オフセットのアドレスを返す
*/
ARRAY_OFFSET *maxOffsetLevelAddressFromArrayOffsetList(ARRAY_OFFSET_LIST *array_offset_list){
	ARRAY_OFFSET_LIST *aoff_list_i;
	ARRAY_OFFSET *max_array_offset;
	int max_pointer_level;
	int tmp_pointer_level;
	//配列オフセットリストが空でない場合
	if(ARRAY_OFFSET_LIST_size(array_offset_list) != 0){
		//最初のリスト内の演算後のポインタレベルを求める
		max_pointer_level = getOffsetLevelFromArrayOffset(ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(array_offset_list)));
		max_array_offset = ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(array_offset_list));
		//リスト内から演算後のポインタレベルの最大レベルを求める
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
	//配列オフセットリストが空の場合は、０を代入する
	else{
		max_pointer_level = 0;
		max_array_offset = NULL;
	}

	return max_array_offset;

}
/**
指定した配列オフセットリストでの演算後のポインタレベルの最大レベルを求める。配列オフセットが空の場合は０を代入する。
@param array_offset_list 指定した配列オフセットリスト

@return 求めた演算後のポインタレベルを返す
*/
int maxOffsetLevelFromArrayOffsetList(ARRAY_OFFSET_LIST *array_offset_list){
	ARRAY_OFFSET_LIST *aoff_list_i;
	int max_pointer_level;
	int tmp_pointer_level;
	//配列オフセットリストが空でない場合
	if(ARRAY_OFFSET_LIST_size(array_offset_list) != 0){
		//最初のリスト内の演算後のポインタレベルを求める
		max_pointer_level = getOffsetLevelFromArrayOffset(ARRAY_OFFSET_LIST_data(ARRAY_OFFSET_LIST_begin(array_offset_list)));

		//リスト内から演算後のポインタレベルの最大レベルを求める
		for(aoff_list_i = ARRAY_OFFSET_LIST_next(ARRAY_OFFSET_LIST_begin(array_offset_list));
			aoff_list_i != ARRAY_OFFSET_LIST_end(array_offset_list);
			aoff_list_i = ARRAY_OFFSET_LIST_next(aoff_list_i)){

				tmp_pointer_level = getOffsetLevelFromArrayOffset(ARRAY_OFFSET_LIST_data(aoff_list_i));

				if(max_pointer_level < tmp_pointer_level){
					max_pointer_level = tmp_pointer_level;
				}
		}
	}
	//配列オフセットリストが空の場合は、０を代入する
	else{
		max_pointer_level = 0;
	}

	return max_pointer_level;

}

/**
対象のASTノードから、演算後のポインタレベルが指定されたポインタレベルと配列レベルの合計と一致するような
変数の配列オフセットを指定された配列オフセットリストから探し出し、見つかったらアドレスを取得する。

@param root 対象のASTノード
@param array_offset_list 対象の配列オフセットリスト
@param pointer_level 指定するポインタレベル
@param array_level 指定する配列レベル

@return 演算後のポインタレベルと指定されたポインタレベルと配列レベルの合計が一致するような変数を返す。失敗した場合はNULLを返す。
 */

ARRAY_OFFSET *searchOffsetLevelAddressFromArrayOffsetList(AST *root, ARRAY_OFFSET_LIST *array_offset_list,
		int pointer_level, int array_level){

	ARRAY_OFFSET *result = NULL;

	ASTListIterator ast_i;

	ARRAY_OFFSET_LISTIterator aoff_list_i;

	//ASTノードから識別子を探索し、見つかった場合
	if(CSTLString_compare_with_char(root->name, "IDENTIFIER") == 0){
		//配列オフセットリストから該当する変数を探す
		for(aoff_list_i = ARRAY_OFFSET_LIST_begin(array_offset_list);
			aoff_list_i != ARRAY_OFFSET_LIST_end(array_offset_list);
			aoff_list_i = ARRAY_OFFSET_LIST_next(aoff_list_i)){

			//配列オフセットリストから該当する変数をもった配列オフセット情報を見つけ、
			//その配列オフセット情報からの演算後のポインタレベルがポインタレベルと配列レベルの合計と一致した場合
			if(root == ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_address &&
					getOffsetLevelFromArrayOffset(ARRAY_OFFSET_LIST_data(aoff_list_i)) == pointer_level + array_level){
				//そのアドレスを取得し、探索を終了させる
				result = ARRAY_OFFSET_LIST_data(aoff_list_i);
				break;
			}

		}
	}
	//見つからない場合は、子ノードの探索を行い
	//配列オフセットのアドレスが取得できるまで探索を行う
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
指定した式から、必要なオフセット情報を取得する。
@param expression 指定した式に関するASTノード
@param function_information_list 関数に関する情報のリスト
@param vtlist 検証対象の式をマークするための変数リスト
@param ignore_ast_list ポインタでの位置が検証済みである、IDENTIFIERを無視するためのASTのアドレスリスト
@param array_offset_list 各ポインタおよび配列ごとのオフセットのリスト
@param target_expression この左辺式の上位に位置するASTノード
@param switch_mode 直接アクセスおよび配列アクセスを探すか、IDENTIFIERを探すかどうかのスイッチフラグ ０：両方さがす　１：direct_refやarray_accessのみ探す
@param allow_subeffect 副作用の式を許すかどうかのフラグ １：許す ０：許さない
@return なし
*/
void getExpressionOffsetInfo(AST *expression, FUNCTION_INFORMATION_LIST *function_information_list, VARIABLE_TABLE_LIST *vtlist, ASTPOINTER_LIST *ignore_ast_list,
 ARRAY_OFFSET_LIST * array_offset_list, AST *target_expression, int *switch_mode, int allow_subeffect){
	ASTListIterator p;
	int pointer_level, array_level;
	//direct_refおよびarray_accessを見つけたら、１次以降のレベルを確認する
	if(CSTLString_compare_with_char(expression->name, "direct_ref") == 0 ||
		CSTLString_compare_with_char(expression->name, "array_access") == 0){
		ARRAY_OFFSET *array_offset = NULL;
		//ポインタおよび配列変数の各次元のオフセットを求める
		getPointerArrayOffset(expression, function_information_list, vtlist, 0, ignore_ast_list, &array_offset, target_expression, NOT_VIA_ANPASAND, NOT_INC_DEC);

		//DEBUG_MODEが有効な時ポインタおよび配列変数の各次元のオフセットの情報を出力する
		#ifdef DEBUG_MODE
			if(array_offset != NULL){
				printARRAY_OFFSET(array_offset);
			}
		#endif
		//ポインタおよび配列変数の各次元のオフセットの情報が取得できた場合、これに関する情報をこの情報のリストへ入れる
		if(array_offset != NULL){
			ARRAY_OFFSET_LIST_push_back_ref(array_offset_list, array_offset);
		}
		//スイッチフラグを１にする
		*switch_mode = 1;
	}
	//スイッチフラグが０であり、IDENTIFIERが見つかった場合
	else if(*switch_mode == 0 && CSTLString_compare_with_char(expression->name, "IDENTIFIER") == 0 ){
		//オフセット情報がないarray_offsetを作成する。
		ARRAY_OFFSET *array_offset;
		VARIABLE_TABLE *variable_table_data;
		OFFSET_LIST *offset_list = OFFSET_LIST_new();
		CSTLString *target_name = CSTLString_new();
		int ignore_flag;

		//指定したIDLISTと名前から最も該当する変数テーブルへのアドレスを取得する
		variable_table_data = searchVARIABLE_TABLE_LIST(expression->idlist, expression->content, vtlist);
		if(variable_table_data != NULL){
			//指定したノードexpressionが、ignore_ast_listに存在しないかどうか調べる
			ignore_flag = checkIgnoreASTList(expression, ignore_ast_list);

			//もし、存在しなければ、配列オフセットリスト
			if(ignore_flag == FAILED){
				getPointerLevelAndArrayLevelFromVARIABLE_TABLE(variable_table_data, &pointer_level, &array_level);

				CSTLString_assign(target_name, CSTLString_c_str(expression->content));

				array_offset = new_ARRAY_OFFSET(target_name, target_expression, expression, offset_list, pointer_level, array_level, NOT_VIA_ANPASAND, NOT_INC_DEC);

				//DEBUG_MODEが有効な時ポインタおよび配列変数の各次元のオフセットの情報を出力する
				#ifdef DEBUG_MODE
					if(array_offset != NULL){
						printARRAY_OFFSET(array_offset);
					}
				#endif

				//それをarray_offset_listに追加する
				ARRAY_OFFSET_LIST_push_back_ref(array_offset_list, array_offset);
			}
		}else{
			fprintf(stderr,"#%s#:%d: variable %s is undeclarated!!\n",getFileName(), expression->line, CSTLString_c_str(expression->content));
			exit(1);
		}

	}
	//インクリメント演算子が来た場合は、インクリメントを通した配列オフセットリストを取得する
	else if(CSTLString_compare_with_char(expression->name, "inc_expr") == 0 ||
		CSTLString_compare_with_char(expression->name, "inc_after_expr") == 0){
		//副作用式を許す場合は、インクリメントを通した配列オフセットリストを取得する
		if(allow_subeffect == ALLOW_SUBEFF){
			getArrayOffsetInIncDecInfo(expression, function_information_list, vtlist,
								array_offset_list, ignore_ast_list, target_expression, VIA_INC);
		}
		//そうでない場合は、望ましくない処理とみなし、強制終了させる
		else{
			fprintf(stderr,"#%s#:%d: This Expression is NOT arrow to contain Inclement expression!!\n",getFileName(), expression->line);
			exit(1);
		}
	}
	//デクリメント演算子が来た場合は、インクリメントを通した配列オフセットリストを取得する
	else if(CSTLString_compare_with_char(expression->name, "dec_expr") == 0 ||
		CSTLString_compare_with_char(expression->name, "dec_after_expr") == 0){
		//副作用式を許す場合は、インクリメントを通した配列オフセットリストを取得する

		if(allow_subeffect == ALLOW_SUBEFF){
			getArrayOffsetInIncDecInfo(expression, function_information_list, vtlist,
								array_offset_list, ignore_ast_list, target_expression, VIA_DEC);
		}
		//そうでない場合は、望ましくない処理とみなし、強制終了させる
		else{
			fprintf(stderr,"#%s#:%d: This Expression is NOT arrow to contain Inclement expression!!\n",getFileName(), expression->line);
			exit(1);
		}
	}
	//子ASTノードを参照する
	for(p = ASTList_begin(expression->children);
		p != ASTList_end(expression->children);
		p = ASTList_next(p)){
			getExpressionOffsetInfo(ASTList_data(p), function_information_list, vtlist, ignore_ast_list, array_offset_list, target_expression, switch_mode, allow_subeffect);
	}

}

/**
指定した引数から、必要なオフセット情報を取得する。
@param argument 指定した引数に関するASTノード
@param function_information_list 関数に関する情報のリスト
@param vtlist 検証対象の式をマークするための変数リスト
@param ignore_ast_list ポインタでの位置が検証済みである、IDENTIFIERを無視するためのASTのアドレスリスト
@param array_offset_list 各ポインタおよび配列ごとのオフセットのリスト
@param target_expression この左辺式の上位に位置するASTノード
@param switch_mode 直接アクセスおよび配列アクセスを探すか、IDENTIFIERを探すかどうかのスイッチフラグ ０：両方さがす　１：direct_refやarray_accessのみ探す
@return なし
*/
void getArgumentOffsetInfo(AST *argument, FUNCTION_INFORMATION_LIST *function_information_list,
		VARIABLE_TABLE_LIST *vtlist, ASTPOINTER_LIST *ignore_ast_list, ARRAY_OFFSET_LIST * array_offset_list,
		AST *target_expression, int *switch_mode){

	getExpressionOffsetInfo(argument, function_information_list, vtlist, ignore_ast_list, array_offset_list, target_expression, switch_mode, DENIDE_SUBEFF);

}

/**
指定した式から、必要なオフセット情報を取得する。これは副作用の式を許す。
@param expression 指定した式に関するASTノード
@param function_information_list 関数に関する情報のリスト
@param vtlist 検証対象の式をマークするための変数リスト
@param ignore_ast_list ポインタでの位置が検証済みである、IDENTIFIERを無視するためのASTのアドレスリスト
@param array_offset_list 各ポインタおよび配列ごとのオフセットのリスト
@param target_expression この左辺式の上位に位置するASTノード
@param switch_mode 直接アクセスおよび配列アクセスを探すか、IDENTIFIERを探すかどうかのスイッチフラグ ０：両方さがす　１：direct_refやarray_accessのみ探す
@return なし
*/
void getSingleExpressionOffsetInfo(AST *expression, FUNCTION_INFORMATION_LIST *function_information_list,
		VARIABLE_TABLE_LIST *vtlist, ASTPOINTER_LIST *ignore_ast_list,
 ARRAY_OFFSET_LIST * array_offset_list, AST *target_expression, int *switch_mode){
 	getExpressionOffsetInfo(expression, function_information_list, vtlist, ignore_ast_list, array_offset_list, target_expression, switch_mode, ALLOW_SUBEFF);
 }

/**
配列オフセット情報から、任意の次元までの配列式を生成する。

@param output 配列式を生成される文字列
@param array_offset 対象の配列オフセット
@param output_level 出力したい次元(このとき、配列オフセットを超える値を入れた場合は、配列オフセットが次元までの配列式を出力する)

@return なし
*/

void createArrayExpression(CSTLString *output, ARRAY_OFFSET *array_offset, int output_level){
	//オフセットリストのイテレータ
	OFFSET_LISTIterator off_list_i;
	//次元をカウントするカウンタ
	int counter;

	//変数名を先に代入する
	CSTLString_assign(output, CSTLString_c_str(array_offset->variable_name));

	//カッコ内の式を追加していく
	for(counter = 0, off_list_i = OFFSET_LIST_begin(array_offset->offset_list);
		counter < output_level && off_list_i != OFFSET_LIST_end(array_offset->offset_list);
		counter++, off_list_i = OFFSET_LIST_next(off_list_i)){
			CSTLString_printf(output, 1, "[ %s ]", *OFFSET_LIST_data(off_list_i));
		}

}

/**
配列オフセット情報から、検証用変数に使われる配列式を生成し、オフセットレベルを返す。
@param output 生成先の文字列
@param array_offset 対象の配列オフセット

@return 配列オフセット情報から生成されたオフセットレベルを返す。
 */
int createValidateVariableArrayExpression(CSTLString *output, ARRAY_OFFSET *array_offset){
	int offset_level_counter;

	OFFSET_LISTIterator off_list_i;

	CSTLString *basis_location_content = CSTLString_new();
	CSTLString *array_string = CSTLString_new();


	//ポインタと配列の記号を削除する
	deletePointerAndArraySynbol(output);

	//配列オフセット情報から、配列式部分を出力する
	for(offset_level_counter = 1, off_list_i = OFFSET_LIST_begin(array_offset->offset_list);
		off_list_i != OFFSET_LIST_end(array_offset->offset_list);
		offset_level_counter++, off_list_i = OFFSET_LIST_next(off_list_i)){

		//次のレベルのための配列を生成する。
		CSTLString_printf(basis_location_content, 0, "basis_location_%d_%s%s", offset_level_counter, (char*)CSTLString_c_str(array_offset->variable_name), (char*)CSTLString_c_str(array_string));
		CSTLString_printf(array_string, 1," [ %s + %s ]", *OFFSET_LIST_data(off_list_i), (char*)CSTLString_c_str(basis_location_content));

	}

	//変数式に配列式を追加する
	CSTLString_printf(output, 1, "%s", CSTLString_c_str(array_string));

	//このときのオフセットレベルを返す
	return offset_level_counter;
}

/**
配列オフセットリストfromlist内のmove_start以降のデータをすべて、もう一方の配列オフセットリストtolistに移動させる。
@param fromlist 移動もとの配列オフセットリスト
@param tolist 移動先の配列オフセットリスト
@param move_start 移動させたいデータの位置(先頭から０番目とする)

@return なし
 */
void moveArrayOffsetList(ARRAY_OFFSET_LIST *fromlist, ARRAY_OFFSET_LIST *tolist, int move_start){
	ARRAY_OFFSET_LISTIterator aoff_i;
	int i;
	int count = 0;
	//移動位置が負の値の場合はエラーを出力し、強制終了させる
	if(move_start < 0){
		fprintf(stderr,"%d:配列オフセットの動かす値が不正です!\n");
		exit(1);
	}else{
		//移動させている個数分を数えながらfromlistのデータをtolistに追加する
		for(aoff_i = ARRAY_OFFSET_LIST_begin(fromlist);
			aoff_i != ARRAY_OFFSET_LIST_end(fromlist);
			aoff_i = ARRAY_OFFSET_LIST_next(aoff_i)){
				//移動させたいデータの位置が0になれば、そこからデータを移動させる
				if(move_start == 0){
					ARRAY_OFFSET_LIST_push_back_ref(tolist, ARRAY_OFFSET_LIST_data(aoff_i));
					count++;
				}else{
					move_start--;
				}
		}
		//末尾から移動させた個数分削除する
		for(i = 0; i < count; i++){
			ARRAY_OFFSET_LIST_pop_back(fromlist);
		}
	}
}
/**
配列オフセットリストfromlist内のmove_start以降のデータをすべて、もう一方の配列オフセットリストtolistにコピーさせる。
@param fromlist コピー元の配列オフセットリスト
@param tolist コピー先の配列オフセットリスト
@param move_start 移動させたいデータの位置(先頭から０番目とする)

@return なし
 */
void copyArrayOffsetList(ARRAY_OFFSET_LIST *fromlist, ARRAY_OFFSET_LIST *tolist, int move_start){
	ARRAY_OFFSET_LISTIterator aoff_i;
	int i;
	//移動位置が負の値の場合はエラーを出力し、強制終了させる
	if(move_start < 0){
		fprintf(stderr,"%d:配列オフセットの動かす値が不正です!\n");
		exit(1);
	}else{
		//コピーさせている個数分を数えながらfromlistのデータをtolistに追加する
		for(aoff_i = ARRAY_OFFSET_LIST_begin(fromlist);
			aoff_i != ARRAY_OFFSET_LIST_end(fromlist);
			aoff_i = ARRAY_OFFSET_LIST_next(aoff_i)){
				//コピーさせたいデータの位置が0になれば、そこからデータを移動させる
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
変数テーブルから、変数の定義に対するノードに該当する情報を探し、それに対する配列オフセット情報を取得する。
@param declarator_array_offset_list 取得先の配列オフセット情報
@param declarator_expression 変数定義までのASTアドレス
@param target_expression 対象のdeclarator_with_initへのASTアドレス
@param vtlist 調べる先の変数テーブル

@return なし
*/
void getDeclaratorArrayOffset(ARRAY_OFFSET_LIST *declarator_array_offset_list, AST *declarator_expression, AST *target_expression, VARIABLE_TABLE_LIST *vtlist){

	//変数のポインタレベルや配列レベル
	int pointer_level, array_level;

	//変数名を作成する
	CSTLString *variable_name = CSTLString_new();
	getStringFromAST(variable_name, declarator_expression);

	//変数テーブルを調べる
	VARIABLE_TABLE *variable_table_data = NULL;
	variable_table_data = searchVARIABLE_TABLE_LIST(target_expression->idlist, variable_name, vtlist);

	//変数名からポインタや配列を示す記号を削除する
	deletePointerAndArraySynbol(variable_name);

	//もし、変数テーブルから該当する変数名を取得できたら
	if(variable_table_data != NULL){

		getPointerLevelAndArrayLevelFromVARIABLE_TABLE(variable_table_data, &pointer_level, &array_level);

		//OFFSET_LIST(空)を生成
		OFFSET_LIST *offset_list = OFFSET_LIST_new();
		//ARRAY_OFFSETを生成
		ARRAY_OFFSET *new_array_offset = new_ARRAY_OFFSET(variable_name, target_expression, target_expression,
								offset_list, pointer_level, array_level, NOT_VIA_ANPASAND, NOT_INC_DEC);

		//配列オフセットリストに追加
		ARRAY_OFFSET_LIST_push_back_ref(declarator_array_offset_list, new_array_offset);
	}
	//できなかったら、エラーを出力して終了する。
	else{
		fprintf(stderr,"#%s#:%d:Undefine IDENTIFIRE is %s!\n", getFileName(), target_expression->line, CSTLString_c_str(variable_name));
		exit(1);
	}
}

/**
配列オフセットリストarray_offset_listから、指定した変数名を探索し、
見つかればその変数名へのアドレスを返す。

@param array_offset_list 探索対象の配列オフセットリスト
@param name 探索したい変数名

@return 見つかれば変数名へのアドレスを返す。そうでなければNULLを返す。
 */
ARRAY_OFFSET *searchARRAY_OFFSET_LIST(ARRAY_OFFSET_LIST *array_offset_list, CSTLString *name){

	ARRAY_OFFSET_LISTIterator a_i;
	ARRAY_OFFSET *result = NULL;
	//配列オフセット内の変数名を比較するのに使用する変数
	CSTLString *aol_vname = CSTLString_new();
	//探索したい変数名を比較するのに使用する変数
	CSTLString *s_vname = CSTLString_new();

	for(a_i = ARRAY_OFFSET_LIST_begin(array_offset_list);
		a_i != ARRAY_OFFSET_LIST_end(array_offset_list);
		a_i = ARRAY_OFFSET_LIST_next(a_i)){

		CSTLString_assign(aol_vname, CSTLString_c_str(ARRAY_OFFSET_LIST_data(a_i)->variable_name));
		CSTLString_assign(s_vname, CSTLString_c_str(name));

		//変数名以外の部分（引数番号を示す部分など）を除去する
		CSTLString_delete_tail_str(aol_vname, "#");
		CSTLString_delete_tail_str(s_vname, "#");
		//配列オフセットリスト内の変数名と探している変数名の名前が一致した場合、resultにそのデータを代入し、終了する
		if(CSTLString_compare(aol_vname, s_vname) == 0){
			result = ARRAY_OFFSET_LIST_data(a_i);
			break;
		}
	}

	//比較用に使用していた変数を開放させる
	CSTLString_delete(aol_vname);
	CSTLString_delete(s_vname);
	return result;
}

/**
対象の配列オフセットリストtarget_array_offset_listに対して、対象から取り除きたい
配列オフセットリストdelete_array_offset_listの名前に該当する配列オフセット情報を
削除する。

@param target_array_offset_list 対象の配列オフセットリスト
@param delete_array_offset_list 対象から取り除きたい配列オフセットリスト

@return なし
 */
void minusArrayOffsetList(ARRAY_OFFSET_LIST *target_array_offset_list, ARRAY_OFFSET_LIST *delete_array_offset_list){

	ARRAY_OFFSET_LISTIterator d_aoff_i, t_aoff_i;

	//delete_array_offset_listから変数名を1つずつ取り出す
	for(d_aoff_i = ARRAY_OFFSET_LIST_begin(delete_array_offset_list);
		d_aoff_i != ARRAY_OFFSET_LIST_end(delete_array_offset_list);
		d_aoff_i = ARRAY_OFFSET_LIST_next(d_aoff_i)){

		//delete_array_offset_listに削除したい配列が存在しないかどうか探す
			for(t_aoff_i = ARRAY_OFFSET_LIST_begin(target_array_offset_list);
				t_aoff_i != ARRAY_OFFSET_LIST_end(target_array_offset_list);
				){

				//見つけたら、該当する配列オフセット情報を削除する
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
配列オフセットリストに配列オフセット情報を追加する。ただし、変数名が重複するのであれば、追加しない。

@param target_array_offset_list 追加先の配列オフセットリスト
@param array_offset 追加する配列オフセット情報

@return なし
 */
void ARRAY_OFFSET_LIST_push_back_ref_not_dup(ARRAY_OFFSET_LIST *target_array_offset_list, ARRAY_OFFSET *array_offset){
	int dup_flag = 0;

	ARRAY_OFFSET_LISTIterator a_i;

	//配列オフセットリストに追加する配列オフセット情報に、同じ名前がないかどうか調べる
	for(a_i = ARRAY_OFFSET_LIST_begin(target_array_offset_list);
		a_i != ARRAY_OFFSET_LIST_end(target_array_offset_list);
		a_i = ARRAY_OFFSET_LIST_next(a_i)){

		//もし、重複する名前が存在すれば、探索を終了させる
		if(CSTLString_compare(ARRAY_OFFSET_LIST_data(a_i)->variable_name, array_offset->variable_name) == 0){
			dup_flag = 1;
			break;
		}
	}

	//もし、配列オフセットリストから重複する配列オフセット情報が存在しなければ、追加する
	if(dup_flag == 0){
		ARRAY_OFFSET_LIST_push_back_ref(target_array_offset_list, array_offset);
	}
}

/**
ASTのポインタリストの内容を出力させる。

@param astpointer_list ASTのポインタリスト

@return なし
 */
void printASTPOINTER_LIST(ASTPOINTER_LIST *astpointer_list){
	ASTPOINTER_LISTIterator a_i;

	for(a_i = ASTPOINTER_LIST_begin(astpointer_list);
		a_i != ASTPOINTER_LIST_end(astpointer_list);
		a_i = ASTPOINTER_LIST_next(a_i)){

		//ポインタのアドレス・行数・ノード名を出力させる
		printf("・%p line = %d %s\n", *ASTPOINTER_LIST_data(a_i), (*ASTPOINTER_LIST_data(a_i))->line,
				CSTLString_c_str((*ASTPOINTER_LIST_data(a_i))->name));
	}
}
