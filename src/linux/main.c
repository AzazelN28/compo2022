#include <SDL2/SDL.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "../types.h"
#include "../framebuf.h"

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
  if (initialized != 0) {
    goto quit;
  }

  float framebuffer_multiplier = 4;

  SDL_Window *window = SDL_CreateWindow(
      "Compo 2022",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      FRAMEBUFFER_WIDTH * framebuffer_multiplier,
      FRAMEBUFFER_HEIGHT * framebuffer_multiplier,
      0 // sin flags (Habrá que ver si implemento FULLSCREEN o no)
  );
  if (window == NULL)
  {
    initialized = 0;
    goto quit;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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

  SDL_Event event;

  bool is_running = true;
  while (is_running)
  {
    // Obtenemos los eventos y los procesamos.
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
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

    SDL_RenderClear(renderer);
    // Aquí deberíamos actualizar el imagedata a partir
    // del framebuffer de 8 bits.
    SDL_RenderPresent(renderer);
  }

// Sí, ya sé que no se debe usar goto pero mira,
// mira lo que me importa:
// ¯\_(ツ)_/¯
quit:
  if (texture != NULL) {
    SDL_DestroyTexture(texture);
  }

  if (surface != NULL) {
    SDL_FreeSurface(surface);
  }

  if (renderer != NULL) {
    SDL_DestroyRenderer(renderer);
  }

  if (window != NULL) {
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
