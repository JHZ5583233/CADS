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
  editor->action_history = newStack(TEXT_EDITOR_INITIAL_CAPACITY);
  return editor;
}

void insertCharacter(TextEditor *editor, int pos, char character) {
    // Implement the insert operation
    if (editor->length >= editor->capacity) {
      int new_capacity;
      new_capacity = 2 * editor->capacity;
      editor->capacity = new_capacity;
      editor->text = realloc(editor->text, new_capacity * sizeof(*editor->text));
      assert(editor->text != NULL);
    }

    for (int i = pos; i < editor->length;i++) {
        editor->text[i + 1] = editor->text[i];
    }
    editor->text[pos] = character;
    editor->length += 1;


    EditOperation current_action = {INSERT, character, pos};
    push(current_action, &editor->action_history);
}

void deleteCharacter(TextEditor *editor, int pos) {
  // Implement the delete operation
    char deleted_char;
    deleted_char = editor->text[pos];

    for (int i = pos; i < editor->length - 1; i++) {
        editor->text[i] = editor->text[i + 1];
    }

    editor->length -= 1;

    EditOperation current_action = {DELETE, deleted_char, pos};
    push(current_action, &editor->action_history);
}

void undo(TextEditor *editor) {
  // Implement the undo operation
    if (isEmptyStack(editor->action_history)) {
      return;
    }

    EditOperation last_action;
    last_action = pop(&editor->action_history);

    if (last_action.type == INSERT) {
        deleteCharacter(editor, last_action.position);
    }
    else if (last_action.type == DELETE)
    {
        insertCharacter(editor, last_action.position, last_action.character);
    }
}

void redo(TextEditor *editor) {
  // Optional for the bonus exercise
}

void destroyTextEditor(TextEditor *editor) {
  // Don't forget to free!
    free(editor->text);
    freeStack(editor->action_history);
    free(editor);
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
