/*!
  @brief このファイルは、CSTLライブラリを用いた文字列型CSTLStringを生成したり、それに関する操作を行うための命令が含まれている。

  @file CSTLString.h
  @author faithnh

 */
#ifndef CSTLSTRING_HEADDER
#define CSTLSTRING_HEADDER

#include <cstl/string.h>

/* stringのインターフェイスと実装を展開 */
CSTL_STRING_INTERFACE(CSTLString, char)

/**
指定したCSTL文字列targetに対して、置換対象の文字列searchから置換したい文字列replaceに置換を行う。
@param target 指定したCSTL文字列
@param search 置換対象の文字列
@param replace 置換したい文字列

@return なし
*/
void CSTLString_replace_string(CSTLString *target, char *search, char *replace);

/**
指定したCSTL文字列target1と比較対象の普通の文字列target2と比較する。

@param target1 指定したCSTL文字列
@param target2 比較対象の普通の文字列

@return 比較した結果を返す、一致した場合は０、そうでない場合は０以外の値を返す。
*/
int CSTLString_compare_with_char(CSTLString *target1, char *target2);

/**
指定したCSTL文字列target1から、指定した文字列del_strの最初に出現する箇所以降を全て削除する。

@param target1 指定したCSTL文字列
@param del_str 削除する場所を指定するための文字列

@return 成功したかどうか否かを返す。成功した場合は１、そうでない場合は0を返す。
 */
int CSTLString_delete_tail_str(CSTLString *target1, char *del_str);

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
void CSTLString_printf(CSTLString *target, int add_flag, char *source, ...);

/**
指定した文字列の前の半角スペース・改行文字・タブを削除する。

@param target 指定した文字列
@return なし
 */
void CSTLString_ltrim(CSTLString *target);

#endif
