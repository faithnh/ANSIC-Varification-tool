
#include"ANSIC_CODE.h"

inline AST *ASTLIST_ITERATOR_1(AST *target){
	return ASTList_data(ASTList_begin(target->children));
}
inline AST *ASTLIST_ITERATOR_2(AST *target){
	return ASTList_data(ASTList_next(ASTList_begin(target->children)));
}
inline AST *ASTLIST_ITERATOR_3(AST *target){
	return ASTList_data(ASTList_next(ASTList_next(ASTList_begin(target->children))));
}
inline AST *ASTLIST_ITERATOR_4(AST *target){
	return ASTList_data(ASTList_next(ASTList_next(ASTList_next(ASTList_begin(target->children)))));
}
inline AST *ASTLIST_ITERATOR_5(AST *target){
	return ASTList_data(ASTList_next(ASTList_next(ASTList_next(ASTList_next(ASTList_begin(target->children))))));
}
inline AST *ASTLIST_ITERATOR_6(AST *target){
	return ASTList_data(ASTList_next(ASTList_next(ASTList_next(ASTList_next(ASTList_next(ASTList_begin(target->children)))))));
}
inline AST *ASTLIST_ITERATOR_7(AST *target){
	return ASTList_data(ASTList_next(ASTList_next(ASTList_next(ASTList_next(ASTList_next(ASTList_next(ASTList_begin(target->children))))))));
}
