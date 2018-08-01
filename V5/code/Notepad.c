#include<stdio.h>
#include<string.h>

// notepad struct 
int mapcur;
int seeCur;
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
  char str_buff[20];
  char str_rom[4096];
  char str_ram[20];

} note;
char *buttomnewline(char *str){
note.buff = str;
note.i = 0;

while(1){
	
	if(*note.buff == '\0'){
		//note.i = 0;
		while(1){
			*note.buff = '-';
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
note.cursor = 0;
note.setcursor = 0;
Enddisplay();
}

void printall(){
printf("\r\n -----------------------------------------------printall---------------------------------------------------\r\n");
printf("keycode = %d\r\n",note.keycode);
printf("str_ram = %s \r\n",note.str_ram);
printf("strlen ram = %d \r\n",strlen(note.str_ram));
printf("str_rom = %s \r\n",note.str_rom);
printf("strlen rom = %d \r\n",strlen(note.str_rom));
printf(" note.cursor  = %d \r\n",note.cursor);
printf(" note.setcursor  = %d \r\n",note.setcursor);
printf("note.shiftpoint = %d\r\n",note.shiftpoint);
printf("mapcursor = %d \r\n",mapcur);

printf("\r\n ---------------------------------------------endprintall---------------------------------------------------\r\n");

}


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


char *insert_rom(char *str, char ch, int setcur) { // insert mind str
  if (setcur == 0) {
    // str = aaa
    note.buff = &ch; // ch = A
    strcpy(note.strfirst, note.buff); // F = A
    strcpy(note.strlast, str); //  L =  aaa
    strcat(note.strfirst, note.strlast); // F = A + L = aaa = Aaaa
    strcpy(note.str_ram, note.strfirst); // Aaaa
    memset(note.strfirst, 0, strlen(note.strfirst));
    memset(note.strlast, 0, strlen(note.strlast));
  } else {

    note.buff = str;
    note.i = 0;
    memset(note.strfirst, '\0', 20);
    memset(note.strlast, '\0', 20);
    note.buff2 = note.strfirst;
    while (1) {
      *note.buff2  = *note.buff;
      note.i++;
      note.buff++;
      note.buff2++;

      if (note.i == setcur) {
        note.buff2 = note.strlast;
        while (1) {
          *note.buff2 = *note.buff;
          note.buff++;
          note.buff2++;
          if (*note.buff == '\0') {
            break;
          }

        }
        break;

      }


    }

    note.buff = &ch;
    strcat(note.strfirst, note.buff);
    strcat(note.strfirst, note.strlast);
    strcpy(note.str_rom, note.strfirst);





    memset(note.strfirst, 0, strlen(note.strfirst));
    memset(note.strlast, 0, strlen(note.strlast));

   


  }



}

void *endrightstring() {
  //  note.j = 0; // endright   start 0 - 20
  note.j = strlen(note.str_rom);
  memset(note.str_ram, 0, strlen(note.str_ram));
  printf("note.j = %d", note.j);
  copynstr(note.str_ram, note.str_rom + strlen(note.str_rom) - 20, 20);
  printf("\r\n-----------------------\r\n");
  printf("End Right : %s", note.str_ram);
  printf("\r\n-----------------------\r\n");

}


void *endleftstring() {

  memset(note.str_ram, '\0', strlen(note.str_ram));
  note.j = 0;
  printf("note.j = %d", note.j);
  copynstr(note.str_ram, note.str_rom + 0, 20);
  printf("\r\n-----------------------\r\n");
  printf("End Left : %s", note.str_ram);
  printf("\r\n-----------------------\r\n");
  // memset(note.str_ram, 0, strlen(note.str_ram));
}

void *midrightstring() {
  memset(note.str_ram, 0, strlen(note.str_ram));
  note.shiftpoint++;
  note.j = note.j + 20;
  copynstr(note.str_ram, note.str_rom + note.j, 20); //  start 20 - next +20 ->>>>>
  printf("note.j = %d", note.j);
  printf("\r\n-----------------------\r\n");
  printf(" Right is shifpoint = %d and str =  %s", note.shiftpoint, note.str_ram);
  printf("\r\n-----------------------\r\n");
  //memset(note.str_ram, 0, strlen(note.str_ram));




}
void *midleftstring() {
  memset(note.str_ram, 0, strlen(note.str_ram));
  note.shiftpoint--;

  note.j = note.j - 20;
  printf("note.j = %d", note.j);
  copynstr(note.str_ram, note.str_rom + note.j, 20); //  start 20 - next +20

  printf("\r\n-----------------------\r\n");
  printf(" Left is shifpoint = %d and str =  %s", note.shiftpoint, note.str_ram);
  printf("\r\n-----------------------\r\n");
  

}

void copynstr(char *str, char * ch, int size) { 
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
  if (setcur == 0 ) { // insert First str
 
    
    note.buff = &ch; // ch = A
    strcpy(note.strfirst, note.buff); // F = A
    strcpy(note.strlast, str); //  L =  aaa
    strcat(note.strfirst, note.strlast); // F = A + L = aaa = Aaaa
    strcpy(note.str_ram, note.strfirst); // Aaaa
    memset(note.strfirst, 0, strlen(note.strfirst));


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

void *addstring(char ch, int index) { // case 1 add right string
  //  add string in left to right
  note.str_ram[index] = ch;
  note.cursor++;
  note.setcursor++;


}
void *addstring2(char ch, int index) { // case 1.2 add middle string
  insertString(note.str_ram, ch, index);
  note.cursor++;
  note.setcursor++;
  if (note.setcursor >=  note.cursor) {
    note.setcursor = note.cursor;
  }


}

void *delstring(char ch, int index) { // case 2  delete right to left
  note.str_ram[index] = ch;
  note.cursor--;
  note.setcursor--;

}
void *delstring2(char ch, int index) { // case 2.1  delete middle to left string
  deleteString(note.str_ram, ch, index);
  note.cursor--;
  note.setcursor--;
  if (note.setcursor >=  note.cursor) {
    note.setcursor = note.cursor;
  }

}


void Enddisplay() {
  
  strcat(note.str_rom,note.str_ram); // move string str_ram to str_rom
  strcat(note.str_rom,"\r\n");

  note.cursor = 0; // clear cursor
  note.setcursor = 0;
  note.shiftpoint = strlen(note.str_rom)/20;      // shifpoint =  str/20
  note.j = strlen(note.str_rom);  //  reset shiftLeftstr
  memset(note.str_ram, '\0', strlen(note.str_ram)); // clear str_ram

}
void newline() {
  if (note.cursor == 18  && seeCur != 1 && note.setcursor >= note.cursor ) { // normal newline 
  Enddisplay();
  }

  if((note.setcursor < note.cursor ) && (note.cursor > 18)){  // insert newline 


  }


}



void notepad(int setcursor, char str, int keycode) {
  newline();
  switch (keycode) {
    //  case 1 add string is Left to Right
    case 1 :
      if (setcursor >= note.cursor) {
        addstring(str, note.cursor);
        printf("\r\n - - - cursor : %d - - - \r\n", note.cursor);
        printf("%s", note.str_ram);

      }
      else if (setcursor < note.cursor) { // insert string befor lastcursor  by setcursor
        addstring2(str, setcursor);
        printf("\r\n - - - cursor : %d - - - \r\n", note.cursor);
        printf("%s", note.str_ram);
      }
      break;  // end case 1
    case 2 :
      if (setcursor >= note.cursor && note.cursor > 0 ) { // delete string in right to left
        delstring(str, note.cursor);
        printf("\r\n - - - cursor : %d - - - \r\n", note.cursor);
        printf("%s", note.str_ram);
      }
      else if (setcursor < note.cursor && note.cursor > 0  ) { // insert string befor lastcursor  by setcursor
        delstring2(str, setcursor);
        printf("\r\n - - - cursor : %d - - - \r\n", note.cursor);
        printf("%s", note.str_ram);
      }

      break;
    case 3:   // shift Left
      if (note.shiftpoint == 0) {
        printf("\r\n-----------------------\r\n");
        printf("str_rom  < 0");
        printf("\r\n-----------------------\r\n");
      }
      if (note.shiftpoint == 1) { // End Left   EndLeft = 1 << str_rom >> EndRight  = strlen(str_rom)

        endleftstring();


      }
      if (note.shiftpoint > 1) {
        midleftstring();
      }
      break;

    case 4:   // shift  Right

      if (note.shiftpoint == 0) {

        printf("\r\n-----------------------\r\n");
        printf("str_rom  < 20");
        printf("\r\n-----------------------\r\n");

      }

      else  if (note.shiftpoint == strlen(note.str_rom)/20) { // end right
        endrightstring();
      }
      else if (note.shiftpoint != strlen(note.str_rom)/20) {
        midrightstring();
      }



      break;


    default : printf("\r\n ------------ error -------------\r\n");
      break;
  }
}

void main(){
	
while(1){
	printf("\r\n Enter text : ");
	scanf(" %[^\n]%*c",&note.ch);
	printf("\r\n Enter setcursor : ");
	scanf("%d",&note.setcursor);
	printf("\r\n Keycode :");	
	scanf("%d",&note.keycode);
	notepad(note.setcursor,note.ch,1);
}	
	
	
}
