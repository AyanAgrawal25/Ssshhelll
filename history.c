#include "header.h"

int max(int a, int b)
{
    if (a < b)
        return b;
    else
        return a;
}

void load_history()
{
    strcpy(hist_filename, home_dir);
    strcat(hist_filename, "/history.txt");
    FILE *file = fopen(hist_filename, "r");
    if (file != NULL)
    {
        char line[1024];
        int no = 0;
        while (fgets(line, sizeof(line), file) != NULL)
        {
            if (no == 0)
            {
                hist_cnt = atoi(line);
                no = 1;
            }

            else
            {
                strcpy(hist[no - 1], line);
                no++;
            }
        }

        fclose(file);
    }
    else
        perror("history.txt");
    return;
}

void history_cmd(int argc, char **argv)
{
    if (argc > 0)
    {
        if (!strcmp(argv[argc - 1], "&"))
            argc--;
    }

    if (argc < 0 || argc > 1)
    {
        fprintf(stderr, "Could not show history : Check arguments!");
        return;
    }

    int num;

    if (argc == 0)
        num = 10;

    if (argc == 1)
        num = atoi(argv[0]);

    int count = num;

    for (int i = max(hist_cnt - count, 0); count > 0; i++, count--)
    {
        printf("%s", hist[i % 20]);
        //count++;
    }
}

void write_history()
{
    FILE *file = fopen(hist_filename, "w");
    int n;

    if (hist_cnt < 20)
        n = hist_cnt;
    else
        n = 20;

    fprintf(file, "%d\n", hist_cnt);
    for (int i = 0; i < n; i++)
        fprintf(file, "%s", hist[i]);

    fclose(file);
}