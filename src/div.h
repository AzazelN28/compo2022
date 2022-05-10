#include "types.h"

#define DIV_PAL_SIGNATURE { "pal", 0x1A, 0x0D, 0x0A, 0, 0 }
#define DIV_MAP_SIGNATURE { "map", 0x1A, 0x0D, 0x0A, 0, 0 }
#define DIV_FPG_SIGNATURE { "fpg", 0x1A, 0x0D, 0x0A, 0, 0 }

/**
 * Este archivo contiene las definiciones necesarias
 * para trabajar con los tipos de archivo de DIV.
 */
typedef struct {
  u1 r;
  u1 g;
  u1 b;
} div_color_t;

typedef struct {
  s2 x;
  s2 y;
} div_cpoint_t;

typedef struct
{
  u1 num_colors;
  u1 type;
  u1 range_type;
  u1 black;
  u1 colors[32];
} div_pal_range_t;

typedef struct
{
  div_color_t colors[256];
  div_pal_range_t ranges[16];
} div_palette_t;

typedef struct {
  u1 signature[8];
  div_palette_t palette;
} div_pal_t;

typedef struct {
  u1 signature[8];
  u2 width;
  u2 height;
  u4 code;
  u1 description[32];
} div_map_header_t;

typedef struct div
{
  u2 num;
  div_cpoint_t *list;
} div_cpoints_t;


typedef struct {
  div_map_header_t header;
  div_palette_t palette;
  div_cpoints_t cpoints;
  u1 *pixels;
} div_map_t;

typedef struct {
  u1 signature[8];
} div_fpg_header_t;

typedef struct {
  u4 code;
  u4 length;
  u1 description[32];
  u1 filename[12];
  u4 width;
  u4 height;
} div_fpg_map_header_t;

typedef struct div_fpg_map_ {
  div_fpg_map_header_t header;
  div_cpoints_t cpoints;
  u1 *pixels;
  struct div_fpg_map_ *next;
} div_fpg_map_t;

typedef struct {
  div_fpg_header_t header;
  div_palette_t palette;
  div_fpg_map_t *maps;
} div_fpg_t;
