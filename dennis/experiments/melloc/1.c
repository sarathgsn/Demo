#include<stdio.h>

#include<stdlib.h>
int main(void)
{
//	int a = 10;
//	char *q = &a;
	int  *p =(int  *) malloc(32);
	printf("%x\n",p);
	if(p){
	printf("%d",*(p-2));
}
//	printf("%", *q);
//	printf("%d",*(p-8));
}
