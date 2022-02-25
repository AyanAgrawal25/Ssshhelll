#ifndef __TOKEN
#define __TOKEN

void command_to_exec(char *cmd);
void tokenize(char* input);
void check_tilda(int argc, char** argv);
int check_ampersand(char *command, int argc, char **argv);
#endif
