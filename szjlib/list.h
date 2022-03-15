#ifndef SZJLIB_LIST_H_
#define SZJLIB_LIST_H_

#include <stdio.h>
#include <stdbool.h>


typedef struct node
{
  struct node *next;
  char data[];
}NODE_T;

typedef struct
{
  NODE_T *head;
  NODE_T *tail;
  size_t element_size;
  size_t list_size;
}LIST_T;


bool List_create(LIST_T* list, size_t elementSize);
bool LIST_destroy(LIST_T* list);
bool LIST_addItem(LIST_T *list, NODE_T *node, void *data);
int LIST_travel(LIST_T *list, void(*func)(const NODE_T *node));

#endif
