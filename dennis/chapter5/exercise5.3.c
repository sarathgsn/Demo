#include<stdio.h>


#define SIZE 100

char* mystrcat (char *p, char *s)
{
    while( *p != '\0')
       p++;
    while( (*p++ = *s++ )  != '\0')
        ;
}





int main(void)
{
    char ptr[SIZE] = "GLOBAL";
    char str[SIZE] = "EDGE";


    mystrcat(ptr, str);
   
    printf("\n %s  \n", ptr);

    return 0;
}
