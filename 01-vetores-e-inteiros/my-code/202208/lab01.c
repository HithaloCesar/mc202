/*
 * Esse programa realiza operações sob um vetor de inteiros definido pelo
 * usuário.
 */

#include <stdio.h>
#define MAX 1000

/**
 * \brief     Remove de um vetor inteiros não presentes em outro vetor.
 * \param[in] u: Vetor de inteiros a ser operado.
 * \param[in] T: Tamanho do vetor u.
 */
void banner_set(int u[], int T) {
	int B;
	scanf("%d", &B);
	int b[MAX];
	for (int i = 0; i < B; i++)
		scanf("%d", &b[i]);
	for (int i = 0; i < T; i++) {
		int b_in_u = 0;
		for (int j = 0; j < B; j++) {
			if (u[i] == b[j]) {
				b_in_u = 1;
				break;
			}
		}
		if (!b_in_u)
			u[i] = 0;
	}
}

/**
 * \brief     Multiplica por um int os valores em índices ímpares de um vetor.
 * \param[in] u: Vetor de inteiros a ser operado.
 * \param[in] T: Tamanho do vetor u.
 */
void mobius_multiplication(int u[], int T) {
	int M;
	scanf("%d", &M);
	for (int i = 0; i < T; i++) {
		if (i % 2 == 1)
			u[i] *= M;
	}
}

/**
 * \brief     Desloca cada elemento de um vetor em P índices para a direita.
 * \param[in] u: Vetor de inteiros a ser operado.
 * \param[in] T: Tamanho do vetor u.
 */
void cyclic_movement(int u[], int T) {
	int P;
	scanf("%d", &P);
	int aux[MAX];
	for (int i = 0; i < P; i++)
		aux[i] = u[T-P+i];
	for (int i = T - 1; i >= P; i--)
		u[i] = u[i-P];
	for (int i = 0; i < P; i++)
		u[i] = aux[i];
}

/**
 * \brief     Inverte um vetor.
 * \param[in] u: Vetor de inteiros a ser operado.
 * \param[in] T: Tamanho do vetor u.
 */
void array_inversion(int u[], int T) {
	int aux;
	for (int i = 0; i < T / 2; i++) {
		aux = u[i];
		u[i] = u[T-1-i];
		u[T-1-i] = aux;
	}
}

/**
 * \brief     Permite a escolha da operação a ser realizada sobre um vetor.
 * \param[in] u: Vetor de inteiros a ser operado.
 * \param[in] T: Tamanho do vetor u.
 */
void operate(int u[], int T) {
	int operation;
	scanf("%d", &operation);
	switch (operation) {
		case 1:
			banner_set(u, T);
			break;
		case 2:
			mobius_multiplication(u, T);
			break;
		case 3:
			cyclic_movement(u, T);
			break;
		case 4:
			array_inversion(u, T);
			break;
	}
}

/**
 * \brief     Imprime um vetor.
 * \param[in] u: Vetor de inteiros a ser impresso.
 * \param[in] T: Tamanho do vetor u.
 */
void print_array(int u[], int T) {
	for (int i = 0; i < T; i++)
		printf("%d ", u[i]);
	printf("\n");
}

/**
 * \brief Executa o programa principal, que realiza operações sob um vetor.
 */
int main(void) {
	int T;
	scanf("%d", &T);
	int u[MAX];
	for (int i = 0; i < T; i++)
		scanf("%d", &u[i]);
	int operation_count;
	scanf("%d", &operation_count);
	for (int i = 0; i < operation_count; i++) {
		operate(u, T);
		print_array(u, T);
	}
	return 0;
}
