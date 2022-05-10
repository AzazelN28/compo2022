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
    palette_get_color(palette, color, &r, &g, &b);
    u4 offset = index * 4;
    imagedata[offset + 0] = r;
    imagedata[offset + 1] = g;
    imagedata[offset + 2] = b;
    imagedata[offset + 3] = 0xFF;
  }
}
