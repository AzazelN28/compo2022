#include <stdbool.h>
#include "../types.h"
#include "../range.h"

#define MOUSE_EXISTS_NO 0x0000
#define MOUSE_EXISTS_YES 0xFFFF

#define MOUSE_RESET 0x00
#define MOUSE_SHOW 0x01
#define MOUSE_HIDE 0x02
#define MOUSE_GET_POS 0x03
#define MOUSE_SET_POS 0x04
#define MOUSE_GET_PRESS 0x05
#define MOUSE_GET_RELEASE 0x06
#define MOUSE_SET_RANGE_X 0x07
#define MOUSE_SET_RANGE_Y 0x08

#define MOUSE_LEFT 0x01
#define MOUSE_RIGHT 0x02
#define MOUSE_MIDDLE 0x04

#define MOUSE_INT 0x33
#define MOUSE_COMMAND(reg, command) \
  reg.x.ax = command;               \
  __dpmi_int(MOUSE_INT, &reg);

typedef struct mouse_
{
  bool shown;
  u2 exists;
  u2 num_buttons;
  u2 buttons;
  u2 counter;
  u2 x;
  u2 y;
  range_t range_x;
  range_t range_y;
} mouse_t;

void mouse_reset(mouse_t *mouse);
void mouse_show(mouse_t *mouse);
void mouse_hide(mouse_t *mouse);
void mouse_get_position(mouse_t *mouse);
void mouse_set_position(mouse_t *mouse);
void mouse_get_press(mouse_t *mouse, u1 button);
void mouse_get_release(mouse_t *mouse, u1 button);
void mouse_set_range_x(mouse_t *mouse);
void mouse_set_range_y(mouse_t *mouse);
