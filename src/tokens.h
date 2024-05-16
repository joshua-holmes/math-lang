typedef struct Token {
  int type;
  char value[21]; // null-terminated string
} Token;
enum TokenType {
  COMMAND,
  NAME,
  NUMBER,
};
int count_tokens(char *line);
void tokenize_line(Token *tokens, int token_count, char *line);
