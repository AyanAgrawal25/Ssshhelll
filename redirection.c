#include "header.h"

redirect_stats1 initialize_redirec(const redirect_stats r)
{
    redirect_stats1 st;
    st.in_file = -1;
    st.stdincpy = -1;
    st.stdoutcpy = -1;
    st.out_file = -1;

    if (r.input == 1)
    {
        if (r.ipf[0] == '\0')
        {
            fprintf(stderr, "Error redirecting : Do proper input near '<'.\n");
            return st;
        }

        int f;
        f = open(r.ipf, O_RDONLY);
        if (r.ipf <= 0)
        {
            perror("Error redirecting");
            return st;
        }

        int x = dup(STDIN_FILENO);
        if (x < 0)
        {
            perror("Error redirecting");
            close(f);
            return st;
        }

        int y = dup2(f, STDIN_FILENO);
        if (y < 0)
        {
            perror("Error redirecting");
            close(x);
            close(f);
            return st;
        }

        st.in_file = f;
        st.stdincpy = x;
    }

    if (r.output == 1)
    {
        if (r.opf[0] == '\0')
        {
            fprintf(stderr, "Error redirecting : Do proper input near '<'.\n");
            return st;
        }

        int F;

        if (r.append == 1)
            F = open(r.opf, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else if (r.output && !r.append)
            F = open(r.opf, O_WRONLY | O_CREAT | O_TRUNC, 0644);

        if (F <= 0)
        {
            perror("Error redirecting");
            return st;
        }

        int X = dup(STDOUT_FILENO);
        if (X < 0)
        {
            perror("Error redirecting");
            close(F);
            return st;
        }

        int Y = dup2(F, STDOUT_FILENO);

        if (Y < 0)
        {
            perror("Error redirecting");
            close(X);
            close(F);
            return st;
        }

        st.out_file = F;
        st.stdoutcpy = X;
    }

    return st;
}

void finish_redirec(const redirect_stats r, const redirect_stats1 r1)
{
    if (r.input == 1)
    {
        if ((dup2(r1.stdincpy, STDIN_FILENO) < 0))
        {
            perror("Fatal error");
            fprintf(stderr, "Bye!\n");
            bye_bye();
        }
        close(r1.stdincpy);
        close(r1.in_file);
    }

    if (r.output == 1)
    {
        if ((dup2(r1.stdoutcpy, STDOUT_FILENO) < 0))
        {
            perror("Fatal error");
            fprintf(stderr, "Bye!\n");
            bye_bye();
        }
        close(r1.stdoutcpy);
        close(r1.out_file);
    }
}
