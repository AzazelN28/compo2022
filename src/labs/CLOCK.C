#include <time.h>
#include <stdio.h>
#include <bios.h>

int main(int argc, char** argv)
{
  while (!bioskey(0x11))
  {
    printf("%f seconds\r", (float)clock() / (float)CLOCKS_PER_SEC);
  }
  return 0;
}
