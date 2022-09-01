#include <stdio.h>

float get_pow(float num, int exp) {
	float value = 1;
	for (int i = 0; i < exp; i++) {
		value *= num;
	}
	return value;
}

float get_circle_area(float radius) {
	float pi = 3.1415;
	return pi * get_pow(radius, 2);
}

int main() {
	float radius;
	scanf("%f", &radius);
	printf("%.4f\n", get_circle_area(radius));
	return 0;
}
