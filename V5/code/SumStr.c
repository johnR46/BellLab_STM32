#include <stdio.h>  
#include <string.h>  


#define  notepad_y 20
#define notepax_max 205


char Dimen2[notepax_max][notepad_y] = {"john nonphala\r\n","sursak sinjlern\r\n","omg\r\n"};
char Dimen1[notepad_y*notepax_max] = ""; //initalise so safe to pass to strcat
    
    
void sumStr(){
	
	 int i;
    for(i = 0; i<notepax_max;i++)
    {
       strcat(Dimen1,Dimen2[i]);
    }
    printf("%s",Dimen1);
    
   
    
}
int main()
{
  
    sumStr();
 
    return 0;   
}
