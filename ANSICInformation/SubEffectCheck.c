#include"SubEffectCheck.h"
#include<stdlib.h>
#include<stdio.h>
#include"../Library/CSTLString.h"
#include"../ANSICInformation/ANSIC_CODE.h"

//副作用式が含まれていない場合
#define NOT_CONTAIN 0
//上から、インクリメント式、デクリメント式、代入式が含まれていた場合
#define CONTAIN_INC 1
#define CONTAIN_DEC 2
#define CONTAIN_ASI 3

//代入演算子が何かというフラグ0:=,1:+=,2:-=,3:*=,4:/=,5:%=,6:<<=,7:>>=,8:&=,9:|=,10:^=
#define EQUAL 0
#define PLUS_EQUAL 1
#define MINUS_EQUAL 2
#define MUL_EQUAL 3
#define DIV_EQUAL 4
#define MOD_EQUAL 5
#define LEFT_EQUAL 6
#define RIGHT_EQUAL 7
#define AND_EQUAL 8
#define OR_EQUAL 9
#define XOR_EQUAL 10

/**
指定されたASTノードnodeから、副作用式(インクリメント式・デクリメント式・代入式)が含まれているかどうかチェックする。

@param node 対象のASTノード

@return 含まれていた式がインクリメント式の場合１、デクリメント式の場合２、代入式の場合３とする。含まれていない場合は０を返す。
 */

int checkContainSubEffectStatement(AST *node){
	int contain_flag = NOT_CONTAIN;
	ASTListIterator ast_p;
	//インクリメント式が見つかった場合、インクリメント式が含まれているというフラグの値で返す
	if(CSTLString_compare_with_char(node->name, "inc_expr") == 0 ||
			CSTLString_compare_with_char(node->name, "inc_after_expr") == 0){
		return CONTAIN_INC;
	}
	//デクリメント式が見つかった場合、デクリメント式が含まれているというフラグの値で返す
	else if(CSTLString_compare_with_char(node->name, "dec_expr") == 0 ||
			CSTLString_compare_with_char(node->name, "dec_after_expr") == 0){
		return CONTAIN_DEC;
	}
	//代入式が見つかった場合、代入式が含まれているというフラグの値で返す
	else if(CSTLString_compare_with_char(node->name, "assignment_expression") == 0){
		return CONTAIN_ASI;
	}
	//そうでなければ、子ノードも探索する
	else{
		for(ast_p = ASTList_begin(node->children);
				contain_flag == NOT_CONTAIN && ast_p != ASTList_end(node->children);
				ast_p = ASTList_next(ast_p)){

			contain_flag = checkContainSubEffectStatement(ASTList_data(ast_p));
		}
	}

	return contain_flag;
}

/**
代入式のタイプを出力させる。

@param assignment_expression_list 代入式に関するASTノードのリスト

@return 代入式のタイプに応じた値を返却する。 0:=,1:+=,2:-=,3:*=,4:/=,5:%=,6:<<=,7:>>=,8:&=,9:|=,10:^=
 */
int getAssignment_TYPE(AST *assignment_expression_list){
	int a_op_flag;
	if(CSTLString_compare_with_char(assignment_expression_list->name, "assignment_expression") == 0){
		//代入式のタイプを求める

		CSTLString *a_op_string = CSTLString_new();
		//代入演算子を取得する
		getStringFromAST(a_op_string, ASTLIST_ITERATOR_2(assignment_expression_list));

		//もし=の場合
		if(CSTLString_compare_with_char(a_op_string, "=") == 0){
			a_op_flag = EQUAL;
		}
		//もし+=の場合
		else if(CSTLString_compare_with_char(a_op_string, "+=") == 0){
			a_op_flag = PLUS_EQUAL;
		}
		//もし-=の場合
		else if(CSTLString_compare_with_char(a_op_string, "-=") == 0){
			a_op_flag = MINUS_EQUAL;
		}
		//もし*=の場合
		else if(CSTLString_compare_with_char(a_op_string, "*=") == 0){
			a_op_flag = MUL_EQUAL;
		}
		//もし/=の場合
		else if(CSTLString_compare_with_char(a_op_string, "/=") == 0){
			a_op_flag = DIV_EQUAL;
		}
		//もし%=の場合
		else if(CSTLString_compare_with_char(a_op_string, "%=") == 0){
			a_op_flag = MOD_EQUAL;
		}
		//もし<<=の場合
		else if(CSTLString_compare_with_char(a_op_string, "<<=") == 0){
			a_op_flag = LEFT_EQUAL;
		}
		//もし>>=の場合
		else if(CSTLString_compare_with_char(a_op_string, ">>=") == 0){
			a_op_flag = RIGHT_EQUAL;
		}
		//もし&=の場合
		else if(CSTLString_compare_with_char(a_op_string, "&=") == 0){
			a_op_flag = AND_EQUAL;
		}
		//もし|=の場合
		else if(CSTLString_compare_with_char(a_op_string, "|=") == 0){
			a_op_flag = OR_EQUAL;
		}
		//もし^=の場合
		else if(CSTLString_compare_with_char(a_op_string, "^=") == 0){
			a_op_flag = XOR_EQUAL;
		}else {
			fprintf(stderr,"#%s#:%d:Invalid Assignment Operator!!",
					getFileName(), ASTList_data(ASTList_next(ASTList_begin(assignment_expression_list->children)))->line);
			exit(1);
		}
		CSTLString_delete(a_op_string);
	}else{
		fprintf(stderr,"不正なノード%sを見つけました",CSTLString_c_str(assignment_expression_list->name));
		exit(1);
	}

	return a_op_flag;
}
