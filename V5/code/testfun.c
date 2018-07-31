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
char *deleteString(char *str, char ch, int setcur) { // delete str is setcur
  //  memset(str + strlen(str) - 1,'\0',1);
  note.buff = str;
  note.i = 0;
  /*    div  strF/index 0 + index(setcur)   strL = /(intdex setcur + strlen(str) */
  while (1) {  // separate str to stfF and strLast
    note.strfirst[note.i]  = *note.buff;  // strf = str index 0 - index setcur
    note.i++;
    note.buff++;
    if (note.i == setcur) {
      note.i = 0;
      while (1) {
        note.strlast[ note.i] = *note.buff;       //
        note.i++;
        note.buff++;
        if ( note.i == setcur + strlen(str)) {
          break;
        }
      }
      break;
    }
  }
  memset(note.strfirst + strlen(note.strfirst) - 1, '\0', 1);
  strcat(note.strfirst, note.strlast);
  strcpy(note.str_ram, note.strfirst);
  memset(note.strfirst, 0, strlen(note.strfirst));
  memset(note.strlast, 0, strlen(note.strlast));
}

char *insertString(char *str, char ch, int setcur) {
  // char *buff; // buffer  = index *buffer = value
  if (setcur == 0) { // insert First str
    // str = aaa
    note.buff = &ch; // ch = A
    strcpy(note.strfirst, note.buff); // F = A
    strcpy(note.strlast, str); //  L =  aaa
    strcat(note.strfirst, note.strlast); // F = A + L = aaa = Aaaa
    strcpy(note.str_ram, note.strfirst); // Aaaa
    memset(note.strfirst, 0, strlen(note.strfirst));
    memset(note.strlast, 0, strlen(note.strlast));
  }
  else {
    note.buff = str;
    note.i = 0;
    /*    div  strF/index 0 + index(setcur)   strL = /(intdex setcur + strlen(str) */
    while (1) {  // separate str to stfF and strLast
      note.strfirst[note.i]  = *note.buff;  // strf = str index 0 - index setcur
      note.i++;
      note.buff++;
      if (note.i == setcur) {
        note.i = 0;
        while (1) {
          note.strlast[ note.i] = *note.buff;       //
          note.i++;
          note.buff++;
          if ( note.i == setcur + strlen(str)) {
            break;
          }
        }
        break;
      }
    }

    note.buff = &ch;
    strcat(note.strfirst, note.buff);
    strcat(note.strfirst, note.strlast);
    strcpy(note.str_ram, note.strfirst);
    memset(note.strfirst, 0, strlen(note.strfirst));
    memset(note.strlast, 0, strlen(note.strlast));

  }
}

void main(){
	
	//insertString("abc",'x',3);
	
	deleteString('')
	printf("%s",note.str_ram);
	
}

