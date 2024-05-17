#include "./tokens.h"
#include "./utils.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  // get input file name
  if (argc < 2) {
    printf("ERROR: Did not provide input file as argument. Exiting.\n");
    exit(1);
  }
  const char *input = argv[1];

  // open file
  FILE *file = fopen(input, "r");
  if (file == NULL) {
    printf("ERROR: Failed to open file.\n");
    exit(1);
  }

  // get size of largest line
  // starting at 2 to account for `\n` and `\0`
  int cur_line_size = 2;
  int max_line_size = 2;
  int line_count = 1;
  int is_last_line_empty = 1;
  while (!feof(file)) {
    char cur_c = fgetc(file);
    if (cur_c == '\n') {
      cur_line_size = 2;
      line_count += 1;
      is_last_line_empty = 1;
    } else {
      cur_line_size += 1;
      if (cur_line_size > max_line_size) {
        max_line_size = cur_line_size;
      }
      if (is_letter(cur_c)) {
        is_last_line_empty = 0;
      }
    }
  }
  if (is_last_line_empty) {
    line_count -= 1;
  }
  fseek(file, 0, SEEK_SET);

  // read a line at a time and tokenize
  Token tokenized_lines[line_count][max_line_size];
  for (int i = 0; i < line_count; i++) {
    char line[max_line_size];
    fgets(line, max_line_size, file);
    to_lower(line);
    int token_count = count_tokens(line);
    tokenize_line(tokenized_lines[i], token_count, line);
  }

  fclose(file);
}
