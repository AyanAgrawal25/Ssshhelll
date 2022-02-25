#ifndef __CRONJOB_H
#define __CRONJOB_H

#include <errno.h>
void replay_func(int argc, char **args);
void replay(char *command, int interval, int period);
#endif