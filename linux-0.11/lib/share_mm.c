/*
/*
/*
write by sw
*/

#define __LIBRARY__
#include <unistd.h>
#include <linux/sched.h>

_syscall3(int ,shmget,int,key,size_t,size,int,shmflg);
_syscall3(void*,shmat,int,shmid,const void*,shmaddr,int,shmflg);

