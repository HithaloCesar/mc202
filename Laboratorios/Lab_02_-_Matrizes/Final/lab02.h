#define MAX 99

typedef struct {
	char id;
	int data[MAX][MAX];
} matrix;

void transpose(int N, int X[][MAX], int Y[][MAX]);

void edges(int N, int X[][MAX], int Y[][MAX]);

void b_sum(int N, int X[][MAX], int Y[][MAX], int Z[][MAX]);

void multi_elem(int N, int X[][MAX], int Y[][MAX], int Z[][MAX]);

void multi_mat(int N, int X[][MAX], int Y[][MAX], int Z[][MAX]);

int (*choose_matrix(int N, matrix *M, char id))[];

char operate(int N, matrix *M);

void print_array(int N, int m[][MAX]);

void stripe_v(int data[][MAX], int N, int thickness, int starter);
