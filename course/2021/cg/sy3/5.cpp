#include <stdio.h>

main() {
	int i, a, b, c,m,n;
	scanf("%d,%d",&m,&n);
	for (i =m; i <= n; i++) {
		a = i / 100;
		b = i / 10 % 10;
		c = i % 10;
		if (a * a * a + b * b * b + c * c * c == i)
			printf("%d\n", i);
	}
}