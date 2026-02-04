#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include "LibStack.h"

typedef struct TextEditor {
  char *text;
  Stack action_history;
  int length;
  int capacity;
} TextEditor;

#endif
