#include <stdio.h>

int main(void) {
	return 0;
}

void matrices_set_dimensions(int matrix_count, Matrix *matrices, int n, int m) {
	for (int matrix_index = 0; matrix_index < matrix_count; matrix_index++) {
		matrix_set_dimensions(&matrices[matrix_index], n, m);
	}
}

void matrices_set_id_alphabetically(int matrix_count, Matrix *matrices) {
	for (int matrix_index = 0; matrix_index < matrix_count; matrix_index++)
		matrix_set_id(&matrices[matrix_index], matrix_index);
}

void matrices_stripe_vertically(int matrix_count, Matrix *matrices, int thickness, int starter) {
	for (int matrix_index = 0; matrix_index < matrix_count; matrix_index++)
		matrix_stripe_v(&matrices[matrix_index], 3, 1);
}

void matrices_set_initial_state(Matrix *matrices, int matrix_dimensions) {
	for (int matrix_index = 0; matrix_index < MATRICES_COUNT; matrix_index++) {
		matrices[matrix_index].rows_count = matrix_dimensions;
		matrices[matrix_index].cols_count = matrix_dimensions;
		matrix_stripe_v(&matrices[matrix_index], 3, 1);
		matrix_set_id(&matrices[matrix_index], matrix_index);
	}

}
