#include	<sys/signal.h>
#include	<stdio.h>
#include	<unistd.h>

static void	signal_handler(int);	/* one handler for both signals */

int
main(void)
{
	printf("Running with pid = %d\n", getpid());
	fflush(stdout);
	if (signal(SIGUSR1, signal_handler) == SIG_ERR)
		fprintf(stderr, "can't catch SIGUSR1\n");
	if (signal(SIGUSR2, signal_handler) == SIG_ERR)
		fprintf(stderr, "can't catch SIGUSR2\n");
	if (signal(SIGHUP, signal_handler) == SIG_ERR) /* some signals can be caught */
		fprintf(stderr, "can't catch SIGHUP\n");
	if (signal(SIGKILL, signal_handler) == SIG_ERR) /* impossible to catch this */
		fprintf(stderr, "can't catch SIGKILL\n");
	for ( ; ; )
		pause();
}

static void
signal_handler(int signo)		/* argument is signal number */
{
	if (signo == SIGUSR1)
		printf("received SIGUSR1\n");
	else if (signo == SIGUSR2)
		printf("received SIGUSR2\n");
	else if (signo != 0)
		fprintf(stderr, "received signal %d\n", signo);
}
