#include <stdio.h>
#include "mouse.h"
#include "keyboard.h"

/**
 * @brief Este es el main de DOS.
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char** argv) {
  mouse_t mouse;
  keyboard_t keyboard;
  mouse_reset(&mouse);
  mouse_show(&mouse);
  printf("Hello, DOS!\n");
  do
  {
    keyboard_update(&keyboard);
    printf("%d %d\n", keyboard.key, keyboard.status);
  }
  while (!KEYBOARD_CODE(keyboard.key));
  mouse_hide(&mouse);
  return 0;
}
