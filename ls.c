#include "header.h"

void ls_cmd(int argc, char **argv)
{
    if (!argc)
    {
        ls_func(".", 0, 0);
        return;
    }
    int af = 0, lf = 0;

    for (int i = 0; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            if (argv[i][1] == 'l' || argv[i][2] == 'l')
                lf = 1;
            if (argv[i][1] == 'a' || argv[i][2] == 'a')
                af = 1;
        }
    }

    int argument_is_dir = 0;

    for (int i = 0; i < argc; i++)
    {
        if (argv[i][0] != '-')
        {
            argument_is_dir = 1;
            ls_func(argv[i], af, lf);
        }
    }
    if (!argument_is_dir)
        ls_func(".", af, lf);
}

int selector_func(const struct dirent *dir)
{
    if (strlen(dir->d_name) && dir->d_name[0] == '.')
        return 0;
    else
        return 1;
}

int ls_func(char path[], int af, int lf)
{
    struct stat st_path;

    if (stat(path, &st_path) == -1)
    {
        perror("Error in listing contents");
        return 0;
    }

    if (S_ISDIR(st_path.st_mode) == 0)
    {
        fprintf(stderr, "Not a directory");
        return 0;
    }

    int file_cnt;
    struct dirent **dir;

    if (af == 1)
    {
        file_cnt = scandir(path, &dir, NULL, alphasort);
        if (file_cnt < 0)
        {
            perror("Error in listing contents");
            free(dir);
            return 0;
        }
    }
    else
    {
        file_cnt = scandir(path, &dir, selector_func, alphasort);
        if (file_cnt < 0)
        {
            perror("Error in listing contents");
            free(dir);
            return 0;
        }
    }

    //for not -l flags
    if (lf == 0)
    {
        int i = 0;
        while (i < file_cnt)
        {
            printf("%s\n", dir[i]->d_name);
            free(dir[i]);
            i++;
        }

        free(dir);
        return 1;
    }

    blkcnt_t num_blocks = 0;

    for (int i = 0; i < file_cnt; i++)
    {
        char *fname = dir[i]->d_name;
        // creating proper file location
        char *fpath = (char *)malloc(sizeof(char) * (strlen(fname) + strlen(path) + 10));
        strcpy(fpath, path);
        strcat(fpath, "/");
        strcat(fpath, fname);

        // retreiving data fopr file

        file_data f;
        if (stat(fpath, &st_path) == -1)
        {
            perror("Error in listing data");
            free(fpath);
            free(dir[i]);
            continue;
        }
        f.user = getpwuid(st_path.st_uid)->pw_name;
        f.group = getgrgid(st_path.st_gid)->gr_name;
        f.size = st_path.st_size;
        f.blocks = st_path.st_blocks;
        f.nlink = st_path.st_nlink;

        f.time = (char *)malloc(sizeof(char) * 26);
        ctime_r(&st_path.st_mtim.tv_sec, f.time);
        f.time += 4;
        f.time[16] = '\0';

        f.permissions = (char *)malloc(sizeof(char) * 11);
        for (int i = 0; i <= 9; i++)
        {
            f.permissions[i] = '-';
        }
        f.permissions[10] = '\0';

        if (S_ISLNK(st_path.st_mode))
            f.permissions[0] = 'l';
        else if (S_ISDIR(st_path.st_mode))
            f.permissions[0] = 'l';

        if (st_path.st_mode & S_IRUSR)
            f.permissions[1] = 'r';
        if (st_path.st_mode & S_IWUSR)
            f.permissions[2] = 'w';
        if (st_path.st_mode & S_IXUSR)
            f.permissions[3] = 'x';
        if (st_path.st_mode & S_IRGRP)
            f.permissions[4] = 'r';
        if (st_path.st_mode & S_IWGRP)
            f.permissions[5] = 'w';
        if (st_path.st_mode & S_IXGRP)
            f.permissions[6] = 'x';
        if (st_path.st_mode & S_IROTH)
            f.permissions[7] = 'r';
        if (st_path.st_mode & S_IWOTH)
            f.permissions[8] = 'w';
        if (st_path.st_mode & S_IXOTH)
            f.permissions[9] = 'x';

        num_blocks = num_blocks + f.blocks;
        f.name = dir[i]->d_name;

        if (f.permissions[0] == 'd')
        {
            printf("%s\t%d\t%s\t%s\t%lu\t%s\t" PURPLE "%s\n" DEFAULT,
                   f.permissions,
                   f.nlink,
                   f.user,
                   f.group,
                   f.size,
                   f.time,
                   f.name);
        }
        else if (f.permissions[3] == 'x')
        {
            printf("%s\t%d\t%s\t%s\t%lu\t%s\t" RED_BOLD "%s\n" DEFAULT,
                   f.permissions,
                   f.nlink,
                   f.user,
                   f.group,
                   f.size,
                   f.time,
                   f.name);
        }
        else
        {
            printf("%s\t%d\t%s\t%s\t%lu\t%s\t" YELLOW_BOLD "%s\n" DEFAULT,
                   f.permissions,
                   f.nlink,
                   f.user,
                   f.group,
                   f.size,
                   f.time,
                   f.name);
        }

        free(fpath);
        free(dir[i]);
    }
    printf(GREEN_BOLD "\nTotal: %ld\n" DEFAULT, num_blocks / 2);
    return 1;
}
