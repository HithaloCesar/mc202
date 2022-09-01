#include <stdio.h>
#include "matrix.h"
#include <stdlib.h>
#include <string.h>
#define MATRICES_COUNT 2
#define MAX_DIMENSION 99
#define MAX_OPERATION_SIZE 17
#define MAX_OPERATION_TOKENS 4
#define MAX_TOKEN_SIZE 11

int int_input(void) {
	int integer;
	scanf(" %d ", &integer);
	return integer;
}

Matrix matrix_alloc(int n, int m) {
	Matrix matrix;
	matrix.data = malloc(n * sizeof(int *));
	for (int row = 0; row < n; row++)
		matrix.data[row] = malloc(m * sizeof(int));
	return matrix;
}

void matrix_set_dimensions(Matrix *matrix, int n, int m) {
	matrix->rows_count = n;
	matrix->cols_count = m;
}

void matrix_set_id_alphabetically(Matrix *matrix, int matrix_index) {
	// O ID da primeira matriz é 'A', da segunda é 'B', etc.
	matrix->id = 65 + matrix_index;
}

void matrix_stripe_v(Matrix *matrix, int thickness, int starter) {
	for (int i = 0; i < matrix->rows_count; i++)
		for (int j = 0; j < matrix->cols_count; j++) {
			if (j % (2 * thickness) < thickness)
				matrix->data[i][j] = starter;
			else
				matrix->data[i][j] = !starter;
		}
}

void matrix_print(Matrix *matrix, int row_count, int cols_count) {
	for (int i = 0; i < row_count; i++) {
		for (int j = 0; j < cols_count; j++)
			printf("%d ", matrix->data[i][j]);
		printf("\n");
	}
}

// char **string_tokens_alloc(int token_count, int max_token_lenght) {
// 	char **tokens = malloc(token_count * sizeof(char *));
// 	for (int i = 0; i < token_count; i++)
// 		tokens[i] = malloc(max_token_lenght * sizeof(char));
// 	return tokens;
// }

int string_token_count(char *string) {
	int token_count = 1;
	int string_lenght = strlen(string);
	for (int char_index = 0; char_index < string_lenght; char_index++)
		if (string[char_index] == ' ' && string[char_index+1] != ' ')
			token_count++;
	return token_count;
}

char **string_split(char *string, int token_count) {
	char **tokens = malloc(token_count * sizeof(char *));
	char *c = strtok(string, " \n");
	int i = 0;
	while (c != NULL) {
		tokens[i++] = c;
		c = strtok(NULL, " \n");
	}
	return tokens;
}

// char **read_operation() {
// 	// char *command = malloc(MAX_OPERATION_SIZE * sizeof(char));
// 	// fgets(command, MAX_OPERATION_SIZE, stdin);
// 	// int token_count = string_token_count(command);
// 	// char **tokens = string_split(command, MAX_OPERATION_TOKENS, MAX_TOKEN_SIZE);
// 	// for (int i = 0; i < 4; i++)
// 	// 	printf("%s", tokens[i]);
// 	return tokens;
// }

char *string_read() {
	char *command = malloc(MAX_OPERATION_SIZE * sizeof(char));
	fgets(command, MAX_OPERATION_SIZE, stdin);
	return command;
}

Matrix *get_pointer_by_id(Matrix *matrices, char id) {
	for (int matrix_index = 0; matrix_index < 2; matrix_index++)
		if (matrices[matrix_index].id == id)
			return &matrices[matrix_index];
	return NULL;
}

void transpose(Matrix *X, Matrix *Y) {
	int aux;
	for (int y_row = 1; y_row < X->rows_count; y_row++)
		for (int y_col = 0; y_col < y_row; y_col++) {
			aux = Y->data[y_row][y_col];
			Y->data[y_row][y_col] = X->data[y_col][y_row];
			Y->data[y_col][y_row] = aux;
		}
}

