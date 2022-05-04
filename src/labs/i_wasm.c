typedef unsigned char u8;
typedef char s8;

typedef unsigned short u16;
typedef short s16;

typedef unsigned int u32;
typedef int s32;

u8 palette[256 * 3];
u8 framebuffer[320 * 200];
u8 imagedata[320 * 200 * 4];

void Palette_GetColor(const u8* palette, u16 index, u8* r, u8* g, u8* b) {
  *r = palette[index * 3 + 0] << 2;
  *g = palette[index * 3 + 1] << 2;
  *b = palette[index * 3 + 2] << 2;
}

void Palette_SetColor(u8* palette, u16 index, u8 r, u8 g, u8 b) {
  palette[index * 3 + 0] = r >> 2;
  palette[index * 3 + 1] = g >> 2;
  palette[index * 3 + 2] = b >> 2;
}

void FrameBuffer_SetPixel(u8* framebuffer, u16 x, u16 y, u8 color) {
  framebuffer[y * 320 + x] = color;
}

u8 FrameBuffer_GetPixel(const u8* framebuffer, u16 x, u16 y) {
  return framebuffer[y * 320 + x];
}

void ImageData_Render(u8* imagedata, u8* framebuffer, u8* palette) {
  u8 r, g, b;
  for (int i = 0; i < 320 * 200; i++) {
    u8 color = framebuffer[i];
    Palette_GetColor(palette, color, &r, &g, &b);
    int offset = i * 4;
    imagedata[offset + 0] = r;
    imagedata[offset + 1] = g;
    imagedata[offset + 2] = b;
    imagedata[offset + 3] = 255;
  }
}
