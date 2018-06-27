#include<stdio.h>
#include<string.h>
char str[20];
char strfirst[20];
char strmiddle[] = "john   Nonphala";
char strlast[20];
char str2[20];

int cur = 0;


//char * strncpy ( char * destination, const char * source, size_t num );
	


void main() {
  int i = 0;
  printf("Enter Str : ");

  for (i = 0; i < 5; i++) {
    scanf("%c", &str[i]);
  }
  
  printf("Enter cur :");
  scanf("%d",&cur);
  
  strncpy(strfirst,str,cur); // strfirst(str(start,last));
  strncpy(strlast,str + cur,strlen(str)-cur);
  
  
   strcat(strfirst,strmiddle);
  strcat(strfirst,strlast);
  
 
  
  printf("%s \n",strfirst);
 // printf("%s \n",strlast);
 

}

