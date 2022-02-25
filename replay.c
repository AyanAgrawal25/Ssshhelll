#include "header.h"

int min(int x, int y)
{
    if (x < y)
        return x;
    else
        return y;
}

void replay(char *command, int interval, int period)
{
    int f = fork();
    if (f == 0)
    {
        int curr = 0;
        while (curr < period)
        {
            int slp = min(period - curr, interval);
            sleep(slp);

            char *cpy = (char *)calloc(1, 1000);
            strcat(cpy, command);
            tokenize(cpy);
            curr += slp;
        }
        exit(0);
    }
}

void replay_func(int argc, char **args)
{
    if (argc <= 5)
    {
        fprintf(stderr, "Error : Check arguments!\n");
        return;
    }
    char *command = (char *)calloc(1, 1000);
    int interval = -1;
    int period = -1;

    int needs[3] = {0, 0, 0};
    for (int i = 0; args[i] != NULL;)
    {
        int f = 0;
        if (!strcmp(args[i], "-command"))
        {
            needs[0] = 1;
            f = 1;
        }
        if (!strcmp(args[i], "-interval"))
        {
            needs[0] = 0;
            needs[1] = 1;
            f = 1;
        }
        if (!strcmp(args[i], "-period"))
        {
            needs[0] = 0;
            needs[2] = 1;
            f = 1;
        }
        if (f == 1)
        {
            i++;
            continue;
        }
        if (needs[0])
        {
            strcat(command, args[i]);
            strcat(command, " ");
        }
        if (needs[1])
        {
            interval = atoi(args[i]);
            needs[1] = 0;
        }
        if (needs[2])
        {
            period = atoi(args[i]);
            needs[2] = 0;
        }
        ++i;
    }

    if (!command[0] || interval == -1 || period == -1)
    {
        fprintf(stderr, "Error in arguments!\n");
        return;
    }

    replay(command, interval, period);
}