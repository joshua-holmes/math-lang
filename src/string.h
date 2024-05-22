typedef struct DynStr {
  char *value;
  int capacity;
  int length;
} DynStr;

DynStr new_str();
void str_append(DynStr *dyn_str, char *str);
void str_free(DynStr *dyn_str);
