/*!
  @brief このファイルは、構文解析によって通されたC言語プログラムから、抽象構文木（AST）を生成させるためのものである。
  また生成させるほかに、実際に抽象構文木からソースファイルを生成しなおしたり、ある部分のノードから文字列を生成させたりといったことができる。

  @file AST.h
  @author faithnh

 */
#ifndef AST_HEADDER
#define AST_HEADDER

#include <cstl/string.h>
#include <cstl/list.h>
#include <stdio.h>
#include "../Library/CSTLString.h"
#include "../Library/IdList.h"

struct abstract_syntax_tree;

CSTL_LIST_INTERFACE(ASTList, struct abstract_syntax_tree)

/**
C言語プログラムの抽象構文木に関する情報が含まれる。
 */
typedef struct abstract_syntax_tree{
	CSTLString *name;			///ノード名
	CSTLString *content;		///ノードの内容
	int line;					///対象のノードの行数
	CSTLString *return_type;	///返却値のタイプ(void、int、doubleなどが入る)
	int block_level;			///ブロックの階層レベル（グローバルの場合は０、何らかの関数内であれば１となる）
	int block_id;				///各々のブロックを識別するためのもの。０から順に設定される
	IDLIST *idlist;				///ブロックの階層および識別子を同時に識別するためのもの。変数定義に関して確認するのに用いる
	ASTList *children;			///ノードが持つ子ノードリスト
} AST;

/**
新しいASTノードを生成する。
@param new_name 新しいノード名
@param new_content 新しい内容
@param new_line 新しい行数
@return 新しく生成されたASTノードへのアドレスが返される。
*/
AST* new_AST(char *new_name, char *new_content,int new_line);

/**
名前と内容が同じであるASTノードを生成する。
@param new_name 新しいノード名
@param new_line 新しい行数
@return 新しく生成されたASTノードへのアドレスが返される。
*/
AST* same_new_AST(char *new_name, int new_line);

/**
ASTのノードをたどり、rootノード以下のノードの名前・内容・行数を表示させる。
また、下位レベルのノードはタブを挿入し表示する。例えば、1レベル下位のノードはタブが1つ挿入した上で表示される。
@param root 新しいノード名
@param tab_level タブレベル(この数分タブが挿入される）
@return なし
*/

void traverseAST(AST* root,int tab_level);

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
void traverseASTwithXML(AST* root,int tab_level);

/**
指定されたASTノード以下の内容を、指定されたファイルに対して出力させる
@param output 出力先のファイル構造体
@param root 指定されたノード名
@param line 出力に利用する行数

@return なし
 */
void fprintDataFromAST(FILE *output, AST *root, int *line);
/**
指定したASTノード以下の内容を出力させる。ASTノードの行数にしたがって出力される。
@param root 新しいノード名
@param line 指定する行数(基本的に１を入力する）
@return なし
*/
void printDataFromAST(AST* root, int *line);

/**
指定したASTノード以下の内容を出力対象の文字列データに出力させる。
@param output 出力対象の文字列データ
@param root 新しいノード名
@return なし
*/
void getStringFromAST(CSTLString* output, AST* root);

/**
getStringFromASTの拡張版。出力対象から除外したASTノード名を指定できる。
@param output 出力対象の文字列データ
@param root 新しいノード名
@param num 除外したいASTノードリストの数
@param except_list 除外したいASTノード
@return なし
*/

void getStringFromASTEnableExcept(CSTLString* output, AST* root,int num, char except_list[][256]);

/**
指定したASTノード以下を全て開放させる。
@param root 指定したASTノード
@return なし
*/
void deleteAST(AST* root);

/**
指定された親ASTノードに指定された子ASTノードを追加する。
@param parent 指定された親ASTノード
@param child 指定された子ASTノード
@return なし
*/
void push_back_childrenAST(AST *parent, AST *child);

