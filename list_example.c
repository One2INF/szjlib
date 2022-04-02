#include <stdio.h>
#include <stdlib.h>

#include "szjlib/log.h"
#include "szjlib/list.h"


#define STR_SIZE    32

typedef struct
{
  int a;
  char str[STR_SIZE];
}DATA_T;

void print_node(void *data)
{
  LOG_ASSERT_ERROR_RETURN_VOID(data, "node = null.");
  LOG_INFO("%4d %16s", ((DATA_T*)data)->a, ((DATA_T*)data)->str);
}

int main(void)
{
  LIST list = NULL;
  LIST_create(&list, sizeof(DATA_T));

  LIST_addItem(list, list, &(DATA_T){1, "I am 1"});
  LIST_addItem(list, list, &(DATA_T){2, "I am 2"});
  LIST_addItem(list, list, &(DATA_T){3, "I am 3"});
  LIST_addItem(list, list, &(DATA_T){4, "I am 4"});
  LIST_addItem(list, list, &(DATA_T){5, "I am 5"});

  LOG_INFO("empty: %d", LIST_empty(list));
  LOG_INFO("size: %zd", LIST_size(list));

  LOG_INFO("print front node:");
  print_node(LIST_front(list));
  LOG_INFO("print back node:");
  print_node(LIST_back(list));

  LOG_INFO("print list:");
  LIST_traverse(list, print_node);

  LIST_pushFront(list, &(DATA_T){6, "push front"});
  LIST_pushBack(list, &(DATA_T){7, "push back"});
  LOG_INFO("print list:");
  LIST_traverse(list, print_node);

  LIST_popFront(list);
  LOG_INFO("print list after pop front:");
  LIST_traverse(list, print_node);

  LIST_popBack(list);
  LOG_INFO("print list after pop back:");
  LIST_traverse(list, print_node);

  LIST_destroy(&list);

  return 0;
}
