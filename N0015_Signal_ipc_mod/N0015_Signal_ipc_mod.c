#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "N0015_Signal_ipc_mod.h"

enum {
	FALSE, TRUE
};

sigset_t sig_m1, sig_m2, sig_null;

volatile sig_atomic_t signal_flag = FALSE;

void sig_func(int signr) {

	signal_flag = TRUE;

}

void message_for_proc(pid_t pid, int signum) {
	kill(pid, signum);
}

void wait_for_syg() {
	while (signal_flag == FALSE)
		sigsuspend(&sig_null);

	signal_flag = FALSE;
}


int main(void) {

	int unused __attribute__((unused));
	pid_t pid;
	char x, y;

	if (signal(SIGUSR1, sig_func) == SIG_ERR)
		exit(EXIT_SUCCESS);
	if (signal(SIGUSR2, sig_func) == SIG_ERR)
		exit(EXIT_SUCCESS);

	sigemptyset(&sig_m1);
	sigemptyset(&sig_null);
	sigaddset(&sig_m1, SIGUSR1);
	sigaddset(&sig_m1, SIGUSR2);
	if (sigprocmask(SIG_BLOCK, &sig_m1, &sig_m2) < 0)
		exit(EXIT_SUCCESS);

	switch (pid = fork()) {
	case -1:
		fprintf(stderr, "Ошибка fork()\n");
		break;

	case 0: /*...в потомке...*/
		for (x = 2; x <= 10; x += 2) {
			wait_for_syg();
			unused = write(STDOUT_FILENO, "ping-", strlen("ping-"));
			kill(getppid(),SIGUSR2);
		}
		break;

	default: /*...в родителе....*/
		for (y = 1; y <= 9; y += 2) {
			unused = write(STDOUT_FILENO, "pong-", strlen("pong-"));
			kill(pid, SIGUSR1);
			wait_for_syg();
		}
	}

	sigprocmask(SIG_SETMASK, &sig_m2, NULL);

	printf("\n\n");
	exit(EXIT_SUCCESS);

}

