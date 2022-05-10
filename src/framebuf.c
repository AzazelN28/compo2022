#include <stddef.h>
#include <assert.h>
#include "types.h"
#include "framebuf.h"

/**
 * Setea un pixel en el framebuffer.
 */
void framebuffer_set_pixel(u1 *framebuffer, u2 x, u2 y, u1 color)
{
  assert(framebuffer != NULL && x < FRAMEBUFFER_WIDTH && y < FRAMEBUFFER_HEIGHT);
  framebuffer[y * FRAMEBUFFER_WIDTH + x] = color;
}

/**
 * Obtiene un pixel del framebuffer.
 */
u1 framebuffer_get_pixel(const u1 *framebuffer, u2 x, u2 y)
{
  assert(framebuffer != NULL && x < FRAMEBUFFER_WIDTH && y < FRAMEBUFFER_HEIGHT);
  return framebuffer[y * FRAMEBUFFER_WIDTH + x];
}
