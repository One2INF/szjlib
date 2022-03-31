/* 
 * szjlib/list.c
 * 
 * Copyright (C) 2022 ZhengJie Shi
 * www.shizhengjie169.wordpress.com
 */

#include "list.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"


typedef struct
{
  /* head = list->next */
  NODE_T *tail;
  size_t element_size;
  size_t list_size;
}LIST_INFO_T;

/*
 *@group Capacity
 */

/*
 * @brief  check whether list is empty.
 * @param  list: point of list.
 * @retval 0: not empty;
 * @retval 1: empty.
 * @author shizj
 * @date   2022.03.29
 */
bool LIST_empty(LIST list)
{
  /* assume not-initialized is empty llist. */
  LOG_ASSERT_ERROR_RETURN_RET(!list, true, "list = null? are you C programmer?");

  return 0 == ((LIST_INFO_T*)list->data)->list_size;
}

/*
 * @brief  size of the list.
 * @param  list: point of list.
 * @retval size of the list.
 * @author shizj
 * @date   2022.03.29
 */
size_t LIST_size(LIST list)
{
  /* assume not-initialized is empty llist. */
  LOG_ASSERT_ERROR_RETURN_RET(!list, true, "list = null? are you C programmer?");

  return ((LIST_INFO_T*)list->data)->list_size;
}

/*
 * @group Element access
 */

/*
 * @brief  get point of list's first node.
 * @param  list: point of list.
 * @retval point of list's first node.
 * @author shizj
 * @date   2022.03.29
 */
NODE_T* LIST_front(LIST list)
{
  LOG_ASSERT_ERROR_RETURN_RET(!list, NULL, "list = null? are you C programmer?");

  return list->next;
}

/*
 * @brief  get node of list's last node.
 * @param  list: point of list.
 * @retval point of list's last node.
 * @author shizj
 * @date   2022.03.29
 */
NODE_T* LIST_back(LIST list)
{
  LOG_ASSERT_ERROR_RETURN_RET(!list, NULL, "list = null? are you C programmer?");
  LOG_ASSERT_ERROR_RETURN_RET(!((LIST_INFO_T*)list->data)->list_size, NULL, "empty list, no back element.");

  return ((LIST_INFO_T*)list->data)->tail;
}

/*
 * @group Modifiers
 */

/*
 * @brief  add node to list's head.
 * @param  list: point of the list.
 * @param  data: point of the data.
 * @retval 0: success;
 * @retval 1: fail.
 * @author shizj
 * @date   2022.03.29
 */
bool LIST_pushFront(LIST list, void *data)
{
  LOG_ASSERT_ERROR_RETURN_RET(!list, false, "list = null? are you C programmer?");
  LOG_ASSERT_ERROR_RETURN_RET(!data, false, "data = null? are you C programmer?");
 
  LIST_INFO_T *list_info = (LIST_INFO_T*)list->data;
  NODE_T *item = malloc(sizeof(NODE_T) + list_info->element_size);
  LOG_ASSERT_ERROR_RETURN_RET(!item, false, "allocate node's memory failed!");
  memcpy(item->data, data, list_info->element_size);
  item->next = list->next;

  /* update head and tail */
  list->next = item;
  if(!list_info->list_size)
  {
    list_info->tail = item;
  }

  ++list_info->list_size;

  return true;
}

/*
 * @brief  add node to list's tail.
 * @param  list: point of the list.
 * @param  data: point of the data.
 * @retval 0: success;
 * @retval 1: fail.
 * @author shizj
 * @date   2022.03.29
 */