/**
指定された親ASTノードに任意の子ASTノードを追加する。
@param parent 指定された親ASTノード
@param num 追加する子ASTノードの数
@param ... 追加する任意の子ASTノード
@return なし
*/
void multi_push_back_childrenAST(AST *parent,int num, ...);

/**
指定された親ASTノードから、指定したノード名より下位についての情報をすべて表示させる。。
また、traverse_flagを１にすることで、指定したノード名についてのすべての情報をツリー構造で表示させることもできる。
さらに、xml_flagを１にすることで、ツリー構造で表示させる内容がXMLとして出力できるようになる(traverse_flagが１になっていることが前提である)。
@param root 指定された親ASTノード
@param target 指定した文字列
@param traverse_flag 指定したノード名以下をツリー構造で表示させるかどうかのフラグ。１なら表示させ、０なら表示させない
@param xml_flag XMLとして出力するかどうかのフラグ。１ならXMLとして出力させる
@return なし
*/
void printTargetASTNode(AST *root, char *target, int traverse_flag , int xml_flag);

/**
指定されたcall_functionに相当する関数から、任意の引数目の情報を取得する。
このとき、指定されたノード名はcall_functionでなければならない。
@param output 出力される引数の内容
@param call_function 名前がcall_functionであるASTノード
@param arg_num 何番目の引数
@return 成功したかどうかを示す。成功したならば１、失敗した場合は０を返す。
*/
int getArgumentString(CSTLString *output, AST* call_function, int arg_num);

/**
getArgumentEnableExceptの拡張版。出力対象にしない文字列を除いた引数の情報をすべて出力させる。
@param output 出力される引数の内容
@param call_function 名前がcall_functionであるASTノード
@param arg_num 何番目の引数
@param num 除外したいASTノードリストの数
@param except_list 除外したいASTノード

@return 成功したかどうかを示す。成功したならば１、失敗した場合は０を返す。
*/
int getArgumentStringEnableExcept(CSTLString *output, AST* call_function, int arg_num, int num, char except_list[][256]);

/**
指定されたcall_functionに相当する関数から、任意の引数目へのノードを取得する。
このとき、指定されたノード名はcall_functionでなければならない。
@param output 取得する対象のノード
@param call_function 名前がcall_functionであるASTノード
@param arg_num 何番目の引数

@return 成功したかどうかを示す。成功したならば１、失敗した場合は０を返す。
*/
int getArgumentAST(AST **output, AST* call_function, int arg_num);

/**
指定したASTノードrootから、指定した名前nameのASTノードを探す。
見つけたASTノードへのアドレスを返す。
@param root 指定したASTノード
@param name 指定した名前
@param depth 探索する子ノードの深さ（無限にする場合は-1を指定、子ノードは検索しない場合は0にする)
@return 見つけたASTノードへのアドレスを返す。
*/
AST *getASTwithString(AST *root, char *name, int depth);

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
void getStringReplaceASTtoString(CSTLString *output, AST *root, AST *target, char *replace_string);

/**
対象のASTノードのroot以下にあるに、関数の返却値のタイプを指定する。

@param root 対象のASTノード

@return なし
*/
void setASTReturnType(AST *root);

/**
対象のASTノードに、ブロックIDおよびブロックレベルを付加する。

@param root 対象のASTノード


@return なし
*/
void setASTBlocklevelAndId(AST *root);

/**
探す対象のASTノードrootから、指定したASTノードのアドレスtargetが存在するかどうか調べる。みつければ、１を返し、そうでなければ０を返す。

@param root 探す対象のASTノード
@param target 指定したASTノードのアドレス

@return 指定したASTノードtargetを見つけたら１を返し、そうでなければ０を返す。
*/
int findASTAddress(AST *root, AST *target);

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

void fprintfStatement(FILE *output, AST *root, int *line, int output_subnode_num, AST **out_block_start, AST **out_block_end);

#endif //AST_HEADDER
