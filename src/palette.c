#include <assert.h>
#include <stddef.h>
#include <stdbool.h>
#include "types.h"
#include "palette.h"

u1 palette[PALETTE_SIZE];
bool palette_is_dirty = true;

void palette_get_color(const u1 *palette, u2 index, u1 *r, u1 *g, u1 *b)
{
  assert(palette != NULL && index < PALETTE_COLORS && r != NULL && g != NULL && b != NULL);
  *r = palette[index * 3 + 0];
  *g = palette[index * 3 + 1];
  *b = palette[index * 3 + 2];
}

void palette_set_color(u1 *palette, u2 index, u1 r, u1 g, u1 b)
{
  assert(palette != NULL && index < PALETTE_COLORS);
  palette[index * 3 + 0] = r;
  palette[index * 3 + 1] = g;
  palette[index * 3 + 2] = b;
  palette_is_dirty = true;
}

bool palette_needs_update()
{
  if (palette_is_dirty)
  {
    palette_is_dirty = false;
    return true;
  }
  return false;
}

void palette_roll(u1 *palette, u1 index, u1 count, u1 increment)
{
  assert(palette != NULL && index < PALETTE_COLORS && count <= PALETTE_COLORS && increment != 0);
}
