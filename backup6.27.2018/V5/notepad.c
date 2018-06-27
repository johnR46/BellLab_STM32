#include<stdio.h>
#include<string.h>


// struct form notepad
struct  {
  int cursor; // auto gen
  int setcursor;  // by user
  int keycode;
  char str_rom[4096];
  char str_ram[20];


} note;

char strmiddle[] = "john   Nonphala";



void notepad(int cursor, int setcursor, char *str, int keycode ) {
  char strfirst[10];
  char strlast[10];
  
  switch (keycode) {
    case 1 : if(setcursor>=cursor){ // sum strlast ++
      note.str_ram[cursor] = str;
      cursor++;
      printf("%s", note.str_ram);
  }
  
  if(setcursor < cursor ){ // insert str                     
  
                           	
  	
  }
   printf("%s",strfirst);
  memset(strfirst,'\0',strlen(strfirst));
  memset(strlast,'\0',strlen(strlast));
	  break;



    default :    printf("\r\nerror\r\n");
      break;

  }
}


void main() {
  int i = 0;

  while (1) {
    printf("\r\n------------------------------\r\n");
    printf("%d\n", i);
    printf("str:    %c", strmiddle[i]);

    printf("\r\n------------------------------\r\n");


      printf("\r\n Enter setcursor : ");
      scanf("%d",&note.setcursor);

    printf("\r\n Enter keycode : ");
    scanf("%d", &note.keycode);

    printf("\r\n .... process notepad .... \r\n");
    notepad(i,note.setcursor+1, strmiddle[i], note.keycode);
    i++;
  }





}
