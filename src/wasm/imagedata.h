#define IMAGEDATA_SIZE 320 * 200 * 4
#define IMAGEDATA_SET_PIXEL(buffer, offset, r, g, b, a) \
  buffer[offset + 0] = r; \
  buffer[offset + 1] = g; \
  buffer[offset + 2] = b; \
  buffer[offset + 3] = a;
