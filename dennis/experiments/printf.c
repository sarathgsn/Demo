char *itoa1(char *buffer, int  len, unsigned input, int base) { 
    static const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *pos = buffer;
    if (input >= base)
        pos = itoa1(buffer, len, input/base, base);

    if (pos-buffer < len-1)
        *pos++ = digits[input % base];
    return pos;
}



int a = 10;
int main()
{

	char *ptr;
	ptr = itoa1(str,10,0x80000000 , 16);
	printf("%s",ptr);


}
