#include "recognizeEq.h"
#include "scanner.h"

#include <stdio.h>  /* printf */
#include <stdlib.h> /* NULL, free */
#include <string.h>

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

int amountVariable(List *lp) {
  List temp = *lp;
  int amount = 0;
  char *v = NULL;

  while (temp != NULL) {
    if (temp->tt == Identifier) {
      char *varName = temp->t.identifier;

      if (amount == 0) {
        amount += 1;
        v = varName;
      } else {
        if (strcmp(v, varName) == 0) {
          continue;
        } else {
          amount = 2;
          break;
        }
      }
    }
    temp = temp->next;
  }

  return amount;
}

int degree(List *lp) {
  int maxDegree = 1;
  List temp = *lp;

  while (temp != NULL) {
    if (temp->tt == Identifier) {
      if (temp->next != NULL && temp->next->tt == Symbol && temp->next->t.symbol == '^') {
        if (temp->next->next != NULL && temp->next->next->tt == Number) {
          int termDegree = temp->next->next->t.number;
          if (termDegree > maxDegree) {
            maxDegree = termDegree;
          }
          temp = temp->next->next->next;
          continue;
        }
      }
    }
    temp = temp->next;
  }
  
  return maxDegree;
}


void recognizeEquations() {
  char *ar;
  List tl, tl1;
  printf("give an equation: ");
  fflush(stdout);
  ar = readInput();

  while (ar[0] != '!') {
    tl = tokenList(ar);
    tl1 = tl;
    if (acceptEquation(&tl1) && tl1 == NULL) {
      printf("this is an equation");

      switch (amountVariable(&tl)) {
      case 0:
        break;
      case 1: {
        printf(" in 1 variable");
        int n = degree(&tl);
        printf(" of degree %d", n);
        break;
      }
      case 2:
        printf(", but not in 1 variable");
        break;
      default:
        break;
      }

      printf("\n");
    } else {
      printf("this is not an equation\n");
    }

    free(ar);
    freeTokenList(tl);
    printf("\ngive an equation: ");
    fflush(stdout);
    ar = readInput();
  }
  free(ar);
  printf("good bye\n");
}
