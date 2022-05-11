#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "range.h"
#include "div.h"
#include "types.h"
#include "palette.h"
#include "framebuf.h"
#include "buffer.h"

void palette_printf(palette_t *palette)
{
  printf("palette\n");
  for (u2 i = 0; i < PAL_COLORS; i++)
  {
    printf("\tcolor %02x %02x %02x",
           palette->colors[i].r,
           palette->colors[i].g,
           palette->colors[i].b);
  }
}

void palette_apply(u1 *palette, palette_t *source)
{
  for (u2 i = 0; i < PAL_COLORS; i++)
  {
    palette_set_color(
        palette,
        i,
        source->colors[i].r,
        source->colors[i].g,
        source->colors[i].b);
  }
}

void pal_load_from_file(const char *filename, pal_t *pal)
{
  assert(filename != NULL && pal != NULL);
  FILE *file = fopen(filename, "rb");
  assert(file != NULL);
  fread(pal, 1, sizeof(pal_t), file);
  fclose(file);
}

void pal_palette_apply(u1 *palette, pal_t *pal)
{
  palette_apply(palette, &pal->palette);
}

void map_load_from_file(const char *filename, map_t *map)
{
  assert(filename != NULL && map != NULL);
  FILE *file = fopen(filename, "rb");
  assert(file != NULL);
  fread(&map->header, 1, sizeof(map_header_t), file);
  fread(&map->palette, 1, sizeof(palette_t), file);
  fread(&map->cpoints.num, 1, sizeof(u2), file);
  if (map->cpoints.num > 0)
  {
    map->cpoints.list = calloc(1, sizeof(cpoint_t) * map->cpoints.num);
    fread(map->cpoints.list, map->cpoints.num, sizeof(cpoint_t), file);
  }
  else
  {
    map->cpoints.list = NULL;
  }
  u4 size = map->header.width * map->header.height;
  map->buffer = calloc(1, size);
  fread(map->buffer, 1, size, file);
  fclose(file);
}

void map_unload(map_t *map)
{
  if (map->cpoints.list != NULL)
  {
    free(map->cpoints.list);
  }
  free(map->buffer);
}

void map_palette_apply(u1 *palette, map_t *map)
{
  palette_apply(palette, &map->palette);
}

u1 map_get_pixel(map_t *map, u2 x, u2 y)
{
  u4 offset = OFFSET(x, y, map->header.width);
  return map->buffer[offset];
}

void buffer_draw(u1 *framebuffer, u1 *imagebuffer, u2 width, u2 height, s2 dx, s2 dy)
{
  u2 ty, tx, y, x;
  for (y = 0; y < height; y++)
  {
    ty = dy + y;
    if (ty < 0)
    {
      continue;
    }
    else if (ty >= FRAMEBUFFER_HEIGHT)
    {
      break;
    }

    for (x = 0; x < width; x++)
    {
      tx = dx + x;
      u4 offset_from = OFFSET(x, y, width);
      if (tx < 0)
      {
        continue;
      }
      else if (tx >= FRAMEBUFFER_WIDTH)
      {
        break;
      }
      u4 offset_to = OFFSET(tx, ty, FRAMEBUFFER_WIDTH);
      u1 color = imagebuffer[offset_from];
      if (!color)
      {
        continue;
      }
      framebuffer[offset_to] = color;
      // framebuffer_set_pixel(framebuffer, ty, tx, map->buffer[offset_from]);
    }
  }
}

void map_draw(u1 *framebuffer, map_t *map, s2 dx, s2 dy)
{
  buffer_draw(framebuffer, map->buffer, map->header.width, map->header.height, dx, dy);
}

void fpg_load_from_file(const char *filename, fpg_t *fpg)
{
  assert(filename != NULL && fpg != NULL);
  FILE *file = fopen(filename, "rb");
  assert(file != NULL);
  fread(&fpg->header, 1, sizeof(fpg_header_t), file);
  fread(&fpg->palette, 1, sizeof(palette_t), file);
  fpg_map_t *current = NULL, *prev = NULL;
  while (!feof(file))
  {
    current = calloc(1, sizeof(fpg_map_t));
    current->next = NULL;
    fread(&current->header, 1, sizeof(fpg_map_header_t), file);
    if (current->header.code == 0)
    {
      break;
    }
    if (prev != NULL)
    {
      // Asignamos al mapa anterior, el actual.
      prev->next = current;
    }
    else
    {
      // Primer mapa.
      fpg->maps = current;
    }
    fread(&current->cpoints.num, 1, sizeof(u4), file);
    if (current->cpoints.num > 0)
    {
      current->cpoints.list = calloc(1, sizeof(cpoint_t) * current->cpoints.num);
      fread(current->cpoints.list, current->cpoints.num, sizeof(cpoint_t), file);
    }
    else
    {
      current->cpoints.list = NULL;
    }
    u4 size = current->header.width * current->header.height;
    // printf("Tamaño: %d\n", size);
    current->buffer = calloc(1, size);
    fread(current->buffer, 1, size, file);
    prev = current;
  }
  fclose(file);
}

