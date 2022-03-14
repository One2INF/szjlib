#ifndef SZJLIB_LOG_H_
#define SZJLIB_LOG_H_


typedef enum
{
  LOG_INFO = 0,
  LOG_WARNING,
  LOG_ERROR,
  LOG_LEVEL_NUM
}LOG_LEVEL_EN;

/* log types */
#define LOG_INFO(fmt, ...)       do{LOG(LOG_INFO,    "[I] %s(%u)@%s: "fmt"\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__);}while(0)
#define LOG_WARNING(fmt, ...)    do{LOG(LOG_WARNING, "[W] %s(%u)@%s: "fmt"\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__);}while(0)
#define LOG_ERROR(fmt, ...)      do{LOG(LOG_ERROR,   "[E] %s(%u)@%s: "fmt"\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__);}while(0)

/* check condition then print log */
#define LOG_INFO_NO_RETURN(condition, fmt, ...)        do{if(condition)LOG_INFO(fmt, ##__VA_ARGS__);}while(0)
#define LOG_WARNING_NO_RETURN(condition, fmt, ...)     do{if(condition)LOG_WARNING(fmt, ##__VA_ARGS__);}while(0)
#define LOG_ERROR_NO_RETURN(condition, fmt, ...)       do{if(condition)LOG_ERROR(fmt, ##__VA_ARGS__);}while(0)

#define LOG_INFO_RETURN_VOID(condition, fmt, ...)      do{if(condition){LOG_INFO(fmt, ##__VA_ARGS__); return;}}while(0)
#define LOG_WARNING_RETURN_VOID(condition, fmt, ...)   do{if(condition){LOG_WARNING(fmt, ##__VA_ARGS__); return;}}while(0)
#define LOG_RETURN_VOID_ERROR(condition, fmt, ...)     do{if(condition){LOG_ERROR(fmt, ##__VA_ARGS__); return;}}while(0)

#define LOG_INFO_RETURN(condition, ret, fmt, ...)      do{if(condition){LOG_INFO(fmt, ##__VA_ARGS__); return ret;}}while(0)
#define LOG_WARNING_RETURN(condition, ret, fmt, ...)   do{if(condition){LOG_WARNING(fmt, ##__VA_ARGS__); return ret;}}while(0)
#define LOG_ERROR_RETURN(condition, ret, fmt, ...)     do{if(condition){LOG_ERROR(fmt, ##__VA_ARGS__); return ret;}}while(0)

void LOG_setLogLevel(LOG_LEVEL_EN enLogLevel);
void LOG(LOG_LEVEL_EN enLogLevel, const char* fmt, ...);

#endif
