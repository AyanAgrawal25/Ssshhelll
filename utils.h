#ifndef __UTILS
#define __UTILS

// process struct (utility)
typedef struct process_info
{
    pid_t pid;
    char proc_name[2000];
    int id;
} procinfo;

//linked list of active processes
typedef struct proc_node
{
    procinfo data;
    struct proc_node *next;
} pnode;

int welcome();
void sigtstp_(int sign);
void sigs();
void sigint_(int sign);
void dead_ch(int sign);
char *relative_pwd(char *direc);
char *get_home_dir();
char *cut_str(const char *str, long int s, long int l);
void bye_bye();
void check_tilda(int argc, char **argv);
int check_ampersand(char *command, int argc, char **argv);
extern int exit_status;

pnode *procs;

pnode *insert_at_last(pnode *head, procinfo info);
procinfo *info_pid(pnode *head, pid_t pid);
pnode *del_pid(pnode *head, pid_t pid);
procinfo *info_id(pnode *head, int id);
int proc_storage(pid_t pid, char *tmp);

char *make_full_cmd_str(char *command, int argc, char **argv);
void ext_funcs(char *command, int argc, char **argv);
int externals(int argc, char **argv, int bg_flag);

#endif