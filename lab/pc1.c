#include <stdlib.h>
#include<stdio.h>
#include <time.h>
#include <sys/times.h>

#define __LIBRARY__
#include <unistd.h>
#include <linux/sched.h>
#define N 5

_syscall2(sem_t*,sem_open,const char *,name, unsigned int,value);
_syscall1(int, sem_wait, sem_t*,sem);
_syscall1(int, sem_post, sem_t*,sem);
_syscall1(int, sem_unlink, const char*,name);

sem_t *Empty,*Full,*Mutex;
int in,out;
int buffer[N];

int main(void)
{

  
    
    int procnum = 0, loopnum = 5;
    int i = 0, j = 0;
    int ret = 0;
    pid_t apid;
    int status;
    in = 0;
    out = 0;
    Empty = sem_open("empty",N);
    Full = sem_open("full",0);
    Mutex = sem_open("mutex",1);


    status=fork();
    if(!status){
        for(i=0;i<N;i++){
            printf("waiting %d child\n",i);
            sem_wait(Mutex);
            printf("child %d is finished\n",i);
        }
    }
    else{
        for (i = 0; i < loopnum; i++)
        {
            status = fork();
            if (status == 0 || status == -1) break;
        }
        if (status == -1)
        {
            printf("%s\n","error");
        }
        else if (status == 0)
        {
            printf("wake up child %d\n",i);
            sem_post(Mutex);
            sleep(5);
            exit(0);
        }
        else
        {
            while (1) {
                ret = wait(NULL);
                if (ret == -1) {
                    break;
                }
            }
            printf("parrent pid: %d\n", getpid());
        }
    } 
    return 0;
}