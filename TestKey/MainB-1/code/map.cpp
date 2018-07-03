#include<stdio.h>
#include<math.h>
int main(){
	int i; 
	int num[8] ={1,2,4,8,16,32,64};
	for(i=1;i<=sizeof(num)/sizeof(num[0])-1;i++)
	  printf("%d\t",num[i] = num[i]>>1);
	   
}
