#include<stdio.h>
unsigned int num_hex_digits(unsigned int n) {
    int ret = 0;
    while(n) {
        n >>= 4;
        ++ret;
    }
    return ret;
}
void main(){
	
	printf("%d",num_hex_digits(0x6));
}
