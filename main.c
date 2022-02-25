#include "header.h"

long int ip_buf_len = 0;
long int ip_len = 0;
char *ip_str = NULL;
int exit_status = 0;

int main()
{
    ext_funcs("clear", 0, NULL);
    int rough = welcome();
    if (rough == -1)
    {
        return 0;
    }
    load_history();

    strcpy(last_acc, "");
    while (1)
    {
        free(ip_str);
        ip_buf_len = ip_len = 0;
        ip_str = (char *)malloc(sizeof(char) * MAX_LEN);
        if (nameplate() == -1)
            return 0;
        // fgets(ip_str, MAX_LEN, stdin);

        size_t sz = 0;
        int f = getline(&ip_str, &sz, stdin);

        if (f < 0)
            bye_bye();

        ip_len = strlen(ip_str);
        if (ip_len <= 0)
        {
            free(ip_str);
            break;
        }
        if (ip_str[ip_len - 1] == '\n')
            ip_str[ip_len - 1] = '\0';

        if (!strcmp(ip_str, ""))
        {
            fprintf(stderr, "Hey, Do enter something!\n");
            continue;
        }

        strcpy(hist[hist_cnt % 20], ip_str);
        strcat(hist[hist_cnt % 20], "\n");
        hist_cnt++;
        write_history();

        tokenize(ip_str);
    }
    bye_bye();
}