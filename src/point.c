#include <stddef.h>
#include <math.h>
#include <assert.h>
#include "types.h"
#include "point.h"
#include "interpol.h"

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

point_t* point_perp_left(point_t* o, const point_t* i) {
  assert(o != NULL && i != NULL);
  return point_set(o, i->y, -i->x);
}

point_t* point_perp_right(point_t* o, const point_t* i) {
  assert(o != NULL && i != NULL);
  return point_set(o, -i->y, i->x);
}

point_t* point_linear(point_t* o, float x, point_t* a, point_t* b)
{
  assert(o != NULL && a != NULL && b != NULL);
  return point_set(
    o,
    linearf(x, a->x, b->x),
    linearf(x, a->y, b->y)
  );
}

point_t *point_quadratic(point_t *o, float x, point_t *a, point_t *b, point_t *c)
{
  assert(o != NULL && a != NULL && b != NULL && c != NULL);
  return point_set(
    o,
    quadraticf(x, a->x, b->x, c->x),
    quadraticf(x, a->y, b->y, c->y)
  );
}

point_t *point_cubic(point_t *o, float x, point_t *a, point_t *b, point_t *c, point_t *d)
{
  assert(o != NULL && a != NULL && b != NULL && c != NULL && d != NULL);
  return point_set(
      o,
      cubicf(x, a->x, b->x, c->x, d->x),
      cubicf(x, a->y, b->y, c->y, d->y));
}

f4 point_length(const point_t* p) {
  assert(p != NULL);
  return hypotf(p->x, p->y);
}

f4 point_direction(const point_t* p) {
  assert(p != NULL);
  return atan2f(p->y, p->x);
}
