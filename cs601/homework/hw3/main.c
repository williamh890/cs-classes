#include <stdio.h>
extern int foo(int n);

int main() {
	int v = foo(5);
	printf("Foo %d\n", v);
	return 0;
}
