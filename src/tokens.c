#include "./utils.h"
#include <stdio.h>

enum TokenType {
  COMMAND,
  NAME,
  NUMBER,
};
typedef struct Token {
  int type;
  char value[21]; // null-terminated string
} Token;

// assumes line is terminated by `\n` then `\0` in that order
int count_tokens(char *line) {
  int space_count = 0;
  int i = 0;
  char pre_c = '\0';
  while (1) {
    char cur_c = line[i];
    if (cur_c == ' ' && pre_c != ' ' && pre_c != '\0') {
      space_count += 1;
    } else if (cur_c == '\n' && pre_c == ' ') {
      space_count -= 1;
    } else if (cur_c == '\0') {
      break;
    }
    pre_c = cur_c;
    i++;
  }
  return space_count + 1;
}

// assumes line is terminated by `\n` then `\0` in that order
void tokenize_line(Token *tokens, int token_count, char *line) {
  int line_count = count_chars_in_line(line);
  int j = 0;
  for (int i = 0; i < token_count; i++) {
    int token_len;
    int is_word = 0;
    int start;
    int end;

    while (!is_letter(line[j]) && !is_number(line[j]))
      j++;

    start = j;
    while (is_letter(line[j]) || is_number(line[j])) {
      is_word = is_letter(line[j]) || is_word;
      j++;
    }
    end = j; // `end` is exclusive

    Token new_token;
    token_len = end - start + 1; // + 1 so it ends with `\0`
    if (token_len > 21) {
      printf("ERROR: Token cannot be longer than 20 characters");
    }
    int tv_i = 0; // token_val index
    for (int k = start; k < end; k++) {
      new_token.value[tv_i] = line[k];
      tv_i++;
    }
    new_token.value[tv_i] = '\0';

    if (is_word) {
      if (cmp_str(new_token.value, "make") ||
          cmp_str(new_token.value, "print") ||
          cmp_str(new_token.value, "add") || cmp_str(new_token.value, "sub")) {
        new_token.type = COMMAND;
      } else {
        new_token.type = NAME;
      }
    } else {
      new_token.type = NUMBER;
    }

    tokens[i] = new_token;
  }
}
