#include "types.h"

#define FRAMEBUFFER_WIDTH   320
#define FRAMEBUFFER_HEIGHT  200
#define FRAMEBUFFER_SIZE    64000

u1 framebuffer[FRAMEBUFFER_SIZE];

void framebuffer_set_pixel(u1 *framebuffer, u2 x, u2 y, u1 color);
u1 framebuffer_get_pixel(const u1 *framebuffer, u2 x, u2 y);
