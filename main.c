/******************//*
@author Kavi Mehta
@date 2023-10-09
@file main.c
*******************/

//Read line buffer size
#define KSH_RL_BUFSIZE 1024

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
