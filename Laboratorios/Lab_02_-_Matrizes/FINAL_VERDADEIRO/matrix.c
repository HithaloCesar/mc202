#include "matrix.h"

void matrix_stripe_v(Matrix *matrix, int thickness, int starter) {
	for (int i = 0; i < matrix->rows_count; i++)
		for (int j = 0; j < matrix->cols_count; j++) {
			if (j % (2 * thickness) < thickness)
				matrix->data[i][j] = starter;
			else
				matrix->data[i][j] = !starter;
		}
}

