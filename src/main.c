/******************//*
@author Kavi Mehta
@date 2023-10-09
@file main.c
*******************/

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Read line buffer size
#define KSH_RL_BUFSIZE 1024
//Split line buffer size
#define KSH_TOK_BUFSIZE 64
//Token delimiters
#define KSH_TOK_DELIM " \t\r\n\a"

/**
 * Readline function implemented with getline()
 * Input :
 * Output : char line
 */
char *ksh_read_line(void){
  char *line = NULL;
  //getline allocates buffer
  ssize_t bufsize = 0;

  if (getline(&line, &bufsize, stdin) == -1){
    // Got to EOF
    if (feof(stdin)){
      exit(EXIT_SUCCESS);
    } else {
      perror("readline");
      exit(EXIT_FAILURE);
    }
  }
  return line;
}

/**
 * For learning purposes don't use getline()
 * Read line function implemented without getline()
 * Input : 
 * Output : char buffer 
*/
char *ksh_read_line_without_get_line(void){
  int bufsize = KSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char)*bufsize);
  // use int here because EOF is an int not char so comparison only works if c is int
  int c;

  if(!buffer){
    fprintf(stderr,"ksh: allocation error\n")
  }

  while(1){
    // Get character from user input
    c = getchar();

    // If EOF append null character and return 
    if (c == EOF || c == '\n'){
      buffer[position] = '\0';
      return buffer
    }
    // else append char c to buffer and loop
    else {
      buffer[position] = c;
    }
    position++;

    // if buffer is exceeded then reallocate
    if (position >= buffer){
      bufsize = KSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer){
        fprintf(stderr, "ksh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

/**
 * Split line into arguments called tokens using whitespace as delimiters
 * Input : char line 
 * Output : Null terminated array of tokens
 */
char **ksh_split_line(char *line){
  int bufsize = KSH_TOK_BUFSIZE;
  int position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens){
    fprintf(stderr, "ksh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  //tokenize line 
  token = strtok(line, KSH_TOK_DELIM);
  while(token != NULL){
    tokens[position] = token;
    position++;
    
    if (position >= bufsize){
      bufsize += KSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens){
        fprintf(stderr, "ksh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
    token = strtok(NULL, KSH_TOK_DELIM)
  }
  tokens[position] = NULL;
  return tokens;
}


/**
 * Loop that takes input, reads, parses, and executes the input
 */
void ksh_loop(void){
  char *line;
  char **args;
  int status;

  do {
    //prompt
    printf("λ ");
    //read the line
    line = ksh_read_line();
    //seperate the line into arguments
    args = ksh_split_line(line);
    //execute the arguments
    status = ksh_execute(args);

    free(line);
    free(args);
    
    //continue loop based on the return of ksh_execute 
  } while (status);
}

/**
@param argc - Argument Count
@param argv - Argument Vector
@return - Status Code
*/
int main(int argc, char *argv[]){
  // Load Config
  
  // Run loop
  ksh_loop()

  // Exit/Shutdown Cleanup

  return EXIT_SUCCESS;
}
