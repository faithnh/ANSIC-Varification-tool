/*!
  @brief このファイルは、string.hにないような処理を実現させるための命令が含まれている。
  具体的には文字列からある場所からある場所までを抽出させるといったことができる。

  @file CharStringExtend.h
  @author faithnh

 */

#ifndef CHAR_STRING_EXTEND_HEADDER
#define CHAR_STRING_EXTEND_HEADDER

/**
文字列sourceから開始文字数startから指定された文字数strlen分の文字列を抽出し、その結果を文字列destへ入れる。
また終端子も付くので、抜き出した文字＋１個分の文字列が必要

@param dest 抽出結果を入れる文字列
@param source 抽出対象の文字列
@param start 抽出の開始位置
@param str_length 抽出する文字数

@return 成功したかどうかのフラグ 成功した場合は１　途中で抽出に失敗した場合は０を返す。
*/
int str_extract(char *dest, char *source, int start, int str_length);

/**
文字列sourceは式であるかどうかを調べる。

@param source 対象の文字列

@return 式である場合は１、そうでない場合は０を返す。

*/
int isExpression(char *source);

#endif
