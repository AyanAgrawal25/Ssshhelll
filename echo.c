#include "header.h"

void go_echo(int argc, char **argv)
{
    if (!argc)
    {
        printf("\n");
        return;
    }
    if (!strcmp(argv[argc - 1], "&"))
        argc--;

    for (long int i = 0; i < argc - 1; i++)
        printf("%s ", argv[i]);
    printf("%s\n", argv[argc - 1]);
}