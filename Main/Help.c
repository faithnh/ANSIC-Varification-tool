#include <stdio.h>
#include "Help.h"

/**
ANSIC Varidate Statement Adder tool ÉwÉãÉvÇèoóÕÇ≥ÇπÇÈÅB

@return Ç»Çµ
 */
void viewHelp(void){
	printf("**************************************************************************\n");
	printf("*              ANSIC Validate Statement Adder Tool ver 1.0               *\n");
	printf("**************************************************************************\n\n");
	printf("Description:\n\n");
	printf(" This tool add validate the illegal statement such array unbound check and undefined operation\n");
	printf("to validate in CBMC. Target Source File is ANSI-C file. NOT support C++ Source File.\n");
	printf("And, NOT support nested assignment or increment or decrement expression.\n\n");
	printf("Command: ./ansic CProgramSourceFileName [Option]\n\n");
	printf("--------------------------------Option List--------------------------------\n\n");
	printf("--array-unbound-check: Check the Array Unbound.\n");
	printf("--undefined-control-check: Check the undefined operation, for example , assigning pointer variable undefined local variable.\n");
	printf("--zero-division-check: Check ZERO division or ZERO remainder operation.\n");
	printf("--h : Show Help.\n");
	printf("--xml : Output XML Tree of C Program.\n\n");
	printf("---------------------------------------------------------------------------\n");
}
