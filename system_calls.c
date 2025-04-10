#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

int main(){
  int fd;
  ssize_t bytes_read, bytes_written;
  char buffer[1024];
  pid_t pid;
  int status;

  //open()
  fd = open("example.txt", O_RDWR | O_CREAT, 0666);
  if(fd == -1){
    perror("open");
    exit(1);
  }
  printf("File Opened successfully, fd = %d\n", fd);

  //write
  const char *msg = "Hello world! OS LAB @123";
  bytes_written = write(fd, msg, strlen(msg));
  if(bytes_written == -1){
    perror("write");
    close(fd);
    exit(1);
  }
  printf("Worte %zd bytes to file\n", bytes_written);

  //offset
  off_t offset = lseek(fd, 0, SEEK_SET);
  if(offset == -1){
    perror("lseek");
    close(fd);
    exit(1);
  }

  //read
  bytes_read= read(fd, buffer, sizeof(buffer)-1);
  if(bytes_read == -1){
    perror("read");
    close(fd);
    exit(1);
  }
  buffer[bytes_read] = '\0';
  printf("Read %zd bytes: %s\n", bytes_read, buffer);

  //sleep()
  printf("Sleeping for 2 seconds\n");
  sleep(2);
  printf("Woke up after 2 seconds");

  //fork()
  pid = fork();
  if(pid == -1){
    perror("fork");
    close(fd);
    exit(1);
  }

  if(pid == 0){
    printf("In child process. PID = %d\n", pid);
    _exit(0);
  }else{
    waitpid(pid, &status, 0);
    printf("Child process finished. PID = %d\n", pid);
  }

  pid = fork();
  if(pid == 0){
    printf("In child process");
    execlp("/bin/ls", "ls", "-l", (char *)NULL);
    perror("Exec");
    _exit(1);
  }else{
    waitpid(pid, &status, 0);
    printf("Exec call finished\n");
  }

  // getpid()
  printf("Current process ID: %d\n", getpid());

  //wait
  pid = fork();
  if(pid == 0){
    _exit(0);
  }else{
    pid_t child_pid = wait(&status);
    if(child_pid == -1){
      perror("wait");
      close(fd);
      exit(1);
    }
    printf("Parent waited for child. PID %d\n", child_pid);
  }

  if(close(fd) == -1){
    perror("close");
    exit(1);
  }

  printf("File closed successfully\n");

  return 0;

} 