#include "./compile.h"
#include "./hashmap.h"
#include "./args.h"
#include "./utils.h"
#include <stdio.h>
#include <stdlib.h>

const char *ASM_OUT = "out.asm";

int main(int argc, char **argv) {
  // get input options
  Options options = handle_args(argc, argv);

  const char *input_fname = options.input_f;

  // open file
  FILE *file = fopen(input_fname, "r");
  if (file == NULL) {
    printf("ERROR: Failed to open file - %s\n", input_fname);
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
  write_to_assembly(&assembly, ASM_OUT);
  asm_free(assembly);

  if (options.assemble_and_link) {
    // assemble
    char *command_fmt = "nasm -f elf64 %s";
    int command_len = snprintf(NULL, 0, "nasm -f elf64 %s", ASM_OUT);
    char command[command_len];
    sprintf(command, "nasm -f elf64 %s", ASM_OUT);
    system(command);

    // remove assembly
  }

  fclose(file);
}
