#include<stdio.h>

int main()
{
	int a[2] = {1,2};
	int b[2] = {1,2};
	int i , j , m = 4, n= 7;
	for(i = 0; i < n; i++) {
		for(j = 0; j < m; j++) {
			if(a[i] == b[j]) {
			     //jump to printf statement
			}

			printf("inner loop\n");

		}

		printf("Outer loop\n");

	}
	printf("out of loops\n");
}
