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

void func(const NODE_T *node)
{
  DATA_T *data = (DATA_T *)node->data;
  LOG_INFO("%4d %32s", data->a, data->str);
}

int main(void)
{
  LIST_T stList;
  List_create(&stList, sizeof(DATA_T));

  LIST_addItem(&stList, stList.head, &(DATA_T){1, "i am 1"});
  LIST_addItem(&stList, stList.head, &(DATA_T){2, "i am 2"});
  LIST_addItem(&stList, stList.head, &(DATA_T){3, "i am 3"});
  LIST_addItem(&stList, stList.head, &(DATA_T){4, "i am 4"});
  LIST_addItem(&stList, stList.head, &(DATA_T){5, "i am 5"});

  LIST_travel(&stList, func);
  LIST_destroy(&stList);

  return 0;
}