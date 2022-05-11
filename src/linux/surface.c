#include <SDL2/SDL.h>
#include "surface.h"

#include "../framebuf.h"
#include "../palette.h"
#include "../types.h"

void surface_render(SDL_Surface *surface, u1 *framebuffer, u1 *palette)
{
  u1 *pixels = (u1 *)surface->pixels;
  u1 r, g, b;
  for (u4 index = 0; index < FRAMEBUFFER_SIZE; index++)
  {
    u1 color = framebuffer[index];
    u4 offset = index << 2;
    palette_get_color(palette, color, &b, &g, &r);
    SURFACE_SET_PIXEL(pixels, offset, r << 2, g << 2, b << 2, 0xFF)
  }
}
