#include "./utils.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum TokenType {
  COMMAND,
  OPERAND,
  NAME,
  NUMBER,
} TokenType;
typedef struct Token {
  TokenType type;
  char *value; // null-terminated string
} Token;
typedef struct TokenizedLine {
  Token *tokens;
  int length;
} TokenizedLine;

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

int get_token_type(char *value, int is_word) {
  if (is_word) {
    if (cmp_str(value, "make") || cmp_str(value, "print")) {
      return COMMAND;
    } else if (cmp_str(value, "add") || cmp_str(value, "sub")) {
      return OPERAND;
    }
    return NAME;
  }
  return NUMBER;
}

// assumes line is terminated by `\n` then `\0` in that order
TokenizedLine tokenize_line(int token_count, char *line) {
  int line_count = count_chars_in_line(line);
  int j = 0;
  TokenizedLine tokenized_line;
  tokenized_line.tokens = malloc(token_count * sizeof(Token));
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
    new_token.value = malloc(token_len * sizeof(char));
    int tv_i = 0; // token_val index
    for (int k = start; k < end; k++) {
      new_token.value[tv_i] = line[k];
      tv_i++;
    }
    new_token.value[tv_i] = '\0';

    new_token.type = get_token_type(new_token.value, is_word);

    tokenized_line.tokens[i] = new_token;
  }
  tokenized_line.length = token_count;
  return tokenized_line;
}

void tokenize_lines(TokenizedLine *tokenized_lines, FILE *file, int line_count, int max_line_size) {
  for (int i = 0; i < line_count; i++) {
    char line[max_line_size];
    fgets(line, max_line_size, file);
    to_lower(line);
    int token_count = count_tokens(line);
    tokenized_lines[i] = tokenize_line(token_count, line);
  }
}

void free_tokens(TokenizedLine *tokenized_lines, int line_count) {
  for (int i = 0; i < line_count; i++) {
    TokenizedLine t_line = tokenized_lines[i];
    for (int j = 0; j < t_line.length; j++) {
      Token token = t_line.tokens[j];
      free(token.value);
    }
    free(t_line.tokens);
  }
}
