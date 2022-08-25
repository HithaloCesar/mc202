#include <stdio.h>

int main(void) {
	int k;
	char original, encriptado, pos_original, pos_encriptado;
	scanf("%d ", &k);
	scanf("%c", &original);
	while (original != '\n') {
		pos_original = original - 'A';
		pos_encriptado = (pos_original + k) % 26;
		encriptado = 'A' + pos_encriptado;
		printf("%c", encriptado);
		scanf("%c", &original);
	}
	printf("\n");
	return 0;
}
