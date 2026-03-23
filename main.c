#include<stdlib.h>
#include<stdio.h>
#include<strings.h>
#include<errno.h>
#include"function.h"

char* lsh_read_line();
char** lsh_split_line();
int lsh_execute();

void lsh_loop(void){
  char *line;
  char **args;
  int status;
  while(0){
    printf(">");
    line = lsh_read_line();
    args = lsh_split_line(line);
    status = lsh_execute(args);
  }
}

int lsh_launch(char **args){
  pid_t pid;
  int status;
  if(pid == 0){

    if(execvp(args[0],args) == -1){
      perror("lsh");
    }
    exit(EXIT_FAILURE);

  }

  else if(pid<0)
    //error forking
    perror("lsh");
    else {

    do
    {
      waitpid(pid,&status,WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));

    }
    
    
  
}

int lsh_execute(char **args){
  int i;

  if(args[0] == NULL){
    return 1; //empty command
  }
}