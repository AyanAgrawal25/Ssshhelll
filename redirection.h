#ifndef __REDIREC
#define __REDIREC

typedef struct
{
    char ipf[8192];
    char opf[8192];
    int input;
    int output;
    int append;
} redirect_stats;

typedef struct
{
    int stdincpy;
    int stdoutcpy;
    int in_file;
    int out_file;
} redirect_stats1;

redirect_stats1 initialize_redirec(const redirect_stats r);
void finish_redirec(const redirect_stats r, const redirect_stats1 r1);

#endif
