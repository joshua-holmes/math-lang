#include "./hashmap.h"
#include "./tokens.h"
#include "./assembly.h"
#include "./utils.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum Status {
  OK,
  OUT_OF_TOKENS,
} Status;
typedef struct Resolution {
  int value;
  Status status;
} Resolution;


Resolution resolve_tokens(HashMap *name_map, TokenizedLine t_line, int *start) {
  Resolution res;
  res.value = 0;
  if (*start >= t_line.length) {
    res.status = OUT_OF_TOKENS;
    return res;
  }

  Token t = t_line.tokens[*start];
  Resolution res_a;
  Resolution res_b;
  switch (t.type) {
  case COMMAND:
    *start += 1;
    if (*start >= t_line.length) {
      printf("ERROR: \"make\" command needs a name after it and value after "
             "the name. Missing name.\n");
      exit(1);
    }
    if (cmp_str(t.value, "make")) {
      Token name_token = t_line.tokens[*start];
      if (name_token.type != NAME) {
        printf("ERROR: Name of variable cannot start with number or be a "
               "reserved keyword.\n\"%s\" is an invalid variable name.\n",
               name_token.value);
        exit(1);
      }
      *start += 1;
      res_a = resolve_tokens(name_map, t_line, start);
      if (res_a.status == OUT_OF_TOKENS) {
        printf("ERROR: \"make\" command needs a name after it and value after "
               "the name. Missing value.\n");
        exit(1);
      }
      hm_set(name_map, name_token.value, res_a.value);
    } else if (cmp_str(t.value, "print")) {
      res_a = resolve_tokens(name_map, t_line, start);
      if (res_a.status == OUT_OF_TOKENS) {
        printf("ERROR: \"print\" command needs a name after it and value after "
               "the name. Missing value.\n");
        exit(1);
      }
    }
    break;
  case OPERAND:
    *start += 1;
    res_a = resolve_tokens(name_map, t_line, start);
    res_b = resolve_tokens(name_map, t_line, start);
    if (res_a.status == OUT_OF_TOKENS || res_b.status == OUT_OF_TOKENS) {
      printf("ERROR: Operands need 2 expressions after them.\n\nFor example, "
             "`add 8` is invalid. It needs something to add 8 to.\n");
      exit(1);
    }
    if (cmp_str(t.value, "add")) {
      res.value = res_a.value + res_b.value;
    } else if (cmp_str(t.value, "sub")) {
      res.value = res_a.value - res_b.value;
    } else {
      printf("ERROR: Unknown operand -> \"%s\"\nThis is a compiler issue.\n",
             t.value);
      exit(1);
    }
    break;
  case NAME: // for getting name only, not setting
    res.value = hm_get(name_map, t.value);
    *start += 1;
    break;
  case NUMBER:
    res.value = atoi(t.value);
    *start += 1;
    break;
  default:
    printf("ERROR: Unknown type \"%d\" with value \"%s\"\nThis is a compiler "
           "issue\n",
           t.type, t.value);
    exit(1);
  }

  return res;
}

void compile_tokens(TokenizedLine *tokenized_lines, int line_count) {
  HashMap name_map = new_hash_map(500);
  Assembly assembly = new_asm();
  for (int i = 0; i < line_count; i++) {
    TokenizedLine t_line = tokenized_lines[i];
    int start_i = 0;
    resolve_tokens(&name_map, t_line, &start_i);
  }
  asm_free(assembly);
  hm_free(name_map);
}
