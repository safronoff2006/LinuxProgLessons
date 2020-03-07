#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void) {
	char pid[255];
	int unused __attribute__((unused));


	fork();
	fork();
	fork();
	sprintf(pid, "PID : %d\n", getpid());
	unused = write(STDOUT_FILENO, pid, strlen(pid));
	exit(0);
}
