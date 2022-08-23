#include <stdio.h>
#define V_SIZE 5

void soma_um(int v[], int n) {
	int i;
	for (i = 0; i < n; i++)
		v[i]++;
}

int main(void) {
	int i, v[V_SIZE] = {1, 2, 3, 4, 5};
	soma_um(v, V_SIZE);
	for (i = 0; i < V_SIZE; i++)
		printf("%d\n", v[i]);
	return 0;
}
