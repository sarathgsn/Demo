#include<stdio.h>

int main()
{

	char *ptr = (const char[]){"abc"};
	if(ptr == "abc") {
	printf("gggg");
	}
}
