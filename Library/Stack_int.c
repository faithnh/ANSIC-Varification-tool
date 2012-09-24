#include "Stack_int.h"

CSTL_VECTOR_IMPLEMENT(STACK_INT, int)

/**
対象の整数スタックstack_intから、指定したインデックスの内容を出力する。インデックスが範囲外である場合は、そのサイズ分まで確保し、0を返す。

@param stack_int 対象の整数スタック
@param index 対象の座標

@return 指定したインデックスでの整数スタックの値を出力する。インデックスが範囲外である場合は0を返す。
*/
int STACK_INT_at_and_alloc(STACK_INT *stack_int, int index){
	int ret_val;
	//もし、指定したインデックスは整数スタックの範囲内である場合
	if(STACK_INT_size(stack_int) > index){
		ret_val = *STACK_INT_at(stack_int, index);
	}
	//範囲外である場合は、そのサイズ分まで確保し、0を返す
	else{
		while(STACK_INT_size(stack_int) <= index){
			STACK_INT_push_back(stack_int, 0);
		}
		ret_val = 0;
	}

	return ret_val;
}

/**
対象の整数スタックstack_intから、指定したインデックスの内容をインクリメントする。
@param stack_int 対象の整数スタック
@param index 指定したインデックス
@return インクリメントに成功したかどうかを示す。成功した場合は１、そうでない場合は０を返す。
*/
int STACK_INT_inclement_at(STACK_INT *stack_int, int index){
		int ret_val;
	//もし、指定したインデックスは整数スタックの範囲内である場合
	if(STACK_INT_size(stack_int) > index){
		//指定したインデックスの内容をインクリメントする
		*STACK_INT_at(stack_int, index) = *STACK_INT_at(stack_int, index) + 1;
		ret_val = 1;
	}
	//範囲外である場合は、0を返す。
	else{

		ret_val = 0;
	}

	return ret_val;
}
