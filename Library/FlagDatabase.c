#include "FlagDatabase.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//XMLモードのフラグの数値と文字列と取得式
#define XML_OUTPUT_MODE 1
#define XML_OUTPUT_MODE_STRING "--xml"
#define GET_XML_OUTPUT_MODE flag_database % 2
//ヘルプモードのフラグの数値と文字列と取得式
#define HELP_MODE 2
#define HELP_MODE_STRING "--h"
#define GET_HELP_MODE (flag_database >> 1) % 2
//配列範囲外参照チェックモードのフラグの数値と文字列と取得式
#define ARRAY_UNBOUND_CHECK_MODE 4
#define ARRAY_UNBOUND_CHECK_MODE_STRING "--array-unbound-check"
#define GET_ARRAY_UNBOUND_CHECK_MODE (flag_database >> 2) % 2
//未定義操作チェックモード(未定義ポインタの参照など)のフラグの数値と文字列と取得式
#define UNDEFINE_CONTROL_CHECK_MODE 8
#define UNDEFINE_CONTROL_CHECK_MODE_STRING "--undefined-control-check"
#define GET_UNDEFINE_CONTROL_CHECK_MODE (flag_database >> 3) % 2
//ゼロ除算チェックモードのフラグの数値と文字列と取得式
#define ZERO_DIVITION_CHECK_MODE 16
#define ZERO_DIVITION_CHECK_MODE_STRING "--zero-division-check"
#define GET_ZERO_DIVITION_CHECK_MODE (flag_database >> 4) % 2
//ゼロ除算チェックモードのフラグの数値と文字列と取得式
#define ZERO_DIVITION_CHECK_MODE 16
#define ZERO_DIVITION_CHECK_MODE_STRING "--zero-division-check"
#define GET_ZERO_DIVITION_CHECK_MODE (flag_database >> 4) % 2
//メモリ解放関係の不正チェックモードのフラグの数値と文字列と取得式
#define FREE_VIOLATION_CHECK_MODE 32
#define FREE_VIOLATION_CHECK_MODE_STRING "--free-violation-check"
#define GET_FREE_VIOLATION_CHECK_MODE (flag_database >> 5) % 2
//プログラムスライシングモードのフラグの数値と文字列と取得式
#define PROGRAM_SLICING_MODE 64
#define PROGRAM_SLICING_MODE_STRING "--program-slicing-mode"
#define GET_PROGRAM_SLICING_MODE (flag_database >> 6) % 2
//簡易版モードのフラグの数値と文字列と取得式
#define SIMPLE_MODE 64
#define SIMPLE_MODE_STRING "--simple-mode"
#define GET_SIMPLE_MODE (flag_database >> 7) % 2

/**
プログラムの引数からフラグデータベースを取得する。
ここで不正にフラグが設定されていた場合（存在しないフラグがある・フラグが二重に定義されている場合）、
エラーを返し、強制終了される。

@param argc 引数フラグの数
@param argv 引数フラグの文字列

@return 引数から取得したフラグを取得する。
*/
int getFlagDatabase(int argc, char * argv[]){

	int i;
	int flag_database = 0;

	for(i = 1; i < argc; i++){
		//フラグである場合
		if(strlen(argv[i]) >= 2 && argv[i][0] == '-' && argv[i][1] == '-'){
			//ＸＭＬモードを示すフラグである場合
			if(strcmp(argv[i], XML_OUTPUT_MODE_STRING) == 0){
				//ＸＭＬモードが二重に定義されていないかどうか調べる。二重に定義されていたらエラーを返し、強制終了される。
				if(!isXmlMode(flag_database)){
					flag_database += XML_OUTPUT_MODE;
				}else{
					fprintf(stderr,"フラグが二重です！\n");
					exit(1);
				}
			}
			//ヘルプモード
			else if(strcmp(argv[i], HELP_MODE_STRING) == 0){
				//ヘルプモードが二重に定義されていないかどうか調べる。二重に定義されていたらエラーを返し、強制終了される。
				if(!isHelpMode(flag_database)){
					flag_database += HELP_MODE;
				}else{
					fprintf(stderr,"フラグが二重です！\n");
					exit(1);
				}
			}
			//配列範囲外参照チェックモード
			else if(strcmp(argv[i], ARRAY_UNBOUND_CHECK_MODE_STRING) == 0){
				//配列範囲外参照チェックモードが二重に定義されていないかどうか調べる。二重に定義されていたらエラーを返し、強制終了される。
				if(!isArrayUnboundCheckMode(flag_database)){
					flag_database += ARRAY_UNBOUND_CHECK_MODE;
				}else{
					fprintf(stderr,"フラグが二重です！\n");
					exit(1);
				}
			}
			//未定義操作チェックモード
			else if(strcmp(argv[i], UNDEFINE_CONTROL_CHECK_MODE_STRING) == 0){
				//未定義操作チェックモードが二重に定義されていないかどうか調べる。二重に定義されていたらエラーを返し、強制終了される。
				if(!isUndefineControlCheckMode(flag_database)){
					flag_database += UNDEFINE_CONTROL_CHECK_MODE;
				}else{
					fprintf(stderr,"フラグが二重です！\n");
					exit(1);
				}
			}
			//ゼロ除算チェックモード
			else if(strcmp(argv[i], ZERO_DIVITION_CHECK_MODE_STRING) == 0){
				//ゼロ除算チェックモードが二重に定義されていないかどうか調べる。二重に定義されていたらエラーを返し、強制終了される。
				if(!isZeroDivitionCheckMode(flag_database)){
					flag_database += ZERO_DIVITION_CHECK_MODE;
				}else{
					fprintf(stderr,"フラグが二重です！\n");
					exit(1);
				}
			}
			//メモリ解放の不正チェックモード
			else if(strcmp(argv[i], FREE_VIOLATION_CHECK_MODE_STRING) == 0){
				//ゼロ除算チェックモードが二重に定義されていないかどうか調べる。二重に定義されていたらエラーを返し、強制終了される。
				if(!isFreeViolationCheckMode(flag_database)){
					flag_database += FREE_VIOLATION_CHECK_MODE;
				}else{
					fprintf(stderr,"フラグが二重です！\n");
					exit(1);
				}
			}
			//プログラムスライシングモード
			else if(strcmp(argv[i], PROGRAM_SLICING_MODE_STRING) == 0){
				//ゼロ除算チェックモードが二重に定義されていないかどうか調べる。二重に定義されていたらエラーを返し、強制終了される。
				if(!isProgramSlicingMode(flag_database)){
					flag_database += PROGRAM_SLICING_MODE;
				}else{
					fprintf(stderr,"フラグが二重です！\n");
					exit(1);
				}
			}
			//シンプルモード
			else if(strcmp(argv[i], SIMPLE_MODE_STRING) == 0){
				//シンプルモードが二重に定義されていないかどうか調べる。二重に定義されていたらエラーを返し、強制終了される。
				if(!isSimpleMode(flag_database)){
					flag_database += SIMPLE_MODE;
				}else{
					fprintf(stderr,"フラグが二重です！\n");
					exit(1);
				}
			}
			//いずれも該当しなかった場合は、未定義のフラグとしてエラーを返し、強制終了される。
			else{
				fprintf(stderr, "未定義のフラグ %s\n", argv[i]);
				exit(1);
			}
		}
	}

	return flag_database;
}

