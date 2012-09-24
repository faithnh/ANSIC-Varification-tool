#include "WriteVelificationStatement.h"
#include "xmlWriter/XmlWriter.h"
#include <stdio.h>
#include<limits.h>

//除算か剰余算かどうかのフラグ
#define TYPE_DIV 0
#define TYPE_MOD 1
/*
 * WriteVelificationStatement.c
 *
 *  Created on: 2012/06/11
 *      Author: fken-2
 */

/*配列範囲外参照と未定義処理の検証式の生成*/
void writeArrayCheck(CSTLString *output, ARRAY_OFFSET_LISTIterator aoff_list_i, int undefined_control_check, int array_unbound_check){
	int array_offset_level;

	int offset_level_counter;

	OFFSET_LISTIterator off_list_i;
	//オフセットレベルの取得
	array_offset_level = OFFSET_LIST_size(ARRAY_OFFSET_LIST_data(aoff_list_i)->offset_list);

	//オフセットレベルが0を超える場合（すなわち、オフセット情報が存在する場合）
	if(array_offset_level > 0){

	//配列の形を保持する情報（処理中で使用される）
		CSTLString *array_string = CSTLString_new();
		CSTLString *basis_location_content = CSTLString_new();
		CSTLString_assign(array_string, "");
		CSTLString_assign(basis_location_content, "");

		//オフセット情報を参照する
		for(offset_level_counter = 1, off_list_i = OFFSET_LIST_begin(ARRAY_OFFSET_LIST_data(aoff_list_i)->offset_list);
			off_list_i != OFFSET_LIST_end(ARRAY_OFFSET_LIST_data(aoff_list_i)->offset_list);
			offset_level_counter++, off_list_i = OFFSET_LIST_next(off_list_i)){
				int is_expression_flag = isExpression(*OFFSET_LIST_data(off_list_i));
				CSTLString *statement = CSTLString_new();

				//未定義処理チェックフラグが成り立っている場合、
				//レベルごとの未定義処理の検証式を生成する。未定義処理の検証式の形式は以下の通りである。
				//if(defined_階層_変数名 == 0 && max_size_階層_変数名 == 0){
				//	printf("#ファイル名#:行数: detected undefine pointer access in variable 変数名);
				//	assert(0);
				//	リターン式;
				//}
				if(undefined_control_check){

					CSTLString_printf(statement,0,"if(*defined_%d_%s%s == 0 && *malloc_flag_%d_%s%s == 0){\n",
								 offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string),
								 offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string)
							);

					CSTLString_printf(statement,1,"printf(\"#%s#:%d: detected undefine pointer access in variable %s\");\n ",getFileName(), ARRAY_OFFSET_LIST_data(aoff_list_i)->target_statement->line, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name));

					CSTLString_printf(statement, 1, "assert(0);\n");

					//リターン命令の返却型に応じる変更(もし、void型であれば、「return;」にする)
					if(CSTLString_compare_with_char(ARRAY_OFFSET_LIST_data(aoff_list_i)->target_statement->return_type, "void") == 0){
						CSTLString_printf(statement, 1, "return;\n");
					}else{
						CSTLString_printf(statement, 1, "return 1;\n");
					}

					CSTLString_printf(statement, 1, "}\n");

				}

				//配列範囲外チェックフラグが成り立っていた場合、
				//レベルごとの配列範囲外参照の検証式を生成する。配列範囲外参照の式の形式は以下の通りである
				//if(0 > 式 + 基本位置 || 式 + 基本位置 < 対象変数の配列長){
				//	printf("#ファイル名#:行数: detected unbound access in variable 変数名 basis_location = %d 式 = %d\n", basis_location, 式);
				//	assert(0);
				//	リターン式;
				//}
				if(array_unbound_check){
					CSTLString_printf(statement,1,"if(0 > %s + basis_location_%d_%s%s){\n",
								 *OFFSET_LIST_data(off_list_i), offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string));
					/*
					CSTLString_printf(statement,1,"printf(\"#%s#:%d:detected unbound access in variable %s ",getFileName(), ARRAY_OFFSET_LIST_data(aoff_list_i)->target_statement->line, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name));

					//basis_locationの内容も出力する
					CSTLString_printf(statement,1," basis_location = %%d ");

					//もし、オフセットの内容が式であれば、式＝値という形で出力する
					if(is_expression_flag == 1){
						CSTLString_printf(statement,1,"(%s = %%d)\\n\"", *OFFSET_LIST_data(off_list_i));
						//basis_locationの内容を含めた引数の内容を入れる
						CSTLString_printf(statement,1,", basis_location_%d_%s%s, %s",offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string) , *OFFSET_LIST_data(off_list_i));
					}

					//そうでなければ、値という形で出力する
					else{
						CSTLString_printf(statement,1,"(%s)\\n\"", *OFFSET_LIST_data(off_list_i));
						//basis_locationの内容の引数の内容を入れる
						CSTLString_printf(statement,1,", basis_location_%d_%s%s", offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string));
					}
					CSTLString_printf(statement, 1, ");\n");
					*/
					//エラーのＸＭＬを出力
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

					//リターン命令の返却型に応じる変更(もし、void型であれば、「return;」にする)
					if(CSTLString_compare_with_char(ARRAY_OFFSET_LIST_data(aoff_list_i)->target_statement->return_type, "void") == 0){
						CSTLString_printf(statement, 1, "return;\n");
					}else{
						CSTLString_printf(statement, 1, "return 1;\n");
					}

					CSTLString_printf(statement, 1, "}\n");
					CSTLString_printf(statement, 1, "if(%s + basis_location_%d_%s%s >= *max_size_%d_%s%s){",
							*OFFSET_LIST_data(off_list_i), offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string),
							offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string));
					//エラーのＸＭＬを出力
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

					//リターン命令の返却型に応じる変更(もし、void型であれば、「return;」にする)
					if(CSTLString_compare_with_char(ARRAY_OFFSET_LIST_data(aoff_list_i)->target_statement->return_type, "void") == 0){
						CSTLString_printf(statement, 1, "return;\n");
					}else{
						CSTLString_printf(statement, 1, "return 1;\n");
					}

					CSTLString_printf(statement, 1, "}\n");
				}
				CSTLString_printf(output, 1, "%s", (char*)CSTLString_c_str(statement));

				//次のレベルのための配列を生成する。
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
	//式に関するCSTL文字列を生成
	CSTLString *identifires_list = CSTLString_new();
	CSTLString *parameter_list = CSTLString_new();
	CSTLString *output = CSTLString_new();
	//次のような式を生成する
	//if( (式) == 0 ){ printf("#ファイル名#:行数:detected zero (divition/mod) operation in expression 式"); assert(0); リターン式; }
	CSTLString_printf(statement, 0, "if( (%s) == 0 ){ printf(\"#%s#:%d:detected zero ", CSTLString_c_str(DIVITION_INFORMATION_LIST_data(di_i)->statement),
		getFileName(), DIVITION_INFORMATION_LIST_data(di_i)->target_expression->line);

	//式のタイプが除算か剰余算によってメッセージを変える
	if(DIVITION_INFORMATION_LIST_data(di_i)->type == TYPE_DIV){
		CSTLString_printf(statement, 1, "division ");
	}else{
		CSTLString_printf(statement, 1, "mod ");
	}
	CSTLString_printf(statement, 1, "oparation in expression %s ", CSTLString_c_str(DIVITION_INFORMATION_LIST_data(di_i)->statement));

	//配列オフセットリストから各識別子の情報を出力させ、式に追加していく
	for(aoff_list_i = ARRAY_OFFSET_LIST_begin(DIVITION_INFORMATION_LIST_data(di_i)->identifiers);
		aoff_list_i != ARRAY_OFFSET_LIST_end(DIVITION_INFORMATION_LIST_data(di_i)->identifiers);
		aoff_list_i = ARRAY_OFFSET_LIST_next(aoff_list_i)){
			createArrayExpression(output, ARRAY_OFFSET_LIST_data(aoff_list_i), INT_MAX);
			CSTLString_printf(identifires_list, 1, "%s = %%d", CSTLString_c_str(output));
			//識別子情報の最後でなければ、カンマ区切りする
			if(ARRAY_OFFSET_LIST_next(aoff_list_i) != ARRAY_OFFSET_LIST_end(DIVITION_INFORMATION_LIST_data(di_i)->identifiers)){
				CSTLString_printf(identifires_list, 1,", ");
			}

			CSTLString_printf(parameter_list, 1, ", %s", CSTLString_c_str(output));

		}
	CSTLString_printf(statement, 1, "( %s )\"%s); assert(0);", CSTLString_c_str(identifires_list), CSTLString_c_str(parameter_list));

	//リターン命令の返却型に応じる変更(もし、void型であれば、「return;」にする)
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
