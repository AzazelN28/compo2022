#ifndef __SPRITES_H__
#define __SPRITES_H__

typedef struct _vec2s {
  s32 x, y;
} vec2s_t;

typedef struct _vec2f {
  f32 x, y;
} vec2f_t;

typedef struct _sprite {
  vec2s_t position;
} sprite_t;

#endif
