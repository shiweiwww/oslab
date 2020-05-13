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
	if(!(pid=fork())){
		a = (int *)(shmat(shmid,NULL,NULL));
		*a=0x12345678;
		printf("child process 0x%08x\n",*a);
		exit(0);
	}
	else{
		wait(NULL);
		a = (int *)(shmat(shmid,NULL,NULL));
		printf("parents process 0x%08x\n",*a);

	}







	return 0;
}
