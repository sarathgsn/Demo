#include<stdio.h>

int main(void)
{
    int a[10] = { 1,2,3,4,5,6,7,7,8};
    int *ptr = &a[5];
    int *str = &a[2];
    if ( ptr > str)
      printf("\n ptr  greater \n");
    else 
        printf("\n str greater  \n");

    return 0;

}

