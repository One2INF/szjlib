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

void print_node(const NODE_T *node)
{
  DATA_T *data = (DATA_T *)node->data;
  LOG_INFO("%4d %16s", data->a, data->str);
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
  LIST_travel(list, print_node);
  LIST_destroy(&list);

  return 0;
}