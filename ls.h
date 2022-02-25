#ifndef _LS
#define _LS

typedef struct data
{
    char *permissions;
    char *user;
    char *group;
    char *time;
    char *name;
    blkcnt_t blocks;
    size_t size;
    int nlink;
} file_data;

void ls_cmd(int argc, char **argv);
int ls_func(char path[], int af, int lf);
int selector_func(const struct dirent *dir);

#endif
