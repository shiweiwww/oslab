#include<stdio.h>
#define __LIBRARY__
#include <unistd.h>
#include <linux/sched.h>

_syscall2(sem_t*,sem_open,const char *,name, unsigned int,value);
_syscall1(int, sem_wait, sem_t*,sem);
_syscall1(int, sem_post, sem_t*,sem);
_syscall1(int, sem_unlink, const char*,name);
sem_t *empty,*full,*mutex;
void print_sem(sem_t *sem){
	printf("%s--->%d\n",sem->key,sem->value);
}
int main(){
	empty=sem_open("empty",10);
	full=sem_open("full",0);
	mutex=sem_open("mutex",1);

	print_sem(empty);
	print_sem(full);
	print_sem(mutex);
	sem_wait(empty);
	printf("-----------full----------->\n");
	sem_wait(full);
	printf("-----------mutex----------->\n");
	sem_wait(mutex);

	return 0;
}
