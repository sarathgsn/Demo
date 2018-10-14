#include<stdio.h>


int main(void) 
{
    int line;
    char **ptr;
    line = getline(ptr, 0, stdin);
    printf("\n %d  \n", line);

    return 0;

}
