#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>

#define EXIT(s) {fprintf(stderr, "%s",s); exit(0);}

#define USAGE(s) {fprintf(stderr, "%s Данные для чтения\n",s); exit(0);}

#define MAX 8192

enum {
	ERROR = -1, SUCCESS
};

int main(int argc, char **argv) {

	FILE *pipe_writer, *file;
	char buffer[MAX];

	if (argc != 2) USAGE(argv[0]);

	if ((file = fopen(argv[1], "r")) == NULL) EXIT("Ошибка открытия файла.........\n");

	if ((pipe_writer = popen("grep Description", "w")) == NULL) EXIT("Ошибка открытия трубы...........\n");

	while (1) {

		if (fgets(buffer, MAX, file) == NULL)
			break;

		if (fputs(buffer, pipe_writer) == EOF)
			EXIT("Ошибка записи........\n");

	}

	pclose(pipe_writer);

	exit(EXIT_SUCCESS);

}

