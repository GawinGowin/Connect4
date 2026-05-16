#include "libft_int.h"

static int digit_value(char c) {
  if (c >= '0' && c <= '9')
    return (c - '0');
  if (c >= 'a' && c <= 'z')
    return (c - 'a' + 10);
  if (c >= 'A' && c <= 'Z')
    return (c - 'A' + 10);
  return (-1);
}

long ft_strtol(const char *nptr, char **endptr, int base) {
  const char *p;
  int sign;
  unsigned long result;
  int digit;

  p = nptr;
  while ((*p >= '\t' && *p <= '\r') || *p == ' ')
    p++;
  sign = 1;
  if (*p == '-') {
    sign = -1;
    p++;
  } else if (*p == '+')
    p++;
  if ((base == 16 || base == 0) && p[0] == '0' && (p[1] == 'x' || p[1] == 'X')) {
    base = 16;
    p += 2;
  } else if (base == 0 && p[0] == '0') {
    base = 8;
  } else if (base == 0) {
    base = 10;
  }
  result = 0;
  while (1) {
    digit = digit_value(*p);
    if (digit < 0 || digit >= base)
      break;
    if (result > (ULONG_MAX - (unsigned long)digit) / (unsigned long)base)
      result = ULONG_MAX;
    else
      result = result * (unsigned long)base + (unsigned long)digit;
    p++;
  }
  if (endptr)
    *endptr = (char *)p;
  if (sign == 1)
    return (result > (unsigned long)LONG_MAX ? LONG_MAX : (long)result);
  if (result > (unsigned long)LONG_MAX + 1)
    return (LONG_MIN);
  return (-(long)result);
}
