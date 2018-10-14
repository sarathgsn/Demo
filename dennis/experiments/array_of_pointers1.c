int main()
{
	char *p[4] = {"hello","world","gloebal","edge"};
	int *pt[4]  = {100,200,300,400};
	int i;
	int a = 100, b = 200, c = 300, d = 400;
	pt[0] = &a;
	pt[1] = &b;
	pt[2] = &c;
	pt[3] = &d;
	for (i = 0; i < 4; i++)
	{
	printf("%s\n",p[i]);	
	printf("%d\n",*pt [i]);	
	}
	
}
