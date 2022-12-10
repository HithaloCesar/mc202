#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ultron.h"

void operate(p_matrix_int matrix, char *operation);

void matrix_insert_row(p_matrix_int matrix);

void matrix_insert_col(p_matrix_int matrix);

void matrix_remove(p_matrix_int matrix, char option);

/** @brief Executa o programa principal, responsável por realizar, sob uma,
 *         matriz de inteiros, operações de inserção e de remoção de linhas e
 *         de colunas.
 *  @return Caso o programa seja executado com sucesso, retorna 0.
 */
int main(void) {
	int row_cnt, col_cnt;
	scanf("%d %d", &row_cnt, &col_cnt);
	p_matrix_int matrix = matrix_int_create(row_cnt, col_cnt);
	matrix_int_input(matrix, row_cnt, col_cnt);
	int operation_cnt;
	scanf("%d", &operation_cnt);
	char *operation = malloc(4 * sizeof(char));
	for (int op_idx = 0; op_idx < operation_cnt; op_idx++) {
		scanf("%s", operation);
		operate(matrix, operation);
		matrix_int_print(matrix);
		printf("###\n");
	}
	matrix_int_free(matrix);
	free(operation);
	printf("COMBINACAO MATRICIAL FINALIZADA!\n");
	return 0;
}

/** @brief Realiza operaçações sob uma matriz de inteiros.
 *  @param matrix Matriz de inteiros a ser operada.
 *  @param operation Primeiro argumento da operação.
 */
void operate(p_matrix_int matrix, char *operation) {
	char option;
	scanf(" %c", &option);
	if (strcmp(operation, "IN") == 0) {
		switch (option) {
			case 'L':
				matrix_insert_row(matrix);
				break;
			case 'C':
				matrix_insert_col(matrix);
				break;
			default:
				exit(1);
				break;
		}
	} else if (strcmp(operation, "OUT") == 0) {
		int idx;
		scanf(" %d", &idx);
		switch (option) {
			case 'L':
				matrix_int_row_del(matrix, idx);
				break;
			case 'C':
				matrix_int_col_del(matrix, idx);
				break;
			default:
				exit(1);
				break;
		}
	} else
		exit(1);
}

/** @brief Insere uma linha em uma matriz de inteiros.
 *  @param matrix Matriz de inteiros a ser alterada.
 */
void matrix_insert_row(p_matrix_int matrix) {
	p_array_int new_row = array_int_create(matrix->col_cnt);
	array_int_input(new_row, matrix->col_cnt);
	matrix_int_row_add(matrix, new_row);
	array_free(new_row);
}

/** @brief Insere uma coluna em uma matriz de inteiros.
 *  @param matrix Matriz de inteiros a ser alterada.
 */
void matrix_insert_col(p_matrix_int matrix) {
	p_array_int new_col = array_int_create(matrix->row_cnt);
	array_int_input(new_col, matrix->row_cnt);
	matrix_int_col_add_sorted(matrix, new_col);
	array_free(new_col);
}
