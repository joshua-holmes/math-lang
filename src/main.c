#include "./compile.h"
#include "./hashmap.h"
#include "./args.h"
#include "./utils.h"
#include <stdio.h>
#include <stdlib.h>

const char *ASM_OUT = "out.asm";
const char *OBJ_OUT = "out.o";

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
    char *asm_command_fmt = "nasm -f elf64 -o %s %s";
    int asm_command_len = snprintf(NULL, 0, asm_command_fmt, OBJ_OUT, ASM_OUT);
    char asm_command[asm_command_len];
    sprintf(asm_command, asm_command_fmt, OBJ_OUT, ASM_OUT);
    system(asm_command);
    remove(ASM_OUT);

    // link
    char *lnk_command_fmt = "ld -o %s %s";
    int lnk_command_len = snprintf(NULL, 0, lnk_command_fmt, options.output_f, OBJ_OUT);
    char lnk_command[lnk_command_len];
    sprintf(lnk_command, lnk_command_fmt, options.output_f, OBJ_OUT);
    system(lnk_command);
    remove(OBJ_OUT);
  }

  fclose(file);
}
