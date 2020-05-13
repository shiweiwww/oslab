/*
/*
/*
write by sw
*/


#define __LIBRARY__
#include <unistd.h>
#include <linux/sched.h>

_syscall2(sem_t*,sem_open,const char *,name, unsigned int,value);
_syscall1(int, sem_wait, sem_t*,sem);
_syscall1(int, sem_post, sem_t*,sem);
_syscall1(int, sem_unlink, const char*,name);

