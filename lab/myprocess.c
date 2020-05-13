#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


#define __LIBRARY__
#include <unistd.h>
#include <linux/sched.h>

_syscall2(sem_t*,sem_open,const char *,name, unsigned int,value);
_syscall1(int, sem_wait, sem_t*,sem);
_syscall1(int, sem_post, sem_t*,sem);
_syscall1(int, sem_unlink, const char*,name);


#define ALLNUM 6
#define CUSTOMERNUM 3
#define BUFFERSIZE 5

void Producters(FILE *fp);
void Customer(int k);
sem_t *empty,*full,*mutex;
FILE *fp;
int Inpos=0;
int Outpos=0;

int main(int argc, char ** argv)
{

    pid_t producter;
    pid_t customer;
    int i;
    empty = sem_open("empty",BUFFERSIZE);
    full = sem_open("full",0);
    mutex = sem_open("mutex",1);

    fp=fopen("./products.txt","wb+");

    producter=fork();
    if(producter != 0)
    {
        Outpos=1;
        printf("test %d\n", Outpos);
        Producters(fp);
    }
    else
    {
        for(i=0;i<CUSTOMERNUM;i++){
            if(!fork()) Customer(Outpos);
        }
    }
    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);
    fclose(fp);
    return 0;
}

void Producters(FILE *fp)
{
    int i=0;
    for (i=0;i<ALLNUM;i++)
    {
        sem_wait(empty);
        sem_wait(mutex);
        printf("product elem:%d\n",i);
        fflush(stdout);
        sem_post(mutex);
        sem_post(full);
    }     
}

void Customer(int k)
{
    int j;
    printf("-----test %d\n", Outpos);
    for (j=0;j<ALLNUM/CUSTOMERNUM;j++)
    {
        sem_wait(full);
        sem_wait(mutex);
        printf("consumer elem:%d\n",k);
        fflush(stdout);
        k++;
        sem_post(mutex);
        sem_post(empty);
    }
    exit(0);    
}
