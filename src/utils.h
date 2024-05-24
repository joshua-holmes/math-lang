#include <stdio.h>

typedef struct FileInfo {
  int line_count;
  int max_line_length;
} FileInfo;

int count_chars_in_line(char *line);
int is_number(char c);
int is_letter(char c);
void to_upper(char *c);
void to_lower(char *c);
int cmp_str(const char *s1, const char *s2);
void copy_str(char *dest, const char *source);
FileInfo read_file_for_info(FILE *file);
