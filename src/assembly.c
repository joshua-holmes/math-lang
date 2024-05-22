#include "./string.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Assembly {
  DynStr bss;
  DynStr data;
  DynStr text;
} Assembly;

typedef enum Section {
  ASM_BSS,
  ASM_DATA,
  ASM_TEXT,
} Section;

void asm_add_line(Assembly *assembly, Section section, const char *line) {
  int length = 0;
  while (line[length++] != '\0');
  int mod_length = length + 5; // auto add 4 spaces before line and a '\n'
  char mod_line[mod_length];
  for (int i = 0; i < mod_length; i++) {
    if (i < 4) {
      mod_line[i] = ' ';
    } else if (i < mod_length - 3) {
      mod_line[i] = line[i - 4];
    } else if (i < mod_length - 1) {
      mod_line[i] = '\n';
    } else {
      mod_line[i] = '\0';
    }
  }

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
