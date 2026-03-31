#include<stdlib.h>
#include<stdio.h>
#include<strings.h>
#include<errno.h>
#include"function.h"



char* lsh_read_line(){
  char *line = NULL;
  size_t bufsize = 0; // have getline allocate a buffer for us
  if (getline(&line, &bufsize, stdin) == -1) {
    if (feof(stdin)) {
      exit(EXIT_SUCCESS);  // We received an EOF
    } else  {
      perror("lsh: getline\n");
      exit(EXIT_FAILURE);
    }
  }
  return line;
};

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
char** lsh_split_line(char *line){
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token, **tokens_backup;

  if (!tokens) {
    fprintf(stderr, "lsh: allocation error\n");
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


int lsh_execute(char **args){
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < lsh_num_commandline(); i++) {
    if (strcmp(args[0], command_line_str[i]) == 0) {
      return (*command_line_func[i])(args);
    }
  }

  return lsh_launch(args);
};

void lsh_loop(void){
  char *line;
  char **args;
  int status;
  while(1){
    printf(">");
    line = lsh_read_line();
    args = lsh_split_line(line);
    status = lsh_execute(args);
  }
}

int lsh_launch(char **args){
  pid_t pid;
  int status;

  pid = fork();
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
    
    
  return 1;
}

int main() {
  lsh_loop();
  return 0;
}