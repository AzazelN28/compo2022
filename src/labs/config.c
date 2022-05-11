#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 1024 

typedef struct ini_
{
  char *name;
  char *value;
  struct ini_ *next;
} ini_t;

void ini_load_from_file(const char* filename, ini_t **start)
{
  FILE* file = fopen("config.txt", "rb");

  int name_len = 0, value_len = 0;
  char name[MAX_LENGTH], value[MAX_LENGTH];

  ini_t *current = NULL, *prev = NULL;
  while (!feof(file))
  {
    current = calloc(1, sizeof(ini_t));

    memset(name, 0, MAX_LENGTH);
    memset(value, 0, MAX_LENGTH);

    fscanf(file, "%s = %s\n", name, value);

    name_len = strlen(name);
    value_len = strlen(value);

    if (!name_len || !value_len)
    {
      continue;
    }

    current->name = calloc(1, name_len);
    memcpy(current->name, name, name_len);

    current->value = calloc(1, value_len);
    memcpy(current->value, value, value_len);
    
    if (*start == NULL)
    {
      *start = current;
    }
    else
    {
      prev->next = current;
    }

    prev = current;
  }
  fclose(file);
}

void ini_unload(ini_t *start)
{
  ini_t* current = NULL, *next = NULL;
  for (current = start; current != NULL; current = next)
  {
    free(current->name);
    free(current->value);

    next = current->next;

    free(current);
  }
}

ini_t *ini_find_value(ini_t* start, const char* name)
{
  ini_t* current = NULL;
  for (current = start; current != NULL; current = current->next)
  {
    if (!strcmp(current->name, name))
    {
      return current;
    }
  }
  return NULL;
}

ini_t *ini_find_value_as_int(ini_t* start, const char* name, int* value)
{
  ini_t *found = ini_find_value(start, name);
  if (found == NULL)
  {
    return NULL;
  }
  *value = atoi(found->value);
  return found;
}

ini_t *ini_find_value_as_float(ini_t* start, const char* name, double* value)
{
  ini_t *found = ini_find_value(start, name);
  if (found == NULL)
  {
    return NULL;
  }
  *value = atof(found->value);
  return found;
}

int main(int argc, char** argv)
{
  ini_t *start = NULL;
  ini_load_from_file("config.txt", &start);

  int width, height, jander;

  ini_find_value_as_int(start, "width", &width);
  ini_find_value_as_int(start, "height", &height);
  ini_find_value_as_int(start, "jander", &jander);

  ini_unload(start);

  printf("%dx%d %d\n", width, height, jander);
  return 0;
}
