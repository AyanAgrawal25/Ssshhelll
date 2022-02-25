#include "header.h"

void dead_ch(int sign)
{
    int wait_st;
    char *pname;
    pid_t pid = waitpid(-1, &wait_st, 1);

    if (pid > 0)
    {
        procinfo *p = info_pid(procs, pid);

        if (p != NULL)
        {
            char *temp = p->proc_name;
            pname = (char *)malloc(sizeof(char) * (strlen(temp) + 1));
            strcpy(pname, temp);
            procs = del_pid(procs, pid);
        }
        else
        {
            pname = (char *)malloc(sizeof(char) * 100);
            strcpy(pname, "Process");
        }

        if (WIFEXITED(wait_st) && WEXITSTATUS(wait_st) == 0)
            fprintf(stderr, GREEN_BOLD "\n%s with pid %d exited normally.\n" DEFAULT, pname, pid);

        else
            fprintf(stderr, RED_BOLD "\n%s with pid %d exited abnormally.\n" DEFAULT, pname, pid);

        nameplate();
        fflush(stdout);
        free(pname);
        return;
    }
    return;
}

void sigint_(int sign)
{
    if (getpid() != PID_SHELL)
        return;
    if (FGPID_CH < 0)
        return;
    raise(SIGINT);
}

void sigs()
{
    signal(SIGCHLD, dead_ch);
    signal(SIGINT, sigint_);
}

int welcome()
{
    printf(RED_BOLD "\n\t***\tWelcome to my Ssshhelll.\t***\t\n\n" DEFAULT);

    user_name = getlogin();
    host_name = (char *)malloc(sizeof(char) * (HOST_NAME_MAX + 1));

    int x = gethostname(host_name, 65);
    if (x != 0)
    {
        perror("hostname");
        return -1;
    }
    FG_CH_NAME[0] = '\0';
    FGPID_CH = -1;
    PID_SHELL = getpid();

    sigs();
    procs = NULL;

    home_dir = get_home_dir();
    if (home_dir == NULL)
    {
        perror("error getting home_dir");
        return -1;
    }
    return 0;
}

char *cut_str(const char *str, long int s, long int l)
{
    long int total_len = strlen(str);
    if (s + l > total_len)
        return NULL;

    char *sub_str = (char *)malloc(sizeof(char) * (l + 1));
    for (long long i = 0; i < l; i++)
    {
        sub_str[i] = str[i + s];
    }
    sub_str[l] = '\0';
    return sub_str;
}

char *get_home_dir()
{
    pid_t pid = getpid();
    char *read_path = (char *)malloc(sizeof(char) * MAX_LEN);
    sprintf(read_path, "/proc/%d/exe", pid);

    char *temp = (char *)malloc(sizeof(char) * MAX_LEN);
    ssize_t exec_len = readlink(read_path, temp, MAX_LEN - 1);

    if (exec_len < 0)
    {
        free(read_path);
        free(temp);
        return getcwd(NULL, 0);
    }
    temp[exec_len] = '\0';
    for (int i = exec_len - 1; i >= 0; i--)
    {
        if (temp[i] == '/')
        {
            temp[i] = '\0';
            break;
        }
    }
    free(read_path);
    return temp;
}

char *relative_pwd(char *direc)
{
    char *c_dir = (char *)malloc(sizeof(char) * (strlen(direc) + 1));
    strcpy(c_dir, direc);

    long int c_len = strlen(c_dir);
    long int home_len = strlen(home_dir);

    if (strcmp(c_dir, home_dir) == 0)
    {
        free(c_dir);
        char *str = (char *)malloc(sizeof(char) * 5);
        strcpy(str, "~");
        return str;
    }

    char *str1 = cut_str(c_dir, 0, home_len);
    if (str1 != NULL && strcmp(str1, home_dir) == 0)
    {
        long int str1_len = strlen(str1);
        if (str1_len < c_len && (c_dir[str1_len] == '/' || c_dir[str1_len] == '\0'))
        {
            char *str2 = cut_str(c_dir, home_len, c_len - home_len);

            char *ans = (char *)malloc(sizeof(char) * (strlen(str2) + 2));
            strcpy(ans, "~");
            strcat(ans, str2);

            free(c_dir);
            free(str1);
            free(str2);
            return ans;
        }
    }
    free(str1);
    return c_dir;
}

void bye_bye()
{
    printf(YELLOW_BOLD "\nGoodbye!\n" DEFAULT);
    free(home_dir);
    free(host_name);
    exit(0);
}

void check_tilda(int argc, char **argv)
{
    for (int i = 0; i < argc; i++)
    {
        if (argv[i][0] == '~')
        {
            long int len = strlen(argv[i]) + strlen(home_dir);
            char *final = (char *)malloc(sizeof(char) * len);
            strcpy(final, home_dir);
            strcat(final, argv[i] + 1);
            argv[i] = final;
        }
    }
}

int check_ampersand(char *command, int argc, char **argv)
{
    long int cmd_size = strlen(command);

    if (command[cmd_size - 1] == '&')
    {
        argv[0] = (char *)malloc(sizeof(char) * 2);
        strcpy(argv[0], "&");
        command[cmd_size - 1] = '\0';

        return 1;
    }

    for (int i = 0; i < argc; i++)
    {
        long int len = strlen(argv[i]);
        if (argv[i][len - 1] != '&')
            continue;

        if (len == 1)
            return i + 1;
        else
        {
            argv[i][len - 1] = '\0';
            argv[i + 1] = (char *)malloc(sizeof(char) * 2);
            strcpy(argv[i + 1], "&");
            return i + 2;
        }
    }
    return argc;
}

