#include<unistd.h>
#include <linux/kernel.h>
#include <asm/segment.h>

char buffer[20];

int sys_iam(const char* name){
	printk("my name is:");
	char rs;
	int i=0;
	while(rs=get_fs_byte(name++)){
			buffer[i++]=rs;
	}
	printk(buffer);
	return 0;
}
int sys_whoami(char *name,unsigned int size){
	printk("get buffer from kernel\n");
	int i=0;
	char c;
	char *temp=name;
	while(c=buffer[i++]){
		put_fs_byte(c,temp++);
	}
	return 0;
}