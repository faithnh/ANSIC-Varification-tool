#include "PreProcess.h"
#include "../Library/CSTLString.h"

#include<stdio.h>
#include<stdlib.h>

#define STRLEN 1024
#define MAX_FILE_PATH 1024
#define COMMAND_PATH 4096

//「/*PROGRAM_START*/」の長さ
#define PROGRAM_START_LENGTH 17

CSTL_LIST_IMPLEMENT(INCLUDE_LIST, INCLUDE_DATA)

/**
新しいインクルードファイルを生成する。
@param include_data includeファイルの名前
@param line その行数
*/
INCLUDE_DATA *new_INCLUDE_DATA(CSTLString *include_data, int line){
	//新たにインクルードファイルを生成する
	INCLUDE_DATA *new_include_data = (INCLUDE_DATA*)malloc(sizeof(INCLUDE_DATA));

	//もし、生成に成功した場合
	if(new_include_data != NULL){
		new_include_data->include_data = include_data;
		new_include_data->line = line;
	}
	//生成に失敗した場合は、エラーを出力したうえ終了させる。
	else{
		fprintf(stderr, "Memory is lack!!\n");
		exit(1);
	}

	return new_include_data;
}

/**
実行させたいソースにプリプロセッサをかける。プリプロセッサのかけたファイルはファイル名_out_pre.cとして出力される。
@param source_file_name 実行させたいソースファイル名

@return 成功したかどうかを示す　成功した場合は１をかえし、そうでない場合は０を返す。
*/
int preProcesser(char *source_file_name){
	//成功フラグ
	int success_flag = 1;

	char out_file_name[MAX_FILE_PATH];
	char excec_command[COMMAND_PATH];
	FILE *test_open;
	//includeをコメントアウトする
	includeComment(source_file_name);

	//出力ファイルの設定
	snprintf(out_file_name, MAX_FILE_PATH, "%s_out.c", source_file_name);

	//コマンドの設定
	snprintf(excec_command, COMMAND_PATH, "gcc -E -P -C %s > %s_pre.c", out_file_name, out_file_name);

	//gccのプリプロセッサの実行
	system(excec_command);

	//出力ファイルの再設定(_pre.cを追加)
	snprintf(out_file_name, MAX_FILE_PATH, "%s_pre.c", out_file_name);
	//テストでファイルを開ける
	test_open = fopen(out_file_name, "r");

	//プログラムスタートを調整が失敗に終わった場合、この処理は失敗に終わったことになる
	if(adjustProgramStart(out_file_name) == 0){
		success_flag = 0;
	}
	return success_flag;
}

/**
"#include"にコメントをかけておく。コメントアウトをかけた結果はファイル名_out.cとして出力される。
@param source_file_name 対象のソースファイル名

@return 成功したかどうかを示す　成功した場合は１をかえし、そうでない場合は０を返す。
*/
int includeComment(char *source_file_name){
	//処理に成功したかどうかを示すフラグ
	int success_flag = 1;

	FILE *in, *out;
	char buff[STRLEN];
	char out_file_name[MAX_FILE_PATH];

	CSTLString *file_buff = CSTLString_new();
	//ソースファイルをオープン
	in = fopen(source_file_name, "rt");

	//開くのに失敗した場合
	if(in == NULL){
		//処理は失敗に終わったこととみなす
		success_flag = 0;
	}else{
		//プログラムの開始を示すコメントを入れておく
		CSTLString_assign(file_buff,"/*PROGRAM_START*/");

		//ファイルから一行ずつ取り出し、file_buffへ格納する
		buff[1] = '\0';
		while(fgets(buff,STRLEN,in) != NULL){
			CSTLString_append(file_buff, (char *)buff);
		}
		fclose(in);

		//#includeをコメントアウトする
		CSTLString_replace_string(file_buff, "#include", "//#xinclude");

		sprintf(out_file_name,"%s_out.c", source_file_name);

		out = fopen(out_file_name, "w");

		fprintf(out, "%s", CSTLString_c_str(file_buff));

		fclose(out);
	}
	CSTLString_delete(file_buff);
	return success_flag;
}

