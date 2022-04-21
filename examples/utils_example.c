#include <stdio.h>

#include "szjlib/utils.h"
#include "szjlib/queue.h"
#include "szjlib/log.h"

int main(int argc, char** argv)
{
  LOG_setLogLevel(LOG_DEBUG);

  UTILS_funfunc();

  UTILS_isBigEndian() ? LOG_INFO("big-endian") : LOG_INFO("little-endian");

	LOG_INFO("storage word length: %d bits", UTILS_wordLength());

	return 0;
}
