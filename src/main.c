#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("ERROR: Did not provide input file as argument. Exiting.\n");
        exit(1);
    }
    const char * input = argv[1];
    printf("%s\n", input);
}
