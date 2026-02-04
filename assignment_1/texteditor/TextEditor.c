#include "TextEditor.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define TEXT_EDITOR_INITIAL_CAPACITY 10

TextEditor* createTextEditor(void) {
  TextEditor *editor = malloc(sizeof(*editor));
  editor->text = malloc(TEXT_EDITOR_INITIAL_CAPACITY * sizeof(*editor->text));
  assert(editor->text != NULL);

  editor->length = 0;
  editor->capacity = TEXT_EDITOR_INITIAL_CAPACITY;
  return editor;
}

void insertCharacter(TextEditor *editor, int pos, char character) {
    // Implement the insert operation
    for (int i = pos; i < editor->capacity;i++) {
        editor->text[i + 1] = editor->text[i];
    }
    editor->text[pos] = character;
}

void deleteCharacter(TextEditor *editor, int pos) {
  // Implement the delete operation

    for (int i =pos;i<editor->length;i++) {
        editor->text[i] = editor->text[i+1];
    }

    editor->length -= 1;
}

void undo(TextEditor *editor) {
  // Implement the undo operation
}

void redo(TextEditor *editor) {
  // Optional for the bonus exercise
}

void destroyTextEditor(TextEditor *editor) {
  // Don't forget to free!
}

void printText(TextEditor *editor) {
  // Print the text
  if (editor->length == 0) {
      printf("EMPTY");
      return;
  }

  for (int i = 0; i < editor->length; i++) {
      printf("%c", editor->text[i]);
  }
}

int main(void) {
  TextEditor *editor = createTextEditor();
  char command;
  int pos;
  char character;

  while(1) {
    scanf(" %c", &command);
    switch (command) {
    case 'i':
      scanf("%d %c", &pos, &character);
      insertCharacter(editor, pos, character);
      break;
    case 'd':
      scanf("%d", &pos);
      deleteCharacter(editor, pos);
      break;
    case 'u':
      undo(editor);
      break;
    case 'r':
      redo(editor);
      break;
    case 'q':
      printText(editor);
      destroyTextEditor(editor);
      return EXIT_SUCCESS;
    default:
      printf("Unknown command.\n");
      break;
    }
  }
}