/**
フラグデータベースから、XML_MODEが含まれているかどうか確認する。
@param flag_database フラグデータベース

@return XML_MODEが含まれていたら１を返し、そうでなければ０を返す。
*/
int isXmlMode(int flag_database){
	return GET_XML_OUTPUT_MODE;
}

/**
フラグデータベースから、HELP_MODEが含まれているかどうか確認する。
@param flag_database フラグデータベース

@return HELP_MODEが含まれていたら１を返し、そうでなければ０を返す。
*/
int isHelpMode(int flag_database){
	return GET_HELP_MODE;
}

/**
フラグデータベースから、ARRAY_UNBOUND_CHECK_MODEが含まれているかどうか確認する。
@param flag_database フラグデータベース

@return ARRAY_UNBOUND_CHECK_MODEが含まれていたら１を返し、そうでなければ０を返す。
*/
int isArrayUnboundCheckMode(int flag_database){
	return GET_ARRAY_UNBOUND_CHECK_MODE;
}

/**
フラグデータベースから、UNDEFINE_CONTROL_CHECK_MODEが含まれているかどうか確認する。
@param flag_database フラグデータベース

@return UNDEFINE_CONTROL_CHECK_MODEが含まれていたら１を返し、そうでなければ０を返す。
*/
int isUndefineControlCheckMode(int flag_database){
	return GET_UNDEFINE_CONTROL_CHECK_MODE;
}

/**
フラグデータベースから、ZERO_DIVITION_CHECK_MODEが含まれているかどうか確認する。
@param flag_database フラグデータベース

@return ZERO_DIVITION_CHECK_MODEが含まれていたら１を返し、そうでなければ０を返す。
*/
int isZeroDivitionCheckMode(int flag_database){
	return GET_ZERO_DIVITION_CHECK_MODE;
}

/**
フラグデータベースから、FREE_VIOLATION_CHECK_MODEが含まれているかどうか確認する。
@param flag_database フラグデータベース

@return FREE_VIOLATION_CHECK_MODEが含まれていたら１を返し、そうでなければ０を返す。
*/
int isFreeViolationCheckMode(int flag_database){
	return GET_FREE_VIOLATION_CHECK_MODE;
}

/**
フラグデータベースから、PROGRAM_SLICING_MODEが含まれているかどうか確認する。
@param flag_database フラグデータベース

@return PROGRAM_SLICING_MODEが含まれていたら１を返し、そうでなければ０を返す。
*/
int isProgramSlicingMode(int flag_database){
	return GET_PROGRAM_SLICING_MODE;
}

/**
フラグデータベースから、SIMPLE_MODEが含まれているかどうか確認する。
@param flag_database フラグデータベース

@return SIMPLE_MODEが含まれていたら１を返し、そうでなければ０を返す。
*/
int isSimpleMode(int flag_database){
	return GET_SIMPLE_MODE;
}
