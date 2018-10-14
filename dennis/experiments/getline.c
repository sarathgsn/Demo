#include <stdio.h>


int main()
{
    char buffer[32];
    char *b = (char *) malloc(10);
    int bufsize = 32;
    int characters;

    printf("Type something: ");
    characters = getline(b,&bufsize,stdin);
    printf("%d characters were read.\n",characters);
    printf("You typed: '%s'\n",b);

    return(0);
}
