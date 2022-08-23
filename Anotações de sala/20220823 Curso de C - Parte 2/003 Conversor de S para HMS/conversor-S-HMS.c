#include <stdio.h>

void hms(int seg) {
	int h = seg / 3600;
	int m = (seg % 3600) / 60;
	int s = seg % 60;
	printf("%dh%dm%ds\n", h, m, s);
}

int main(void) {
	int s;
	scanf("%d", &s);
	hms(s);
	return 0;
}
