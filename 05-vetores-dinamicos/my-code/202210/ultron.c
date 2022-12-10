#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ultron.h"

/** @brief Aloca uma struct que representa uma matriz de inteiros.
 *  @param matrix Ponteiro para a struct da matriz a ser alocada.
 *  @param rows_alloc Quantidade de linhas a serem alocadas.
 *  @param cols_alloc Quantidade de colunas a serem alocadas.
 */
void matrix_int_alloc(p_matrix_int matrix, int rows_alloc, int cols_alloc) {
	matrix->data = malloc(rows_alloc * sizeof(int*));
	for (int i = 0; i < rows_alloc; i++)
		matrix->data[i] = malloc(cols_alloc * sizeof(int));
}

/** @brief Cria uma struct que representa uma matriz de inteiros.
 *  @param rows_alloc Quantidade de linhas a serem alocadas.
 *  @param cols_alloc Quantidade de colunas a serem alocadas.
 *  @return Matriz criada.
 */
p_matrix_int matrix_int_create(int rows_alloc, int cols_alloc) {
	p_matrix_int matrix = malloc(sizeof(struct matrix_int));
	matrix_int_alloc(matrix, rows_alloc, cols_alloc);
	matrix->row_cnt = 0;
	matrix->col_cnt = 0;
	matrix->rows_alloc = rows_alloc;
	matrix->cols_alloc = cols_alloc;
	return matrix;
}

/** @brief Cria um vetor de inteiros.
 *  @param ints_alloc Quantidade de inteiros que podem ser armazenados no
 *                    vetor.
 *  @return Um ponteiro para o vetor de inteiros criado.
 */
p_array_int array_int_create(int ints_alloc) {
	p_array_int array = malloc(sizeof(struct array_int));
	array->data = malloc(ints_alloc * sizeof(int));
	array->len = 0;
	array->alloc = ints_alloc;
	return array;
}

/** @brief Se necessário, dobra o armazenamento disponível em um vetor de int.
 *  @param array Vetor de inteiros a ser analisado.
 *  @param len Quantidade de inteiros armazendos no vetor.
 *  @param alloc Quantidade de inteiros que podem ser armazenados no vetor.
 */
void array_int_add_realloc_def(int *array, int *len, int *alloc) {
	if (*len == *alloc) {
		*alloc *= 2;
		array = realloc(array, *alloc * sizeof(int));
	}
}

/** @brief Se necessário, dobra o armazenamento disponível em uma struct que
 *         representa um vetor de inteiros.
 *  @param array Vetor de inteiros a ser analisado.
 */
void array_int_add_realloc(p_array_int array) {
	array_int_add_realloc_def(array->data, &array->len, &array->alloc);
}

/** @brief Adiciona um inteiro em uma struct que representa um vetor de int.
 *  @param array Vetor de inteiros onde o inteiro deve ser adicionado.
 *  @param integer Inteiro a ser adicionado após o último elemento do vetor.
 */
void array_int_add(p_array_int array, int integer) {
	array_int_add_realloc(array);
	array->data[array->len] = integer;
	array->len++;
}

/** @brief Permite a inserção de inteiros em uma struct que representa um vetor
 *         de inteiros.
 *  @param array Vetor de inteiros a ser preenchido.
 *  @param ints_cnt Quantidade de inteiros a serem inseridos no vetor.
 */
void array_int_input(p_array_int array, int ints_cnt) {
	array->len = 0;
	for (int int_idx = 0; int_idx < ints_cnt; int_idx++) {
		int integer;
		scanf("%d", &integer);
		array_int_add(array, integer);
	}
}

/** @brief Se necessário, dobra o armazenamento disponível para linhas em uma
 *         struct que representa uma matriz de inteiros.
 *  @param matrix Matriz de inteiros a ser analisada.
 */
void matrix_int_row_insert_realloc(p_matrix_int matrix) {
	if (matrix->row_cnt == matrix->rows_alloc) {
		matrix->rows_alloc *= 2;
		matrix->data = realloc(matrix->data, matrix->rows_alloc * sizeof(int *));
		int row_idx;
		for (row_idx = matrix->row_cnt; row_idx < matrix->rows_alloc; row_idx++)
			matrix->data[row_idx] = malloc(matrix->cols_alloc * sizeof(int));
	}
}

/** @brief Adiciona uma linha após a última linha de uma matriz.
 *  @param matrix Matrix na qual linha deve ser adicionada.
 *  @param array Linha a ser adicionada na matriz.
 */
void matrix_int_row_add(p_matrix_int matrix, p_array_int row) {
	if (matrix->col_cnt != 0 && matrix->col_cnt != row->len)
		exit(1);
	matrix_int_row_insert_realloc(matrix);
	for (int i = 0; i < row->len; i++)
		matrix->data[matrix->row_cnt][i] = row->data[i];
	matrix->row_cnt++;
	matrix->col_cnt = row->len;
}

/** @brief Permite a inserção de inteiros em uma struct que representa uma
 *         matriz de inteiros.
 *  @param matrix Matriz de inteiros a ser preenchida.
 *  @param row_cnt Quantidade de linhas na matriz após seu preenchimento.
 *  @param col_cnt Quantidade de colunas na matriz após seu preenchimento.
 */
void matrix_int_input(p_matrix_int matrix, int row_cnt, int col_cnt) {
	p_array_int row = array_int_create(col_cnt);
	for (int row_idx = 0; row_idx < row_cnt; row_idx++) {
		array_int_input(row, col_cnt);
		matrix_int_row_add(matrix, row);
	}
	array_free(row);
}

