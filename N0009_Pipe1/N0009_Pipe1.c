#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>

#define USAGE printf("usage : %s данные\n", argv[0]);

#define MAX 4096

int main(int argc, char *argv[]) {
	int pp[2], file, i, n;
	pid_t pid;
	char buffer[MAX];
	FILE *dataptr;

	if (argc != 2) {
		USAGE
		exit(EXIT_SUCCESS);
	}

	if ((file = open(argv[1], O_RDONLY)) < 0) {
		perror("open : ");
		exit(EXIT_SUCCESS);
	}

	/*Устанавливаем трубу*/
	if (pipe(pp) < 0) {
		perror("pipe : ");
		exit(EXIT_SUCCESS);
	}

	/*Создаем новый процесс*/
	if ((pid = fork()) < 0) {
		perror("pipe : ");
		exit(EXIT_SUCCESS);

	} else if (pid > 0) { /*Родитель*/

		close(pp[0]); /*Закрываем чтение*/
		n = read(file, buffer, MAX);
		if ((write(pp[1], buffer, n)) != n) {
			perror(" write : ");
			exit(EXIT_SUCCESS);
		}

		if ((waitpid(pid, NULL, 0)) < 0) {
			perror("waitpid : ");
			exit(EXIT_SUCCESS);
		}

	} else { /*Это потомок*/

		close(pp[1]); /*Закрываем запись*/
		n = read(pp[0], buffer, MAX);
		if ((write(STDOUT_FILENO, buffer, n)) != n) {
			perror(" write : ");
			exit(EXIT_SUCCESS);
		}

	}

	exit(EXIT_SUCCESS);

}
