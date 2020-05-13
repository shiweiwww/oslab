#include<stdio.h>
#define __LIBRARY__
#include <unistd.h>
_syscall2(int,whoami,char*,name,unsigned int,size);
int main(){
	const char *name;
	int i=0;
	whoami(name,10);
	for(i=0;name[i];i++){
		printf("%c",name[i]);
	}
	return 0;
}
