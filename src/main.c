#include <stdio.h>
#include <stdlib.h>
#include "./tokens.h"
#include "./utils.h"

int main(int argc, char** argv) {
  // get input file name
  if (argc < 2) {
    printf("ERROR: Did not provide input file as argument. Exiting.\n");
    exit(1);
  }
  const char* input = argv[1];

  // open file
  FILE* file = fopen(input, "r");
  if (file == NULL) {
    printf("ERROR: Failed to open file.\n");
    exit(1);
  }

  // get size of largest line
  // starting at 2 to account for `\n` and `\0`
  int cur_line_size = 2;
  int max_line_size = 2;
  while (!feof(file)) {
    if (fgetc(file) == '\n') {
      cur_line_size = 2;
    } else {
      cur_line_size += 1;
      if (cur_line_size > max_line_size) {
        max_line_size = cur_line_size;
      }
    }
  }
  fseek(file, 0, SEEK_SET);

  // read a line at a time
  while (!feof(file)) {
    char line[max_line_size];
    fgets(line, max_line_size, file);
    to_lower(line);
    int i = 0;

    int token_count = count_tokens(line);
    Token tokens[token_count];
    tokenize_line(tokens, token_count, line);
    for (int i = 0; i < token_count; i++) {
      printf("TOKENS %d, %s\n", tokens[i].type, tokens[i].value);
    }
  }

  fclose(file);
}
