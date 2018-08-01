#include<stdio.h>
#include<string.h>
#define notepad_max_X 205
#define notepad_max_y 20

char str1[notepad_max_X][notepad_max_y] = {"john nonphala\r\n","sursak sinjlern\r\n","omg\r\n"};
char str2[notepad_max_X*notepad_max_y];  // 4100 
int i;
char *buff;
char buff2;
char *convertArrayStr_2D_to_1D(){
	
    // normal 
	 for(i = 0; i<notepad_max_X;i++)
    {
       strcat(str2,str1[i]);
    }
        printf("%s",str2);
	
	
	// pointer 
    
    
   


}

void main(){

convertArrayStr_2D_to_1D();

}
