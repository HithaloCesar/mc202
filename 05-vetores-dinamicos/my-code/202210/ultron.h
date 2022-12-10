typedef struct array_int *p_array_int;

struct array_int {
	int *data;
	int len;
	int alloc;
};

typedef struct matrix_int *p_matrix_int;

struct matrix_int {
	int **data;
	int row_cnt;
	int rows_alloc;
	int col_cnt;
	int cols_alloc;
};

p_matrix_int matrix_int_create(int m, int n);

p_array_int array_int_create(int len);

void matrix_int_input(p_matrix_int matrix, int m, int n);

void array_int_input(p_array_int array, int array_len);

void matrix_int_row_add(p_matrix_int matrix, p_array_int array);

void array_free(p_array_int array);

void matrix_int_col_add_sorted(p_matrix_int matrix, p_array_int array);

void matrix_int_row_del(p_matrix_int matrix, int row_idx);

void matrix_int_col_del(p_matrix_int matrix, int col_idx);

void matrix_int_print(p_matrix_int matrix);

void matrix_int_free(p_matrix_int matrix);
