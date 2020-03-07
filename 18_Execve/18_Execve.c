/* execve01.c */
#include <unistd.h>
#include <stdio.h>

int main (int argc, char ** argv)
{
        printf ("pid=%d\n", getpid ());

        execv ("/bin/cat", argv);

        return 0;
}
