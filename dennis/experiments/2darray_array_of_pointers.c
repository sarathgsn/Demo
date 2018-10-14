char a[4][6] = {"head","art","sharp","drive"};
char *b[4] = {"head","art","sharp","drive"};

int main()
{
	int i = 0;
	
	for( i = 0 ; i < 4 ; i ++ )
	{
	printf("a[%d] = %d , b[%d] =%d\n", i, sizeof(a[i]),i ,sizeof(b[i]));
	}
	for( i = 0 ; i < 4 ; i ++ )
	{
	 printf("a[%d] = %d , b[%d] =%d\n", i,strlen(a[i]),i, strlen(b[i]));
	}
	for( i = 0 ; i < 4 ; i ++ )
	{
		printf("a[%d] = %s, b[%d] = %s\n",i,a[i],i,b[i]);
	}
}
