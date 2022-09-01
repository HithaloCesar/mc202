#include <stdio.h>
#include <string.h>

typedef char Nome;

typedef struct {
	Nome nomeCompleto[100];
	char celular[15];
} Cliente;

Cliente magica(Cliente c) {
	for (int i = strlen(c.celular); i > 0; i--)
		c.celular[i] = c.celular[i - 1];
	c.celular[0] = '9';
	return c;
}

int main(void) {
	Cliente c;
	strcpy(c.celular, "12345678");
	c = magica(c);
	printf("%s\n", c.celular);
}
