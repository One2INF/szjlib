#include "utils.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "log.h"


/* funny functions */

/**
  * @brief  printf unix
  * @param  None
  * @retval void
  * @author AT&T Bell Labs and David Korn
  * @date   4th International Obfuscated C Code Contest (1987)
  */
void UTILS_funfunc(void)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-contains-nul"
#define UNIX    1

  LOG_DEBUG("%s\012\0", &(UNIX)["have"]);
  LOG_DEBUG("%s\012\0", (UNIX)["have"] + "fun" - 0x60);

  printf(&UNIX["\021%six\012\0"], (UNIX)["have"] + "fun" - 0x60);
 
 #pragma GCC diagnostic pop
}

/**
  * @brief  judge the compiler chain's storage word length
  * @param  None
  * @retval word bits.
  * @author shizj
  * @date   2020.11.16
  */
int UTILS_wordLength(void)
{
  return sizeof(int) * 8;
}

/**
  * @brief  judge the machine whether big-endgian or little-endian
  * @param  None
  * @retval 0: big-endgian
  * @retval 1: little-endian
  * @author shizj
  * @date   2020.11.15
  */
bool UTILS_isBigEndian(void)
{
  uint16_t data = 0x1234;
  char *p = (char*)&data;

  if(0x12 == *p)
    return true;
  else
    return false;
}
