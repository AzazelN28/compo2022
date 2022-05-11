#include <SDL2/SDL.h>
#include "../types.h"

#define SURFACE_SET_PIXEL(buffer, offset, r, g, b, a) \
  buffer[offset + 0] = r;                             \
  buffer[offset + 1] = g;                             \
  buffer[offset + 2] = b;                             \
  buffer[offset + 3] = a;

void surface_render(SDL_Surface *surface, u1 *framebuffer, u1 *palette);
