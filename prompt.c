#include "header.h"

int nameplate() //prompt function
{
    if (user_name == NULL)
    {
        perror("login error:");
        return -1;
    }

    char *absolute_path = getcwd(NULL, 0); // string is malloc-ed and stores cwd
    path = relative_pwd(absolute_path);

    printf("<" PURPLE "%s@%s" DEFAULT ":" CYAN_BOLD "%s" DEFAULT "> ", user_name, host_name, path);

    free(absolute_path);
    free(path);
    return 0;
}