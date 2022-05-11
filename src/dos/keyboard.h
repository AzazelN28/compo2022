#include "../types.h"

#define BIT(flags, num) flags &num == num

#define KEYBOARD_SHIFT_RIGHT(status) BIT(status, 0x0001)
#define KEYBOARD_SHIFT_LEFT(status) BIT(status, 0x0002)
#define KEYBOARD_CTRL(status) BIT(status, 0x0004)
#define KEYBOARD_ALT(status) BIT(status, 0x0008)
#define KEYBOARD_SCROLL_LOCK(status) BIT(status, 0x0010)
#define KEYBOARD_NUM_LOCK(status) BIT(status, 0x0020)
#define KEYBOARD_CAPS_LOCK(status) BIT(status, 0x0040)
#define KEYBOARD_INSERT_LOCK(status) BIT(status, 0x0080)

#define KEYBOARD_CTRL_LEFT(status) BIT(status, 0x0100)
#define KEYBOARD_ALT_LEFT(status) BIT(status, 0x0200)
#define KEYBOARD_CTRL_RIGHT(status) BIT(status, 0x0400)
#define KEYBOARD_ALT_RIGHT(status) BIT(status, 0x0800)
#define KEYBOARD_SCROLL_LOCK_PRESSED(status) BIT(status, 0x1000)
#define KEYBOARD_NUM_LOCK_PRESSED(status) BIT(status, 0x2000)
#define KEYBOARD_CAPS_LOCK_PRESSED(status) BIT(status, 0x4000)
#define KEYBOARD_SYSREQ_PRESSED(status) BIT(status, 0x8000)

#define K_ESCAPE 1

typedef struct keyboard_
{
  s4 status;

  s4 key;

  u1 key_code;
  u1 key_char;
} keyboard_t;

void keyboard_update(keyboard_t* keyboard);