void fpg_unload(fpg_t *fpg)
{
  for (fpg_map_t *current = fpg->maps; current != NULL; current = current->next)
  {
    if (current->cpoints.list != NULL)
    {
      free(current->cpoints.list);
    }
    free(current->buffer);
  }
}

void fpg_palette_apply(u1 *palette, fpg_t *fpg)
{
  palette_apply(palette, &fpg->palette);
}

fpg_map_t *fpg_find_map(fpg_t *fpg, u4 code)
{
  for (fpg_map_t *map = fpg->maps; map != NULL; map = map->next)
  {
    if (map->header.code == code)
    {
      return map;
    }
  }
  return NULL;
}

void fpg_printf(fpg_t *fpg)
{
  for (fpg_map_t *map = fpg->maps; map != NULL; map = map->next)
  {
    printf("%04d %s %s\n", map->header.code, map->header.description, map->header.filename);
  }
}

void fpg_draw(u1 *framebuffer, fpg_t *fpg, u4 code, s2 dx, s2 dy)
{
  fpg_map_t *map = fpg_find_map(fpg, code);
  buffer_draw(framebuffer, map->buffer, map->header.width, map->header.height, dx, dy);
}

void fnt_load_from_file(const char *filename, fnt_t *fnt)
{
  assert(filename != NULL && fnt != NULL);
  FILE *file = fopen(filename, "rb");
  assert(file != NULL);
  fread(&fnt->header, 1, sizeof(fnt_header_t), file);
  fread(&fnt->palette, 1, sizeof(palette_t), file);
  fread(&fnt->charset, 1, sizeof(u4), file);
  fnt->space = 0;
  fnt->avg_width = 0;
  fnt->max_width = 0;
  fnt->max_height = 0;
  for (u2 i = 0; i < FNT_NUM_GLYPHS; i++)
  {
    fnt_glyph_t *glyph = &(fnt->glyphs[i]);
    fread(&glyph->header, 1, sizeof(fnt_glyph_header_t), file);

    fnt->max_width = MAX(fnt->max_width, glyph->header.width);
    fnt->max_height = MAX(fnt->max_height, glyph->header.height + glyph->header.y);
    fnt->avg_width += glyph->header.width;

    glyph->size = glyph->header.width * glyph->header.height;
    glyph->buffer = (u1 *)(calloc(1, glyph->size));
  }
  fnt->avg_width /= FNT_NUM_GLYPHS;
  fnt->space = fnt->avg_width >> 1;

  for (u2 i = 0; i < FNT_NUM_GLYPHS; i++)
  {
    fnt_glyph_t *glyph = &(fnt->glyphs[i]);
    fseek(file, glyph->header.offset, SEEK_SET);
    fread(glyph->buffer, 1, glyph->size, file);
  }
  fclose(file);
}

void fnt_unload(fnt_t *fnt)
{
  for (u2 i = 0; i < FNT_NUM_GLYPHS; i++)
  {
    free(fnt->glyphs[i].buffer);
  }
}

void fnt_palette_apply(u1 *palette, fnt_t *fnt)
{
  palette_apply(palette, &fnt->palette);
}

s2 fnt_compute_width(fnt_t* fnt, const char* text)
{
  s4 index = 0;
  s4 length = strlen(text);
  s2 computed_width = 0;
  for (index = 0; index < length; index++)
  {
    u1 character = text[index];
    fnt_glyph_t *glyph = &(fnt->glyphs[character]);
    computed_width += glyph->header.width;
  }
  return computed_width;
}

void fnt_write(u1 *framebuffer, fnt_t* fnt, const char* text, s2 dx, s2 dy)
{
  s4 index = 0;
  s4 length = strlen(text);

  s2 cx = dx;
  s2 cy = dy;
  for (index = 0; index < length; index++)
  {
    u1 character = text[index];
    fnt_glyph_t *glyph = &(fnt->glyphs[character]);
    buffer_draw(
      framebuffer,
      glyph->buffer,
      glyph->header.width,
      glyph->header.height,
      cx,
      cy + glyph->header.y
    );
    if (character == 32)
    {
      cx += fnt->avg_width;
    }
    else
    {
      cx += glyph->header.width + 1;
    }
  }
}

void fnt_write_aligned(u1 *framebuffer, fnt_t *fnt, const char *text, s2 dx, s2 dy, u1 alignment)
{
  // TODO: Debemos calcular el ancho y el alto para poder establecer qué offset deben
  // tener las coordenadas.
}
