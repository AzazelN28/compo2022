#include <stddef.h>
#include <stdbool.h>
#include <dos.h>
#include <assert.h>
#include "mouse.h"

void mouse_reset(mouse_t* mouse) {
  union REGS reg;
  assert(mouse != NULL);

  MOUSE_COMMAND(reg, MOUSE_RESET)

  // Obtenemos si existe y la cantidad
  // de botones que tiene.
  mouse->exists = reg.x.ax;
  mouse->num_buttons = reg.x.bx;
}

void mouse_show(mouse_t* mouse) {
  union REGS reg;
  assert(mouse != NULL);

  MOUSE_COMMAND(reg, MOUSE_SHOW)

  mouse->shown = true;
}

void mouse_hide(mouse_t* mouse) {
  union REGS reg;
  assert(mouse != NULL);

  MOUSE_COMMAND(reg, MOUSE_HIDE)

  mouse->shown = false;
}

void mouse_get_position(mouse_t* mouse) {
  union REGS reg;
  assert(mouse != NULL);

  MOUSE_COMMAND(reg, MOUSE_GET_POS)

  mouse->buttons = reg.x.bx;
  mouse->x = reg.x.cx;
  mouse->y = reg.x.dx;
}

void mouse_set_position(mouse_t* mouse) {
  union REGS reg;
  assert(mouse != NULL);

  reg.x.cx = mouse->x;
  reg.x.dx = mouse->y;
  MOUSE_COMMAND(reg, MOUSE_SET_POS)
}

void mouse_get_press(mouse_t* mouse, u1 button) {
  union REGS reg;
  assert(mouse != NULL);

  reg.x.bx = button;

  MOUSE_COMMAND(reg, MOUSE_GET_PRESS)

  mouse->buttons = reg.x.ax;
  mouse->counter = reg.x.bx;
  mouse->x = reg.x.cx;
  mouse->y = reg.x.dx;
}

void mouse_get_release(mouse_t* mouse, u1 button) {
  union REGS reg;
  assert(mouse != NULL);

  reg.x.bx = button;
  MOUSE_COMMAND(reg, MOUSE_GET_RELEASE)
  mouse->buttons = reg.x.ax;
  mouse->counter = reg.x.bx;
  mouse->x = reg.x.cx;
  mouse->y = reg.x.dx;
}

void mouse_set_range_x(mouse_t* mouse) {
  union REGS reg;
  assert(mouse != NULL);

  reg.x.cx = mouse->range_x.min;
  reg.x.dx = mouse->range_x.max;
  MOUSE_COMMAND(reg, MOUSE_SET_RANGE_X)
}

void mouse_set_range_y(mouse_t* mouse) {
  union REGS reg;
  assert(mouse != NULL);

  reg.x.cx = mouse->range_y.min;
  reg.x.dx = mouse->range_y.max;
  MOUSE_COMMAND(reg, MOUSE_SET_RANGE_Y)
}

