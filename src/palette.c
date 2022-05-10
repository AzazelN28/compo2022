#include <assert.h>
#include <stddef.h>
#include <stdbool.h>
#include "types.h"
#include "palette.h"

void palette_get_color(const u1 *palette, u2 index, u1 *r, u1 *g, u1 *b)
{
  assert(palette != NULL && index < PALETTE_COLORS && r != NULL && g != NULL && b != NULL);
  *r = palette[index * 3 + 0] << 2;
  *g = palette[index * 3 + 1] << 2;
  *b = palette[index * 3 + 2] << 2;
}

void palette_set_color(u1 *palette, u2 index, u1 r, u1 g, u1 b)
{
  assert(palette != NULL && index < PALETTE_COLORS);
  palette[index * 3 + 0] = r >> 2;
  palette[index * 3 + 1] = g >> 2;
  palette[index * 3 + 2] = b >> 2;
}

void palette_roll(u1 *palette, u1 index, u1 count, u1 increment)
{
  assert(palette != NULL && index < PALETTE_COLORS && count <= PALETTE_COLORS && increment != 0);
}
