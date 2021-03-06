#include "imagedata.h"
#include "../framebuf.h"
#include "../palette.h"
#include "../types.h"

u1 imagedata[IMAGEDATA_SIZE];

void imagedata_render(u1 *imagedata, u1 *framebuffer, u1 *palette)
{
  u1 r, g, b;
  for (u4 index = 0; index < FRAMEBUFFER_SIZE; index++)
  {
    u1 color = framebuffer[index];
    u4 offset = index << 2;
    palette_get_color(palette, color, &r, &g, &b);
    IMAGEDATA_SET_PIXEL(imagedata, offset, r, g, b, 0xFF)
  }
}
