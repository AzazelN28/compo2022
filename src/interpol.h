#include "types.h"

#define LINEAR(x, a, b) ((1 - x) * a + x * b)
#define QUADRATIC(x, a, b, c) LINEAR(x, LINEAR(x, a, b), LINEAR(x, b, c))
#define CUBIC(x, a, b, c, d) LINEAR(x, QUADRATIC(x, a, b, c), QUADRATIC(x, b, c, d))

f4 linearf(f4 x, f4 a, f4 b);
f4 quadraticf(f4 x, f4 a, f4 b, f4 c);
f4 cubicf(f4 x, f4 a, f4 b, f4 c, f4 d);
