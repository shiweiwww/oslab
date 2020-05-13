#include <stdlib.h>
#include<stdio.h>
#include <time.h>
#include <sys/times.h>

#define __LIBRARY__
#include <unistd.h>
#include <linux/sched.h>

_syscall3(int ,shmget,int,key,size_t,size,int,shmflg);
_syscall3(void*,shmat,int,shmid,const void*,shmaddr,int,shmflg);

int shmid,*a;

int main(){
	int key = 1234;
	int pid,i;

	shmid = shmget(key,23,0);
	a = (int *)(shmat(shmid,NULL,NULL));
	printf("ccc 0x%08x\n",*a);
	return 0;
}
