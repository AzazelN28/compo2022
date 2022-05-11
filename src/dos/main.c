#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "mouse.h"
#include "keyboard.h"
#include "video.h"

#include "../types.h"
#include "../palette.h"
#include "../framebuf.h"
#include "../game.h"

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
  
  bool is_palette_dirty = true;
  u1 palette[PALETTE_SIZE];
  u1 framebuffer[FRAMEBUFFER_SIZE];

  memset(palette, PALETTE_SIZE, 0);
  memset(framebuffer, FRAMEBUFFER_SIZE, 0);

  // Creamos una paleta en blanco y negro.
  for (u2 i = 0; i < 256; i++) {
    palette_set_color(palette, i, i, i, i);
  }

  printf("Hello, DOS!\n");

  mouse_reset(&mouse);
  mouse_show(&mouse);

  video_init();

  bool is_running = true;
  while (is_running)
  {
    keyboard_update(&keyboard);
    mouse_get_position(&mouse);

    framebuffer_set_pixel(
      framebuffer,
      mouse.position.x,
      mouse.position.y,
      255
    );

    // Actualizamos el código del juego.
    game_loop();

    // Actualizamos la pantalla.
    if (is_palette_dirty)
    {
      video_palette_update(palette);
    }
    video_framebuffer_update(framebuffer);

    // Si se presiona la tecla Escape, salimos del juego.
    if (keyboard.key_code == K_ESCAPE) {
      is_running = false;
      break;
    }
  }

  video_terminate();

  mouse_hide(&mouse);

  return 0;
}
