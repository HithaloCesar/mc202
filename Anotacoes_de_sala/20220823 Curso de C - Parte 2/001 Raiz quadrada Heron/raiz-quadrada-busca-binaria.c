#include <stdio.h>
#include <math.h>
#define ERROR 1e-12

double square_root(double x) {
	double low = 0, high = x, guess = x;
	while (fabs(guess * guess - x) > ERROR) {
		if (guess * guess > x)
			high = guess;
		if (guess * guess < x)
			low = guess;
		guess = (low + high) / 2;
	}
	return guess;
}

int main(void) {
	double x;
	printf("Insira um número: ");
	scanf("%lf", &x);
	printf("Raiz quadrada: %g", square_root(x));
	return 0;
}
