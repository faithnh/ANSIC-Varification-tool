#include "XmlWriter.h"
#include "../../Library/CSTLString.h"
/*
 * XmlWriter.c
 *
 *  Created on: 2012/09/07
 *      Author: faithnh
 */


void xmlSanitize(CSTLString *str){
	CSTLString_replace_string(str,"%","%%");
	CSTLString_replace_string(str,"\\","\\\\");
	CSTLString_replace_string(str,"&","&amp;");
	CSTLString_replace_string(str,"\"","&quot;");
	CSTLString_replace_string(str,"<","&lt;");
	CSTLString_replace_string(str,">","&gt");
	CSTLString_replace_string(str,"\'","&apos;");
}
/**
 * 右辺および左辺の配列オフセット情報から事前状態をXMLで出力させる
 */
void writeFormerVariableXML(FILE *output, ARRAY_OFFSET_LIST *left_array_offset_list, ARRAY_OFFSET_LIST *right_array_offset_list, VARIABLE_TABLE_LIST *vtlist){
	ARRAY_OFFSET_LISTIterator i;
	fprintf(output, "printf(\"<before_variable_info>\");");
	for(i = ARRAY_OFFSET_LIST_begin(left_array_offset_list);
			i != ARRAY_OFFSET_LIST_end(left_array_offset_list);
			i = ARRAY_OFFSET_LIST_next(i)){
			ARRAY_OFFSET *data = ARRAY_OFFSET_LIST_data(i);
			VARIABLE_TABLE *variable = searchVARIABLE_TABLE_LIST(data->variable_address->idlist, data->variable_name, vtlist);
			CSTLString *variable_type_name = getTypeOfVariable(data->variable_name, variable);
			int array_level, pointer_level;
			//配列とポインタのレベルを変数から取得
			getPointerLevelAndArrayLevelFromVARIABLE_TABLE(variable, &pointer_level, &array_level);
			if(OFFSET_LIST_size(data->offset_list) == 0){
				if(array_level + pointer_level > 0){
					fprintf(output, "printf(\"<variable type=#dquot#%s#dquot# name=#dquot#%s#dquot# value=#dquot#%%d#dquot# max_size=#dquot#%%d#dquot# basis_location=#dquot#%%d#dquot# defined=#dquot#%%d#dquot# alloced=#dquot#%%d#dquot#></variable>\", %s, *max_size_1_%s, basis_location_1_%s, *defined_1_%s, *malloc_flag_1_%s);\n",
											CSTLString_c_str(variable_type_name), CSTLString_c_str(data->variable_name), CSTLString_c_str(data->variable_name),
											CSTLString_c_str(data->variable_name), CSTLString_c_str(data->variable_name), CSTLString_c_str(data->variable_name),
											CSTLString_c_str(data->variable_name));
				}else{
					fprintf(output, "printf(\"<variable type=#dquot#%s#dquot# name=#dquot#%s#dquot# value=#dquot#%%d#dquot#></variable>\", %s);\n",
							CSTLString_c_str(variable_type_name), CSTLString_c_str(data->variable_name), CSTLString_c_str(data->variable_name));
				}
			}else{

				fprintf(output, "printf(\"<variable type=#dquot#%s#dquot# name=#dquot#%s#dquot# value=#dquot##dquot# max_size=#dquot#%%d#dquot# basis_location=#dquot#%%d#dquot# defined=#dquot#%%d#dquot# alloced=#dquot#%%d#dquot#></variable>\", *max_size_1_%s, basis_location_1_%s, *defined_1_%s, *malloc_flag_1_%s);\n",
						CSTLString_c_str(variable_type_name), CSTLString_c_str(data->variable_name),CSTLString_c_str(data->variable_name),
						CSTLString_c_str(data->variable_name), CSTLString_c_str(data->variable_name), CSTLString_c_str(data->variable_name));
			}
			CSTLString_delete(variable_type_name);
	}

	for(i = ARRAY_OFFSET_LIST_begin(right_array_offset_list);
			i != ARRAY_OFFSET_LIST_end(right_array_offset_list);
			i = ARRAY_OFFSET_LIST_next(i)){
			ARRAY_OFFSET *data = ARRAY_OFFSET_LIST_data(i);
			VARIABLE_TABLE *variable = searchVARIABLE_TABLE_LIST(data->variable_address->idlist, data->variable_name, vtlist);
			CSTLString *variable_type_name = getTypeOfVariable(data->variable_name, variable);
			int array_level, pointer_level;
			//配列とポインタのレベルを変数から取得
			getPointerLevelAndArrayLevelFromVARIABLE_TABLE(variable, &pointer_level, &array_level);
			if(OFFSET_LIST_size(data->offset_list) == 0){
				if(array_level + pointer_level > 0){
					fprintf(output, "printf(\"<variable type=#dquot#%s#dquot# name=#dquot#%s#dquot# value=#dquot#%%d#dquot# max_size=#dquot#%%d#dquot# basis_location=#dquot#%%d#dquot# defined=#dquot#%%d#dquot# alloced=#dquot#%%d#dquot#></variable>\", %s, *max_size_1_%s, basis_location_1_%s, *defined_1_%s, *malloc_flag_1_%s);\n",
											CSTLString_c_str(variable_type_name), CSTLString_c_str(data->variable_name), CSTLString_c_str(data->variable_name),
											CSTLString_c_str(data->variable_name), CSTLString_c_str(data->variable_name), CSTLString_c_str(data->variable_name),
											CSTLString_c_str(data->variable_name));
				}else{
					fprintf(output, "printf(\"<variable type=#dquot#%s#dquot# name=#dquot#%s#dquot# value=#dquot#%%d#dquot#></variable>\", %s);\n",
							CSTLString_c_str(variable_type_name), CSTLString_c_str(data->variable_name), CSTLString_c_str(data->variable_name));
				}
			}else{
				fprintf(output, "printf(\"<variable type=#dquot#%s#dquot# name=#dquot#%s#dquot# value=#dquot##dquot# max_size=#dquot#%%d#dquot# basis_location=#dquot#%%d#dquot# defined=#dquot#%%d#dquot# alloced=#dquot#%%d#dquot#></variable>\", *max_size_1_%s, basis_location_1_%s, *defined_1_%s, *malloc_flag_1_%s);\n",
						CSTLString_c_str(variable_type_name), CSTLString_c_str(data->variable_name),CSTLString_c_str(data->variable_name),
						CSTLString_c_str(data->variable_name), CSTLString_c_str(data->variable_name), CSTLString_c_str(data->variable_name));
			}
			CSTLString_delete(variable_type_name);
	}
	fprintf(output, "printf(\"</before_variable_info>\");");
}
/**
 * TODO:○右辺の配列オフセット情報から事後状態をXMLで出力させる
 */
