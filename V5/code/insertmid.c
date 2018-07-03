#include<stdio.h>

#include<string.h>
char ss[20] = "john nonphala";
char ch = 'A';





char *insert(char *str, char ch, int setcur) { // insert mind str
  char *buff; // buffer  = index *buffer = value
  // %s = buff
  // %c = *buff;
  buff = str; // buffer index 0
  buff += setcur;
  *buff = ch;
}

char *insertString(char *str, char ch, int setcur) {
  char *buff; // buffer  = index *buffer = value
  int i = 0;
  buff = str;
  char strfirst[20]; // strF
  memset(strfirst, '\0', strlen(strfirst)); // clear str
  char strlast[20];  // strL
  memset(strlast, '\0', strlen(strlast));

  while (1) {  // separate str to stfF and strLast
    strfirst[i]  = *buff;  // strf = str index 0 - index setcur 
    i++;
    buff++;
    if (i == setcur ) {
    //  strfirst[i] = ch;

      i = 0;
      while (1) {
        strlast[i] = *buff;       // strl  = str index setcur - strlen(str)
        i++;
        buff++;
        if (i == setcur + strlen(str)) {
            memset(str, '\0', strlen(str));
         	//strcat(strfirst,strlast);
			//strcat(str,strfirst);
   		    buff = strfirst;
            i = 0;
            while (1) {
            str[i] = *buff;
            i++;
            buff++;
            if (i == strlen(strfirst) ) {
              buff = strlast;
              i = 0;
              while (1) {
            	str[i+strlen(strfirst)] = *buff;
                i++;
                buff++;
                if (i == strlen(strlast) ) {
                  break;
                }
              } 

              break;
            }

          } 
          break;
        }


      }



      break;
      
    }
    
    
  }
  
  printf("\r\nstrF = %s\r\n",strfirst);
  printf("\r\nstrL = %s\r\n",strlast);
  

}




int  main() {
  printf(" str = %s \n", ss);
  printf("setcur = %d\n", 7);
  insertString(ss, ch, 7);
  
  
  printf("%s",ss);


  return 0;
}
