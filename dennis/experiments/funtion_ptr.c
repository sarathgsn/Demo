typedef int (*fun)(void);

int main()
{
	fun f1 = main;
	printf("%d\n",sizeof(f1));
	printf("%d\n",sizeof(while));
}
	
