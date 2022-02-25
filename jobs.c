#include "header.h"

void sortprocesses(sort_proc sorting[], int n)
{
    // bubble sorting
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (strcmp(sorting[j].proc_name, sorting[i].proc_name) < 0)
            {
                sort_proc temp;
                temp = sorting[j];
                sorting[j] = sorting[i];
                sorting[i] = temp;
            }
        }
    }
}

int procjobs(sort_proc sorting[], pnode *p)
{
    int i = 0;
    for (; p != NULL;)
    {
        int pid = p->data.pid;
        if (!pid)
            continue;

        strcpy(sorting[i].proc_name, p->data.proc_name);
        sorting[i].pid = p->data.pid;
        i++;
        p = p->next;
    }
    return i;
}

void jobs(int argc, char **argv)
{
    if (argc < 0 || argc > 2)
    {
        fprintf(stderr, "Error: Wrong arguments");
        return;
    }
    int pass = 0;

    int r_flag = 0;
    int s_flag = 0;

    if (argc == 0)
    {
        pass = 1;
    }

    if (argc == 1)
    {
        if (argv[0][1] == 'r')
        {
            r_flag = 1;
        }
        if (argv[0][2] != '\0')
        {
            if (argv[0][2] == 's')
            {
                s_flag = 1;
            }
        }

        if (argv[0][1] == 's')
        {
            s_flag = 1;
        }
        if (argv[0][2] != '\0')
        {
            if (argv[0][2] == 'r')
            {
                r_flag = 1;
            }
        }
    }

    if (argc == 2)
    {
        if (argv[0][1] == 'r' || argv[1][1] == 'r')
            r_flag = 1;
        if (argv[0][1] == 's' || argv[1][1] == 's')
            s_flag = 1;
    }

    pnode *p = procs;
    sort_proc sorting[1024];
    char state_strS[50];
    char state_strR[50];

    long i = 0;
    for (; p != NULL;)
    {
        char process_state;
        sorting[i].id = i + 1;

        char *stat_file_loc;
        stat_file_loc = (char *)malloc(100);
        sprintf(stat_file_loc, "/proc/%d/stat", p->data.pid);

        FILE *stat_file = fopen(stat_file_loc, "r");

        if (stat_file == NULL)
        {
            perror("Error finding process");
            process_state = '\0';
        }

        fscanf(stat_file,
               "%*s %*s %c %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s "
               "%*s %*s %*s %*s %*s %*s",
               &process_state);

        if (process_state == '\0')
        {
            fprintf(stderr, "Error finding process!");
            return;
        }
        else if (process_state == 'T')
            strcpy(state_strS, "Stopped");
        else
            strcpy(state_strR, "Running");

        sorting[i].status = process_state;

        p = p->next;
        i++;
    }

    pnode *x = procs;
    int num = procjobs(sorting, x);
    sortprocesses(sorting, num);

    if (pass == 1)
    {
        for (long int i = 0; i < num; i++)
        {
            if (sorting[i].status == 'T')
            {
                printf("[%d] %s %s [%d]\n", sorting[i].id, state_strS, sorting[i].proc_name, sorting[i].pid);
            }
            if (sorting[i].status == 'S')
            {
                printf("[%d] %s %s [%d]\n", sorting[i].id, state_strR, sorting[i].proc_name, sorting[i].pid);
            }
        }
        return;
    }

    if (pass == 0)
    {
        for (long int i = 0; i < num; i++)
        {
            if (s_flag && sorting[i].status == 'T')
            {
                printf("[%d] %s %s [%d]\n", sorting[i].id, state_strS, sorting[i].proc_name, sorting[i].pid);
            }
            if (r_flag && sorting[i].status == 'S')
            {
                printf("[%d] %s %s [%d]\n", sorting[i].id, state_strR, sorting[i].proc_name, sorting[i].pid);
            }
        }
    }

    return;
}