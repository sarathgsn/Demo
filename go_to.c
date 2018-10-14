#include <stdio.h>

int
main()
{
    int i = 0;
    if (i < 2) {
        if (i == 0) {
            goto statement;
        }else if( i == 1) { goto lable;}

i++;
    }



statement:
    printf("i value = %d\n", i);
    
printf("second printf) \n");
	return 0;
lable:
	printf("in lable\n");
return 0;
}
