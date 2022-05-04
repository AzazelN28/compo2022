#include "types.h"

typedef struct point_
{
  s2 x, y;
} point_t;

point_t *point_set(point_t *o, s2 x, s2 y);
point_t *point_add(point_t *o, const point_t *a, const point_t *b);
point_t *point_subtract(point_t *o, const point_t *a, const point_t *b);
point_t *point_multiply(point_t *o, const point_t *a, const point_t *b);
point_t *point_divide(point_t *o, const point_t *a, const point_t *b);
point_t *point_scale(point_t *o, const point_t *i, f4 s);
f4 point_length(const point_t *p);
f4 point_direction(const point_t *p);
