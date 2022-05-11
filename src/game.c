#include <stddef.h>

#include "types.h"
#include "game.h"
#include "actor.h"

void game_input()
{
  // TODO: Aquí deberíamos actualizar la entrada del
  // juego.
}

void game_update()
{
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

void game_loop()
{
  game_input();
  game_update();
  game_output();
}
