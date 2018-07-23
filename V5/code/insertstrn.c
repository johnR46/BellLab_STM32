#include<stdio.h>
#include<string.h>

struct{
int cursor;
int i;
char *buff;
char *buff2;

char str_ram[40];
char str_rom[4096];
}note;

char *s = "john nonpala";
char *y;

char *copynstr(char *str, char * ch, int size) { // strbuff
  note.buff2 = str;
  note.buff = ch; // copy ch to str
  note.i = 0;
  while (1) {
    *note.buff2 = *note.buff;
    note.buff++;
    note.buff2++;
    note.i++;
    if (note.i == size) {
      break;
    }
  }
}

void main(){


copynstr(y,s,5);
printf("%s",y);
}
