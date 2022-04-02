#ifndef SZJLIB_LOG_H_
#define SZJLIB_LOG_H_


typedef enum
{
  LOG_DEBUG = 0,
  LOG_INFO,
  LOG_WARNING,
  LOG_ERROR,
  LOG_LEVEL_NUM
}LOG_LEVEL_EN;

/* log types */
#define LOG_DEBUG(fmt, ...)      do{LOG(LOG_DEBUG,   "[D] %s(%u)@%s: "fmt"\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__);}while(0)
#define LOG_INFO(fmt, ...)       do{LOG(LOG_INFO,    "[I] %s(%u)@%s: "fmt"\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__);}while(0)
#define LOG_WARNING(fmt, ...)    do{LOG(LOG_WARNING, "[W] %s(%u)@%s: "fmt"\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__);}while(0)
#define LOG_ERROR(fmt, ...)      do{LOG(LOG_ERROR,   "[E] %s(%u)@%s: "fmt"\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__);}while(0)

/* check condition then print log */
#define LOG_ASSERT_DEBUG(condition, fmt, ...)      do{if(!(condition))LOG_DEBUG(fmt, ##__VA_ARGS__);}while(0)
#define LOG_ASSERT_INFO(condition, fmt, ...)       do{if(!(condition))LOG_INFO(fmt, ##__VA_ARGS__);}while(0)
#define LOG_ASSERT_WARNING(condition, fmt, ...)    do{if(!(condition))LOG_WARNING(fmt, ##__VA_ARGS__);}while(0)
#define LOG_ASSERT_ERROR(condition, fmt, ...)      do{if(!(condition))LOG_ERROR(fmt, ##__VA_ARGS__);}while(0)

#define LOG_ASSERT_DEBUG_RETURN_VOID(condition, fmt,...)       do{if(!(condition)){LOG_DEBUG(fmt, ##__VA_ARGS__); return;}}while(0)
#define LOG_ASSERT_INFO_RETURN_VOID(condition, fmt,...)        do{if(!(condition)){LOG_INFO(fmt, ##__VA_ARGS__); return;}}while(0)
#define LOG_ASSERT_WARNING_RETURN_VOID(condition, fmt, ...)    do{if(!(condition)){LOG_WARNING(fmt, ##__VA_ARGS__); return;}}while(0)
#define LOG_ASSERT_ERROR_RETURN_VOID(condition, fmt, ...)      do{if(!(condition)){LOG_ERROR(fmt, ##__VA_ARGS__); return;}}while(0)

#define LOG_ASSERT_DEBUG_RETURN_RET(condition, ret, fmt, ...)      do{if(!(condition)){LOG_DEBUG(fmt, ##__VA_ARGS__); return ret;}}while(0)
#define LOG_ASSERT_INFO_RETURN_RET(condition, ret, fmt, ...)       do{if(!(condition)){LOG_INFO(fmt, ##__VA_ARGS__); return ret;}}while(0)
#define LOG_ASSERT_WARNING_RETURN_RET(condition, ret, fmt, ...)    do{if(!(condition)){LOG_WARNING(fmt, ##__VA_ARGS__); return ret;}}while(0)
#define LOG_ASSERT_ERROR_RETURN_RET(condition, ret, fmt, ...)      do{if(!(condition)){LOG_ERROR(fmt, ##__VA_ARGS__); return ret;}}while(0)

void LOG_setLogLevel(LOG_LEVEL_EN enLogLevel);
void LOG(LOG_LEVEL_EN enLogLevel, const char* fmt, ...);

#endif
