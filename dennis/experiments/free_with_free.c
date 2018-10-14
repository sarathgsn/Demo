#include<stdio.h>
#include<stdlib.h>

int main()
{
	char *p = malloc(100);
	realloc(p,0);
}
