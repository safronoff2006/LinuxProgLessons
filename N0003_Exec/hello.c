#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int i = 0;
	printf("%s\n", argv[0]);
	printf("Программа запущена и получила строку : ");
	while (argv[++i] != NULL)
		printf("%s ", argv[i]);

	printf("\n");


	return 0;
}
