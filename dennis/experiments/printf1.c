





int myAtoi(char *str)
{
    int res = 0; // Initialize result
 int i ; 
    // Iterate through all characters of input string and
    // update result
    for ( i = 0; str[i] != '\0'; ++i)
        res = res*10 + str[i] - '0';
  
    // return result.
    return res;
}
  








void tostring(char str[], int num)

{

    int i, rem, len = 0, n;

 

    n = num;

    while (n != 0)

    {

        len++;

        n /= 10;

    }

    for (i = 0; i < len; i++)

    {

        rem = num % 10;

        num = num / 10;

        str[len - (i + 1)] = rem + '0';

    }

    str[len] = '\0';

}

int main()
{
	va_list 
	int temp;
	char *ptr = 0x80000000;
	char *str = "./,),(-*,(";
	temp = atoi(str);
//	char str1[10];
//	tostring(str,0x80000000);
	printf("%d",temp);
	
}
