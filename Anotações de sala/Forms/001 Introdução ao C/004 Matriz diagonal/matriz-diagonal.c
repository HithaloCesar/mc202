#include <stdio.h>
#define N 3

void verify_matrix(int matrix[][N]) {
	int aux = 1;
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			if (matrix[i][j] != 0) {
				printf("A matriz não é triangular inferior.\n");
				aux = 0;
				break;
			}
		}
	}
	for (int i = N - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (matrix[i][j] != 0) {
				printf("A matriz não é triangular superior.\n");
				aux = 0;
				break;
			}
		}
	}
	if (aux == 1)
		printf("Essa matriz é uma matriz diagonal!\n");
	else {
		printf("Essa matriz não é uma matriz diagonal!\n");
	}
}

int main(void) {
	int matrix[N][N];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &matrix[i][j]);
		}
	}
	verify_matrix(matrix);
	return 0;
}
