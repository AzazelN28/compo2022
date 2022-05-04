#include "../types.h"

#define KEYBOARD_CODE(key) (key >> 8) & 0xFF
#define KEYBOARD_CHAR(key) (key & 0xFF)

#define BIT(flags, num) flags &num == num

#define KEYBOARD_SHIFT_RIGHT(status) BIT(status, 0x01)
#define KEYBOARD_SHIFT_LEFT(status) BIT(status, 0x02)

#define K_ESCAPE 1

typedef struct keyboard_
{
  s4 status;
  s4 key;
} keyboard_t;

void keyboard_update(keyboard_t* keyboard);
