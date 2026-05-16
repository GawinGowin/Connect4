#include "ft_printf_int.h"

int ft_vdprintf(int fd, const char *fmt, va_list args) {
  int i;
  int cnt;

  i = 0;
  cnt = 0;
  while (fmt[i] != '\0') {
    if (fmt[i] == '%') {
      cnt += switch_fmt_render(fmt[i + 1])(fd, args, fmt[i + 1]);
      i++;
    } else if (write(fd, &fmt[i], 1) != -1)
      cnt++;
    i++;
  }
  return (cnt);
}

int ft_dprintf(int fd, const char *fmt, ...) {
  va_list args;
  int cnt;

  va_start(args, fmt);
  cnt = ft_vdprintf(fd, fmt, args);
  va_end(args);
  return (cnt);
}
