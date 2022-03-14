#include "log.h"

#include <stdio.h>
#include <stdarg.h>

/* define log output destination */
#define Log2Printf    LOG
//#define Log2File      LOG
//#define Log2Log       LOG  /* stdout and file */

#define PATH_OF_LOG    "log00.log"


static LOG_LEVEL_EN sg_enCurrentLogLevel = LOG_INFO;

/*
 * @brief  set Log Level
 * @param  enLogLevel: log level
 * @retval None
 * @author shizj
 * @date   2021.3.23
 */
void LOG_setLogLevel(LOG_LEVEL_EN enLogLevel)
{
  sg_enCurrentLogLevel = enLogLevel;
}

/*
 * @brief  print log
 * @param  enLogLlevel: log level;
 * @param  fmt: format;
 * @param  ...: parameters.
 * @retval None
 * @author ZhengJie Shi
 * @date   2020.12.09
 */
void Log2Printf(LOG_LEVEL_EN enLogLevel, const char* fmt, ...)
{
  if(sg_enCurrentLogLevel > enLogLevel)
    return;

  va_list va;
  va_start(va, fmt);
  vprintf(fmt, va);
  va_end(va);
}

/*
 * @brief  print log to file
 * @param  enLogLlevel: log level;
 * @param  fmt: format;
 * @param  ...: parameters.
 * @retval None
 * @author ZhengJie Shi
 * @date   2020.12.09
 */
void Log2File(LOG_LEVEL_EN enLogLevel, const char* fmt, ...)
{
  if(sg_enCurrentLogLevel > enLogLevel)
    return;

  FILE* pFile = fopen(PATH_OF_LOG, "a");

  va_list va;
  va_start(va, fmt);
  vfprintf(pFile, fmt, va);
  va_end(va);
}

/*
 * @brief  print log to log for debug
 * @param  enLogLlevel: log level;
 * @param  fmt: format;
 * @param  ...: parameters.
 * @retval None
 * @author ZhengJie Shi
 * @date   2020.12.09
 */
void Log2Log(LOG_LEVEL_EN enLogLevel, const char* fmt, ...)
{
  if(sg_enCurrentLogLevel > enLogLevel)
    return;

  FILE* pFile = fopen("log00.log", "a");

  va_list va;
  va_start(va, fmt);
  vprintf(fmt, va);
  vfprintf(pFile, fmt, va);
  va_end(va);
}
