#include <stdio.h>
#include <string.h>

int main () {
   char src[4095];
   char dest[15][255];
  int start = 0;
  int limit = 255;
  int end = 4095;
 
  // memset(dest, '\0', sizeof(dest));
   strcpy(src, "The Company runs official accounts on social mediassssss  understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourTheThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourTheThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourTheThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe");

while(end>=0){
   memset(dest, '\0', strlen(dest));
   strncpy(dest,src+start,start+limit);
   printf("dest :%s\n", dest);
   printf("strlen dest is %d\n",strlen(dest));
   printf("start :%d\n", start);
   printf("end :%d\n", end);
   memset(dest, '\0', strlen(dest));

   start+=255;
   end-=255;
   	
  }
   return(0);
}
