/* 
 * szjlib/queue.c
 * Implemented by circular buffer.
 * 
 * Copyright (C) 2022 ZhengJie Shi
 * www.shizhengjie169.wordpress.com
 */

#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "log.h"


struct queue
{
  void *head;
  void *tail;
  size_t element_size;
  size_t size;
  size_t max_size;
  char buff[];
};

/*
 *@group Capacity
 */

/*
 * @brief  check whether queue is empty.
 * @param  queue: the queue.
 * @retval 0: not empty;
 * @retval 1: empty.
 * @author shizj
 * @date   2022.03.29
 */
bool QUEUE_empty(QUEUE queue)
{
  /* assume not-initialized is empty lqueue. */
  LOG_ASSERT_ERROR_RETURN_RET(queue, true, "queue = null? are you C programmer?");

  return 0 == queue->size;
}

/*
 * @brief  check whether queue is full.
 * @param  queue: the queue.
 * @retval 0: not empty;
 * @retval 1: empty.
 * @author shizj
 * @date   2022.03.29
 */
bool QUEUE_full(QUEUE queue)
{
  /* assume not-initialized is empty lqueue. */
  LOG_ASSERT_ERROR_RETURN_RET(queue, true, "queue = null? are you C programmer?");

  return queue->size == queue->max_size;
}

/*
 * @brief  get size of the queue.
 * @param  queue: the queue.
 * @retval size of the queue.
 * @author shizj
 * @date   2022.03.29
 */
size_t QUEUE_size(QUEUE queue)
{
  /* assume not-initialized is empty lqueue. */
  LOG_ASSERT_ERROR_RETURN_RET(queue, true, "queue = null? are you C programmer?");

  return queue->size;
}

/*
 * @group Element access
 */

/*
 * @brief  get queue's head item.
 * @param  queue: the queue.
 * @retval point of queue's first item.
 * @author shizj
 * @date   2022.03.29
 */
void* QUEUE_front(QUEUE queue)
{
  LOG_ASSERT_ERROR_RETURN_RET(queue, NULL, "queue = null? are you C programmer?");

  return queue->head;
}

/*
 * @brief  get queue's tail item.
 * @param  queue: the queue.
 * @retval point of queue's last item.
 * @author shizj
 * @date   2022.03.29
 */
void* QUEUE_back(QUEUE queue)
{
  LOG_ASSERT_ERROR_RETURN_RET(queue, NULL, "queue = null? are you C programmer?");

  return queue->tail;
}

/*
 * @brief  get queue's item by index.
 * @param  queue: the queue.
 * @param  pos: index of item.
 * @retval point of queue's item.
 * @author shizj
 * @date   2022.03.29
 */
void* QUEUE_at(QUEUE queue, size_t pos)
{
  LOG_ASSERT_ERROR_RETURN_RET(queue, NULL, "queue = null? are you C programmer?");
  LOG_ASSERT_ERROR_RETURN_RET(pos < queue->size, NULL, "pos out of queue size.");

  void *item;
  if((char*)queue->head + pos * queue->element_size > queue->buff + queue->element_size * (queue->max_size - 1))
  {
    item = queue->head - queue->element_size * (queue->max_size - pos - 1);
  }
  else
  {
    item = queue->head + pos * queue->element_size;
  }

  return item;
}

/*
 * @group Modifiers
 */

/*
 * @brief  add item to queue's head.
 * @param  queue: the queue.
 * @param  data: point of the data.
 * @retval 0: success;
 * @retval 1: fail.
 * @author shizj
 * @date   2022.03.29
 */
bool QUEUE_pushFront(QUEUE queue, void *data)
{
  LOG_ASSERT_ERROR_RETURN_RET(queue, false, "queue = null? are you C programmer?");
  LOG_ASSERT_ERROR_RETURN_RET(data, false, "data = null? are you C programmer?");
  LOG_ASSERT_ERROR_RETURN_RET(queue->size < queue->max_size, false, "full queue, can't push element.");

  /* update head */
  if(queue->size)
  {
    if(queue->head == queue->buff)
    {
      queue->head = queue->buff + queue->element_size * (queue->max_size - 1);
    }
    else
    {
      queue->head = queue->head - queue->element_size;
    }
  }

  memcpy(queue->head, data, queue->element_size);
  ++queue->size;

  return true;
}

/*
 * @brief  add item to queue's tail.
 * @param  queue: the queue.
 * @param  data: point of the data.
 * @retval 0: success;
 * @retval 1: fail.
 * @author shizj
 * @date   2022.03.29
 */
