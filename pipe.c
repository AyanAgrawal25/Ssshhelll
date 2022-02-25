#include "header.h"

int **p;
char *cmd;
int pipes;

void print_fault()
{
    perror("Error piping");
    fprintf(stderr, "Exiting...\n");
    bye_bye();
}

void error_func()
{
    perror("Error piping");

    free(cmd);
    int k = 0;
    while (k < pipes)
        free(p[k++]);
    free(p);
}

void piping(char arr[])
{
    if (!arr)
        return;

    pipes = 0;
    int i = 0;

    while (i < strlen(arr))
    {
        if (arr[i] == '|')
            pipes++;

        i++;
    }

    if (pipes == 0)
    {
        command_to_exec(arr);
        return;
    }

    char *x;
    char *nxt = strtok_r(arr, "|", &x);

    if (!nxt)
        return;

    cmd = (char *)malloc(strlen(nxt) + 1);

    strcpy(cmd, nxt);

    p = (int **)malloc(sizeof(int *) * pipes);
    int j = 0;
    while (j < pipes)
        p[j++] = (int *)malloc(8);

    int stout_cp = dup(1);

    if (stout_cp < 0)
    {
        error_func();
        return;
    }
    else if (pipe(p[0]) == -1)
    {
        error_func();
        close(stout_cp);
        return;
    }
    else if (dup2(p[0][1], 1) < 0)
    {
        close(p[0][1]);
        close(p[0][0]);
        error_func();
        close(stout_cp);
        return;
    }
    else
    {
        command_to_exec(cmd);
        close(p[0][1]);

        int stin_cp = dup(0);
        if (stin_cp < 0)
            print_fault();

        int z = 0;
        for (; (nxt = strtok_r(NULL, "|", &x)) != NULL;)
        {
            cmd = (char *)realloc(cmd, strlen(nxt) + 1);
            strcpy(cmd,nxt);
            ++z;

            if (z == pipes)
                break;

            if ((pipe(p[z]) < 0) || (dup2(p[z][1], 1) < 0) || (dup2(p[z - 1][0], 0) < 0))
                print_fault();

            command_to_exec(cmd);
            close(p[z][1]);
            close(p[z - 1][0]);
        }

        if ((dup2(stout_cp, STDOUT_FILENO) < 0) || (dup2(p[z - 1][0], 0) < 0))
            print_fault();
        command_to_exec(cmd);

        if (dup2(stin_cp, 0) < 0)
            print_fault();

        close(stin_cp);
        close(stout_cp);
        close(p[z - 1][0]);

        free(cmd);
        int t = 0;
        while (t < pipes)
            free(p[t++]);
        free(p);
    }
}