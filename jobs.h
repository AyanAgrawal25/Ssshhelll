#ifndef __JOBS
#define __JOBS

typedef struct x
{
    pid_t pid;
    char proc_name[2000];
    int id;
    char status;
} sort_proc;

void jobs(int argc, char **argv);
int procjobs(sort_proc sorting[], pnode *p);
void sortprocesses(sort_proc sorting[], int f);
#endif
