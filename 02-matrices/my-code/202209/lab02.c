#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_INPUT_CHAR 16
#define MATRICES_COUNT 2
#define MAX_TOKEN_COUNT 4
#define MAX_MATRIX_TOKEN_COUNT 3

typedef struct {
	char id;
	int **data;
	int row_count;
	int col_count;
} Matrix;

char *buffer_alloc(int input_char_limit) {
	const int buffer_size = input_char_limit + 2;
	char *buffer = malloc(buffer_size * sizeof(char));
	return buffer;
}

void input_buffer_clear(void) {
	char c = getchar();
	while (c != '\n' && c != EOF)
		c = getchar();
}

static bool is_too_long(char *buffer) {
	char *p_newline = strchr(buffer, '\n');
	if (p_newline == NULL) {
		input_buffer_clear();
		return true;
	}
	*p_newline = '\0';
	return false;
}

static bool has_leading_whitespace(char *buffer) {
	if (buffer[0] == ' ') {
		return true;
	}
	return false;
}

static bool is_empty(char *buffer) {
	if (strlen(buffer) == 0)
		return true;
	return false;
}

void input_validation(
		char *buffer,
		int input_char_limit) {
	const int buffer_size = input_char_limit + 2;
	int invalid_input = true;
	while (invalid_input) {
		fgets(buffer, buffer_size, stdin);
		if (is_too_long(buffer)) {
			printf("Erro: A entrada de texto não pode conter mais de");
			printf(" %d caracteres!\n", input_char_limit);
			continue;
		}
		if (has_leading_whitespace(buffer)) {
			printf("Erro: A entrada de texto não pode iniciar com um espaço!\n");
			continue;
		}
		if (is_empty(buffer)) {
			printf("Erro: A entrada de texto não pode ser vazia!\n");
			continue;
		}
		invalid_input = 0;
	}
}

int int_input(
		char *buffer,
		int input_char_limit) {
	input_validation(buffer, input_char_limit);
	int integer;
	sscanf(buffer, "%d", &integer);
	return integer;
}

Matrix matrix_alloc(
		int row_count,
		int col_count) {
	Matrix matrix;
	matrix.data = malloc(row_count * sizeof(int *));
	for (int row = 0; row < row_count; row++)
		matrix.data[row] = malloc(col_count * sizeof(int));
	return matrix;
}

Matrix *matrices_alloc(
		int matrices_count,
		int row_count,
		int col_count) {
	Matrix *matrices = malloc(matrices_count * sizeof(Matrix));
	for (int matrix_index = 0; matrix_index < matrices_count; matrix_index++)
		matrices[matrix_index] = matrix_alloc(row_count, col_count);
	return matrices;
}

void matrix_set_dimensions(
		Matrix *matrix,
		int row_count,
		int col_count) {
	matrix->row_count = row_count;
	matrix->col_count = col_count;
}

void matrix_set_id_alphabetically(
		Matrix *matrix,
		int matrix_index) {
	// O ID da primeira matriz é 'A', da segunda é 'B', etc.
	matrix->id = 65 + matrix_index;
}

static void matrix_stripe_v(
		Matrix *matrix,
		int thickness,
		int starter) {
	for (int i = 0; i < matrix->row_count; i++)
		for (int j = 0; j < matrix->col_count; j++) {
			if (j % (2 * thickness) < thickness)
				matrix->data[i][j] = starter;
			else
				matrix->data[i][j] = !starter;
		}
}

static void matrix_stripe_h(
		Matrix *matrix,
		int thickness,
		int starter) {
	for (int i = 0; i < matrix->row_count; i++)
		for (int j = 0; j < matrix->col_count; j++) {
			if (j % (2 * thickness) < thickness)
				matrix->data[i][j] = starter;
			else
				matrix->data[i][j] = !starter;
		}
}

void matrix_stripe(
		Matrix *matrix,
		char orientation,
		int thickness,
		int starter) {
	if (orientation == 'v')
		matrix_stripe_v(matrix, thickness, starter);
	else if (orientation == 'h')
		matrix_stripe_h(matrix, thickness, starter);
}

