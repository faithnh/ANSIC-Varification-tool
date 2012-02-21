#ifndef AST_HEADDER
#include "AST.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "../Library/Stack_int.h"
#include "ANSIC_CODE.h"

CSTL_LIST_IMPLEMENT(ASTList, struct abstract_syntax_tree)

/**
新しいASTノードを生成する。
@param new_name 新しいノード名
@param new_content 新しい内容
@param new_line 新しい行数
@return 新しく生成されたASTノードへのアドレスが返される。
*/
AST* new_AST(char *new_name, char *new_content,int new_line){
	//新しいASTノードを動的確保で取得する
	AST* new_ASTNode = (AST*)malloc(sizeof(AST));
	//新しいASTノードに名前・内容・行数を指定し、子ノードの情報を初期化させる
	new_ASTNode->name = CSTLString_new();
	CSTLString_assign(new_ASTNode->name, new_name);
	new_ASTNode->content = CSTLString_new();
	CSTLString_assign(new_ASTNode->content, new_content);
	new_ASTNode->line = new_line;
	new_ASTNode->children = ASTList_new();

	//返却値のタイプは初期化する（これはsetASTReturnTypeによってあとで追加される）
	new_ASTNode->return_type = CSTLString_new();

	//ブロックレベルやIDの初期化をおこなう（これはsetASTBlocklevelAndIdによってあとで追加される）
	new_ASTNode->block_level = 0;
	new_ASTNode->block_id = 0;
	new_ASTNode->idlist = IDLIST_new();

	//ASTのデバッグモードAST_DEBUG_MODEを定義した場合、新しいASTノードの名前・内容・行数を表示させる
#ifdef AST_DEBUG_MODE
	printf("new node = \"%s\" content = \"%s\" line = \"%d\"\n",CSTLString_c_str(new_ASTNode->name),CSTLString_c_str(new_ASTNode->content),new_ASTNode->line);
	fflush(stdout);
#endif

	//新しいASTノードを返す
	return new_ASTNode;

}

/**
名前と内容が同じであるASTノードを生成する。
@param new_name 新しいノード名
@param new_line 新しい行数
@return 新しく生成されたASTノードへのアドレスが返される。
*/
AST* same_new_AST(char *new_name, int new_line){
	//名前と内容が同じASTノードを生成させる
	return new_AST(new_name, new_name, new_line);
}

/**
ASTのノードをたどり、rootノード以下のノードの名前・内容・行数を表示させる。
また、下位レベルのノードはタブを挿入し表示する。例えば、1レベル下位のノードはタブが1つ挿入した上で表示される。
@param root 新しいノード名
@param tab_level タブレベル(この数分タブが挿入される）
@return なし
*/
void traverseAST(AST *root, int tab_level){
	int i;
	ASTListIterator p;

	//tab_level分タブを出力させる
	for(i = 0; i < tab_level; i++){
		printf("\t");
	}
	//リーフノード（子ASTノードの数が0のASTノード）の場合、*を追加で出力させる。こうすることでリーフノードを強調させる
	if(ASTList_size(root->children) == 0){
		printf("*");
	}
	//ASTノードの名前・内容・行数を出力させる
	printf("node name = \"%s\" content = \"%s\" line = \"%d\" return_type = \"%s\" block_level = \"%d\" block_level = \"%d\"",
		CSTLString_c_str(root->name), CSTLString_c_str(root->content) ,root->line, CSTLString_c_str(root->return_type), root->block_level, root->block_id);
	//block_idの内容を出力する。
	printf("idlist = \"");
	printIDLIST(root->idlist, 0);
	printf("\"\n");

	//ASTノードが子ASTノードの情報を持っていたら、子ASTノードについて再帰的に参照させる
	for(p = ASTList_begin(root->children); p != ASTList_end(root->children); p = ASTList_next(p)){
		traverseAST(ASTList_data(p), tab_level + 1);
	}
}

