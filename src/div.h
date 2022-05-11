#include "types.h"

#define SIGNATURE_SIZE    8
#define DESCRIPTION_SIZE  32
#define FILENAME_SIZE     12

#define PAL_SIGNATURE "pal\x1A\x0D\x0A\x00\x00"
#define PAL_RANGE_COLORS  32
#define PAL_RANGES        16
#define PAL_COLORS        256

#define MAP_SIGNATURE "map\x1A\x0D\x0A\x00\x00"

#define FPG_SIGNATURE "fpg\x1A\x0D\x0A\x00\x00"

#define FNT_SIGNATURE "fnt\x1A\x0D\x0A\x00\x00"
#define FNT_NUM_GLYPHS 256

#define FNT_NUMBERS     0x10
#define FNT_UPPERCASE   0x08
#define FNT_LOWERCASE   0x04
#define FNT_SYMBOLS     0x02
#define FNT_EXTENDED    0x01

/**
 * Este archivo contiene las definiciones necesarias
 * para trabajar con los tipos de archivo de DIV.
 */
typedef struct
{
  u1 r;
  u1 g;
  u1 b;
} color_t;

typedef struct
{
  s2 x;
  s2 y;
} cpoint_t;

typedef struct
{
  u1 num_colors;
  u1 type;
  u1 range_type;
  u1 black;
  u1 colors[PAL_RANGE_COLORS];
} pal_range_t;

typedef struct
{
  color_t colors[PAL_COLORS];
  pal_range_t ranges[PAL_RANGES];
} palette_t;

typedef struct
{
  u1 signature[SIGNATURE_SIZE];
} pal_header_t;

typedef struct
{
  pal_header_t header;
  palette_t palette;
} pal_t;

typedef struct
{
  u1 signature[SIGNATURE_SIZE];
  u2 width;
  u2 height;
  u4 code;
  u1 description[DESCRIPTION_SIZE];
} map_header_t;

typedef struct div
{
  u2 num;
  cpoint_t *list;
} cpoints_t;

typedef struct
{
  map_header_t header;
  palette_t palette;
  cpoints_t cpoints;
  u4 size;
  u1 *buffer;
} map_t;

typedef struct
{
  u1 signature[SIGNATURE_SIZE];
} fpg_header_t;

typedef struct
{
  u4 code;
  u4 length;
  u1 description[DESCRIPTION_SIZE];
  u1 filename[FILENAME_SIZE];
  u4 width;
  u4 height;
} fpg_map_header_t;

typedef struct fpg_map_
{
  fpg_map_header_t header;
  cpoints_t cpoints;
  u1 *buffer;
  struct fpg_map_ *next;
} fpg_map_t;

typedef struct
{
  fpg_header_t header;
  palette_t palette;
  fpg_map_t *maps;
} fpg_t;

typedef struct
{
  u1 signature[SIGNATURE_SIZE];
} fnt_header_t;

typedef struct
{
  u4 width;
  u4 height;
  s4 y;
  u4 offset;
} fnt_glyph_header_t;

typedef struct
{
  fnt_glyph_header_t header;
  u4 size;
  u1 *buffer;
} fnt_glyph_t;

typedef struct
{
  fnt_header_t header;
  palette_t palette;
  u4 charset;
  fnt_glyph_t glyphs[FNT_NUM_GLYPHS];
} fnt_t;

void pal_load_from_file(const char *filename, pal_t *pal);
void pal_palette_apply(u1* palette, pal_t* pal);

void map_load_from_file(const char *filename, map_t *map);
void map_unload(map_t *map);
void map_draw(u1* framebuffer, map_t* map, u2 x, u2 y);
void map_palette_apply(u1* palette, map_t* map);

void fpg_load_from_file(const char *filename, fpg_t *fpg);
void fpg_unload(fpg_t *fpg);
void fnt_load_from_file(const char *filename, fnt_t *fnt);
void fnt_unload(fnt_t *fnt);
