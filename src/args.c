#include <stdio.h>
#include <stdlib.h>

#include "./utils.h"

typedef struct Options {
  char *input_f;
  char *output_f;
  int assemble_and_link; // bool
} Options;

void print_help() {
  printf("Usage: mang [options] filename\n");
  printf("Options:\n");
  printf("\t-o --output: If --no-asm is not set, this is the name of the compiled executable.\n");
  printf("\t--no-asm: When this option is present, -o is ignored. The program does not link or assemble. The output is an assembly file. Primarily used for debugging purposes.\n");
  printf("\t-h --help: Prints this help message.\n");
  printf("If no options are given and only the input filename is given, the program will compile, assemble, link, then produce an executable called \"out\"\n");
}

Options parse_args(int argc, char **argv) {
  Options options;
  options.assemble_and_link = 1;
  options.output_f = "out";
  options.input_f = 0;

  for (int i = 1; i < argc; i++) {
    char *a = argv[i];
    if (cmp_str(a, "-o") || cmp_str(a, "--output")) {
      if (i + 1 >= argc) {
        printf("ERROR: \"--output\" option needs a value after it.\n");
        print_help();
        exit(1);
      }
      options.output_f = argv[++i];
    } else if (cmp_str(a, "--no-asm")) {
      options.assemble_and_link = 0;
    } else if (cmp_str(a, "-h") || cmp_str(a, "--help")) {
      print_help();
      exit(0);
    } else if (a[0] == '-') {
      printf("ERROR: Unknown option \"%s\"\n", a);
      print_help();
      exit(1);
    } else {
      options.input_f = a;
    }
  }

  return options;
}

void validate_args(Options *options) {
  if (options->input_f == 0) {
    printf("ERROR: No input file given.\n");
    print_help();
    exit(1);
  } else if (options->assemble_and_link && (system("which nasm > /dev/null") || system("which ld > /dev/null"))) {
    printf("\nERROR: When assembling and linking is enabled, both the `nasm` and `ld` programs must be installed and added to path.\n");
    printf("If you want to disable assembling and linking, pass the --no-asm flag to mang when compiling.\n");
    exit(1);
  }
}

Options handle_args(int argc, char **argv) {
  Options options = parse_args(argc, argv);
  validate_args(&options);
  return options;
};
