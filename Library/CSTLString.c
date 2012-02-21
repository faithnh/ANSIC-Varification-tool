#include "CSTLString.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdarg.h>

#define STRLEN 1024

CSTL_STRING_IMPLEMENT(CSTLString, char)

/**
指定したCSTL文字列targetに対して、置換対象の文字列searchから置換したい文字列replaceに置換を行う。
@param target 指定したCSTL文字列
@param search 置換対象の文字列
@param replace 置換したい文字列

@return なし
*/
void CSTLString_replace_string(CSTLString *target, char *search, char *replace){
	int location = CSTLString_find(target,search,0);
	while(location != CSTL_NPOS){
		CSTLString_replace(target, location, strlen(search), replace);
		location = CSTLString_find(target,search,location + strlen(replace));
	}
}
/**
指定したCSTL文字列target1と比較対象の普通の文字列target2と比較する。

@param target1 指定したCSTL文字列
@param target2 比較対象の普通の文字列

@return 比較した結果を返す、一致した場合は０、そうでない場合は０以外の値を返す。
*/
int CSTLString_compare_with_char(CSTLString *target1, char *target2){
	int compare;

	CSTLString *target_CSTLString2 = CSTLString_new();
	CSTLString_assign(target_CSTLString2,target2);

	compare = CSTLString_compare(target1, target_CSTLString2);
	CSTLString_delete(target_CSTLString2);

	return compare;
}

/**
指定したCSTL文字列target1から、指定した文字列del_strの最初に出現する箇所以降を全て削除する。

@param target1 指定したCSTL文字列
@param del_str 削除する場所を指定するための文字列

@return 成功したかどうか否かを返す。成功した場合は１、そうでない場合は0を返す。
 */
int CSTLString_delete_tail_str(CSTLString *target1, char *del_str){
	//先頭から文字列を探索する
	int location = CSTLString_find(target1, del_str, 0);


	//指定した削除する文字列を見つけた場合、それ以降の文字列をすべて削除する
	if(location != CSTL_NPOS){
		CSTLString_erase(target1, location, CSTLString_size(target1) - location);
		//１を返す
		return 1;
	}else{
		//そうでない場合は探索に失敗したとして、０を返す
		return 0;
	}
}

/**
指定した文字列sourceを簡易版の書式フォーマット形式で指定したCSTL文字列targetに入力する。
簡易版なので、%d、%f、%s、%d、%%にしか対応していない。\nは可能。
また、add_flagを指定することで、追加・代入の選択もできる。
@param target 入力先の指定したCSTL文字列（あらかじめ初期化する必要あり）
@param add_flag 追加挿入するかどうかのフラグ　１：追加　０：代入
@param source 指定した文字列（書式フォーマット形式）
@param ... 書式に対応した任意の引数
@return なし
*/
void CSTLString_printf(CSTLString *target, int add_flag, char *source, ...){
	//可変長引数リスト
	va_list args;
	//可変長引数を始める
    va_start(args, source);

	//数字型を文字列に変えるための文字列変数
	char toChar[STRLEN];

	//文字列を走査する位置
	int location;

	//文字列の長さ
	int length = strlen(source);

	//代入先の文字列の初期化
	if(add_flag == 0){
		CSTLString_assign(target, "");
	}
	for(location = 0; location < length ; location++){

		if( source[location] == '%'){
			if(location + 1 < length){
				//%dが来たらそれらを引数である整数に切り替える
				if(source[location + 1] == 'd'){
					int va_list = va_arg(args, int);
					snprintf(toChar, STRLEN, "%d", va_list);
					CSTLString_append(target, toChar);
				}
				//%fが来たらそれらを引数である実数に切り替える
				else if(source[location + 1] == 'f'){
					double va_list = va_arg(args, double);
					snprintf(toChar, STRLEN, "%f", va_list);
					CSTLString_append(target, toChar);
				}
				//%sが来たらそれらを引数である文字列に切り替える
				else if(source[location + 1] == 's'){
					char *va_list = va_arg(args, char*);
					CSTLString_append(target, va_list);
				}
				//%cが来たらそれらを引数である文字に切り替える
				else if(source[location + 1] == 'c'){
					int va_list = va_arg(args, int);
					CSTLString_push_back(target, (char)va_list);
				}
				//%%が来たら%にする。
				else if(source[location + 1] == '%'){
					CSTLString_push_back(target, '%');
				}
				//それ以外が来たら、エラーとして出力する。
				else{
					fprintf(stderr, "文字列エラー。'%%'のあとの入力が不正です！\n");
					exit(1);
				}
				location++;
			}else{
				fprintf(stderr, "文字列エラー。'%%'のあとの入力が不正です！\n");
				exit(1);
			}
		}else{
			CSTLString_push_back(target, source[location]);
		}
	}
}

/**
指定した文字列の前の半角スペース・改行文字・タブを削除する。

@param target 指定した文字列
@return なし
 */
void CSTLString_ltrim(CSTLString *target){
	while(*CSTLString_at(target, 0) == ' ' || *CSTLString_at(target, 0) == '\t' ||
			*CSTLString_at(target, 0) == '\n'){
		target = CSTLString_replace(target, 0, 1, "");
	}

}
