#include <stdio.h>


 void foo() __attribute__((noreturn));


int foo()
{
	int n;
        if ( n > 0 )
                return 1;
        else
                return 0;
}
void main()
{
	int vari __attribute__((noreturn));
	printf("hello");
	foo();
}
