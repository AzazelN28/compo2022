#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "mouse.h"
#include "keyboard.h"
#include "video.h"

#include "../palette.h"
#include "../framebuf.h"

/**
 * @brief Este es el main de DOS.
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char** argv) {
  mouse_t mouse;
  keyboard_t keyboard;

  bool palette_dirty = false;
  u1 palette[PALETTE_SIZE];

  u1 framebuffer[FRAMEBUFFER_SIZE];

  memset(palette, PALETTE_SIZE, 0);
  memset(framebuffer, FRAMEBUFFER_SIZE, 0);

  printf("Hello, DOS!\n");

  mouse_reset(&mouse);
  mouse_show(&mouse);

  // video_init();

  bool is_running = true;
  while (is_running)
  {
    keyboard_update(&keyboard);

    // ¿La paleta necesita actualizarse?
    if (palette_dirty) {
      video_palette_update(palette);
    }

    // video_framebuffer_update(framebuffer);

    printf("%d %c %d\r", keyboard.key_code, keyboard.key_char, keyboard.status);

    // Si se presiona la tecla Escape, salimos del juego.
    if (keyboard.key_code == K_ESCAPE) {
      printf("Goodbye!\n");
      is_running = false;
      break;
    }
  }

  // video_terminate();

  mouse_hide(&mouse);

  return 0;
}
