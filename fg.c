#include "header.h"

int foregnd(int argc, char **argv)
{
    if (argc != 1)
    {
        fprintf(stderr, "Error : Wrong arguments.\n");
        return 0;
    }

    int jobn = atoi(argv[0]);

    if (jobn <= 0)
    {
        fprintf(stderr, "Error : Wrong arguments.\n");
        return 0;
    }

    procinfo *proc;
    proc = info_id(procs, jobn);

    if (proc == NULL)
    {
        fprintf(stderr, "Process not found!\n");
        return 0;
    }

    pid_t pid_ch = proc->pid;
    printf("[%d] %s now in foreground.\n", jobn, proc->proc_name);

    FGPID_CH = pid_ch;
    strcpy(FG_CH_NAME, proc->proc_name);

    procs = del_pid(procs, pid_ch);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);

    tcsetpgrp(STDIN_FILENO, pid_ch);

    kill(pid_ch, SIGCONT);

    int w_stop;
    waitpid(pid_ch, &w_stop, WUNTRACED);

    tcsetpgrp(STDIN_FILENO, getpgrp());

    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);

    long id_ch;

    if (WIFSTOPPED(w_stop))
    {
        id_ch = proc_storage(FGPID_CH, FG_CH_NAME);
        printf("[%ld] %s stopped.\n", id_ch, FG_CH_NAME);
    }

    FGPID_CH = -1;
    FG_CH_NAME[0] = '\0';

    if ((WIFEXITED(w_stop) && WEXITSTATUS(w_stop) == EXIT_SUCCESS))
    {
        printf("Foreground Process exited normally!.\n");
    }

    if ((WIFEXITED(w_stop)))
    {
        if (WEXITSTATUS(w_stop) == EXIT_SUCCESS)
        {
            return 1;
        }

        return 0;
    }

    return 0;
}