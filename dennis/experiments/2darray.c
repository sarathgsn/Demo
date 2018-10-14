int main()
{
	int a[10][2] = {{1,2},{3,4},{5,6}};
	
	printf("%p\n",a );
	printf("%p\n",&a);
	printf("%p\n",*a);
	printf("%p\n",a+1);
	printf("%p\n",&a+1);
	printf("%p\n",*a+1);
	
}
