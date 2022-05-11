#include "types.h"

typedef struct range_
{
  u2 min;
  u2 max;
} range_t;

#define CLAMP(x, min, max) (((x < min) ? (min) : ((x > max) ? (max) : (x))))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

