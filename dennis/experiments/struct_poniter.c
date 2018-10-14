#include<stdio.h>
#pragma pack (2)
struct a 
{
	int b;
	int a;
	char c;
};
int main()
{
//	struct a *b = malloc(sizeof(struct a));
//	(*b).a = 10; //b->a = 10;
//	(*b).b = 20;
	struct a b = {.a = 10};

	printf("%d\n",b.b);
	printf("%d\n",b.a);
	printf("%d\n",b.c);
}
	
