#include <stdio.h>

double aplicacao(double ini, double mensal, double j, int t) {
	double s = ini;
	for (int i = 0; i < t; i++) {
		s *= (1 + j);
		s += mensal;
	}
	return s;
}

int main(void) {
	double ini;
	scanf("%lf", &ini);
	double mensal;
	scanf("%lf", &mensal);
	double j;
	scanf("%lf", &j);
	int t;
	scanf("%d", &t);
	printf("%lf\n", aplicacao(ini, mensal, j, t));
	return 0;
}
