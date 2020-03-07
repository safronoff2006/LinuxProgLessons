/* forkexec01.c */
#include <unistd.h>
#include <stdio.h>

extern char **environ;

int main(void) {

	char *echo_args[] = { "echo", "child\n", NULL };


	if (!fork()) {
		execve("/bin/echo", echo_args, environ);
		fprintf(stderr, "an error occured\n");
		return 1;
	}

	printf("parent\n");
	return 0;
}
