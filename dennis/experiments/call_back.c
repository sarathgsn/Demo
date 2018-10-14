#include<stdio.h>
#if 0
void populate_array(int *array, size_t arraySize, int (*getNextValue)(void))
{
    int i;
    for (i=0; i<arraySize; i++) {
        array[i] = getNextValue();
}
}

int getNextRandomValue(void)
{ 
    printf("getNextRandomValue\n");
    return rand();
}

int main(void)
{
    int myarray[10];
    populate_array(myarray, 10, getNextRandomValue);
}
#endif 


/*function poiters comparision*/

fun(int a, int b){
printf("in fun");
}

int main()
{
      int (*ptr)(int , int) = NULL;
       ptr = fun;
	// ptr = &fun; /*assigning in proper way*/
	if ( ptr == fun ) 
		printf("true\n");
	else
		printf("else\n");
}

/*assigning a function in two ways ptr = fun ;and ptr =&fun;*/
/* calling is also in two ways ptr(12,12); or (*ptr)(12,12); */


/* array of function pointers 

1:::: int (*ptr[10])(int , int) = {NULL};
2:way
typedef int (*pt2Function)(float, char, char);
pt2function ptr1[10] = {NULL};
assigning address
// assign the function's address - 'DoIt' and 'DoMore' are suitable functions
   // like defined above in 2.1-4
   ptr[0] = ptr1[1] = &DoIt;
   ptr[1] = ptr1[0] = &DoMore;

// calling a function using an index to address the function pointer
   printf("%d\n", funcArr1[1](12, 'a', 'b'));         //  short form
   printf("%d\n", (*funcArr1[0])(12, 'a', 'b'));      // "correct" way of calling
   printf("%d\n", (*funcArr2[1])(56, 'a', 'b'));
   printf("%d\n", (*funcArr2[0])(34, 'a', 'b'));
*/

