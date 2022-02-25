#ifndef __CD
#define __CD

char present_dir[2000];

int change(char *path);
void change_dir(int argc, char **argv);
char *trim_str(char *str, char c);
int change_last();

#endif
