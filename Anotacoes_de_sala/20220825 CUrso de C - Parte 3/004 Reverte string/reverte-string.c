#include <stdio.h>
#include <string.h>
#define MAX 100

void reverte(char str[]) {
	int i, tam = strlen(str);
	char aux;
	for (i = 0; i < tam / 2; i++)
		aux = str[i];
		str[i] = str[tam - i - 1];
		str[tam - i - 1] = aux;
}

int main(void) {
	char str[MAX];
	fgets(str, MAX, stdin);
	reverte(str);
	printf("%s", str);
	return 0;
}
