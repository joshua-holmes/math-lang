#include <stdio.h>

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
int count_tokens(char *line);
TokenizedLine tokenize_line(int token_count, char *line);
void tokenize_lines(TokenizedLine *tokenized_lines, FILE *file, int line_count, int max_line_size);
void free_tokens(TokenizedLine *tokenized_lines, int line_count);
