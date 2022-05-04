// #include <pc.h>
#include <bios.h>
#include <stdio.h>

typedef unsigned int u32;
typedef signed int s32;

typedef unsigned char u8;

#define KEYBOARD_CODE(key) (key >> 8) & 0xFF
#define KEYBOARD_CHAR(key) (key & 0xFF)

#define BIT(flags, num) flags & num == num

#define KEYBOARD_SHIFT_RIGHT(status) BIT(status, 0x01)
#define KEYBOARD_SHIFT_LEFT(status) BIT(status, 0x02)

typedef struct keyboard_ {
  s32 status;
  s32 key;
} keyboard_t;

int main(int argc, char** argv) {
  int key;
//  while (!(key = kbhit()));
//  printf("%d\n", key);
  while (!(key = bioskey(0x11)));
  printf("%d %d %c\n", key, KEYBOARD_CODE(key), KEYBOARD_CHAR(key));
  key = bioskey(0x12);
  printf("%d\n", key);
  return 0;
}
