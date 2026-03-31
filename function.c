#include"function.h"

char *command_line_str[] = {
  "cd",
  "help",
  "exit"
};

int lsh_num_commandline(){
    return sizeof(command_line_str)/sizeof(char *);
}

int lsh_cd(char **args){
  if(args[1] == NULL){
    fprintf(stderr,"lsh: expected argument to \"cd\"\n");
  }
  else{
    if(chdir(args[1]) != 0){
        perror("lsh");
    }
  }
  return 1;
}

int lsh_help(char **args)
{
  int i;
  printf("the program is developed by shengli in 20260331 from Stephen Brennan's LSH\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < lsh_num_commandline(); i++) {
    printf("  %s\n", command_line_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

int lsh_exit(char **args)
{
  return 0;
}

int (*command_line_func[])(char **) = {
   &lsh_cd,
   &lsh_help,
   &lsh_exit
};