/**
プログラムの始まりを示す位置まですべて削除する。
@param source_file_name 対象のソースファイル名

@return 成功したかどうかを示す　成功した場合は１をかえし、そうでない場合は０を返す。
*/
int adjustProgramStart(char *source_file_name){
	//処理に成功したかどうかを示すフラグ
	int success_flag = 1;

	FILE *in, *out;
	char buff[STRLEN];
	int program_start_location;

	CSTLString *file_buff = CSTLString_new();
	//ソースファイルをオープン
	in = fopen(source_file_name, "rt");

	//開くのに失敗した場合
	if(in == NULL){
		//処理は失敗に終わったこととみなす
		success_flag = 0;
	}else{

		//ファイルから一行ずつ取り出し、file_buffへ格納する
		buff[1] = '\0';
		while(fgets(buff,STRLEN,in) != NULL){
			CSTLString_append(file_buff, (char *)buff);
		}
		fclose(in);
		//「/*PROGRAM_START*/」を探し出し、見つければ、そのコメントごとすべて削除する
		program_start_location = CSTLString_find(file_buff,"/*PROGRAM_START*/",0);
		if(program_start_location != CSTL_NPOS){
			CSTLString_replace(file_buff,0,program_start_location + PROGRAM_START_LENGTH,"");
		}

		out = fopen(source_file_name, "w");

		fprintf(out, "%s", CSTLString_c_str(file_buff));

		fclose(out);
	}
	CSTLString_delete(file_buff);
	return success_flag;
}

/**
"#include"にコメントをかけたもののみを取り出し、取りだしたものをインクルードファイルのリストinclude_listにいれる。
@param file_name 開くファイル名
@param include_list インクルードリスト

@return なし
*/
void readIncludeDataFromFile(char *file_name, INCLUDE_LIST *include_list){
	FILE *in;

	char fbuff[STRLEN];

	int line = 1;
		//ファイルを開く
	in = fopen(file_name, "r");

	//ファイルを開くのに成功したら
	if(in != NULL){
			//一行ずつ参照する
			while(fgets(fbuff, STRLEN, in) != NULL){
				CSTLString *line_buff = CSTLString_new();
				CSTLString_assign(line_buff, fbuff);
				if(CSTLString_find(line_buff,"//#xinclude",0) != CSTL_NPOS){
					CSTLString_replace_string(line_buff, "//#xinclude", "#include");
					INCLUDE_LIST_push_back_ref(include_list, new_INCLUDE_DATA(line_buff, line));
				}else{
					CSTLString_delete(line_buff);
				}

				line++;
			}
	}
	//ファイルが開けれらなければエラーを出力し終了する
	else{
		fprintf(stderr, "File %s is not exist or invalid!\n", file_name);
		exit(1);
	}
}

/**
インクルードリストを基に、対象のファイルにインクルードを追加する。
@param file_name 開くファイル名
@param include_list インクルードリスト

@return なし
*/
void addIncludeDataFromFile(char *file_name, INCLUDE_LIST *include_list){
	FILE *in, *tmp;

	char fbuff[STRLEN];

	char tmp_file_name[MAX_FILE_PATH];

	char move_command[STRLEN];

	snprintf(tmp_file_name, MAX_FILE_PATH,"%s,tmp", file_name);

	snprintf(move_command, STRLEN, "mv %s %s", tmp_file_name, file_name);

	INCLUDE_LISTIterator inlist_iterator;

	//tmpファイルを開く
	tmp = fopen(tmp_file_name, "w");
	in = fopen(file_name, "r");

	//ファイルを開くのに成功したら
	if(in != NULL){
			for(inlist_iterator = INCLUDE_LIST_begin(include_list);
				inlist_iterator != INCLUDE_LIST_end(include_list);
				inlist_iterator = INCLUDE_LIST_next(inlist_iterator)){

				fprintf(tmp, "%s", CSTLString_c_str(INCLUDE_LIST_data(inlist_iterator)->include_data));
			}
			//一行ずつ参照する
			while(fgets(fbuff, STRLEN, in) != NULL){
				fprintf(tmp, "%s", fbuff);
			}

			fclose(tmp);
			fclose(in);

			//tmpファイルを元のファイルとして上書きする
			system(move_command);
	}
	//ファイルが開けれらなければエラーを出力し終了する
	else{
		fprintf(stderr, "File %s is not exist or invalid!\n", file_name);
		exit(1);
	}
}
