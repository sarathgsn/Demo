char str[2][6] = {"hello world"};
char str1[2][20] = { "global","edge"};
char str2[][10] = {"hyper active"};
char str3[][20] = {"sarath","babu"};

int main()
{
	printf("%s\n",str);
	printf("%c\n",*(*(str+0)+6));
	printf("%c\n",*(*(str+0)+7));
	printf("%c\n",*(*(str+0)+9));
}
