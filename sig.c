#include "header.h"

int sig(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Error :Wrong arguments.\n");
        return 0;
    }
    int jobn = atoi(argv[0]);
    int sign = atoi(argv[0]);

    if (jobn <= 0 || sign <= 0)
    {
        fprintf(stderr, "Error: Give valid argument\n");
        return 0;
    }

    procinfo *p = info_id(procs, jobn);

    if (p == NULL)
    {
        fprintf(stderr, "Process not found!\n");
        return 0;
    }

    if (kill(p->pid, sign) == -1)
    {
        perror("Error sending signal");
        return 0;
    }
    return 1;
}
