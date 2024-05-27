#include <stdlib.h>

int DEFAULT_CAPACITY = 6;
typedef struct DynStr {
  char *value;
  int capacity;
  int length;
} DynStr;

DynStr new_str() {
  DynStr s;
  s.value = calloc(DEFAULT_CAPACITY, sizeof(char));
  s.capacity = DEFAULT_CAPACITY;
  s.length = 1;
  return s;
};

void str_append(DynStr *dyn_str, char *str) {
  int length = 0;
  while (str[length++] != '\0')
    ;

  // reallocate
  if (length + dyn_str->length > dyn_str->capacity) {
    int new_cap = length + dyn_str->capacity * 2;
    char *new_value = calloc(new_cap, sizeof(char));
    for (int i = 0; i < dyn_str->length; i++) {
      new_value[i] = dyn_str->value[i];
    }
    free(dyn_str->value);
    dyn_str->value = new_value;
    dyn_str->capacity = new_cap;
  }

  for (int i = 0; i < length; i++) {
    dyn_str->value[i + dyn_str->length - 1] = str[i];
  }
  dyn_str->length += length - 1;
}

void str_free(DynStr *dyn_str) { free(dyn_str->value); }