/**
ASTのノードをたどり、rootノード以下のノードの名前・内容・行数をXML形式で出力する。（デバッグ用）
また、下位レベルのノードはタブを挿入し出力する。例えば、1レベル下位のノードはタブが1つ挿入した上でタグが出力される。
XMLについては次の形式で出力する(aはルートノード、a_subはリーフノードであるとする）
<a content = "" line = "1">
	<leaf name="a_sub" content = "+" line = "1"/>
</a>

@param root 新しいノード名
@param tab_level タブレベル(この数分タブが挿入される）
@return なし
*/
void traverseASTwithXML(AST* root,int tab_level){
	int i;
	ASTListIterator p;
	//リーフノードか判定するフラグ
	int reaf_flag = 0;

	//リーフノード（子ASTノードの数が0のASTノード）の場合、*を追加で出力させる。こうすることでリーフノードを強調させる
	if(ASTList_size(root->children) == 0){
		reaf_flag = 1;
	}


	//tab_level分タブを出力させる
	for(i = 0; i < tab_level; i++){
		printf("\t");
	}
	//リーフノードである場合
	if(reaf_flag == 1){

		//タグ名が名前である空要素タグで、内容・行数を出力させる
		printf("<leaf name = \"%s\" content = \"%s\" line = \"%d\"/>\n", CSTLString_c_str(root->name), CSTLString_c_str(root->content) ,root->line);

	}else{

		//タグ名が名前である開始タグで、内容・行数を出力させる
		printf("<%s content = \"%s\" line = \"%d\">\n", CSTLString_c_str(root->name), CSTLString_c_str(root->content) ,root->line);
		//子ASTノードについても同じ形式で出力をさせる
		for(p = ASTList_begin(root->children); p != ASTList_end(root->children); p = ASTList_next(p)){
			traverseASTwithXML(ASTList_data(p), tab_level + 1);
		}

		//tab_level分タブを出力させる
		for(i = 0; i < tab_level; i++){
			printf("\t");
		}
		//タグ名が名前である終了タグを出力させる
		printf("</%s>\n", CSTLString_c_str(root->name));
	}

}

/**
指定されたASTノード以下の内容を、指定されたファイルに対して出力させる
@param output 出力先のファイル構造体
@param root 指定されたノード名
@param line 出力に利用する行数

@return なし
 */
void fprintDataFromAST(FILE *output, AST *root, int *line){
	ASTListIterator p;

	//リーフノード（子ASTノードの数が0のASTノード）の場合
	if(ASTList_size(root->children) == 0){
		//ASTノードの行数と引数の行数がかみ合わないとき、改行を出力させ、出力する行数を調整する
		while(*line < root->line){
			fprintf(output, "\n");
			*line = *line + 1;
		}
		//ASTノードの内容を出力させる
		fprintf(output, "%s ",CSTLString_c_str(root->content));
	}

	//ASTノードが子ASTノードの情報を持っていたら、子ASTノードについて再帰的に参照させる
	for(p = ASTList_begin(root->children); p != ASTList_end(root->children); p = ASTList_next(p)){
		fprintDataFromAST(output, ASTList_data(p), line);
	}
}

/**
指定したASTノード以下の内容を出力させる。ASTノードの行数にしたがって出力される。
@param root 新しいノード名
@param line 指定する行数(基本的に１を入力する）
@return なし
*/
void printDataFromAST(AST* root, int *line){

	fprintDataFromAST(stdout, root, line);
}

/**
getStringFromASTの内部処理
@param output 出力対象の文字列データ
@param root 新しいノード名
@return なし
*/
void getStringFromAST_Internal(CSTLString* output, AST* root){
	ASTListIterator p;
	//リーフノード（子ASTノードの数が0のASTノード）の場合、その内容をoutputに追加させる
	if(ASTList_size(root->children) == 0){
		CSTLString_append(output, CSTLString_c_str(root->content));
		CSTLString_append(output, " ");
	}

	//ASTノードが子ASTノードの情報を持っていたら、子ASTノードについて再帰的に参照させる
	for(p = ASTList_begin(root->children); p != ASTList_end(root->children); p = ASTList_next(p)){
		getStringFromAST_Internal(output, ASTList_data(p));
	}
}

/**
指定したASTノード以下の内容を出力対象の文字列データに出力させる。
@param output 出力対象の文字列データ
@param root 新しいノード名
@return なし
*/
void getStringFromAST(CSTLString* output, AST* root){
	getStringFromAST_Internal(output, root);

	//文字列の末尾が半角スペースのとき、それを削除する
	if(CSTLString_size(output) > 0 && *CSTLString_at(output, CSTLString_size(output) - 1) == ' '){
		CSTLString_pop_back(output);
	}
	//前についてある空白文字などを削除する
	CSTLString_ltrim(output);
}

