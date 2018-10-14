#include <stdio.h>

int main()
{
    int c;

    while ( (c=getchar()) != EOF) {

        if (c == '\\') {
            putchar('\\');
            putchar('\\');
        }
        if (c == '\t') {
            putchar('\\');
            putchar('t');
        }
        if (c == '\b') {
            putchar('\\');
            putchar('b');
 
        }
            putchar(c);        
    }
    return 0;
}
