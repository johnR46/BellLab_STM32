#include <stdio.h>
#include <string.h>

int main () {
  char src[4096];
  char dest[256];
  int start = 0;
  int end = 4096;

  // memset(dest, '\0', sizeof(dest));
  strcpy(src, "The Company runs official accounts on social mediassssss  understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourTheThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourTheThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourTheThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe Company runs official accounts on social media by understanding that social media is a place for communication based on a tie among individuals and that information is disclosed to the public and cannot be completely eliminated once dispatched, encourThe");
  printf("strlen src is %d\n", strlen(src)); // strlen(src) =  4096

  while (end != 0) {
  	memset(dest, '\0',1);
    strncat(dest, src + start+256, 256  );
    printf("start :%d\n", start);
    printf("end :%d\n", end);
    printf("strlen dest is %d\n", strlen(dest));
    printf("dest :%s\n", dest);
    memset(dest, '\0',1);

    start = start + 256;
    end -= 256;

 }

  return (0);
}