/**
getStringFromASTEnableExceptの内部処理
@param output 出力対象の文字列データ
@param root 新しいノード名
@param num 除外したいASTノードリストの数
@param except_list 除外したいASTノード
@return なし
*/
void getStringFromASTEnableExcept_Internal(CSTLString* output, AST* root, int num, char except_list[][256]){
	ASTListIterator p;
	int i;
	va_list EXCEPT_LIST;
	int except_flag;

	//リーフノード（子ASTノードの数が0のASTノード）の場合、その内容をoutputに追加させる
	if(ASTList_size(root->children) == 0){
		CSTLString_append(output, CSTLString_c_str(root->content));
		CSTLString_append(output, " ");
	}

	//ASTノードが子ASTノードの情報を持っていたら、子ASTノードについて再帰的に参照させる
	for(p = ASTList_begin(root->children); p != ASTList_end(root->children); p = ASTList_next(p)){


		except_flag = 0;
		//除外リストを全て参照する
		for(i = 0; i < num; i++){
			//除外リストとマッチした場合、除外フラグが立つ
			if(CSTLString_compare_with_char(ASTList_data(p)->name,except_list[i]) == 0){
			 except_flag = 1;
			 break;
			}
		}

		//除外フラグが立っていなければ、その子ASTノードは探索対象に入る
		if(except_flag == 0){
			getStringFromASTEnableExcept_Internal(output, ASTList_data(p), num, except_list);
		}
	}
}

/**
getStringFromASTの拡張版。出力対象から除外したASTノード名を指定できる。
@param output 出力対象の文字列データ
@param root 新しいノード名
@param num 除外したいASTノードリストの数
@param except_list 除外したいASTノード
@return なし
*/
void getStringFromASTEnableExcept(CSTLString* output, AST* root,int num, char except_list[][256]){
	getStringFromASTEnableExcept_Internal(output, root, num, except_list);

	//文字列の末尾が半角スペースのとき、それを削除する
	if(CSTLString_size(output) > 0 && *CSTLString_at(output, CSTLString_size(output) - 1) == ' '){
		CSTLString_pop_back(output);
	}
	//前についてある空白文字などを削除する
	CSTLString_ltrim(output);
}

/**
指定したASTノード以下を全て開放させる
@param output 出力対象の文字列データ
@return なし
*/
void deleteAST_sub(AST* sub_root){
	int i;
	ASTListIterator p;
	//ASTノードが子ASTノードの情報を持っていたら、子ASTノードについて再帰的に参照させる
	for(p = ASTList_begin(sub_root->children); p != ASTList_end(sub_root->children); p = ASTList_next(p)){
		deleteAST_sub(ASTList_data(p));
	}

	//子ASTノードの参照が終われば、そのリスト自体を削除させる
	ASTList_delete(sub_root->children);

}

/**
指定したASTノード以下を全て開放させる。
@param root 指定したASTノード
@return なし
*/
void deleteAST(AST* root){
	int i;
	//ASTノードが子ASTノードの情報を持っていたら、子ASTノードについて再帰的に参照させる
	ASTListIterator p;
	for(p = ASTList_begin(root->children); p != ASTList_end(root->children); p = ASTList_next(p)){
		deleteAST_sub(ASTList_data(p));
	}
	//子ASTノードの参照が終われば、そのリスト自体を削除させる
	ASTList_delete(root->children);
	//rootノード自体を開放する
	free(root);

}

/**
指定された親ASTノードに指定された子ASTノードを追加する。
@param parent 指定された親ASTノード
@param child 指定された子ASTノード
@return なし
*/
void push_back_childrenAST(AST *parent, AST *child){

	//親ASTノードに子ASTノードを追加する
	ASTList_push_back_ref(parent->children, child);
}

