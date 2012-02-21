#include"Return_Info.h"

#include<stdio.h>
#include<stdlib.h>

/**
リターン命令に関する情報を生成させる。
@param target_expression リターン命令自体へのノードへのアドレス
@param return_array_offset_list リターン命令で表記された式の配列オフセットリスト

@return 生成されたリターン命令に関する情報へのアドレスを返す。
*/
RETURN_INFO *new_RETURN_INFO(AST *target_expression, ARRAY_OFFSET_LIST *return_array_offset_list){
	RETURN_INFO *new_return_info = (RETURN_INFO*)malloc(sizeof(RETURN_INFO));

	if(new_return_info == NULL){
		fprintf(stderr, "メモリ不足\n");
		exit(1);
	}else{
		new_return_info->target_expression = target_expression;
		new_return_info->return_array_offset_list = return_array_offset_list;
	}

	return new_return_info;

}
