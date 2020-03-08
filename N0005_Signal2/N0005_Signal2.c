#include <signal.h>
#include <stdio.h>

int main()

{
	int unused __attribute__((unused));
	int a, b;

	printf("Число : ");

	unused = scanf("%d", &a);

	printf("делится на : ");

	unused = scanf("%d", &b);

	if (b == 0)

		raise(SIGFPE);

	else

		printf("Результат = %d\n", a / b);

	return 0;

}
