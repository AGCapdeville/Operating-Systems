#include "buffer.h"

buffer_item buffer[BUFFER_SIZE];
pthread_mutex_t mutex;
sem_t empty;
sem_t full;

int insertPointer = 0, removePointer = 0;

void *producer(void *param);
void *consumer(void *param);
int insert_item(buffer_item);
int remove_item(buffer_item*);

int main(int argc, char *argv[])
{
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	int sleepTime, producerThreads, consumerThreads;
	int i, j;

	if (argc != 4)
	{
		fprintf(stderr, "Usage: buffer <sleep time> <producer threads> <consumer threads>\n");
		return -1;
	}

	sleepTime = strtol(argv[1], NULL, 10);
	producerThreads = strtol(argv[2], NULL, 10);
	consumerThreads = strtol(argv[3], NULL, 10);

	//Initialize the the locks
	printf("%d\n", pthread_mutex_init(&mutex, NULL));
	printf("%d\n", sem_init(&empty, 0, 5));
	printf("%d\n", sem_init(&full, 0, 0));
	srandom(time(0));

	//Create the producer and consumer threads
	for (i = 0; i < producerThreads; i++)
	{
		pthread_t tid;
		pthread_create(&tid, &attr, producer, NULL);
	}

	for (j = 0; j < consumerThreads; j++)
	{
		pthread_t tid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tid, &attr, consumer, NULL);
	}

	//Sleep for user specified time
	sleep(sleepTime);
	return 0;
}

void *producer(void *param)
{
	buffer_item rand;
	int r;

	while (true)
	{
		r = random() % BUFFER_SIZE;
		sleep(r);
		rand = random();

		if (insert_item(rand))
			fprintf(stderr, "Error");

		printf("Producer produced %d \n", rand);

	}
}

void *consumer(void *param)
{
	buffer_item rand;
	int r;

	while (true)
	{
		r = random() % BUFFER_SIZE;
		sleep(r);

		if (remove_item(&rand))
			fprintf(stderr, "Error Consuming");
		else
			printf("Consumer consumed %d \n", rand);
	}
}

int insert_item(buffer_item item)
{
	//Acquire Empty Semaphore
	sem_wait(&empty);

	//Acquire mutex lock to protect buffer
	pthread_mutex_lock(&mutex);
	buffer[insertPointer++] = item;
	insertPointer = insertPointer % 5;

	//Release mutex lock and full semaphore
	pthread_mutex_unlock(&mutex);
	sem_post(&full);

	return 0;
}

int remove_item(buffer_item *item)
{
	//Acquire Full Semaphore
	sem_wait(&full);

	//Acquire mutex lock to protect buffer
	pthread_mutex_lock(&mutex);
	*item = buffer[removePointer];
	buffer[removePointer++] = -1;
	removePointer = removePointer % 5;

	//Release mutex lock and empty semaphore
	pthread_mutex_unlock(&mutex);
	sem_post(&empty);

	return 0;
}

