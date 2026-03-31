#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);
int lsh_launch(char **args);

extern char *command_line_str[];
extern int (*command_line_func[])(char **);
extern int lsh_num_commandline();