#include <stdio.h>

int main(void) {
	
	int c;

	puts("Please print out some text!");

	while ((c = getchar()) != '\n' && c != EOF) {
		putchar(c);
		}
	puts("Done!!!");

	return 0;
	}
