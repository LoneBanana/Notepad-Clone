#include <stdio.h>
#include <stdlib.h>
int main(void) {
	

	char str[] = "testing.c";
	char *name = "funny-fun-fun";
	char *format = "cc -x c %s -o %s";
	char cmd_str[100] = {0};
	
	snprintf(cmd_str, sizeof(cmd_str), format, str, name);	

	system(cmd_str);


	return 0;
	}
