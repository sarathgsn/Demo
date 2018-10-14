void fun()
{
	printf("in fun\n");
}
void fun1()
{
	printf("in fun \n");
}
void fun2()
{
	printf("in fun 2\n");
}
void fun3()
{
	printf("in fun 3\n");
}



typedef void (*function)(void);

void demo(function **invoke)
{
	function **hello = invoke;
		printf("%p\n",invoke);
		printf("%p\n",(hello)());
	//(*invoke)();
	int i = 0;
	for(i = 0; i < 3; i++)
	{
	}
}
int main()
{
//	function **invoke;
	function *api[] = {
	fun,fun1,fun2,fun3 };
	printf("%p\n",fun);
//	invoke = api;
//	(*invoke)();
	demo(api);	

}
