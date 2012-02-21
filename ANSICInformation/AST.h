/*!
  @brief ���̃t�@�C���́A�\����͂ɂ���Ēʂ��ꂽC����v���O��������A���ۍ\���؁iAST�j�𐶐������邽�߂̂��̂ł���B
  �܂�����������ق��ɁA���ۂɒ��ۍ\���؂���\�[�X�t�@�C���𐶐����Ȃ�������A���镔���̃m�[�h���當����𐶐���������Ƃ��������Ƃ��ł���B

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
C����v���O�����̒��ۍ\���؂Ɋւ����񂪊܂܂��B
 */
typedef struct abstract_syntax_tree{
	CSTLString *name;			///�m�[�h��
	CSTLString *content;		///�m�[�h�̓��e
	int line;					///�Ώۂ̃m�[�h�̍s��
	CSTLString *return_type;	///�ԋp�l�̃^�C�v(void�Aint�Adouble�Ȃǂ�����)
	int block_level;			///�u���b�N�̊K�w���x���i�O���[�o���̏ꍇ�͂O�A���炩�̊֐����ł���΂P�ƂȂ�j
	int block_id;				///�e�X�̃u���b�N�����ʂ��邽�߂̂��́B�O���珇�ɐݒ肳���
	IDLIST *idlist;				///�u���b�N�̊K�w����ю��ʎq�𓯎��Ɏ��ʂ��邽�߂̂��́B�ϐ���`�Ɋւ��Ċm�F����̂ɗp����
	ASTList *children;			///�m�[�h�����q�m�[�h���X�g
} AST;

/**
�V����AST�m�[�h�𐶐�����B
@param new_name �V�����m�[�h��
@param new_content �V�������e
@param new_line �V�����s��
@return �V�����������ꂽAST�m�[�h�ւ̃A�h���X���Ԃ����B
*/
AST* new_AST(char *new_name, char *new_content,int new_line);

/**
���O�Ɠ��e�������ł���AST�m�[�h�𐶐�����B
@param new_name �V�����m�[�h��
@param new_line �V�����s��
@return �V�����������ꂽAST�m�[�h�ւ̃A�h���X���Ԃ����B
*/
AST* same_new_AST(char *new_name, int new_line);

/**
AST�̃m�[�h�����ǂ�Aroot�m�[�h�ȉ��̃m�[�h�̖��O�E���e�E�s����\��������B
�܂��A���ʃ��x���̃m�[�h�̓^�u��}�����\������B�Ⴆ�΁A1���x�����ʂ̃m�[�h�̓^�u��1�}��������ŕ\�������B
@param root �V�����m�[�h��
@param tab_level �^�u���x��(���̐����^�u���}�������j
@return �Ȃ�
*/

void traverseAST(AST* root,int tab_level);

/**
AST�̃m�[�h�����ǂ�Aroot�m�[�h�ȉ��̃m�[�h�̖��O�E���e�E�s����XML�`���ŏo�͂���B�i�f�o�b�O�p�j
�܂��A���ʃ��x���̃m�[�h�̓^�u��}�����o�͂���B�Ⴆ�΁A1���x�����ʂ̃m�[�h�̓^�u��1�}��������Ń^�O���o�͂����B
XML�ɂ��Ă͎��̌`���ŏo�͂���(a�̓��[�g�m�[�h�Aa_sub�̓��[�t�m�[�h�ł���Ƃ���j
<a content = "" line = "1">
	<leaf name="a_sub" content = "+" line = "1"/>
</a>

@param root �V�����m�[�h��
@param tab_level �^�u���x��(���̐����^�u���}�������j
@return �Ȃ�
*/
void traverseASTwithXML(AST* root,int tab_level);

/**
�w�肳�ꂽAST�m�[�h�ȉ��̓��e���A�w�肳�ꂽ�t�@�C���ɑ΂��ďo�͂�����
@param output �o�͐�̃t�@�C���\����
@param root �w�肳�ꂽ�m�[�h��
@param line �o�͂ɗ��p����s��

@return �Ȃ�
 */
void fprintDataFromAST(FILE *output, AST *root, int *line);
/**
�w�肵��AST�m�[�h�ȉ��̓��e���o�͂�����BAST�m�[�h�̍s���ɂ��������ďo�͂����B
@param root �V�����m�[�h��
@param line �w�肷��s��(��{�I�ɂP����͂���j
@return �Ȃ�
*/
void printDataFromAST(AST* root, int *line);

