#include "./compile.h"
#include "./hashmap.h"
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
  FileInfo f_info = read_file_for_info(file);

  // read a line at a time and tokenize
  TokenizedLine tokenized_lines[f_info.line_count];
  tokenize_lines(tokenized_lines, file, f_info.line_count,
                 f_info.max_line_length);

  // build assembly file from tokens
  Assembly assembly = new_asm();
  compile_tokens(&assembly, tokenized_lines, f_info.line_count);

  // assembly
  asm_free(assembly);

  fclose(file);
}
