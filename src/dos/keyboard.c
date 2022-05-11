#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <bios.h>
#include "keyboard.h"

void keyboard_update(keyboard_t *keyboard)
{
  assert(keyboard != NULL);
  keyboard->key = bioskey(0x11);
  keyboard->key_code = (keyboard->key >> 8) & 0xFF;
  keyboard->key_char = keyboard->key & 0xFF;
  keyboard->status = bioskey(0x12);
}
