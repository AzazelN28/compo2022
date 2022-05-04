#include <stdio.h>
#include <math.h>
#include <assert.h>

typedef unsigned char u8;
typedef signed char s8;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned int u32;
typedef signed int s32;

typedef struct rect_ {
  s16 x, y, width, height;
} rect_t;

typedef struct point_ {
  s16 x, y;
} point_t;

int point_distance(const point_t* a, const point_t* b) {
  return hypotf(a->x - b->x, a->y - b->y);
}

float point_angle(const point_t* a, const point_t* b) {
  return atan2f(a->y - b->y, a->x - b->x);
}

u8 rect_contains(const rect_t* rect, const point_t* point) {
  assert(rect != NULL);
  assert(point != NULL);
  return point->x > rect->x
      && point->x < rect->x + rect->width
      && point->y > rect->y
      && point->y < rect->y + rect->height;
}

int main(int argc, char** argv) {
  rect_t rect;
  point_t point;

  rect.x = 10;
  rect.y = 10;
  rect.width = 20;
  rect.height = 20;

  point.x = 20;
  point.y = 20;
  
  rect_contains(NULL, NULL);
  rect_contains(&rect, &point);
}
