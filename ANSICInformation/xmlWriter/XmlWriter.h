/*
 * XmlWriter.h
 *
 *  Created on: 2012/09/07
 *      Author: faithnh
 */

#ifndef XMLWRITER_H_
#define XMLWRITER_H_

#include<stdio.h>
#include "../PointerArrayControl.h"
#include "../Synbol.h"
void xmlSanitize(CSTLString *str);
void writeFormerVariableXML(FILE *output, ARRAY_OFFSET_LIST *left_array_offset_list, ARRAY_OFFSET_LIST *right_array_offset_list, VARIABLE_TABLE_LIST *vtlist);
void writeAfterVariableXML(FILE *output, ARRAY_OFFSET_LIST *left_array_offset_list, VARIABLE_TABLE_LIST *vtlist);
void printXmlData(FILE *output, AST *root, const char *type);
void outputErrorXml(CSTLString *statement, ARRAY_OFFSET_LISTIterator aoff_list_i,
		OFFSET_LISTIterator off_list_i, int offset_level_counter, CSTLString *array_string);
#endif /* XMLWRITER_H_ */
