#include<stdio.h>

#define SIZE 100


char* strncopy(char *dst,  char *src, int n)
{
    char *temp = dst;
    while (n-- && (*dst++ = *src++))
        ;
    *dst = '\0';
    return temp;

}


int main(void) 
{
    char src[SIZE];// = "global";
    char des[SIZE];
    char *temp;
    int len;
    
    temp = strncopy(des, src, 3);
    printf("\n %s  \n", temp);


    return 0;
}