/**
指定された親ASTノードに任意の子ASTノードを追加する。
@param parent 指定された親ASTノード
@param num 追加する子ASTノードの数
@param ... 追加する任意の子ASTノード
@return なし
*/
void multi_push_back_childrenAST(AST *parent,int num, ...){
	va_list AST_list;
	int i;
	//子ASTノードリストを取得
	va_start(AST_list, num);

	//子ASTノードの数分参照させる
	for(i = 0; i < num; i++){
		//親ASTノードに子ASTノードを追加する
		push_back_childrenAST(parent,va_arg(AST_list, AST*));
	}

	//子ASTノードリストを削除させる
	va_end(AST_list);
}
/**
指定された親ASTノードから、指定したノード名より下位についての情報をすべて表示させる。
また、traverse_flagを１にすることで、指定したノード名についてのすべての情報をツリー構造で表示させることもできる。
さらに、xml_flagを１にすることで、ツリー構造で表示させる内容がXMLとして出力できるようになる(traverse_flagが１になっていることが前提である)。
@param root 指定された親ASTノード
@param target 指定した文字列
@param traverse_flag 指定したノード名以下をツリー構造で表示させるかどうかのフラグ。１なら表示させ、０なら表示させない
@param xml_flag XMLとして出力するかどうかのフラグ。１ならXMLとして出力させる
@return なし
*/
void printTargetASTNode(AST *root, char *target, int traverse_flag , int xml_flag){
	int i;
	ASTListIterator p;
	CSTLString *node_content;
	//指定したノード名が見つかった場合
	if(CSTLString_compare_with_char(root->name, target) == 0){
		//ノード情報設定するための文字列にノードの内容を設定する
		node_content = CSTLString_new();
		getStringFromAST(node_content, root);
		//指定したASTノードの行数とその下位を含めたすべての情報を出力させる
		printf("line = \"%d\" , content = \"%s\"\n", root->line, CSTLString_c_str(node_content) );

		//ツリー構造も表示させるフラグが１になっている場合、ツリー構造も表示させる
		if(traverse_flag == 1){
			printf("\n#AST TREE INFOMATION\n");
			//XMLとして出力させるためのフラグが立ったら、XMLとして出力する。
			if(xml_flag == 1){
				traverseASTwithXML(root, 1);
			}else{
				traverseAST(root, 1);
			}
			printf("\n#HERE IS END AST TREE INFOMATION\n");
		}
		//ノード情報を設定するための文字列を破棄する
		CSTLString_delete(node_content);
	}

	//ASTノードが子ASTノードの情報を持っていたら、子ASTノードについて再帰的に参照させる
	for(p = ASTList_begin(root->children); p != ASTList_end(root->children); p = ASTList_next(p)){
		printTargetASTNode(ASTList_data(p), target, traverse_flag, xml_flag);
	}
}
/**
getArgumentStringの内部処理
@param output 出力される引数の内容
@param call_function 名前がcall_functionであるASTノード
@param arg_num 何番目の引数

@return 成功したかどうかを示す。成功したならば１、失敗した場合は０を返す。
*/
int getArgumentString_Internal(CSTLString *output, AST* argument, int *arg_num){
	ASTListIterator p;
	//成功したかどうかのフラグ
	int success_flag = 0;
	//もし、引数の内容を示すt_argument_expressionが来た場合
	if(CSTLString_compare_with_char(argument->name, "t_argument_expression") == 0){
		//引数を示す変数を減らし、0になればその引数の内容をoutputに設定する
		*arg_num = *arg_num - 1;
		if(*arg_num == 0){
			//success_flagを１にする
			success_flag = 1;
			getStringFromAST(output, argument);
		}
	}
	//ASTノードが子ASTノードの情報を持っていたら、子ASTノードについて再帰的に参照させる。success_flagが１になったら終了させる。
	for(p = ASTList_begin(argument->children); success_flag == 0 && p != ASTList_end(argument->children); p = ASTList_next(p)){
		success_flag = getArgumentString_Internal(output, ASTList_data(p), arg_num);
	}

	return success_flag;
}

/**
指定されたcall_functionに相当する関数から、任意の引数目の情報を取得する。
このとき、指定されたノード名はcall_functionでなければならない。
@param output 出力される引数の内容
@param call_function 名前がcall_functionであるASTノード
@param arg_num 何番目の引数
@return 成功したかどうかを示す。成功したならば１、失敗した場合は０を返す。
*/
int getArgumentString(CSTLString *output, AST* call_function, int arg_num){

	int success_flag;
	if(CSTLString_compare_with_char(call_function->name, "call_function") == 0){
		int *p_arg_num = &arg_num;
		success_flag = getArgumentString_Internal(output, call_function, p_arg_num);
	}else{
		success_flag = 0;
	}
	return success_flag;
}

