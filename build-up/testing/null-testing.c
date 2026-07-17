#include <stdio.h>

int main(int argc, char **argv) {
	
	int *a = NULL;
	a++;
	printf("%p", a);
	printf("%d, %d", sizeof(a), sizeof(int));

	return 0;
	}
