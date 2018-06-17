#include<stdio.h>
#include<string.h>
char  BYTE_WRITE[] = {0x57,0xab,0x3c,0x29,0x00}; // >>0x57,0xab, 0x3c, dataLength,0x00 <<
char WR_REQ_DATA[] 	= {0x57,0xAB,0x2D}; // 57,AB,2D,Data

// data input now user
char Data[] = "HOLA  ESTOS SON NUEVOS DATOS EN LA MEMORIA";

// convert to hex 









void main(){
	//printf("%s\n",Data);
	
	sprintf(WR_REQ_DATA,"%s",Data);
	
//	strcat(WR_REQ_DATA,Data);
	printf("%s",WR_REQ_DATA);
}
