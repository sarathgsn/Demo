#include<stdio.h>
int main(void) 
{
    int a;
    int *p;
    printf("\n  %d \n", sizeof(&a));
    printf("\n  %d \n", sizeof(a));
    return 0;
}
