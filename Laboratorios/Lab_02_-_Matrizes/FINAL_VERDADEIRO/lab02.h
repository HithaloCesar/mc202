#define MAX 99

void transpose(int N, int X[][MAX], int Y[][MAX]);

void edges(int N, int X[][MAX], int Y[][MAX]);

void b_sum(int N, int X[][MAX], int Y[][MAX], int Z[][MAX]);

void multi_elem(int N, int X[][MAX], int Y[][MAX], int Z[][MAX]);

void multi_mat(int N, int X[][MAX], int Y[][MAX], int Z[][MAX]);

int (*choose_matrix(int N, Matrix *M, char id))[];

char operate(int N, Matrix *M);

void print_array(int N, int m[][MAX]);

void stripe_v(int data[][MAX], int N, int thickness, int starter);
