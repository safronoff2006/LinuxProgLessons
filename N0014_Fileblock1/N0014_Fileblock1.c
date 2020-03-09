#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {

	int unused __attribute__((unused));
	int fd;
	int x, y;
	pid_t pid;

	unlink("fileblock"); /*Удаляем предыдущий файл*/

	fd = open("fileblock", O_WRONLY | O_CREAT, 0777);

	if (fd == -1) {
		perror("open : ");
		exit(0);
	}

	if ((pid = fork()) == -1) {
		perror("fork :");
		exit(0);
	} else if (pid) { /*Родительский процесс*/
		while (1) {
			for (x = 0; x < 10; x++) {
				sleep(1);
				unused = write(fd, (char*) "x", 1);
			}

			break;
		}
	} else { /*Процесс-потомок*/

		while (1) {
			for (y = 0; y < 10; y++) {
				sleep(1);
				unused = write(fd, (char*) "X", 1);
			}
			break;
		}
	}

	return 0;

}
