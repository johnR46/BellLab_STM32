#include<stdio.h>
#include<string.h>

struct{
int cursor;
int i;
char *buff;
char *buff2;

char str_ram[20];
char str_rom[4096];
}note;

char *xx = "John nonphala AAAAAAAAAAAAAAAAAAasdaslihdf;lisadfglkhjasdliuyaqtdfilaswfsdlkjhgdfsljkhdgsflkjhlk/hdfgz,k/h.xzcg,mh,mbvxcgz,X";

char *copynstr(char *str,char * ch,int size){	 
    note.buff2 = str;
	note.buff = ch; // copy ch to str
	note.i = 0;
	while(1){
	*note.buff2 = *note.buff;
	note.buff++;
	note.buff2++;
	note.i++;
	if(note.i == size+1){
		break;
	}
	}
	
	printf("\r\n----------------------------------------------\r\n");
	printf("str copy ch = %s",str);
	printf("\r\nsize_str = %d\r\n",size);
	printf("\r\n----------------------------------------------\r\n");

	
}


void main(){

	int x = 0;
	
	printf("\r\n -- all --\r\n");
	printf("%s",xx);
	printf("\r\n -- ---- --\r\n");
	
copynstr(note.str_ram, xx +2, 5);

printf("\r\n  ------------ \r\n");

copynstr(note.str_ram,xx + strlen(xx) - 5 ,5);




}
