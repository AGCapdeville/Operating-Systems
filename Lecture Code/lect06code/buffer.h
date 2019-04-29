/* buffer.h*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

typedef int buffer_item;

#define BUFFER_SIZE 5

int insert_item(buffer_item item);
int remove_item(buffer_item *item);
