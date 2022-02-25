#include "header.h"

void command_to_exec(char *command)
{
    redirect_stats rd;

    rd.append = 0;
    rd.input = 0;
    rd.output = 0;
    rd.ipf[0] = '\0';
    rd.opf[0] = '\0';

    if (command == NULL)
        return;

    long int cmd_size = strlen(command);

    char *main_cmd = strtok(command, jagah_hatao);

    if (main_cmd == NULL)
        return;

    char *cmd;
    cmd = (char *)malloc(sizeof(char) * (strlen(main_cmd) + 1));
    strcpy(cmd, main_cmd);

    char **cmd_arg = (char **)malloc(sizeof(char *) * (cmd_size + 1));
    int arg_cnt = 0;

    int curr_input_file = 0;
    int curr_output_file = 0;

    while ((main_cmd = strtok(NULL, jagah_hatao)) != NULL)
    {
        if (!strcmp(main_cmd, "<"))
        {
            if (curr_input_file || curr_output_file)
            {
                fprintf(stderr, "Error parsing command\n");
                return;
            }

            rd.input = 1;
            curr_input_file = 1;
            continue;
        }
        else if (strcmp(main_cmd, ">") == 0)
        {
            if (curr_input_file || curr_output_file)
            {
                fprintf(stderr, "Error parsing command\n");
                return;
            }

            rd.output = 1;
            rd.append = 0;
            curr_output_file = 1;
            continue;
        }
        else if (strcmp(main_cmd, ">>") == 0)
        {
            if (curr_input_file || curr_output_file)
            {
                fprintf(stderr, "Error parsing command\n");
                return;
            }

            rd.output = 1;
            rd.append = 1;
            curr_output_file = 1;
            continue;
        }

        if (curr_output_file)
        {
            strcpy(rd.opf, main_cmd);
            curr_output_file = false;
            continue;
        }
        else if (curr_input_file)
        {
            strcpy(rd.ipf, main_cmd);
            curr_input_file = false;
            continue;
        }

        cmd_arg[arg_cnt] = (char *)malloc(sizeof(char) * (strlen(main_cmd) + 1));
        strcpy(cmd_arg[arg_cnt++], main_cmd);
    }

    if (curr_input_file)
    {
        fprintf(stderr, "Error parsing command\n");
        return;
    }
    if (curr_output_file)
    {
        fprintf(stderr, "Error parsing command\n");
        return;
    }

    arg_cnt = check_ampersand(cmd, arg_cnt, cmd_arg);
    check_tilda(arg_cnt, cmd_arg);

    redirect_stats1 r1 = initialize_redirec(rd);
    if (rd.input && r1.in_file == -1)
        return;
    if (rd.output && r1.out_file == -1)
        return;

    if (!strcmp(cmd, "echo"))
        go_echo(arg_cnt, cmd_arg);
    else if (!strcmp(cmd, "cd"))
        change_dir(arg_cnt, cmd_arg);
    else if (!strcmp(cmd, "pwd"))
        pwd_func(arg_cnt, cmd_arg);
    else if (!strcmp(cmd, "ls"))
        ls_cmd(arg_cnt, cmd_arg);
    else if (!strcmp(cmd, "pinfo"))
        func_pinfo(arg_cnt, cmd_arg);
    else if (!strcmp(cmd, "quit") || !strcmp(cmd, "exit") || !strcmp(cmd, "q"))
        bye_bye();
    else if (!strcmp(cmd, "repeat"))
        repeat_cmds(arg_cnt, cmd_arg);
    else if (!strcmp(cmd, "history"))
        history_cmd(arg_cnt, cmd_arg);
    else if (!strcmp(cmd, "fg"))
        foregnd(arg_cnt, cmd_arg);
    else if (!strcmp(cmd, "bg"))
        backgnd(arg_cnt, cmd_arg);
    else if (!strcmp(cmd, "jobs"))
        jobs(arg_cnt, cmd_arg);
    else if (!strcmp(cmd, "sig"))
        sig(arg_cnt, cmd_arg);
    else if (!strcmp(cmd, "replay"))
        replay_func(arg_cnt, cmd_arg);
    else
        ext_funcs(cmd, arg_cnt, cmd_arg);

    finish_redirec(rd, r1);

    free(cmd);
    for (long int i = 0; i < arg_cnt; i++)
        free(cmd_arg[i]);

    free(cmd_arg);
}

void tokenize(char *input)
{
    long int semi_cnt = 1;
    for (long int i = 0; i < strlen(input); i++)
    {
        if (input[i] == ';')
            semi_cnt++;
    }

    char **tokens = (char **)malloc(sizeof(char *) * semi_cnt);
    long int num_tokens = 0;

    char *a = strtok(input, ";");
    for (; a != NULL;)
    {
        tokens[num_tokens] = (char *)malloc(sizeof(char) * (strlen(a) + 1));
        strcpy(tokens[num_tokens++], a);
        a = strtok(NULL, ";");
    }

    for (long int i = 0; i < num_tokens; i++)
    {
        piping(tokens[i]);
        free(tokens[i]);
    }

    free(tokens);
}
