#include <stdio.h>

int main() {
	int i, a, n, g = 0;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		scanf("%d", &a);
		if (a >= 60) {
			g++;
		}
	}
	printf("%.2f", (float)g / n);
}