void writeAfterVariableXML(FILE *output, ARRAY_OFFSET_LIST *left_array_offset_list, VARIABLE_TABLE_LIST *vtlist){
	ARRAY_OFFSET_LISTIterator i;
	fprintf(output, "printf(\"<after_variable_info>\");");
	for(i = ARRAY_OFFSET_LIST_begin(left_array_offset_list);
			i != ARRAY_OFFSET_LIST_end(left_array_offset_list);
			i = ARRAY_OFFSET_LIST_next(i)){
			//配列参照のオフセットリストの取得
			ARRAY_OFFSET *data = ARRAY_OFFSET_LIST_data(i);
			VARIABLE_TABLE *variable = searchVARIABLE_TABLE_LIST(data->variable_address->idlist, data->variable_name, vtlist);
			CSTLString *variable_type_name = getTypeOfVariable(data->variable_name, variable);
			int array_level, pointer_level;
			//配列とポインタのレベルを変数から取得
			getPointerLevelAndArrayLevelFromVARIABLE_TABLE(variable, &pointer_level, &array_level);

			//配列参照のオフセットリストが存在しない場合
			if(OFFSET_LIST_size(data->offset_list) == 0){
				if(array_level + pointer_level > 0){
					fprintf(output, "printf(\"<variable type=#dquot#%s#dquot# name=#dquot#%s#dquot# value=#dquot#%%d#dquot# max_size=#dquot#%%d#dquot# basis_location=#dquot#%%d#dquot# defined=#dquot#%%d#dquot# alloced=#dquot#%%d#dquot#></variable>\", %s, *max_size_1_%s, basis_location_1_%s, *defined_1_%s, *malloc_flag_1_%s);\n",
											CSTLString_c_str(variable_type_name), CSTLString_c_str(data->variable_name), CSTLString_c_str(data->variable_name),
											CSTLString_c_str(data->variable_name), CSTLString_c_str(data->variable_name), CSTLString_c_str(data->variable_name),
											CSTLString_c_str(data->variable_name));
				}else{
					fprintf(output, "printf(\"<variable type=#dquot#%s#dquot# name=#dquot#%s#dquot# value=#dquot#%%d#dquot#></variable>\", %s);\n",
							CSTLString_c_str(variable_type_name), CSTLString_c_str(data->variable_name), CSTLString_c_str(data->variable_name));
				}
			}else{
				fprintf(output, "printf(\"<variable type=#dquot#%s#dquot# name=#dquot#%s#dquot# value=#dquot##dquot# max_size=#dquot#%%d#dquot# basis_location=#dquot#%%d#dquot# defined=#dquot#%%d#dquot# alloced=#dquot#%%d#dquot#></variable>\", *max_size_1_%s, basis_location_1_%s, *defined_1_%s, *malloc_flag_1_%s);\n",
						CSTLString_c_str(variable_type_name), CSTLString_c_str(data->variable_name),CSTLString_c_str(data->variable_name),
						CSTLString_c_str(data->variable_name), CSTLString_c_str(data->variable_name), CSTLString_c_str(data->variable_name));
			}
			CSTLString_delete(variable_type_name);
	}
	fprintf(output, "printf(\"</after_variable_info>\");");
}
/**
 指定したファイルに対して、指定したASTに対するXMLを出力させる。
 */
