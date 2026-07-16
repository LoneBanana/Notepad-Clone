#include <stdio.h>

/*

The way this editor will work:
1. It will first print the contents of the file in question
2. Then, it will write into the file accordingly

Extra exercise after this: look into errno function and modify code so that it handles errors better and gives more info about
which errors are occurring
*/


int main(int argc, char *argv[]) {
	FILE *fp;	
	if (argc == 1) {
		perror("Too few args");
		return 2;
		} else if (argc > 2 || (fp = fopen(argv[1], "r")) == NULL) {	
			perror("Invalid file name");
			fclose(fp);
			return 3;
			}
		
	//Print contents of file

	fp = fopen(argv[1], "r");
	int c;
	register int j = 1;
	putchar('\n');
	while ((c = fgetc(fp)) != EOF) {
		static int printLineNum = 1;
		if (printLineNum) {
			printf("%d ", j);
			printLineNum = 0;
			j++;
			}
		putchar(c);
		if (c == '\n')
			printLineNum = 1;
		}
	fclose(fp);

	// Get line to be edited
	
	puts("What line number would you like to edit, (indexed from 1)");

	int n;
	scanf("%d", &n);
	
	if (n == EOF) {
		perror("EOF");
		return 1;
		}
	n -= 1;	
	


	// Loop to find nth-line, starting at 1
	
	int i = 0;
	fp = fopen(argv[1], "r");
	FILE *tmp = fopen("temp-stuff", "w");
	
	while (i < n && (c = fgetc(fp)) != EOF) {
		fputc(c, tmp);
		if (c == '\n')
			i++;
		}
	while ((c = getchar()) != '\n');
	fputc(c,tmp);
	while ((c = getchar()) != '\n' && c != EOF) {
		fputc(c, tmp);
		}
	
	while ((c = fgetc(fp)) != '\n' && c != EOF);

	while ((c = fgetc(fp)) != EOF) {
		fputc(c, tmp);
		}
		
	// Copying contents into the other file
	

	

	return 0;
	}
