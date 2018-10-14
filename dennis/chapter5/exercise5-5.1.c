#include<stdio.h>

#define SIZE 100


void  mystrncat(char *src, char *des, int n)
{
    while(  *src != '\0')
        src++;
    while( (*src++ = *des++ ) && n--)
        ;


}




int main(void) 
{
    char src[SIZE] = "GLOBAL";
    char des[SIZE] = "edge";


    mystrncat(src, des, 3);

    printf("\n after cancatination %s  \n", src);

    return 0;

}
