#include "header.h"

void backgnd(int argc, char **argv)
{
    if (argc != 1)
    {
        fprintf(stderr, "Error: Wrong Arguments\n");
        return;
    }

    int jobn = atoi(argv[0]);
    if (jobn <= 0)
    {
        fprintf(stderr, "Error: Wrong Job No.\n");
        return;
    }

    procinfo *p = info_id(procs, jobn);

    if (p == NULL)
    {
        fprintf(stderr, "Process not found!\n");
        return;
    }

    int ch = p->pid;

    if (kill(ch, 18) < 0)
    {
        perror("Error running it in background\n");
        return;
    }

    printf("[%d] %s sent to background\n", jobn, p->proc_name);
    return;
}