/**
getArgumentStringEnableExceptの内部処理
@param output 出力される引数の内容
@param call_function 名前がcall_functionであるASTノード
@param arg_num 何番目の引数
@param num 除外したいASTノードリストの数
@param except_list 除外したいASTノード

@return 成功したかどうかを示す。成功したならば１、失敗した場合は０を返す。
*/
int getArgumentStringEnableExcept_Internal(CSTLString *output, AST* argument, int *arg_num, int num, char except_list[][256]){
	ASTListIterator p;
	//成功したかどうかのフラグ
	int success_flag = 0;
	//もし、引数の内容を示すt_argument_expressionが来た場合
	if(CSTLString_compare_with_char(argument->name, "t_argument_expression") == 0){
		//引数を示す変数を減らし、0になればその引数の内容をoutputに設定する
		*arg_num = *arg_num - 1;
		if(*arg_num == 0){
			//success_flagを１にする
			success_flag = 1;
			getStringFromASTEnableExcept(output, argument, num, except_list);
		}
	}
	//ASTノードが子ASTノードの情報を持っていたら、子ASTノードについて再帰的に参照させる。success_flagが１になったら終了させる。
	for(p = ASTList_begin(argument->children); success_flag == 0 && p != ASTList_end(argument->children); p = ASTList_next(p)){
		success_flag = getArgumentStringEnableExcept_Internal(output, ASTList_data(p), arg_num, num, except_list);
	}

	return success_flag;
}
/**
getArgumentEnableExceptの拡張版。出力対象にしない文字列を除いた引数の情報をすべて出力させる。
@param output 出力される引数の内容
@param call_function 名前がcall_functionであるASTノード
@param arg_num 何番目の引数
@param num 除外したいASTノードリストの数
@param except_list 除外したいASTノード

@return 成功したかどうかを示す。成功したならば１、失敗した場合は０を返す。
*/
int getArgumentStringEnableExcept(CSTLString *output, AST* call_function, int arg_num, int num, char except_list[][256]){
	int success_flag;
	if(CSTLString_compare_with_char(call_function->name, "call_function") == 0){
		int *p_arg_num = &arg_num;
		success_flag = getArgumentStringEnableExcept_Internal(output, call_function, p_arg_num, num, except_list);
	}else{
		success_flag = 0;
	}
	return success_flag;
}

/**
getArgumentASTの内部処理
@param output 取得する対象のノード
@param call_function 名前がcall_functionであるASTノード
@param arg_num 何番目の引数

@return 成功したかどうかを示す。成功したならば１、失敗した場合は０を返す。
*/
int getArgumentAST_Internal(AST **output, AST* argument, int *arg_num){
	ASTListIterator p;
	//成功したかどうかのフラグ
	int success_flag = 0;
	//もし、引数の内容を示すt_argument_expressionが来た場合
	if(CSTLString_compare_with_char(argument->name, "t_argument_expression") == 0){
		//引数を示す変数を減らし、0になればその引数の内容をoutputに設定する
		*arg_num = *arg_num - 1;
		if(*arg_num == 0){
			//success_flagを１にする
			success_flag = 1;
			*output = argument;
		}
	}
	//ASTノードが子ASTノードの情報を持っていたら、子ASTノードについて再帰的に参照させる。success_flagが１になったら終了させる。
	for(p = ASTList_begin(argument->children); success_flag == 0 && p != ASTList_end(argument->children); p = ASTList_next(p)){
		success_flag = getArgumentAST_Internal(output, ASTList_data(p), arg_num);
	}

	return success_flag;
}

/**
指定されたcall_functionに相当する関数から、任意の引数目へのノードを取得する。
このとき、指定されたノード名はcall_functionでなければならない。
@param output 取得する対象のノード
@param call_function 名前がcall_functionであるASTノード
@param arg_num 何番目の引数

@return 成功したかどうかを示す。成功したならば１、失敗した場合は０を返す。
*/
int getArgumentAST(AST **output, AST* call_function, int arg_num){
	int success_flag;
	if(CSTLString_compare_with_char(call_function->name, "call_function") == 0){
		int *p_arg_num = &arg_num;
		success_flag = getArgumentAST_Internal(output, call_function, p_arg_num);
	}else{
		success_flag = 0;
	}
	return success_flag;

}

