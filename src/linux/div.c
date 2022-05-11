#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../div.h"
#include "../types.h"
#include "../palette.h"
#include "../framebuf.h"
#include "../buffer.h"

void palette_apply(u1* palette, palette_t* source)
{
  for (u2 i = 0; i < PAL_COLORS; i++)
  {
    palette_set_color(
      palette,
      i,
      source->colors[i].r,
      source->colors[i].g,
      source->colors[i].b
    );
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

void pal_palette_apply(u1* palette, pal_t* pal)
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
  if (map->cpoints.num > 0) {
    map->cpoints.list = calloc(1, sizeof(cpoint_t) * map->cpoints.num);
    fread(map->cpoints.list, map->cpoints.num, sizeof(cpoint_t), file);
  } else {
    map->cpoints.list = NULL;
  }
  u4 size = map->header.width *map->header.height;
  map->buffer = calloc(1, size);
  fread(map->buffer, 1, size, file);
  fclose(file);
}

void map_unload(map_t* map)
{
  if (map->cpoints.list != NULL)
  {
    free(map->cpoints.list);
  }
  free(map->buffer);
}

void map_palette_apply(u1* palette, map_t* map)
{
  palette_apply(palette, &map->palette);
}

u1 map_get_pixel(map_t* map, u2 x, u2 y)
{
  u4 offset = OFFSET(x, y, map->header.width);
  return map->buffer[offset];
}

void map_draw(u1* framebuffer, map_t* map, u2 dx, u2 dy)
{
  u2 ty, tx, y, x;
  for (y = 0; y < map->header.height; y++)
  {
    ty = dy + y;
    if (ty >= FRAMEBUFFER_HEIGHT)
    {
      printf("Break on through to the other side\n");
      break;
    }

    for (x = 0; x < map->header.width; x++)
    {
      tx = dx + x;
      u4 offset_from = OFFSET(x, y, map->header.width);
      if (tx >= FRAMEBUFFER_WIDTH)
      {
        printf("Break on the wall\n");
        break;
      }
      u4 offset_to = OFFSET(tx, ty, FRAMEBUFFER_WIDTH);
      framebuffer[offset_to] = map->buffer[offset_from];
      // framebuffer_set_pixel(framebuffer, ty, tx, map->buffer[offset_from]);
    }
  }
  printf("Drawn %dx%d pixels\n", x, y);
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
    fread(&current->header, 1, sizeof(fpg_map_header_t), file);
    /*
    printf("Código: %d\n", current->header.code);
    printf("Longitud: %d\n", current->header.length);
    printf("Descripción: %s\n", current->header.description);
    printf("Nombre: %s\n", current->header.filename);
    printf("Ancho: %d\n", current->header.width);
    printf("Alto: %d\n", current->header.height);
    */
    fread(&current->cpoints.num, 1, sizeof(u4), file);
    if (current->cpoints.num > 0)
    {
      current->cpoints.list = calloc(1, sizeof(cpoint_t) * current->cpoints.num);
      fread(current->cpoints.list, current->cpoints.num, sizeof(cpoint_t), file);
      /*
      printf("Puntos de control %d\n", current->cpoints.num);
      for (u4 i = 0; i < current->cpoints.num; i++)
      {
        printf("\tPunto de control %d: %d, %d\n", i, current->cpoints.list[i].x, current->cpoints.list[i].y);
      }
      */
    } else {
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
  for (fpg_map_t* current = fpg->maps; current != NULL; current = current->next)
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

void fnt_load_from_file(const char *filename, fnt_t *fnt)
{
  assert(filename != NULL && fnt != NULL);
  FILE *file = fopen(filename, "rb");
  assert(file != NULL);
  fread(&fnt->header, 1, sizeof(fnt_header_t), file);
  fread(&fnt->palette, 1, sizeof(palette_t), file);
  fread(&fnt->charset, 1, sizeof(u4), file);
  for (u2 i = 0; i < FNT_NUM_GLYPHS; i++)
  {
    fnt_glyph_t *glyph = &(fnt->glyphs[i]);
    fread(&glyph->header, 1, sizeof(fnt_glyph_header_t), file);
    glyph->size = glyph->header.width * glyph->header.height;
    glyph->buffer = (u1 *)(calloc(1, glyph->size));
  }

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
