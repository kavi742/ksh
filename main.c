/******************//*
@author Kavi Mehta
@date 2023-10-09
@file main.c
*******************/
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

int main(int argc, char *argv[]){
  // Load Config
  
  // Run loop
  ksh_loop()

  // Exit/Shutdown Cleanup

  return EXIT_SUCCESS;
}
