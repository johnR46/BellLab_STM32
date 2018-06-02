#include<stdio.h>
#include<string.h>
int BYTE_WRITE[] = {0x57,0xab,0x3c,0x29,0x00}; // >> 0x3c, dataLength,0x00 <<
int WR_REQ_DATA[] 	= {0x57,0xAB,0x2D}; // 57,AB,2D,Data
char DataToCH376[] = "HOLA  ESTOS SON NUEVOS DATOS EN LA MEMORIA";

char ss[] = {};
int j = 0;
int i = 0;
void DataToWrite() {
 
  printf("len ch is %d\n",strlen(DataToCH376));

  for(i = 0; i < strlen(DataToCH376); i++){
   ss[i] = (int)DataToCH376[i];
   printf("%d\n",i);
  }
 
}


void main(){


DataToWrite();

	printf("len ss is %d\n",strlen(ss));
	for( i = 0;i <strlen(ss); i++ ){
	printf("%c",ss[i]);
	}
	
		
}
