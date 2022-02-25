#include "header.h"

void pwd_func(int argc, char **argv)
{
    if (!argc)
    {
        char *x = getcwd(NULL, 0);

        if (x == NULL)
            perror("Error in showing cwd");

        printf("%s\n", x);
        free(x);
    }
    else if (argc)
    {
        if (argv[0][0] == '&')
        {
            char *x = getcwd(NULL, 0);

            if (x == NULL)
                perror("Error in showing cwd");

            printf("%s\n", x);
            free(x);
        }
        else
            fprintf(stderr, "Error in showing cwd : check arguments\n");
    }
    else
        fprintf(stderr, "Error in showing cwd : check arguments\n");
}