/* recognizeEq.h - Equation recognizer header */

#ifndef RECOGNIZEEQ_H
#define RECOGNIZEEQ_H

#include "scanner.h"

int acceptNumber(List *lp);
int acceptIdentifier(List *lp);
int acceptCharacter(List *lp, char c);
int acceptTerm(List *lp);
int acceptExpression(List *lp);
int acceptEquation(List *lp);
void recognizeEquations();

#endif
