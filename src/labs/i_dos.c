#include <sys/movedata.h>
#include <dpmi.h>
// #include <conio.h>
#include <pc.h>

#include "i_types.h"

#define INPUT_STATUS 0x3DA
#define VRETRACE_BIT 0x08

u8 framebuffer[320 * 200];
u8 palette[768];

/**
 * Actualizamos los datos de la paleta
 * volc ndolos directamente de la memoria
 * que hemos reservado.
 */
void Palette_Update() {
  u8 index;
  u16 offset;
  for (index = 0; index < 256; index++) {
    offset = index * 3;
    u8 r = palette[offset + 0];
    u8 g = palette[offset + 1];
    u8 b = palette[offset + 2];
    outportb(0x3C8, index);
    outportb(0x3C9, r);
    outportb(0x3C9, g);
    outportb(0x3C9, b);
  }
}

void Display_Init() {
  // Iniciamos el modo 13.
  __dpmi_regs regs;
  regs.x.ax = 0x13;
  __dpmi_int(0x10, &regs);
}

void Display_WaitRetrace() {
  while (inp(INPUT_STATUS) & VRETRACE_BIT);
  while (!(inp(INPUT_STATUS) & VRETRACE_BIT));
}

void Display_Update() {
  // M‚todo m s lento.
  dosmemput(framebuffer, 320 * 200, 0xA0000);
  // M‚todo m s r pido.
  // __djgpp_nearptr_enable();
  // char *video = __djgpp_conventional_base + 0xA0000;
  // memcpy(video, framebuffer);
  // __djgpp_nearptr_disable();
}

void Display_Terminate() {
  // Restauramos el modo texto.
  __dpmi_regs regs;
  regs.x.ax = 0x10;
  __dpmi_int(0x10, &regs);
}

int main(int argc, char** argv) {
  int color, offset;
  for (color = 0; color < 16; color++)
  {
    palette[offset + 0] = color << 2;
    palette[offset + 1] = color << 2;
    palette[offset + 2] = color << 2;
  }

  int x, y;
  color = 0;
  for (x = 0; x < 320; x++) {
    if (x > 0 && x % 20 == 0) {
      color++;
    }
    for (y = 0; y < 200; y++) {
      framebuffer[y * 320 + x] = color;
    }
  }

  Palette_Update();
  Display_Init();
  int frame = 0;
  while (frame < 20000) {
    Display_Update();
    Display_WaitRetrace();
    frame++;
  }
  Display_Terminate();
  return 0;
}
