#include<stdio.h>


int
isprintf( int c)
{

	return ((c >= ' ' && c <= '~') ? 1 : 0);
}







int main()
{

 printf("%d\n",isprintf('\n'));


}
