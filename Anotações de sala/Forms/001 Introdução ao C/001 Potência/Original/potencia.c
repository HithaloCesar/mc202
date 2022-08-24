#include <stdio.h>

float get_pow(float num, int exp) {
	float value = num;
	for (int i = 0; i < exp; i++) {
		value *= num;
	}
	return value;
}

int main() {
	float num, exp;
	scanf("%f %f", &num, &exp);
	printf("%.2f\n", get_pow(num, exp));
	return 0;
}
