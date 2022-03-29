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
  NODE_T *head;
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
  LOG_ASSERT_ERROR_RETURN_RET(!list, true, "list = null? are you C programmer");

  return NULL == list->next;
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
  LOG_ASSERT_ERROR_RETURN_RET(!list, true, "list = null? are you C programmer");

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
  LOG_ASSERT_ERROR_RETURN_RET(!list, NULL, "list = null? are you C programmer");

  return ((LIST_INFO_T*)list->data)->head;
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
  LOG_ASSERT_ERROR_RETURN_RET(!list, NULL, "list = null? are you C programmer");

  return ((LIST_INFO_T*)list->data)->tail;
}

/*
 * @group Modifiers
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
  list_info->head = NULL;
  list_info->tail = NULL;
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
  LOG_ASSERT_ERROR_RETURN_RET(!list, false, "list = null? are you C programmer.");

  NODE_T *iterator = list;
  NODE_T *temp;
  while(iterator)
  {
    temp = iterator;
    free(temp);
    iterator = iterator->next;
  }

  *plist = NULL;

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
  LOG_ASSERT_ERROR_RETURN_RET(!list, false, "list = null? are you C programmer");
  LOG_ASSERT_ERROR_RETURN_RET(!node, false, "node = null? are you C programmer");
  LOG_ASSERT_ERROR_RETURN_RET(!data, false, "data = null? are you C programmer");

  LIST_INFO_T *list_info = (LIST_INFO_T*)list->data;
  NODE_T *item = malloc(sizeof(NODE_T) + list_info->element_size);
  LOG_ASSERT_ERROR_RETURN_RET(!item, false, "allocate node's memory failed!");

  /* insert item */
  memcpy(item->data, data, list_info->element_size);
  item->next = node->next;
  node->next = item;  

  ++list_info->list_size;
  list_info->head = list->next;
  if(!item->next)
  {
    list_info->tail = item;
  }

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
int LIST_travel(LIST list, void(*func)(const NODE_T *node))
{
  LOG_ASSERT_ERROR_RETURN_RET(!list, false, "list = null? are you C programmer");
  LOG_ASSERT_ERROR_RETURN_RET(!func, false, "func = null? are you C programmer");

  NODE_T *node = list->next;
  while(node)
  {
    func(node);
    node = node->next;
  }

  return 0;
}

/**
  * @brief  pop element
  * @param  pstQueue: queue control block
  * @retval 0: success
  * @retval 1: fail
  * @author shizj
  * @date   2020.11.15
  */
//int QueuePop(SQ_QUEUE_T* pstQueue)
//{
//  if(pstQueue->elementnum == 0)
//  {
//    SZJ_PRINTF("Pop WARRING: queue is empty!");
//    return -1;
//  }
//  /* user must self-guarantee validity of element type */
//  --pstQueue->elementnum;
//
//  pstQueue->front = (char*)pstQueue->front + pstQueue->elementsize;
//  if(pstQueue->front >= pstQueue->end)
//  {
//    pstQueue->front = pstQueue->base;
//  }
//
//  return 0;
//}
