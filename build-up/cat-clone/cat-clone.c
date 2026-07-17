// This command is meant to mimic the cat command in C
#include <stdio.h>
int main(int argc, char **argv) {
	

	if (argc > 2) {
		perror("Too many args");
		return 2;
		// 2 is the return typically for shell built-ins
		// and misusing command line arguments
	} else if (argc == 2) {
		int c;

		FILE *fp = fopen(argv[1], "r");

		if (!fp) {
			perror("File does not exist");
			return 3;

			//3 is for file-tree and resources issues
			//in this case, file does not exist, which is a problem

			}
		while ((c = fgetc(fp)) != EOF) {
			putchar(c);
			}
		} else {
			int c;

			while ((c = getchar()) != EOF) {
				putchar(c);
				}	

			}
		


	return 0;
	}
