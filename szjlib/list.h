#ifndef SZJLIB_LIST_H_
#define SZJLIB_LIST_H_

#include <stdio.h>
#include <stdbool.h>


typedef struct node NODE_T;
typedef struct node* LIST;

/******* Capacity *******/
bool LIST_empty(LIST list);
size_t LIST_size(LIST list);

/******* Element access *******/
NODE_T* LIST_front(LIST list);
NODE_T* LIST_back(LIST list);

/******* Modifiers *******/
bool LIST_pushFront(LIST list, void *data);
bool LIST_pushBack(LIST list, void *data);
bool LIST_addItem(LIST list, NODE_T *node, void *data);
bool LIST_popFront(LIST list);
bool LIST_popBack(LIST list);
bool LIST_erase(LIST list, NODE_T *node);

/******* Opertaions *******/
bool LIST_create(LIST *plist, size_t elementSize);
bool LIST_destroy(LIST *plist);
bool LIST_traverse(LIST list, void(*func)(void*));
bool LIST_clear(LIST list);

#endif