/**
�w�肵��AST�m�[�h�ȉ��̓��e���o�͑Ώۂ̕�����f�[�^�ɏo�͂�����B
@param output �o�͑Ώۂ̕�����f�[�^
@param root �V�����m�[�h��
@return �Ȃ�
*/
void getStringFromAST(CSTLString* output, AST* root);

/**
getStringFromAST�̊g���ŁB�o�͑Ώۂ��珜�O����AST�m�[�h�����w��ł���B
@param output �o�͑Ώۂ̕�����f�[�^
@param root �V�����m�[�h��
@param num ���O������AST�m�[�h���X�g�̐�
@param except_list ���O������AST�m�[�h
@return �Ȃ�
*/

void getStringFromASTEnableExcept(CSTLString* output, AST* root,int num, char except_list[][256]);

/**
�w�肵��AST�m�[�h�ȉ���S�ĊJ��������B
@param root �w�肵��AST�m�[�h
@return �Ȃ�
*/
void deleteAST(AST* root);

/**
�w�肳�ꂽ�eAST�m�[�h�Ɏw�肳�ꂽ�qAST�m�[�h��ǉ�����B
@param parent �w�肳�ꂽ�eAST�m�[�h
@param child �w�肳�ꂽ�qAST�m�[�h
@return �Ȃ�
*/
void push_back_childrenAST(AST *parent, AST *child);

/**
�w�肳�ꂽ�eAST�m�[�h�ɔC�ӂ̎qAST�m�[�h��ǉ�����B
@param parent �w�肳�ꂽ�eAST�m�[�h
@param num �ǉ�����qAST�m�[�h�̐�
@param ... �ǉ�����C�ӂ̎qAST�m�[�h
@return �Ȃ�
*/
void multi_push_back_childrenAST(AST *parent,int num, ...);

/**
�w�肳�ꂽ�eAST�m�[�h����A�w�肵���m�[�h����艺�ʂɂ��Ă̏������ׂĕ\��������B�B
�܂��Atraverse_flag���P�ɂ��邱�ƂŁA�w�肵���m�[�h���ɂ��Ă̂��ׂĂ̏����c���[�\���ŕ\�������邱�Ƃ��ł���B
����ɁAxml_flag���P�ɂ��邱�ƂŁA�c���[�\���ŕ\����������e��XML�Ƃ��ďo�͂ł���悤�ɂȂ�(traverse_flag���P�ɂȂ��Ă��邱�Ƃ��O��ł���)�B
@param root �w�肳�ꂽ�eAST�m�[�h
@param target �w�肵��������
@param traverse_flag �w�肵���m�[�h���ȉ����c���[�\���ŕ\�������邩�ǂ����̃t���O�B�P�Ȃ�\�������A�O�Ȃ�\�������Ȃ�
@param xml_flag XML�Ƃ��ďo�͂��邩�ǂ����̃t���O�B�P�Ȃ�XML�Ƃ��ďo�͂�����
@return �Ȃ�
*/
void printTargetASTNode(AST *root, char *target, int traverse_flag , int xml_flag);

/**
�w�肳�ꂽcall_function�ɑ�������֐�����A�C�ӂ̈����ڂ̏����擾����B
���̂Ƃ��A�w�肳�ꂽ�m�[�h����call_function�łȂ���΂Ȃ�Ȃ��B
@param output �o�͂��������̓��e
@param call_function ���O��call_function�ł���AST�m�[�h
@param arg_num ���Ԗڂ̈���
@return �����������ǂ����������B���������Ȃ�΂P�A���s�����ꍇ�͂O��Ԃ��B
*/
int getArgumentString(CSTLString *output, AST* call_function, int arg_num);

/**
getArgumentEnableExcept�̊g���ŁB�o�͑Ώۂɂ��Ȃ�������������������̏������ׂďo�͂�����B
@param output �o�͂��������̓��e
@param call_function ���O��call_function�ł���AST�m�[�h
@param arg_num ���Ԗڂ̈���
@param num ���O������AST�m�[�h���X�g�̐�
@param except_list ���O������AST�m�[�h

@return �����������ǂ����������B���������Ȃ�΂P�A���s�����ꍇ�͂O��Ԃ��B
*/
int getArgumentStringEnableExcept(CSTLString *output, AST* call_function, int arg_num, int num, char except_list[][256]);

