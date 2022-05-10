#include "types.h"

/**
 * Interpolación lineal.
 */
f4 linearf(f4 x, f4 a, f4 b)
{
  return (1.0 - x) * a + x * b;
}

/**
 * Interpolación cuadrática.
 */
f4 quadraticf(f4 x, f4 a, f4 b, f4 c)
{
  return linearf(x, linearf(x, a, b), linearf(x, b, c));
}

/**
 * Interpolación cúbica.
 */
f4 cubicf(f4 x, f4 a, f4 b, f4 c, f4 d)
{
  return linearf(x, quadraticf(x, a, b, c), quadraticf(x, b, c, d));
}
