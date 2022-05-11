#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
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

  mouse_reset(&mouse);
  mouse_show(&mouse);

  mouse.position.x = VIDEO_WIDTH >> 1;
  mouse.position.y = VIDEO_HEIGHT >> 1;
  mouse_set_position(&mouse);

  video_init();

  f4 ms = 0;

  bool is_running = true;
  while (is_running)
  {
    // FIXME: esto no funciona bien, se queda esperando
    // que presiones la tecla.
    keyboard_update(&keyboard);
    mouse_get_position(&mouse);

    map_draw(framebuffer, &map, 0, 0);

    // Actualizamos el código del juego.
    ms = 1000.0 * (float)clock() / (float)CLOCKS_PER_SEC;
    game_loop(ms);

    // Pintamos en pantalla el número de updates que
    // han ocurrido.
    u1 updates_buffer[32];
    snprintf(updates_buffer, 32, "%d %02f\n", game_time.updates, game_time.time);
    fnt_write(framebuffer, &fnt, updates_buffer, 0, 0);

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
