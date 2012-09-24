#include"StoreInformation.h"
#include"../Library/CSTLString.h"
#include<stdio.h>
#include<string.h>

#define STORE_INFOMATION_SIZE 4096

///ファイル名を確保するための領域
char fileName[STORE_INFOMATION_SIZE]="";

/**
ファイル名を設定する。4096バイト分までの文字が確保でき、それ以上は切り捨てられる。

@param str ファイル名

@return なし
*/
void setFileName(char *str){
	//エラー対策のため、エスケープマーク\が存在する場合は、\\に置き換える。
	CSTLString *tmp = CSTLString_new_assign(str);
	CSTLString_replace_string(tmp, "\\", "\\\\");

	//4096バイト分までの文字を確保する
	strncpy(fileName, CSTLString_c_str(tmp), STORE_INFOMATION_SIZE);

	CSTLString_delete(tmp);
}

/**
設定したファイル名を呼び出す。

@return 呼び出されたファイル名を返す
*/
char *getFileName(){
	return fileName;
}
