#include <stddef.h>

#include "types.h"
#include "game.h"
#include "actor.h"
#include "framebuf.h"

game_time_t game_time;

void game_input()
{
  // TODO: Aquí deberíamos actualizar la entrada del
  // juego.
}

void game_update()
{
  game_time.updates++;

  actor_t* actors = NULL;
  if (actors != NULL)
  {
    // TODO: Aquí deberíamos actualizar el comportamiento
    // de las entidades.
    for (actor_t *actor = actors; actor != NULL; actor = actor->next)
    {
      // TODO: Aquí deberíamos actualizar el comportamiento de los
      // actores.
    }
  }
}

void game_audio()
{
  // TODO: Actualizar el audio del juego.
}

void game_render()
{
  actor_t *actors = NULL;

  if (actors != NULL)
  {
    for (actor_t *actor = actors; actor != NULL; actor = actor->next)
    {
      // TODO: Aquí deberíamos actualizar el comportamiento de los
      // actores.
    }
  }
}

void game_output()
{
  // game_audio();
  game_render();
}

void game_loop(f4 ms)
{
  game_time.current = ms;
  game_time.elapsed = game_time.current - game_time.previous;
  game_time.previous = game_time.current;
  game_time.remaining += game_time.elapsed;
  game_input();
  while (game_time.remaining >= GAME_TIME_MS_PER_UPDATE)
  {
    game_update();
    game_time.time += GAME_TIME_MS_PER_UPDATE;
    game_time.remaining -= GAME_TIME_MS_PER_UPDATE;
  }
  game_output();

}
