#include "sup_lib.h"
#include <errno.h>

void* sbrk(intptr_t increment) {
  errno = ENOMEM;
  return (void *)-1;
}

int kill(pid_t pid, int sig) {
  errno = EINVAL;
  return -1;
}

pid_t getpid(void) {
  return -1;
}

void _exit(int status) {
  return;
}

ssize_t write(int fd, const void *buf, size_t count) {
  errno = EBADF;
  return -1;
}

int close(int fd) {
  errno = EBADF;
  return -1;
}

int fstat(int fd, struct stat *statbuf) {
  errno = EBADF;
  return -1;
}

int isatty(int fd) {
  errno = EBADF;
  return 0;
}

off_t lseek(int fd, off_t offset, int whence) {
  errno = EBADF;
  return (off_t)-1;
}

ssize_t read(int fd, void *buf, size_t count) {
  errno = EBADF;
  return -1;
}