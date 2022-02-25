#ifndef _HEAD
#define _HEAD

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <limits.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <signal.h>
#include <grp.h>
#include <pwd.h>

// all header files
#include "cd.h"
#include "tokenize.h"
#include "utils.h"
#include "prompt.h"
#include "echo.h"
#include "ls.h"
#include "pwd.h"
#include "pinfo.h"
#include "repeat.h"
#include "history.h"
#include "redirection.h"
#include "fg.h"
#include "jobs.h"
#include "bg.h"
#include "sig.h"
#include "replay.h"
#include "pipe.h"

#define MAX_LEN 8192
#define HIST_FILE ".history.txt"

pid_t FGPID_CH;
pid_t PID_SHELL;
char FG_CH_NAME[MAX_LEN];
char last_acc[2000];

// colours
#define RED "\033[0;31m"
#define BLUE "\033[1;34m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define CYAN "\033[0;36m"
#define RED_BOLD "\033[1;31m"
#define GREEN_BOLD "\033[1;32m"
#define YELLOW_BOLD "\033[1;33m"
#define CYAN_BOLD "\033[1;36m"
#define WHITE "\033[0;37m"
#define PURPLE "\033[0;35m"
#define DEFAULT "\033[0m"

//space delimiter
#define jagah_hatao " \t\r\n\v\f"

char hist[20][500];
char *home_dir;
char *user_name;
char *host_name;
int hist_cnt;

#endif