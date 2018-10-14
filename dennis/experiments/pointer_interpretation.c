
#include <stdio.h>


char *n;

int main()
{
	char *h = 0;
	char *p = "dupisio";
	char s[8] = "subtle";
	p = &s[0];
	*p = 'p';
	p = p + 4;
	p = n;
	*p = n;
	printf("%s\n",++p);
}
