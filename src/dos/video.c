#include <dpmi.h>
// #include <conio.h>
#include <pc.h>

#include "video.h"

#ifdef VIDEO_USE_DOSMEMPUT
#include <sys/movedata.h> // Para poder usar dosmemput
#endif

#ifdef VIDEO_USE_FARPOKEB
#include <sys/farptr.h> // Para trabajar con farpoke
#include <go32.h> // Para la declaración de _dos_ds
#endif

#ifdef VIDEO_USE_DISABLE_PROTECTION
#include <sys/nearptr.h> // Para desactivar la memoria protegida
#include <string.h> // Necesitamos tener disponible memcpy
#endif

#include "../palette.h"
#include "../framebuf.h"
#include "../types.h"

void video_init()
{
  // Iniciamos el modo 13.
  __dpmi_regs regs;
  regs.x.ax = VIDEO_MODE_GRAPHICS;
  __dpmi_int(VIDEO_INT, &regs);
}

void video_palette_update(const u1* palette)
{
  outportb(0x3C8, 0);
  for (u2 i = 0; i < VIDEO_PALETTE_SIZE; i++)
  {
    outportb(0x3C9, palette[i]);
  }
}

void video_framebuffer_update(const u1* framebuffer) {
  #ifdef VIDEO_USE_DOSMEMPUT
    dosmemput(framebuffer, VIDEO_SIZE, VIDEO_BASE_ADDRESS);
  #endif

  #ifdef VIDEO_USE_FARPOKEB
    _farsetsel(_dos_ds);
    for (u2 i = 0; i < VIDEO_SIZE; i++)
    {
      _farnspokeb(VIDEO_BASE_ADDRESS + i, framebuffer[i]);
    }
  #endif

  #ifdef VIDEO_USE_FARPOKEL
    _farsetsel(_dos_ds);
    for (u2 i = 0; i < VIDEO_SIZE; i += 4)
    {
      _farnspokel(VIDEO_BASE_ADDRESS + i, framebuffer[i]);
    }
#endif

  #ifdef VIDEO_USE_DISABLE_PROTECTION
    if (__djgpp_nearptr_enable()) {
      u1 *screen = (u1 *)(__djgpp_conventional_base + VIDEO_BASE_ADDRESS);
      memcpy(screen, framebuffer, VIDEO_SIZE);
      __djgpp_nearptr_disable();
    }
  #endif
}

void video_wait_retrace()
{
  while (inportb(VIDEO_INPUT_STATUS) & VIDEO_VERTICAL_RETRACE_BIT);
  while (!(inportb(VIDEO_INPUT_STATUS) & VIDEO_VERTICAL_RETRACE_BIT));
}

void video_terminate()
{
  // Restauramos el modo texto.
  __dpmi_regs regs;
  regs.x.ax = VIDEO_MODE_TEXT;
  __dpmi_int(VIDEO_INT, &regs);
}
