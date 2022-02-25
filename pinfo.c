#include "header.h"

void func_pinfo(int argc, char **argv)
{
    if (argc > 1 || argc < 0)
    {
        fprintf(stderr, "Error in pinfo : Check arguments\n");
        return;
    }
    else if (!argc)
    {
        proc_info(-1);
        return;
    }
    int pid = atoi(argv[0]);
    if (argc && pid < 0)
    {
        fprintf(stderr, "Error in pinfo : Check arguments\n");
        return;
    }
    proc_info(pid);
}

int proc_info(int pid)
{
    if (pid < 0)
        pid = getpid();

    char *stat_file_loc;
    stat_file_loc = (char *)malloc(100);
    sprintf(stat_file_loc, "/proc/%d/stat", pid);

    FILE *stat_file = fopen(stat_file_loc, "r");

    if (stat_file == NULL)
    {
        perror("Error finding process");
        return 0;
    }

    long long int p_memory;
    int storepid;
    char *tmp = (char *)malloc(MAX_LEN);
    char *proc_path = (char *)malloc(MAX_LEN);

    char r_s = '-';
    int par_grp;
    int set_grp;

    fscanf(stat_file,
           "%d %*s %c %*s %d %*s %*s %d %*s %*s %*s %*s %*s %*s %*s %*s %*s "
           "%*s %*s %*s %*s %*s %lld",
           &storepid, &r_s, &par_grp, &set_grp, &p_memory);

    char fg_or_bg;

    if (par_grp == set_grp)
        fg_or_bg = '+';
    else
        fg_or_bg = ' ';

    printf("pid -- %d\n", pid);
    printf("Process Status -- %c%c\n", r_s, fg_or_bg);
    printf("Memory -- %lld {Virtual Memory}\n", p_memory);
    fclose(stat_file);

    char *execpath = (char *)malloc(1000);
    sprintf(execpath, "/proc/%d/exe", pid);

    long int exec_size = readlink(execpath, tmp, MAX_LEN);
    if (exec_size < 0)
    {
        perror("Error finding process");
        return 0;
    }

    tmp[exec_size] = '\0';
    proc_path = relative_pwd(tmp);

    printf("Executable Path -- %s\n", proc_path);

    free(proc_path);
    free(tmp);
    free(execpath);
    free(stat_file_loc);

    return 1;
}