bool LIST_pushBack(LIST list, void *data)
{
  LOG_ASSERT_ERROR_RETURN_RET(!list, false, "list = null? are you C programmer?");
  LOG_ASSERT_ERROR_RETURN_RET(!data, false, "data = null? are you C programmer?");
 
  LIST_INFO_T *list_info = (LIST_INFO_T*)list->data;
  NODE_T *item = malloc(sizeof(NODE_T) + list_info->element_size);
  LOG_ASSERT_ERROR_RETURN_RET(!item, false, "allocate node's memory failed!");
  memcpy(item->data, data, list_info->element_size);
  item->next = NULL;

  list_info->tail->next = item;
  /* update head and tail */
  if(!list_info->list_size)
  {
    list->next = item;
  }
  list_info->tail = item;

  ++list_info->list_size;

  return true;
}

/*
 * @brief  add a item to list.
 * @param  list: point of the list.
 * @param  node: item will be added behind the node.
 * @param  data: point of the data.
 * @retval 0: success;
 * @retval 1: fail.
 * @author shizj
 * @date   2020.11.15
 */
bool LIST_addItem(LIST list, NODE_T *node, void *data)
{
  LOG_ASSERT_ERROR_RETURN_RET(!list, false, "list = null? are you C programmer?");
  LOG_ASSERT_ERROR_RETURN_RET(!node, false, "node = null? are you C programmer?");
  LOG_ASSERT_ERROR_RETURN_RET(!data, false, "data = null? are you C programmer?");

  LIST_INFO_T *list_info = (LIST_INFO_T*)list->data;
  NODE_T *item = malloc(sizeof(NODE_T) + list_info->element_size);
  LOG_ASSERT_ERROR_RETURN_RET(!item, false, "allocate node's memory failed!");

  /* insert item */
  memcpy(item->data, data, list_info->element_size);
  item->next = node->next;
  node->next = item;  

  /* only need update tail, head has been updated when spliced list */
  if(!list_info->list_size)
  {
    list_info->tail = item;
  }

  ++list_info->list_size;

  return true;
}

/*
 * @brief  remove list's head node.
 * @param  list: point of the list.
 * @retval 0: success;
 * @retval 1: fail.
 * @author shizj
 * @date   2022.03.29
 */
bool LIST_popFront(LIST list)
{
  LOG_ASSERT_ERROR_RETURN_RET(!list, false, "list = null? are you C programmer?");
  LOG_ASSERT_ERROR_RETURN_RET(!list->next, false, "can't pop empty list.");

  LIST_INFO_T *list_info = (LIST_INFO_T*)list->data;
  NODE_T *head = list->next;
  --list_info->list_size;

  /* update head and tail */
  list->next = list->next->next;
  if(!list_info->list_size)
  {
    list_info->tail = list;
  }

  free(head);

  return true;   
}

/*
 * @brief  remove list's tail node.
 * @param  list: point of the list.
 * @retval 0: success;
 * @retval 1: fail.
 * @author shizj
 * @date   2022.03.29
 */
bool LIST_popBack(LIST list)
{
  LOG_ASSERT_ERROR_RETURN_RET(!list, false, "list = null? are you C programmer?");
  LOG_ASSERT_ERROR_RETURN_RET(!list->next, false, "can't pop empty list.");

  LIST_INFO_T *list_info = (LIST_INFO_T*)list->data;
  NODE_T *tail = list_info->tail;
  --list_info->list_size;

  /* update head and tail */
  if(list_info->list_size)
  {
    NODE_T *parent_of_tail = list;
    while(parent_of_tail && parent_of_tail->next != list_info->tail)
    {
      parent_of_tail = parent_of_tail->next;
    }
    list_info->tail = parent_of_tail;
    list_info->tail->next = NULL;
  }
  else
  {
    list->next = NULL;
    list_info->tail = list;
  }

  free(tail);

  return true;   
}

/*
 * @brief  remove node from list.
 * @param  list: point of the list.
 * @param  node: point of the node.
 * @retval 0: success;
 * @retval 1: fail.
 * @author shizj
 * @date   2022.03.29
 */