pnode *insert_at_last(pnode *head, procinfo info)
{
    pnode *n = (pnode *)malloc(sizeof(pnode));

    n->data = info;
    n->next = NULL;

    if (head == NULL)
        return n;

    pnode *iterate = head;
    while (iterate->next != NULL)
        iterate = iterate->next;
    iterate->next = n;
    return head;
}

pnode *del_pid(pnode *head, pid_t pid)
{
    if (head == NULL)
        return NULL;

    if (head->data.pid == pid)
    {
        pnode *tmp = head->next;
        free(head);
        return tmp;
    }

    pnode *iterate = head->next;
    pnode *prev = head;

    while (iterate != NULL)
    {
        if (iterate->data.pid == pid)
        {
            prev->next = iterate->next;
            free(iterate);
            return head;
        }
        prev = iterate;
        iterate = iterate->next;
    }
    return head;
}

procinfo *info_pid(pnode *head, pid_t pid)
{
    for (int i = 0; head != NULL;)
    {
        ++i;
        if (head->data.pid == pid)
        {
            head->data.id = i;
            return &(head->data);
        }
        head = head->next;
    }
    return NULL;
}

procinfo *info_id(pnode *head, int id)
{
    for (int i = 0; head != NULL;)
    {
        ++i;
        if (i == id)
        {
            head->data.id = i;
            return &(head->data);
        }
        head = head->next;
    }
    return NULL;
}

int proc_storage(pid_t pid, char *tmp)
{
    procinfo proc;
    proc.id = -1;
    proc.pid = pid;
    strcpy(proc.proc_name, tmp);

    procs = insert_at_last(procs, proc);

    procinfo *x = info_pid(procs, pid);
    if (x == NULL)
        return -1;
    else
        return x->id;
}

void ext_funcs(char *command, int argc, char **argv)
{
    char **new_argv = (char **)malloc(sizeof(char *) * (argc + 2));
    new_argv[0] = command;
    int bg_flag = 0;
    if (argc > 0 && strcmp(argv[argc - 1], "&") == 0)
    {
        bg_flag = 1;
        argc--;
    }

    int new_argc = 1;
    for (int i = 0; i < argc; i++)
    {
        new_argv[new_argc] = argv[i];
        new_argc++;
    }
    new_argv[new_argc] = NULL;
    externals(new_argc, new_argv, bg_flag);
    free(new_argv);
}

char *make_full_cmd_str(char *command, int argc, char **argv)
{
    long int i = 0;
    char *temp = (char *)malloc(sizeof(char) * MAX_LEN);
    strcpy(temp, command);
    long int total_len = strlen(temp);

    while (i < argc)
    {
        total_len = total_len + strlen(argv[i]) + 1;
        if (total_len >= MAX_LEN - 1)
            break;
        strcat(temp, argv[i++]);
        if (i != argc - 1)
            strcat(temp, " ");
    }
    return temp;
}

int externals(int argc, char **argv, int bg_flag)
{
    if (bg_flag == 0)
    {
        // FG
        pid_t pid = fork();

        if (pid > 0)
        {
            FGPID_CH = pid;
            char *tmp_str = make_full_cmd_str("", argc, argv);
            strcpy(FG_CH_NAME, tmp_str);
            free(tmp_str);

            signal(21, SIG_IGN);
            signal(22, SIG_IGN);

            setpgid(pid, 0);
            tcsetpgrp(0, pid);

            int w_stop;
            waitpid(pid, &w_stop, 2);

            tcsetpgrp(0, getpgrp());

            signal(21, SIG_DFL);
            signal(22, SIG_DFL);

            if (WIFSTOPPED(w_stop))
            {
                long id_ch = proc_storage(FGPID_CH, FG_CH_NAME);
                printf("[%ld] %s %d stopped.\n", id_ch, FG_CH_NAME, FGPID_CH);
            }

            FGPID_CH = -1;
            FG_CH_NAME[0] = '\0';

            return (WIFEXITED(w_stop) && WEXITSTATUS(w_stop) == 0);
        }
        else if (pid == 0)
        {
            // for child
            setpgid(0, 0);

            if (execvp(argv[0], argv) < 0)
            {
                perror("Error executing command");
                exit(1);
            }
        }
        else
        {
            perror("Error executing command");
            return 0;
        }
    }
    else
    {
        // BG

        pid_t pid = fork();

        if (pid == 0)
        {
            setpgid(0, 0);
            if (execvp(argv[0], argv) < 0)
            {
                perror("Error executing command");
                exit(1);
            }
        }
        else if (pid < 0)
        {
            perror("Error executing command");
            return 0;
        }
        else
        {
            char *tmp_str;
            tmp_str = make_full_cmd_str("", argc, argv);
            proc_storage(pid, tmp_str);
            free(tmp_str);

            printf("%d\n", pid);

            setpgid(pid, 0);
            tcsetpgrp(0, getpgrp());
            return 1;
        }
    }
    return 1;
}