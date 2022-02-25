#include "header.h"

char *trim_str(char *str, char c)
{
    char *t = str;
    while (*t == c)
        t++;

    long int i = strlen(t) - 1;
    while (t[i] == c)
    {
        t[i] = '\0';
        i--;
    }
    return t;
}

void change_dir(int argc, char **argv)
{
    getcwd(present_dir, 2000);
    if (!argc)
    {
        change("~");
        strcpy(last_acc, present_dir);
        return;
    }
    else if (argc >= 2)
    {
        fprintf(stderr, "Error in changing directory: Invalid arguments\n");
        return;
    }
    else
    {
        if (!strcmp(argv[0], "-"))
        {
            if (!strcmp(last_acc, ""))
            {
                fprintf(stderr, "Error : OLD PWD not set.");
                return;
            }
            change_last();
            // return;
        }
        else
        {
            char *tmp = trim_str(argv[0], '\"');
            tmp = trim_str(tmp, '\'');
            change(tmp);
        }
    }
    strcpy(last_acc, present_dir);
}

int change(char *path)
{
    char *final;
    final = (char *)malloc(sizeof(char) * MAX_LEN);

    if (strcmp(path, "~") == 0 || (strcmp(path, "") == 0))
        strcpy(final, home_dir);
    else
        strcpy(final, path);

    int check = chdir(final);
    if (check == -1)
    {
        perror("Error in changing directory");
        return 0;
    }
    return 1;
}

int change_last()
{
    char *final;
    final = (char *)malloc(sizeof(char) * MAX_LEN);
    final = relative_pwd(last_acc);

    if (!strcmp(final, "~"))
    {
        int check = chdir(home_dir);
        if (check == -1)
        {
            perror("Error in changing directory");
            return 0;
        }
        printf("%s\n", home_dir);
        return 1;
    }

    int check = chdir(final);
    if (check == -1)
    {
        perror("Error in changing directory");
        return 0;
    }
    printf("%s\n", final);

    return 1;
}