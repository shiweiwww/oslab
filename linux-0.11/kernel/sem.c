#include<unistd.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <asm/system.h>
#include <asm/segment.h>

sem_t semaphore[20];
FIRST_ITEM=0;


int strncmp(char *ct,char *st,int count){
	int i=1;
	while(i++<=count){
		if(*ct++!=*st++) return 1;
	}
	return 0;
}

sem_t* sys_sem_open(const char *name, unsigned int value)
{

	sem_t *sem;
	char rs,buffer[20];
	int i=0,j=-1,res=-1;
	while((rs=get_fs_byte(name++))!='\0'){
		buffer[i++]=rs;
	}
	buffer[i]='\0';
	int len = i;
	
	for(i=0;i<20;i++){
		res = strncmp(&buffer,&(semaphore[i].key),len);
		if(!res) {break;}
		else {
			if(!semaphore[i].key[0] && j<0) j=i;
		}
	}
	if(!res){sem=&semaphore[i];}
	else{
		sem=&semaphore[j];

		if(!sem->head){
			printk("kong %s\n",sem->key);
			sem->head=(struct Queue *)get_free_page();
			sem->head->next=NULL;
			sem->head->pcb=NULL;
		}

		sem->value = value;
		for(j=0;j<=len;j++)
			sem->key[j] = buffer[j];		
	}
	char *p=&sem->key;
	for(i=0;i<buffer[i];i++){
		put_fs_byte(buffer[i],p++);
	}
	put_fs_long(sem->value,&sem->value);
	return sem;
}

void print_queue(char *name,struct Queue *head){

	struct Queue *p=head->next;
	printk("starting....\n");
	while(p){
		printk("%s   %d task id:%d    0x%x\n",name,p->pcb->state,p->pcb->pid,p->pcb);
		p = p->next;
	}

}

void insert(struct Queue *head,struct task_struct *pcb){
	struct Queue *p=(struct Queue *)get_free_page();
	struct Queue *pre=head;
	while(pre->next) pre=pre->next;
	p->next = pre->next;
	p->pcb = pcb;
	pre->next=p;

}
struct task_struct *get_task(struct Queue *head){
	struct Queue *p = head->next;
	if(p){
		head->next=p->next;
		return p->pcb;
	}
}

int sys_sem_wait(sem_t *sem){
	cli();
	sem_t *semp = (sem_t*)(sem);
	semp->value--;
	if(semp->value<0){
		current->state = TASK_UNINTERRUPTIBLE;
		insert(sem->head,current);
		schedule();
	}
	sti();
	return 0;
}
int sys_sem_post(sem_t *sem){
	cli();
	sem_t *semp = (sem_t*)(sem);
	sem->value++;
	if(sem->value<=0){
		struct task_struct *p=get_task(sem->head);
		if(p) p->state=0;
	}
	sti();
	return 0;
}
int sys_sem_unlink(const char *name){
	printk("sys_sem_unlink\n");
	return 0;
}
