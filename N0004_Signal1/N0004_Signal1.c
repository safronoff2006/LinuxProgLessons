#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigfunc(int sig) {

	char c;

	if (sig != SIGINT)
		return;

	else {

		printf("\nХотите завершить программу (y/n) : ");

		while ((c = getchar()) != 'y') {
			return;
		}

		exit(0);

	}

}

int main(void) {

	int i;

	signal(SIGINT, sigfunc);

	while (1)

	{

		printf(" Вы можете завершить программу с помощью CTRL+C ");

		for (i = 0; i <= 48; i++)

			printf("\b");

	}

	return 0;

}
