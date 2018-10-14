#include<stdio.h>




int main(void)
{
	unsigned long pattern;
	unsigned long offset;
	unsigned long num_words;
	unsigned long anti_pattern;
	unsigned long temp;
	unsigned long *addr, *start, *end;

	start = (unsigned long *)malloc(20);
	end = start + 20;
	num_words = ((unsigned long)end - (unsigned long )start)/sizeof(unsigned long) + 1;
	for (pattern = 1, offset = 0; offset < num_words; pattern++, offset++) {
		start[offset] = pattern;
	}

	/*
	 * Check each location and invert it for the second pass.
	 */
	for (pattern = 1, offset = 0; offset < num_words; pattern++, offset++) {
		temp = start[offset];
		if (temp != pattern) {
			printf ("\nFAILURE (read/write) @ 0x%.8lx:"
					" expected 0x%.8lx, actual 0x%.8lx)\n",
					(unsigned long)&start[offset], pattern, temp);
			return 1;
		}

		anti_pattern = ~pattern;
		start[offset] = anti_pattern;
	}

		start[6] = 100; 
	/*
	 * Check each location for the inverted pattern and zero it.
	 */
	for (pattern = 1, offset = 0; offset < num_words; pattern++, offset++) {
		anti_pattern = ~pattern;
		temp = start[offset];
		if (temp != anti_pattern) {
			printf ("\nFAILURE (read/write): @ 0x%.8lx:"
					" expected 0x%.8lx, actual 0x%.8lx)\n",
					(unsigned long)&start[offset], anti_pattern, temp);
			return 1;
		}
		start[offset] = 0;
	}
}

