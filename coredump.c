#include<stdio.h>


void  function3(int var, char *str)
{ 
	str =NULL;
	printf("var ==%d\n", var);
	
//	funtcion2("function2", 10);
	
	printf(" str ===%s", *str);
}







void  function2( char *str, int var)
{
	printf("var ==%d\n", var);
	
	function3(300,"function3");
	
	printf(" str ===%s", str);
}







void  function(int var, char *str)
{
	printf("var ==%d\n", var);
	
	function2("function2",200);
	
	printf(" str ===%s", str);
}




int main(void) 
{
    int *ptr;
    function(100,"funtion1");
//    printf("\n  %d \n", *ptr);

    return 0;
}
