#include <stdlib.h>
#include <time.h>

#include "types.h"

void random_init()
{
  time_t t;
  srand((u4)time(&t));
}

u2 random_between(u2 min, u2 max)
{
  return min + (rand() % (max - min + 1));
}
