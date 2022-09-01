#include <stdio.h>

void soma_um(int x) {
	/* Apenas a variável local é alterada. */
	x = x + 1;
}

int main(void) {
	int x = 1;
	soma_um(x);
	printf("%d\n", x);
	return 0;
}
