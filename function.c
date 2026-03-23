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

int (*command_line_func[])(char **) = {
   &lsh_cd,
   &lsh_help,
   &lsh_exit
};
