#include <stdio.h>

/**
 * \brief     Remove de um vetor inteiros não presentes em outro vetor.
 * \param[in] u: Vetor de inteiros n1, n2, ..., nT.
 * \param[in] T: Tamanho do vetor u.
 */
void banner_set(int u[], int T) {
    int B;
    scanf("%d", &B);
    int b[B];
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
 * \param[in] u: Vetor de inteiros n1, n2, ..., nT.
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
 * \param[in] u: Vetor de inteiros n1, n2, ..., nT.
 * \param[in] T: Tamanho do vetor u.
 */
void cyclic_movement(int u[], int T) {
    int P;
    scanf("%d", &P);
    int aux[P];
    for (int i = 0; i < P; i++)
        aux[i] = u[T-P+i];
    for (int i = T - 1; i >= P; i--)
        u[i] = u[i-P];
    for (int i = 0; i < P; i++)
        u[i] = aux[i];
}

/**
 * \brief     Inverte um vetor.
 * \param[in] u: Vetor de inteiros n1, n2, ..., nT.
 * \param[in] T: Tamanho do vetor u.
 */
void vector_inversion(int u[], int T) {
    int aux;
    for (int i = 0; i < T / 2; i++) {
        aux = u[i];
        u[i] = u[T-1-i];
        u[T-1-i] = aux;
    }
}

/**
 * \brief     Realiza uma operação sob um vetor.
 * \param[in] u: Vetor de inteiros n1, n2, ..., nT.
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
        vector_inversion(u, T);
        break;
    }
}

/**
 * \brief     Imprime um vetor.
 * \param[in] u: Vetor de inteiros n1, n2, ..., nT.
 * \param[in] T: Tamanho do vetor u.
 */
void print_vector(int u[], int T) {
    for (int i = 0; i < T; i++)
        if (i != T-1)
            printf("%d ", u[i]);
        else
            printf("%d\n", u[i]);
}

/**
 * \brief Executa o programa principal, que realiza operações um vetor.
 */
int main(void) {
    int T;
    scanf("%d", &T);
    int u[T];
    for (int i = 0; i < T; i++)
        scanf("%d", &u[i]);
    int operation_count;
    scanf("%d", &operation_count);
    for (int i = 0; i < operation_count; i++) {
        operate(u, T);
        print_vector(u, T);
    }
    return 0;
}
