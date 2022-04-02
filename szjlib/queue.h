#ifndef SZJLIB_QUEUE_H_
#define SZJLIB_QUEUE_H_

#include <stdio.h>
#include <stdbool.h>


typedef struct queue* QUEUE;

/******* Capacity *******/
bool QUEUE_empty(QUEUE queue);
size_t QUEUE_size(QUEUE queue);
size_t QUEUE_maxSize(QUEUE queue);

/******* Element access *******/
void* QUEUE_front(QUEUE queue);
void* QUEUE_back(QUEUE queue);
void* QUEUE_at(QUEUE queue, size_t pos);

/******* Modifiers *******/
bool QUEUE_pushFront(QUEUE queue, void *data);
bool QUEUE_pushBack(QUEUE queue, void *data);
bool QUEUE_popFront(QUEUE queue);
bool QUEUE_popBack(QUEUE queue);

/******* Opertaions *******/
bool QUEUE_create(QUEUE *pqueue, size_t queue_size, size_t element_size);
bool QUEUE_destroy(QUEUE *pqueue);
bool QUEUE_traverse(QUEUE queue, void(*func)(void*));
bool QUEUE_clear(QUEUE queue);

#endif
