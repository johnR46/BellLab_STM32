#include<stdio.h>
#include<string.h>

int BYTE_LENGHT[2]; // length data,0x00
int WR_REQ_DATA[] 	= {0x57,0xAB,0x2D}; // 
char DataToCH376[] = "HOLA  ESTOS SON NUEVOS DATOS EN LA MEMORIA"; // data
void main(){


int i = strlen(DataToCH376);

//printf("i = %d\n",i);

BYTE_LENGHT[0] = i;
BYTE_LENGHT[1] = 0;


for( i = 0;i<sizeof(BYTE_LENGHT )-6;i++){
	printf("is %d in %d \n ",BYTE_LENGHT[i],i);
}
	
}
