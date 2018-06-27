#include<stdio.h>
#include<string.h>
char str4096[4096];
char str20[20];

void CursorShift(){
	int i = 0;
	     printf("please Enter \n");
	     
  do{
  
    scanf("%c",&str20[i]);
    i++;
    
   }
  while (i!=20);
}

void main() {

  printf("CurStr Left Right Start \n");
CursorShift();

}



