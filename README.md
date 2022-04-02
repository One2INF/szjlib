# szjlib
My log module, ADT, utils.

# LOG
``` C
LOG_DEBUG(fmt, ...);
LOG_INFO(fmt, ...);
LOG_WARNING(fmt, ...);
LOG_ERROR(fmt, ...);

/* check condition then print log */
LOG_ASSERT_DEBUG(condition, fmt, ...);
LOG_ASSERT_INFO(condition, fmt, ...);
LOG_ASSERT_WARNING(condition, fmt, ...);

LOG_ASSERT_DEBUG_RETURN_VOID(condition, fmt,...);
LOG_ASSERT_INFO_RETURN_VOID(condition, fmt,...);
LOG_ASSERT_WARNING_RETURN_VOID(condition, fmt, ...);
LOG_ASSERT_ERROR_RETURN_VOID(condition, fmt, ...);

LOG_ASSERT_DEBUG_RETURN_RET(condition, ret, fmt, ...);
LOG_ASSERT_INFO_RETURN_RET(condition, ret, fmt, ...);
LOG_ASSERT_WARNING_RETURN_RET(condition, ret, fmt, ...);
LOG_ASSERT_ERROR_RETURN_RET(condition, ret, fmt, ...);

void LOG_setLogLevel(LOG_LEVEL_EN enLogLevel);
void LOG(LOG_LEVEL_EN enLogLevel, const char* fmt, ...);
```

# ADT
## list
``` C
/******* Capacity *******/
bool LIST_empty(LIST list);
size_t LIST_size(LIST list);

/******* Element access *******/
void* LIST_front(LIST list);
void* LIST_back(LIST list);

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
```

## queue
``` C
/******* Capacity *******/
bool QUEUE_empty(QUEUE queue);
size_t QUEUE_size(QUEUE queue);
size_t QUEUE_maxSize(QUEUE queue);

/******* Element access *******/
void* QUEUE_front(QUEUE queue);
void* QUEUE_back(QUEUE queue);
void* QUEUE_at(QUEUE queue, size_t pos);

/******* Modifiers *******/
bool QUEUE_pushFront(QUEUE queue, void *data);
bool QUEUE_pushBack(QUEUE queue, void *data);
bool QUEUE_popFront(QUEUE queue);
bool QUEUE_popBack(QUEUE queue);

/******* Opertaions *******/
bool QUEUE_create(QUEUE *pqueue, size_t queue_size, size_t element_size);
bool QUEUE_destroy(QUEUE *pqueue);
bool QUEUE_traverse(QUEUE queue, void(*func)(void*));
bool QUEUE_clear(QUEUE queue);
```

# UTILS
``` C
/* macro function */
#define UTILLS_VARIABLE_NAME(value) (#value)


void UTILS_funfunc(void);
int UTILS_wordLength(void);
bool UTILS_isBigEndian(void);
```

# NOTES
- use C11, should add complie flag `-std=c11`.
