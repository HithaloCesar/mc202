#include <stdio.h>

int main(void) {
	int i;
	double lista[10];
	printf("Digite 10 números:\n");
	for (i = 0; i < 10; i++)
		scanf("%lf", &lista[i]);
	printf("Positivos:\n");
	for (i = 0; i < 10; i++) {
		if (lista[i] > 0)
			printf("%.2lf\n", lista[i]);
	}
	return 0;
}
