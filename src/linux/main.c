#include <SDL2/SDL.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "surface.h"

#include "../types.h"
#include "../framebuf.h"
#include "../palette.h"
#include "../game.h"
#include "../div.h"
#include "../buffer.h"

/**
 * @brief Este es el main de Linux.
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char **argv)
{
  s4 initialized = SDL_Init(SDL_INIT_EVERYTHING);
  if (initialized != 0)
  {
    goto quit;
  }

  float framebuffer_scale = 4;

  SDL_Window *window = SDL_CreateWindow(
      "Compo 2022",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      FRAMEBUFFER_WIDTH * framebuffer_scale,
      FRAMEBUFFER_HEIGHT * framebuffer_scale,
      0 // sin flags (Habrá que ver si implemento FULLSCREEN o no)
  );
  if (window == NULL)
  {
    initialized = 0;
    goto quit;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL)
  {
    initialized = 0;
    goto quit;
  }

  SDL_Surface *surface = SDL_CreateRGBSurface(
    0,
    FRAMEBUFFER_WIDTH,
    FRAMEBUFFER_HEIGHT,
    32,
    0xff000000,
    0x00ff0000,
    0x0000ff00,
    0x000000ff
  );
  if (surface == NULL)
  {
    initialized = 0;
    goto quit;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (texture == NULL)
  {
    initialized = 0;
    goto quit;
  }

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

  SDL_Event event;

  bool is_running = true;
  while (is_running)
  {
    // Obtenemos los eventos y los procesamos.
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
      case SDL_MOUSEMOTION:
      case SDL_MOUSEWHEEL:
        break;

      case SDL_KEYDOWN:
      case SDL_KEYUP:
        break;

      case SDL_QUIT:
        is_running = false;
        break;
      }
    }

    // Aquí deberíamos actualizar el comportamiento
    // del juego.
    game_loop();

    // Aquí deberíamos actualizar el imagedata a partir
    // del framebuffer de 8 bits.
    SDL_LockSurface(surface);
    surface_render(surface, framebuffer, palette);
    SDL_UnlockSurface(surface);

    SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch);

    // Presentamos la mandanga.
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
  }

// Sí, ya sé que no se debe usar goto pero mira,
// mira lo que me importa:
// ¯\_(ツ)_/¯
quit:
  fnt_unload(&fnt);
  fpg_unload(&fpg);
  map_unload(&map);

  if (texture != NULL)
  {
    SDL_DestroyTexture(texture);
  }

  if (surface != NULL)
  {
    SDL_FreeSurface(surface);
  }

  if (renderer != NULL)
  {
    SDL_DestroyRenderer(renderer);
  }

  if (window != NULL)
  {
    SDL_DestroyWindow(window);
  }

  if (initialized == 0)
  {
    SDL_Quit();
  }
  else
  {
    SDL_Log("Error: %s\n", SDL_GetError());
    return 1;
  }
  return 0;
}
