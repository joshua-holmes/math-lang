#include <stdio.h>

// assumes line is terminated by `\n` then `\0` in that order
// includes `\n` and `\0` in count
int count_chars_in_line(char *line) {
  int i = 0;
  while (line[i] != '\0')
    i++;
  return i + 1;
}

int is_number(char c) {
  if (c <= '9' && c >= '0') {
    return 1;
  } else {
    return 0;
  }
}

int is_letter(char c) {
  if (c <= 'z' && c >= 'A') {
    return 1;
  } else {
    return 0;
  }
}

// assumes terminated by `\0`
void to_upper(char *c) {
  int i = 0;
  while (c[i] != '\0') {
    if (!is_letter(c[i])) {
      i++;
      continue;
    };
    if (c[i] >= 'a') {
      c[i] -= 32;
    }
    i++;
  }
}

// assumes terminated by `\0`
void to_lower(char *c) {
  int i = 0;
  while (c[i] != '\0') {
    if (!is_letter(c[i])) {
      i++;
      continue;
    };
    if (c[i] < 'a') {
      c[i] += 32;
    }
    i++;
  }
}

// assumes both terminated by `\0`
int cmp_str(const char *s1, const char *s2) {
  int i = 0;
  while (s1[i] != '\0' && s2[i] != '\0') {
    if (s1[i] != s2[i])
      return 0;
    i++;
  }
  return s1[i] == s2[i];
}
