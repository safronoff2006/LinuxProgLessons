#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
/* обработчик для SIGINT */
static void sigint_handler(int signo) {
	/*
	 * Технически не следует использовать printf()
	 * в обработчике сигнала, но если вы так сделаете, это не смертельно.
	 * Подробнее об этом мы поговорим в разделе
	 * «Реентерабельность».
	 */
	printf("Захвачен сигнал SIGINT!\n");
	exit(EXIT_SUCCESS);
}
int main(void) {
	/*
	 * Регистрируем sigint_handler как наш обработчик
	 * для сигнала SIGINT.
	 */
	if (signal(SIGINT, sigint_handler) == SIG_ERR) {
		fprintf(stderr, "Невозможно обработать SIGINT!\n");
		exit(EXIT_FAILURE);
	}
	for (;;)
		pause();
	return 0;
}
