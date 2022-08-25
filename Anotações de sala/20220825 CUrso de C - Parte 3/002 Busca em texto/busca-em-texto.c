#include <stdio.h>
#define MAX 1000

int ocorre(char texto[], int pos, char padrao[]) {
	int texto_acaba_antes, nao_padrao, nao_coringa;
	for (int j = 0; padrao[j] != '\0'; j++) {
		texto_acaba_antes = texto[pos + j] == '\0';
		nao_padrao = texto[pos + j] != padrao[j];
		nao_coringa = padrao[j] != '*';
		if (texto_acaba_antes || (nao_padrao && nao_coringa))
			return 0;
	}
	return 1;
}

void imprime_trecho(char texto[], int ini, int tam) {
	printf("%d: ", ini);
	int j;
	for (j = 0; j < tam; j++)
		printf("%c", texto[ini + j]);
	printf("\n");
}

/*
	int tamanho(char string[]) {
		int i;
		for (i = 0; string[i] != '\0'; i++);
		return i;
	}
 */

int tamanho(char string[]) {
	int i;
	while (string[i] != '\0')
		i++;
	return i;
}

int main(void) {
	int i;
	char texto[MAX], padrao[MAX];
	scanf("%s ", padrao);
	fgets(texto, MAX, stdin);
	printf("Procurando por %s no texto: %s\n", padrao, texto);
	for (i = 0; texto[i] != '\0'; i++)
		if (ocorre(texto, i, padrao))
			imprime_trecho(texto, i, tamanho(padrao));
	return 0;
}