/**
指定したASTノードrootから、指定した名前nameのASTノードを探す。
見つけたASTノードへのアドレスを返す。
@param root 指定したASTノード
@param name 指定した名前
@param depth 探索する子ノードの深さ（無限にする場合は-1を指定、子ノードは検索しない場合は0にする)
@return 見つけたASTノードへのアドレスを返す。
*/
AST *getASTwithString(AST *root, char *name, int depth){
	//子ASTノードをたどるイテレータ
	ASTListIterator p;
	//出力させるASTノード
	AST *output = NULL;
	if(depth < -1){
		fprintf(stderr, "深さが未定義です。\n");
		exit(1);
	}
	//指定した名前のASTノードを見つけたらその時点で返す。
	if(CSTLString_compare_with_char(root->name, name) == 0){
		output = root;
	}
	else{
		//depthが0になるまで繰り返す
		if(depth > 0){
			//ASTノードが子ASTノードの情報を持っていたら、子ASTノードについて再帰的に参照させる。success_flagが１になったら終了させる。
			for(p = ASTList_begin(root->children); output == NULL && p != ASTList_end(root->children); p = ASTList_next(p)){
				output = getASTwithString(ASTList_data(p), name, depth - 1);
			}
		}
		//depthが-1であれば、必ず子ノードを参照する
		else if(depth == -1){
			//ASTノードが子ASTノードの情報を持っていたら、子ASTノードについて再帰的に参照させる。success_flagが１になったら終了させる。
			for(p = ASTList_begin(root->children); output == NULL && p != ASTList_end(root->children); p = ASTList_next(p)){
				output = getASTwithString(ASTList_data(p), name, depth);
			}
		}
	}

	return output;

}

/**
getStringReplaceASTtoStringの内部処理。

@param root 指定したASTノード
@param output 出力する情報
@param target 変換対象のASTノードのアドレス
@param replace_string 変換先の文字列

@return なし
*/
void getStringReplaceASTtoString_Internal(CSTLString *output, AST *root, AST *target, char *replace_string){
	ASTListIterator p;
	//リーフノード（子ASTノードの数が0のASTノード）の場合、その内容をoutputに追加させる
	if(root == target){
		CSTLString_append(output, replace_string);
		CSTLString_append(output, " ");
	}else if(ASTList_size(root->children) == 0){
		CSTLString_append(output, CSTLString_c_str(root->content));
		CSTLString_append(output, " ");
	}else{
		//ASTノードが子ASTノードの情報を持っていたら、子ASTノードについて再帰的に参照させる
		for(p = ASTList_begin(root->children); p != ASTList_end(root->children); p = ASTList_next(p)){
			getStringReplaceASTtoString_Internal(output, ASTList_data(p), target, replace_string);
		}
	}
}

/**
指定したASTノードrootに対しての情報を文字列outputを出力させる。
そのとき、ASTノードのtargetのアドレス値と一致するノードを見つけた（アドレスとして全く同じASTノードを見つけた）
場合、そのノードだけreplace_stringに変換して出力させる。

@param root 指定したASTノード
@param output 出力する情報
@param target 変換対象のASTノードのアドレス
@param replace_string 変換先の文字列

@return なし
*/
void getStringReplaceASTtoString(CSTLString *output, AST *root, AST *target, char *replace_string){
	getStringReplaceASTtoString_Internal(output, root, target, replace_string);

	//文字列の末尾が半角スペースのとき、それを削除する
	if(CSTLString_size(output) > 0 && *CSTLString_at(output, CSTLString_size(output) - 1) == ' '){
		CSTLString_pop_back(output);
	}
}

/**
setASTReturnTypeの内部処理。ここでは、タイプを付加していく。

@param root 対象のASTノード
@param type 付加する返却値のタイプ

@return なし
*/
void setASTReturnType_Internal(AST *root, CSTLString *type){
	ASTListIterator ast_i;

	//返却値のタイプを付加する。
	CSTLString_printf(root->return_type, 0, "%s", CSTLString_c_str(type));

	//子ノードにも同じような処理を適応する
	for(ast_i = ASTList_begin(root->children);
		ast_i != ASTList_end(root->children);
		ast_i = ASTList_next(ast_i)){
			setASTReturnType_Internal(ASTList_data(ast_i), type);
	}
}

