#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
int main(void) {

	char template[] = "/tmp/tmp.XXXXXX";
	int fd = mkstemp(template);

	if (fd == -1) {
		perror("Bad file descriptor");
		return 1;
		}
	
	FILE *fp = fdopen(fd, "w");

	if (fp == NULL) {
		perror("Unable to open fd per indicated mode");
		return 1;
		}
	
	puts("DONE!!!");
	
	char *msg = "Hello guys!!";

	fwrite(msg, 1, strlen(msg), fp);

	fclose(fp);	


	return 0;
	}
