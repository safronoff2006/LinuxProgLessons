#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>
#include "N0006_Signal_ipc.h"

enum {
	FALSE, TRUE
};

sigset_t sig_m1, sig_m2, sig_null;
int signal_flag = FALSE;

void sig_func(int signr) {
	start_signalset();
	signal_flag = TRUE;
}

void start_signalset() {
	if (signal(SIGUSR1, sig_func) == SIG_ERR) exit(0);
	if (signal(SIGUSR2, sig_func) == SIG_ERR) exit(0);
	sigemptyset(&sig_m1);
	sigemptyset(&sig_null);
	sigaddset(&sig_m1, SIGUSR1);
	sigaddset(&sig_m1, SIGUSR2);
	if (sigprocmask(SIG_BLOCK, &sig_m1, &sig_m2) < 0) exit(0);
}

void message_for_parents(pid_t pid) {
	kill(pid, SIGUSR2);
}

void wait_for_parents() {
	while (signal_flag == FALSE) sigsuspend(&sig_null);
	signal_flag = FALSE;
	if (sigprocmask(SIG_SETMASK, &sig_m2, NULL) < 0) exit(0);
}

void message_for_child(pid_t pid) {
	kill(pid, SIGUSR1);
}

void wait_for_child(void) {
	while (signal_flag == FALSE) sigsuspend(&sig_null);
	signal_flag = FALSE;
	if (sigprocmask(SIG_SETMASK, &sig_m2, NULL) < 0) exit(0);
}

int main(void) {
	int unused __attribute__((unused));
	pid_t pid;
	char x, y;

	start_signalset();

	switch (pid = fork()) {
	case -1:
		fprintf(stderr, "Ошибка fork()\n");
		exit(0);
	case 0: /*...в потомке...*/
		for (x = 2; x <= 10; x += 2) {
			wait_for_parents();
			unused = write(STDOUT_FILENO, "ping-",strlen("ping-"));
			message_for_parents(getppid());
		}
		exit(0);
	default: /*...в родителе....*/
		for (y = 1; y <= 9; y += 2) {
			unused = write(STDOUT_FILENO, "pong-",strlen("pong-"));
			message_for_child(pid);
			wait_for_child();
		}
	}
	printf("\n\n");
	return 0;
}

