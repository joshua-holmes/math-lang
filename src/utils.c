#include <stdio.h>

typedef struct FileInfo {
  int line_count;
  int max_line_length;
} FileInfo;

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

void copy_str(char *dest, const char *source) {
  int i = 0;
  while (source[i] != '\0') {
    dest[i] = source[i];
    i++;
  }
  dest[i] = '\0';
}

FileInfo read_file_for_info(FILE *file) {
  // starting at 2 to account for `\n` and `\0`
  int cur_line_size = 2;
  int max_line_length = 2;
  int line_count = 1;
  int is_last_line_empty = 1;
  while (!feof(file)) {
    char cur_c = fgetc(file);
    if (cur_c == '\n') {
      cur_line_size = 2;
      line_count += 1;
      is_last_line_empty = 1;
    } else {
      cur_line_size += 1;
      if (cur_line_size > max_line_length) {
        max_line_length = cur_line_size;
      }
      if (is_letter(cur_c)) {
        is_last_line_empty = 0;
      }
    }
  }
  if (is_last_line_empty) {
    line_count -= 1;
  }
  fseek(file, 0, SEEK_SET);
  FileInfo f_info;
  f_info.line_count = line_count;
  f_info.max_line_length = max_line_length;

  return f_info;
}
