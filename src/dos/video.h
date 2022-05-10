#include "../types.h"

// #define VIDEO_USE_DOSMEMPUT
// #define VIDEO_USE_FARPOKE
#define VIDEO_USE_DISABLE_PROTECTION

#define VIDEO_WIDTH             320
#define VIDEO_HEIGHT            200

#define VIDEO_INT             0x10

#define VIDEO_BASE_ADDRESS    0xA0000

#define VIDEO_MODE_GRAPHICS   0x13
#define VIDEO_MODE_TEXT       0x03

#define VIDEO_PALETTE_SIZE    768

#define VIDEO_PALETTE_RESET   0x03C6
#define VIDEO_PALETTE_READ    0x03C7
#define VIDEO_PALETTE_WRITE   0x03C8
#define VIDEO_PALETTE_DATA    0x03C9

#define VIDEO_INPUT_STATUS         0x3DA
#define VIDEO_VERTICAL_RETRACE_BIT 0x08

void video_init();
void video_palette_update(const u1* palette);
void video_framebuffer_update(const u1* framebuffer);
void video_wait_retrace();
void video_terminate();
