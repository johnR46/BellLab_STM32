#include <stdio.h>
#include <string.h>

int main () {
   char str[50]; // 
   char dest[10];  // 5

   strcpy(str,"This is string.h library function");
   puts(str);
   
   memset(str,'0',7);
   
   
   
   printf("%s",str);
   return(0);
}
