#include <stdio.h>
#include <strings.h>
#define MAX_SIZE 1024

void editBuffer(char *buf, int lineEdit, size_t bytesRead, FILE *fp) {
	size_t l, r;
	l = 0;	
	int count = 0;
	while (count < lineEdit && buf[l] != '\0') {
		if (buf[l] == '\n') {
			count++;
			}	
		l++;	
		}
	r = l;
	while (buf[r] != '\0' && buf[r] != '\n') {
		r++;
		}
	fread(buf+l-1, sizeof(char), r-l+1, stdin);

	int c;

	while ((c = getchar()) != '\n' && c != EOF);

	fwrite(buf, sizeof(char), bytesRead, fp);
	
	

	}

int main(int argc, char **argv) {
	
	FILE *fp = fopen(argv[1], "r");
	char buf[MAX_SIZE] = {0};
	size_t bytesRead = fread(buf, sizeof(char), MAX_SIZE-1, fp); // Indicates that each chunk is 1 byte and MAX_SIZE - 1 chunks are present	
	fclose(fp);	
	
	int lineEdit;
	puts("Line you would like to edit? (Counting from 1)");
	scanf("%d", &lineEdit);
	fp = fopen(argv[1], "w");
	editBuffer(buf, lineEdit-1, bytesRead, fp);
	fclose(fp);	

	puts("\nRESULT:\n");	
	puts(buf);

	return 0;
	}
