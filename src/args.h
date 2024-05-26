typedef struct Options {
  char *input_f;
  char *output_f;
  int assemble_and_link; // bool
} Options;
Options handle_args(int argc, char **argv);
