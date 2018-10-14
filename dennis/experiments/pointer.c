#include<stdio.h>


int main()
{	int *ptr;
	char buf[64];
		buf[39] = 8;
	ptr =(int *) buf;
	int x = 0x5042;
	char *p = (char *)&x;
	
 	printf("%p\n",(void *)buf[39]);
 	printf("%p\n",ptr+9);
	printf("%d\n",*(ptr+9));
}
