#include<stdio.h>
#include<string.h>

void *vp; 
int a = 100, *ip;
float f = 12.2, *fp;
char ch = 'a';

 
int main(){

	//vp =&a;
	vp =&ch;
	printf("%c",*(char *)vp);
	

	return 0;
}
