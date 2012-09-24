/*
 * WriteVelificationStatement.h
 *
 *  Created on: 2012/06/11
 *      Author: fken-2
 */

#ifndef WRITEVELIFICATIONSTATEMENT_H_
#define WRITEVELIFICATIONSTATEMENT_H_

#include "PointerArrayControl.h"
#include "DivitionInformation.h"
#include "../Library/CSTLString.h"

void writeArrayCheck(CSTLString *output, ARRAY_OFFSET_LISTIterator aoff_list_i, int undefined_control_check, int array_unbound_check);

void writeZeroCheck(CSTLString *statement, DIVITION_INFORMATION_LISTIterator di_i);
#endif /* WRITEVELIFICATIONSTATEMENT_H_ */
