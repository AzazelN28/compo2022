#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../div.h"
#include "../types.h"

void pal_load_from_file(const char* filename, div_palette_t* palette)
{
  assert(filename != NULL && palette != NULL);
  FILE *file = fopen(filename, "rb");
  assert(file != NULL);
  fread(palette, 1, sizeof(div_palette_t), file);
  fclose(file);
}

void map_load_from_file(const char* filename, div_map_t* map)
{
  assert(filename != NULL && map != NULL);
  FILE *file = fopen(filename, "rb");
  assert(file != NULL);
  fread(&map->header, 1, sizeof(div_map_header_t), file);
  fread(&map->palette, 1, sizeof(div_palette_t), file);
  fread(&map->cpoints.num, 1, sizeof(u2), file);
  map->cpoints.list = malloc(sizeof(div_cpoint_t) * map->cpoints.num);
  for (u2 i = 0; i < map->cpoints.num; i++)
  {
    fread(&map->cpoints.list[i], 1, sizeof(div_cpoint_t), file);
  }
  map->pixels = malloc(sizeof(u1) * map->header.width * map->header.height);
  fread(&map->pixels, 1, map->header.width * map->header.height, file);
  fclose(file);
}

void fpg_load_from_file(const char* filename, div_fpg_t* fpg)
{
  assert(filename != NULL && fpg != NULL);
  FILE *file = fopen(filename, "rb");
  assert(file != NULL);
  fread(&fpg->header, 1, sizeof(div_fpg_header_t), file);
  fread(&fpg->palette, 1, sizeof(div_palette_t), file);
  div_fpg_map_t *current = NULL, *prev = NULL;
  while (!feof(file)) {
    current = malloc(sizeof(div_fpg_map_t));
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
    fread(&current->header, 1, sizeof(div_fpg_map_header_t), file);
    fread(&current->cpoints.num, 1, sizeof(u4), file);
    current->cpoints.list = malloc(sizeof(div_cpoint_t) * current->cpoints.num);
    for (u4 i = 0; i < current->cpoints.num; i++)
    {
      fread(&current->cpoints.list[i], 1, sizeof(div_cpoint_t), file);
    }
    current->pixels = malloc(sizeof(u1) * current->header.width * current->header.height);
    fread(&current->pixels, 1, current->header.width * current->header.height, file);
    prev = current;
  }
  fclose(file);
}
