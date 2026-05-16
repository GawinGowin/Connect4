#include "connect4.h"
#include "libft.h"

static t_parse_err parse_posint(const char *s, int *out, int min, int max);
static const char *parse_err_to_str(t_parse_err err);

t_parse_err parse_args(int argc, char **argv, t_args *ret) {
  int pos = 0;

  ft_memset(ret, 0, sizeof(t_args));
  for (int i = 1; i < argc; i++) {
    if (pos == 0) {
      t_parse_err e = parse_posint(argv[i], &ret->rows, 6, MAX_ROWS);
      if (e)
        return e;
    } else if (pos == 1) {
      t_parse_err e = parse_posint(argv[i], &ret->cols, 7, MAX_COLS);
      if (e)
        return e;
    } else
      return PARSE_USAGE;
    pos++;
  }
  if (pos != 2)
    return PARSE_USAGE;
  return PARSE_OK;
}

static t_parse_err parse_posint(const char *s, int *value, int min, int max) {
  char *endptr;
  long gained_value = ft_strtol(s, &endptr, 10);

  if (*endptr != '\0') {
    return PARSE_NOT_DIGIT;
  }
  if (gained_value < 0) {
    return PARSE_NEGATIVE;
  }
  if (gained_value < min) {
    return PARSE_TOO_SMALL;
  }
  if (gained_value > max) {
    return PARSE_TOO_BIG;
  }
  *value = (int)gained_value;
  return PARSE_OK;
}
void print_usage(char *program, t_parse_err err) {
  const char *msg = parse_err_to_str(err);
  if (msg)
    ft_printf("%s: %s\n", program, msg);
  ft_printf("Usage: %s <rows> <cols>\n", program);
  ft_printf("  6 <= rows <= %d, 7 <= cols <= %d\n", MAX_ROWS, MAX_COLS);
}

static const char *parse_err_to_str(t_parse_err err) {
  switch (err) {
  case PARSE_USAGE:
    return NULL;
  case PARSE_NOT_DIGIT:
    return "expected a numerical parameter";
  case PARSE_NEGATIVE:
    return "expected a positive number";
  case PARSE_TOO_SMALL:
    return "number too small";
  case PARSE_TOO_BIG:
    return "number too large";
  default:
    return "unknown error";
  }
}
