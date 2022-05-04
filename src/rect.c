#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include "point.h"
#include "types.h"

typedef struct rect_
{
  s2 x, y, width, height;
} rect_t;

rect_t* rect_set(rect_t* o, s2 x, s2 y, s2 width, s2 height)
{
  assert(o != NULL);
  o->x = x;
  o->y = y;
  o->width = width;
  o->height = height;
  return o;
}

bool rect_contains_point(const rect_t* r, const point_t* p)
{
  assert(r != NULL);
  assert(p != NULL);
  return p->x > r->x
      && p->x < r->x + r->width
      && p->y > r->y
      && p->y < r->y + r->height;
}

bool rect_contains_rect(const rect_t* a, const rect_t* b)
{
  assert(a != NULL);
  assert(b != NULL);
  if (a->x + a->width < b->x || a->x > b->x + b->width) {
    return false;
  }
  if (a->y + a->height < b->y || a->y > b->y + b->height) {
    return false;
  }
  return true;
}

bool rect_intersects_rect(const rect_t* a, const rect_t* b)
{

}
