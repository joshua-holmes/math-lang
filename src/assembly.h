#include "./string.h"

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

void asm_add_line(Assembly *assembly, Section section, const char *line);
Assembly new_asm();
void asm_free(Assembly assembly);
