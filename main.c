#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#define LAUNCH 0

/*
@function are declared and definited here
*/
int help(char** args){
    printf("the shell was developed by sheng li,and it was very simple\n");
};
int Exit(char** args){
  return 0;
};

/*
@set up the command names and function pointers
*/
char *command_line_str[] = {"help","Exit"};
int (*command_line_func[])(char **) = {&help};

/*
@it can fork the process
@it still test,Launch is set 0
*/
#ifdef LAUNCH 
int shell_launch(char** args){
}
#endif

/*
@count the number of functions
*/
int the_number_of_commandline(){
    return sizeof(command_line_str)/sizeof(char*);
};
//the return value is status
int shell_execute(char** args){
    //input is empty
    if(args[0] == NULL) return 1;
    //copared the input args with commandline_string,if it mached,the function will be execued
    for(int i=0;i<the_number_of_commandline();i++){
        if(strcmp(args[0],command_line_str[i]) == 0){
           return (*command_line_func[i])(args);  
           //the function will be executed and the return value type will be an integer
        }
    }
    return 1; //we don't find out the command
};

/*
@the steps will get the input and split it into command
@there are three steps:read,split,loop
*/
char *read_line(void){
  char *line = NULL;
  ssize_t bufsize = 0;  //getline return type is ssize_t, that is long
  if(getline(&line,&bufsize,stdin) == -1){
    if (feof(stdin))
    {
        exit(EXIT_SUCCESS);
    }
    else{
        perror("getline\n");
        exit(EXIT_FAILURE);
    }
  }
  return line;
};
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
char **split_line(char *line){
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token, **tokens_backup;

  if (!tokens) {
    fprintf(stderr, "shell: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens_backup = tokens;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
		free(tokens_backup);
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
};
void shell_loop(void){
  char *line;
  char **args;
  int status;

  do
  {
    printf(">");
    line = read_line();
    args = split_line(line);
    status = shell_execute(args);
  } while (status);
  
};

int main(void){
shell_loop();
    return 0;
}