/*#include<stdio.h>


int main(void) 
{
    int x = 0x12;

    char c = (char)x;

    printf("\n %d  \n", c);
    return 0;

}
#include <stdio.h>
int main() 
{
    unsigned int i = 1;
    char *c = (char*)&i;
    if (*c)    
        printf("Little endian");
    else
        printf("Big endian");
//    getchar();
    return 0;
}*/
#include<stdio.h>
int main(void) 
{
    int x  = 12345678;
    int *p; 
       p = &x;
       char *ptr;
       ptr = (char *)&x;
    printf("\n *ptr = %d \n", *ptr);

    return 0;
}
