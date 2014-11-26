#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int handle_one(int fd);

void
handle(int fd)
{
  while (handle_one(fd) >= 0)
    ; /* loop */
}

int
handle_one(int fd)
{
  char cmd[128];
  int buflen = 4096;  // intentional overflow: should be sizeof(cmd)-1
  ssize_t cc = read(fd, cmd, buflen);
  if (cc <= 0)
    return -1;

  while (cc > 0 && (cmd[cc-1] == '\r' || cmd[cc-1] == '\n'))
    cc--;
  cmd[cc] = '\0';
  char* arg = strchr(cmd, ' ');
  if (!arg)
    return -1;
  *(arg++) = '\0';

  if (!strcmp(cmd, "ls")) {
    DIR* d = opendir(arg);
    if (d) {
      for (;;) {
        struct dirent* de = readdir(d);
        if (!de)
          break;

        write(fd, de->d_name, strlen(de->d_name));
        write(fd, "\n", 1);
      }
      closedir(d);
    }
  }

  if (!strcmp(cmd, "read")) {
    int x = open(arg, O_RDONLY);
    if (x >= 0) {
      for (;;) {
        char buf[1024];
        ssize_t cx = read(x, buf, sizeof(buf));
        if (cx <= 0)
          break;
        write(fd, buf, cx);
      }
      close(x);
    }
  }

  if (!strcmp(cmd, "create")) {
    int x = open(arg, O_RDWR | O_CREAT | O_EXCL, 0666);
    if (x >= 0) {
      char* msg = "Hello world.\n";
      write(x, msg, strlen(msg));
      close(x);
    }
  }

  if (!strcmp(cmd, "exec")) {
    int pid = fork();
    if (pid == 0) {
      dup2(fd, 0);
      dup2(fd, 1);
      dup2(fd, 2);
      close(fd);
      execlp(arg, arg, 0);
      exit(-1);
    }

    int status;
    wait(&status);
  }

  return 0;
}
