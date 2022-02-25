#ifndef __HISTORY_H
#define __HISTORY_H

char hist_filename[500];

void load_history();
void history_cmd(int argc, char **argv);
void write_history();
int max(int a, int b);
#endif
