#include <stdio.h>
int main() {
	int  n, i;
	double  x0,x = 1, m = 1, s = 1;
	scanf("%lf %d", &x0, &n);
	for (i = 1; i <= n; i++) {
		x *= x0;
		m *= i;
		s += (x / m);
	}
	printf("%lf", s);
	return 0;
}