void edges(Matrix *X, Matrix *Y) {
	Matrix aux = matrix_alloc(X->rows_count, X->cols_count);
	matrix_set_dimensions(&aux, X->rows_count, X->cols_count);
	for (int x_row = 0; x_row < X->rows_count; x_row++)
		for (int x_col = 0; x_col < X->cols_count; x_col++)
			aux.data[x_row][x_col] = X->data[x_row][x_col];
	for (int y_row = 0; y_row < Y->rows_count; y_row++)
		for (int y_col = 0; y_col < Y->cols_count; y_col++)
			Y->data[y_row][y_col] = X->data[y_row][y_col];
	for (int aux_row = 1; aux_row < aux.rows_count - 1; aux_row++)
		for (int aux_col = 1; aux_col < aux.cols_count - 1; aux_col++) {
			int diagonals_are_1 = (
				aux.data[aux_row-1][aux_col-1] == 1
				&& aux.data[aux_row-1][aux_col+1] == 1
				&& aux.data[aux_row+1][aux_col-1] == 1
				&& aux.data[aux_row+1][aux_col+1] == 1
			);
			if (diagonals_are_1)
				Y->data[aux_row][aux_col] = 0;
		}
}

Matrix *operate(char *command, Matrix *matrices) {
	int token_count = string_token_count(command);
	char **tokens = string_split(command, token_count);
	Matrix **operation_matrices = malloc(token_count * sizeof(Matrix *));
	// O limite do loop é token_count - 1) pois o primeiro token é o operador.
	for (int matrix_index = 0; matrix_index < token_count - 1; matrix_index++)
		operation_matrices[matrix_index] = get_pointer_by_id(matrices, *tokens[matrix_index + 1]);
	if (token_count == 3) {
		if (strcmp(tokens[0], "TRANSPOSTA") == 0)
			transpose(operation_matrices[0], operation_matrices[1]);
			// criar matrix_transpose pra uma matriz só.
		else if (strcmp(tokens[0], "BORDAS") == 0)
			edges(operation_matrices[0], operation_matrices[1]);
			// criar matrix_edges pra uma matriz só.
		return operation_matrices[1];
	}
	// if (token_count == 4) {
	// 	if (strcmp(tokens[0], "SOMA") == 0)
	// 		binary_sum(
	// 			operation_matrices[0],
	// 			operation_matrices[1],
	// 			operation_matrices[2]
	// 		)
	// 		// criar matrix_binary_sum com apenas 2 parametros.
	// 	else if (strcmp(tokens[0], "MULTI_ELEM") == 0)
	// 		multi_elem(
	// 			operation_matrices[0],
	// 			operation_matrices[1],
	// 			operation_matrices[2]
	// 		)
	// 		// criar matrix_multi_elem com apenas 2 parametros.
	// 	else if (strcmp(tokens[0], "MULTI_MAT") == 0)
	// 		multi_mat(
	// 			operation_matrices[0],
	// 			operation_matrices[1],
	// 			operation_matrices[2]
	// 		)
	// 		// criar matrix_multi_mat com apenas 2 parametros.
	// 	return operation_matrices[2];
	// }
}

int main(void) {
	int matrix_dimensions = int_input();
	int operation_count = int_input();
	Matrix *matrices = malloc(MATRICES_COUNT * sizeof(Matrix));
	for (int matrix_index = 0; matrix_index < MATRICES_COUNT; matrix_index++)
		matrices[matrix_index] = matrix_alloc(matrix_dimensions, matrix_dimensions);
	for (int matrix_index = 0; matrix_index < MATRICES_COUNT; matrix_index++) {
		matrix_set_dimensions(&matrices[matrix_index], matrix_dimensions, matrix_dimensions);
		matrix_set_id_alphabetically(&matrices[matrix_index], matrix_index);
		matrix_stripe_v(&matrices[matrix_index], 3, 1);
	}
	for (int operation_index = 0; operation_index < operation_count; operation_index++) {
		//char **tokens = read_operation();
		char *command = string_read();
		Matrix *result = operate(command, matrices);
		matrix_print(result, matrix_dimensions, matrix_dimensions);

	}
	// matrix_print(&matrices[0], matrix_dimensions, matrix_dimensions);



	// matrices_set_dimensions(2, matrices, matrix_dimensions, matrix_dimensions);
	// matrices_set_id_alphabetically(2, matrices);
	// matrices_stripe_vertically(2, matrices, 3, 1);
	// for (int i = 0; i < O; i++) {
	// 	printf("\n");
	// 	char id = operate(N, matrices);
	// 	int (*result)[] = choose_matrix(N, matrices, id);
	// 	print_array(N, result);
	// }
	return 0;
}
