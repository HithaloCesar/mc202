#include <stdio.h>
#define MAX 1000

void copia_string(char str1[], char str2[]) {
	int i;
	for (i = 0; str1[i] != '\0'; i++)
		str2[i] = str1[i];
	str2[i] = '\0';
}

int main(void) {
	char str1[MAX], str2[MAX];
	fgets(str1, MAX, stdin);
	copia_string(str1, str2);
	printf("%s", str2);
	return 0;
}
