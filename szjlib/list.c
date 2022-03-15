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


/*
 * @brief  create list.
 * @param  list: point of list.
 * @param  elementSize: size of list element.
 * @retval 0: success;
 * @retval 1: fail.
 * @author shizj
 * @date   2020.11.15
 */
bool List_create(LIST_T* list, size_t elementSize)
{
  if(!list)
  {
    LOG_ERROR("list = null? are you C programmer?");
    return false;
  }

  if(0 == elementSize)
  {
    LOG_ERROR("size = 0? are you kidding me???");
    return false;
  }

  list->head = NULL;
  list->tail = NULL;
  list->element_size = elementSize;
  list->list_size = 0;

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
bool LIST_destroy(LIST_T* list)
{
  if(!list)
  {
    LOG_ERROR("list = null? are you C programmer?");
    return false;
  }

  NODE_T *iterator = list->head;
  NODE_T *temp;
  while(iterator)
  {
    temp = iterator;
    free(temp);
    iterator = iterator->next;
  }

  list->head = NULL;
  list->tail = NULL;
  list->element_size = 0;
  list->list_size = 0;

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
bool LIST_addItem(LIST_T *list, NODE_T *node, void *data)
{
  if(!list)
  {
    LOG_ERROR("list = null? are you C programmer?");
    return false;
  }

//  if(!node)
//  {
//    LOG_ERROR("node = null? are you C programmer?");
//    return false;
//  }

  if(!data)
  {
    LOG_ERROR("data = null? are you C programmer?");
    return false;
  }

  NODE_T *item = malloc(sizeof(NODE_T) + list->element_size);
  if(!item)
  {
    LOG_ERROR("allocate node's memory failed!");
    return false;
  }

  NODE_T **p = &list->head;
  while (*p)
  {
    p = &(*p)->next;
  }

  memcpy(item->data, data, list->element_size);
  item->next = NULL;
  *p = item;  

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
int LIST_travel(LIST_T *list, void(*func)(const NODE_T *node))
{
  if(!list)
  {
    LOG_ERROR("list = null? are you C programmer?");
    return false;
  }

  if(!func)
  {
    LOG_ERROR("func = null? are you C programmer?");
    return false;
  }

  NODE_T *node = list->head;
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
