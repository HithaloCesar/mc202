#include <stdio.h>

void print_even(int max) {
	int i;
	for (i = 0; i != max + 1; i += 2) {
		printf("%d\n", i);
	}
}

int main(void) {
	int max;
	scanf("%d", &max);
	print_even(max);
	return 0;
}
