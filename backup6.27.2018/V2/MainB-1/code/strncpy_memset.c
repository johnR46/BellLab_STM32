#include <stdio.h>
#include <string.h>
#define size_buff  255

char src[4096];
char dest[size_buff +1];

int len = 0;
int main () {
  char *p = src;

 
  strcpy(src, "John Norman Born John Frederick Lange, Jr. June 3, 1931 (age 87) Chicago, Illinois Occupation Professor of philosophy, writer Nationality American Education Bachelor of Arts Master of Arts Doctor of Philosophy Alma mater University of Nebraska University of Southern California Princeton University Genre Sword and planet Notable works Gor novel series Spouse Bernice L. Green (1956present) Children John David Jennifer Relatives John Frederick Lange, Sr. (father) Almyra D. Lange ne Taylor (mother) John NoA");
  printf("strlen src is %d\n", strlen(src)); // strlen(src) =  4096
printf("------src-----------\n");
printf("%s\n",src);
printf("------dest-----------\n");

int start =0;
int k = 0;
len = strlen(src);

	while(len>=size_buff){
		memset(dest,0,size_buff+1);
		strncpy(dest,p,size_buff);
		p+=size_buff;
		len-=size_buff;
		printf("%s\n",dest);
		printf("string dest = %d\n",strlen(dest));
		printf("string it is  = %d\n",k);
		k++;
		
		
	}
	if(len>0){
	memset(dest,0,size_buff+1);
	strncpy(dest,p,len);
	printf("%s\n",dest);
	printf("string dest = %d\n",strlen(dest));
	printf("string it is  = %d\n",k);
	printf("--------------------------------------------\n");	
	}
	
	

  return (0);
}
