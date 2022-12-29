#include <stdio.h>
main() {
	int  a0, n, i;
	double s, a;
	scanf( "%d %d", &a0, &n);
	s = 0;
	a=a0;
	for (i = 1; i <= n; i++) {
		s += a;
		a = a * 10 + a0;
	}
	printf("%.0lf", s);
}.