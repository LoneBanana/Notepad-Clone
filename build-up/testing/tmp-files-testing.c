#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//Goal: use temporary files to run C-programs right from the terminal without having to make new files, compile, etc...

//Idea is that it should work almost the same as "python3" command in terminal, but for C programs
#define MAX_SIZE 2048

int main(int argc, char **argv) {
	
	//Read user input
	char buf[MAX_SIZE] = {0};
	size_t bytesRead = fread(buf, 1, MAX_SIZE-1, stdin);

	char template[] = "/tmp/tmp.XXXXXX"; // It doesn't make its own directory
	int fd = mkstemp(template); //make secure temp --> gives it a name and unique file descriptor

	if (fd == -1) {
		perror("Unable to create file descriptor");
		return 1;
		}
	FILE *fp = fdopen(fd, "w");
	
	if (!fp) {
		perror("Unable to open fd per indicated mode");	
		return 1;
		}

	fwrite(buf, 1, bytesRead, fp);

	char cmd_buf[100] = {0};
	char *format = "cc -x c %s -o %s";
	snprintf(cmd_buf, sizeof(cmd_buf)-1, format, template, template);	
	system(cmd_buf);
	system(template);
	
	unlink(template);

	puts("DONE");

	return 0;
	}
