#include <stdio.h>
#include <unistd.h>

int main() {
  //child reads, parent writes
  int pipe1[2];
  pipe(pipe1);
  //parent reads, child writes
  int pipe2[2];
  pipe(pipe2);

  if (fork() == 0) {
    close(pipe1[1]);
    close(pipe2[0]);

    int i;
    read(pipe1[0], &i, sizeof(i));
    printf("child received: %d\n", i);
    
    i++;
    write(pipe2[1], &i, sizeof(i));

    close(pipe1[0]);
    close(pipe2[1]);
  } else {
    close(pipe1[0]);
    close(pipe2[1]);

    int i = 2;
    
    printf("parent sending: %d\n", i);    
    write(pipe1[1], &i, sizeof(i));

    read(pipe2[0], &i, sizeof(i));
    printf("parent received: %d\n", i);

    close(pipe1[1]);
    close(pipe2[0]);
  }
  return 0;
}
