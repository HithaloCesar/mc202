#include <stdio.h>
#include <string.h>
#define OPERATION_SIZE 11

void transpose(int N, int X[][N], int Y[][N]) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			Y[j][i] = X[i][j];
}

void sum(int N, int X[][N], int Y[][N], int Z[][N]) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			if (X[i][j] == 1 || Y[i][j] == 1)
				Z[i][j] = 1;
			else
				Z[i][j] = 0;
		}
}

void multi_elem(int N, int X[][N], int Y[][N], int Z[][N]) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			Z[i][j] = X[i][j] * Y[i][j];
}

void multi_elem(int N, int X[][N], int Y[][N], int Z[][N]) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)

}

void striped_v(int N, int m[][N], int thickness) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			if (j % 6 < 3)
				m[i][j] = 1;
			else
				m[i][j] = 0;
		}
}

int (*choose_matrix(int N, int A[][N], int B[][N], char option))[] {
	if (option == 'A')
		return A;
	if (option == 'B')
		return B;
}

char operate(int N, int A[][N], int B[][N]) {
	char operation[OPERATION_SIZE];
	scanf("%s ", operation);
	if (strcmp(operation, "TRANSPOSTA") == 0) {
		char x, y;
		scanf("%c %c", &x, &y);
		int (*X)[N] = choose_matrix(N, A, B, x);
		int (*Y)[N] = choose_matrix(N, A, B, y);
		transpose(N, X, Y);
		return y;
	} else if (strcmp(operation, "SOMA") == 0) {
		char x, y, z;
		scanf("%c %c %c", &x, &y, &z);
		int (*X)[N] = choose_matrix(N, A, B, x);
		int (*Y)[N] = choose_matrix(N, A, B, y);
		int (*Z)[N] = choose_matrix(N, A, B, z);
		sum(N, X, Y, Z);
		return z;
	} else if (strcmp(operation, "MULTI_ELEM") == 0) {
		char x, y, z;
		scanf("%c %c %c", &x, &y, &z);
		int (*X)[N] = choose_matrix(N, A, B, x);
		int (*Y)[N] = choose_matrix(N, A, B, y);
		int (*Z)[N] = choose_matrix(N, A, B, z);
		multi_elem(N, X, Y, Z);
	} else if (strcmp(operation, "MULTI_MAT") == 0) {
		char x, y, z;
		scanf("%c %c %c", &x, &y, &z);
		int (*X)[N] = choose_matrix(N, A, B, x);
		int (*Y)[N] = choose_matrix(N, A, B, y);
		int (*Z)[N] = choose_matrix(N, A, B, z);
		multi_mat(N, X, Y, Z);
	}
}

void print_array(int N, int m[][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf("%d ", m[i][j]);
		printf("\n");
	}
}

int main(void) {
	int N;
	scanf("%d", &N);
	int O;
	scanf("%d", &O);
	int A[N][N], B[N][N];
	striped_v(N, A, 3);
	striped_v(N, B, 3);
	for (int operation_count = 0; operation_count < O; operation_count++) {
		char result_id = operate(N, A, B);
		int (*result)[N] = choose_matrix(N, A, B, result_id);
		printf("\n");
		print_array(N, result);
	}
	return 0;
}
