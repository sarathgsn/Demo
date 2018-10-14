#include<stdio.h>

int main(void) 
{
    extern acc[10];// = { 10,11,22,33};
    printf("\n %d  \n",acc[0]);
    return 0;
}