void matrices_set_initial_state(
		Matrix *matrices,
		int matrices_count,
		int dimensions) {
	for (int matrix_index = 0; matrix_index < MATRICES_COUNT; matrix_index++) {
		matrix_set_dimensions(&matrices[matrix_index], dimensions, dimensions);
		matrix_set_id_alphabetically(&matrices[matrix_index], matrix_index);
		matrix_stripe(&matrices[matrix_index], 'v', 3, 1);
	}
}

int string_token_count(char *string) {
	int token_count = 1;
	int string_lenght = strlen(string);
	for (int char_index = 0; char_index < string_lenght; char_index++)
		if (string[char_index] == ' ' && string[char_index+1] != ' ')
			token_count++;
	return token_count;
}

int string_split(
		char *string,
		char **tokens) {
	int token_count = string_token_count(string);
	char *c = strtok(string, " \n");
	int i = 0;
	while (c != NULL) {
		tokens[i++] = c;
		c = strtok(NULL, " \n");
	}
	return token_count;
}

Matrix *get_pointer_by_id(
		Matrix *matrices,
		int matrices_count,
		char id) {
	for (int matrix_index = 0; matrix_index < matrices_count; matrix_index++)
		if (matrices[matrix_index].id == id)
			return &matrices[matrix_index];
	return NULL;
}

void set_operation_matrices(
		int matrix_token_count,
		Matrix **operation_matrices,
		Matrix *matrices,
		char **m_tokens) {
	for (int matrix_index = 0; matrix_index < matrix_token_count; matrix_index++)
		operation_matrices[matrix_index] = (
			get_pointer_by_id(matrices, MATRICES_COUNT, *m_tokens[matrix_index])
		);
}

void matrix_free(Matrix *matrix) {
	for (int row = 0; row < matrix->row_count; row++)
		free(matrix->data[row]);
	free(matrix->data);
}

Matrix matrix_transpose_copy(Matrix *A) {
	Matrix At = matrix_alloc(A->row_count, A->col_count);
	matrix_set_dimensions(&At, A->row_count, A->col_count);
	for (int i = 0; i < A->row_count; i++)
		for (int j = 0; j < A->col_count; j++)
			At.data[i][j] = A->data[j][i];
	return At;
}

void transpose_to(
		Matrix *X,
		Matrix *Y) {
	Matrix Xt = matrix_transpose_copy(X);
	Xt.id = Y->id;
	matrix_free(Y);
	*Y = Xt;
}

Matrix matrix_edges_copy(Matrix *A) {
	Matrix Ae = matrix_alloc(A->row_count, A->col_count);
	matrix_set_dimensions(&Ae, A->row_count, A->col_count);
	for (int i = 0; i < A->row_count; i++)
		for (int j = 0; j < A->col_count; j++)
			Ae.data[i][j] = A->data[i][j];
	for (int i = 1; i < A->row_count - 1; i++)
		for (int j = 1; j < A->col_count - 1; j++) {
			bool diagonals_are_1 = (
				A->data[i-1][j-1] == 1
				&& A->data[i-1][j+1] == 1
				&& A->data[i+1][j-1] == 1
				&& A->data[i+1][j+1] == 1
			);
			if (diagonals_are_1)
				Ae.data[i][j] = 0;
		}
	return Ae;
}

void edges_to(
		Matrix *X,
		Matrix *Y) {
	Matrix Xe = matrix_edges_copy(X);
	Xe.id = Y->id;
	matrix_free(Y);
	*Y = Xe;
}

Matrix matrix_binary_sum_copy(
		Matrix *A,
		Matrix *B) {
	Matrix ABbs = matrix_alloc(A->row_count, A->col_count);
	matrix_set_dimensions(&ABbs, A->row_count, A->col_count);
	for (int i = 0; i < A->row_count; i++)
		for (int j = 0; j < A->col_count; j++) {
			if (A->data[i][j] == 1 || B->data[i][j] == 1)
				ABbs.data[i][j] = 1;
			else
				ABbs.data[i][j] = 0;
		}
	return ABbs;
}

void binary_sum_to(
		Matrix *X,
		Matrix *Y,
		Matrix *Z) {
	Matrix XYbs = matrix_binary_sum_copy(X, Y);
	XYbs.id = Z->id;
	matrix_free(Z);
	*Z = XYbs;
}

