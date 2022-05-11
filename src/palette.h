#include <stdbool.h>
#include "types.h"

#define PALETTE_COLORS 256
#define PALETTE_SIZE 768

extern u1 palette[PALETTE_SIZE];
extern bool palette_is_dirty;

void palette_get_color(const u1 *palette, u2 index, u1 *r, u1 *g, u1 *b);
void palette_set_color(u1 *palette, u2 index, u1 r, u1 g, u1 b);
void palette_roll(u1* palette, u1 index, u1 count, u1 direction);
bool palette_needs_update();
