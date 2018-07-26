#include<stdio.h>
#include<string.h>


struct{
int cursor;
int i;
char *buff;
char *buff2;
char str_buff[20];
char str_ram[20];
char str_rom[4096];
}note;


char *x  =  "AAA\r\nBBB\r\nCCC\r\nDDD\r\nEEE\r\nFFF\r\nGGG\r\nHHH\r\nIII\r\nJJJ\r\nKKK\r\nLLL\r\nMMM\r\nNNN\r\nPPP\r\nQQQ\r\nRRR\r\nSSS\r\nTTT\r\nUUU\r\nWWW\r\nXXX\r\nYYY\r\nZZZ";


char *y = "john nonpharewewrretwuts fddddddddhdjdddddd                la";


char *insertlen(char *str,char *ch,int start){
	
	note.buff = str;
	note.buff2 = ch;
	note.i = 0;
	
	while(1){
	note.i++;
	note.buff++;
	if(note.i == start){
	//	printf("%c",*note.buff);
		note.i = 0;
		while(1){
			*note.buff = *note.buff2;
			note.buff++;
			note.buff2++;
			
			if(note.i == strlen(note.buff2)){
				break;
			}
			
		}
		break;
	}
	}
	

printf("%s",note.str_rom);
}

void main(){

	strcpy(note.str_rom,x);

	insertlen(note.str_rom,y,20);
	

	
}
