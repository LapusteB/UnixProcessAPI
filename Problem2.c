#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


// entry point
int main(int argc, char *argv[]) {
  
  char *cmd1;//BUFSIZ
  char *cmd2;
  cmd1 = malloc(sizeof(char*));
  cmd2 = malloc(sizeof(char*));

  scanf("%s | %s", cmd1, cmd2);

  int fd[2], id, id2;
  pipe(fd);

  if(id = fork() == 0) {
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);

    execlp(cmd1, cmd1, (char *) NULL);
  }

  if(id2 = fork() == 0) {
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);

    execlp(cmd2, cmd2, (char *) NULL);
  }

  close(fd[0]);
  close(fd[1]);
  
  printf("++++");
  wait(&id);
  wait(&id2);

  return 0;
};