void printXmlData(FILE *output, AST *root, const char *type){
	CSTLString *c = CSTLString_new();
	CSTLString *path = CSTLString_new_assign(getFileName());
	getStringFromAST(c,root);
	xmlSanitize(c);

	CSTLString_replace_string(path,"\\","\\\\\\\\");
	fprintf(output, "printf(\"<source file=#dquot#%s#dquot# loc=#dquot#%d#dquot# type=#dquot#%s#dquot#>\");\n",CSTLString_c_str(path), root->line, type);
	fprintf(output, "printf(\"<prog text=#dquot#%s#dquot#></prog>\");\n", CSTLString_c_str(c));

	CSTLString_delete(c);
	CSTLString_delete(path);
}

void outputErrorXml(CSTLString *statement, ARRAY_OFFSET_LISTIterator aoff_list_i,
		OFFSET_LISTIterator off_list_i, int offset_level_counter, CSTLString *array_string){
	int is_expression_flag = isExpression(*OFFSET_LIST_data(off_list_i));

	//エラーのＸＭＬを出力
	CSTLString_printf(statement,1,"printf(\"<error type = #dquot#Upper Unbound#dquot# variable=#dquot#%s#dquot#>\");\n",(char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name));
	if(is_expression_flag == 1){
		CSTLString_printf(statement,1,"printf(\"<expression text=#dquot#%s#dquot# value=#dquot#%%d#dquot#></expression>\",%s);\n", *OFFSET_LIST_data(off_list_i), *OFFSET_LIST_data(off_list_i));
	}else{
		CSTLString_printf(statement,1,"printf(\"<expression value=#dquot#%%d#dquot#></expression>\",%s);\n",*OFFSET_LIST_data(off_list_i));
	}
	CSTLString_printf(statement,1,"printf(\"<basic_location value=#dquot#%%d#dquot#></basic_location>\", basis_location_%d_%s%s);\n", offset_level_counter, (char*)CSTLString_c_str(ARRAY_OFFSET_LIST_data(aoff_list_i)->variable_name), (char*)CSTLString_c_str(array_string));
	CSTLString_printf(statement,1,"printf(\"</error>\");\n");
	CSTLString_printf(statement,1,"printf(\"</source>\");\n");
}
