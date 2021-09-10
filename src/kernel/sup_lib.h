#ifndef _SUP_LIB_H_INCLUDED_
#define _SUP_LIB_H_INCLUDED_

#include <stdint.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

void* sbrk(intptr_t increment);
int kill(pid_t pid, int sig);
pid_t getpid(void);
void _exit(int status);
ssize_t write(int fd, const void *buf, size_t count);
int close(int fd);
int fstat(int fd, struct stat *statbuf);
int isatty(int fd);
off_t lseek(int fd, off_t offset, int whence);
ssize_t read(int fd, void *buf, size_t count);

#endif