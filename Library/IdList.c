#include "IdList.h"
#include<stdio.h>

CSTL_LIST_IMPLEMENT(IDLIST, int)


/**
二つのIDLIST target1,target2を比較し、次の状態であれば、１を返す。そうでなければ０を返す。
target2の一番最初のリストの値が0である。
target2のリスト内の値が全て、target1のリスト内の値と一致する場合

@param target1 比較対象のIDLIST１
@param target2 比較対象のIDLIST２

@return 比較して上記道理になると１を返し、そうでなければ、０を返す。
*/
int IDLIST_compare_with(IDLIST *target1, IDLIST *target2){
	int success_flag = 1;

	IDLISTIterator ti1,ti2;

	if(*IDLIST_data(IDLIST_begin(target2)) != 0){
		for(ti1 = IDLIST_begin(target1), ti2 = IDLIST_begin(target2);
			ti1 != IDLIST_end(target1) && ti2 != IDLIST_end(target2);
			ti1 = IDLIST_next(ti1), ti2 = IDLIST_next(ti2)){
			//途中で一致しない場合は、０にし、終了する。
			if(*IDLIST_data(ti1) != *IDLIST_data(ti2)){
				success_flag = 0;
				break;
			}
		}

		if(ti1 == IDLIST_end(target1) && ti2 != IDLIST_end(target2)){
			success_flag = 0;
		}
	}

	return success_flag;

}

/**
整数スタックの内容sourceを入れたい対象のIDLISTdestへ入れる。

@param dest 対象のIDLIST
@param source 入れる整数スタック内容
@param num 整数スタックに入れる数

@return なし
*/
void SET_STACK_INTToIDLIST(IDLIST *dest, STACK_INT *source, int num){
	//IDLISTの内容を初期化
	IDLIST_clear(dest);

	//整数スタックの内容がなければ、0のみをIDLISTへ入れる。
	if(num == 0){
		IDLIST_push_back(dest, 0);
	}else{
		int si_loc;
		for(si_loc = 0; si_loc < num; si_loc++){
			//1レベル目である場合は、整数スタックの入っているデータ＋1をIDLISTへ入れる。
			if(si_loc == 0){
				IDLIST_push_back(dest, *STACK_INT_at(source, si_loc) + 1);
			}
			//そうでない場合は、整数スタックの入っているデータをIDLISTへ入れる
			else{
				IDLIST_push_back(dest, *STACK_INT_at(source, si_loc));
			}
		}
	}
}


/**
IDLISTの内容を出力する。

@param idlist 出力対象のIDLIST
@param new_line_flag 改行するかどうかのフラグ　1：改行する　０：改行しない
@return なし
*/
void printIDLIST(IDLIST *idlist,int new_line_flag){
	IDLISTIterator idlist_i;

	for(idlist_i = IDLIST_begin(idlist);
		idlist_i != IDLIST_end(idlist);
		idlist_i = IDLIST_next(idlist_i)){
			//「値1-値2-...-値n」の形で出力する
			printf("%d",*IDLIST_data(idlist_i));
			if(IDLIST_next(idlist_i) != IDLIST_end(idlist)){
				printf("-");
			}
		}

	//改行フラグが立っていたら改行する
	if(new_line_flag == 1){
		printf("\n");
	}
}
