#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
/* обработчик для SIGINT и SIGTERM */

static void signal_handler(int signo) {
	if (signo == SIGINT)
		printf("Захвачен сигнал SIGINT!\n");
	else if (signo == SIGTERM)
		printf("Захвачен сигнал SIGTERM!\n");
	else {
		/* этого ни в коем случае не должно произойти */
		fprintf(stderr, "Неожиданный сигнал!\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
int main(void) {
	/*
	 * Регистрируем signal_handler как наш обработчик сигнала
	 * для SIGINT.
	 */
	if (signal(SIGINT, signal_handler) == SIG_ERR) {
		fprintf(stderr, "Невозможно обработать SIGINT!\n");
		exit(EXIT_FAILURE);
	}
	/*
	 * Регистрируем signal_handler как наш обработчик сигнала
	 * для SIGTERM.
	 */
	if (signal(SIGTERM, signal_handler) == SIG_ERR) {
		fprintf(stderr, "Невозможно обработать SIGTERM!\n");
		exit(EXIT_FAILURE);
	}
	/* Сбрасываем поведение SIGPROF, чтобы он действовал как по умолчанию. */
	if (signal(SIGPROF, SIG_DFL) == SIG_ERR) {
		fprintf(stderr, "Невозможно сбросить SIGPROF!\n");
		exit(EXIT_FAILURE);
	}
	/* Игнорируем SIGHUP. */
	if (signal(SIGHUP, SIG_IGN) == SIG_ERR) {
		fprintf(stderr, "Невозможно игнорировать SIGHUP!\n");
		exit(EXIT_FAILURE);
	}
	for (;;)
		pause();
	return 0;
}
