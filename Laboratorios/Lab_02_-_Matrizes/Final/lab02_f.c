#include <stdio.h>
#include <string.h>
#include "lab02.h"
#define QTD_M 2
#define MAX 99
#define OPERATION_SIZE 11

/**
 * \brief     Transpõe uma matriz quadrada de inteiros, X, para outra, Y.
 * \param[in] N: Dimensões das matrizes quadradas X e Y.
 * \param[in] X: Matriz quadrada cujos valores serão transpostos para Y.
 * \param[in] Y: Matriz que receberá os valores transpostos de X.
 */
void transpose(int N, int X[][MAX], int Y[][MAX]) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			Y[j][i] = X[i][j];
}

/**
 * \brief     Encontra as bordas da matriz quadrada binária X e guarda-as em Y.
 * \param[in] N: Dimensões das matrizes quadradas binárias X e Y.
 * \param[in] X: Matriz quadrada binária cujas bordas serão guardadas em Y.
 * \param[in] Y: Matriz quadrada binária que guardará as bordas de X.
 */
void edges(int N, int X[][MAX], int Y[][MAX]) {
	int aux[MAX][MAX];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			aux[i][j] = X[i][j];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			Y[i][j] = X[i][j];
	for (int i = 1; i < N - 1; i++)
		for (int j = 1; j < N - 1; j++) {
			int diagonals_are_1 = (
				aux[i-1][j-1] == 1 && aux[i-1][j+1] == 1
				&& aux[i+1][j-1] == 1 && aux[i+1][j+1] == 1
			);
			if (diagonals_are_1)
				Y[i][j] = 0;
		}
}

/**
 * \brief     Soma as matrizes quadradas binárias X e Y e guarda a soma em Z.
 * \param[in] N: Dimensões das matrizes quadradas X, Y e Z.
 * \param[in] X: Matriz quadrada cujos elementos são os primeiros adendos.
 * \param[in] Y: Matriz quadrada cujos elementos são os segundos adendos.
 * \param[in] Z: Matriz quadrada cujos elementos são a soma binária de X e Y.
 */
void b_sum(int N, int X[][MAX], int Y[][MAX], int Z[][MAX]) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			if (X[i][j] == 1 || Y[i][j] == 1)
				Z[i][j] = 1;
			else
				Z[i][j] = 0;
		}
}

/**
 * \brief     Multiplica elemento a elemento as matrizes X e Y, e guarda em Z.
 * \param[in] N: Dimensões das matrizes quadradas X, Y e Z.
 * \param[in] X: Matriz quadrada a ser multiplicada por Y.
 * \param[in] Y: Matriz quadrada a ser multiplicada por X.
 * \param[in] Z: Matriz quadrada que receberá os produtos de X e Y.
 */
void multi_elem(int N, int X[][MAX], int Y[][MAX], int Z[][MAX]) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			Z[i][j] = X[i][j] * Y[i][j];
}

/**
 * \brief     Multiplica as matrizes X e Y, e guarda em Z.
 * \param[in] N: Dimensões das matrizes quadradas X, Y e Z.
 * \param[in] X: Matriz quadrada a ser multiplicada por Y.
 * \param[in] Y: Matriz quadrada a ser multiplicada por X.
 * \param[in] Z: Matriz quadrada que receberá o produto de X e Y.
 */
void multi_mat(int N, int X[][MAX], int Y[][MAX], int Z[][MAX]) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			int aux = 0;
			for (int k = 0; k < N; k++)
				aux += X[i][k] * Y[k][j];
			if (aux > 0)
				Z[i][j] = 1;
			else
				Z[i][j] = 0;
		}
}

/**
 * \brief     Aplica numa matriz quadrada um padrão listrado vertical binário.
 * \param[in] A: Matriz a ser listrada verticalmente com algarismos binários.
 * \param[in] B:
 * \param[in] N: Dimensão da matriz quadrada.
 * \param[in] name: Espessura das listras.
 */
int (*choose_matrix(int N, matrix *M, char id))[] {
	int i = 0;
	for (i = 0; i < MAX_MATRICES; i++)
		if (M[i].id == id)
			return M[i].data;
	return 0;
}

char operate(int N, matrix *M) {
	char operation[MAX_OPERATION_SIZE];
	scanf("%s", operation);
	char x, y;
	scanf(" %c %c", &x, &y);
	int (*X)[] = choose_matrix(N, M, x);
	int (*Y)[] = choose_matrix(N, M, y);
	if (strcmp(operation, "TRANSPOSTA") == 0) {
		transpose(N, X, Y);
		return y;
	}
	if (strcmp(operation, "BORDAS") == 0) {
		edges(N, X, Y);
		return y;
	}
	char z;
	scanf(" %c", &z);
	int (*Z)[] = choose_matrix(N, M, z);
	if (strcmp(operation, "SOMA") == 0) {
		b_sum(N, X, Y, Z);
		return z;
	}
	if (strcmp(operation, "MULTI_ELEM") == 0) {
		multi_elem(N, X, Y, Z);
		return z;
	}
	if (strcmp(operation, "MULTI_MAT") == 0) {
		multi_mat(N, X, Y, Z);
		return z;
	}
	return 0;
}

void print_array(int N, int m[][MAX]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf("%d ", m[i][j]);
		printf("\n");
	}
}

/**
 * \brief     Aplica numa matriz quadrada um padrão listrado vertical binário.
 * \param[in] m: Matriz a ser listrada verticalmente com algarismos binários.
 * \param[in] N: Dimensão da matriz quadrada.
 * \param[in] thickness: Espessura das listras.
 * \param[in] S: Valor da primeira listra, da esquerda para a direita (0 ou 1).
 */
void stripe_v(int data[][MAX], int N, int thickness, int starter) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			if (j % (2 * thickness) < thickness)
				data[i][j] = starter;
			else
				data[i][j] = !starter;
		}
}