/** @brief Adiciona coerentemente um inteiro em um vetor de inteiros ordenado.
 *  @param array Vetor de inteiros onde o inteiro deve ser adicionado.
 *  @param len Quantidade de inteiros armazendos no vetor.
 *  @param add Inteiro a ser adicionado de forma coerente no vetor ordenado.
 */
static void array_int_add_sorted_def_s(int *array, int *len, int add) {
	int i;
	for (i = *len - 1; i >= 0 && array[i] > add; i--)
		array[i + 1] = array[i];
	array[i + 1] = add;
}

/** @brief Adiciona coerentemente um inteiro em um vetor de inteiros ordenado.
 *         Caso necessário, dobra o armazenamento do vetor.
 *  @param array Vetor de inteiros ordenados no qual será adicionado o inteiro.
 *  @param array_len Quantidade de inteiros armazenados no vetor.
 *  @param array_alloc Quantidade de inteiros que podem ser armazenados no
 *                     vetor.
 *  @param add Inteiro a ser adicionado de forma ordenada no vetor.
 */
void array_int_add_sorted_def(
		int *array,
		int *array_len,
		int *array_alloc,
		int add) {
	array_int_add_realloc_def(array, array_len, array_alloc);
	array_int_add_sorted_def_s(array, array_len, add);
	(*array_len)++;
}

/** @brief Se necessário, dobra o armazenamento disponível para colunas em uma
 *         struct que representa uma matriz de inteiros.
 *  @param matrix Matriz a ser analisada.
 */
void matrix_int_col_add_realloc(p_matrix_int matrix) {
	if (matrix->col_cnt == matrix->cols_alloc) {
		matrix->cols_alloc *= 2;
		for (int row_idx = 0; row_idx < matrix->rows_alloc; row_idx++)
			matrix->data[row_idx] = (
				realloc(matrix->data[row_idx], matrix->cols_alloc * sizeof(int))
			);
	}
}

/** @brief Adiciona uma nova coluna em uma matriz de inteiros, de forma a
 *         manter a ordem dos elementos em cada linha.
 *  @param matrix Matriz na qual a nova coluna será adicionada.
 *  @param array Coluna a ser adicionada na matriz.
 */
void matrix_int_col_add_sorted(p_matrix_int matrix, p_array_int array) {
	if (matrix->row_cnt != 0 && matrix->row_cnt != array->len)
		exit(1);
	matrix_int_col_add_realloc(matrix);
	for (int i = 0; i < matrix->row_cnt; i++)
		array_int_add_sorted_def_s(
			matrix->data[i], &matrix->col_cnt, array->data[i]
		);
	matrix->col_cnt++;
	matrix->row_cnt = array->len;
}

/** @brief Quando convém, reduz o número de linhas alocadas para uma matriz
 *         de inteiros.
 *  @param matrix Matriz a ser analisada.
 */
void matrix_int_row_del_realloc(p_matrix_int matrix) {
	if (matrix->row_cnt <= 1 / 4 * matrix->rows_alloc) {
		matrix->rows_alloc /= 2;
		matrix->data = realloc(matrix->data, matrix->rows_alloc * sizeof(int *));
	}
}

/** @brief Exclui uma linha de uma matriz de inteiros.
 *  @param matrix Matriz cuja linha de índice row_idx será deletada.
 *  @param row_idx índice da linha a ser deletada da matriz.
 */
void matrix_int_row_del(p_matrix_int matrix, int row_idx) {
	for (int i = row_idx; i < matrix->row_cnt - 1; i++)
		for (int j = 0; j < matrix->col_cnt; j++)
			matrix->data[i][j] = matrix->data[i + 1][j];
	matrix->row_cnt--;
	matrix_int_row_del_realloc(matrix);
}

/** @brief Quando convém, reduz o número de colunas alocadas para uma matriz
 *         de inteiros.
 *  @param matrix Matriz a ser analisada.
 */
void matrix_int_col_del_realloc(p_matrix_int matrix) {
	if (matrix->col_cnt <= 1 / 4 * matrix->cols_alloc) {
		matrix->cols_alloc /= 2;
		for (int i = 0; i < matrix->row_cnt; i++)
			matrix->data[i] = (
				realloc(matrix->data[i], matrix->cols_alloc * sizeof(int))
			);
	}
}

/** @brief Exclui uma coluna de uma matriz de inteiros.
 *  @param matrix Matriz cuja coluna de índice col_idx será deletada.
 *  @param col_idx índice da coluna a ser deletada da matriz.
 */
void matrix_int_col_del(p_matrix_int matrix, int col_idx) {
	for (int i = 0; i < matrix->row_cnt; i++) {
		for (int j = col_idx; j < matrix->col_cnt - 1; j++)
			matrix->data[i][j] = matrix->data[i][j + 1];
	}
	matrix->col_cnt--;
	matrix_int_col_del_realloc(matrix);
}

/** @brief Imprime uma matriz de inteiros.
 *  @param matrix Matriz de inteiros a ser impressa.
 */
void matrix_int_print(p_matrix_int matrix) {
	for (int i = 0; i < matrix->row_cnt; i++) {
		for (int j = 0; j < matrix->col_cnt; j++)
			printf("%d ", matrix->data[i][j]);
		printf("\n");
	}
}

/** @brief Libera a memória ocupada por um vetor de inteiros.
 *  @param array Vetor de inteiros a ser destruído.
 */
void array_free(p_array_int array) {
	free(array->data);
	free(array);
}

/** @brief Libera a memória ocupada por uma matriz de inteiros.
 *  @param matrix Matriz de inteiros a ser destruída.
 */
void matrix_int_free(p_matrix_int matrix) {
	for (int row_idx = 0; row_idx < matrix->rows_alloc; row_idx++)
		free(matrix->data[row_idx]);
	free(matrix->data);
	free(matrix);
}
