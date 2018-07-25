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
  char str_rom[4096];
  char str_ram[40];
  char 
 

} note;


char *x = "zxcvbnm,,./asdfghjkl;'qweertyuiop'"; // 34 = 17/2 
char y[17];
char z[17];


char *insert_rom(char *str,char ch,int setcursor){

	note.buff = str;
	note.i = 0;
	memset(note.strfirst,'\0',20);
	memset(note.strlast,'\0',20);
	
	note.buff2 = note.strfirst;
	
	
	while(1){
		*note.buff2  = *note.buff;
		note.i++;
		note.buff++;
		note.buff2++;
		
		if(note.i == setcursor){
			note.buff2 = note.strlast;
			while(1){
				*note.buff2 = *note.buff;
				note.buff++;
				note.buff2++;
				if(*note.buff == '\0'){
					break;
				}
				
			}
			break;
		
			}
	
			
		}
		
		
		
		
				
	
	
	printf("str F  = %s\n",note.strfirst);
	printf("str L  = %s\n",note.strlast);
	

	
}


void main(){
	
	
	
	insert_rom(x,'Z',2);
	


	


	
}

