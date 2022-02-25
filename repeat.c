#include "header.h"

void repeat_cmds(int argc, char **argv)
{
    int num_rep = atoi(argv[0]);

    if (num_rep == 0)
    {
        fprintf(stderr, "Check the argument for repeating command!\n");
    }

    char **new_argv = (char **)malloc(sizeof(char *) * (argc + 5));
    char *new_cmd = (char *)malloc(sizeof(char) * MAX_LEN);
    new_cmd = argv[1];

    int new_argc = 0;
    for (int i = 2; i < argc; i++)
    {
        new_argv[new_argc] = argv[i];
        new_argc++;
    }
    new_argv[new_argc] = NULL;

    for (int j = 0; j < num_rep; j++)
    {
        if (!strcmp(new_cmd, "echo"))
            go_echo(new_argc, new_argv);
        else if (!strcmp(new_cmd, "cd"))
            change_dir(new_argc, new_argv);
        else if (!strcmp(new_cmd, "pwd"))
            pwd_func(new_argc, new_argv);
        else if (!strcmp(new_cmd, "ls"))
            ls_cmd(new_argc, new_argv);
        else if (!strcmp(new_cmd, "pinfo"))
            func_pinfo(new_argc, new_argv);
        else
            ext_funcs(new_cmd, new_argc, new_argv);
    }

    // free(new_argv);
    // free(new_cmd);
}