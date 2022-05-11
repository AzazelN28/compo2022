#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "mouse.h"
#include "keyboard.h"
#include "video.h"

#include "../types.h"
#include "../framebuf.h"
#include "../palette.h"
#include "../game.h"
#include "../div.h"
#include "../buffer.h"

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

  pal_t pal;
  map_t map;
  fpg_t fpg;
  fnt_t fnt;

  pal_load_from_file("dist/test.pal", &pal);
  pal_palette_apply(palette, &pal);

  map_load_from_file("dist/test.map", &map);
  map_palette_apply(palette, &map);
  map_draw(framebuffer, &map, 0, 0);

  fpg_load_from_file("dist/test.fpg", &fpg);

  fnt_load_from_file("dist/nuevofnt.fnt", &fnt);
  fnt_write(framebuffer, &fnt, "Hola, Mundo!", 100, 100);

  fpg_printf(&fpg);
  fpg_draw(framebuffer, &fpg, 100, 0, 0);

  printf("Hello, DOS!\n");

  mouse_reset(&mouse);
  mouse_show(&mouse);

  video_init();

  bool is_running = true;
  while (is_running)
  {
    // FIXME: esto no funciona bien, se queda esperando
    // que presiones la tecla.
    keyboard_update(&keyboard);
    mouse_get_position(&mouse);

    // Actualizamos el código del juego.
    game_loop();

    // Actualizamos la pantalla.
    if (palette_needs_update())
    {
      video_palette_update(palette);
    }
    video_framebuffer_update(framebuffer);
    video_wait_retrace();

    // Si se presiona la tecla Escape, salimos del juego.
    if (keyboard.key_code == K_ESCAPE)
    {
      is_running = false;
      break;
    }
  }

  video_terminate();

  mouse_hide(&mouse);

  return 0;
}