/**
対象のASTノードのroot以下にあるに、関数の返却値のタイプを指定する。

@param root 対象のASTノード

@return なし
*/
void setASTReturnType(AST *root){
	ASTListIterator ast_i;
	//関数定義を見つけた場合
	if(CSTLString_compare_with_char(root->name, "function_definition") == 0){
		//設定する返却の型
		CSTLString *return_type = CSTLString_new();

		//子ノードから返却値を取得
		for(ast_i = ASTList_begin(root->children);
			ast_i != ASTList_end(root->children);
			ast_i = ASTList_next(ast_i)){
				//型名として属する名前をみつけたら返却の型を取得する。
				if(CSTLString_compare_with_char(ASTList_data(ast_i)->name, "declaration_specifiers") == 0 ||
				CSTLString_compare_with_char(ASTList_data(ast_i)->name, "storage_class_specifier") == 0 ||
				CSTLString_compare_with_char(ASTList_data(ast_i)->name, "type_specifier") == 0 ||
				CSTLString_compare_with_char(ASTList_data(ast_i)->name, "type_qualifier") == 0 ||
				CSTLString_compare_with_char(ASTList_data(ast_i)->name, "function_specifier") == 0){
					getStringFromAST(return_type, ASTList_data(ast_i));
					break;
				}
		}

		//関数定義以下の子ノードについては全て返却の型を付加させる。
		for(ast_i = ASTList_begin(root->children);
			ast_i != ASTList_end(root->children);
			ast_i = ASTList_next(ast_i)){
				//declaration_specifiersから、返却の型を取得する。
				setASTReturnType_Internal(ASTList_data(ast_i), return_type);
		}

		CSTLString_delete(return_type);

	}
	//そうでなかったら、子ノードも探索する
	else{


		for(ast_i = ASTList_begin(root->children);
			ast_i != ASTList_end(root->children);
			ast_i = ASTList_next(ast_i)){
				setASTReturnType(ASTList_data(ast_i));
		}
	}
}
/**
setASTBlocklevelAndIdの内部処理である。

@param root 対象のASTノード

@return なし
*/
void setASTBlocklevelAndId_Internal(AST *root, STACK_INT *block_ids, int *block_level){
	ASTListIterator ast_i;

	int block_id;

	//"{"が来たら、ブロックレベルを上げる
	if(CSTLString_compare_with_char(root->name, "{") == 0){
		*block_level = *block_level + 1;
		STACK_INT_at_and_alloc(block_ids, *block_level - 1);
	}
	//"}"が来たら、次の同レベルブロックのために、先ほどのブロックレベルに対するIDをインクリメントしたうえで、ブロックレベルを下げる
	else if(CSTLString_compare_with_char(root->name,"}") == 0){
		STACK_INT_inclement_at(block_ids, *block_level - 1);
		*block_level = *block_level - 1;
	}

	//ブロックレベルが0を超える場合はblock_idsからブロックIDを取得する
	if(*block_level > 0){
		block_id = STACK_INT_at_and_alloc(block_ids, *block_level - 1);
	}
	//0である場合はブロックIDは0にする
	else{
		block_id = 0;
	}

	//指定したASTノードにブロックレベルとブロックIDとIDLISTを付加する
	root->block_level = *block_level;
	root->block_id = block_id;
	SET_STACK_INTToIDLIST(root->idlist, block_ids, *block_level);

	for(ast_i = ASTList_begin(root->children);
		ast_i != ASTList_end(root->children);
		ast_i = ASTList_next(ast_i)){

			setASTBlocklevelAndId_Internal(ASTList_data(ast_i), block_ids, block_level);
	}
}

/**
対象のASTノードに、ブロックIDおよびブロックレベルを付加する。

@param root 対象のASTノード


@return なし
*/
void setASTBlocklevelAndId(AST *root){
	STACK_INT *block_ids = STACK_INT_new();
	int block_level = 0;
	setASTBlocklevelAndId_Internal(root, block_ids, &block_level);
}

/**
探す対象のASTノードrootから、指定したASTノードのアドレスtargetが存在するかどうか調べる。みつければ、１を返し、そうでなければ０を返す。

@param root 探す対象のASTノード
@param target 指定したASTノードのアドレス

@return 指定したASTノードtargetを見つけたら１を返し、そうでなければ０を返す。
*/
int findASTAddress(AST *root, AST *target){
	int find_flag = 0;

	ASTListIterator ast_i;

	//もし、targetを見つけられたら、１を返す。
	if(root == target){
		find_flag = 1;
	}
	//そうでなければ、子ノードも探し、子ノードから見つけることが出来たら終了する
	else{
		for(ast_i = ASTList_begin(root->children);
			find_flag == 0 && ast_i != ASTList_end(root->children);
			ast_i = ASTList_next(ast_i)){

				find_flag = findASTAddress(ASTList_data(ast_i), target);
		}
	}

	return find_flag;
}


