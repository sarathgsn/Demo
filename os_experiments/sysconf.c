#include <unistd.h>
#include <stdio.h>

int main(void)
{
	printf("max files  %lu\n",sysconf(_SC_OPEN_MAX));
	return 0;
}
