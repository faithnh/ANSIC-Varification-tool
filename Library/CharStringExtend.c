#include <stdio.h>
#include <string.h>

#include "CharStringExtend.h"

/**
文字列sourceから開始文字数startから指定された文字数strlen分の文字列を抽出し、その結果を文字列destへ入れる。
また終端子も付くので、抜き出した文字＋１個分の文字列が必要

@param dest 抽出結果を入れる文字列
@param source 抽出対象の文字列
@param start 抽出の開始位置
@param str_length 抽出する文字数

@return 成功したかどうかのフラグ 成功した場合は１　途中で抽出に失敗した場合は０を返す。
*/
int str_extract(char *dest, char *source, int start, int str_length){
	//成功フラグ
	int success_flag = 1;

	//sourceの文字数
	int source_length;

	int source_iterator;
	int dest_iterator;

	source_length = strlen(source);

	//文字列sourceから開始文字数startから指定された文字数strlen分の文字列を抽出し、その結果を文字列destへ入れる
	for(source_iterator = start, dest_iterator = 0;
		source_iterator < source_length && source_iterator < start + str_length;
		source_iterator++ , dest_iterator++){

			*(dest + dest_iterator) = *(source + source_iterator);

		}

	//もし、source_iteratorがsource_length以上またはdest_iteratrorがdest_length以上で、なおかつsource_iteratorがstart+strlen未満の場合
	if(source_iterator >= source_length && source_iterator < start + str_length){
		success_flag = 0;
	}
	*(dest + dest_iterator) = '\0';

	return success_flag;
}

/**
文字列sourceは式または識別子であるかどうかを調べる。

@param source 対象の文字列

@return 式または識別子である場合は１、そうでない場合は０を返す。
*/
int isExpression(char *source){
	int source_length = strlen(source);

	int source_iterator;

	int is_expression_flag = 0;
	//文字列sourceを調べる
	for(source_iterator = 0; source_iterator < source_length; source_iterator++){
		//もし、数字や空白、終端、改行以外の文字が来た場合は、式または識別子とみなす
		if(('0' > source[source_iterator] || '9' < source[source_iterator]) &&
		 source[source_iterator] != ' ' && source[source_iterator] != '\0' &&
		  source[source_iterator] != '\n'){
			is_expression_flag = 1;
			break;
		}
	}

	return is_expression_flag;
}
