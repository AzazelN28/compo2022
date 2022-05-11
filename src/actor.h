#include "point.h"

enum actor_state_e
{
  ACTOR_STATE_DEAD = 0,
  ACTOR_STATE_ALIVE,
  ACTOR_STATE_SLEEP
};

typedef struct actor_
{
  // Posición del actor (esto son coordenadas
  // del scroll).
  point_t position;

  // Estado en el que se encuentra el actor.
  // Esto pueden ser varios estados:
  // - Muerto
  // - Vivo
  // - Durmiendo
  u1 state;

  // Siguiente.
  struct actor_ *next;
} actor_t;
