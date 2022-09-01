#include <stdio.h>
#include <string.h>
#include "lab02.h"
#define QTD_M 2
#define MAX 99
#define OPERATION_SIZE 11

int main(void) {
	int N;
	scanf("%d", &N);
	int O;
	scanf("%d", &O);
	matrix M[MAX_MATRICES];
	for (int m = 0; m < MAX_MATRICES; m++) {
		stripe_v(M[m].data, N, 3, 1);
		M[m].id = 65 + m;
	}
	for (int i = 0; i < O; i++) {
		printf("\n");
		char id = operate(N, M);
		int (*result)[] = choose_matrix(N, M, id);
		print_array(N, result);
	}
	return 0;
}
