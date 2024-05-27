#include "./string.h"
#include "./utils.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Assembly {
  DynStr bss;
  DynStr data;
  DynStr text;
  uint var_count;
} Assembly;

typedef enum Section {
  ASM_BSS,
  ASM_DATA,
  ASM_TEXT,
} Section;

// when dynamically creating asm var names, define length here
static const int ASM_VAR_LENGTH = 10;

void asm_add_line(Assembly *assembly, Section section, const char *line) {
  int length = 0;
  while (line[length++] != '\0')
    ;
  char *fmt = section == ASM_TEXT ? "        %s\n" : "    %s\n";
  int mod_length = snprintf(NULL, 0, fmt, line);
  char mod_line[mod_length];
  sprintf(mod_line, fmt, line);

  switch (section) {
  case ASM_BSS:
    str_append(&assembly->bss, mod_line);
    break;
  case ASM_DATA:
    str_append(&assembly->data, mod_line);
    break;
  case ASM_TEXT:
    str_append(&assembly->text, mod_line);
    break;
  default:
    printf("ERROR: ASM section \"%d\" does not exist. Compiler error.",
           section);
    exit(1);
  }
}

Assembly new_asm() {
  Assembly assembly;
  assembly.var_count = 0;

  DynStr bss = new_str();
  str_append(&bss, "section .bss\n");
  assembly.bss = bss;

  DynStr data = new_str();
  str_append(&data, "section .data\n");
  assembly.data = data;

  DynStr text = new_str();
  str_append(&text, "section .text\n    global _start\n    _start:\n");
  assembly.text = text;

  return assembly;
}

void asm_create_unique_var_name(Assembly *assembly, char str[ASM_VAR_LENGTH]) {
  sprintf(str, "%x", ++assembly->var_count);

  // ensure string is null terminated
  str[ASM_VAR_LENGTH - 1] = '\0';

  // get length
  int length = 0;
  while (str[length++] != '\0')
    ;

  char str_buf[ASM_VAR_LENGTH];
  copy_str(str_buf, str);
  int len_diff = ASM_VAR_LENGTH - length;
  for (int i = 0; i < ASM_VAR_LENGTH; i++) {
    int adj_i = i - len_diff;
    if (i == 0) {
      str[i] = 'v'; // start vars with this
    } else if (adj_i < 0) {
      str[i] = '0';
    } else {
      str[i] = str_buf[adj_i];
    }
  }
}

void asm_print_var(Assembly *assembly, int value) {
  // insert data in data section
  char var_name[ASM_VAR_LENGTH];
  asm_create_unique_var_name(assembly, var_name);

  char *data_1_formatting = "%s: db \"%d\", 10";
  int data_1_length = snprintf(NULL, 0, data_1_formatting, var_name, value);
  char data_1_line[data_1_length];
  sprintf(data_1_line, data_1_formatting, var_name, value);
  asm_add_line(assembly, ASM_DATA, data_1_line);

  char *data_2_formatting = "%s_len: equ $-%s";
  int data_2_length = snprintf(NULL, 0, data_2_formatting, var_name, var_name);
  char data_2_line[data_2_length];
  sprintf(data_2_line, data_2_formatting, var_name, var_name);
  asm_add_line(assembly, ASM_DATA, data_2_line);

  // insert data in text section
  asm_add_line(assembly, ASM_TEXT, "mov rax,1");
  asm_add_line(assembly, ASM_TEXT, "mov rdi,1");

  char *data_3_formatting = "mov rsi,%s";
  int data_3_length = snprintf(NULL, 0, data_3_formatting, var_name);
  char data_3_line[data_3_length];
  sprintf(data_3_line, data_3_formatting, var_name, value);
  asm_add_line(assembly, ASM_TEXT, data_3_line);

  char *data_4_formatting = "mov rdx,%s_len\n";
  int data_4_length = snprintf(NULL, 0, data_4_formatting, var_name);
  char data_4_line[data_4_length];
  sprintf(data_4_line, data_4_formatting, var_name);
  asm_add_line(assembly, ASM_TEXT, data_4_line);

  asm_add_line(assembly, ASM_TEXT, "syscall\n");
}

void write_to_assembly(Assembly *assembly, const char *output_fname) {
  // wrap up the assembly program
  asm_add_line(assembly, ASM_TEXT, "; end program");
  asm_add_line(assembly, ASM_TEXT, "mov rax,60");
  asm_add_line(assembly, ASM_TEXT, "mov rdi,0");
  asm_add_line(assembly, ASM_TEXT, "syscall");

  FILE *file = fopen(output_fname, "w");
  fprintf(file, "%s", assembly->bss.value);
  fprintf(file, "\n");
  fprintf(file, "%s", assembly->data.value);
  fprintf(file, "\n");
  fprintf(file, "%s", assembly->text.value);
  fprintf(file, "\n");
  fclose(file);
}

void asm_free(Assembly assembly) {
  str_free(&assembly.bss);
  str_free(&assembly.data);
  str_free(&assembly.text);
}
