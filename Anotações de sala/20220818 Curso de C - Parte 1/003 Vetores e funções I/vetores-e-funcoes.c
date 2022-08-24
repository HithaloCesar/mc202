#include <stdio.h>
#define LIST_SIZE 10

void le_vetor(double lista[], int n) {
	int i;
	printf("Digite 10 números:\n");
	for (i = 0; i < 10; i++)
		scanf("%lf", &lista[i]);
}

void imprime_positivos(double lista[], int n) {
	int i;
	printf("Positivos:\n");
	for (i = 0; i < 10; i++) {
		if (lista[i] > 0)
			printf("%.2lf\n", lista[i]);
	}
}

int main(void) {
	double lista[LIST_SIZE];
	le_vetor(lista, LIST_SIZE);
	imprime_positivos(lista, LIST_SIZE);
	return 0;
}
