#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()

{
	int unused __attribute__((unused));
	int fd_fifo; /*дескриптор FIFO*/
	char buffer[] = "Текстовая строка для fifo\n";
	char buf[100];
	memset(buf, 0, sizeof(buf));

	/*Если файл с таким именем существует, удалим его*/

	unlink("/tmp/fifo0001.1");
	/*Создаем FIFO*/
	if ((mkfifo("/tmp/fifo0001.1",  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1) {
		fprintf(stderr, "Невозможно создать fifo\n");
		exit(EXIT_SUCCESS);
	}

	/*Открываем fifo для чтения и записи*/

	if ((fd_fifo = open("/tmp/fifo0001.1", O_RDWR)) == -1) {
		fprintf(stderr, "Невозможно открыть fifo\n");
		exit(EXIT_SUCCESS);
	}

	unused = write(fd_fifo, buffer, strlen(buffer));

	if (read(fd_fifo, &buf, sizeof(buf)) == -1)
		fprintf(stderr, "Невозможно прочесть из FIFO\n");

	else
		printf("Прочитано из FIFO : %s\n", buf);

	return 0;

}
