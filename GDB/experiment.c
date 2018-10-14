#include<stdio.h>
char *str;

struct abc {
	int a;
	char *ptr;
	int c;
};

void temp1(int *ptr, int *temp)
{
	struct abc s ;
	s.a = 100;
	s.ptr ="hello";
	s.c = 500;
	*ptr = 1000;
	*temp = 2000;
	printf("%d\n",*ptr);
}






void fun(int *ptr, int *temp)
{
	*ptr = 100;
	*temp = 200;
	temp1(ptr, temp);
	printf("%d\n",*ptr);

}






int main()
{
  int x = 10, y = 20, z = 30;

  if ( x < y)
	printf("x lessthan y\n");
  else 
	printf("false\n");

	switch(3)
	{
		case 1: while ( x < 20)
			{
				printf("in case 1\n");
		case 2: if ( x == 15)
				printf("in case 2\n");
			x++;
			}
			break;
		default:
			printf("default\n");
			break;
	}
	
	fun(&x,&y);
	printf("%d %d\n",x ,y);
} 
  

