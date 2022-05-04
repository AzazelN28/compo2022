#include <stddef.h>
#include <assert.h>
#include <bios.h>
#include "keyboard.h"

void keyboard_update(keyboard_t *keyboard)
{
  assert(keyboard != NULL);
  keyboard->key = bioskey(0x11);
  keyboard->status = bioskey(0x12);
}
