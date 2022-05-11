#include "types.h"

#define PALETTE_COLORS 256
#define PALETTE_SIZE 768

u1 palette[PALETTE_SIZE];

void palette_get_color(const u1 *palette, u2 index, u1 *r, u1 *g, u1 *b);
void palette_set_color(u1 *palette, u2 index, u1 r, u1 g, u1 b);
void palette_roll(u1* palette, u1 index, u1 count, u1 direction);
