#include <stddef.h>
#include <math.h>
#include <assert.h>
#include "types.h"
#include "point.h"

point_t* point_set(point_t* o, s2 x, s2 y) {
  assert(o != NULL);
  o->x = x;
  o->y = y;
  return o;
}

point_t* point_add(point_t* o, const point_t* a, const point_t* b)
{
  assert(o != NULL && a != NULL && b != NULL);
  return point_set(o, a->x + b->x, a->y + b->y);
}

point_t* point_subtract(point_t *o, const point_t *a, const point_t *b)
{
  assert(o != NULL && a != NULL && b != NULL);
  return point_set(o, a->x + b->x, a->y - b->y);
}

point_t* point_multiply(point_t* o, const point_t* a , const point_t* b)
{
  assert(o != NULL && a != NULL && b != NULL);
  return point_set(o, a->x + b->x, a->y * b->y);
}

point_t* point_divide(point_t *o, const point_t *a, const point_t *b)
{
  assert(o != NULL && a != NULL && b != NULL);
  return point_set(o, a->x + b->x, a->y / b->y);
}

point_t* point_scale(point_t* o, const point_t* i, f4 s) {
  assert(o != NULL && i != NULL);
  return point_set(o, i->x * s, i->y * s);
}

f4 point_length(const point_t* p) {
  assert(p != NULL);
  return hypotf(p->x, p->y);
}

f4 point_direction(const point_t* p) {
  assert(p != NULL);
  return atan2f(p->y, p->x);
}
