/*!
  @brief このファイルは、本体に関するフラグ設定を格納するための命令が含まれている。
  たとえば、xmlとして出力するとかなどといった設定が含まれている。

  @file FlagDatabase.h
  @author faithnh

 */

#ifndef FLAGDATABASE_HEADDER
#define FLAGDATABASE_HEADDER



/**
プログラムの引数からフラグデータベースを取得する。
ここで不正にフラグが設定されていた場合（存在しないフラグがある・フラグが二重に定義されている場合）、
エラーを返し、強制終了される。

@param argc 引数フラグの数
@param argv 引数フラグの文字列

@return 引数から取得したフラグを取得する
*/
int getFlagDatabase(int argc, char * argv[]);

/**
フラグデータベースから、XML_MODEが含まれているかどうか確認する。
@param flag_database フラグデータベース

@return XML_MODEが含まれていたら１を返し、そうでなければ０を返す。
*/
int isXmlMode(int flag_database);

/**
フラグデータベースから、HELP_MODEが含まれているかどうか確認する。
@param flag_database フラグデータベース

@return HELP_MODEが含まれていたら１を返し、そうでなければ０を返す。
*/
int isHelpMode(int flag_database);

/**
フラグデータベースから、ARRAY_UNBOUND_CHECK_MODEが含まれているかどうか確認する。
@param flag_database フラグデータベース

@return ARRAY_UNBOUND_CHECK_MODEが含まれていたら１を返し、そうでなければ０を返す。
*/
int isArrayUnboundCheckMode(int flag_database);

/**
フラグデータベースから、UNDEFINE_CONTROL_CHECK_MODEが含まれているかどうか確認する。
@param flag_database フラグデータベース

@return UNDEFINE_CONTROL_CHECK_MODEが含まれていたら１を返し、そうでなければ０を返す。
*/
int isUndefineControlCheckMode(int flag_database);

/**
フラグデータベースから、ZERO_DIVITION_CHECK_MODEが含まれているかどうか確認する。
@param flag_database フラグデータベース

@return ZERO_DIVITION_CHECK_MODEが含まれていたら１を返し、そうでなければ０を返す。
*/
int isZeroDivitionCheckMode(int flag_database);

/**
フラグデータベースから、FREE_VIOLATION_CHECK_MODEが含まれているかどうか確認する。
@param flag_database フラグデータベース

@return FREE_VIOLATION_CHECK_MODEが含まれていたら１を返し、そうでなければ０を返す。
*/
int isFreeViolationCheckMode(int flag_database);

/**
フラグデータベースから、PROGRAM_SLICING_MODEが含まれているかどうか確認する。
@param flag_database フラグデータベース

@return PROGRAM_SLICING_MODEが含まれていたら１を返し、そうでなければ０を返す。
*/
int isProgramSlicingMode(int flag_database);

#endif
