
/* fork01.c */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main (void)
{
        pid_t pid = fork ();

        if (pid == 0) {
                printf ("child (pid=%d)\n", getpid());
        } else {
                printf ("parent (pid=%d, child's pid=%d)\n", getpid(), pid);
        }

        return 0;
}
