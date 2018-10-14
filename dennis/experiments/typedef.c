
typedef int (*INTARRAY)[10];
typedef int INTARR[10];
int main()
{
	INTARRAY a;
	INTARR b = {1,2,3,4,5,6};
	a = &b;
	printf("%d\n",sizeof(a));
	b[5] = 9;
	printf("%d\n",*(*a+5));
}

