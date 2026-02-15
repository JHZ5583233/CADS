#include "recognizeEq.h"
#include "scanner.h"

#include <stdio.h>  /* printf */
#include <stdlib.h> /* NULL, free */

int acceptNumber(List *lp) {
  if (*lp != NULL && (*lp)->tt == Number) {
    *lp = (*lp)->next;
    return 1;
  }
  return 0;
}

int acceptIdentifier(List *lp) {
  if (*lp != NULL && (*lp)->tt == Identifier) {
    *lp = (*lp)->next;
    return 1;
  }
  return 0;
}

int acceptCharacter(List *lp, char c) {
  if (*lp != NULL && (*lp)->tt == Symbol && ((*lp)->t).symbol == c) {
    *lp = (*lp)->next;
    return 1;
  }
  return 0;
}

int acceptTerm(List *lp) {
  List temp = *lp;
  int hasNumber = acceptNumber(&temp);
  
  if (acceptIdentifier(&temp)) {
    if (acceptCharacter(&temp, '^')) {
      if (!acceptNumber(&temp)) {
        return 0;
      }
    }
    *lp = temp;
    return 1;
  }
  
  if (hasNumber) {
    *lp = temp;
    return 1;
  }
  
  return 0;
}

int acceptExpression(List *lp) {
  List temp = *lp;

  acceptCharacter(&temp, '-'); 
  if (!acceptTerm(&temp)) {
    return 0;
  }

  while (acceptCharacter(&temp, '+') || acceptCharacter(&temp, '-')) {
    if (!acceptTerm(&temp)) {
      return 0;
    }
  }
  
  *lp = temp;
  return 1;
}

int acceptEquation(List *lp) {
  List temp = *lp;
  
  if (!acceptExpression(&temp)) {
    return 0;
  }
  
  if (!acceptCharacter(&temp, '=')) {
    return 0;
  }
  
  if (!acceptExpression(&temp)) {
    return 0;
  }
  
  *lp = temp;
  return 1;
}

void recognizeEquations() {
  char *ar;
  List tl, tl1;
  printf("give an equation: ");
  ar = readInput();
  while (ar[0] != '!') {
    tl = tokenList(ar);
    printf("the token list is ");
    printList(tl);
    tl1 = tl;
    if (acceptEquation(&tl1) && tl1 == NULL) {
      printf("this is an equation\n");
    } else {
      printf("this is not an equation\n");
    }
    free(ar);
    freeTokenList(tl);
    printf("\ngive an equation: ");
    ar = readInput();
  }
  free(ar);
  printf("good bye\n");
}