/**
指定されたノードに対して、statementの直前まで出力させる。また、出力対象となっているノード番号が来るまでは出力の対象としない。
ブロックとして表記されている場合は始まりのブロックや終わりのブロックへのASTノードのアドレスをout_block_startやout_block_endに
設定する。そうでなければ、NULLで設定される。

@param output 出力先のファイル構造体
@param root 指定されたASTノード
@param line 出力に利用する行数
@param output_subnode_num 出力対象となるノード番号 １～ｎ（１に指定すると、すべての子ノードが出力の対象となる）
@param out_block_start ブロックとして表記されている場合は、始まりのブロックへのASTノードのアドレスを返却する
@param out_block_end ブロックとして表記されている場合は、終わりブのロックへのASTノードのアドレスを返却する。
@return なし
 */

void fprintfStatement(FILE *output, AST *root, int *line, int output_subnode_num, AST **out_block_start, AST **out_block_end){

	ASTListIterator ast_i;

	*out_block_start = NULL;
	*out_block_end = NULL;

	int counter;

	//対象のASTノードの子ノードを探索する
	for(counter = 1, ast_i = ASTList_begin(root->children);
		ast_i != ASTList_end(root->children);
		counter++, ast_i = ASTList_next(ast_i)){
		//指定された出力対象となるノード番号を超えた場合、出力対象とする
		if(counter >= output_subnode_num){
			//statementを見つけた場合
			if(CSTLString_compare_with_char(ASTList_data(ast_i)->name, "statement") == 0){

				//ブロックとして表記されている場合、始まりと終わりブロックへのASTノードのアドレスを取得する
				if(CSTLString_compare_with_char(ASTLIST_ITERATOR_1(ASTList_data(ast_i))->name, "compound_statement_a") == 0){
					*out_block_start = ASTLIST_ITERATOR_1(ASTLIST_ITERATOR_1(ASTList_data(ast_i)));
					*out_block_end = ASTLIST_ITERATOR_2(ASTLIST_ITERATOR_1(ASTList_data(ast_i)));
					fprintDataFromAST(output, ASTLIST_ITERATOR_1(ASTLIST_ITERATOR_1(ASTList_data(ast_i))), line);
				}
				else if(CSTLString_compare_with_char(ASTLIST_ITERATOR_1(ASTList_data(ast_i))->name, "compound_statement_b") == 0){
					*out_block_start = ASTLIST_ITERATOR_1(ASTLIST_ITERATOR_1(ASTList_data(ast_i)));
					*out_block_end = ASTLIST_ITERATOR_3(ASTLIST_ITERATOR_1(ASTList_data(ast_i)));
					fprintDataFromAST(output, ASTLIST_ITERATOR_1(ASTLIST_ITERATOR_1(ASTList_data(ast_i))), line);
				}

				break;

			}
			//compound_statement_aを見つけた場合
			else if(CSTLString_compare_with_char(ASTList_data(ast_i)->name, "compound_statement_a") == 0){
				*out_block_start = ASTLIST_ITERATOR_1(ASTList_data(ast_i));
				*out_block_end = ASTLIST_ITERATOR_2(ASTList_data(ast_i));
				fprintDataFromAST(output, ASTLIST_ITERATOR_1(ASTList_data(ast_i)), line);
			}
			//compound_statement_bを見つけた場合
			else if(CSTLString_compare_with_char(ASTList_data(ast_i)->name, "compound_statement_b") == 0){
				*out_block_start = ASTLIST_ITERATOR_1(ASTList_data(ast_i));
				*out_block_end = ASTLIST_ITERATOR_3(ASTList_data(ast_i));
				fprintDataFromAST(output, ASTLIST_ITERATOR_1(ASTList_data(ast_i)), line);
			}else{

				//子ノード以下の内容を、行数に応じて出力させる
				fprintDataFromAST(output, ASTList_data(ast_i), line);

			}
		}

	}

}
