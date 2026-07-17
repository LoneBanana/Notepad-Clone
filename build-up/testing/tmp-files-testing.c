#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#define MAX_SIZE 1024


int main(int argc, char **argv) {
	
	char buffer[MAX_SIZE] = {0};
	size_t sizeRead = fread(buffer, 1, MAX_SIZE - 1, stdin);
	
	char template[] = "/tmp/c-residue/tmp.XXXXXX"; //exactly six X's are required while using mkstemp
	//Also, template NEEDS to be static array like this
	
	int fd = mkstemp(template); //fd is same as "file-descriptor";
	 //Basically, unique number assigned to each stream;

	 /*
	ex:
	1. stdin --> 0
	2. stdout --> 1
	3. stderr --> 2
	 */

	if (fd == -1) {
		perror("Failure creating temporary file directory!");
		exit(1);
		unlink(template);
		}
	FILE *fp = fdopen(fd, "w");

	if (!fp) {
		perror("Failure converting file descriptor to pointer!");
		exit(1);
		}
		
	fwrite(buffer, 1, strlen(buffer), fp);	
	fclose(fp);

	char *cmd_str = "cc -x c %s -o %s";
	
	sprintf(str, template);
	
	system(cmd_str);
	


	return 0;
	}