/**
�w�肳�ꂽcall_function�ɑ�������֐�����A�C�ӂ̈����ڂւ̃m�[�h���擾����B
���̂Ƃ��A�w�肳�ꂽ�m�[�h����call_function�łȂ���΂Ȃ�Ȃ��B
@param output �擾����Ώۂ̃m�[�h
@param call_function ���O��call_function�ł���AST�m�[�h
@param arg_num ���Ԗڂ̈���

@return �����������ǂ����������B���������Ȃ�΂P�A���s�����ꍇ�͂O��Ԃ��B
*/
int getArgumentAST(AST **output, AST* call_function, int arg_num);

/**
�w�肵��AST�m�[�hroot����A�w�肵�����Oname��AST�m�[�h��T���B
������AST�m�[�h�ւ̃A�h���X��Ԃ��B
@param root �w�肵��AST�m�[�h
@param name �w�肵�����O
@param depth �T������q�m�[�h�̐[���i�����ɂ���ꍇ��-1���w��A�q�m�[�h�͌������Ȃ��ꍇ��0�ɂ���)
@return ������AST�m�[�h�ւ̃A�h���X��Ԃ��B
*/
AST *getASTwithString(AST *root, char *name, int depth);

/**
�w�肵��AST�m�[�hroot�ɑ΂��Ă̏��𕶎���output���o�͂�����B
���̂Ƃ��AAST�m�[�h��target�̃A�h���X�l�ƈ�v����m�[�h���������i�A�h���X�Ƃ��đS������AST�m�[�h���������j
�ꍇ�A���̃m�[�h����replace_string�ɕϊ����ďo�͂�����B

@param root �w�肵��AST�m�[�h
@param output �o�͂�����
@param target �ϊ��Ώۂ�AST�m�[�h�̃A�h���X
@param replace_string �ϊ���̕�����

@return �Ȃ�
*/
void getStringReplaceASTtoString(CSTLString *output, AST *root, AST *target, char *replace_string);

/**
�Ώۂ�AST�m�[�h��root�ȉ��ɂ���ɁA�֐��̕ԋp�l�̃^�C�v���w�肷��B

@param root �Ώۂ�AST�m�[�h

@return �Ȃ�
*/
void setASTReturnType(AST *root);

/**
�Ώۂ�AST�m�[�h�ɁA�u���b�NID����уu���b�N���x����t������B

@param root �Ώۂ�AST�m�[�h


@return �Ȃ�
*/
void setASTBlocklevelAndId(AST *root);

/**
�T���Ώۂ�AST�m�[�hroot����A�w�肵��AST�m�[�h�̃A�h���Xtarget�����݂��邩�ǂ������ׂ�B�݂���΁A�P��Ԃ��A�����łȂ���΂O��Ԃ��B

@param root �T���Ώۂ�AST�m�[�h
@param target �w�肵��AST�m�[�h�̃A�h���X

@return �w�肵��AST�m�[�htarget����������P��Ԃ��A�����łȂ���΂O��Ԃ��B
*/
int findASTAddress(AST *root, AST *target);

/**
�w�肳�ꂽ�m�[�h�ɑ΂��āAstatement�̒��O�܂ŏo�͂�����B�܂��A�o�͑ΏۂƂȂ��Ă���m�[�h�ԍ�������܂ł͏o�͂̑ΏۂƂ��Ȃ��B
�u���b�N�Ƃ��ĕ\�L����Ă���ꍇ�͎n�܂�̃u���b�N��I���̃u���b�N�ւ�AST�m�[�h�̃A�h���X��out_block_start��out_block_end��
�ݒ肷��B�����łȂ���΁ANULL�Őݒ肳���B

@param output �o�͐�̃t�@�C���\����
@param root �w�肳�ꂽAST�m�[�h
@param line �o�͂ɗ��p����s��
@param output_subnode_num �o�͑ΏۂƂȂ�m�[�h�ԍ� �P�`���i�P�Ɏw�肷��ƁA���ׂĂ̎q�m�[�h���o�͂̑ΏۂƂȂ�j
@param out_block_start �u���b�N�Ƃ��ĕ\�L����Ă���ꍇ�́A�n�܂�̃u���b�N�ւ�AST�m�[�h�̃A�h���X��ԋp����
@param out_block_end �u���b�N�Ƃ��ĕ\�L����Ă���ꍇ�́A�I���u�̃��b�N�ւ�AST�m�[�h�̃A�h���X��ԋp����B
@return �Ȃ�
 */

void fprintfStatement(FILE *output, AST *root, int *line, int output_subnode_num, AST **out_block_start, AST **out_block_end);

#endif //AST_HEADDER
