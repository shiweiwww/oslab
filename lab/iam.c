#include<stdio.h>
#define __LIBRARY__
#include <unistd.h>
_syscall1(int, iam, const char*,name);
int main(){
	iam("hello,shiwei!\n");
	return 0;
}
