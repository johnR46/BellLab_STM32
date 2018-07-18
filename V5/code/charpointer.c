#include<stdio.h>
#include<string.h>

struct  {
  int cursor; // auto gen
  int setcursor;  // by user
  int keycode;
  int i;
  int j;
  int state;
  int shiftpoint;
  char *buff; // buffer  = index *buffer = value
  char *buff2;
  char strfirst[20]; // strF
  char strlast[20];
  char ch;
  char str_buff[20];
  char str_rom[4096];
  char str_ram[20];
  char Left[20];
  char Right[20];


} note;


void *addstring(char *str,char ch, int index) { // case 1 add right string
  //  add string in left to right
  note.buff = str;
  while(*note.buff!='\0'){
  	note.buff++;
  }
  *note.buff  = ch;
  
 // note.str_ram[index] = ch;
  note.cursor++;
  note.setcursor++;
 /*
  printf(" \r\n str_ram \r\n");
  printf("%s", note.str_ram);
  printf(" \r\n str_ram \r\n");
  printf("\r\n -------------\r\n");
  printf("cursor = %d", note.cursor);
  printf("\r\n -------------\r\n");
  
  */

}

char ch[20]  = "john nonphala";


void main(){
	printf("strlen  : %d",strlen(ch));

	

	
}

