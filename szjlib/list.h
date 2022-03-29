#ifndef SZJLIB_LIST_H_
#define SZJLIB_LIST_H_

#include <stdio.h>
#include <stdbool.h>


typedef struct node
{
  struct node *next;
  char data[];
}NODE_T, *LIST;


/******* Capacity *******/
bool LIST_empty(LIST list);
size_t LIST_size(LIST list);

/******* Element access *******/
NODE_T* LIST_back(LIST list);
NODE_T* LIST_front(LIST list);

/******* Modifiers *******/
bool LIST_create(LIST *plist, size_t elementSize);
bool LIST_destroy(LIST *plist);
bool LIST_addItem(LIST list, NODE_T *node, void *data);
int LIST_travel(LIST list, void(*func)(const NODE_T *node));

#endif
