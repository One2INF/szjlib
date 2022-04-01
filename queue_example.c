#include <stdio.h>
#include <stdlib.h>

#include "szjlib/log.h"
#include "szjlib/queue.h"


#define STR_SIZE      32
#define QUEUE_SIZE    5

typedef struct
{
  int a;
  char str[STR_SIZE];
}DATA_T;

void print_item(void *data)
{
  LOG_INFO("%4d %16s", ((DATA_T*)data)->a, ((DATA_T*)data)->str);
}

int main(void)
{
  QUEUE queue = NULL;
  QUEUE_create(&queue, QUEUE_SIZE, sizeof(DATA_T));

  QUEUE_pushBack(queue, &(DATA_T){1, "I am 1"});
  QUEUE_pushBack(queue, &(DATA_T){2, "I am 2"});
  QUEUE_pushBack(queue, &(DATA_T){3, "I am 3"});
  QUEUE_pushBack(queue, &(DATA_T){4, "I am 4"});
  QUEUE_pushBack(queue, &(DATA_T){5, "I am 5"});
  QUEUE_pushBack(queue, &(DATA_T){6, "I am 6"});

  LOG_INFO("front item:");
  print_item(QUEUE_front(queue));
  LOG_INFO("back item:");
  print_item(QUEUE_back(queue));

  LOG_INFO("print the queue:");
  QUEUE_traverse(queue, print_item);

  QUEUE_popFront(queue);
  LOG_INFO("print the queue after pop front:");
  QUEUE_traverse(queue, print_item);
  QUEUE_popBack(queue);
  LOG_INFO("print the queue after pop back:");
  QUEUE_traverse(queue, print_item);

  QUEUE_popFront(queue);
  QUEUE_popFront(queue);
  QUEUE_popFront(queue);
  QUEUE_popFront(queue);
  LOG_INFO("print the queue after pop:");
  QUEUE_traverse(queue, print_item);

  QUEUE_destroy(&queue);

  return 0;
}
