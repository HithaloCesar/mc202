#include <stdio.h>

double maximo(double a, double b) {
	if (a > b)
		return a;
	return b;
}

double potencia(double a, double b) {
	int i;
	double prod = 1;
	for (i = 0; i < b; i++)
		prod *= a;
	return prod;
}

int main(void) {
	double a, b;
	printf("Entre com a e b: ");
	scanf("%lf %lf", &a, &b);
	printf("Maior: %.2lf\n", maximo(a, b));
	printf("a^b: %.2lf\n", potencia(a, b));
	return 0;
}
