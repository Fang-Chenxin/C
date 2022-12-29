#include <stdio.h>
#include <string.h>

int main() {
	char ch[20];	
	char c;int i=0;
	while(scanf("%c", &c) && c != '\n')
    {
        ch[i++] = c;
    }
    ch[i] = '\0';
	c=getchar();
	int n = strlen(ch);
	for (i = 0; i < n; i++) {
		if (ch[i] == c) {
			for (int j = i; j < n - 1; j++) {
				ch[j] = ch[j + 1];
			}
			n--;
		}
	}
	for (int i = 0; i < n; i++) {
		printf("%c", ch[i]);
	}
	return 0;
}
