#include <stdio.h>

int main() {
	int n, i, m = 1, f = 1;
	float s = 0;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		s += 1.0 / m * f;
		m += 3;
		f = -f;
	}
	printf("sum=%0.3f", s);
}