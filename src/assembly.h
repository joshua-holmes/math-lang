#include <stdlib.h>
#include "./string.h"

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

static const int ASM_VAR_LENGTH = 10;

void asm_add_line(Assembly *assembly, Section section, const char *line);
Assembly new_asm();
void asm_free(Assembly assembly);
void asm_create_unique_var_name(Assembly *assembly, char str[ASM_VAR_LENGTH]);
void asm_print_var(Assembly *assembly, int value);
void write_to_assembly(Assembly *assembly, const char *fout_name);