bool QUEUE_pushBack(QUEUE queue, void *data)
{
  LOG_ASSERT_ERROR_RETURN_RET(queue, false, "queue = null? are you C programmer?");
  LOG_ASSERT_ERROR_RETURN_RET(data, false, "data = null? are you C programmer?");
  LOG_ASSERT_ERROR_RETURN_RET(queue->size < queue->max_size, false, "full queue, can't push element.");
 
  /* update tail */
  if(queue->size)
  {
    if(queue->tail == queue->buff + queue->element_size * (queue->max_size - 1))
    {
      queue->tail = queue->buff;
    }
    else
    {
      queue->tail = queue->tail + queue->element_size;
    }
  }

  memcpy(queue->tail, data, queue->element_size);
  ++queue->size;

  return true;
}

/*
 * @brief  remove queue's head item.
 * @param  queue: point of the queue.
 * @retval 0: success;
 * @retval 1: fail.
 * @author shizj
 * @date   2022.03.29
 */
bool QUEUE_popFront(QUEUE queue)
{
  LOG_ASSERT_ERROR_RETURN_RET(queue, false, "queue = null? are you C programmer?");
  LOG_ASSERT_ERROR_RETURN_RET(queue->size, false, "can't pop empty queue.");

  /* update head */
  if(queue->head == queue->buff + queue->element_size * (queue->max_size - 1))
  {
    queue->head = queue->buff;
  }
  else
  {
    queue->head = queue->head + queue->element_size;
  }

  --queue->size;

  return true;   
}

/*
 * @brief  remove queue's tail node.
 * @param  queue: point of the queue.
 * @retval 0: success;
 * @retval 1: fail.
 * @author shizj
 * @date   2022.03.29
 */
bool QUEUE_popBack(QUEUE queue)
{
  LOG_ASSERT_ERROR_RETURN_RET(queue, false, "queue = null? are you C programmer?");
  LOG_ASSERT_ERROR_RETURN_RET(queue->size, false, "can't pop empty queue.");

  /* update tail */
  if(queue->tail == queue->buff)
  {
    queue->tail = queue->buff + queue->element_size * (queue->max_size - 1);
  }
  else
  {
    queue->tail = queue->tail - queue->element_size;
  }

  --queue->size;

  return true;   
}

/*
 * @group Operations
 */

/*
 * @brief  create queue.
 * @param  queue: point of queue.
 * @param  elementSize: size of queue element.
 * @retval 0: success;
 * @retval 1: fail.
 * @author shizj
 * @date   2020.11.15
 */
bool QUEUE_create(QUEUE *pqueue, size_t queue_size, size_t element_size)
{
  LOG_ASSERT_ERROR_RETURN_RET(pqueue, false, "pqueue = null? are you C programmer?");

  QUEUE queue = *pqueue;
  LOG_ASSERT_ERROR_RETURN_RET(!queue, false, "queue != null? destory it first.");
  LOG_ASSERT_ERROR_RETURN_RET(queue_size, false, "queue size = 0? are you kidding me???");
  LOG_ASSERT_ERROR_RETURN_RET(element_size, false, "element size = 0? are you kidding me???");

  queue = malloc(sizeof(struct queue) + element_size * queue_size);
  LOG_ASSERT_ERROR_RETURN_RET(queue, false, "allocate queue's memory failed!");

  queue->head = queue->tail = queue->buff;
  queue->size = 0;
  queue->max_size = queue_size;
  queue->element_size = element_size;

  *pqueue = queue;

  return true;
}

/*
 * @brief  destroy queue.
 * @param  queue: point of queue.
 * @retval 0: success;
 * @retval 1: fail.
 * @author shizj
 * @date   2020.11.15
 */
bool QUEUE_destroy(QUEUE *pqueue)
{
  QUEUE queue = *pqueue;
  LOG_ASSERT_ERROR_RETURN_RET(queue, false, "queue = null? are you C programmer?");

  free(queue);

  *pqueue = NULL;

  return true;
}

/*
 * @brief  travel the queue and run function.
 * @param  queue: point of the queue.
 * @param  func: function point.
 * @retval 0: success
 * @retval 1: fail
 * @author shizj
 * @date   2020.11.15
 */
bool QUEUE_traverse(QUEUE queue, void(*func)(void*))
{
  LOG_ASSERT_ERROR_RETURN_RET(queue, false, "queue = null? are you C programmer.");
  LOG_ASSERT_ERROR_RETURN_RET(func, false, "func = null? are you C programmer.");
  LOG_ASSERT_ERROR_RETURN_RET(queue->size, false, "empty queue.");

  void *item = queue->head;
  for(size_t size = 0; size < queue->size; ++size)
  {
    func(item);

    item += queue->element_size;
    if(item == queue->buff + queue->element_size * queue->max_size)
    {
      item = queue->buff;
    }
  }

  return true;
}

/*
 * @brief  clear the queue.
 * @param  queue: point of the queue.
 * @retval 0: success
 * @retval 1: fail
 * @author shizj
 * @date   2020.11.15
 */
bool QUEUE_clear(QUEUE queue)
{
  LOG_ASSERT_ERROR_RETURN_RET(queue, false, "queue = null? are you C programmer?");

  queue->head = queue->tail = queue->buff;
  queue->size = 0;

  return true;
}