bool LIST_erase(LIST list, NODE_T *node)
{
  LOG_ASSERT_ERROR_RETURN_RET(!list, false, "list = null? are you C programmer?");
  LOG_ASSERT_ERROR_RETURN_RET(!list->next, false, "can't pop empty list.");
  LOG_ASSERT_ERROR_RETURN_RET(!node, false, "node = null? are you C programmer?");

  NODE_T *parent_node;
  for(parent_node = list; parent_node->next != NULL; parent_node = parent_node->next)
  {
    if(parent_node->next == node)
      break;
  }
  LOG_ASSERT_ERROR_RETURN_RET(parent_node->next != node, false, "node isn't belong to list?");

  parent_node->next = node->next;
  LIST_INFO_T *list_info = (LIST_INFO_T*)list->data;
  --list_info->list_size;

  /* only need update tail, head has been updated when spliced list */
  if(list_info->tail == node)
  {
    list_info->tail = parent_node;
    list_info->tail->next = NULL;
  }

  free(node);

  return true;
}

/*
 * @group Operations
 */

/*
 * @brief  create list.
 * @param  list: point of list.
 * @param  elementSize: size of list element.
 * @retval 0: success;
 * @retval 1: fail.
 * @author shizj
 * @date   2020.11.15
 */
bool LIST_create(LIST *plist, size_t elementSize)
{
  LOG_ASSERT_ERROR_RETURN_RET(!plist, false, "plist = null? are you C programmer?");

  LIST list = *plist;
  LOG_ASSERT_ERROR_RETURN_RET(list, false, "list != null? destory it first.");
  LOG_ASSERT_ERROR_RETURN_RET(0 == elementSize, false, "element size = 0? are you kidding me???");

  list = *plist = malloc(sizeof(NODE_T) + sizeof(LIST_INFO_T));
  list->next = NULL;
  LIST_INFO_T *list_info = (LIST_INFO_T*)list->data;
  /* tail = list for convince */
  list_info->tail = list;
  list_info->element_size = elementSize;
  list_info->list_size = 0;

  return true;
}

/*
 * @brief  destroy list.
 * @param  list: point of list.
 * @retval 0: success;
 * @retval 1: fail.
 * @author shizj
 * @date   2020.11.15
 */
bool LIST_destroy(LIST *plist)
{
  LIST list = *plist;
  LOG_ASSERT_ERROR_RETURN_RET(!list, false, "list = null? are you C programmer?");

  NODE_T *iterator = list;
  NODE_T *temp;
  do
  {
    temp = iterator;
    free(temp);
  }while((iterator = iterator->next));

  *plist = NULL;

  return true;
}

/*
 * @brief  travel the list and run function.
 * @param  list: point of the list.
 * @param  func: function point.
 * @retval 0: success
 * @retval 1: fail
 * @author shizj
 * @date   2020.11.15
 */
bool LIST_travel(LIST list, void(*func)(const NODE_T*))
{
  LOG_ASSERT_ERROR_RETURN_RET(!list, false, "list = null? are you C programmer");
  LOG_ASSERT_ERROR_RETURN_RET(!func, false, "func = null? are you C programmer");

  NODE_T *iterator = list->next;
  while(iterator)
  {
    func(iterator);
    iterator = iterator->next;
  }

  return true;
}

/*
 * @brief  clear the list's elements.
 * @param  list: point of the list.
 * @retval 0: success
 * @retval 1: fail
 * @author shizj
 * @date   2020.11.15
 */
bool LIST_clear(LIST list)
{
  LOG_ASSERT_ERROR_RETURN_RET(!list, false, "list = null? are you C programmer?");

  NODE_T *iterator = list->next;
  NODE_T *temp;
  while(iterator)
  {
    temp = iterator;
    free(temp);
    iterator = iterator->next;
  };

  list->next = NULL;
  LIST_INFO_T *list_info = (LIST_INFO_T*)list->data;
  /* tail = list for convince */
  list_info->tail = list;
  list_info->list_size = 0;

  return true;
}
