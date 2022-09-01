#include <stdio.h>
#define V_SIZE 10

void read_entrys(double v[], int n) {
	for (int i = 0; i < V_SIZE; i++)
		scanf("%lf", &v[i]);
}

void hadamard(double v[], double u[], double w[], int n) {
	for (int i = 0; i < n; i++)
		w[i] = v[i] * u[i];
}

void print_v(double v[], int n) {
	for (int i = 0; i < n; i++)
		printf("%.2lf\n", v[i]);
}

int main(void) {
	double u[V_SIZE], v[V_SIZE], w[V_SIZE];
	printf("Entre com os 10 números do vetor u:\n");
	read_entrys(u, V_SIZE);
	printf("Entre com os 10 números do vetor v:\n");
	read_entrys(v, V_SIZE);
	hadamard(v, u, w, V_SIZE);
	print_v(w, V_SIZE);
}