Matrix matrix_product_elements_copy(
		Matrix *A,
		Matrix *B) {
	Matrix ABme = matrix_alloc(A->row_count, A->col_count);
	matrix_set_dimensions(&ABme, A->row_count, A->col_count);
	for (int i = 0; i < A->row_count; i++)
		for (int j = 0; j < A->col_count; j++)
			ABme.data[i][j] = A->data[i][j] * B->data[i][j];
	return ABme;
}

void product_elements_to(Matrix *X,
		Matrix *Y,
		Matrix *Z) {
	Matrix XYme = matrix_product_elements_copy(X, Y);
	XYme.id = Z->id;
	matrix_free(Z);
	*Z = XYme;
}

void matrix_binary(Matrix *A) {
	for (int i = 0; i < A->row_count; i++)
		for (int j = 0; j < A->col_count; j++) {
			if (A->data[i][j] != 0)
				A->data[i][j] = 1;
			else
				A->data[i][j] = 0;
		}
}

Matrix matrix_product_copy(
		Matrix *A,
		Matrix *B) {
	Matrix ABm = matrix_alloc(A->row_count, A->col_count);
	matrix_set_dimensions(&ABm, A->row_count, A->col_count);
	for (int i = 0; i < A->row_count; i++)
		for (int j = 0; j < B->col_count; j++) {
			int aux = 0;
			for (int k = 0; k < A->col_count; k++)
				aux += A->data[i][k] * B->data[k][j];
			ABm.data[i][j] = aux;
		}
	return ABm;
}

void binary_product_to(
		Matrix *X,
		Matrix *Y,
		Matrix *Z) {
	Matrix XYbp = matrix_product_copy(X, Y);
	matrix_binary(&XYbp);
	XYbp.id = Z->id;
	matrix_free(Z);
	*Z = XYbp;
}

void operate(
		char *operation,
		Matrix **matrices) {
	if (strcmp(operation, "TRANSPOSTA") == 0)
		transpose_to(matrices[0], matrices[1]);
	else if (strcmp(operation, "BORDAS") == 0)
		edges_to(matrices[0], matrices[1]);
	else if (strcmp(operation, "SOMA") == 0)
		binary_sum_to(matrices[0], matrices[1], matrices[2]);
	else if (strcmp(operation, "MULTI_ELEM") == 0)
		product_elements_to(matrices[0], matrices[1], matrices[2]);
	else if (strcmp(operation, "MULTI_MAT") == 0)
		binary_product_to(matrices[0], matrices[1], matrices[2]);
}

void matrix_print(Matrix *matrix) {
	for (int i = 0; i < matrix->row_count; i++) {
		for (int j = 0; j < matrix->col_count; j++)
			printf("%d ", matrix->data[i][j]);
		printf("\n");
	}
}

void free_memory(
		char *buffer,
		Matrix *matrices,
		char **tokens,
		Matrix **operation_matrices) {
	free(buffer);
	for (int k = 0; k < MATRICES_COUNT; k++) {
		for (int i = 0; i < matrices[k].row_count; i++)
			free(matrices[k].data[i]);
		free(matrices[k].data);
	}
	free(matrices);
	free(tokens);
	free(operation_matrices);
}

int main(void) {
	char *buffer = buffer_alloc(MAX_INPUT_CHAR);
	unsigned int matrices_dimensions = int_input(buffer, 2);
	unsigned int operation_count = int_input(buffer, 2);
	Matrix *matrices = matrices_alloc(
		MATRICES_COUNT, matrices_dimensions, matrices_dimensions
	);
	matrices_set_initial_state(matrices, MATRICES_COUNT, matrices_dimensions);
	char **tokens = malloc(MAX_TOKEN_COUNT * sizeof(char *));
	Matrix **operation_matrices = (
		malloc(MAX_MATRIX_TOKEN_COUNT * sizeof(Matrix *))
	);
	for (int op_index = 0; op_index < operation_count; op_index++) {
		printf("\n");
		input_validation(buffer, MAX_INPUT_CHAR);
		const int token_count = string_split(buffer, tokens);
		const int matrix_token_count = token_count - 1;
		char *operation = tokens[0];
		char **matrix_tokens = &tokens[1];
		set_operation_matrices(
			matrix_token_count, operation_matrices, matrices, matrix_tokens
		);
		operate(operation, operation_matrices);
		matrix_print(operation_matrices[matrix_token_count-1]);
	}
	free_memory(buffer, matrices, tokens, operation_matrices);
	return 0;
}
