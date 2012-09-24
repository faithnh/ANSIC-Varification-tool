/*!
  @brief これはファイル名などといったプログラム内で共通する部分を確保するための命令が含まれている。
  主にファイル名などを確保する。

  @file StoreInformation.h
  @author faithnh
 */

#ifndef STORE_INFORMATION_HEADDER
#define STORE_INFORMATION_HEADDER

/**
ファイル名を設定する。4096バイト分までの文字が確保でき、それ以上は切り捨てられる。

@param str ファイル名

@return なし
*/
void setFileName(char *str);
/**
設定したファイル名を呼び出す。

@return 呼び出されたファイル名を返す
*/
char *getFileName();
#endif
