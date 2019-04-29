#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#define PARAM 10
int sum; // this data is shared by the thread(s)
void *runner(void *param); // the thread

int main(int argc, char *argv[]) {
	pthread_t tid; // the thread identifier
	
	// create the thread
	pthread_create(&tid, NULL, runner, (void *) PARAM);
	// wait for the thread to exit
	pthread_join(tid, NULL);
	printf("sum = %d\n", sum);
}

void *runner(void *param) {
	int i;
	long upper = (long) param;
	sum = 0;
	if (upper > 0)
		for (i = 1; i <= upper; i++)
		{
			sum += i;
			putc('.', stdout);
			fflush(stdout);
			sleep(1);
		}
	putc('\n', stdout);
	pthread_exit(0);
}
