#include<stdio.h>
#include<string.h>
struct  {
  int cursor; // auto gen
  int setcursor;  // by user
  int cursor_rom;
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
  char str_buff[40];
  char str_rom[4096];
  char str_ram[40];
} note;

char *buttomnewline(char *str){
note.buff = str;
note.i = 0;

while(1){
	
	if(*note.buff == '\0'){
		//note.i = 0;
		while(1){
			*note.buff = 32;
			note.buff++;
			note.i++;
			if(note.i == 18){
				break;
			}
		}
		break;
		
	}
	//printf("\n%d\n",note.i);
	note.buff++;
	note.i++;
	
}

note.cursor += 	note.i;

}


int  main(){
	
	strcpy(note.str_ram,"wefrasdfglikj");
	
	
	buttomnewline(note.str_ram);
	
	printf("%s",note.str_ram);
	printf("\n%d",strlen(note.str_ram));
	
printf("\n%d",note.cursor);
	
	
	
return 0;	
}
