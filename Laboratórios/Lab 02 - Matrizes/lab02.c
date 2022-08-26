#include <stdio.h>
#include <string.h>
#define OPERATION_SIZE 11

void transpose(int N, int m1[][N], int m2[][N]) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			m2[j][i] = m1[i][j];
}

void sum(int N, int m1[][N], int m2[][N], int m_result[][N]) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			if (m1[i][j] == 1 || m2[i][j] == 1)
				m_result[i][j] = 1;
			else
				m_result[i][j] = 0;
		}
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

void print_array(int N, int m[][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf("%d ", m[i][j]);
		printf("\n");
	}
}

void operate(int N, int A[][N], int B[][N]) {
	char operation[OPERATION_SIZE];
	scanf("%s ", operation);
	if (strcmp(operation, "TRANSPOSTA") == 0) {
		char X, Y;
		scanf("%c %c", &X, &Y);
		if (X == 'A' && Y == 'A')
			transpose(N, A, A);
		if (X == 'A' && Y == 'B')
			transpose(N, A, B);
		if (X == 'B' && Y == 'B')
			transpose(N, B, B);
		if (X == 'B' && Y == 'A')
			transpose(N, B, A);
	} else if (strcmp(operation, "SOMA") == 0) {
		char X, Y, Z;
		int m_result[N][N];
		scanf("%c %c %c", &X, &Y, &Z);
		sum(N, x, y, z);
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
		operate(N, A, B);
		print_array(N, A);
	}
	return 0;
}
