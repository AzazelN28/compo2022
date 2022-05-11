#include "types.h"

#define GAME_TIME_MS_PER_UPDATE 1000 / 30

typedef struct
{
  f4 previous;
  f4 current;
  f4 elapsed;
  f4 remaining;
  f4 time;
  u4 updates;
} game_time_t;

extern game_time_t game_time;

// Estas serían las fases del juego. En cada una
// de estas fases procesaríamos la información necesaria
// para actualizar la entrada, el comportamiento de las
// entidades, las animaciones, el render, etc.
void game_input();
void game_update();
void game_output();

void game_loop(f4 ms);
