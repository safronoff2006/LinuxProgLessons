#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()

{

	unlink("fifo0001");

	/*Создаем новый FIFO*/

	if ((mkfifo("fifo0001", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)

	{

		fprintf(stderr, "Невозможно создать FIFO\n");

		exit(EXIT_SUCCESS);

	}

	printf("Можно записать в FIFO сразу %ld байтов\n",
			pathconf("fifo0001", _PC_PIPE_BUF));

	printf("Одновременно можно открыть %ld FIFO \n", sysconf(_SC_OPEN_MAX));

	exit(EXIT_SUCCESS);

}
