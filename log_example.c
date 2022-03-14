#include<stdio.h>

#include"szjlib/log.h"


enum
{
  FALSE = 0,
  TRUE
};

void void_f(void)
{
  LOG_WARNING_CHECK_RETURN_VOID(TRUE, "return from void_f.");

  fprintf(stdout, "this line shouldn't print.\n");
}

int int_f(void)
{
  LOG_WARNING_CHECK_RETURN_RET(TRUE, -1, "return -1 from int_f.");
  
  fprintf(stdout, "this line shouldn't print.\n");
  return 0;
}

int main(void)
{
  fprintf(stdout, "default log level is info.\n");
  LOG_INFO("log info!");
  LOG_WARNING("log warning!");
  LOG_ERROR("log error!");

  fprintf(stdout, "\nset log level to warning, log info shouldn't show.\n");
  LOG_setLogLevel(LOG_WARNING);

  LOG_INFO("log info!");
  LOG_WARNING("log warning!");
  LOG_ERROR("log error!");

  fprintf(stdout, "\nlog check fuction.\n");
  LOG_INFO_CHECK(TRUE, "log info check");
  LOG_WARNING_CHECK(TRUE, "log warning check");
  LOG_ERROR_CHECK(TRUE, "log error check");

  fprintf(stdout, "\n");
  void_f();
  fprintf(stdout, "int_f(): %d\n", int_f());
  
  return 0;
}