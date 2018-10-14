#include<stdio.h>
#include<string.h>

int main()
{

    char a[] = "abcdefgh";
    char b[] = "abcdefgh";
    memmove(a+2,a,7);
    memcpy(b+2,b,7);
    printf("%s\n",a);
    printf("%s\n",b);
}
