#include <stdio.h>

#define LINEAR(x, a, b) (((1 - x) * a) + (x * b))
#define QUADRATIC(x, a, b, c) LINEAR(x, LINEAR(x, a, b), LINEAR(x, b, c))
#define CUBIC(x, a, b, c, d) LINEAR(x, QUADRATIC(x, a, b, c), QUADRATIC(x, b, c, d))

int main(int argc, char** argv) {
  printf("%f\n", LINEAR(0.5, 0, 100));
  printf("%f\n", QUADRATIC(0.5, 0, 50, 100));
  printf("%f\n", CUBIC(0.5, 0, 50, 50, 100));
  return 0;
}
