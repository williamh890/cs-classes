#include <stdio.h>
extern long sumtorial(long n);

int main() {
	for (int i = 0; i < 100; ++i) {
		int v = sumtorial(i);
		printf("%d, ", v);
	}
		printf("\n");
	return 0;
}
