/* 
 * szjlib/log.c
 *
 * Copyright (C) 2022 ZhengJie Shi
 * www.shizhengjie169.wordpress.com
 */

#include "log.h"

#include <stdio.h>
#include <stdarg.h>

/* define log output destination */
//#define Log2Printf    LOG
//#define Log2File      LOG
#define Log2Log       LOG  /* stdout and file */

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

  FILE* pf= fopen(PATH_OF_LOG, "a");
  if(pf == NULL)
  {
    fprintf(stdout, "open log file failed\n");
    return;
  }

  va_list va;
  va_start(va, fmt);
  vfprintf(pf, fmt, va);
  va_end(va);

  fclose(pf);
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

  FILE* pf = fopen(PATH_OF_LOG, "a");
  if(pf == NULL)
  {
    fprintf(stdout, "open log file failed\n");
    return;
  }

  va_list va, vf;
  va_start(va, fmt);
  va_copy(vf, va);
  vprintf(fmt, va);
  vfprintf(pf, fmt, vf);  

  fclose(pf);
}
