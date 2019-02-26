/**
* Name: Adam Capdeville
* Lab/task: Lab 1
* Date: 01/28/19
**/

#ifndef __list_h_
#define __list_h_

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE_OF_DATA 32
#define NUM_OF_NODES 5

typedef struct list
{
   char *data;
   struct list *next;
} LIST;

void allocate_list(LIST **list, int count);

void load_list(LIST *list);

void print_list(LIST *list);

void free_list_emb(LIST *head);
void free_list_tail(LIST *head);
void free_list_iter(LIST *head);

#endif
