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

char *insertsetString(char *str, char *ch, int start) {

  note.buff = str;
  note.buff2 = ch;
  note.i = 0;

  while (1) {
    note.i++;
    note.buff++;
    if (note.i == start) {
      //  printf("%c",*note.buff);
      note.i = 0;
      while (1) {
        *note.buff = *note.buff2;
        note.buff++;
        note.buff2++;

        if (note.i == strlen(note.buff2)) {
          break;
        }

      }
      break;
    }
  }


  //printf("%s",note.str_rom);
}




void main(){
	
	strcpy(note.str_ram,"john nonphala Sura\r\n");
	
	
	strcat(note.str_rom,note.str_ram);
	memset(note)
	
	
	printf("%s",note.str_rom);

	
}

