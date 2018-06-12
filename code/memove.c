#include <stdio.h>
#include <string.h>

int main () {
  char src[4096];
  char dest[16][256];

  strcpy(src, "The Company runs official accounts on social mediassssss  understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourTheThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourTheThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourTheThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe");

  int i = 0, j = 0;
   int k = 1;
   printf("strlen is src = %d\n",strlen(src));
  
  for (i = 0; i < 16; i++) {
    for (j = 0; j < 256; j++) {
    
      dest[i][j] = src[k++];
     // printf("%d\n",k);
    }
  }
  
    //for(i = 0;i<16;i++){
    	printf("%c",dest[0][0]);
	


  return (0);
}
