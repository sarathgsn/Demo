char *cstr = "hello";
char *sstr;
char *dstr;

int main()
{
	sstr = malloc(10);
	printf("0x%08x\n",sstr);
	sstr = "world";
	printf("0x%08x\n",sstr);

	dstr = malloc(10);
	printf("0x%08x\n",dstr);
	strcpy(dstr,"gloabl");
	printf("0x%08x\n",dstr);
}

